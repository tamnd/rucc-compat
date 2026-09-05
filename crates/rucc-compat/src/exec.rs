//! Running the generated code, which is the question none of the other checks answer.
//!
//! Design: `spec/20-execution-testing.md` in the compiler repository.
//!
//! [`crate::differ`] asks whether rucc preprocesses a file the way the reference does, and
//! [`crate::pipeline`] asks whether rucc gets it through its own front end and lowering. Both
//! are questions about compiling. Every one of them can come out green while the executable
//! prints the wrong answer, because between the last thing the verifier sees and the first
//! thing the processor sees there are four passes and an encoder, and the only test that covers
//! all of them at once is running the program.
//!
//! So each case is built, by every path in [`Route`] that this machine has, and run, and an
//! oracle says whether the run was right. The result is one of eight words and not two: a
//! summary that collapsed them into passed and failed would hide the difference between a
//! compiler that is wrong and a compiler that is incomplete, and those are not the same news.

use std::ffi::OsString;
use std::fmt::Write as _;
use std::fs;
use std::path::{Path, PathBuf};
use std::process::Command;
use std::time::Duration;

use crate::corpus::{Corpus, Exclusion, Oracle};
use crate::coverage::{self, Marks};
use crate::differ::{self, Case};
use crate::ledger;
use crate::pipeline::{named, said, stem};
use crate::sandbox::{self, End, Limits, Ran};
use crate::toml::Error;
use crate::work;

/// The eight words a case can come out as, in the order the report counts them.
///
/// The first four are the ways a case can be held against the compiler, the next two are the
/// ways it cannot be measured, and the last is what an entry in the manifest turns one of the
/// first four into.
pub const WORDS: &[&str] = &[
    "passed",
    "wrong answer",
    "crashed",
    "timed out",
    "did not build",
    "not compared",
    "skipped",
    "excluded",
];

/// How long a compiler gets before it is treated as hung.
///
/// Generous, and not the case timeout. A compiler taking a minute over a test program is a
/// performance bug worth its own issue, and killing it at ten seconds would report that bug as
/// a build failure of the case, which is the wrong place for anybody to start looking.
pub const BUILD_TIMEOUT: Duration = Duration::from_secs(120);

/// How much address space a run gets, in kibibytes, where one can be set at all.
pub const MEMORY: u64 = 2 * 1024 * 1024;

/// Which way a case was built.
///
/// Not alternatives to choose between. Every path the machine has runs over every case, and a
/// case that passes on one and fails on another is a bug in the one that fails, located by
/// construction. That is how the encoder gets checked against the assembly printer without
/// anybody writing an encoder differential: the two come out of one instruction description, so
/// a disagreement is a disagreement inside that description, and it arrives as a wrong answer
/// rather than as a byte diff nobody reads.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Route {
    /// `rucc -S`, the system assembler, the system linker. The path that depends on the least:
    /// no encoder, no object writer, no relocations, and an intermediate artifact somebody can
    /// read and hand to the reference compiler on its own.
    Assembly,
    /// `rucc -c` and the system linker, which is the encoder and the relocations.
    Object,
    /// `rucc case.c -o case`, which is what a user runs.
    Driver,
}

impl Route {
    /// The word the command line and the report use.
    #[must_use]
    pub fn word(self) -> &'static str {
        match self {
            Route::Assembly => "assembly",
            Route::Object => "object",
            Route::Driver => "driver",
        }
    }

    /// The route of that name.
    #[must_use]
    pub fn named(word: &str) -> Option<Route> {
        Route::all().into_iter().find(|r| r.word() == word)
    }

    /// All three, in the order they were built and the order they are reported.
    #[must_use]
    pub fn all() -> Vec<Route> {
        vec![Route::Assembly, Route::Object, Route::Driver]
    }
}

/// How to run.
#[derive(Debug, Clone)]
pub struct Settings {
    /// The compiler under test.
    pub rucc: PathBuf,
    /// The reference, which is also the assembler and the linker for the first two routes.
    pub cc: PathBuf,
    /// Which build paths to take.
    pub routes: Vec<Route>,
    /// The optimization level to pass both compilers, as the digit or letter after `-O`.
    ///
    /// `None` passes no `-O` at all, which is each compiler's own default and is a different
    /// measurement from `-O0`.
    pub opt: Option<String>,
    /// Stop after this many cases, for a quick look.
    pub limit: Option<usize>,
    /// Run only the unit of this name.
    pub unit: Option<String>,
    /// Run only cases whose name contains one of these, or all of them when empty.
    pub only: Vec<String>,
    /// Run only cases the last run here did not call green.
    pub failed: bool,
    /// What to call the machine in the report, or `None` for the platform it runs on.
    pub machine: Option<String>,
    /// Seconds per run, over what the corpus asks for.
    ///
    /// Here for the one case the manifest cannot know about, which is a slower machine or an
    /// emulator. A corpus that always needs longer should say so in its manifest instead, where
    /// the next person to run it gets the same answer without being told.
    pub timeout: Option<u64>,
    /// How much address space to give a run, in kibibytes.
    pub memory: Option<u64>,
    /// How many cases to have in the air at once, or `None` for a share of the machine.
    ///
    /// Not part of what is measured. A case says the same thing whichever thread built it, and a
    /// report that came out different at two settings of this is a bug in the harness rather
    /// than news about the compiler.
    pub jobs: Option<usize>,
    /// Whether to ask the compiler under test which of its lowering rules each build fired.
    ///
    /// Only the compiler under test is asked, since the flag is one of ours and the reference has
    /// never heard of it.
    pub coverage: bool,
}

impl Default for Settings {
    fn default() -> Settings {
        Settings {
            rucc: PathBuf::from("rucc"),
            cc: PathBuf::from("cc"),
            routes: Route::all(),
            opt: None,
            limit: None,
            unit: None,
            only: Vec::new(),
            failed: false,
            machine: None,
            timeout: None,
            memory: Some(MEMORY),
            jobs: None,
            coverage: false,
        }
    }
}

impl Settings {
    /// Whether this run is looking at every case the corpus has.
    ///
    /// A part of a corpus cannot say anything about an exclusion it never reached, so the
    /// staleness check only runs when this is true.
    #[must_use]
    pub fn is_whole(&self) -> bool {
        self.limit.is_none() && self.unit.is_none() && self.only.is_empty() && !self.failed
    }

