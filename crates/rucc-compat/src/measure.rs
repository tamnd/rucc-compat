//! Holding rucc to a bound on how long a file takes to compile and how much memory it takes.
//!
//! Every other command asks whether rucc got something right. This one asks what it cost, which
//! is a different kind of regression and one none of them would notice: a compiler that starts
//! keeping every function's IR alive until the end of the file still produces the same object,
//! and the first anybody hears of it is a build machine running out of memory on a generated
//! parser. That has happened twice already, which is why it is a command rather than a hope.
//!
//! A unit opts in by naming a bound, `seconds`, `megabytes` or both, and the corpus names the
//! levels to compile it at. Each file of the unit is compiled to an object once per level, one
//! file at a time, and the run fails when rucc takes longer than the bound, holds more than the
//! bound, or does not produce an object at all.
//!
//! The reference compiles the same file at the same level first. Its numbers go in the report so
//! that a reader can see what the file costs a mature compiler, and nothing is ever judged by
//! them: gcc's cost moves between releases for reasons that have nothing to do with rucc. The one
//! thing the reference decides is whether the file is fair to ask for at all. A file the reference
//! will not compile on this machine is skipped rather than blamed on rucc.
//!
//! Nothing runs in parallel. Two compiles sharing a machine each take longer than either would
//! alone, and a time bound that is only met on an idle machine is not a bound anybody can use.

use std::ffi::OsString;
use std::fmt::Write as _;
use std::fs;
use std::path::{Path, PathBuf};
use std::time::Duration;

use crate::corpus::{Corpus, LEVELS};
use crate::differ::{self, Case};
use crate::exec;
use crate::pipeline::said;
use crate::sandbox::{self, End, Limits, Ran};
use crate::toml::Error;

/// How long a compile gets when its unit bounds memory and not time.
///
/// Something has to stop a compiler that has gone into a loop, and ten minutes is long enough that
/// nobody would call a file that needs it a working build.
pub const UNBOUNDED_TIME: Duration = Duration::from_secs(600);

/// How many times its memory bound a compile gets as address space before the system says no.
///
/// A guard for the machine rather than the bound itself. The bound is on resident memory and is
/// judged after the compile ends, which on its own would let a compiler that has regressed badly
/// push a shared machine into swap before anybody judged anything. Address space is always more
/// than what is resident, so the guard is set well above the bound and only ever stops a compile
/// that was going to fail the bound anyway.
pub const GUARD: u64 = 4;

/// How to run.
#[derive(Debug, Clone)]
pub struct Settings {
    /// The compiler under test.
    pub rucc: PathBuf,
    /// The reference, or `None` to measure rucc on its own.
    pub cc: Option<PathBuf>,
    /// One level to measure at instead of the ones the manifest names.
    pub opt: Option<String>,
    /// Measure only the unit of this name.
    pub unit: Option<String>,
    /// Measure only cases whose name contains one of these, or all of them when empty.
    pub only: Vec<String>,
    /// What to call the machine in the report, or `None` for the platform it runs on.
    pub machine: Option<String>,
}

impl Default for Settings {
    fn default() -> Settings {
        Settings {
            rucc: PathBuf::from("rucc"),
            cc: Some(PathBuf::from("cc")),
            opt: None,
            unit: None,
            only: Vec::new(),
            machine: None,
        }
    }
}

/// What one compile cost.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct Cost {
    /// How long it took.
    pub took: Duration,
    /// The most resident memory it held at once, in kibibytes, where the machine can say.
    pub peak: Option<u64>,
}

impl Cost {
    fn of(ran: &Ran) -> Cost {
        Cost { took: ran.took, peak: ran.peak }
    }

    /// The time and the memory, for a table.
    #[must_use]
    pub fn said(&self) -> String {
        let peak = match self.peak {
            Some(kib) => format!("{} MiB", kib.div_ceil(1024)),
            None => "memory unknown".to_owned(),
        };
        format!("{:.2} s, {peak}", self.took.as_secs_f64())
    }
}

/// The bounds one file is held to.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Default)]
pub struct Bound {
    /// Seconds, if time is bounded.
    pub seconds: Option<u64>,
    /// MiB of resident memory, if memory is bounded.
    pub megabytes: Option<u64>,
}

impl Bound {
    /// How long the compile gets before it is killed.
    #[must_use]
    pub fn timeout(&self) -> Duration {
        self.seconds.map_or(UNBOUNDED_TIME, Duration::from_secs)
    }

    /// The address space the compile is allowed, in kibibytes, if memory is bounded.
    #[must_use]
    pub fn guard(&self) -> Option<u64> {
        self.megabytes.map(|mib| mib * 1024 * GUARD)
    }

