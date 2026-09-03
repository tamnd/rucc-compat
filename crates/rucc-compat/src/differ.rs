//! The differential: the same file through two preprocessors, and what came out different.

use std::fmt::Write as _;
use std::fs;
use std::path::{Path, PathBuf};
use std::process::Command;

use crate::corpus::{Corpus, Question, Register, Unit, UnitKind};
use crate::lexer;
use crate::toml::Error;

/// The comparison rules, which is what the register can suppress by name.
pub mod rule {
    /// The preprocessing tokens, in order, whatever the whitespace between them was.
    pub const TEXT: &str = "token-text";
    /// Where the spaces are, once runs of them are one space.
    pub const SPACING: &str = "spacing";
    /// The line markers.
    pub const MARKERS: &str = "markers";
}

/// How to run.
#[derive(Debug, Clone)]
pub struct Settings {
    /// The compiler under test.
    pub rucc: PathBuf,
    /// The reference, normally the system `cc`.
    pub cc: PathBuf,
    /// Whether to compare line markers as well.
    pub markers: bool,
    /// Stop after this many cases, for a quick look.
    pub limit: Option<usize>,
    /// Run only the unit of this name.
    pub unit: Option<String>,
}

impl Default for Settings {
    fn default() -> Settings {
        Settings {
            rucc: PathBuf::from("rucc"),
            cc: PathBuf::from("cc"),
            markers: false,
            limit: None,
            unit: None,
        }
    }
}

/// One thing to preprocess.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Case {
    /// Which unit of the corpus it came from.
    pub unit: String,
    /// What it is called in the report, which is the unit and the file.
    pub name: String,
    /// The file both compilers are pointed at.
    pub file: PathBuf,
    /// The directory they run in, so that a relative include in the corpus resolves the way
    /// it would if the corpus were being built.
    pub dir: PathBuf,
    /// Flags, already made absolute, passed to both unchanged.
    pub flags: Vec<String>,
}

/// The first place two outputs stopped agreeing.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Diff {
    /// Which line of the normalized output, counting from one.
    pub line: usize,
    /// What rucc printed.
    pub ours: String,
    /// What the reference printed.
    pub theirs: String,
}

/// What happened to one case.
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum Status {
    /// Both preprocessors agreed on everything that was compared.
    Same,
    /// The tokens differ. This is the failure that matters.
    Text(Diff),
    /// The tokens are the same and the spaces between them are not.
    Spacing(Diff),
    /// The tokens and the spacing are the same and the line markers are not.
    Markers(Diff),
    /// rucc could not preprocess something the reference could.
    Failed(String),
    /// The reference could not preprocess it either, so there is nothing to compare. Usually
    /// a header that is not meant to be included on its own.
    Unsupported(String),
}

impl Status {
    /// The rule this status is a breach of, if it is one.
    #[must_use]
    pub fn rule(&self) -> Option<&'static str> {
        match self {
            Status::Text(_) => Some(rule::TEXT),
            Status::Spacing(_) => Some(rule::SPACING),
            Status::Markers(_) => Some(rule::MARKERS),
            _ => None,
        }
    }

    /// Both sides of the first differing line, which is what a register entry matches in.
    ///
    /// Both rather than one, because a difference is as often something the reference printed
    /// and we did not as the other way around, and an entry should be able to name either.
    #[must_use]
    pub fn differing_line(&self) -> String {
        match self {
            Status::Text(d) | Status::Spacing(d) | Status::Markers(d) => {
                format!("{}\n{}", d.ours, d.theirs)
            }
            Status::Same | Status::Failed(_) | Status::Unsupported(_) => String::new(),
        }
    }

    /// A word for the table.
    #[must_use]
    pub fn word(&self) -> &'static str {
        match self {
            Status::Same => "same",
            Status::Text(_) => "tokens",
            Status::Spacing(_) => "spacing",
            Status::Markers(_) => "markers",
            Status::Failed(_) => "failed",
            Status::Unsupported(_) => "unsupported",
        }
    }
}

/// One case and what came of it.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Outcome {
    /// The case name.
    pub case: String,
    /// What happened.
    pub status: Status,
    /// The divergence that covers it, when the register has one.
    pub accepted: Option<String>,
}

impl Outcome {
    /// Whether this outcome fails the run.
    #[must_use]
    pub fn is_failure(&self) -> bool {
        if self.accepted.is_some() {
            return false;
        }
        matches!(
            self.status,
            Status::Text(_) | Status::Spacing(_) | Status::Markers(_) | Status::Failed(_)
        )
    }
}

/// Everything one corpus produced.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Report {
    /// Which corpus.
    pub corpus: String,
    /// Every case, in the order they ran.
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

    /// One line, for the terminal.
    #[must_use]
    pub fn summary(&self) -> String {
        let accepted = self.outcomes.iter().filter(|o| o.accepted.is_some()).count();
        format!(
            "{}: {} cases, {} same, {} unsupported, {} accepted, {} failing",
            self.corpus,
            self.outcomes.len(),
            self.count("same"),
            self.count("unsupported"),
            accepted,
            self.failures()
        )
    }
}

