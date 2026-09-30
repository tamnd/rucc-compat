//! The assembler differential, which is what the `kernel-asm` corpus is for.
//!
//! A kernel cannot test an assembler by booting, because too many things break at once and the
//! symptom is a hang. So the assembler is tested on its own, on the text the kernel really gives
//! it. Every `.S` unit of a build rk made with GCC is preprocessed by the reference with the flags
//! kbuild used, and every C unit is compiled to assembly by the reference with `-S`, which is the
//! kernel's inline asm exactly as GCC expanded it with every directive GCC writes around it. Each
//! text is then assembled twice, by the reference assembler and by rucc, and the two objects are
//! compared with [`crate::elf::compare`].
//!
//! The texts are never kept. They are big and they are the kernel's, so what this keeps is a
//! manifest of their hashes, which says whether two runs were given the same input without
//! anybody having to store it.

use std::fmt::Write as _;
use std::fs;
use std::path::{Path, PathBuf};
use std::time::Duration;

use crate::corpus::{Corpus, Question, Register, UnitKind};
use crate::differ::{self, Case, Found};
use crate::elf;
use crate::kernel;
use crate::ledger;
use crate::sandbox::{self, Limits};
use crate::sha256;
use crate::toml::Error;
use crate::work;

/// The register rule for an object difference. `matches` looks in the case name and the first
/// difference, as in `units/arch/x86/entry/entry_64.S section bytes: .text: ...`.
pub const RULE: &str = "object";

/// How to run.
#[derive(Debug, Clone)]
pub struct Settings {
    /// The assembler under test, driven as `rucc -c -x assembler`.
    pub rucc: PathBuf,
    /// The reference compiler, which makes the texts.
    pub cc: PathBuf,
    /// The reference assembler and any words it needs before the file, as in `as` or
    /// `llvm-mc -filetype=obj -triple x86_64-linux-gnu`.
    pub assembler: Vec<String>,
    /// The target rucc is told to assemble for, which is needed anywhere but on x86-64 Linux.
    pub target: Option<String>,
    /// Stop after this many cases, for a quick look.
    pub limit: Option<usize>,
    /// Run only the unit of this name.
    pub unit: Option<String>,
    /// Run only cases whose name contains one of these.
    pub only: Vec<String>,
    /// Run only cases the last run here did not call green.
    pub failed: bool,
    /// How many cases to have in the air at once.
    pub jobs: Option<usize>,
}

impl Default for Settings {
    fn default() -> Settings {
        Settings {
            rucc: PathBuf::from("rucc"),
            cc: PathBuf::from("cc"),
            assembler: vec!["as".to_owned()],
            target: None,
            limit: None,
            unit: None,
            only: Vec::new(),
            failed: false,
            jobs: None,
        }
    }
}

/// What came of one case.
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum Status {
    /// The two objects are the same.
    Same,
    /// They differ, every way they do, the first one first.
    Differs(Vec<elf::Difference>),
    /// rucc would not assemble the text, with the first line it said.
    Refused(String),
    /// The reference could not make the text or assemble it, so there is nothing to compare.
    NotCompared(String),
}

impl Status {
    /// A word for the table.
    #[must_use]
    pub fn word(&self) -> &'static str {
        match self {
            Status::Same => "same",
            Status::Differs(_) => "differs",
            Status::Refused(_) => "rucc error",
            Status::NotCompared(_) => "not compared",
        }
    }

    /// What the failure is grouped under in the report: the kind of the first difference, or
    /// what rucc said with the file and line taken off.
    #[must_use]
    pub fn bucket(&self) -> Option<String> {
        match self {
            Status::Differs(found) => found.first().map(|d| d.bucket.clone()),
            Status::Refused(said) => Some(format!("rucc: {}", message(said))),
            _ => None,
        }
    }
}

/// An error line without the place it was found, so that the same complaint about two files is
/// one bucket.
#[must_use]
pub fn message(line: &str) -> String {
    match line.find("error: ") {
        Some(at) => line[at + "error: ".len()..].trim().to_owned(),
        None => line.trim().to_owned(),
    }
}

/// One case and what came of it.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Outcome {
    /// The unit and the source, as in `units/arch/x86/entry/entry_64.S`.
    pub case: String,
    /// What happened.
    pub status: Status,
    /// The sha256 of the text both assemblers were given, when the reference made one.
    pub input: Option<String>,
    /// The divergence that covers it, when the register has one.
    pub accepted: Option<String>,
}

