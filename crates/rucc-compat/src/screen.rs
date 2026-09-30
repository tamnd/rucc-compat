//! Screening the reference, which is the one thing every oracle takes on trust.
//!
//! [`crate::exec`] holds rucc to what the reference compiler does. A differential oracle takes the
//! reference's output as the answer, and the other two run the reference's build first and skip
//! the case when it gets its own check wrong, so whatever gcc passes is what the harness believes.
//! That is only sound when the program has one right answer. A program that reads past the end of
//! an array, shifts a value by more than its width or overflows a signed integer has none: gcc
//! passes it because of where gcc put things and what gcc folded, and a compiler that put them
//! somewhere else is not wrong about it.
//!
//! So each case is built once more with the reference under the address and undefined behaviour
//! sanitizers and run, and what the sanitizers say is the answer to one question, which is whether
//! a pass or a failure on this case means anything. A case they flag has to be written down in
//! the manifest as an `[[untrustworthy]]` entry, and an entry for a case they no longer flag is
//! stale, the same two rules that keep the exclusion list honest.
//!
//! The screen says nothing about rucc and never runs it. What it produces is a statement about the
//! corpus, which is why it is its own command rather than a column in `exec`: a statement about
//! the corpus is true on every level and every path, and there is no reason to pay for it once
//! for each of them.

use std::fmt::Write as _;
use std::fs;
use std::path::Path;
use std::time::Duration;

use crate::corpus::{Corpus, Untrustworthy};
use crate::differ::{self, Case};
use crate::exec::{self, Route, Settings};
use crate::pipeline::stem;
use crate::sandbox::{End, Limits, Ran};
use crate::toml::Error;
use crate::work;

/// What the reference is built with, on top of the case's own flags and the level.
///
/// Both sanitizers at once, because they catch different halves of what makes an answer
/// meaningless and a second build of every case costs more than the second sanitizer does. Not
/// recovering is what makes the first finding the one that is reported, and keeping the frame
/// pointer is what makes a report say where it happened.
///
/// The one check taken back out is a left shift of a negative value or into the sign bit. ISO C
/// leaves that undefined and the GCC manual says in so many words that GNU C does not: the
/// section on integers under implementation-defined behaviour says gcc does not use the latitude,
/// and that `-fsanitize=shift` diagnoses it anyway. Every corpus here is compared under a GNU
/// dialect, so a program doing it has one right answer and the screen would be reporting the
/// sanitizer's opinion of ISO C rather than a program without one. A shift by the width or more
/// is still checked, since GNU C leaves that undefined as well.
pub const SANITIZE: &[&str] = &[
    "-fsanitize=address,undefined",
    "-fno-sanitize-recover=all",
    "-fno-sanitize=shift-base",
    "-fno-omit-frame-pointer",
];

/// What the programs are run with, through `env`, since the harness hands a run no environment of
/// its own.
///
/// Leak detection is off because a test program that exits without freeing what it allocated is
/// every test program, and a leak has no bearing on what the program printed. The stack traces
/// are off because the first line is the finding and the rest is noise in a table.
const OPTIONS: &[&str] = &["ASAN_OPTIONS=detect_leaks=0", "UBSAN_OPTIONS=print_stacktrace=0"];

/// How many times the corpus's own time a sanitized run gets, since every load and store is
/// checked and a program that finishes in time under the plain build can run out of it here.
const SLOWER: u32 = 4;

/// What came of screening one case.
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum Verdict {
    /// It ran under both sanitizers and neither said anything.
    Clean,
    /// A sanitizer reported something, which is the finding.
    Flagged {
        /// The line that said it.
        why: String,
    },
    /// It could not be screened, because the sanitized build failed or the run ended some way
    /// the sanitizers did not explain.
    ///
    /// Not a failure. A program that needs something the sanitizer runtime takes over, such as
    /// the stack or a fixed address, is not the program's fault or the screen's, and the plain
    /// build is still judged by `exec` the way it always was.
    Unscreened {
        /// What happened instead.
        why: String,
    },
}

impl Verdict {
    /// The word for this verdict in the report.
    #[must_use]
    pub fn word(&self) -> &'static str {
        match self {
            Verdict::Clean => "clean",
            Verdict::Flagged { .. } => "flagged",
            Verdict::Unscreened { .. } => "unscreened",
        }
    }

    /// What was said, or nothing when the word says it all.
    #[must_use]
    pub fn why(&self) -> &str {
        match self {
            Verdict::Clean => "",
            Verdict::Flagged { why } | Verdict::Unscreened { why } => why,
        }
    }
}

