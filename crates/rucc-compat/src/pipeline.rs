//! The pipeline check: a corpus taken all the way through rucc on its own.
//!
//! The differential in [`crate::differ`] asks whether rucc preprocesses a file the way the
//! reference compiler does. This asks a different question, one no reference compiler can
//! answer: whether rucc gets the file through its own front end, its own lowering and its own
//! verifier, and whether the IR it wrote reads back as the IR it wrote. That is three runs of
//! the compiler over each case.
//!
//! Each case goes through:
//!
//! 1. `--emit=tast`, which is parsing and semantic analysis.
//! 2. `--emit=ir`, which is lowering, and which runs the verifier on the way out.
//! 3. `--emit=ir` again over the IR from step 2, which parses the IR back in and verifies it
//!    a second time, and the two texts have to be the same byte for byte.
//!
//! The round trip is the step worth explaining. A printer and a parser that disagree can each
//! look right on its own, and a text that does not survive being read back is a text that
//! cannot be trusted as the record of what the compiler decided. Comparing the second print
//! against the first is the cheapest way to find that out, and it costs one more run.

use std::fmt::Write as _;
use std::fs;
use std::path::{Path, PathBuf};
use std::process::Command;

use crate::corpus::{Corpus, Exclusion};
use crate::differ::{self, Case};
use crate::toml::Error;

/// How to run.
#[derive(Debug, Clone)]
pub struct Settings {
    /// The compiler under test.
    pub rucc: PathBuf,
    /// Stop after this many cases, for a quick look.
    pub limit: Option<usize>,
    /// Run only the unit of this name.
    pub unit: Option<String>,
}

impl Default for Settings {
    fn default() -> Settings {
        Settings { rucc: PathBuf::from("rucc"), limit: None, unit: None }
    }
}

impl Settings {
    /// Whether this run is looking at every case the corpus has.
    ///
    /// A part of a corpus cannot say anything about an exclusion it never reached, so the
    /// staleness check only runs when this is true.
    #[must_use]
    pub fn is_whole(&self) -> bool {
        self.limit.is_none() && self.unit.is_none()
    }
}

/// Which of the three runs a case did not get through.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Step {
    /// The front end, under `--emit=tast`.
    Tast,
    /// Lowering and the verifier, under `--emit=ir`.
    Ir,
    /// Reading that IR back in, which is the verifier a second time.
    Reread,
    /// Printing what was read back, which did not match what was printed the first time.
    RoundTrip,
}

impl Step {
    /// A word for the table.
    #[must_use]
    pub fn word(self) -> &'static str {
        match self {
            Step::Tast => "tast",
            Step::Ir => "ir",
            Step::Reread => "reread",
            Step::RoundTrip => "round-trip",
        }
    }
}

/// What happened to one case.
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum Status {
    /// All three runs got through and the two IR texts are the same.
    Passed,
    /// One of them did not.
    Failed {
        /// Where it stopped.
        step: Step,
        /// What it said, cut to the first few lines.
        why: String,
    },
}

impl Status {
    /// A word for the table.
    #[must_use]
    pub fn word(&self) -> &'static str {
        match self {
            Status::Passed => "passed",
            Status::Failed { step, .. } => step.word(),
        }
    }
}

/// One case and what came of it.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Outcome {
    /// The case name, which is the unit and the file.
    pub case: String,
    /// What happened.
    pub status: Status,
    /// The issue of the exclusion that covers it, when the manifest has one.
    pub excused: Option<String>,
}

impl Outcome {
    /// Whether this outcome fails the run.
    #[must_use]
    pub fn is_failure(&self) -> bool {
        self.excused.is_none() && matches!(self.status, Status::Failed { .. })
    }

    /// Whether this outcome is an exclusion that is no longer excluding anything.
    #[must_use]
    pub fn is_stale(&self) -> bool {
        self.excused.is_some() && self.status == Status::Passed
    }
}

/// Everything one corpus produced.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Report {
    /// Which corpus.
    pub corpus: String,
    /// Every case, in name order.
    pub outcomes: Vec<Outcome>,
    /// Exclusions that name a case this corpus does not have.
    ///
    /// Empty unless the whole corpus ran, since a filtered run has no opinion about a case it
    /// did not reach.
    pub unmatched: Vec<Exclusion>,
}