impl Outcome {
    /// Whether this outcome fails the run.
    #[must_use]
    pub fn is_failure(&self) -> bool {
        self.accepted.is_none() && matches!(self.status, Status::Differs(_) | Status::Refused(_))
    }
}

/// Everything one run came to.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Report {
    /// Which corpus.
    pub corpus: String,
    /// Every case, in name order.
    pub outcomes: Vec<Outcome>,
}

impl Report {
    /// How many cases ended each way.
    #[must_use]
    pub fn count(&self, word: &str) -> usize {
        self.outcomes.iter().filter(|o| o.status.word() == word).count()
    }

    /// How many cases fail the run.
    #[must_use]
    pub fn failures(&self) -> usize {
        self.outcomes.iter().filter(|o| o.is_failure()).count()
    }

    /// The share of compared cases that came out the same or accepted, as a percentage.
    #[must_use]
    pub fn rate(&self) -> f64 {
        let compared = self.outcomes.len() - self.count("not compared");
        if compared == 0 {
            return 100.0;
        }
        let good = compared - self.failures();
        #[allow(clippy::cast_precision_loss)]
        let rate = good as f64 * 100.0 / compared as f64;
        rate
    }

    /// One line, for the terminal.
    #[must_use]
    pub fn summary(&self) -> String {
        let accepted = self.outcomes.iter().filter(|o| o.accepted.is_some()).count();
        format!(
            "{}: {} cases, {} same, {} differ, {} rucc errors, {} not compared, {} accepted, {} failing, {:.1}% passing",
            self.corpus,
            self.outcomes.len(),
            self.count("same"),
            self.count("differs"),
            self.count("rucc error"),
            self.count("not compared"),
            accepted,
            self.failures(),
            self.rate()
        )
    }

    /// The failing cases grouped by bucket, the biggest bucket first.
    #[must_use]
    pub fn buckets(&self) -> Vec<(String, Vec<&Outcome>)> {
        let mut groups: Vec<(String, Vec<&Outcome>)> = Vec::new();
        for o in self.outcomes.iter().filter(|o| o.is_failure()) {
            let bucket = o.status.bucket().unwrap_or_default();
            match groups.iter_mut().find(|(b, _)| *b == bucket) {
                Some((_, list)) => list.push(o),
                None => groups.push((bucket, vec![o])),
            }
        }
        groups.sort_by(|a, b| b.1.len().cmp(&a.1.len()).then_with(|| a.0.cmp(&b.0)));
        groups
    }

    /// The manifest: one line per case the reference made a text for, the hash and the name.
    #[must_use]
    pub fn manifest(&self) -> String {
        let mut out = String::new();
        for o in &self.outcomes {
            if let Some(hash) = &o.input {
                let _ = writeln!(out, "{hash}  {}", o.case);
            }
        }
        out
    }
}

/// How an old manifest and a new one differ: texts that changed, cases that are new, and cases
/// that went away.
#[must_use]
pub fn drift(old: &str, new: &str) -> (usize, usize, usize) {
    let read = |text: &str| -> std::collections::BTreeMap<String, String> {
        text.lines()
            .filter_map(|l| l.split_once("  "))
            .map(|(h, c)| (c.to_owned(), h.to_owned()))
            .collect()
    };
    let (old, new) = (read(old), read(new));
    let changed = new.iter().filter(|(c, h)| old.get(*c).is_some_and(|o| o != *h)).count();
    let added = new.keys().filter(|c| !old.contains_key(*c)).count();
    let gone = old.keys().filter(|c| !new.contains_key(*c)).count();
    (changed, added, gone)
}

/// How long one step gets. The biggest `-S` of a kernel unit takes a few seconds, so this is for
/// a tool that hangs.
const STEP_TIME: Duration = Duration::from_secs(120);

/// Whether a case is a `.S` unit, which is preprocessed, rather than a C unit, which is compiled
/// to assembly.
fn is_assembly(case: &Case) -> bool {
    case.file.extension().is_some_and(|e| e == "S")
}

/// The words of every `-Wa,` flag, which are what kbuild passes the assembler.
#[must_use]
pub fn assembler_words(flags: &[String]) -> Vec<String> {
    flags
        .iter()
        .filter_map(|f| f.strip_prefix("-Wa,"))
        .flat_map(|w| w.split(','))
        .filter(|w| !w.is_empty())
        .map(str::to_owned)
        .collect()
}

