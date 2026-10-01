//! The accept and reject corpus: programs a compiler has to take, programs it has to refuse, and
//! the sentence each refusal has to say.
//!
//! Every other corpus here is made of programs that are meant to build, so all of them together
//! say nothing about the other half of a compiler's job. A compiler that took every file it was
//! given and made something of it would pass all of them, and it would also take a call to a
//! function nobody declared, a `float *` set from an `int *`, and a `break` with no loop around
//! it. Those are constraint violations, and the standard says a conforming compiler has to say
//! something about each one. gcc 16 makes most of them errors, and a program written against gcc
//! is written against those errors as much as against anything gcc compiles.
//!
//! So a case here is a small file that says at the top what it expects:
//!
//! ```c
//! /* verdict: reject */
//! /* error: break statement not within loop or switch */
//! int main(void) { break; return 0; }
//! ```
//!
//! An `accept` case passes when both compilers take it with `-fsyntax-only`. A `reject` case
//! passes when both refuse it and the error of each contains every `error:` sentence the case
//! names. The sentence is gcc's wording, which is the wording rucc has decided to use, so it is
//! held to the reference as well as to rucc: a sentence gcc 16 no longer says is a case that is
//! out of date, and the run says so rather than blaming rucc for it.
//!
//! gcc writes its quotes as `‘` and `’` when the locale allows it and as `'` when it does not,
//! and which one a machine gets is not something a case should have to know. Both are read as
//! `'` in the reference's output. rucc's output is read as it is.

use std::fs;
use std::path::{Path, PathBuf};
use std::time::Duration;

use crate::corpus::{Corpus, Exclusion};
use crate::differ::{self, Case};
use crate::sandbox::{self, End, Limits};
use crate::toml::Error;

/// What a case says it expects, read from the comments at the top of it.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Expect {
    /// Whether the program is one both compilers have to take.
    pub accept: bool,
    /// The sentences the error of a refused program has to contain, each one in full.
    pub sentences: Vec<String>,
}

/// Reads the expectation off the top of a case.
///
/// The header is the run of `/* key: value */` lines the file starts with, and it ends at the
/// first line that is not one, so a comment further down the program is never read as a promise.
///
/// # Errors
///
/// When there is no `verdict`, when it is something other than `accept` or `reject`, when an
/// accepted case names a sentence, and when a rejected case names none. A rejection with no
/// sentence would pass on a compiler that refused the program for the wrong reason, which is the
/// failure this corpus is here to catch.
pub fn expect(text: &str) -> Result<Expect, String> {
    let mut verdict = None;
    let mut sentences = Vec::new();
    for line in text.lines() {
        let line = line.trim();
        let Some(inner) = line.strip_prefix("/*").and_then(|l| l.strip_suffix("*/")) else {
            break;
        };
        let Some((key, value)) = inner.split_once(':') else { break };
        let value = value.trim().to_owned();
        match key.trim() {
            "verdict" => verdict = Some(value),
            "error" => sentences.push(value),
            other => return Err(format!("the header has `{other}`, which is not a key")),
        }
    }
    let accept = match verdict.as_deref() {
        Some("accept") => true,
        Some("reject") => false,
        Some(other) => return Err(format!("the verdict is `{other}`, not accept or reject")),
        None => return Err("the file does not start with a `/* verdict: ... */` line".to_owned()),
    };
    if accept && !sentences.is_empty() {
        return Err("an accepted case names an error it should not have".to_owned());
    }
    if !accept && sentences.is_empty() {
        return Err("a rejected case names no error it has to contain".to_owned());
    }
    Ok(Expect { accept, sentences })
}