impl Report {
    /// How many cases got through.
    #[must_use]
    pub fn passed(&self) -> usize {
        self.outcomes.iter().filter(|o| o.status == Status::Passed).count()
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

    /// One line, for the terminal.
    #[must_use]
    pub fn summary(&self) -> String {
        let excused = self.outcomes.iter().filter(|o| o.excused.is_some()).count();
        format!(
            "{}: {} cases, {} passed, {} excluded, {} failing, {} stale",
            self.corpus,
            self.outcomes.len(),
            self.passed(),
            excused,
            self.outcomes.iter().filter(|o| o.is_failure()).count(),
            self.stale()
        )
    }
}

/// Runs a corpus through the pipeline.
///
/// # Errors
///
/// When the cases cannot be worked out, which means the tree is not where it should be.
pub fn run(
    repo: &Path,
    corpus: &Corpus,
    settings: &Settings,
    scratch: &Path,
) -> Result<Report, Error> {
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
    let cases = match settings.limit {
        Some(limit) => &cases[..limit.min(cases.len())],
        None => &cases[..],
    };
    let rucc = differ::program(&settings.rucc);
    let mut outcomes = Vec::with_capacity(cases.len());
    for case in cases {
        let status = check(case, &rucc, scratch);
        let excused = corpus.excuse(&case.name).map(|e| e.issue.clone());
        outcomes.push(Outcome { case: case.name.clone(), status, excused });
    }
    let unmatched = match settings.is_whole() {
        true => corpus
            .excluded
            .iter()
            .filter(|e| !all.iter().any(|c| c.name == e.case))
            .cloned()
            .collect(),
        false => Vec::new(),
    };
    Ok(Report { corpus: corpus.name.clone(), outcomes, unmatched })
}

/// Takes one case through the three runs.
#[must_use]
pub fn check(case: &Case, rucc: &Path, scratch: &Path) -> Status {
    if let Err(why) = emit(rucc, case, "tast", &case.file) {
        return Status::Failed { step: Step::Tast, why };
    }
    let first = match emit(rucc, case, "ir", &case.file) {
        Ok(text) => text,
        Err(why) => return Status::Failed { step: Step::Ir, why },
    };
    // The IR goes to a file rather than a pipe because the driver decides it is reading IR
    // from the `.ir` extension, and because a case that fails is a case somebody is about to
    // want to look at.
    let path = scratch.join(format!("{}.ir", stem(&case.name)));
    if let Some(dir) = path.parent() {
        if let Err(e) = fs::create_dir_all(dir) {
            return Status::Failed { step: Step::Reread, why: format!("{}: {e}", dir.display()) };
        }
    }
    if let Err(e) = fs::write(&path, &first) {
        return Status::Failed { step: Step::Reread, why: format!("{}: {e}", path.display()) };
    }
    let again = match emit(rucc, case, "ir", &path) {
        Ok(text) => text,
        Err(why) => return Status::Failed { step: Step::Reread, why },
    };
    if first != again {
        return Status::Failed { step: Step::RoundTrip, why: difference(&first, &again) };
    }
    Status::Passed
}

/// Runs rucc once, asking for one of the intermediate forms on standard output.
fn emit(rucc: &Path, case: &Case, what: &str, file: &Path) -> Result<String, String> {
    // Reading IR back in takes no flags of the corpus. Those flags are include paths and
    // language settings for the C, and the IR has already had all of that resolved into it.
    let is_ir_input = file.extension().is_some_and(|e| e == "ir");
    let mut command = Command::new(rucc);
    command.arg(format!("--emit={what}")).arg("-o").arg("-");
    if !is_ir_input {
        command.args(&case.flags);
    }
    let output = command.arg(named(file, &case.dir)).current_dir(&case.dir).output();
    let output = match output {
        Ok(output) => output,
        Err(e) => return Err(format!("could not run {}: {e}", rucc.display())),
    };
    if !output.status.success() {
        return Err(said(&output.stderr));
    }
    Ok(String::from_utf8_lossy(&output.stdout).into_owned())
}

/// The file as the compiler should be told about it, which is relative to the directory it
/// runs in whenever that is possible.
///
/// A diagnostic quotes the path it was given, so an absolute one puts the whole of a vendored
/// tree in front of every message and the report becomes unreadable. The compiler runs in the
/// tree already, so the short name resolves to the same file.
fn named(file: &Path, dir: &Path) -> PathBuf {
    match file.strip_prefix(dir) {
        Ok(relative) => relative.to_path_buf(),
        Err(_) => file.to_path_buf(),
    }
}

/// The part of what a failing run said that names the problem.
///
/// The errors come first, because a header three levels down produces an include chain and a
/// warning for every level of it, and a report that takes the first three lines of that is a
/// report of where the compiler was rather than of what went wrong. Everything else is kept
/// after them for the case where the run failed without saying `error` anywhere.
fn said(stderr: &[u8]) -> String {
    let text = String::from_utf8_lossy(stderr);
    let kept = |line: &&str| {
        let line = line.trim();
        !line.is_empty() && !line.starts_with("In file included from") && !line.starts_with("from ")
    };
    let lines: Vec<&str> = text.lines().filter(kept).collect();
    let (errors, rest): (Vec<&str>, Vec<&str>) =
        lines.into_iter().partition(|line| line.contains("error:"));
    let mut lines = errors;
    lines.extend(rest);
    lines.truncate(3);
    match lines.is_empty() {
        true => "it failed and said nothing".to_owned(),
        false => lines.join("; "),
    }
}

/// Where two IR texts stopped agreeing, as one line somebody can read in a table.
fn difference(first: &str, again: &str) -> String {
    let mut ours = first.lines();
    let mut theirs = again.lines();
    let mut at = 0;
    loop {
        at += 1;
        match (ours.next(), theirs.next()) {
            (None, None) => return "they differ only in how they end".to_owned(),
            (a, b) if a == b => {}
            (a, b) => {
                let a = a.unwrap_or("<the text ends>");
                let b = b.unwrap_or("<the text ends>");
                return format!("line {at}, printed `{a}` and read back as `{b}`");
            }
        }
    }
}

/// A case name turned into something that can be a file name.
fn stem(case: &str) -> String {
    case.replace(['/', '\\', ':'], "_")
}

/// The report, as the markdown that lands in `results/`.
#[must_use]
pub fn markdown(report: &Report, settings: &Settings) -> String {
    let mut out = String::new();
    let _ = writeln!(out, "# {} through the pipeline\n", report.corpus);
    let _ = writeln!(out, "Compiler under test: `{}`.\n", settings.rucc.display());
    let _ = writeln!(out, "{}\n", report.summary());
    let failing: Vec<&Outcome> = report.outcomes.iter().filter(|o| o.is_failure()).collect();
    if failing.is_empty() {
        let _ = writeln!(out, "Nothing is failing that is not excluded.\n");
    } else {
        let _ = writeln!(out, "## Failing\n");
        let _ = writeln!(out, "| case | step | what it said |");
        let _ = writeln!(out, "| --- | --- | --- |");
        for outcome in failing {
            let why = match &outcome.status {
                Status::Failed { why, .. } => why.replace('|', "\\|"),
                Status::Passed => String::new(),
            };
            let _ = writeln!(out, "| {} | {} | {why} |", outcome.case, outcome.status.word());
        }
        let _ = writeln!(out);
    }
    let stale: Vec<&Outcome> = report.outcomes.iter().filter(|o| o.is_stale()).collect();
    if !stale.is_empty() || !report.unmatched.is_empty() {
        let _ = writeln!(out, "## Exclusions to remove\n");
        for outcome in stale {
            let issue = outcome.excused.clone().unwrap_or_default();
            let _ = writeln!(out, "- `{}` passes now, {issue}", outcome.case);
        }
        for entry in &report.unmatched {
            let _ =
                writeln!(out, "- `{}` is not a case of this corpus, {}", entry.case, entry.issue);
        }
        let _ = writeln!(out);
    }
    let excluded: Vec<&Outcome> =
        report.outcomes.iter().filter(|o| o.excused.is_some() && !o.is_stale()).collect();
    if !excluded.is_empty() {
        let _ = writeln!(out, "## Still excluded\n");
        let _ = writeln!(out, "| case | issue | step |");
        let _ = writeln!(out, "| --- | --- | --- |");
        for outcome in excluded {
            let issue = outcome.excused.clone().unwrap_or_default();
            let _ = writeln!(out, "| {} | {issue} | {} |", outcome.case, outcome.status.word());
        }
        let _ = writeln!(out);
    }
    out
}

#[cfg(test)]
mod tests {
    use super::*;

