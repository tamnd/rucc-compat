//! A Linux kernel built by rk, read as two corpora: its units for the `-E` differential, and its
//! probes as a differential of their own.
//!
//! rk is the kernel harness in tamnd/rucc-kernel. It builds a pinned kernel with kbuild's output
//! in a directory of its own, through a compiler shim that appends one JSON line per compiler call
//! to `compile.jsonl` there, and writes `build.json` next to it naming the version, the row, the
//! configuration, the era and the compiler. That directory is the corpus, the way a meson build
//! directory is for Postgres, and the log is the list of cases.
//!
//! A call in the log is one of two things. A unit is a C or assembly file compiled to an object
//! that ends up in the kernel, and those go through the same machinery as a compile database
//! entry, so `run` compares them the way it compares every other file. A probe is a question
//! kbuild asked the compiler and threw the output of away, such as whether it takes
//! `-fcf-protection=branch`. kbuild reads the answer from whether the call succeeded, so a probe
//! rucc says no to and GCC says yes to is a flag kbuild quietly leaves out, which changes the
//! kernel before a single unit is compiled. Those are asked again of both compilers here and the
//! answers compared.
//!
//! Only a build made with GCC is read. The reference is what the build was made with, and a build
//! rucc made would be comparing rucc against itself.

use std::collections::HashMap;
use std::fmt::Write as _;
use std::fs;
use std::path::{Path, PathBuf};
use std::process::Command;
use std::time::Duration;

use crate::corpus::{Build, Builder, Corpus, Persona, Question, Register, Source, Unit, UnitKind};
use crate::differ::{self, Found, Settings, rule};
use crate::ledger;
use crate::meson::{self, Entry, Value};
use crate::sandbox::{self, Limits};
use crate::sha256;
use crate::toml::Error;
use crate::work;

/// The compile log's name in kbuild's output directory.
pub const LOG: &str = "compile.jsonl";

/// The build summary's name, next to the log.
pub const SUMMARY: &str = "build.json";

/// What a unit's source has to contain for it to be one that exports a symbol.
///
/// Those are always taken whatever the sample says. `genksyms` computes the CRC of every exported
/// symbol from the `-E` output of the file that exports it, and a module built by GCC loads into a
/// kernel built by rucc only when the CRCs agree, so for these files the preprocessed text is the
/// ABI. `EXPORT_SYMBOL_GPL` and the namespaced forms all start with this.
const EXPORTS: &str = "EXPORT_SYMBOL";

/// One line of `compile.jsonl`, the part of it this reads.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Record {
    /// The command line as kbuild wrote it. The first word is the shim.
    pub argv: Vec<String>,
    /// The compiler that actually ran.
    pub compiler: String,
    /// The directory it ran in, which is kbuild's output directory.
    pub cwd: PathBuf,
    /// The files it read, as the command line spelled them.
    pub inputs: Vec<String>,
    /// The exit status, or `None` for a compiler that died on a signal.
    pub exit: Option<i32>,
    /// Whether the call was a probe rather than a unit.
    pub probe: bool,
}

impl Record {
    /// Whether the compiler said yes.
    #[must_use]
    pub fn succeeded(&self) -> bool {
        self.exit == Some(0)
    }

    /// The C or assembly source a unit compiles.
    #[must_use]
    pub fn source(&self) -> Option<&str> {
        self.inputs
            .iter()
            .find(|path| Path::new(path).extension().is_some_and(|e| e == "c" || e == "S"))
            .map(String::as_str)
    }

    /// Whether this is a unit: not a probe, compiled with `-c`, and from a `.c` or `.S` file.
    ///
    /// The same test rk's `is_unit` makes, so the two tools count the same calls.
    #[must_use]
    pub fn is_unit(&self) -> bool {
        !self.probe && self.argv.iter().any(|a| a == "-c") && self.source().is_some()
    }

    /// The object the call wrote, as the command line spelled it.
    #[must_use]
    pub fn output(&self) -> Option<&str> {
        let at = self.argv.iter().position(|a| a == "-o")?;
        self.argv.get(at + 1).map(String::as_str)
    }
}

/// Reads a compile log, skipping lines that do not parse.
///
/// A line can be cut short when a build is killed part way through a write, and one bad line
/// should not cost the other ten thousand. The count of lines skipped comes back with the records
/// so the caller can say so.
#[must_use]
pub fn records(text: &str) -> (Vec<Record>, usize) {
    let mut out = Vec::new();
    let mut skipped = 0;
    for line in text.lines().filter(|l| !l.trim().is_empty()) {
        match meson::parse(line).ok().as_ref().and_then(record) {
            Some(r) => out.push(r),
            None => skipped += 1,
        }
    }
    (out, skipped)
}