    /// The `-O` flag both compilers get, if there is one.
    #[must_use]
    pub fn level(&self) -> Option<String> {
        self.opt.as_ref().map(|level| format!("-O{level}"))
    }
}

/// What came of one case on one route.
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum Status {
    /// It built, it ran, and the oracle agreed with it.
    Passed,
    /// It built and ran and gave an answer that is not the right one, which is the outcome this
    /// whole harness exists to find.
    Wrong {
        /// Where the answer and the right answer parted company.
        why: String,
    },
    /// A signal killed it, or Windows faulted it.
    Crashed {
        /// Which signal, or which fault.
        why: String,
    },
    /// It was still running when its time ran out.
    ///
    /// Its own outcome and not a wrong answer: a program that would have printed the right thing
    /// eventually is a performance bug and a program that printed the wrong thing is a
    /// miscompilation, and a report that mixed them would send somebody to the wrong place.
    TimedOut,
    /// The compiler under test refused it, or the assembler or the linker did.
    DidNotBuild {
        /// What was said, cut to the lines that name the problem.
        why: String,
    },
    /// It ran and there was nothing to hold the answer against.
    ///
    /// Not a pass. A harness that quietly counts an unmeasurable case as a success is a harness
    /// that reports a number nobody should act on.
    NotCompared {
        /// What was missing.
        why: String,
    },
    /// The reference compiler refused it, so it is not a valid case rather than a failure.
    ///
    /// A corpus written in 2005 holds programs no compiler released this decade accepts, and
    /// counting those against us would make the number a fiction.
    Skipped {
        /// What the reference said.
        why: String,
    },
}

impl Status {
    /// The word for this outcome, which is one of [`WORDS`].
    #[must_use]
    pub fn word(&self) -> &'static str {
        match self {
            Status::Passed => "passed",
            Status::Wrong { .. } => "wrong answer",
            Status::Crashed { .. } => "crashed",
            Status::TimedOut => "timed out",
            Status::DidNotBuild { .. } => "did not build",
            Status::NotCompared { .. } => "not compared",
            Status::Skipped { .. } => "skipped",
        }
    }

    /// Whether this is one of the four ways a case is held against the compiler.
    #[must_use]
    pub fn is_against_us(&self) -> bool {
        matches!(
            self,
            Status::Wrong { .. }
                | Status::Crashed { .. }
                | Status::TimedOut
                | Status::DidNotBuild { .. }
        )
    }

    /// What it said, for the table, or nothing when the word says it all.
    #[must_use]
    pub fn why(&self) -> &str {
        match self {
            Status::Passed | Status::TimedOut => "",
            Status::Wrong { why }
            | Status::Crashed { why }
            | Status::DidNotBuild { why }
            | Status::NotCompared { why }
            | Status::Skipped { why } => why,
        }
    }
}

/// One case, on one route, and what came of it.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Outcome {
    /// The case name, which is the unit and the file, the same identity `check` uses.
    pub case: String,
    /// Which way it was built.
    pub route: Route,
    /// What happened.
    pub status: Status,
    /// The manifest entry that covers it, when there is one.
    pub excused: Option<Exclusion>,
}

impl Outcome {
    /// Whether the entry that covers this case admits to what actually happened.
    #[must_use]
    pub fn is_covered(&self) -> bool {
        match &self.excused {
            None => false,
            Some(entry) => entry.outcome.as_deref() == Some(self.status.word()),
        }
    }

    /// The word this counts as, which is `excluded` when an entry admits to it.
    #[must_use]
    pub fn word(&self) -> &'static str {
        match self.is_covered() {
            true => "excluded",
            false => self.status.word(),
        }
    }

    /// Whether this is an exclusion that no longer excludes anything.
    #[must_use]
    pub fn is_stale(&self) -> bool {
        self.excused.is_some() && self.status == Status::Passed
    }

    /// Whether this case fails in a way its entry did not admit to.
    ///
    /// The rule that keeps the list honest in the direction that matters. A case excluded for a
    /// build failure that starts giving a wrong answer instead has not started passing and has
    /// not stayed the same, and the second of those admissions is far worse than the first.
    #[must_use]
    pub fn is_changed(&self) -> bool {
        self.excused.is_some() && self.status.is_against_us() && !self.is_covered()
    }

    /// Whether this outcome fails the run.
    #[must_use]
    pub fn is_failure(&self) -> bool {
        match self.excused.is_some() {
            true => self.is_changed(),
            false => self.status.is_against_us(),
        }
    }
}

/// Everything one corpus produced.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Report {
    /// Which corpus.
    pub corpus: String,
    /// Which oracle decided every case in it.
    pub oracle: Oracle,
    /// Every case on every route, in name order.
    pub outcomes: Vec<Outcome>,
    /// Exclusions naming a case this corpus does not have.
    ///
    /// Empty unless the whole corpus ran, since a filtered run has no opinion about a case it
    /// did not reach.
    pub unmatched: Vec<Exclusion>,
    /// What the compiler under test says it is.
    pub rucc: String,
    /// What the reference says it is, since a number measured against gcc 13 and one measured
    /// against gcc 16 are different numbers.
    pub cc: String,
    /// The machine, because a Windows result and a Linux result are different results.
    pub machine: String,
    /// The optimization level both compilers were given, or `None` for their own defaults.
    pub opt: Option<String>,
    /// The memory limit that was actually applied, in kibibytes, or `None` when this machine
    /// has no way to set one and the report says so rather than pretending.
    pub memory: Option<u64>,
    /// How long each case got.
    pub timeout: Duration,
    /// Which lowering rules the builds in this run fired, when the run asked.
    ///
    /// About the rule set and not about any one case, which is why it is here rather than on an
    /// outcome. A caller sweeping several corpora unions these and quotes the union.
    pub fired: Option<Marks>,
}

impl Report {
    /// How many outcomes count as this word, which is one of [`WORDS`].
    #[must_use]
    pub fn count(&self, word: &str) -> usize {
        self.outcomes.iter().filter(|o| o.word() == word).count()
    }

    /// How many exclusions no longer exclude anything.
    #[must_use]
    pub fn stale(&self) -> usize {
        self.outcomes.iter().filter(|o| o.is_stale()).count() + self.unmatched.len()
    }