/// Runs a corpus.
///
/// # Errors
///
/// When the cases cannot be worked out, which means the tree is not where it should be.
pub fn run(
    repo: &Path,
    corpus: &Corpus,
    settings: &Settings,
    register: &Register,
    scratch: &Path,
) -> Result<Report, Error> {
    let cases = cases(repo, corpus, scratch)?;
    let cases: Vec<Case> = match &settings.unit {
        Some(unit) => cases.into_iter().filter(|c| c.unit == *unit).collect(),
        None => cases,
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
    let settings =
        &Settings { rucc: program(&settings.rucc), cc: program(&settings.cc), ..settings.clone() };
    // Everything that has to be the same on both sides before a difference means anything.
    let agree = agreement(&settings.cc);
    let mut outcomes = Vec::with_capacity(cases.len());
    for case in cases {
        let status = compare(case, settings, &agree);
        let differing = status.differing_line();
        let accepted = status
            .rule()
            .and_then(|rule| {
                register.accepts(Question {
                    rule,
                    corpus: &corpus.name,
                    unit: &case.unit,
                    text: &differing,
                })
            })
            .map(|d| d.id.clone());
        outcomes.push(Outcome { case: case.name.clone(), status, accepted });
    }
    Ok(Report { corpus: corpus.name.clone(), outcomes })
}

/// A program path a subprocess can find from any directory.
///
/// The compilers are run in the corpus tree rather than in the directory the harness was
/// started from, so `rucc/target/release/rucc` would be looked for in the tree and not found.
/// A bare name is left as it is, because that is a PATH lookup and the PATH does not care
/// where we are.
pub(crate) fn program(path: &Path) -> PathBuf {
    if path.is_absolute() || path.components().count() <= 1 {
        return path.to_path_buf();
    }
    match std::env::current_dir() {
        Ok(dir) => dir.join(path),
        Err(_) => path.to_path_buf(),
    }
}

/// Preprocesses one case both ways and says how they differed.
#[must_use]
pub fn compare(case: &Case, settings: &Settings, agree: &[String]) -> Status {
    let theirs = match preprocess(&settings.cc, case, &[]) {
        Ok(text) => text,
        Err(why) => return Status::Unsupported(why),
    };
    let ours = match preprocess(&settings.rucc, case, agree) {
        Ok(text) => text,
        Err(why) => return Status::Failed(why),
    };
    let ours = normalize(&ours);
    let theirs = normalize(&theirs);
    if ours.text != theirs.text {
        return Status::Text(first_difference(&ours, &theirs, By::Tokens));
    }
    if ours.spacing != theirs.spacing {
        return Status::Spacing(first_difference(&ours, &theirs, By::Spacing));
    }
    if settings.markers && ours.markers != theirs.markers {
        return Status::Markers(first_difference(&ours, &theirs, By::Markers));
    }
    Status::Same
}

/// Runs one preprocessor, or says why it would not.
fn preprocess(program: &Path, case: &Case, extra: &[String]) -> Result<String, String> {
    let output = Command::new(program)
        .arg("-E")
        .args(extra)
        .args(&case.flags)
        .arg(&case.file)
        .current_dir(&case.dir)
        .output();
    let output = match output {
        Ok(output) => output,
        Err(e) => return Err(format!("{}: {e}", program.display())),
    };
    if !output.status.success() {
        return Err(why(&String::from_utf8_lossy(&output.stderr)));
    }
    Ok(String::from_utf8_lossy(&output.stdout).into_owned())
}

/// The separator between tokens in [`Normalized::text`].
///
/// A byte that no C source has any business containing, so that two tokens joined by it can
/// never be mistaken for one token that was spelled that way.
const SEPARATOR: char = '\u{1}';

/// How many diagnostics a failure is worth keeping. The first one is normally the cause and
/// the rest are what it led to, but one line on its own is often the include chain rather
/// than the error, and a report that only says which file we were in is no use to anybody.
const KEPT: usize = 3;

/// The interesting part of what a compiler said before it gave up.
fn why(stderr: &str) -> String {
    let diagnostics: Vec<&str> = stderr
        .lines()
        .filter(|line| line.contains("error:") || line.contains("fatal:"))
        .take(KEPT)
        .collect();
    if !diagnostics.is_empty() {
        return diagnostics.join("\n");
    }
    let lines: Vec<&str> = stderr.lines().take(KEPT).collect();
    if lines.is_empty() {
        return "exited with a failure and said nothing".to_owned();
    }
    lines.join("\n")
}

/// One output, in the three forms the three rules compare.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Normalized {
    /// Every preprocessing token, in order, joined by a byte no C source contains. This is
    /// what the `token-text` rule compares, and it is a string rather than a list because the
    /// amalgamation is two million tokens and this way it costs about what the output costs.
    pub text: String,
    /// The non marker lines, blank ones dropped and runs of spaces collapsed.
    pub spacing: Vec<String>,
    /// The same lines as `spacing`, as their tokens rather than as their text. This is what
    /// says which line a token difference is on, and `spacing` is what gets printed for it: a
    /// reader wants the line as it was written, and a search over the collapsed text would
    /// stop at the first line whose spacing differs, which is not the same line at all.
    pub tokens: Vec<String>,
    /// The line marker lines.
    pub markers: Vec<String>,
}