fn record(value: &Value) -> Option<Record> {
    let strings = |key: &str| -> Option<Vec<String>> {
        match value.get(key) {
            None => Some(Vec::new()),
            Some(Value::Array(items)) => {
                items.iter().map(|v| v.as_str().map(str::to_owned)).collect()
            }
            Some(_) => None,
        }
    };
    let argv = strings("argv")?;
    if argv.is_empty() {
        return None;
    }
    let inputs = match value.get("inputs") {
        None => Vec::new(),
        Some(Value::Array(items)) => items
            .iter()
            .map(|i| i.get("path").and_then(Value::as_str).map(str::to_owned))
            .collect::<Option<Vec<String>>>()?,
        Some(_) => return None,
    };
    let exit = match value.get("exit") {
        Some(Value::Number(n)) => Some(n.parse().ok()?),
        _ => None,
    };
    Some(Record {
        argv,
        compiler: value.get("compiler").and_then(Value::as_str).unwrap_or_default().to_owned(),
        cwd: PathBuf::from(value.get("cwd").and_then(Value::as_str)?),
        inputs,
        exit,
        probe: matches!(value.get("probe"), Some(Value::Bool(true))),
    })
}

/// What `build.json` says about the build, the part of it this reads.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Summary {
    /// The kernel version, as in `7.2.8`.
    pub version: String,
    /// The era, as in `E11`.
    pub era: String,
    /// The row, as in `x86_64`.
    pub row: String,
    /// The configuration target, as in `defconfig`.
    pub config: String,
    /// The first line of the compiler's `--version`.
    pub compiler: String,
    /// Whether rk took the compiler for rucc.
    pub rucc: bool,
}

impl Summary {
    /// Whether the build was made with GCC, which is what the reference has to be.
    #[must_use]
    pub fn is_gcc(&self) -> bool {
        !self.rucc && (self.compiler.contains("gcc") || self.compiler.contains("GCC"))
    }
}

/// Reads `build.json`.
///
/// # Errors
///
/// When it is not JSON, or does not name a version, an era and a compiler.
pub fn summary(text: &str, whose: &str) -> Result<Summary, Error> {
    let fail = |message: &str| Error { message: format!("{whose}: {message}") };
    let doc = meson::parse(text).map_err(|e| fail(&e))?;
    let field = |key: &str| doc.get(key).and_then(Value::as_str).map(str::to_owned);
    let compiler = doc.get("compiler").ok_or_else(|| fail("names no compiler"))?;
    Ok(Summary {
        version: field("version").ok_or_else(|| fail("names no version"))?,
        era: field("era").ok_or_else(|| fail("names no era"))?,
        row: field("row").unwrap_or_default(),
        config: field("config").unwrap_or_default(),
        compiler: compiler.get("version").and_then(Value::as_str).unwrap_or_default().to_owned(),
        rucc: matches!(compiler.get("rucc"), Some(Value::Bool(true))),
    })
}

/// Reads a build directory's summary and log, after checking the build is the one the manifest is
/// about.
///
/// # Errors
///
/// When either file is missing or unreadable, or the build is of another version, of another era,
/// or was not made with GCC.
pub fn read(build: &Path, version: &str, persona: &Persona) -> Result<Vec<Record>, Error> {
    let load = |name: &str| {
        let path = build.join(name);
        fs::read_to_string(&path)
            .map_err(|e| Error { message: format!("{}: {e}", path.display()) })
            .map(|text| (text, path.display().to_string()))
    };
    let (text, whose) = load(SUMMARY)?;
    let summary = summary(&text, &whose)?;
    if summary.version != version {
        return Err(Error {
            message: format!(
                "{} is a build of linux {}, and the manifest is about {version}",
                build.display(),
                summary.version
            ),
        });
    }
    if !summary.is_gcc() {
        return Err(Error {
            message: format!(
                "{} was built with `{}`, and the reference has to be GCC",
                build.display(),
                summary.compiler
            ),
        });
    }
    if summary.era != persona.era {
        return Err(Error {
            message: format!(
                "{} is a build of era {}, and the manifest's persona is for {}",
                build.display(),
                summary.era,
                persona.era
            ),
        });
    }
    let (text, whose) = load(LOG)?;
    let (records, skipped) = records(&text);
    if skipped > 0 {
        eprintln!("{whose}: {skipped} lines did not parse and were skipped");
    }
    Ok(records)
}

/// The version and persona of a corpus made from an rk build.
fn pinned(corpus: &Corpus) -> Option<(&str, &Persona)> {
    match &corpus.source {
        Source::Build(Build { version, builder: Builder::Rk(persona), .. }) => {
            Some((version.as_str(), persona))
        }
        _ => None,
    }
}

/// The kernel source tree, from the `source` link kbuild leaves in an output directory that is
/// not the tree itself.
fn source_tree(build: &Path) -> Option<PathBuf> {
    let link = fs::read_link(build.join("source")).ok()?;
    Some(if link.is_absolute() { link } else { build.join(link) })
}

/// Which of the named units a `kernel-units` unit takes.
///
/// `size` of them by a hash of the name, the ones whose hashes come first, which picks the same
/// units every time and spreads them over the tree without anybody choosing. Then every unit
/// `exports` says yes to, whether or not the hash picked it. `None` takes everything.
#[must_use]
pub fn sample(names: &[String], size: Option<usize>, exports: impl Fn(usize) -> bool) -> Vec<bool> {
    let Some(size) = size else { return vec![true; names.len()] };
    let mut ranked: Vec<(String, usize)> =
        names.iter().enumerate().map(|(at, name)| (sha256::hex(name.as_bytes()), at)).collect();
    ranked.sort();
    let mut taken = vec![false; names.len()];
    for (_, at) in ranked.into_iter().take(size) {
        taken[at] = true;
    }
    for (at, slot) in taken.iter_mut().enumerate() {
        if !*slot && exports(at) {
            *slot = true;
        }
    }
    taken
}