/// One case and what the screen made of it.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Outcome {
    /// The case name, the same string `exec` prints.
    pub case: String,
    /// What the sanitizers said.
    pub verdict: Verdict,
    /// The manifest entry saying this case is not to be trusted, when there is one.
    pub entry: Option<Untrustworthy>,
}

impl Outcome {
    /// Whether the sanitizers flagged a case the manifest says nothing about.
    #[must_use]
    pub fn is_unlisted(&self) -> bool {
        self.entry.is_none() && matches!(self.verdict, Verdict::Flagged { .. })
    }

    /// Whether the manifest calls this case untrustworthy and the sanitizers found nothing.
    ///
    /// Only a clean run makes an entry stale. A case that could not be screened has not been shown
    /// to be fine, and taking the entry out on that would be trusting it on no evidence at all.
    #[must_use]
    pub fn is_stale(&self) -> bool {
        self.entry.is_some() && self.verdict == Verdict::Clean
    }

    /// Whether this case fails the screen.
    #[must_use]
    pub fn is_failure(&self) -> bool {
        self.is_unlisted() || self.is_stale()
    }
}

/// Everything one corpus's screen produced.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Report {
    /// Which corpus.
    pub corpus: String,
    /// Every case, in name order.
    pub outcomes: Vec<Outcome>,
    /// Entries naming a case this corpus does not have, which is only known when every case ran.
    pub unmatched: Vec<Untrustworthy>,
    /// What the reference said it was.
    pub cc: String,
    /// What the machine is called.
    pub machine: String,
    /// The level both builds were made at.
    pub opt: Option<String>,
    /// How long each sanitized run got.
    pub timeout: Duration,
}

impl Report {
    /// How many cases fail the screen, counting an unmatched entry as one.
    #[must_use]
    pub fn failures(&self) -> usize {
        self.outcomes.iter().filter(|o| o.is_failure()).count() + self.unmatched.len()
    }

    /// How many cases came out as each verdict.
    #[must_use]
    pub fn count(&self, word: &str) -> usize {
        self.outcomes.iter().filter(|o| o.verdict.word() == word).count()
    }

    /// The one line the command prints for the corpus.
    #[must_use]
    pub fn summary(&self) -> String {
        format!(
            "{}: {} cases, {} clean, {} flagged, {} unscreened, {} failing the screen",
            self.corpus,
            self.outcomes.len(),
            self.count("clean"),
            self.count("flagged"),
            self.count("unscreened"),
            self.failures()
        )
    }
}

/// Screens one corpus.
///
/// # Errors
///
/// When the corpus has no oracle, when its cases cannot be listed, or when the unit asked for is
/// not one it has. A case that fails is an outcome, not an error.
pub fn run(
    repo: &Path,
    corpus: &Corpus,
    settings: &Settings,
    scratch: &Path,
) -> Result<Report, Error> {
    if corpus.oracle.is_none() {
        return Err(Error {
            message: format!(
                "{}: no `oracle` in the manifest, so nothing here is a program to screen",
                corpus.name
            ),
        });
    }
    let found = differ::without_helpers(differ::cases(repo, corpus, scratch)?, corpus);
    let all = found.cases;
    let cases: Vec<Case> = all
        .iter()
        .filter(|c| settings.unit.as_ref().is_none_or(|unit| c.unit == *unit))
        .filter(|c| settings.only.is_empty() || settings.only.iter().any(|p| c.name.contains(p)))
        .cloned()
        .collect();
    if let Some(unit) = &settings.unit {
        if cases.is_empty() {
            return Err(Error { message: differ::no_such_unit(corpus, unit) });
        }
    }
    let cases = match settings.limit {
        Some(limit) => &cases[..limit.min(cases.len())],
        None => &cases[..],
    };

    let cc = differ::program(&settings.cc);
    let mut runner: Vec<String> = vec!["env".to_owned()];
    runner.extend(OPTIONS.iter().map(|o| (*o).to_owned()));
    runner.extend(settings.runner.iter().cloned());
    // Only the path that builds with the reference's own driver, since the other two exist to
    // put rucc's output through the reference's assembler and linker and rucc is not in this.
    let settings = Settings { cc, runner, routes: vec![Route::Driver], ..settings.clone() };
    let seconds = settings.timeout.unwrap_or(corpus.timeout);
    // No memory limit. The address sanitizer reserves a shadow of the whole address space up front
    // and a limit on address space refuses it before `main` is reached.
    let limits = Limits { timeout: Duration::from_secs(seconds) * SLOWER, memory: None };

    let each = |case: &Case| -> Verdict {
        let dir = scratch.join(stem(&case.name));
        let _ = fs::remove_dir_all(&dir);
        let verdict = screen(case, corpus, &settings, &dir, &limits);
        // Kept when there is something to look at, the way `exec` keeps a failing case.
        if verdict == Verdict::Clean {
            let _ = fs::remove_dir_all(&dir);
        }
        verdict
    };
    let verdicts = work::spread(cases, work::jobs(settings.jobs), each);
    let outcomes: Vec<Outcome> = cases
        .iter()
        .zip(verdicts)
        .map(|(case, verdict)| Outcome {
            case: case.name.clone(),
            verdict,
            entry: corpus.untrustworthy_at(&case.name, settings.opt.as_deref()).cloned(),
        })
        .collect();

    let whole = settings.limit.is_none() && settings.unit.is_none() && settings.only.is_empty();
    let unmatched = match whole {
        true => corpus
            .untrustworthy
            .iter()
            .filter(|u| !all.iter().any(|c| c.name == u.case))
            .cloned()
            .collect(),
        false => Vec::new(),
    };
    Ok(Report {
        corpus: corpus.name.clone(),
        outcomes,
        unmatched,
        cc: exec::version(&settings.cc),
        machine: settings.machine.clone().unwrap_or_else(exec::platform),
        opt: settings.opt.clone(),
        timeout: limits.timeout,
    })
}