    /// How many things fail the run, which is the failures and the stale exclusions together.
    ///
    /// A stale exclusion counts because an exclusion list that only ever grows is a list that
    /// hides work rather than tracking it. When a case starts passing, the entry has to go.
    #[must_use]
    pub fn failures(&self) -> usize {
        self.outcomes.iter().filter(|o| o.is_failure()).count() + self.stale()
    }

    /// Every one of the eight counts, in order, including the ones that are zero.
    ///
    /// The zeroes are there on purpose. A report that prints only the outcomes it saw is a
    /// report where the reader cannot tell a corpus with no crashes from a corpus whose crashes
    /// were counted as something else.
    #[must_use]
    pub fn split(&self) -> Vec<(&'static str, usize)> {
        WORDS.iter().map(|word| (*word, self.count(word))).collect()
    }

    /// One line, for the terminal.
    #[must_use]
    pub fn summary(&self) -> String {
        let counts: Vec<String> =
            self.split().into_iter().map(|(word, n)| format!("{n} {word}")).collect();
        format!(
            "{}: {} runs, {}, {} stale",
            self.corpus,
            self.outcomes.len(),
            counts.join(", "),
            self.stale()
        )
    }
}

/// Builds and runs a corpus, every case on every route.
///
/// # Errors
///
/// When the corpus names no oracle, so nothing here could decide anything, or when the cases
/// cannot be worked out, which means the tree is not where it should be.
pub fn run(
    repo: &Path,
    corpus: &Corpus,
    settings: &Settings,
    scratch: &Path,
) -> Result<Report, Error> {
    let Some(oracle) = corpus.oracle else {
        return Err(Error {
            message: format!(
                "{}: no `oracle` in the manifest, so there is nothing to decide a run by",
                corpus.name
            ),
        });
    };
    let all = differ::cases(repo, corpus, scratch)?;
    let cases: Vec<Case> = match &settings.unit {
        Some(unit) => all.iter().filter(|c| c.unit == *unit).cloned().collect(),
        None => all.clone(),
    };
    if let Some(unit) = &settings.unit {
        if cases.is_empty() {
            return Err(Error {
                message: format!("{}: there is no unit called `{unit}`", corpus.name),
            });
        }
    }
    // Narrowed before the limit, so `--limit 20 --failed` is the first twenty of the failures
    // rather than whichever of the first twenty cases happened to fail.
    let record = ledger::path(repo, &corpus.name, "exec", settings.opt.as_deref());
    let keep = ledger::Keep::new(&settings.only, settings.failed.then_some(record.as_path()))
        .map_err(|message| Error { message: format!("{}: {message}", corpus.name) })?;
    let cases: Vec<Case> = cases.into_iter().filter(|c| keep.wants(&c.name)).collect();
    if cases.is_empty() && !keep.is_all() {
        return Err(Error { message: format!("{}: {}", corpus.name, keep.emptiness()) });
    }
    let cases = match settings.limit {
        Some(limit) => &cases[..limit.min(cases.len())],
        None => &cases[..],
    };

    let rucc = differ::program(&settings.rucc);
    let cc = differ::program(&settings.cc);
    let settings = Settings { rucc, cc, ..settings.clone() };
    let memory = settings.memory.and_then(sandbox::memory_limit);
    let seconds = settings.timeout.unwrap_or(corpus.timeout);
    let limits = Limits { timeout: Duration::from_secs(seconds), memory };

    // Several at a time. Each case owns a scratch directory named after itself and reads nothing
    // any other case wrote, so the only thing the threads share is the two compiler binaries and
    // neither of those is written to. See [`work`] for why this is not every core.
    let each = |case: &Case| -> (Vec<Outcome>, Result<Option<Marks>, String>) {
        let dir = scratch.join(stem(&case.name));
        let _ = fs::remove_dir_all(&dir);
        let mut mine = Vec::with_capacity(settings.routes.len());
        for (route, status) in check(case, corpus, oracle, &settings, &dir, &limits) {
            // Asked per route rather than once for the case, because an entry may name the paths
            // it speaks on and the three paths do not do the same thing with what rucc produced.
            let excused =
                corpus.exec_excuse(&case.name, settings.opt.as_deref(), route.word()).cloned();
            mine.push(Outcome { case: case.name.clone(), route, status, excused });
        }
        // Read before the directory goes, since what the compiler wrote about this case is in it.
        let fired = match settings.coverage {
            true => coverage::gather(&dir),
            false => Ok(None),
        };
        // Kept when something went wrong, because a case that failed is a case somebody is about
        // to want to look at, and thrown away otherwise, because a corpus of two thousand cases
        // times three routes is a great deal of disk to leave behind for nothing.
        if mine.iter().all(|o| o.status == Status::Passed) {
            let _ = fs::remove_dir_all(&dir);
        }
        (mine, fired)
    };
    let produced = work::spread(cases, work::jobs(settings.jobs), each);

    // The union is taken here rather than per case, because what a corpus reached is one answer
    // however many programs it took to reach it, and because merging in the order the cases were
    // in is what keeps the answer the same at every setting of `--jobs`.
    let mut outcomes: Vec<Outcome> = Vec::with_capacity(produced.len() * settings.routes.len());
    let mut fired = settings.coverage.then(Marks::default);
    for (case, (mine, gathered)) in cases.iter().zip(produced) {
        outcomes.extend(mine);
        let gathered =
            gathered.map_err(|message| Error { message: format!("{}: {message}", corpus.name) })?;
        if let (Some(all), Some(marks)) = (fired.as_mut(), gathered) {
            all.merge(&marks, &case.name).map_err(|message| Error { message })?;
        }
    }

    // One row per case and not per route, since `--failed` narrows by case. Green is the same
    // thing the run being green means, which is neither a failure nor a stale exclusion: an
    // exclusion that has started passing is a thing somebody has to act on, and a rerun that
    // called it green would be the one rerun where the only check for it cannot fire.
    let mut seen: Vec<(String, String, bool)> = Vec::with_capacity(cases.len());
    for outcome in &outcomes {
        let green = outcome.status == Status::Passed && !outcome.is_stale();
        let word = match outcome.is_stale() {
            true => "stale",
            false => outcome.word(),
        };
        match seen.last_mut() {
            Some(row) if row.0 == outcome.case => {
                row.2 &= green;
                if !green && row.1 == "passed" {
                    row.1 = word.to_owned();
                }
            }
            _ => seen.push((outcome.case.clone(), word.to_owned(), green)),
        }
    }
    if let Err(e) = ledger::save(&record, &seen) {
        eprintln!("{}: could not write {}: {e}", corpus.name, record.display());
    }

    let unmatched = match settings.is_whole() {
        true => corpus
            .exec_excluded
            .iter()
            .filter(|e| !all.iter().any(|c| c.name == e.case))
            .cloned()
            .collect(),
        false => Vec::new(),
    };
    Ok(Report {
        corpus: corpus.name.clone(),
        oracle,
        outcomes,
        unmatched,
        rucc: version(&settings.rucc),
        cc: version(&settings.cc),
        machine: settings.machine.clone().unwrap_or_else(platform),
        opt: settings.opt.clone(),
        memory,
        timeout: limits.timeout,
        fired,
    })
}