fn first_line(ran: &sandbox::Ran) -> String {
    let text = String::from_utf8_lossy(&ran.err);
    let line = text.lines().map(str::trim).find(|l| !l.is_empty());
    match line {
        Some(line) => line.to_owned(),
        None => ran.end.said(),
    }
}

/// Takes one case through both assemblers.
fn one(case: &Case, at: usize, settings: &Settings, scratch: &Path) -> (Status, Option<String>) {
    let text = scratch.join(format!("{at}.s"));
    let theirs = scratch.join(format!("{at}-reference.o"));
    let ours = scratch.join(format!("{at}-rucc.o"));
    let limits = Limits { timeout: STEP_TIME, memory: None };
    let cc = differ::program(&settings.cc);
    let mut args = case.flags.clone();
    args.push(if is_assembly(case) { "-E" } else { "-S" }.to_owned());
    args.extend(["-o".to_owned(), text.to_string_lossy().into_owned()]);
    args.push(case.file.to_string_lossy().into_owned());
    match sandbox::run(&cc, &args, &case.dir, &limits) {
        Ok(ran) if ran.end.is_clean() => {}
        Ok(ran) => return (Status::NotCompared(format!("cc: {}", first_line(&ran))), None),
        Err(e) => return (Status::NotCompared(e), None),
    }
    let input = fs::read(&text).ok().map(|bytes| sha256::hex(&bytes));
    let words = assembler_words(&case.flags);
    let file = text.to_string_lossy().into_owned();

    let program = differ::program(Path::new(&settings.assembler[0]));
    let mut args: Vec<String> = settings.assembler[1..].to_vec();
    args.extend(words.iter().cloned());
    args.extend(["-o".to_owned(), theirs.to_string_lossy().into_owned(), file.clone()]);
    let status = match sandbox::run(&program, &args, &case.dir, &limits) {
        Ok(ran) if ran.end.is_clean() => None,
        Ok(ran) => Some(Status::NotCompared(format!("as: {}", first_line(&ran)))),
        Err(e) => Some(Status::NotCompared(e)),
    };
    let status = status.or_else(|| {
        let rucc = differ::program(&settings.rucc);
        let mut args: Vec<String> = Vec::new();
        if let Some(target) = &settings.target {
            args.push(format!("--target={target}"));
        }
        args.extend(["-c", "-x", "assembler"].map(str::to_owned));
        args.extend(case.flags.iter().filter(|f| f.starts_with("-Wa,")).cloned());
        args.extend(["-o".to_owned(), ours.to_string_lossy().into_owned(), file.clone()]);
        match sandbox::run(&rucc, &args, &case.dir, &limits) {
            Ok(ran) if ran.end.is_clean() => None,
            Ok(ran) => Some(Status::Refused(first_line(&ran))),
            Err(e) => Some(Status::NotCompared(e)),
        }
    });
    let status = status.unwrap_or_else(|| {
        let read =
            |path: &Path| fs::read(path).map_err(|e| e.to_string()).and_then(|b| elf::read(&b));
        match (read(&theirs), read(&ours)) {
            (Err(e), _) => Status::NotCompared(format!("the reference object: {e}")),
            (_, Err(e)) => Status::Refused(format!("rucc's object: {e}")),
            (Ok(a), Ok(b)) => match elf::compare(&a, &b) {
                found if found.is_empty() => Status::Same,
                found => Status::Differs(found),
            },
        }
    });
    // A text that went wrong is kept for whoever looks at it next, and the rest is thrown away,
    // since a whole kernel's worth of them is several gigabytes.
    if matches!(status, Status::Same | Status::NotCompared(_)) {
        let _ = fs::remove_file(&text);
    }
    let _ = fs::remove_file(&theirs);
    let _ = fs::remove_file(&ours);
    (status, input)
}