    fn outcome(case: &str, status: Status, excused: Option<&str>) -> Outcome {
        Outcome { case: case.to_owned(), status, excused: excused.map(str::to_owned) }
    }

    fn failed(step: Step) -> Status {
        Status::Failed { step, why: "something".to_owned() }
    }

    #[test]
    fn a_case_that_gets_through_all_three_runs_is_the_only_thing_that_counts_as_passing() {
        let report = Report {
            corpus: "c-testsuite".to_owned(),
            outcomes: vec![
                outcome("t/a.c", Status::Passed, None),
                outcome("t/b.c", failed(Step::RoundTrip), None),
            ],
            unmatched: Vec::new(),
        };
        assert_eq!(report.passed(), 1);
        assert_eq!(report.failures(), 1);
    }

    #[test]
    fn a_failure_the_manifest_has_an_issue_for_does_not_fail_the_run() {
        let report = Report {
            corpus: "c-testsuite".to_owned(),
            outcomes: vec![outcome("t/a.c", failed(Step::Tast), Some("#142"))],
            unmatched: Vec::new(),
        };
        assert_eq!(report.failures(), 0);
    }

    #[test]
    fn an_exclusion_whose_case_has_started_passing_fails_the_run_so_the_list_shrinks() {
        let report = Report {
            corpus: "c-testsuite".to_owned(),
            outcomes: vec![outcome("t/a.c", Status::Passed, Some("#142"))],
            unmatched: Vec::new(),
        };
        assert_eq!(report.stale(), 1);
        assert_eq!(report.failures(), 1);
    }