/// Splits an output into the forms the rules compare.
#[must_use]
pub fn normalize(out: &str) -> Normalized {
    let mut text = String::with_capacity(out.len());
    let mut spacing = Vec::new();
    let mut tokens = Vec::new();
    let mut markers = Vec::new();
    for line in out.lines() {
        let line = line.trim_end();
        if is_marker(line) {
            // The preamble markers name a file that does not exist, and the two compilers
            // disagree on whether to emit them at all. That is not a property of the corpus.
            if !line.contains("<built-in>")
                && !line.contains("<command-line>")
                && !line.contains("<command line>")
            {
                markers.push(collapse(line));
            }
            continue;
        }
        if line.trim().is_empty() {
            continue;
        }
        let mut line_tokens = String::new();
        for token in lexer::tokens(line) {
            if !text.is_empty() {
                text.push(SEPARATOR);
            }
            text.push_str(&token);
            if !line_tokens.is_empty() {
                line_tokens.push(SEPARATOR);
            }
            line_tokens.push_str(&token);
        }
        tokens.push(line_tokens);
        spacing.push(collapse(line));
    }
    Normalized { text, spacing, tokens, markers }
}

/// A line marker, which is the only `#` line that survives preprocessing.
fn is_marker(line: &str) -> bool {
    let rest = line.trim_start();
    let Some(rest) = rest.strip_prefix('#') else { return false };
    let rest = rest.trim_start();
    rest.starts_with(|c: char| c.is_ascii_digit())
}

/// The line with leading space dropped and every run of whitespace one space.
fn collapse(line: &str) -> String {
    let mut out = String::with_capacity(line.len());
    for word in line.split_whitespace() {
        if !out.is_empty() {
            out.push(' ');
        }
        out.push_str(word);
    }
    out
}

/// The first line the two disagree on, found in `by` and printed from `show`.
///
/// Two arrays because the question and the answer are not the same text. A token difference is
/// located by comparing tokens, since a search over the collapsed lines would stop at the
/// first line whose spacing differs and report a missing space as though it were the bug. What
/// gets printed is still the line, because that is what a reader can act on.
///
/// `by` and `show` are the same length and line up, so an index found in one is valid in the
/// other.
fn first_difference(ours: &Normalized, theirs: &Normalized, by: By) -> Diff {
    let (mine, yours) = match by {
        By::Tokens => (&ours.tokens, &theirs.tokens),
        By::Spacing => (&ours.spacing, &theirs.spacing),
        By::Markers => (&ours.markers, &theirs.markers),
    };
    let mut at = 0;
    while at < mine.len() && at < yours.len() && mine[at] == yours[at] {
        at += 1;
    }
    let (show_ours, show_theirs) = match by {
        By::Markers => (&ours.markers, &theirs.markers),
        By::Tokens | By::Spacing => (&ours.spacing, &theirs.spacing),
    };
    Diff {
        line: at + 1,
        ours: show_ours.get(at).cloned().unwrap_or_else(|| "<end of output>".to_owned()),
        theirs: show_theirs.get(at).cloned().unwrap_or_else(|| "<end of output>".to_owned()),
    }
}

/// Which of the three forms a search runs over.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
enum By {
    Tokens,
    Spacing,
    Markers,
}

/// The flags that make rucc configured the way the reference compiler already is.
///
/// A difference between two compilers only means something if they were asked the same
/// question. These are the parts of the question that the reference answers for itself and
/// that we would otherwise have to guess, so they are read off the reference rather than
/// written down: the headers it reads, the compiler it says it is, and the language it thinks
/// it is compiling.
#[must_use]
pub fn agreement(cc: &Path) -> Vec<String> {
    let mut flags = system_includes(cc);
    flags.extend(predefined(cc));
    flags
}

/// The flags read out of the reference compiler's own `-dM` dump.
///
/// One subprocess, because both answers are in the same output and running the compiler twice
/// to read one macro each would be two chances for them to disagree.
fn predefined(cc: &Path) -> Vec<String> {
    let Ok(output) = Command::new(cc).args(["-dM", "-E", "-x", "c", "/dev/null"]).output() else {
        return Vec::new();
    };
    let text = String::from_utf8_lossy(&output.stdout);
    let dump = Dump::read(&text);
    let mut flags = Vec::new();
    if let Some(version) = dump.gnuc_version() {
        flags.push(format!("-fgnuc-version={version}"));
    }
    if let Some(std) = dump.std() {
        flags.push(format!("-std={std}"));
    }
    flags
}