    /// The bounds, for a table.
    #[must_use]
    pub fn said(&self) -> String {
        let time = self.seconds.map(|s| format!("{s} s"));
        let memory = self.megabytes.map(|m| format!("{m} MiB"));
        [time, memory].into_iter().flatten().collect::<Vec<_>>().join(", ")
    }
}

/// How one compile of one file at one level came out.
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum Status {
    /// It produced an object inside every bound.
    Within,
    /// It was still going when its time ran out and was killed.
    OverTime,
    /// It held more resident memory than its bound at some point.
    OverMemory,
    /// It ended without producing an object, and this is what it said.
    DidNotBuild(String),
    /// It died on a signal.
    Crashed(String),
    /// The reference would not compile the file either, so it says nothing about rucc.
    Skipped(String),
}

impl Status {
    /// One word or phrase, for a table and for the summary.
    #[must_use]
    pub fn word(&self) -> &'static str {
        match self {
            Status::Within => "within",
            Status::OverTime => "over time",
            Status::OverMemory => "over memory",
            Status::DidNotBuild(_) => "did not build",
            Status::Crashed(_) => "crashed",
            Status::Skipped(_) => "skipped",
        }
    }

    /// Whether this fails the run.
    #[must_use]
    pub fn is_failure(&self) -> bool {
        !matches!(self, Status::Within | Status::Skipped(_))
    }
}

/// One file at one level.
#[derive(Debug, Clone)]
pub struct Outcome {
    /// The case, named the way every other report names it.
    pub case: String,
    /// The level, as the digit or letter after `-O`.
    pub level: String,
    /// What it was held to.
    pub bound: Bound,
    /// What rucc cost, or `None` when it was not asked because the reference refused the file.
    pub ours: Option<Cost>,
    /// What the reference cost, when there was a reference and it built the file.
    pub theirs: Option<Cost>,
    /// How it came out.
    pub status: Status,
}

/// Everything one corpus came to.
#[derive(Debug, Clone)]
pub struct Report {
    /// The corpus.
    pub corpus: String,
    /// What the compiler under test said it was.
    pub rucc: String,
    /// What the reference said it was, or `None` when there was none.
    pub cc: Option<String>,
    /// The machine.
    pub machine: String,
    /// Every file at every level, in the order they ran.
    pub outcomes: Vec<Outcome>,
}

impl Report {
    /// How many outcomes fail the run.
    #[must_use]
    pub fn failures(&self) -> usize {
        self.outcomes.iter().filter(|o| o.status.is_failure()).count()
    }

    /// One line, for the terminal.
    #[must_use]
    pub fn summary(&self) -> String {
        let mut parts = Vec::new();
        for word in ["within", "over time", "over memory", "did not build", "crashed", "skipped"] {
            let n = self.outcomes.iter().filter(|o| o.status.word() == word).count();
            if n > 0 || word == "within" {
                parts.push(format!("{n} {word}"));
            }
        }
        format!("{}: {} measured, {}", self.corpus, self.outcomes.len(), parts.join(", "))
    }
}

/// Judges one compile by rucc against its bound.
///
/// Memory is looked at before the way it ended, because a compile that blew through its bound and
/// was then stopped by the address space guard ends as a failure to allocate, and calling that
/// "did not build" would hide the thing that actually went wrong.
#[must_use]
pub fn judge(bound: Bound, ran: &Ran) -> Status {
    let over_memory = match (bound.megabytes, ran.peak) {
        (Some(mib), Some(kib)) => kib > mib * 1024,
        _ => false,
    };
    if ran.end == End::TimedOut {
        return Status::OverTime;
    }
    if over_memory {
        return Status::OverMemory;
    }
    match &ran.end {
        End::Exited(0) => Status::Within,
        End::Signalled { .. } | End::Faulted(_) => Status::Crashed(ran.end.said()),
        _ => Status::DidNotBuild(said(&ran.err)),
    }
}