/// One case, built every way and run every time.
#[must_use]
pub fn check(
    case: &Case,
    corpus: &Corpus,
    oracle: Oracle,
    settings: &Settings,
    dir: &Path,
    limits: &Limits,
) -> Vec<(Route, Status)> {
    let inputs = inputs(case, corpus);
    let every = |status: &Status| -> Vec<(Route, Status)> {
        settings.routes.iter().map(|route| (*route, status.clone())).collect()
    };

    // The reference goes first, because it is the arbiter of what is a valid case and because
    // the first two routes need it as the assembler and the linker anyway. A program it refuses
    // is not a program we are failing to compile.
    let theirs = dir.join("reference");
    let theirs = match build(&settings.cc, false, Route::Driver, &inputs, case, settings, &theirs) {
        Ok(exe) => exe,
        Err(why) => return every(&Status::Skipped { why }),
    };
    // The reference is run under the other two oracles as well, and it is held to the same
    // rule the case under test will be. A self checking program that returns non-zero when the
    // reference built it, or one whose output does not match what the corpus recorded, is a
    // program written on assumptions no compiler released this decade holds to, and there is
    // nothing there to hold us to either. It is the same judgement the failed build above
    // makes, one step later, and it is made by running rather than by a list, so it cannot go
    // stale and nobody has to notice when the reference changes its mind.
    let expected = match oracle {
        Oracle::Differential => match sandbox::run(&theirs, &[] as &[&str], dir, limits) {
            Ok(ran) => Some(ran),
            Err(why) => return every(&Status::NotCompared { why }),
        },
        Oracle::SelfCheck | Oracle::Recorded => {
            match sandbox::run(&theirs, &[] as &[&str], dir, limits) {
                Err(why) => return every(&Status::Skipped { why }),
                Ok(ran) => match judge(oracle, case, &ran, None) {
                    Status::Passed => None,
                    // Nothing to hold the reference to is nothing to hold us to either, and it
                    // is not the reference getting the program wrong, so it keeps its own word.
                    missing @ Status::NotCompared { .. } => return every(&missing),
                    verdict => return every(&Status::Skipped { why: reference_failed(&verdict) }),
                },
            }
        }
    };

    let mut out = Vec::with_capacity(settings.routes.len());
    for route in &settings.routes {
        let at = dir.join(route.word());
        let status = match build(&settings.rucc, true, *route, &inputs, case, settings, &at) {
            Err(why) => Status::DidNotBuild { why },
            Ok(exe) => match sandbox::run(&exe, &[] as &[&str], &at, limits) {
                Err(why) => Status::DidNotBuild { why },
                Ok(ran) => judge(oracle, case, &ran, expected.as_ref()),
            },
        };
        out.push((*route, status));
    }
    out
}

/// Why a case whose own oracle the reference compiler does not satisfy is skipped.
///
/// It names the verdict rather than saying the reference failed, because the two verdicts it
/// can carry are different statements: a wrong answer means the program expects something no
/// compiler does, and a crash or a timeout means the program does not work at all here.
fn reference_failed(verdict: &Status) -> String {
    format!(
        "the reference compiler's own build of this program is a {}: {}",
        verdict.word(),
        verdict.why()
    )
}

/// The files that go into one case, which is the case itself and whatever its unit links with
/// every case.
fn inputs(case: &Case, corpus: &Corpus) -> Vec<PathBuf> {
    let mut inputs = vec![case.file.clone()];
    if let Some(unit) = corpus.units.iter().find(|u| u.name == case.unit) {
        inputs.extend(unit.link.iter().map(|name| case.dir.join(name)));
    }
    inputs
}

/// Builds one case one way, and answers with the executable.
///
/// # Errors
///
/// With what the compiler, the assembler or the linker said, which is a result and not a fault:
/// the caller turns it into an outcome that says which of the two compilers refused it.
fn build(
    compiler: &Path,
    mine: bool,
    route: Route,
    inputs: &[PathBuf],
    case: &Case,
    settings: &Settings,
    out: &Path,
) -> Result<PathBuf, String> {
    fs::create_dir_all(out).map_err(|e| format!("{}: {e}", out.display()))?;
    let exe = out.join("run");
    let recording = |what: &str| recording(mine, settings, out, what);
    match route {
        Route::Driver => {
            let mut args = flags(case, settings);
            args.extend(recording("driver"));
            for input in inputs {
                args.extend(spelled(input, &case.dir));
            }
            args.push("-o".into());
            args.push(exe.clone().into_os_string());
            once(compiler, &args, &case.dir)?;
        }
        Route::Assembly | Route::Object => {
            // One run of the compiler per input, because `-S` and `-c` each write one file and
            // there is nowhere for the second one to go.
            let (flag, ext) = match route {
                Route::Assembly => ("-S", "s"),
                _ => ("-c", "o"),
            };
            let mut parts = Vec::with_capacity(inputs.len());
            for (index, input) in inputs.iter().enumerate() {
                let part = out.join(format!("part{index}.{ext}"));
                let mut args = flags(case, settings);
                args.extend(recording(&format!("part{index}")));
                args.push(flag.into());
                args.extend(spelled(input, &case.dir));
                args.push("-o".into());
                args.push(part.clone().into_os_string());
                once(compiler, &args, &case.dir)?;
                parts.push(part);
            }
            // The reference compiler is the assembler and the linker, which is what makes this
            // route depend on nothing of ours after the assembly text.
            let mut args: Vec<OsString> = parts.into_iter().map(PathBuf::into_os_string).collect();
            // Whether the link makes a position independent executable is pinned rather than
            // inherited, because it is a distribution's choice and not a fact about the program.
            // Debian and Ubuntu build gcc to default to `-pie` and a gcc built from source
            // defaults the other way, so `execute/pr54937.c` failed here on one machine and
            // passed on another with the same compiler version, which is the sort of difference
            // an exclusion list cannot say anything true about. The driver route is left alone:
            // rucc's own driver decides that for itself, and a gap that only a position
            // independent link finds is one worth keeping a route that finds it.
            if cfg!(target_os = "linux") {
                args.push("-no-pie".into());
            }
            args.push("-o".into());
            args.push(exe.clone().into_os_string());
            once(&settings.cc, &args, out)?;
        }
    }
    Ok(exe)
}