/// The units of a kernel build as cases of one unit, each with the flags kbuild compiled it with.
///
/// A case is named after its source relative to the kernel tree, or to the output directory for a
/// file the build generated. The flags are the unit's own minus `-c`, the object and the
/// dependency file, which is what [`meson::compile_flags`] takes out of a compile database entry.
///
/// # Errors
///
/// When the build cannot be read or is not the one the manifest names.
pub fn unit_cases(
    build: &Path,
    corpus: &Corpus,
    unit: &Unit,
    out: &mut Found,
) -> Result<(), Error> {
    let (version, persona) = pinned(corpus).ok_or_else(|| Error {
        message: format!("{}: a kernel unit in a corpus rk did not build", corpus.name),
    })?;
    let records = read(build, version, persona)?;
    let entries: Vec<Entry> = records
        .iter()
        .filter(|r| r.is_unit())
        .map(|r| Entry {
            directory: r.cwd.clone(),
            file: r.source().unwrap_or_default().to_owned(),
            output: r.output().unwrap_or_default().to_owned(),
            arguments: r.argv.clone(),
        })
        .collect();
    let mut roots: Vec<PathBuf> = source_tree(build).into_iter().collect();
    roots.push(build.to_path_buf());
    let named =
        meson::names(&entries, &roots, |e| Some(e.output.clone()).filter(|o| !o.is_empty()));
    let exports = |at: usize| {
        let entry = &entries[at];
        fs::read(entry.directory.join(&entry.file))
            .is_ok_and(|text| text.windows(EXPORTS.len()).any(|w| w == EXPORTS.as_bytes()))
    };
    let taken = sample(&named, unit.sample, exports);
    for ((entry, name), take) in entries.iter().zip(&named).zip(taken) {
        if take {
            meson::offer(entry, name, unit, out);
        }
    }
    Ok(())
}

/// What a probe asks: its arguments without the compiler, the persona, the output and the names
/// of temporary files, which change from run to run.
///
/// This is `question` in rk's `probes.rs`, word for word, so that a disagreement found here and one
/// `rk probes` found can be matched by their text.
#[must_use]
pub fn question(argv: &[String]) -> String {
    let mut words = Vec::new();
    let mut args = argv.iter().skip(1);
    while let Some(arg) = args.next() {
        if arg == "-o" {
            args.next();
            continue;
        }
        if arg.starts_with("-fgnuc-version=") || (arg.starts_with("-o") && arg.len() > 2) {
            continue;
        }
        if arg.contains(".tmp_") {
            words.push("TMP".to_owned());
            continue;
        }
        words.push(arg.clone());
    }
    words.join(" ")
}

/// A probe's arguments, without the compiler, with its output sent to `out` instead of where the
/// record says.
///
/// The record's output is usually a file in a `.tmp_` directory that kbuild removed as soon as it
/// had its answer, or `/dev/null`, and neither is somewhere two compilers running side by side
/// should both write.
#[must_use]
pub fn replay(argv: &[String], out: &Path) -> Vec<String> {
    let out = out.to_string_lossy().into_owned();
    let mut words = Vec::new();
    let mut args = argv.iter().skip(1);
    while let Some(arg) = args.next() {
        if arg == "-o" {
            args.next();
            words.push("-o".to_owned());
            words.push(out.clone());
        } else if arg.starts_with("-o") && arg.len() > 2 {
            words.push("-o".to_owned());
            words.push(out.clone());
        } else {
            words.push(arg.clone());
        }
    }
    words
}

/// Whether a probe reads its program from standard input, which the log does not keep.
///
/// kbuild's `as-instr` and the `asm goto` tests pipe a program in with `-` as the input, and the
/// answer depends on the program. Asked again with nothing on standard input they would both say
/// yes to everything, so they are not asked at all.
#[must_use]
pub fn reads_stdin(argv: &[String]) -> bool {
    let mut previous = "";
    for arg in argv.iter().skip(1) {
        if arg == "-" && previous != "-o" {
            return true;
        }
        previous = arg;
    }
    false
}

/// One question kbuild asked, however many times it asked it.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Probe {
    /// The question, in rk's form.
    pub question: String,
    /// The first call that asked it.
    pub argv: Vec<String>,
    /// Where that call ran.
    pub cwd: PathBuf,
    /// What the build's compiler answered the first time.
    pub recorded: bool,
    /// How many calls asked it.
    pub asked: usize,
}