/// The cases of a corpus's `kernel-asm` units.
fn cases(repo: &Path, corpus: &Corpus, settings: &Settings) -> Result<Found, Error> {
    let mut found = Found::default();
    let units: Vec<_> = corpus.units.iter().filter(|u| u.kind == UnitKind::KernelAsm).collect();
    if units.is_empty() {
        return Err(Error { message: format!("{}: no `kernel-asm` unit", corpus.name) });
    }
    if let Some(name) = &settings.unit {
        if !units.iter().any(|u| u.name == *name) {
            return Err(Error {
                message: format!("{}: there is no unit called `{name}`", corpus.name),
            });
        }
    }
    let tree = corpus.tree(repo);
    for unit in units.into_iter().filter(|u| settings.unit.as_ref().is_none_or(|n| *n == u.name)) {
        kernel::unit_cases(&tree, corpus, unit, &mut found)?;
    }
    found.cases.sort_by(|a, b| a.name.cmp(&b.name));
    Ok(found)
}

/// Runs the assembler differential over a corpus.
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
    if settings.assembler.is_empty() {
        return Err(Error { message: "--as names no assembler".to_owned() });
    }
    let found = cases(repo, corpus, settings)?;
    let record = ledger::path(repo, &corpus.name, "asm", None);
    let keep = ledger::Keep::new(&settings.only, settings.failed.then_some(record.as_path()))
        .map_err(|message| Error { message: format!("{}: {message}", corpus.name) })?;
    let all: Vec<&Case> = found.cases.iter().filter(|c| keep.wants(&c.name)).collect();
    if all.is_empty() && !keep.is_all() {
        return Err(Error { message: format!("{}: {}", corpus.name, keep.emptiness()) });
    }
    let all = match settings.limit {
        Some(limit) => &all[..limit.min(all.len())],
        None => &all[..],
    };
    fs::create_dir_all(scratch)
        .map_err(|e| Error { message: format!("{}: {e}", scratch.display()) })?;
    let numbered: Vec<(usize, &Case)> = all.iter().copied().enumerate().collect();
    let outcomes = work::spread(&numbered, work::jobs(settings.jobs), |(at, case)| {
        let (status, input) = one(case, *at, settings, scratch);
        let accepted = match &status {
            Status::Differs(found) => Some(format!("{} {}", case.name, found[0])),
            Status::Refused(said) => Some(format!("{} {said}", case.name)),
            _ => None,
        }
        .and_then(|text| {
            register
                .accepts(Question {
                    rule: RULE,
                    corpus: &corpus.name,
                    unit: &case.unit,
                    text: &text,
                })
                .map(|d| d.id.clone())
        });
        Outcome { case: case.name.clone(), status, input, accepted }
    });
    let seen: Vec<(String, String, bool)> = outcomes
        .iter()
        .map(|o| (o.case.clone(), o.status.word().to_owned(), !o.is_failure()))
        .collect();
    if let Err(e) = ledger::save(&record, &seen) {
        eprintln!("{}: could not write {}: {e}", corpus.name, record.display());
    }
    Ok(Report { corpus: corpus.name.clone(), outcomes })
}

/// The report, as the markdown that lands in `results/`.
#[must_use]
pub fn markdown(report: &Report, settings: &Settings, register: &Register) -> String {
    let mut out = String::new();
    let _ = writeln!(out, "# {}\n", report.corpus);
    let _ = writeln!(out, "{}\n", report.summary());
    let _ = writeln!(
        out,
        "Texts made by `{}`. Reference assembler: `{}`. Under test: `{}`. A `.S` unit is compared on its `-E` output and a C unit on its `-S` output.\n",
        settings.cc.display(),
        settings.assembler.join(" "),
        settings.rucc.display()
    );
    let buckets = report.buckets();
    if buckets.is_empty() {
        let _ = writeln!(out, "Nothing failing.\n");
    } else {
        let _ = writeln!(out, "## Failing, by what went wrong first\n");
        let _ = writeln!(out, "| cases | first difference or error |\n|---|---|");
        for (bucket, list) in &buckets {
            let _ = writeln!(out, "| {} | {} |", list.len(), bucket.replace('|', "\\|"));
        }
        let _ = writeln!(out);
        for (bucket, list) in &buckets {
            let _ = writeln!(out, "### {bucket}\n");
            for o in list.iter().take(20) {
                let detail = match &o.status {
                    Status::Differs(found) => found[0].detail.clone(),
                    Status::Refused(said) => said.clone(),
                    _ => String::new(),
                };
                let _ = writeln!(out, "- `{}`: {}", o.case, detail.replace('|', "\\|"));
            }
            if list.len() > 20 {
                let _ = writeln!(out, "- and {} more", list.len() - 20);
            }
            let _ = writeln!(out);
        }
    }
    let accepted: Vec<&Outcome> = report.outcomes.iter().filter(|o| o.accepted.is_some()).collect();
    if !accepted.is_empty() {
        let _ = writeln!(out, "## Accepted\n");
        for o in accepted {
            let id = o.accepted.as_deref().unwrap_or_default();
            let issue =
                register.entries.iter().find(|d| d.id == id).map_or("", |d| d.issue.as_str());
            let _ = writeln!(out, "- `{}` ({id}, {issue})", o.case);
        }
        let _ = writeln!(out);
    }
    let quiet: Vec<&Outcome> =
        report.outcomes.iter().filter(|o| matches!(o.status, Status::NotCompared(_))).collect();
    if !quiet.is_empty() {
        let _ = writeln!(out, "## Not compared\n");
        let _ = writeln!(
            out,
            "The reference could not make the text or assemble it, so there was nothing to hold rucc to.\n"
        );
        for o in quiet {
            if let Status::NotCompared(why) = &o.status {
                let _ = writeln!(out, "- `{}`: {}", o.case, why.replace('|', "\\|"));
            }
        }
        let _ = writeln!(out);
    }
    out
}