/// The flag that asks for which lowering rules a build fired, when this build is one to ask.
///
/// Only ever handed to the compiler under test: it is an unstable option of ours and the
/// reference compiler would refuse the whole build over it. One file per invocation rather than
/// per case, since a case built through assembly runs the compiler once per input and the second
/// run would otherwise write over what the first one recorded.
fn recording(mine: bool, settings: &Settings, out: &Path, what: &str) -> Vec<OsString> {
    match mine && settings.coverage {
        false => Vec::new(),
        true => {
            let file = out.join(coverage::file_name(what));
            vec![format!("-Zrule-coverage={}", file.display()).into()]
        }
    }
}

/// Runs a compiler once and says what it said if it refused.
fn once(compiler: &Path, args: &[OsString], dir: &Path) -> Result<(), String> {
    let limits = Limits { timeout: BUILD_TIMEOUT, memory: None };
    let ran = sandbox::run(compiler, args, dir, &limits)?;
    match ran.end {
        End::Exited(0) => Ok(()),
        End::TimedOut => Err(format!(
            "{} took more than {} seconds over it",
            compiler.display(),
            BUILD_TIMEOUT.as_secs()
        )),
        End::Signalled { .. } | End::Faulted(_) => {
            Err(format!("{} died: {}", compiler.display(), ran.end.said()))
        }
        End::Exited(_) => Err(said(&ran.err)),
    }
}

/// The flags both compilers get for a case, which is the corpus's own and the level.
fn flags(case: &Case, settings: &Settings) -> Vec<OsString> {
    let mut args: Vec<OsString> = case.flags.iter().map(OsString::from).collect();
    if let Some(level) = settings.level() {
        args.push(level.into());
    }
    args
}

/// One input, as the compiler should be told about it.
///
/// A file with no `.c` on the end is not C to a compiler that goes by the extension, and
/// chibicc's `test/common` is exactly that, so `-x c` says what it is and `-x none` puts the
/// extension rule back for whatever comes after.
fn spelled(input: &Path, dir: &Path) -> Vec<OsString> {
    let short = named(input, dir);
    match short.extension().is_some_and(|e| e == "c") {
        true => vec![short.into_os_string()],
        false => {
            vec!["-x".into(), "c".into(), short.into_os_string(), "-x".into(), "none".into()]
        }
    }
}

/// Whether one run was right, by the corpus's oracle.
#[must_use]
pub fn judge(oracle: Oracle, case: &Case, ours: &Ran, theirs: Option<&Ran>) -> Status {
    // How it ended comes first, whatever the oracle is. A program killed by a signal has no
    // answer to compare, and a program that ran out of time never got to one.
    match &ours.end {
        End::TimedOut => return Status::TimedOut,
        End::Signalled { .. } | End::Faulted(_) => {
            return Status::Crashed { why: ours.end.said() };
        }
        End::Exited(_) => {}
    }
    match oracle {
        Oracle::SelfCheck => match ours.end.is_clean() {
            true => Status::Passed,
            false => Status::Wrong {
                why: format!(
                    "{}, and a program of this suite returns zero when it agrees with itself",
                    ours.end.said()
                ),
            },
        },
        Oracle::Recorded => match recorded(&case.file) {
            None => Status::NotCompared {
                why: "the corpus ships no expected output beside this program".to_owned(),
            },
            Some(want) => {
                if !ours.end.is_clean() {
                    return Status::Wrong { why: ours.end.said() };
                }
                let got = ours.text();
                match got == want {
                    true => Status::Passed,
                    false => Status::Wrong { why: differing(&want, &got) },
                }
            }
        },
        Oracle::Differential => match theirs {
            None => Status::NotCompared {
                why: "the reference compiler's program was never run".to_owned(),
            },
            Some(theirs) => {
                if ours.end != theirs.end {
                    return Status::Wrong {
                        why: format!(
                            "ours {} and the reference {}",
                            ours.end.said(),
                            theirs.end.said()
                        ),
                    };
                }
                match ours.out == theirs.out {
                    true => Status::Passed,
                    // Standard error is captured and not compared, because two compilers may
                    // legitimately produce programs that warn differently through library
                    // messages neither of them controls.
                    false => Status::Wrong { why: differing(&theirs.text(), &ours.text()) },
                }
            }
        },
    }
}

/// What the corpus says this program should print, if it says.
///
/// Two spellings, because the c-testsuite renamed these files at some point and the pin this
/// repository holds is on the older side of that. Looking for both costs one `stat` and saves
/// the whole corpus going quiet on the day the pin moves.
fn recorded(file: &Path) -> Option<String> {
    let mut name = file.as_os_str().to_owned();
    name.push(".expected");
    let older = PathBuf::from(name);
    let mut name = file.as_os_str().to_owned();
    name.push(".expected_output");
    let newer = PathBuf::from(name);
    fs::read_to_string(&older).or_else(|_| fs::read_to_string(&newer)).ok()
}

/// Where two outputs stopped agreeing, as one line somebody can read in a table.
///
/// The comparison itself is over the whole of both, always. This is the report cutting it down,
/// which is the only place that is allowed to happen.
#[must_use]
pub fn differing(want: &str, got: &str) -> String {
    let mut theirs = want.lines();
    let mut ours = got.lines();
    let mut at = 0;
    loop {
        at += 1;
        match (theirs.next(), ours.next()) {
            (None, None) => return "they differ only in how they end".to_owned(),
            (a, b) if a == b => {}
            (a, b) => {
                let a = cut(a.unwrap_or("<the output ends>"));
                let b = cut(b.unwrap_or("<the output ends>"));
                return format!("line {at}, wanted `{a}` and got `{b}`");
            }
        }
    }
}