/// Builds one case with the reference under the sanitizers and runs it.
fn screen(
    case: &Case,
    corpus: &Corpus,
    settings: &Settings,
    dir: &Path,
    limits: &Limits,
) -> Verdict {
    let inputs = exec::inputs(case, corpus);
    let mut sanitized = case.clone();
    sanitized.flags.extend(SANITIZE.iter().map(|f| (*f).to_owned()));
    let exe = match exec::build(
        &settings.cc,
        false,
        Route::Driver,
        &inputs,
        &sanitized,
        settings,
        &dir.join("sanitized"),
    ) {
        Ok(exe) => exe,
        Err(why) => {
            return Verdict::Unscreened { why: format!("the sanitized build failed: {why}") };
        }
    };
    match exec::launch(&exe, dir, limits, settings) {
        Err(why) => Verdict::Unscreened { why },
        Ok(ran) => judge(&ran),
    }
}

/// What one sanitized run says.
///
/// The report is looked for whatever the exit status was, since a sanitizer that finds something
/// ends the program with an ordinary failing status and a program can fail on its own with the
/// sanitizers silent. Only the second of those is left to the plain build to judge.
#[must_use]
pub fn judge(ran: &Ran) -> Verdict {
    let err = String::from_utf8_lossy(&ran.err);
    if let Some(finding) = err.lines().find_map(finding) {
        return Verdict::Flagged { why: finding };
    }
    match &ran.end {
        End::Exited(_) => Verdict::Clean,
        other => Verdict::Unscreened {
            why: format!("it ended with {} and no sanitizer said why", other.said()),
        },
    }
}

/// The finding on one line of what a sanitized program wrote, if there is one there.
///
/// The undefined behaviour sanitizer writes `file:line:column: runtime error: what`, and the file
/// and position are kept because the same kind of finding in two places is two findings. The
/// address sanitizer writes `==pid==ERROR: AddressSanitizer: kind on address ...`, and the pid and
/// the address are taken off because they change on every run and a manifest line cannot match
/// them.
fn finding(line: &str) -> Option<String> {
    const KEEP: usize = 120;
    let short = |text: &str| match text.chars().count() > KEEP {
        false => text.to_owned(),
        true => format!("{}...", text.chars().take(KEEP).collect::<String>()),
    };
    if line.contains(": runtime error: ") {
        return Some(short(line.trim()));
    }
    let at = line.find("ERROR: ")?;
    let rest = &line[at + "ERROR: ".len()..];
    if !rest.contains("Sanitizer") {
        return None;
    }
    let rest = rest.split(" on address ").next().unwrap_or(rest);
    let rest = rest.split(" on unknown address").next().unwrap_or(rest);
    let rest = rest.split(" at pc ").next().unwrap_or(rest);
    Some(short(rest.trim()))
}