/// A `-dM` dump, as the questions we ask it.
///
/// Split from the subprocess so that the tests run against a dump written down in the test
/// rather than against whichever compiler the machine running them happens to have.
struct Dump<'a> {
    lines: Vec<(&'a str, &'a str)>,
}

impl<'a> Dump<'a> {
    fn read(text: &'a str) -> Dump<'a> {
        let lines = text
            .lines()
            .filter_map(|line| line.strip_prefix("#define "))
            // A function-like macro has no space before its parenthesis, so this splits its
            // name off with the parameters attached, and none of the macros asked about here
            // are function-like.
            .map(|rest| rest.split_once(' ').unwrap_or((rest, "")))
            .collect();
        Dump { lines }
    }

    fn get(&self, name: &str) -> Option<&'a str> {
        self.lines.iter().find(|(n, _)| *n == name).map(|(_, value)| value.trim())
    }

    fn number(&self, name: &str) -> Option<u32> {
        self.get(name)?.parse().ok()
    }

    /// What the reference answers `__GNUC_PREREQ` with, as `major.minor.patch`.
    ///
    /// This is not cosmetic. glibc's `sys/cdefs.h` gates most of what it hands a caller on
    /// `__GNUC_PREREQ`, so two compilers claiming different versions are handed different
    /// headers and are no longer preprocessing the same program.
    ///
    /// `None` when the reference does not define `__GNUC__` at all, which means it is not
    /// pretending to be GCC and neither should we make it.
    fn gnuc_version(&self) -> Option<String> {
        // The major has to be there. A minor or a patchlevel that is missing is zero, the way
        // GCC treats a release that has none.
        let major = self.number("__GNUC__")?;
        let minor = self.number("__GNUC_MINOR__").unwrap_or(0);
        let patch = self.number("__GNUC_PATCHLEVEL__").unwrap_or(0);
        Some(format!("{major}.{minor}.{patch}"))
    }

    /// The `-std=` argument that asks for the language the reference is already compiling.
    ///
    /// The default dialect is not the same across compilers and it is not the same across
    /// releases of one compiler, so it cannot be written down. GCC 13 defaults to gnu17 and
    /// rucc defaults to gnu23, and that difference alone gives us `nullptr_t` out of
    /// `stddef.h` and `char8_t` out of `uchar.h` that the reference never sees.
    ///
    /// `__STRICT_ANSI__` is the extensions question, which is a separate axis from the year
    /// and is exactly the difference between `c17` and `gnu17`.
    fn std(&self) -> Option<String> {
        let year = match self.get("__STDC_VERSION__") {
            // No `__STDC_VERSION__` at all is C89, which never defined it.
            None => "89",
            Some("199409L") => "89",
            Some("199901L") => "99",
            Some("201112L") => "11",
            Some("201710L") => "17",
            Some("202311L") => "23",
            // A version we do not have a spelling for. Saying nothing leaves our own default
            // in place, which is wrong but is at least a difference the report will show,
            // rather than a flag that asks for the wrong language.
            Some(_) => return None,
        };
        let strict = self.get("__STRICT_ANSI__").is_some();
        Some(format!("{}{year}", if strict { "c" } else { "gnu" }))
    }
}

/// The directories the reference compiler searches for `#include <...>`, as `-isystem` flags.
///
/// GCC and clang both print this list under `-v` while preprocessing, between two lines that
/// have said the same thing for twenty years.
#[must_use]
pub fn system_includes(cc: &Path) -> Vec<String> {
    let output = Command::new(cc).args(["-E", "-v", "-x", "c", "/dev/null"]).output();
    let Ok(output) = output else { return Vec::new() };
    let text = String::from_utf8_lossy(&output.stderr);
    let mut flags = Vec::new();
    let mut inside = false;
    for line in text.lines() {
        if line.starts_with("#include <...>") {
            inside = true;
            continue;
        }
        if line.starts_with("End of search list") {
            break;
        }
        if inside && line.starts_with(' ') {
            let path = line.trim();
            // A framework directory is a macOS thing that no C include ever resolves through.
            if path.ends_with("(framework directory)") {
                continue;
            }
            flags.push("-isystem".to_owned());
            flags.push(path.to_owned());
        }
    }
    flags
}