/// One line of output, short enough for a table cell.
fn cut(line: &str) -> String {
    const KEEP: usize = 60;
    match line.chars().count() > KEEP {
        false => line.to_owned(),
        true => format!("{}...", line.chars().take(KEEP).collect::<String>()),
    }
}

/// What a compiler says it is, in one line.
fn version(compiler: &Path) -> String {
    let Ok(out) = Command::new(compiler).arg("--version").output() else {
        return format!("{} (it would not say)", compiler.display());
    };
    let text = String::from_utf8_lossy(&out.stdout);
    match text.lines().next() {
        Some(line) if !line.trim().is_empty() => line.trim().to_owned(),
        _ => format!("{} (it said nothing)", compiler.display()),
    }
}

/// The machine, as much of it as belongs in a file anybody may read.
fn platform() -> String {
    format!("{} {}", std::env::consts::OS, std::env::consts::ARCH)
}

/// The report, as the markdown that lands in `results/`.
#[must_use]
pub fn markdown(report: &Report, settings: &Settings) -> String {
    let mut out = String::new();
    let _ = writeln!(out, "# {} run\n", report.corpus);
    let _ = writeln!(out, "Compiler under test: `{}`.\n", report.rucc);
    let _ = writeln!(out, "Reference: `{}`.\n", report.cc);
    let _ = writeln!(out, "Machine: {}.\n", report.machine);
    let level = match &report.opt {
        Some(level) => format!("`-O{level}`"),
        None => "whatever each compiler defaults to".to_owned(),
    };
    let routes: Vec<&str> = settings.routes.iter().map(|r| r.word()).collect();
    let _ = writeln!(
        out,
        "Oracle: {}. Build paths: {}. Optimization: {level}.\n",
        report.oracle.word(),
        routes.join(", ")
    );
    let memory = match report.memory {
        Some(kib) => format!("{} MiB", kib / 1024),
        None => "none, this machine has no way to set one".to_owned(),
    };
    let _ = writeln!(
        out,
        "Each run gets {} seconds and a memory limit of {memory}.\n",
        report.timeout.as_secs()
    );
    if let Some(fired) = &report.fired {
        // The rules this corpus reached, which is about the rule set rather than about any case
        // here, and is a number only a corpus can produce. The list of the ones nothing reached
        // is its own report, since it is a list of work rather than a line of a summary.
        let _ = writeln!(
            out,
            "Lowering rules fired: {} of {}, which is {:.1} percent of `{}`.\n",
            fired.fired(),
            fired.rules.len(),
            fired.percent(),
            fired.source
        );
    }

    let _ = writeln!(out, "## Counts\n");
    let _ = writeln!(out, "| outcome | runs |");
    let _ = writeln!(out, "| --- | --- |");
    for (word, count) in report.split() {
        let _ = writeln!(out, "| {word} | {count} |");
    }
    let _ = writeln!(out);

    let failing: Vec<&Outcome> = report.outcomes.iter().filter(|o| o.is_failure()).collect();
    if failing.is_empty() {
        let _ = writeln!(out, "Nothing is failing that is not excluded.\n");
    } else {
        let _ = writeln!(out, "## Failing\n");
        let _ = writeln!(out, "| case | path | outcome | what happened |");
        let _ = writeln!(out, "| --- | --- | --- | --- |");
        for outcome in failing {
            let why = outcome.status.why().replace('|', "\\|");
            let _ = writeln!(
                out,
                "| {} | {} | {} | {why} |",
                outcome.case,
                outcome.route.word(),
                outcome.status.word()
            );
        }
        let _ = writeln!(out);
    }

    let stale: Vec<&Outcome> = report.outcomes.iter().filter(|o| o.is_stale()).collect();
    if !stale.is_empty() || !report.unmatched.is_empty() {
        let _ = writeln!(out, "## Exclusions to remove\n");
        for outcome in stale {
            let issue = outcome.excused.as_ref().map(|e| e.issue.clone()).unwrap_or_default();
            let _ = writeln!(
                out,
                "- `{}` passes on the {} path now, {issue}",
                outcome.case,
                outcome.route.word()
            );
        }
        for entry in &report.unmatched {
            let _ =
                writeln!(out, "- `{}` is not a case of this corpus, {}", entry.case, entry.issue);
        }
        let _ = writeln!(out);
    }

    let excluded: Vec<&Outcome> = report.outcomes.iter().filter(|o| o.is_covered()).collect();
    if !excluded.is_empty() {
        let _ = writeln!(out, "## Still excluded\n");
        let _ = writeln!(out, "| case | path | outcome | issue |");
        let _ = writeln!(out, "| --- | --- | --- | --- |");
        for outcome in excluded {
            let issue = outcome.excused.as_ref().map(|e| e.issue.clone()).unwrap_or_default();
            let _ = writeln!(
                out,
                "| {} | {} | {} | {issue} |",
                outcome.case,
                outcome.route.word(),
                outcome.status.word()
            );
        }
        let _ = writeln!(out);
    }
    out
}

/// A helper for the caller that has to name the file this corpus writes.
///
/// The level is in the name because a run at `-O0` and a run at `-O2` are different results and
/// writing them both to one path would leave whichever finished last.
#[must_use]
pub fn result_file(corpus: &str, opt: Option<&str>) -> String {
    match opt {
        None => format!("{corpus}-exec.md"),
        Some(level) => format!("{corpus}-exec-O{level}.md"),
    }
}

#[cfg(test)]
mod tests {
    use std::env;

    use super::*;
    use crate::corpus::EXEC_OUTCOMES;

    fn case(name: &str) -> Case {
        Case {
            unit: "u".to_owned(),
            name: name.to_owned(),
            file: PathBuf::from("/nowhere/a.c"),
            dir: PathBuf::from("/nowhere"),
            flags: Vec::new(),
        }
    }

    fn ran(end: End, out: &str) -> Ran {
        Ran { end, out: out.as_bytes().to_vec(), err: Vec::new() }
    }