/// The screen as a document, for `--report`.
#[must_use]
pub fn markdown(report: &Report) -> String {
    let mut out = String::new();
    let _ = writeln!(out, "# {} screen\n", report.corpus);
    let _ = writeln!(out, "Reference: `{}`.\n", report.cc);
    let _ = writeln!(out, "Machine: {}.\n", report.machine);
    let level = match &report.opt {
        Some(level) => format!("`-O{level}`"),
        None => "the reference's default".to_owned(),
    };
    let _ = writeln!(
        out,
        "Built with `{}` at {level}, and each run gets {} seconds.\n",
        SANITIZE.join(" "),
        report.timeout.as_secs()
    );
    let _ = writeln!(out, "## Counts\n");
    let _ = writeln!(out, "| verdict | cases |");
    let _ = writeln!(out, "| --- | --- |");
    for word in ["clean", "flagged", "unscreened"] {
        let _ = writeln!(out, "| {word} | {} |", report.count(word));
    }
    let _ = writeln!(out);
    let rows: Vec<&Outcome> = report
        .outcomes
        .iter()
        .filter(|o| o.verdict != Verdict::Clean || o.entry.is_some())
        .collect();
    if !rows.is_empty() {
        let _ = writeln!(out, "## Cases\n");
        let _ = writeln!(out, "| case | verdict | in the manifest | what was said |");
        let _ = writeln!(out, "| --- | --- | --- | --- |");
        for o in rows {
            let listed = match (&o.entry, o.is_stale()) {
                (None, _) => "no",
                (Some(_), true) => "stale",
                (Some(_), false) => "yes",
            };
            let why = o.verdict.why().replace('|', "\\|");
            let _ = writeln!(out, "| `{}` | {} | {listed} | {why} |", o.case, o.verdict.word());
        }
        let _ = writeln!(out);
    }
    if !report.unmatched.is_empty() {
        let _ = writeln!(out, "## Entries naming no case\n");
        for u in &report.unmatched {
            let _ = writeln!(out, "- `{}`", u.case);
        }
        let _ = writeln!(out);
    }
    out
}

/// The name of the file `--report` writes.
#[must_use]
pub fn result_file(corpus: &str, opt: Option<&str>) -> String {
    match opt {
        None => format!("{corpus}-screen.md"),
        Some(level) => format!("{corpus}-screen-O{level}.md"),
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn ran(end: End, err: &str) -> Ran {
        Ran { end, out: Vec::new(), err: err.as_bytes().to_vec(), took: Duration::ZERO, peak: None }
    }

    #[test]
    fn an_undefined_behaviour_report_is_kept_with_where_it_was() {
        let got = judge(&ran(
            End::Exited(1),
            "pr1234.c:7:12: runtime error: signed integer overflow: 2147483647 + 1 cannot be represented in type 'int'\n",
        ));
        let Verdict::Flagged { why } = got else { panic!("{got:?}") };
        assert!(why.starts_with("pr1234.c:7:12: runtime error: signed integer overflow"), "{why}");
    }

    #[test]
    fn an_address_report_loses_the_pid_and_the_address() {
        let got = judge(&ran(
            End::Exited(1),
            "=================================================================\n==4242==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7ffd1234 at pc 0x4011 bp 0x7ffd sp 0x7ffc\n",
        ));
        assert_eq!(got, Verdict::Flagged { why: "AddressSanitizer: stack-buffer-overflow".into() });
    }

    #[test]
    fn a_failing_program_the_sanitizers_say_nothing_about_is_clean() {
        // The plain build is what `exec` judges. The screen only asks whether the sanitizers found
        // anything, and a program that calls `abort` on its own has not been caught doing
        // anything undefined.
        assert_eq!(judge(&ran(End::Exited(134), "")), Verdict::Clean);
    }

    #[test]
    fn a_signal_the_sanitizers_do_not_explain_is_not_screened() {
        let got = judge(&ran(End::Signalled { number: 6, name: "SIGABRT" }, ""));
        assert_eq!(got.word(), "unscreened");
    }

    #[test]
    fn an_error_line_from_something_other_than_a_sanitizer_is_not_a_finding() {
        assert_eq!(finding("ERROR: the test failed"), None);
    }

    #[test]
    fn a_stale_entry_needs_a_clean_run_and_not_just_a_missing_finding() {
        let entry = Some(Untrustworthy { case: "a.c".into(), why: "w".into(), opt: Vec::new() });
        let clean = Outcome { case: "a.c".into(), verdict: Verdict::Clean, entry: entry.clone() };
        assert!(clean.is_stale() && clean.is_failure());
        let unscreened =
            Outcome { case: "a.c".into(), verdict: Verdict::Unscreened { why: "x".into() }, entry };
        assert!(!unscreened.is_failure());
        let unlisted = Outcome {
            case: "a.c".into(),
            verdict: Verdict::Flagged { why: "x".into() },
            entry: None,
        };
        assert!(unlisted.is_unlisted() && unlisted.is_failure());
    }
}