/// How one case came out.
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum Status {
    /// Both compilers did what the case says, and every sentence was in both.
    Passed,
    /// rucc took a program it should have refused.
    AcceptedWrongly,
    /// rucc refused a program it should have taken, with the first thing it said.
    RejectedWrongly(String),
    /// rucc refused it without saying this sentence, with the first error it did say.
    WrongSentence {
        /// The sentence it did not say.
        missing: String,
        /// What it said instead.
        said: String,
    },
    /// rucc died, or ran out of time, rather than answering.
    Crashed(String),
    /// gcc 16 does not do what the case says, so the case is out of date rather than rucc wrong.
    ReferenceDisagrees(String),
    /// The header could not be read.
    BadHeader(String),
}

impl Status {
    /// The word the report groups by.
    #[must_use]
    pub fn word(&self) -> &'static str {
        match self {
            Status::Passed => "passed",
            Status::AcceptedWrongly => "accepted wrongly",
            Status::RejectedWrongly(_) => "rejected wrongly",
            Status::WrongSentence { .. } => "wrong sentence",
            Status::Crashed(_) => "crashed",
            Status::ReferenceDisagrees(_) => "reference disagrees",
            Status::BadHeader(_) => "bad header",
        }
    }

    /// What there is to say beyond the word, for a failure.
    #[must_use]
    pub fn detail(&self) -> String {
        match self {
            Status::Passed | Status::AcceptedWrongly => String::new(),
            Status::RejectedWrongly(said)
            | Status::Crashed(said)
            | Status::ReferenceDisagrees(said)
            | Status::BadHeader(said) => said.clone(),
            Status::WrongSentence { missing, said } => {
                format!("wanted \"{missing}\", said \"{said}\"")
            }
        }
    }
}

/// One case and how it came out.
#[derive(Debug, Clone)]
pub struct Outcome {
    /// The case name, the unit and the file.
    pub case: String,
    /// Whether it was an accept case, for the count.
    pub accept: bool,
    /// How it came out.
    pub status: Status,
    /// The exclusion that admits to it, when there is one.
    pub excused: Option<Exclusion>,
}

impl Outcome {
    /// A failure nothing admits to.
    #[must_use]
    pub fn is_failure(&self) -> bool {
        self.status != Status::Passed && self.excused.is_none()
    }

    /// An exclusion over a case that passes, which has to come off the list.
    #[must_use]
    pub fn is_stale(&self) -> bool {
        self.status == Status::Passed && self.excused.is_some()
    }
}

/// What a run over one corpus came to.
#[derive(Debug, Clone, Default)]
pub struct Report {
    /// The corpus.
    pub corpus: String,
    /// Every case, in name order.
    pub outcomes: Vec<Outcome>,
    /// Exclusions naming no case of the corpus.
    pub unmatched: Vec<Exclusion>,
}

impl Report {
    /// What makes the run red: failures nothing admits to, stale exclusions and unmatched ones.
    #[must_use]
    pub fn failures(&self) -> usize {
        self.outcomes.iter().filter(|o| o.is_failure() || o.is_stale()).count()
            + self.unmatched.len()
    }

    /// One line, the way the other commands print theirs.
    #[must_use]
    pub fn summary(&self) -> String {
        let count = |f: &dyn Fn(&Outcome) -> bool| self.outcomes.iter().filter(|o| f(o)).count();
        let accept = count(&|o| o.accept);
        let reject = self.outcomes.len() - accept;
        let passed = count(&|o| o.status == Status::Passed);
        let words = [
            "accepted wrongly",
            "rejected wrongly",
            "wrong sentence",
            "crashed",
            "reference disagrees",
            "bad header",
        ];
        let mut parts = vec![format!(
            "{}: {} cases, {accept} to accept and {reject} to reject, {passed} passed",
            self.corpus,
            self.outcomes.len()
        )];
        for word in words {
            parts.push(format!(
                "{} {word}",
                count(&|o| o.status.word() == word && o.excused.is_none())
            ));
        }
        parts.push(format!("{} excluded", count(&|o| o.excused.is_some())));
        parts.push(format!("{} stale", count(&Outcome::is_stale) + self.unmatched.len()));
        parts.join(", ")
    }
}