/// The probes in a log, one per question, in the order they were first asked.
///
/// kbuild asks the same question from every directory whose Makefile tests the flag, so a build
/// has thousands of probe calls and a few hundred questions. Asking each question once is the
/// same differential at a tenth of the cost.
#[must_use]
pub fn probes(records: &[Record]) -> Vec<Probe> {
    let mut out: Vec<Probe> = Vec::new();
    let mut seen: HashMap<String, usize> = HashMap::new();
    for record in records.iter().filter(|r| r.probe) {
        let question = question(&record.argv);
        match seen.get(&question) {
            Some(&at) => out[at].asked += 1,
            None => {
                seen.insert(question.clone(), out.len());
                out.push(Probe {
                    question,
                    argv: record.argv.clone(),
                    cwd: record.cwd.clone(),
                    recorded: record.succeeded(),
                    asked: 1,
                });
            }
        }
    }
    out
}

/// What came of asking one probe of both compilers.
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum Status {
    /// Both said the same thing.
    Same,
    /// The reference said yes and rucc said no, with what rucc said. kbuild leaves out whatever
    /// the probe was about.
    No(String),
    /// The reference said no and rucc said yes. kbuild puts in something GCC would not have been
    /// given.
    Yes,
    /// The probe reads standard input, which the log does not keep, so it was not asked.
    NotAsked,
    /// The reference could not be run on it at all.
    Unsupported(String),
}

impl Status {
    /// A word for the table.
    #[must_use]
    pub fn word(&self) -> &'static str {
        match self {
            Status::Same => "same",
            Status::No(_) => "rucc no",
            Status::Yes => "rucc yes",
            Status::NotAsked => "not asked",
            Status::Unsupported(_) => "unsupported",
        }
    }

    /// Whether the two compilers answered differently.
    #[must_use]
    pub fn disagrees(&self) -> bool {
        matches!(self, Status::No(_) | Status::Yes)
    }
}

/// One probe and what came of it.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Outcome {
    /// The case name, which is the unit and the question.
    pub case: String,
    /// The question on its own, which is what the register matches.
    pub question: String,
    /// What happened.
    pub status: Status,
    /// The divergence that covers it, when the register has one.
    pub accepted: Option<String>,
    /// Whether the reference answered differently from the build it is supposed to have made,
    /// which says `--cc` is not that compiler.
    pub drifted: bool,
}

impl Outcome {
    /// Whether this outcome fails the run.
    #[must_use]
    pub fn is_failure(&self) -> bool {
        self.accepted.is_none() && self.status.disagrees()
    }
}

/// Everything the probes of one build came to.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Report {
    /// Which corpus.
    pub corpus: String,
    /// How many probe calls the log had.
    pub calls: usize,
    /// Every question, in the order they ran.
    pub outcomes: Vec<Outcome>,
}

impl Report {
    /// How many questions ended each way.
    #[must_use]
    pub fn count(&self, word: &str) -> usize {
        self.outcomes.iter().filter(|o| o.status.word() == word).count()
    }

    /// How many questions fail the run.
    #[must_use]
    pub fn failures(&self) -> usize {
        self.outcomes.iter().filter(|o| o.is_failure()).count()
    }

    /// One line, for the terminal.
    #[must_use]
    pub fn summary(&self) -> String {
        let accepted = self.outcomes.iter().filter(|o| o.accepted.is_some()).count();
        let drifted = self.outcomes.iter().filter(|o| o.drifted).count();
        format!(
            "{}: {} probe calls, {} questions, {} same, {} not asked, {} unsupported, {} accepted, {} failing, {} where the reference disagrees with the build",
            self.corpus,
            self.calls,
            self.outcomes.len(),
            self.count("same"),
            self.count("not asked"),
            self.count("unsupported"),
            accepted,
            self.failures(),
            drifted
        )
    }
}

/// How long one probe gets. A probe compiles an empty file, so this is generous, and it is there
/// for a compiler that hangs rather than for one that is slow.
const PROBE_TIME: Duration = Duration::from_secs(30);

/// One compiler's answer: yes, or no with the first thing it said.
fn ask(
    program: &Path,
    extra: &[String],
    probe: &Probe,
    out: &Path,
) -> Result<Result<(), String>, String> {
    let mut args = extra.to_vec();
    args.extend(replay(&probe.argv, out));
    let limits = Limits { timeout: PROBE_TIME, memory: None };
    let ran = sandbox::run(program, &args, &probe.cwd, &limits);
    let _ = fs::remove_file(out);
    let ran = ran?;
    Ok(if ran.end.is_clean() { Ok(()) } else { Err(ran.complaint()) })
}