/// Measures every bounded file of a corpus at every level the corpus names.
///
/// # Errors
///
/// When the tree is not there, when a level is not one, or when a compiler cannot be started at
/// all, which is a fact about this machine rather than about the file.
pub fn run(
    repo: &Path,
    corpus: &Corpus,
    settings: &Settings,
    scratch: &Path,
) -> Result<Report, Error> {
    let levels = match &settings.opt {
        Some(level) if !LEVELS.contains(&level.as_str()) => {
            return Err(Error {
                message: format!("`{level}` is not a level, try one of {}", LEVELS.join(", ")),
            });
        }
        Some(level) => vec![level.clone()],
        None => corpus.levels.clone(),
    };
    let found = differ::cases(repo, corpus, scratch)?;
    let bounded: Vec<(&Case, Bound)> = found
        .cases
        .iter()
        .filter_map(|case| {
            let unit = corpus.units.iter().find(|u| u.name == case.unit)?;
            let wanted = settings.unit.as_ref().is_none_or(|name| *name == unit.name)
                && (settings.only.is_empty()
                    || settings.only.iter().any(|p| case.name.contains(p)));
            (unit.is_bounded() && wanted)
                .then_some((case, Bound { seconds: unit.seconds, megabytes: unit.megabytes }))
        })
        .collect();
    fs::create_dir_all(scratch)
        .map_err(|e| Error { message: format!("{}: {e}", scratch.display()) })?;
    let object = scratch.join("measured.o");
    let mut outcomes = Vec::new();
    for level in &levels {
        for (case, bound) in &bounded {
            outcomes.push(one(case, *bound, level, settings, &object)?);
        }
    }
    let _ = fs::remove_file(&object);
    Ok(Report {
        corpus: corpus.name.clone(),
        rucc: exec::version(&settings.rucc),
        cc: settings.cc.as_deref().map(exec::version),
        machine: settings.machine.clone().unwrap_or_else(exec::platform),
        outcomes,
    })
}

/// One file at one level, the reference first.
fn one(
    case: &Case,
    bound: Bound,
    level: &str,
    settings: &Settings,
    object: &Path,
) -> Result<Outcome, Error> {
    let mut args: Vec<OsString> = case.flags.iter().map(OsString::from).collect();
    args.push(format!("-O{level}").into());
    args.push("-c".into());
    args.push(case.file.clone().into_os_string());
    args.push("-o".into());
    args.push(object.as_os_str().to_owned());
    let outcome = |ours, theirs, status| Outcome {
        case: case.name.clone(),
        level: level.to_owned(),
        bound,
        ours,
        theirs,
        status,
    };
    let mut theirs = None;
    if let Some(cc) = &settings.cc {
        // The reference gets the same guard and four times the time, since it is here to say
        // whether the file is fair and a slow reference is not a reason to call it unfair.
        let limits = Limits { timeout: bound.timeout() * 4, memory: None };
        let ran =
            sandbox::run(cc, &args, &case.dir, &limits).map_err(|message| Error { message })?;
        if !ran.end.is_clean() {
            let why = match ran.end {
                End::Exited(_) => said(&ran.err),
                _ => ran.end.said(),
            };
            return Ok(outcome(
                None,
                None,
                Status::Skipped(format!("the reference refused it: {why}")),
            ));
        }
        theirs = Some(Cost::of(&ran));
    }
    let limits =
        Limits { timeout: bound.timeout(), memory: bound.guard().and_then(sandbox::memory_limit) };
    let ran = sandbox::run(&settings.rucc, &args, &case.dir, &limits)
        .map_err(|message| Error { message })?;
    Ok(outcome(Some(Cost::of(&ran)), theirs, judge(bound, &ran)))
}

/// The file the report for a corpus is written to, under `results/`.
#[must_use]
pub fn result_file(corpus: &str) -> String {
    format!("{corpus}-measure.md")
}

/// The report, as the markdown that lands in `results/`.
#[must_use]
pub fn markdown(report: &Report) -> String {
    let mut out = String::new();
    let _ = writeln!(out, "# {} measured\n", report.corpus);
    let _ = writeln!(out, "Compiler under test: `{}`.\n", report.rucc);
    match &report.cc {
        Some(cc) => {
            let _ = writeln!(out, "Reference: `{cc}`, shown for comparison and never judged.\n");
        }
        None => {
            let _ = writeln!(out, "Reference: none.\n");
        }
    }
    let _ = writeln!(out, "Machine: {}.\n", report.machine);
    let _ = writeln!(
        out,
        "Each file is compiled to an object on its own, one at a time, and timed from start to finish. Memory is the most resident memory the compiler held at once.\n"
    );
    let _ = writeln!(out, "{}\n", report.summary());
    let _ = writeln!(out, "| Case | Level | Bound | rucc | Reference | Outcome |");
    let _ = writeln!(out, "| --- | --- | --- | --- | --- | --- |");
    for o in &report.outcomes {
        let ours = o.ours.map_or_else(|| "not run".to_owned(), |c| c.said());
        let theirs = o.theirs.map_or_else(|| "none".to_owned(), |c| c.said());
        let _ = writeln!(
            out,
            "| `{}` | `-O{}` | {} | {ours} | {theirs} | {} |",
            o.case,
            o.level,
            o.bound.said(),
            o.status.word()
        );
    }
    let reasons: Vec<&Outcome> = report
        .outcomes
        .iter()
        .filter(|o| {
            matches!(o.status, Status::DidNotBuild(_) | Status::Crashed(_) | Status::Skipped(_))
        })
        .collect();
    if !reasons.is_empty() {
        let _ = writeln!(out, "\n## What was said\n");
        for o in reasons {
            let why = match &o.status {
                Status::DidNotBuild(why) | Status::Crashed(why) | Status::Skipped(why) => why,
                _ => continue,
            };
            let _ = writeln!(out, "- `{}` at `-O{}`: {why}", o.case, o.level);
        }
    }
    out
}