/// What to run.
#[derive(Debug, Clone)]
pub struct Settings {
    /// The compiler under test.
    pub rucc: PathBuf,
    /// The reference.
    pub cc: PathBuf,
    /// Only the cases whose names contain one of these, when there are any.
    pub only: Vec<String>,
}

/// Runs every case of a corpus through both compilers and judges each one.
///
/// # Errors
///
/// When the cases cannot be listed, or a compiler cannot be started at all.
pub fn run(
    repo: &Path,
    corpus: &Corpus,
    settings: &Settings,
    scratch: &Path,
) -> Result<Report, Error> {
    let found = differ::cases(repo, corpus, scratch)?;
    let limits = Limits { timeout: Duration::from_secs(corpus.timeout), memory: None };
    let mut report = Report { corpus: corpus.name.clone(), ..Report::default() };
    for case in &found.cases {
        if !settings.only.is_empty() && !settings.only.iter().any(|p| case.name.contains(p)) {
            continue;
        }
        let (accept, status) = judge(case, settings, &limits)?;
        let excused = corpus.excuse(&case.name).cloned();
        report.outcomes.push(Outcome { case: case.name.clone(), accept, status, excused });
    }
    if settings.only.is_empty() {
        report.unmatched = corpus
            .excluded
            .iter()
            .filter(|e| e.here() && !found.cases.iter().any(|c| c.name == e.case))
            .cloned()
            .collect();
    }
    Ok(report)
}

/// Builds one case with both compilers and says how it came out.
fn judge(case: &Case, settings: &Settings, limits: &Limits) -> Result<(bool, Status), Error> {
    let text = fs::read_to_string(&case.file)
        .map_err(|e| Error { message: format!("{}: {e}", case.file.display()) })?;
    let expect = match expect(&text) {
        Ok(expect) => expect,
        Err(why) => return Ok((false, Status::BadHeader(why))),
    };
    let mut args = case.flags.clone();
    args.push("-fsyntax-only".to_owned());
    args.push(case.file.display().to_string());
    let reference = sandbox::run(&settings.cc, &args, &case.dir, limits)
        .map_err(|message| Error { message })?;
    let ours = sandbox::run(&settings.rucc, &args, &case.dir, limits)
        .map_err(|message| Error { message })?;
    let theirs = plain_quotes(&String::from_utf8_lossy(&reference.err));
    let said = String::from_utf8_lossy(&ours.err).into_owned();
    if let Some(wrong) = disagrees(&expect, &reference.end, &theirs) {
        return Ok((expect.accept, Status::ReferenceDisagrees(wrong)));
    }
    let status = match ours.end {
        End::Exited(0) if expect.accept => Status::Passed,
        End::Exited(0) => Status::AcceptedWrongly,
        End::Exited(_) if expect.accept => Status::RejectedWrongly(first_error(&said)),
        End::Exited(_) => match expect.sentences.iter().find(|s| !errors(&said).contains(*s)) {
            Some(missing) => {
                Status::WrongSentence { missing: missing.clone(), said: first_error(&said) }
            }
            None => Status::Passed,
        },
        ref end => Status::Crashed(end.said()),
    };
    Ok((expect.accept, status))
}

/// What is wrong with the reference's answer, when it does not do what the case says.
fn disagrees(expect: &Expect, end: &End, said: &str) -> Option<String> {
    match end {
        End::Exited(0) if expect.accept => None,
        End::Exited(0) => Some("gcc takes it".to_owned()),
        End::Exited(_) if expect.accept => Some(format!("gcc refuses it: {}", first_error(said))),
        End::Exited(_) => {
            let found = errors(said);
            expect
                .sentences
                .iter()
                .find(|s| !found.contains(*s))
                .map(|missing| format!("gcc does not say \"{missing}\""))
        }
        other => Some(format!("gcc ended with {}", other.said())),
    }
}

/// The error lines of a compiler's output, joined, so that a sentence is looked for only where a
/// compiler said something was wrong and never in a note or a warning.
fn errors(said: &str) -> String {
    said.lines().filter(|line| line.contains("error:")).collect::<Vec<_>>().join("\n")
}