    fn excusing(word: &str) -> Exclusion {
        Exclusion {
            case: "u/a.c".to_owned(),
            issue: "#1".to_owned(),
            why: "it does not work yet".to_owned(),
            when: Vec::new(),
            outcome: Some(word.to_owned()),
            opt: Vec::new(),
            route: Vec::new(),
        }
    }

    fn outcome(status: Status, excused: Option<Exclusion>) -> Outcome {
        Outcome { case: "u/a.c".to_owned(), route: Route::Object, status, excused }
    }

    fn report(outcomes: Vec<Outcome>) -> Report {
        Report {
            corpus: "t".to_owned(),
            oracle: Oracle::SelfCheck,
            outcomes,
            unmatched: Vec::new(),
            rucc: "rucc 0.3.7".to_owned(),
            cc: "gcc (GCC) 16.2.0".to_owned(),
            machine: "linux x86_64".to_owned(),
            opt: None,
            memory: None,
            timeout: Duration::from_secs(10),
            fired: None,
        }
    }

    /// The list the manifest validates against and the list the report prints have to be the
    /// same list, or an entry could name an outcome no case ever comes out as and would excuse
    /// nothing while looking as though it excused something.
    #[test]
    fn the_outcomes_an_exclusion_may_name_are_outcomes_a_case_can_have() {
        for word in EXEC_OUTCOMES {
            assert!(WORDS.contains(word), "`{word}` is not one of the eight");
        }
        let against: Vec<&str> = [
            Status::Wrong { why: String::new() },
            Status::Crashed { why: String::new() },
            Status::TimedOut,
            Status::DidNotBuild { why: String::new() },
        ]
        .iter()
        .map(Status::word)
        .collect();
        assert_eq!(against, EXEC_OUTCOMES);
    }

    #[test]
    fn a_signal_is_a_crash_and_the_exit_status_that_looks_like_one_is_not() {
        let killed = ran(End::Signalled { number: 11, name: "SIGSEGV" }, "");
        assert_eq!(
            judge(Oracle::SelfCheck, &case("u/a.c"), &killed, None),
            Status::Crashed { why: "SIGSEGV (11)".to_owned() }
        );
        let returned = ran(End::Exited(139), "");
        assert_eq!(
            judge(Oracle::SelfCheck, &case("u/a.c"), &returned, None).word(),
            "wrong answer"
        );
    }

    #[test]
    fn a_program_that_ran_out_of_time_is_not_a_program_that_gave_a_wrong_answer() {
        let out = judge(Oracle::SelfCheck, &case("u/a.c"), &ran(End::TimedOut, ""), None);
        assert_eq!(out, Status::TimedOut);
        assert_ne!(out.word(), "wrong answer");
    }

    #[test]
    fn a_self_checking_program_passes_by_returning_zero_and_fails_any_other_way() {
        let it = case("u/a.c");
        assert_eq!(
            judge(Oracle::SelfCheck, &it, &ran(End::Exited(0), "noise"), None),
            Status::Passed
        );
        assert!(judge(Oracle::SelfCheck, &it, &ran(End::Exited(1), ""), None).is_against_us());
    }

    #[test]
    fn the_differential_compares_the_status_and_the_output_and_not_the_complaints() {
        let it = case("u/a.c");
        let mut theirs = ran(End::Exited(3), "hello\n");
        theirs.err = b"a warning of theirs\n".to_vec();
        let mut ours = ran(End::Exited(3), "hello\n");
        ours.err = b"a different one of ours\n".to_vec();
        assert_eq!(judge(Oracle::Differential, &it, &ours, Some(&theirs)), Status::Passed);

        let ours = ran(End::Exited(3), "hello\nand then this\n");
        let out = judge(Oracle::Differential, &it, &ours, Some(&theirs));
        assert_eq!(out.word(), "wrong answer");
        assert!(out.why().contains("line 2"), "{}", out.why());
    }

    #[test]
    fn a_case_with_nothing_to_compare_against_is_not_compared_rather_than_passed() {
        let it = case("u/a.c");
        // The recorded oracle over a file with no recorded output beside it.
        let out = judge(Oracle::Recorded, &it, &ran(End::Exited(0), ""), None);
        assert_eq!(out.word(), "not compared");
        assert!(!out.is_against_us(), "an unmeasurable case is nobody's failure");
        assert_ne!(out, Status::Passed);
    }

    #[test]
    fn the_recorded_oracle_wants_the_output_it_was_given_and_a_clean_exit() {
        let dir = env::temp_dir().join(format!("rucc-compat-exec-{}", std::process::id()));
        let _ = fs::remove_dir_all(&dir);
        fs::create_dir_all(&dir).unwrap();
        let file = dir.join("a.c");
        fs::write(&file, "int main(void) { return 0; }\n").unwrap();
        fs::write(dir.join("a.c.expected"), "one\ntwo\n").unwrap();
        let it = Case { file, dir: dir.clone(), ..case("u/a.c") };

        assert_eq!(
            judge(Oracle::Recorded, &it, &ran(End::Exited(0), "one\ntwo\n"), None),
            Status::Passed
        );
        let out = judge(Oracle::Recorded, &it, &ran(End::Exited(0), "one\ntoo\n"), None);
        assert_eq!(out.word(), "wrong answer");
        assert!(out.why().contains("line 2"), "{}", out.why());
        // The right output and a status saying the program was unhappy is still not a pass.
        let out = judge(Oracle::Recorded, &it, &ran(End::Exited(1), "one\ntwo\n"), None);
        assert_eq!(out.word(), "wrong answer");
        let _ = fs::remove_dir_all(&dir);
    }

    /// A program whose own oracle the reference does not satisfy is not a case, and the word for
    /// that is the one a program the reference refused to build already gets. What it must not be
    /// is a pass, since a program neither compiler gets right is not a thing either of them got
    /// right, and it must not be a failure of ours either.
    #[test]
    fn a_case_the_reference_cannot_pass_either_is_skipped_and_says_which_way_it_failed() {
        let wrong = Status::Wrong { why: "returned 1".to_owned() };
        let skipped = Status::Skipped { why: reference_failed(&wrong) };
        assert_eq!(skipped.word(), "skipped");
        assert_eq!(
            skipped.why(),
            "the reference compiler's own build of this program is a wrong answer: returned 1"
        );
        assert!(!skipped.is_against_us());
        assert_eq!(report(vec![outcome(skipped, None)]).failures(), 0);

        let crashed = Status::Crashed { why: "killed by SIGSEGV".to_owned() };
        assert!(reference_failed(&crashed).contains("a crashed: killed by SIGSEGV"));
    }