/// Asks every probe of a kernel build again, of the reference and of rucc with the era's persona,
/// and compares the answers.
///
/// # Errors
///
/// When the build cannot be read or is not the one the manifest names.
pub fn run(
    repo: &Path,
    corpus: &Corpus,
    settings: &Settings,
    register: &Register,
    scratch: &Path,
) -> Result<Report, Error> {
    let (version, persona) = pinned(corpus)
        .ok_or_else(|| Error { message: format!("{}: not a kernel build", corpus.name) })?;
    let Some(unit) = corpus.units.iter().find(|u| u.kind == UnitKind::KernelProbes) else {
        return Err(Error { message: format!("{}: no `kernel-probes` unit", corpus.name) });
    };
    if settings.unit.as_ref().is_some_and(|u| *u != unit.name) {
        return Err(Error {
            message: format!(
                "{}: there is no unit called `{}`",
                corpus.name,
                settings.unit.as_deref().unwrap_or_default()
            ),
        });
    }
    let records = read(&corpus.tree(repo), version, persona)?;
    let calls = records.iter().filter(|r| r.probe).count();
    let all: Vec<(String, Probe)> = probes(&records)
        .into_iter()
        .map(|p| (format!("{}/{}", unit.name, p.question), p))
        .filter(|(name, _)| {
            !unit.skip.iter().any(|s| name.strip_prefix(&format!("{}/", unit.name)) == Some(s))
        })
        .collect();
    let record = ledger::path(repo, &corpus.name, "run", None);
    let keep = ledger::Keep::new(&settings.only, settings.failed.then_some(record.as_path()))
        .map_err(|message| Error { message: format!("{}: {message}", corpus.name) })?;
    let all: Vec<(String, Probe)> = all.into_iter().filter(|(name, _)| keep.wants(name)).collect();
    if all.is_empty() && !keep.is_all() {
        return Err(Error { message: format!("{}: {}", corpus.name, keep.emptiness()) });
    }
    let all = match settings.limit {
        Some(limit) => &all[..limit.min(all.len())],
        None => &all[..],
    };
    fs::create_dir_all(scratch)
        .map_err(|e| Error { message: format!("{}: {e}", scratch.display()) })?;
    let cc = differ::program(&settings.cc);
    let rucc = differ::program(&settings.rucc);
    let flags = corpus.persona().unwrap_or_default();
    let numbered: Vec<(usize, &(String, Probe))> = all.iter().enumerate().collect();
    let outcomes = work::spread(&numbered, work::jobs(settings.jobs), |(at, (name, probe))| {
        let status = if reads_stdin(&probe.argv) {
            (Status::NotAsked, false)
        } else {
            let theirs = ask(&cc, &[], probe, &scratch.join(format!("probe-{at}-cc.out")));
            let ours = ask(&rucc, &flags, probe, &scratch.join(format!("probe-{at}-rucc.out")));
            match (theirs, ours) {
                (Err(why), _) => (Status::Unsupported(why), false),
                (Ok(theirs), ours) => {
                    let drifted = theirs.is_ok() != probe.recorded;
                    let ours = ours.and_then(|answer| answer);
                    let status = match (theirs.is_ok(), ours) {
                        (true, Ok(())) | (false, Err(_)) => Status::Same,
                        (true, Err(why)) => Status::No(why),
                        (false, Ok(())) => Status::Yes,
                    };
                    (status, drifted)
                }
            }
        };
        let (status, drifted) = status;
        let accepted = status
            .disagrees()
            .then(|| {
                register.accepts(Question {
                    rule: rule::ANSWER,
                    corpus: &corpus.name,
                    unit: &unit.name,
                    text: &probe.question,
                })
            })
            .flatten()
            .map(|d| d.id.clone());
        Outcome { case: name.clone(), question: probe.question.clone(), status, accepted, drifted }
    });
    let seen: Vec<(String, String, bool)> = outcomes
        .iter()
        .map(|o| (o.case.clone(), o.status.word().to_owned(), !o.is_failure()))
        .collect();
    if let Err(e) = ledger::save(&record, &seen) {
        eprintln!("{}: could not write {}: {e}", corpus.name, record.display());
    }
    Ok(Report { corpus: corpus.name.clone(), calls, outcomes })
}

/// A line to print when the reference is not the compiler the build was made with.
///
/// Not a failure, since a machine may have the same GCC under another name, but a difference
/// between the two compilers means little when the reference is a different one again.
#[must_use]
pub fn other_reference(build: &Path, cc: &Path) -> Option<String> {
    let text = fs::read_to_string(build.join(SUMMARY)).ok()?;
    let built = summary(&text, SUMMARY).ok()?.compiler;
    let output = Command::new(cc).arg("--version").output().ok()?;
    let ours = String::from_utf8_lossy(&output.stdout).lines().next()?.trim().to_owned();
    (ours != built)
        .then(|| format!("the build was made with `{built}` and the reference here is `{ours}`"))
}