/// The first error a compiler gave, without the place it gave it at, for the report.
fn first_error(said: &str) -> String {
    said.lines()
        .find_map(|line| line.split_once("error: ").map(|(_, rest)| rest.trim().to_owned()))
        .unwrap_or_else(|| "no error line".to_owned())
}

/// gcc's typographic quotes as the plain ones it writes in the C locale.
fn plain_quotes(text: &str) -> String {
    text.replace(['\u{2018}', '\u{2019}'], "'")
}

/// The results as a page of markdown, for `--report`.
#[must_use]
pub fn markdown(report: &Report, settings: &Settings) -> String {
    let mut page = format!("# {} verdicts\n\n", report.corpus);
    page.push_str(&format!(
        "rucc is `{}` and the reference is `{}`. {}.\n\n",
        settings.rucc.display(),
        settings.cc.display(),
        report.summary()
    ));
    let failing: Vec<&Outcome> =
        report.outcomes.iter().filter(|o| o.status != Status::Passed).collect();
    if failing.is_empty() {
        page.push_str("Every case came out the way it says it should.\n");
        return page;
    }
    page.push_str("| case | outcome | detail | issue |\n|---|---|---|---|\n");
    for outcome in failing {
        let issue = outcome.excused.as_ref().map_or("", |e| e.issue.as_str());
        page.push_str(&format!(
            "| `{}` | {} | {} | {issue} |\n",
            outcome.case,
            outcome.status.word(),
            outcome.status.detail().replace('|', "\\|")
        ));
    }
    page
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn a_rejected_case_names_its_sentences() {
        let text = "/* verdict: reject */\n/* error: duplicate case value */\nint x;\n";
        let got = expect(text).expect("the header reads");
        assert!(!got.accept);
        assert_eq!(got.sentences, vec!["duplicate case value".to_owned()]);
    }

    #[test]
    fn the_header_ends_at_the_first_line_that_is_not_one() {
        let text = "/* verdict: accept */\nint x;\n/* error: not part of the header */\n";
        assert_eq!(expect(text), Ok(Expect { accept: true, sentences: Vec::new() }));
    }

    #[test]
    fn a_rejection_with_no_sentence_is_refused() {
        let e = expect("/* verdict: reject */\nint x;\n").expect_err("it names no sentence");
        assert!(e.contains("names no error"), "{e}");
    }

    #[test]
    fn an_accepted_case_with_a_sentence_is_refused() {
        let e = expect("/* verdict: accept */\n/* error: x */\n").expect_err("it names one");
        assert!(e.contains("should not have"), "{e}");
    }

    #[test]
    fn a_file_with_no_verdict_is_refused() {
        assert!(expect("int x;\n").is_err());
        assert!(expect("/* verdict: maybe */\n").is_err());
        assert!(expect("/* sentence: x */\n").is_err());
    }

    #[test]
    fn a_sentence_is_looked_for_only_in_errors() {
        let said = "a.c:1:1: warning: duplicate case value\na.c:2:1: error: something else\n";
        assert!(!errors(said).contains("duplicate case value"));
        assert_eq!(first_error(said), "something else");
    }

    #[test]
    fn the_reference_has_to_say_the_sentence_too() {
        let expect = Expect { accept: false, sentences: vec!["duplicate case value".to_owned()] };
        let said = "a.c:1:1: error: something else\n";
        let wrong = disagrees(&expect, &End::Exited(1), said).expect("gcc said something else");
        assert!(wrong.contains("does not say"), "{wrong}");
        assert_eq!(disagrees(&expect, &End::Exited(0), ""), Some("gcc takes it".to_owned()));
        let right = "a.c:1:1: error: duplicate case value\n";
        assert_eq!(disagrees(&expect, &End::Exited(1), right), None);
    }

    #[test]
    fn typographic_quotes_are_read_as_plain_ones() {
        assert_eq!(plain_quotes("label \u{2018}l\u{2019}"), "label 'l'");
    }
}