    #[test]
    fn an_exclusion_naming_a_case_that_is_not_in_the_corpus_fails_the_run_too() {
        let entry = Exclusion {
            case: "t/gone.c".to_owned(),
            issue: "#142".to_owned(),
            why: "it was renamed upstream".to_owned(),
            when: Vec::new(),
        };
        let report = Report {
            corpus: "c-testsuite".to_owned(),
            outcomes: vec![outcome("t/a.c", Status::Passed, None)],
            unmatched: vec![entry],
        };
        assert_eq!(report.failures(), 1);
    }

    #[test]
    fn a_run_of_part_of_a_corpus_says_nothing_about_the_exclusions_it_never_reached() {
        let whole = Settings::default();
        assert!(whole.is_whole());
        assert!(!Settings { limit: Some(10), ..Settings::default() }.is_whole());
        assert!(!Settings { unit: Some("tests".to_owned()), ..Settings::default() }.is_whole());
    }

    #[test]
    fn the_round_trip_report_names_the_line_the_two_texts_stopped_agreeing_on() {
        let first = "func @f {\n  ret 1\n}\n";
        let again = "func @f {\n  ret 2\n}\n";
        assert_eq!(
            difference(first, again),
            "line 2, printed `  ret 1` and read back as `  ret 2`"
        );
    }

    #[test]
    fn a_text_that_reads_back_shorter_than_it_was_printed_says_where_it_stopped() {
        assert!(difference("a\nb\n", "a\n").contains("<the text ends>"));
    }

    #[test]
    fn what_a_failing_run_said_is_cut_to_the_lines_that_name_the_problem() {
        let stderr = b"one\n\ntwo\nthree\nfour\n";
        assert_eq!(said(stderr), "one; two; three");
        assert_eq!(said(b"   \n"), "it failed and said nothing");
    }

    #[test]
    fn the_error_is_reported_rather_than_the_include_chain_that_leads_to_it() {
        // A header three levels down gives this shape, and the first three lines of it say
        // nothing at all about what went wrong.
        let stderr = b"\
In file included from t.c:1:1:
                 from /usr/include/stdio.h:28:1:
                 from /usr/include/features.h:33:1:
/usr/include/features.h:33:1: warning: something minor
/usr/include/features.h:40:1: error: the thing that actually failed
";
        assert_eq!(
            said(stderr),
            "/usr/include/features.h:40:1: error: the thing that actually failed; \
/usr/include/features.h:33:1: warning: something minor"
        );
    }

    #[test]
    fn the_compiler_is_told_the_short_name_so_its_diagnostics_are_readable() {
        let tree = PathBuf::from("/vendor/c-testsuite/tests");
        assert_eq!(
            named(&tree.join("single-exec/00001.c"), &tree),
            Path::new("single-exec/00001.c")
        );
        // A scratch file is not under the tree and keeps the only name that finds it.
        let elsewhere = PathBuf::from("/tmp/pipeline/a.ir");
        assert_eq!(named(&elsewhere, &tree), elsewhere);
    }

    #[test]
    fn a_case_name_becomes_a_file_name_without_making_directories_that_are_not_there() {
        assert_eq!(stem("tests/single-exec/00001.c"), "tests_single-exec_00001.c");
    }
}