/// The probe report, as the markdown that lands in `results/`.
#[must_use]
pub fn markdown(report: &Report, settings: &Settings, register: &Register) -> String {
    let mut out = String::new();
    let _ = writeln!(out, "# {}\n", report.corpus);
    let _ = writeln!(out, "{}\n", report.summary());
    let _ = writeln!(
        out,
        "Reference: `{}`. Under test: `{}`. A question is the probe's arguments in the form `rk probes` prints them.\n",
        settings.cc.display(),
        settings.rucc.display()
    );
    let failures: Vec<&Outcome> = report.outcomes.iter().filter(|o| o.is_failure()).collect();
    if failures.is_empty() {
        let _ = writeln!(out, "Nothing failing.\n");
    } else {
        let _ = writeln!(out, "## Failing\n");
        let _ =
            writeln!(out, "| reference | rucc | question | what rucc said |\n|---|---|---|---|");
        for o in failures {
            let (theirs, ours, said) = match &o.status {
                Status::No(why) => ("yes", "no", why.as_str()),
                _ => ("no", "yes", ""),
            };
            let _ = writeln!(
                out,
                "| {theirs} | {ours} | `{}` | {} |",
                o.question.replace('|', "\\|"),
                said.replace('|', "\\|")
            );
        }
        let _ = writeln!(out);
    }
    let accepted: Vec<&Outcome> = report.outcomes.iter().filter(|o| o.accepted.is_some()).collect();
    if !accepted.is_empty() {
        let _ = writeln!(out, "## Accepted\n");
        for o in accepted {
            let id = o.accepted.as_deref().unwrap_or_default();
            let issue =
                register.entries.iter().find(|d| d.id == id).map_or("", |d| d.issue.as_str());
            let _ = writeln!(out, "- `{}` ({}, {id}, {issue})", o.question, o.status.word());
        }
        let _ = writeln!(out);
    }
    let drifted: Vec<&Outcome> = report.outcomes.iter().filter(|o| o.drifted).collect();
    if !drifted.is_empty() {
        let _ = writeln!(out, "## The reference disagrees with the build\n");
        let _ = writeln!(
            out,
            "The reference answered these differently from the compiler the build was made with, which usually means `--cc` is not that compiler.\n"
        );
        for o in drifted {
            let _ = writeln!(out, "- `{}`", o.question);
        }
        let _ = writeln!(out);
    }
    let quiet: Vec<&Outcome> = report
        .outcomes
        .iter()
        .filter(|o| matches!(o.status, Status::NotAsked | Status::Unsupported(_)))
        .collect();
    if !quiet.is_empty() {
        let _ = writeln!(out, "## Not compared\n");
        let _ = writeln!(
            out,
            "A probe that reads its program from standard input is not asked, because the log does not keep what kbuild piped in. A probe the reference could not be run on has nothing to compare against.\n"
        );
        for o in quiet {
            let _ = writeln!(out, "- `{}` ({})", o.question, o.status.word());
        }
        let _ = writeln!(out);
    }
    out
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::corpus::Divergence;

    fn words(line: &str) -> Vec<String> {
        line.split_whitespace().map(str::to_owned).collect()
    }

    /// Three lines the way rk-cc writes them: a probe, a unit, and a line cut short.
    const LOG_TEXT: &str = r#"{"started":1,"argv":["/o/rk-bin/rk-cc","-Werror","-mno-red-zone","-c","-x","c","/dev/null","-o",".tmp_12/tmp"],"compiler":"/usr/bin/gcc","cwd":"/o","wall-seconds":0.1,"exit":0,"probe":true}
{"started":1,"argv":["/o/rk-bin/rk-cc","-Wp,-MMD,kernel/.fork.o.d","-nostdinc","-I/src/include","-DKBUILD_BASENAME=\"fork\"","-c","-o","kernel/fork.o","/src/kernel/fork.c"],"compiler":"/usr/bin/gcc","cwd":"/o","inputs":[{"path":"/src/kernel/fork.c","sha256":"aa"}],"outputs":[{"path":"kernel/fork.o","sha256":"bb"}],"wall-seconds":0.3,"exit":0}
{"started":1,"argv":["#;

    #[test]
    fn the_log_is_read_a_line_at_a_time_and_a_cut_line_is_counted() {
        let (records, skipped) = records(LOG_TEXT);
        assert_eq!(skipped, 1);
        assert_eq!(records.len(), 2);
        assert!(records[0].probe && records[0].succeeded() && !records[0].is_unit());
        let unit = &records[1];
        assert!(unit.is_unit());
        assert_eq!(unit.source(), Some("/src/kernel/fork.c"));
        assert_eq!(unit.output(), Some("kernel/fork.o"));
        assert_eq!(unit.cwd, PathBuf::from("/o"));
        assert_eq!(unit.argv[4], "-DKBUILD_BASENAME=\"fork\"");
    }

    #[test]
    fn a_unit_keeps_its_flags_and_loses_its_object_and_dependency_file() {
        let (records, _) = records(LOG_TEXT);
        let unit = &records[1];
        assert_eq!(
            meson::compile_flags(&unit.argv, unit.source().unwrap()),
            ["-nostdinc", "-I/src/include", "-DKBUILD_BASENAME=\"fork\""]
        );
    }

    #[test]
    fn a_call_with_no_c_or_s_source_is_not_a_unit() {
        let link = Record {
            argv: words("rk-cc -c -o a.o a.s"),
            compiler: String::new(),
            cwd: PathBuf::from("/o"),
            inputs: vec!["a.s".to_owned()],
            exit: Some(0),
            probe: false,
        };
        assert!(!link.is_unit());
    }

    const BUILD_JSON: &str = r#"{
  "version": "7.2.8",
  "row": "x86_64",
  "config": "defconfig",
  "era": "E11",
  "compiler": {"path": "/usr/bin/gcc-14", "version": "gcc-14 (Debian 14.2.0-19) 14.2.0", "sha256": "cc", "rucc": false},
  "persona": [],
  "configured": true,
  "built": true
}"#;

    fn persona() -> Persona {
        Persona { era: "E11".to_owned(), gnuc: "14.2.0".to_owned() }
    }

    #[test]
    fn the_summary_names_the_version_the_era_and_the_compiler() {
        let s = summary(BUILD_JSON, "build.json").unwrap();
        assert_eq!(s.version, "7.2.8");
        assert_eq!(s.era, "E11");
        assert_eq!(s.config, "defconfig");
        assert!(s.is_gcc());
        let rucc = BUILD_JSON.replace("\"rucc\": false", "\"rucc\": true");
        assert!(!summary(&rucc, "build.json").unwrap().is_gcc());
        let clang = BUILD_JSON.replace("gcc-14 (Debian 14.2.0-19) 14.2.0", "clang version 20");
        assert!(!summary(&clang, "build.json").unwrap().is_gcc());
        assert!(summary("{\"version\": \"7.2.8\"}", "build.json").is_err());
    }

    fn build_dir(name: &str, json: &str) -> PathBuf {
        let dir =
            std::env::temp_dir().join(format!("rucc-compat-kernel-{name}-{}", std::process::id()));
        let _ = fs::remove_dir_all(&dir);
        fs::create_dir_all(&dir).unwrap();
        fs::write(dir.join(SUMMARY), json).unwrap();
        fs::write(dir.join(LOG), LOG_TEXT).unwrap();
        dir
    }

    #[test]
    fn a_build_of_another_version_era_or_compiler_is_refused() {
        let good = build_dir("good", BUILD_JSON);
        assert_eq!(read(&good, "7.2.8", &persona()).unwrap().len(), 2);
        let e = read(&good, "6.18.54", &persona()).unwrap_err();
        assert!(e.message.contains("7.2.8") && e.message.contains("6.18.54"), "{}", e.message);
        let other = Persona { era: "E10".to_owned(), gnuc: "12.2.0".to_owned() };
        assert!(read(&good, "7.2.8", &other).unwrap_err().message.contains("E10"));
        let rucc = build_dir("rucc", &BUILD_JSON.replace("\"rucc\": false", "\"rucc\": true"));
        assert!(read(&rucc, "7.2.8", &persona()).unwrap_err().message.contains("GCC"));
        let _ = fs::remove_dir_all(good);
        let _ = fs::remove_dir_all(rucc);
    }

    #[test]
    fn the_sample_is_the_same_every_time_and_takes_every_exporter() {
        let names: Vec<String> = (0..50).map(|n| format!("drivers/x/f{n}.c")).collect();
        let first = sample(&names, Some(10), |_| false);
        assert_eq!(first.iter().filter(|t| **t).count(), 10);
        assert_eq!(first, sample(&names, Some(10), |_| false));
        // The hash decides, not the order, so reversing the list picks the same names.
        let mut reversed = names.clone();
        reversed.reverse();
        let again = sample(&reversed, Some(10), |_| false);
        let picked = |names: &[String], taken: &[bool]| {
            let mut out: Vec<String> =
                names.iter().zip(taken).filter(|(_, t)| **t).map(|(n, _)| n.clone()).collect();
            out.sort();
            out
        };
        assert_eq!(picked(&names, &first), picked(&reversed, &again));
        let with_exports = sample(&names, Some(10), |at| at % 7 == 0);
        for at in (0..50).filter(|at| at % 7 == 0) {
            assert!(with_exports[at], "exporter {at} was left out");
        }
        assert!(sample(&names, None, |_| false).iter().all(|t| *t));
    }

    // Unix only. The names come from the `source` link rk leaves in the build directory, which
    // the test makes with a Unix symlink, and the log it writes holds the paths as JSON strings,
    // where a Windows path's backslashes are escapes. rk builds Linux on Linux, so nothing on
    // Windows reads a kernel build.
    #[cfg(unix)]
    #[test]
    fn units_are_sampled_and_named_from_the_tree() {
        let root =
            std::env::temp_dir().join(format!("rucc-compat-kernel-units-{}", std::process::id()));
        let _ = fs::remove_dir_all(&root);
        let (src, out) = (root.join("linux"), root.join("out"));
        fs::create_dir_all(src.join("lib")).unwrap();
        fs::create_dir_all(&out).unwrap();
        let mut log = String::new();
        for n in 0..20 {
            let text = if n == 3 { "int f;\nEXPORT_SYMBOL(f);\n" } else { "int f;\n" };
            fs::write(src.join(format!("lib/f{n}.c")), text).unwrap();
            let _ = writeln!(
                log,
                r#"{{"argv":["{o}/rk-bin/rk-cc","-Wp,-MMD,lib/.f{n}.o.d","-DX","-c","-o","lib/f{n}.o","{s}/lib/f{n}.c"],"compiler":"gcc","cwd":"{o}","inputs":[{{"path":"{s}/lib/f{n}.c","sha256":""}}],"exit":0}}"#,
                o = out.display(),
                s = src.display()
            );
        }
        fs::write(out.join(LOG), log).unwrap();
        fs::write(out.join(SUMMARY), BUILD_JSON).unwrap();
        std::os::unix::fs::symlink(&src, out.join("source")).unwrap();
        let manifest = "name = \"kernel-pp\"\nsummary = \"s\"\nsource = \"build\"\nbuilder = \"rk\"\nvariable = \"RUCC_COMPAT_NOT_SET\"\nversion = \"7.2.8\"\nera = \"E11\"\ngnuc = \"14.2.0\"\n\n[[unit]]\nname = \"units\"\nkind = \"kernel-units\"\nsample = 4\n";
        fs::create_dir_all(root.join("repo/corpus/kernel-pp")).unwrap();
        fs::write(root.join("repo/corpus/kernel-pp/corpus.toml"), manifest).unwrap();
        let corpus = crate::corpus::load(&root.join("repo"), "kernel-pp").unwrap();
        assert_eq!(corpus.persona(), Some(vec!["-fgnuc-version=14.2.0".to_owned()]));
        let unit = &corpus.units[0];
        assert_eq!(unit.sample, Some(4));
        let mut found = Found::default();
        unit_cases(&out, &corpus, unit, &mut found).unwrap();
        let names: Vec<&str> = found.cases.iter().map(|c| c.name.as_str()).collect();
        assert!(names.len() == 4 || names.len() == 5, "{names:?}");
        assert!(names.contains(&"units/lib/f3.c"), "the exporter was not taken: {names:?}");
        assert!(names.iter().all(|n| n.starts_with("units/lib/")), "{names:?}");
        let case = &found.cases[0];
        assert_eq!(case.dir, out);
        assert_eq!(case.flags, ["-DX"]);
        let _ = fs::remove_dir_all(root);
    }

    #[test]
    fn a_question_is_the_one_rk_would_write() {
        let argv = words(
            "/p/rk-bin/rk-cc -fgnuc-version=14.2.0 -Werror -mno-red-zone -c -x c /dev/null -o .tmp_40/tmp",
        );
        assert_eq!(question(&argv), "-Werror -mno-red-zone -c -x c /dev/null");
        let joined = words("/o/rk-bin/rk-cc -S -x c /dev/null -o.tmp_1/tmp.s -Wa,--x=.tmp_1/y");
        assert_eq!(question(&joined), "-S -x c /dev/null TMP");
    }

    #[test]
    fn a_replayed_probe_writes_where_it_is_told_and_nowhere_else() {
        let out = Path::new("/scratch/p.out");
        let argv = words("/o/rk-bin/rk-cc -Werror -c -x c /dev/null -o .tmp_12/tmp");
        assert_eq!(replay(&argv, out), words("-Werror -c -x c /dev/null -o /scratch/p.out"));
        let joined = words("/o/rk-bin/rk-cc -S -x c /dev/null -o.tmp_12/tmp");
        assert_eq!(replay(&joined, out), words("-S -x c /dev/null -o /scratch/p.out"));
        assert_eq!(replay(&words("rk-cc --version"), out), ["--version"]);
    }

    #[test]
    fn a_probe_reading_standard_input_is_told_apart_from_one_writing_standard_output() {
        assert!(reads_stdin(&words("rk-cc -c -x assembler-with-cpp -o .tmp_1/tmp -")));
        assert!(!reads_stdin(&words("rk-cc -S -x c /dev/null -o -")));
    }

    #[test]
    fn probes_are_asked_once_per_question() {
        let probe = |tmp: &str, exit: i32| Record {
            argv: words(&format!(
                "/o/rk-bin/rk-cc -Werror -mno-red-zone -c -x c /dev/null -o {tmp}"
            )),
            compiler: String::new(),
            cwd: PathBuf::from("/o"),
            inputs: Vec::new(),
            exit: Some(exit),
            probe: true,
        };
        let mut unit = probe("x.o", 0);
        unit.probe = false;
        let found = probes(&[probe(".tmp_1/tmp", 0), unit, probe(".tmp_2/tmp", 1)]);
        assert_eq!(found.len(), 1);
        assert_eq!(found[0].asked, 2);
        assert!(found[0].recorded);
        assert_eq!(found[0].question, "-Werror -mno-red-zone -c -x c /dev/null");
    }

    #[test]
    fn a_disagreement_is_a_failure_until_the_register_accepts_it() {
        let outcome = |status: Status, accepted: Option<&str>| Outcome {
            case: "probes/-x".to_owned(),
            question: "-x".to_owned(),
            status,
            accepted: accepted.map(str::to_owned),
            drifted: false,
        };
        assert!(outcome(Status::No("no".to_owned()), None).is_failure());
        assert!(outcome(Status::Yes, None).is_failure());
        assert!(!outcome(Status::Yes, Some("known")).is_failure());
        assert!(!outcome(Status::NotAsked, None).is_failure());
        assert!(!outcome(Status::Unsupported(String::new()), None).is_failure());
        let entry = Divergence {
            id: "cf".to_owned(),
            what: String::new(),
            why: String::new(),
            issue: "#1".to_owned(),
            rule: rule::ANSWER.to_owned(),
            corpus: Some("kernel-probes".to_owned()),
            unit: None,
            matches: Some("-fcf-protection".to_owned()),
        };
        let register = Register { entries: vec![entry] };
        let q =
            |text| Question { rule: rule::ANSWER, corpus: "kernel-probes", unit: "probes", text };
        assert!(register.accepts(q("-Werror -fcf-protection=branch -c")).is_some());
        assert!(register.accepts(q("-Werror -mno-red-zone -c")).is_none());
    }
}