/// Works out everything a corpus asks to be preprocessed.
///
/// Header units get a file of one line each, written into `scratch`, because a header set is
/// checked by including each header on its own and that is also how a user finds out that one
/// of them does not stand up on its own.
///
/// # Errors
///
/// When the tree is missing, or a unit names a directory that is not there.
pub fn cases(repo: &Path, corpus: &Corpus, scratch: &Path) -> Result<Vec<Case>, Error> {
    let tree = corpus.tree(repo);
    if !tree.is_dir() {
        return Err(Error {
            message: format!(
                "{}: `{}` is not there, run `fetch` first",
                corpus.name,
                tree.display()
            ),
        });
    }
    fs::create_dir_all(scratch)
        .map_err(|e| Error { message: format!("{}: {e}", scratch.display()) })?;
    let mut cases = Vec::new();
    for unit in &corpus.units {
        match unit.kind {
            UnitKind::Source => sources(&tree, unit, &mut cases)?,
            UnitKind::Headers => headers(&tree, unit, scratch, &mut cases)?,
        }
    }
    cases.sort_by(|a, b| a.name.cmp(&b.name));
    Ok(cases)
}

fn sources(tree: &Path, unit: &Unit, cases: &mut Vec<Case>) -> Result<(), Error> {
    let flags = absolute(&unit.flags, tree);
    // A file the manifest lists is named from the tree, and a file found by walking is named
    // from the directory the unit already names, so that a case is called `single-exec/00001.c`
    // rather than repeating the directory in the name of every one of two hundred cases.
    let mut found: Vec<(String, PathBuf)> =
        unit.files.iter().map(|file| (file.clone(), tree.join(file))).collect();
    // A unit that names a directory is walked for its `.c` files, so that a corpus of a few
    // hundred test programs is a manifest of five lines rather than a list nobody updates
    // when the upstream version moves.
    if let Some(dir) = &unit.dir {
        let root = resolve(dir, tree);
        let mut walked = Vec::new();
        walk(&root, &root, &unit.skip, ".c", &mut walked)?;
        walked.sort();
        found.extend(walked.into_iter().map(|name| {
            let path = root.join(&name);
            (name, path)
        }));
    }
    for (name, file) in found {
        cases.push(Case {
            unit: unit.name.clone(),
            name: format!("{}/{name}", unit.name),
            file,
            dir: tree.to_path_buf(),
            flags: flags.clone(),
        });
    }
    Ok(())
}

fn headers(tree: &Path, unit: &Unit, scratch: &Path, cases: &mut Vec<Case>) -> Result<(), Error> {
    let flags = absolute(&unit.flags, tree);
    let mut names = unit.files.clone();
    if let Some(dir) = &unit.dir {
        let root = resolve(dir, tree);
        let mut found = Vec::new();
        walk(&root, &root, &unit.skip, ".h", &mut found)?;
        found.sort();
        names.extend(found);
    }
    for name in names {
        let stub = scratch.join(format!("{}_{}.c", unit.name, name.replace(['/', '.', '-'], "_")));
        fs::write(&stub, format!("#include <{name}>\n"))
            .map_err(|e| Error { message: format!("{}: {e}", stub.display()) })?;
        cases.push(Case {
            unit: unit.name.clone(),
            name: format!("{}/{name}", unit.name),
            file: stub,
            dir: scratch.to_path_buf(),
            flags: flags.clone(),
        });
    }
    Ok(())
}

/// Every file under `root` whose name ends in `ext`, named relative to `root`.
fn walk(
    root: &Path,
    dir: &Path,
    skip: &[String],
    ext: &str,
    found: &mut Vec<String>,
) -> Result<(), Error> {
    let listing =
        fs::read_dir(dir).map_err(|e| Error { message: format!("{}: {e}", dir.display()) })?;
    for entry in listing.flatten() {
        let path = entry.path();
        let Ok(relative) = path.strip_prefix(root) else { continue };
        // Forward slashes on every platform. This name is what an `#include` says, what a
        // `skip` in the manifest matches and what an exclusion names, and none of those three
        // should read differently depending on which machine ran the harness.
        let name = relative.to_string_lossy().replace('\\', "/");
        if skip.iter().any(|s| name == *s || name.starts_with(&format!("{s}/"))) {
            continue;
        }
        if path.is_dir() {
            walk(root, &path, skip, ext, found)?;
        } else if name.ends_with(ext) {
            found.push(name);
        }
    }
    Ok(())
}

/// Flags with their relative paths resolved against the tree, since the compilers run there
/// but a manifest is written relative to the tree it describes.
fn absolute(flags: &[String], tree: &Path) -> Vec<String> {
    let mut out = Vec::with_capacity(flags.len());
    let mut expecting = false;
    for flag in flags {
        if expecting {
            out.push(resolve(flag, tree).to_string_lossy().into_owned());
            expecting = false;
            continue;
        }
        match flag.as_str() {
            "-I" | "-isystem" | "-iquote" | "-idirafter" => {
                expecting = true;
                out.push(flag.clone());
            }
            _ => match flag.strip_prefix("-I") {
                Some(path) if !path.is_empty() => {
                    out.push(format!("-I{}", resolve(path, tree).display()));
                }
                _ => out.push(flag.clone()),
            },
        }
    }
    out
}