#[cfg(test)]
mod tests {
    use super::*;

    fn ran(end: End, peak: Option<u64>) -> Ran {
        Ran {
            end,
            out: Vec::new(),
            err: b"error: something\n".to_vec(),
            took: Duration::from_millis(1500),
            peak,
        }
    }

    const BOUND: Bound = Bound { seconds: Some(60), megabytes: Some(100) };

    #[test]
    fn a_compile_inside_both_bounds_is_within_them() {
        assert_eq!(judge(BOUND, &ran(End::Exited(0), Some(100 * 1024))), Status::Within);
    }

    #[test]
    fn a_compile_that_held_more_than_its_bound_is_over_memory_even_though_it_built() {
        assert_eq!(judge(BOUND, &ran(End::Exited(0), Some(100 * 1024 + 1))), Status::OverMemory);
    }

    #[test]
    fn a_compile_stopped_by_the_guard_is_over_memory_rather_than_a_failure_to_build() {
        assert_eq!(judge(BOUND, &ran(End::Exited(1), Some(300 * 1024))), Status::OverMemory);
    }

    #[test]
    fn a_compile_that_was_killed_for_time_is_over_time() {
        assert_eq!(judge(BOUND, &ran(End::TimedOut, Some(10))), Status::OverTime);
    }

    #[test]
    fn a_compile_that_refused_says_why_and_one_that_died_says_how() {
        let refused = judge(BOUND, &ran(End::Exited(1), Some(10)));
        assert_eq!(refused.word(), "did not build");
        assert!(matches!(&refused, Status::DidNotBuild(why) if why.contains("something")));
        let died = judge(BOUND, &ran(End::Signalled { number: 11, name: "SIGSEGV" }, None));
        assert!(matches!(&died, Status::Crashed(why) if why.contains("SIGSEGV")));
    }

    #[test]
    fn a_memory_bound_means_nothing_where_the_machine_cannot_say_how_much_was_used() {
        assert_eq!(judge(BOUND, &ran(End::Exited(0), None)), Status::Within);
    }

    #[test]
    fn with_no_time_bound_a_compile_still_gets_stopped_eventually() {
        assert_eq!(Bound { seconds: None, megabytes: Some(1) }.timeout(), UNBOUNDED_TIME);
        assert_eq!(BOUND.timeout(), Duration::from_secs(60));
        assert_eq!(BOUND.guard(), Some(100 * 1024 * GUARD));
        assert_eq!(Bound::default().guard(), None);
    }

    #[test]
    fn only_a_skipped_or_within_outcome_leaves_the_run_green() {
        assert!(!Status::Within.is_failure());
        assert!(!Status::Skipped(String::new()).is_failure());
        for bad in [
            Status::OverTime,
            Status::OverMemory,
            Status::DidNotBuild(String::new()),
            Status::Crashed(String::new()),
        ] {
            assert!(bad.is_failure(), "{}", bad.word());
        }
    }

    #[test]
    fn the_report_names_every_file_at_every_level_and_the_reference_is_context() {
        let outcome = |level: &str, status| Outcome {
            case: "grammar/gram.c".to_owned(),
            level: level.to_owned(),
            bound: BOUND,
            ours: Some(Cost { took: Duration::from_millis(2410), peak: Some(206 * 1024) }),
            theirs: Some(Cost { took: Duration::from_millis(4550), peak: Some(137 * 1024) }),
            status,
        };
        let report = Report {
            corpus: "scale".to_owned(),
            rucc: "rucc 0.1".to_owned(),
            cc: Some("gcc 16".to_owned()),
            machine: "linux x86_64".to_owned(),
            outcomes: vec![outcome("0", Status::Within), outcome("2", Status::OverMemory)],
        };
        assert_eq!(report.failures(), 1);
        assert_eq!(report.summary(), "scale: 2 measured, 1 within, 1 over memory");
        let text = markdown(&report);
        assert!(text.contains("| `grammar/gram.c` | `-O0` | 60 s, 100 MiB | 2.41 s, 206 MiB | 4.55 s, 137 MiB | within |"), "{text}");
        assert!(text.contains("`-O2`"));
        assert!(text.contains("never judged"));
    }