    #[test]
    fn an_entry_that_admits_to_what_happened_excludes_it_and_one_that_does_not_fails_the_run() {
        let built =
            outcome(Status::DidNotBuild { why: "no".to_owned() }, Some(excusing("did not build")));
        assert_eq!(built.word(), "excluded");
        assert!(!built.is_failure());

        // The case the rule is written for. An entry admitting to a build failure does not cover
        // a wrong answer, which is a much worse admission and has to be seen.
        let wrong =
            outcome(Status::Wrong { why: "no".to_owned() }, Some(excusing("did not build")));
        assert_eq!(wrong.word(), "wrong answer");
        assert!(wrong.is_changed());
        assert!(wrong.is_failure());
    }

    #[test]
    fn an_entry_whose_case_has_started_passing_fails_the_run_so_the_list_shrinks() {
        let done = report(vec![outcome(Status::Passed, Some(excusing("did not build")))]);
        assert_eq!(done.stale(), 1);
        assert_eq!(done.failures(), 1);
        assert_eq!(done.count("passed"), 1);
    }

    #[test]
    fn an_entry_naming_a_case_that_is_not_in_the_corpus_fails_the_run_too() {
        let mut done = report(vec![outcome(Status::Passed, None)]);
        done.unmatched = vec![Exclusion { case: "u/gone.c".to_owned(), ..excusing("crashed") }];
        assert_eq!(done.failures(), 1);
    }

    #[test]
    fn a_case_the_reference_refuses_is_skipped_and_is_nobody_s_failure() {
        let done = report(vec![outcome(Status::Skipped { why: "gcc said no".to_owned() }, None)]);
        assert_eq!(done.count("skipped"), 1);
        assert_eq!(done.failures(), 0);
    }

    #[test]
    fn every_one_of_the_eight_is_counted_including_the_ones_that_did_not_happen() {
        let done = report(vec![
            outcome(Status::Passed, None),
            outcome(Status::Wrong { why: String::new() }, None),
        ]);
        let split = done.split();
        assert_eq!(split.len(), 8);
        assert_eq!(split[0], ("passed", 1));
        assert_eq!(split[1], ("wrong answer", 1));
        assert_eq!(split[2], ("crashed", 0));
    }

    #[test]
    fn a_run_of_part_of_a_corpus_says_nothing_about_the_exclusions_it_never_reached() {
        assert!(Settings::default().is_whole());
        assert!(!Settings { limit: Some(10), ..Settings::default() }.is_whole());
        assert!(!Settings { unit: Some("test".to_owned()), ..Settings::default() }.is_whole());
        assert!(!Settings { only: vec!["a".to_owned()], ..Settings::default() }.is_whole());
        assert!(!Settings { failed: true, ..Settings::default() }.is_whole());
    }

    #[test]
    fn the_report_names_both_compilers_the_machine_and_what_was_measured() {
        let text = markdown(&report(vec![outcome(Status::Passed, None)]), &Settings::default());
        assert!(text.contains("rucc 0.3.7"), "{text}");
        assert!(text.contains("gcc (GCC) 16.2.0"), "{text}");
        assert!(text.contains("linux x86_64"), "{text}");
        assert!(text.contains("self-check"), "{text}");
        assert!(text.contains("assembly, object, driver"), "{text}");
        // The limit that was not applied is said out loud rather than left to look like one.
        assert!(text.contains("no way to set one"), "{text}");
    }

    #[test]
    fn a_file_with_no_extension_is_named_as_c_and_the_rule_is_put_back_after_it() {
        let dir = Path::new("/tree");
        assert_eq!(spelled(Path::new("/tree/test/arith.c"), dir), ["test/arith.c"]);
        assert_eq!(
            spelled(Path::new("/tree/test/common"), dir),
            ["-x", "c", "test/common", "-x", "none"]
        );
    }

    /// The flag is ours and the reference has never heard of it, so handing it over would turn
    /// every case in the corpus into a program gcc refused, which the harness would read as the
    /// corpus being invalid rather than as the harness being wrong.
    #[test]
    fn only_the_compiler_under_test_is_asked_which_rules_it_fired() {
        let out = Path::new("/tmp/case/object");
        let on = Settings { coverage: true, ..Settings::default() };
        assert_eq!(
            recording(true, &on, out, "part0"),
            [OsString::from("-Zrule-coverage=/tmp/case/object/part0.cov")]
        );
        assert!(recording(false, &on, out, "driver").is_empty());
        // And nothing at all is asked for when nobody asked.
        assert!(recording(true, &Settings::default(), out, "part0").is_empty());
        // One file per invocation, since the two parts of a case are two runs of the compiler.
        assert_ne!(recording(true, &on, out, "part0"), recording(true, &on, out, "part1"));
    }

    #[test]
    fn the_report_says_what_the_run_reached_of_the_rule_set_when_it_was_asked() {
        let mut done = report(vec![outcome(Status::Passed, None)]);
        assert!(!markdown(&done, &Settings::default()).contains("Lowering rules"));

        let text = "\
# rucc rule coverage: 1 of 2 rules in rules/x86-64.rules fired
fired rules/x86-64.rules:12 (add.i32 x y)
unused rules/x86-64.rules:19 (sub.i32 x y)
";
        done.fired = Some(coverage::parse(text, "a.cov").unwrap());
        let text = markdown(&done, &Settings::default());
        assert!(text.contains("Lowering rules fired: 1 of 2"), "{text}");
        assert!(text.contains("50.0 percent"), "{text}");
    }

    #[test]
    fn the_level_is_in_the_result_file_name_because_two_levels_are_two_results() {
        assert_eq!(result_file("c-testsuite", None), "c-testsuite-exec.md");
        assert_eq!(result_file("c-testsuite", Some("2")), "c-testsuite-exec-O2.md");
    }

    #[test]
    fn a_long_line_of_output_is_cut_in_the_report_and_never_in_the_comparison() {
        let long = "x".repeat(400);
        let why = differing(&long, "y");
        assert!(why.contains("..."), "{why}");
        assert!(why.len() < 200, "{why}");
        // The comparison itself saw the whole of both, which is what made this a difference.
        assert_ne!(long, "y");
    }
}