fn resolve(path: &str, tree: &Path) -> PathBuf {
    let path = Path::new(path);
    if path.is_absolute() { path.to_path_buf() } else { tree.join(path) }
}

/// The report, as the markdown that lands in `results/`.
#[must_use]
pub fn markdown(report: &Report, settings: &Settings, register: &Register) -> String {
    let mut out = String::new();
    let _ = writeln!(out, "# {}\n", report.corpus);
    let _ = writeln!(out, "{}\n", report.summary());
    let _ = writeln!(
        out,
        "Reference: `{}`. Under test: `{}`. Markers compared: {}.\n",
        settings.cc.display(),
        settings.rucc.display(),
        if settings.markers { "yes" } else { "no" }
    );
    let failures: Vec<&Outcome> = report.outcomes.iter().filter(|o| o.is_failure()).collect();
    if failures.is_empty() {
        let _ = writeln!(out, "Nothing failing.\n");
    } else {
        let _ = writeln!(out, "## Failing\n");
        for outcome in failures {
            let _ = writeln!(out, "### {} ({})\n", outcome.case, outcome.status.word());
            match &outcome.status {
                Status::Text(d) | Status::Spacing(d) | Status::Markers(d) => {
                    let _ = writeln!(out, "Line {} of the normalized output.\n", d.line);
                    let _ = writeln!(out, "```");
                    let _ = writeln!(out, "rucc: {}", d.ours);
                    let _ = writeln!(out, "cc:   {}", d.theirs);
                    let _ = writeln!(out, "```\n");
                }
                Status::Failed(why) => {
                    let _ = writeln!(out, "```\n{why}\n```\n");
                }
                Status::Same | Status::Unsupported(_) => {}
            }
        }
    }
    let accepted: Vec<&Outcome> = report.outcomes.iter().filter(|o| o.accepted.is_some()).collect();
    if !accepted.is_empty() {
        let _ = writeln!(out, "## Accepted\n");
        let _ =
            writeln!(out, "Differences the register covers, each waiting on the issue it names.\n");
        // Grouped by entry rather than listed by case, so that the reason and the issue are
        // written once and the list underneath is the evidence for how much the entry is
        // holding up. An entry covering a hundred cases is a different thing from one
        // covering one, and a flat list hides which it is.
        let mut ids: Vec<&str> = Vec::new();
        for id in accepted.iter().filter_map(|o| o.accepted.as_deref()) {
            if !ids.contains(&id) {
                ids.push(id);
            }
        }
        for id in ids {
            let _ = writeln!(out, "### {id}\n");
            if let Some(entry) = register.entries.iter().find(|d| d.id == id) {
                let _ = writeln!(out, "{} {} Waiting on {}.\n", entry.what, entry.why, entry.issue);
            }
            for outcome in accepted.iter().filter(|o| o.accepted.as_deref() == Some(id)) {
                let _ = writeln!(out, "- {} ({})", outcome.case, outcome.status.word());
            }
            let _ = writeln!(out);
        }
    }
    let unsupported: Vec<&Outcome> =
        report.outcomes.iter().filter(|o| matches!(o.status, Status::Unsupported(_))).collect();
    if !unsupported.is_empty() {
        let _ = writeln!(out, "## Not compared\n");
        let _ = writeln!(
            out,
            "The reference could not preprocess these either, so there is nothing to compare. Normally a header that is not meant to be included on its own.\n"
        );
        for outcome in unsupported {
            let _ = writeln!(out, "- {}", outcome.case);
        }
        let _ = writeln!(out);
    }
    out
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn the_version_the_reference_claims_is_read_out_of_its_own_dump() {
        // Real lines from `gcc -dM -E -x c /dev/null`, in the order and among the noise they
        // actually come in, because the point of reading them is that we did not write them.
        let dump = "\
#define __SIZEOF_INT__ 4
#define __GNUC_MINOR__ 3
#define __GNUC_PATCHLEVEL__ 0
#define __GNUC_STDC_INLINE__ 1
#define __GNUC__ 13
#define __GNUC_EXECUTION_CHARSET_NAME \"UTF-8\"
";
        assert_eq!(Dump::read(dump).gnuc_version().as_deref(), Some("13.3.0"));
    }

    #[test]
    fn a_reference_that_is_not_pretending_to_be_gcc_is_left_alone() {
        // No `__GNUC__` means no claim to copy, and inventing one would be us deciding what
        // the headers should see rather than matching what they already saw.
        assert_eq!(Dump::read("#define __SIZEOF_INT__ 4\n").gnuc_version(), None);
        // A claim with nothing after it is still a claim, and the rest is zero.
        assert_eq!(Dump::read("#define __GNUC__ 15\n").gnuc_version().as_deref(), Some("15.0.0"));
    }

    #[test]
    fn the_dialect_is_read_off_the_reference_because_no_two_compilers_default_the_same_way() {
        // GCC 13 defaults to gnu17 and rucc defaults to gnu23, and that difference alone gives
        // us `nullptr_t` out of stddef.h and `char8_t` out of uchar.h that the reference never
        // sees. The year and the extensions are two separate axes and both have to match.
        let std = |text: &str| Dump::read(text).std();
        assert_eq!(std("#define __STDC_VERSION__ 201710L\n").as_deref(), Some("gnu17"));
        assert_eq!(
            std("#define __STDC_VERSION__ 201710L\n#define __STRICT_ANSI__ 1\n").as_deref(),
            Some("c17")
        );
        assert_eq!(std("#define __STDC_VERSION__ 202311L\n").as_deref(), Some("gnu23"));
        // C89 never defined the macro, so its absence is an answer rather than a gap.
        assert_eq!(std("#define __GNUC__ 13\n").as_deref(), Some("gnu89"));
        // A year we have no spelling for leaves our default alone. That is wrong, and it shows
        // up in the report as a difference, which beats asking for the wrong language.
        assert_eq!(std("#define __STDC_VERSION__ 202900L\n"), None);
    }

    #[test]
    fn markers_and_blank_lines_are_not_part_of_the_token_text() {
        let a = normalize("# 1 \"a.c\"\nint x;\n\n");
        let b = normalize("int  x ;\n");
        assert_eq!(a.text, b.text);
        assert_eq!(a.markers.len(), 1);
        assert!(b.markers.is_empty());
    }

    #[test]
    fn a_run_of_spaces_is_the_same_tokens_and_a_missing_space_is_not() {
        let a = normalize("int  x;\n");
        let b = normalize("int x;\n");
        let c = normalize("intx;\n");
        assert_eq!(a.text, b.text);
        assert_eq!(a.spacing, b.spacing);
        assert_ne!(a.text, c.text);
    }

    #[test]
    fn a_line_break_in_a_different_place_is_the_same_tokens_and_different_spacing() {
        let a = normalize("int x;\nint y;\n");
        let b = normalize("int x; int y;\n");
        assert_eq!(a.text, b.text);
        assert_ne!(a.spacing, b.spacing);
    }

    #[test]
    fn the_preamble_markers_are_dropped_because_the_two_disagree_on_emitting_them() {
        let ours = normalize("# 1 \"a.c\"\nint x;\n");
        let theirs = normalize(
            "# 1 \"a.c\"\n# 1 \"<built-in>\"\n# 1 \"<command-line>\"\n# 1 \"a.c\"\nint x;\n",
        );
        assert_eq!(ours.markers, theirs.markers[..1]);
    }

    #[test]
    fn a_failure_reports_the_diagnostics_rather_than_the_include_chain() {
        let stderr = "In file included from a.c:1:\n                 from b.h:2:\nb.h:9:8: error: no\nb.h:10:1: error: and then this\n";
        assert_eq!(why(stderr), "b.h:9:8: error: no\nb.h:10:1: error: and then this");
        assert_eq!(why(""), "exited with a failure and said nothing");
        assert_eq!(why("killed\n"), "killed");
    }

    #[test]
    fn a_hash_that_is_not_a_marker_is_not_a_marker() {
        assert!(is_marker("# 1 \"a.c\""));
        assert!(is_marker("#42"));
        assert!(!is_marker("#pragma once"));
        assert!(!is_marker("int x;"));
    }

    #[test]
    fn the_difference_is_the_first_line_they_disagree_on() {
        let ours = normalize("int a;\nint b;\nint c;\n");
        let theirs = normalize("int a;\nint z;\nint c;\n");
        let diff = first_difference(&ours, &theirs, By::Tokens);
        assert_eq!(diff.line, 2);
        assert_eq!(diff.ours, "int b;");
        assert_eq!(diff.theirs, "int z;");
    }

    #[test]
    fn one_output_running_out_early_is_a_difference_at_the_end() {
        let ours = normalize("int a;\n");
        let theirs = normalize("int a;\nint b;\n");
        let diff = first_difference(&ours, &theirs, By::Tokens);
        assert_eq!(diff.line, 2);
        assert_eq!(diff.ours, "<end of output>");
    }

    #[test]
    fn a_token_difference_points_at_the_tokens_and_not_at_an_earlier_spacing_difference() {
        // Both files say the same thing on line one and spell it differently, and differ in
        // tokens on line two. Searching the collapsed lines would stop at line one and report
        // a missing space as though it were the bug, which is what the glibc report was doing.
        let ours = normalize("int a ;\nint b;\n");
        let theirs = normalize("int a;\nint z;\n");
        let diff = first_difference(&ours, &theirs, By::Tokens);
        assert_eq!(diff.line, 2);
        assert_eq!(diff.ours, "int b;");

        // The spacing rule still stops at line one, because for that rule line one is the bug.
        let diff = first_difference(&ours, &theirs, By::Spacing);
        assert_eq!(diff.line, 1);
    }

    #[test]
    fn include_paths_in_flags_are_resolved_against_the_tree() {
        let tree = Path::new("/vendor/t");
        let flags =
            vec!["-I".to_owned(), "include".to_owned(), "-Isrc".to_owned(), "-DA=1".to_owned()];
        // Built with `join` rather than written out, because the separator is a backslash on
        // Windows and the point of the test is the resolving, not the spelling.
        let expected = [
            "-I".to_owned(),
            tree.join("include").display().to_string(),
            format!("-I{}", tree.join("src").display()),
            "-DA=1".to_owned(),
        ];
        assert_eq!(absolute(&flags, tree), expected);
    }

    #[test]
    fn a_source_unit_that_names_a_directory_is_walked_for_its_c_files() {
        let root = std::env::temp_dir().join(format!("rucc-compat-walk-{}", std::process::id()));
        let _ = fs::remove_dir_all(&root);
        fs::create_dir_all(root.join("tests/deep")).unwrap();
        fs::write(root.join("tests/b.c"), "").unwrap();
        fs::write(root.join("tests/a.c"), "").unwrap();
        fs::write(root.join("tests/a.h"), "").unwrap();
        fs::write(root.join("tests/skipped.c"), "").unwrap();
        fs::write(root.join("tests/deep/c.c"), "").unwrap();
        let unit = Unit {
            name: "suite".to_owned(),
            kind: UnitKind::Source,
            files: Vec::new(),
            dir: Some("tests".to_owned()),
            skip: vec!["skipped.c".to_owned()],
            flags: Vec::new(),
            link: Vec::new(),
        };
        let mut cases = Vec::new();
        sources(&root, &unit, &mut cases).unwrap();
        let names: Vec<&str> = cases.iter().map(|c| c.name.as_str()).collect();
        // The header is not a case, the skip took one out, and a case is named from the
        // directory the unit already named rather than repeating it.
        assert_eq!(names, ["suite/a.c", "suite/b.c", "suite/deep/c.c"]);
        // The compilers still run in the tree, so a relative include in the corpus resolves
        // the way it would in a real build of it.
        assert_eq!(cases[0].dir, root);
        assert_eq!(cases[0].file, root.join("tests/a.c"));
        let _ = fs::remove_dir_all(&root);
    }

    #[test]
    fn a_relative_program_is_made_absolute_and_a_bare_name_is_not() {
        assert_eq!(program(Path::new("cc")), Path::new("cc"));
        assert!(program(Path::new("target/release/rucc")).is_absolute());
        // Built rather than written out. A path that begins with a slash is absolute on Unix
        // and is only rooted on Windows, where it still resolves against the current drive,
        // so a literal one tests the platform rather than this function.
        let already = std::env::current_dir().unwrap().join("cc");
        assert_eq!(program(&already), already);
    }

    #[test]
    fn a_status_maps_to_the_rule_the_register_can_suppress() {
        let diff = Diff { line: 1, ours: String::new(), theirs: String::new() };
        assert_eq!(Status::Text(diff.clone()).rule(), Some(rule::TEXT));
        assert_eq!(Status::Same.rule(), None);
        assert_eq!(Status::Failed(String::new()).rule(), None);
    }

    #[test]
    fn an_accepted_difference_is_not_a_failure_and_a_failure_to_run_always_is() {
        let diff = Diff { line: 1, ours: String::new(), theirs: String::new() };
        let accepted = Outcome {
            case: "a".to_owned(),
            status: Status::Spacing(diff.clone()),
            accepted: Some("spacing-known".to_owned()),
        };
        assert!(!accepted.is_failure());
        let failed = Outcome {
            case: "a".to_owned(),
            status: Status::Failed("no".to_owned()),
            accepted: None,
        };
        assert!(failed.is_failure());
        let unsupported = Outcome {
            case: "a".to_owned(),
            status: Status::Unsupported("no".to_owned()),
            accepted: None,
        };
        assert!(!unsupported.is_failure());
    }

    #[test]
    fn the_report_counts_what_it_says_it_counts() {
        let diff = Diff { line: 3, ours: "a".to_owned(), theirs: "b".to_owned() };
        let report = Report {
            corpus: "t".to_owned(),
            outcomes: vec![
                Outcome { case: "a.h".to_owned(), status: Status::Same, accepted: None },
                Outcome { case: "b.h".to_owned(), status: Status::Text(diff), accepted: None },
                Outcome {
                    case: "c.h".to_owned(),
                    status: Status::Unsupported("x".to_owned()),
                    accepted: None,
                },
            ],
        };
        assert_eq!(report.count("same"), 1);
        assert_eq!(report.failures(), 1);
        let text = markdown(&report, &Settings::default(), &Register::default());
        assert!(text.contains("### b.h (tokens)"), "{text}");
        assert!(text.contains("Line 3"), "{text}");
        assert!(text.contains("- c.h"), "{text}");
    }
}