    /// The whole command against a compiler that is a shell script, which is the one way to know
    /// that a file really is compiled, timed and judged without needing a compiler on the machine.
    #[cfg(unix)]
    #[test]
    fn a_corpus_is_measured_at_each_of_its_levels_and_a_slow_compiler_fails_the_bound() {
        use std::os::unix::fs::PermissionsExt as _;

        let root = std::env::temp_dir().join(format!("rucc-compat-measure-{}", std::process::id()));
        let _ = fs::remove_dir_all(&root);
        let tree = root.join("corpus").join("big");
        fs::create_dir_all(&tree).unwrap();
        fs::write(
            tree.join("corpus.toml"),
            "name = \"big\"\nsummary = \"s\"\nsource = \"installed\"\nlevels = [\"0\", \"2\"]\n\n[[unit]]\nname = \"g\"\nkind = \"source\"\nfiles = [\"corpus/big/a.c\"]\nseconds = 1\n\n[[unit]]\nname = \"free\"\nkind = \"source\"\nfiles = [\"corpus/big/a.c\"]\n",
        )
        .unwrap();
        fs::write(tree.join("a.c"), "int x;\n").unwrap();
        // Quick at -O0 and too slow at -O2, which is the shape of the regressions this is for.
        let script = |name: &str, body: &str| {
            let path = root.join(name);
            fs::write(&path, format!("#!/bin/sh\n{body}\n")).unwrap();
            fs::set_permissions(&path, fs::Permissions::from_mode(0o755)).unwrap();
            path
        };
        let rucc = script("rucc", "case \"$*\" in *-O2*) exec sleep 5 ;; esac\nexit 0");
        let cc = script("cc", "exit 0");
        let corpus = crate::corpus::load(&root, "big").unwrap();
        let settings = Settings { rucc, cc: Some(cc), ..Settings::default() };
        let report = run(&root, &corpus, &settings, &root.join("scratch")).unwrap();
        let _ = fs::remove_dir_all(&root);
        let seen: Vec<(&str, &str, &str)> = report
            .outcomes
            .iter()
            .map(|o| (o.case.as_str(), o.level.as_str(), o.status.word()))
            .collect();
        assert_eq!(
            seen,
            [("g/corpus/big/a.c", "0", "within"), ("g/corpus/big/a.c", "2", "over time")]
        );
        assert!(
            report.outcomes[1].ours.unwrap().took < Duration::from_secs(4),
            "killed at the bound"
        );
    }

    #[cfg(unix)]
    #[test]
    fn a_file_the_reference_refuses_is_skipped_and_rucc_is_not_asked() {
        use std::os::unix::fs::PermissionsExt as _;

        let root = std::env::temp_dir().join(format!("rucc-compat-refused-{}", std::process::id()));
        let _ = fs::remove_dir_all(&root);
        let tree = root.join("corpus").join("big");
        fs::create_dir_all(&tree).unwrap();
        fs::write(
            tree.join("corpus.toml"),
            "name = \"big\"\nsummary = \"s\"\nsource = \"installed\"\nlevels = [\"0\"]\n\n[[unit]]\nname = \"g\"\nkind = \"source\"\nfiles = [\"corpus/big/a.c\"]\nmegabytes = 64\n",
        )
        .unwrap();
        fs::write(tree.join("a.c"), "int x;\n").unwrap();
        let path = root.join("cc");
        fs::write(&path, "#!/bin/sh\necho 'a.c:1: error: no' >&2\nexit 1\n").unwrap();
        fs::set_permissions(&path, fs::Permissions::from_mode(0o755)).unwrap();
        let corpus = crate::corpus::load(&root, "big").unwrap();
        let settings =
            Settings { rucc: root.join("there-is-no-rucc"), cc: Some(path), ..Settings::default() };
        let report = run(&root, &corpus, &settings, &root.join("scratch")).unwrap();
        let _ = fs::remove_dir_all(&root);
        assert_eq!(report.outcomes.len(), 1);
        assert!(
            matches!(&report.outcomes[0].status, Status::Skipped(why) if why.contains("error: no"))
        );
        assert_eq!(report.outcomes[0].ours, None);
        assert_eq!(report.failures(), 0);
    }
}