#[cfg(test)]
mod tests {
    use super::*;

    fn outcome(case: &str, status: Status) -> Outcome {
        Outcome { case: case.to_owned(), status, input: Some(format!("h{case}")), accepted: None }
    }

    fn differs(bucket: &str) -> Status {
        Status::Differs(vec![elf::Difference { bucket: bucket.to_owned(), detail: "d".to_owned() }])
    }

    #[test]
    fn an_error_is_bucketed_without_its_place() {
        assert_eq!(
            message("/tmp/7.s:12:5: error: unknown directive `.foo`"),
            "unknown directive `.foo`"
        );
        assert_eq!(message("it said nothing"), "it said nothing");
        let refused = Status::Refused("a.s:1:1: error: bad operand".to_owned());
        assert_eq!(refused.bucket().as_deref(), Some("rucc: bad operand"));
    }

    #[test]
    fn failures_are_grouped_biggest_first_and_not_compared_is_not_a_failure() {
        let report = Report {
            corpus: "kernel-asm".to_owned(),
            outcomes: vec![
                outcome("u/a.c", Status::Same),
                outcome("u/b.c", differs("section bytes: .text")),
                outcome("u/c.S", Status::Refused("x.s:1:1: error: nope".to_owned())),
                outcome("u/d.c", differs("section bytes: .text")),
                outcome("u/e.c", Status::NotCompared("cc: no".to_owned())),
            ],
        };
        assert_eq!(report.failures(), 3);
        let buckets = report.buckets();
        assert_eq!(buckets[0].0, "section bytes: .text");
        assert_eq!(buckets[0].1.len(), 2);
        assert_eq!(buckets[1].0, "rucc: nope");
        assert!((report.rate() - 25.0).abs() < 1e-9, "{}", report.rate());
        assert!(report.summary().contains("5 cases, 1 same, 2 differ, 1 rucc errors"));
    }

    #[test]
    fn an_accepted_difference_does_not_fail() {
        let mut o = outcome("u/b.c", differs("relocations: .text"));
        assert!(o.is_failure());
        o.accepted = Some("known".to_owned());
        assert!(!o.is_failure());
    }

    #[test]
    fn the_manifest_says_which_texts_changed() {
        let old = "aa  u/a.c\nbb  u/b.c\ncc  u/c.S\n";
        let new = "aa  u/a.c\nbx  u/b.c\ndd  u/d.S\n";
        assert_eq!(drift(old, new), (1, 1, 1));
        let report = Report {
            corpus: "k".to_owned(),
            outcomes: vec![
                outcome("u/a.c", Status::Same),
                Outcome { input: None, ..outcome("u/z.c", Status::NotCompared(String::new())) },
            ],
        };
        assert_eq!(report.manifest(), "hu/a.c  u/a.c\n");
    }

    #[test]
    fn the_assembler_gets_what_kbuild_passed_it() {
        let flags: Vec<String> =
            ["-DX", "-Wa,--noexecstack", "-Wa,-mrelax-relocations=no,--64", "-O2"]
                .map(str::to_owned)
                .to_vec();
        assert_eq!(assembler_words(&flags), ["--noexecstack", "-mrelax-relocations=no", "--64"]);
    }
}
