//! Csmith against the reference: generate a program from each seed, build it with both compilers
//! at one level, run both, and say whether they agree.
//!
//! The corpora in this repository are programs somebody wrote, which is their strength and their
//! limit. They cover what their authors thought of. A Csmith program is written by nobody: it is
//! a few thousand lines of arithmetic over every integer type, through pointers, bitfields,
//! packed structures, unions, globals and volatiles, printed as one checksum at the end, and
//! free of undefined behaviour by construction. Two compilers that agree on ten thousand of them
//! agree on a great deal of C that no test suite thought to write down.
//!
//! # What makes it the same run everywhere
//!
//! The seeds are in `corpus/csmith/seeds.txt`, along with the version of Csmith that turns them
//! into programs. Csmith is a pure function of its seed and its version, so the list is the whole
//! of the input: two machines with the same Csmith and the same list run the same programs, and a
//! seed that disagrees today and agreed last week is a regression somebody can bisect. A Csmith
//! of another version makes other programs from the same seeds, which is still a fine test but is
//! not the same run, so it is said out loud rather than refused.
//!
//! # What counts against the compiler
//!
//! A seed whose program the reference cannot build or run to the end is not news about rucc.
//! Csmith's programs are free of undefined behaviour but not of long loops, and a program that
//! runs past the time is one with no answer to compare against, so it is counted apart and not
//! held against anybody. Everything else is: a program rucc refuses to build, a compiler that
//! crashes, and a program rucc built that ends differently or prints a different checksum.
//!
//! # Reduction
//!
//! A disagreement in a five thousand line program is not something a person can read, so with
//! `--reduce` each one is handed to C-Vise (or C-Reduce, which takes the same arguments) with a
//! test that keeps it the same failure, and the file that comes out goes under
//! `results/csmith/`. The test for a wrong answer builds the reference a second time under
//! AddressSanitizer and UndefinedBehaviorSanitizer and asks it for the same answer, and asks gcc
//! for warnings about reading something never written, because a reducer left to itself will
//! happily cut a program down to one that reads an uninitialised variable, and then the two
//! compilers are both right and the file is noise.

use std::fs;
use std::io::Write as _;
use std::path::{Path, PathBuf};
use std::process::Command;
use std::time::Duration;

use crate::sandbox::{self, End, Limits};
use crate::work;

/// What the command was asked to do.
#[derive(Debug, Clone)]
pub struct Settings {
    /// The compiler under test.
    pub rucc: PathBuf,
    /// The reference.
    pub cc: PathBuf,
    /// Csmith itself.
    pub csmith: PathBuf,
    /// Where `csmith.h` is, when it is not beside the binary.
    pub include: Option<PathBuf>,
    /// The level both compilers are given after `-O`.
    pub opt: String,
    /// How many seeds at once, or half the machine.
    pub jobs: Option<usize>,
    /// Only the first this many seeds of the list.
    pub limit: Option<usize>,
    /// Only these seeds, which need not be in the list.
    pub only: Vec<u64>,
    /// Reduce each failure and write it under `results/csmith/`.
    pub reduce: bool,
    /// The reducer, `cvise` unless told otherwise.
    pub reducer: PathBuf,
}

impl Default for Settings {
    fn default() -> Settings {
        Settings {
            rucc: PathBuf::from("rucc"),
            cc: PathBuf::from("cc"),
            csmith: PathBuf::from("csmith"),
            include: None,
            opt: "0".to_owned(),
            jobs: None,
            limit: None,
            only: Vec::new(),
            reduce: false,
            reducer: PathBuf::from("cvise"),
        }
    }
}

/// The checked in list: the Csmith it was written for, and the seeds.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Seeds {
    /// The version line, `csmith 2.4.0 0cdc710`, which is what `csmith --version` says folded
    /// onto one line.
    pub version: String,
    /// The seeds, in the order they are run.
    pub seeds: Vec<u64>,
}

/// Where the list is, relative to the root of the repository.
pub const SEEDS: &str = "corpus/csmith/seeds.txt";

/// Reads the list. A line starting with `#` is a comment, the first other line is the version,
/// and every line after it is one seed.
///
/// # Errors
///
/// When the file is unreadable, has no version line, or has a line that is not a number.
pub fn parse(text: &str) -> Result<Seeds, String> {
    let mut lines = text.lines().map(str::trim).filter(|l| !l.is_empty() && !l.starts_with('#'));
    let version = lines.next().ok_or("the seed list has no version line")?.to_owned();
    if !version.starts_with("csmith ") {
        return Err(format!("the first line of the seed list is `{version}`, not a version"));
    }
    let mut seeds = Vec::new();
    for line in lines {
        let seed = line.parse().map_err(|_| format!("`{line}` in the seed list is not a seed"))?;
        seeds.push(seed);
    }
    Ok(Seeds { version, seeds })
}

/// The version line of the Csmith that will be run, in the form [`Seeds::version`] has.
///
/// # Errors
///
/// When Csmith cannot be run.
pub fn version_of(csmith: &Path) -> Result<String, String> {
    let out = Command::new(csmith)
        .arg("--version")
        .output()
        .map_err(|e| format!("could not run {}: {e}", csmith.display()))?;
    let text = String::from_utf8_lossy(&out.stdout);
    let mut words: Vec<&str> = Vec::new();
    for line in text.lines() {
        // `csmith 2.4.0` and then `Git version: 0cdc710`, of which only the hash is worth keeping.
        match line.strip_prefix("Git version:") {
            Some(hash) => words.push(hash.trim()),
            None => words.extend(line.split_whitespace()),
        }
    }
    Ok(words.join(" "))
}

/// Where `csmith.h` is: the directory given, or `include` beside the directory the binary is
/// in, which is where `cmake --install` puts it. Older releases put it one level further down,
/// in `include/csmith-2.3.0`, so that is looked for as well.
///
/// # Errors
///
/// When it is in neither place.
pub fn include_dir(settings: &Settings) -> Result<PathBuf, String> {
    if let Some(dir) = &settings.include {
        return Ok(dir.clone());
    }
    let binary = which(&settings.csmith)
        .ok_or_else(|| format!("{} is not on the path", settings.csmith.display()))?;
    let root = binary.parent().and_then(Path::parent).map(|p| p.join("include"));
    let Some(root) = root else {
        return Err(format!("{} has no directory above it", binary.display()));
    };
    if root.join("csmith.h").is_file() {
        return Ok(root);
    }
    let found = fs::read_dir(&root).ok().and_then(|listing| {
        listing.flatten().map(|e| e.path()).find(|p| p.join("csmith.h").is_file())
    });
    found.ok_or_else(|| {
        format!("no csmith.h under {}, so say where it is with --include", root.display())
    })
}

/// The file a bare program name would run, which is the binary itself for a path.
fn which(program: &Path) -> Option<PathBuf> {
    if program.components().count() > 1 {
        return Some(program.to_path_buf());
    }
    let path = std::env::var_os("PATH")?;
    std::env::split_paths(&path).map(|dir| dir.join(program)).find(|p| p.is_file())
}

/// How one seed came out.
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum Outcome {
    /// Both programs printed the same and ended the same way.
    Agree,
    /// There is nothing to compare against: Csmith made no program, or the reference could not
    /// build it or run it to the end.
    NoAnswer(String),
    /// rucc did not build it, either by refusing it or by crashing.
    Refused(String),
    /// The program rucc built ended differently or printed something else.
    Wrong(String),
}

impl Outcome {
    /// Whether this one counts against the compiler.
    #[must_use]
    pub fn failed(&self) -> bool {
        matches!(self, Outcome::Refused(_) | Outcome::Wrong(_))
    }

    /// The word the summary counts it under.
    #[must_use]
    pub fn bucket(&self) -> &'static str {
        match self {
            Outcome::Agree => "agree",
            Outcome::NoAnswer(_) => "no answer from the reference",
            Outcome::Refused(_) => "rucc did not build",
            Outcome::Wrong(_) => "wrong answer",
        }
    }

    fn detail(&self) -> &str {
        match self {
            Outcome::Agree => "",
            Outcome::NoAnswer(said) | Outcome::Refused(said) | Outcome::Wrong(said) => said,
        }
    }
}

/// One seed and what became of it.
#[derive(Debug, Clone)]
pub struct Case {
    /// The seed.
    pub seed: u64,
    /// What happened.
    pub outcome: Outcome,
    /// The reduced file, when one was asked for and the reducer got somewhere.
    pub reduced: Option<PathBuf>,
}

/// Every seed's case, in the order of the list.
#[derive(Debug, Clone)]
pub struct Done {
    /// The cases.
    pub cases: Vec<Case>,
    /// The level they were built at.
    pub opt: String,
}

impl Done {
    /// How many count against the compiler.
    #[must_use]
    pub fn failures(&self) -> usize {
        self.cases.iter().filter(|c| c.outcome.failed()).count()
    }

    /// One line saying how it went.
    #[must_use]
    pub fn summary(&self) -> String {
        let count =
            |bucket: &str| self.cases.iter().filter(|c| c.outcome.bucket() == bucket).count();
        format!(
            "csmith at -O{}: {} seeds, {} agree, {} wrong, {} not built by rucc, {} with no answer \
             from the reference",
            self.opt,
            self.cases.len(),
            count("agree"),
            count("wrong answer"),
            count("rucc did not build"),
            count("no answer from the reference"),
        )
    }

    /// The report written under `results/`.
    #[must_use]
    pub fn markdown(&self, version: &str) -> String {
        let mut out = String::new();
        out.push_str("# Csmith\n\n");
        out.push_str(&format!(
            "The seeds in `{SEEDS}`, made into programs by {version}, built by rucc and by the \
             reference at `-O{}`, run, and compared.\n\n",
            self.opt
        ));
        out.push_str(&format!("{}\n", self.summary()));
        let failed: Vec<&Case> = self.cases.iter().filter(|c| c.outcome.failed()).collect();
        if !failed.is_empty() {
            out.push_str("\n| seed | what | detail | reduced |\n|---|---|---|---|\n");
            for case in failed {
                let reduced = case
                    .reduced
                    .as_ref()
                    .and_then(|p| p.file_name())
                    .map_or(String::new(), |n| format!("`{}`", n.to_string_lossy()));
                out.push_str(&format!(
                    "| {} | {} | {} | {reduced} |\n",
                    case.seed,
                    case.outcome.bucket(),
                    case.outcome.detail().replace('|', "\\|"),
                ));
            }
        }
        out
    }
}

/// How long Csmith gets to write a program, which it nearly always does in well under a second.
const GENERATE: Duration = Duration::from_secs(30);
/// How long either compiler gets to build one.
const BUILD: Duration = Duration::from_secs(120);
/// How long the reference's program gets to run. Csmith's programs that finish at all mostly
/// finish in a fraction of a second, and the rest are the ones with no answer.
const RUN: Duration = Duration::from_secs(10);
/// How long rucc's program gets, which is twice the reference's so that a program that is only
/// slower is not reported as a wrong answer.
const RUN_RUCC: Duration = Duration::from_secs(20);

/// Runs every seed.
///
/// # Errors
///
/// When the scratch directory cannot be made, or `csmith.h` cannot be found.
pub fn run(seeds: &[u64], settings: &Settings, scratch: &Path) -> Result<Done, String> {
    let include = include_dir(settings)?;
    fs::create_dir_all(scratch).map_err(|e| format!("{}: {e}", scratch.display()))?;
    let jobs = work::jobs(settings.jobs);
    let cases = work::spread(seeds, jobs, |&seed| {
        let dir = scratch.join(seed.to_string());
        let outcome = one(seed, settings, &include, &dir);
        // Said as it happens as well as in the summary, because ten thousand seeds is most of a
        // working day and a failure in the first hour is worth knowing about in the first hour.
        if outcome.failed() {
            println!("  seed {seed}: {}", outcome.bucket());
        }
        // A seed that agreed has nothing anyone will look at, and ten thousand of them is a lot
        // of disk. One that failed keeps its directory, which is where the reducer starts.
        if !outcome.failed() {
            let _ = fs::remove_dir_all(&dir);
        }
        Case { seed, outcome, reduced: None }
    });
    Ok(Done { cases, opt: settings.opt.clone() })
}

/// One seed, in its own directory.
fn one(seed: u64, settings: &Settings, include: &Path, dir: &Path) -> Outcome {
    if let Err(e) = fs::create_dir_all(dir) {
        return Outcome::NoAnswer(format!("{}: {e}", dir.display()));
    }
    let limits = |timeout| Limits { timeout, memory: None };
    let seed_text = seed.to_string();
    let made = sandbox::run(
        &settings.csmith,
        &["--seed", &seed_text, "-o", "p.c"],
        dir,
        &limits(GENERATE),
    );
    match made {
        Ok(ran) if ran.end.is_clean() => {}
        Ok(ran) => return Outcome::NoAnswer(format!("csmith made no program, {}", ran.end.said())),
        Err(e) => return Outcome::NoAnswer(e),
    }
    let level = format!("-O{}", settings.opt);
    let inc = format!("-I{}", include.display());
    let build = |compiler: &Path, out: &str| {
        sandbox::run(compiler, &[level.as_str(), "-w", &inc, "p.c", "-o", out], dir, &limits(BUILD))
    };
    match build(&settings.cc, "g") {
        Ok(ran) if ran.end.is_clean() => {}
        Ok(ran) => {
            return Outcome::NoAnswer(format!(
                "the reference did not build it: {}",
                ran.complaint()
            ));
        }
        Err(e) => return Outcome::NoAnswer(e),
    }
    let expected = match sandbox::run(&dir.join("g"), &[] as &[&str], dir, &limits(RUN)) {
        Ok(ran) if ran.end.is_clean() => ran,
        Ok(ran) => {
            return Outcome::NoAnswer(format!("the reference's program: {}", ran.end.said()));
        }
        Err(e) => return Outcome::NoAnswer(e),
    };
    match build(&settings.rucc, "r") {
        Ok(ran) if ran.end.is_clean() => {}
        Ok(ran) => {
            let _ = fs::write(dir.join("rucc.err"), &ran.err);
            return Outcome::Refused(match ran.end {
                End::Exited(_) => ran.complaint(),
                ref end => format!("rucc ended with {}: {}", end.said(), ran.complaint()),
            });
        }
        Err(e) => return Outcome::Refused(e),
    }
    let got = match sandbox::run(&dir.join("r"), &[] as &[&str], dir, &limits(RUN_RUCC)) {
        Ok(ran) => ran,
        Err(e) => return Outcome::Wrong(e),
    };
    if got.end != expected.end {
        return Outcome::Wrong(format!(
            "the reference's program ended with {} and rucc's with {}",
            expected.end.said(),
            got.end.said()
        ));
    }
    if got.out != expected.out {
        return Outcome::Wrong(format!(
            "the reference printed `{}` and rucc `{}`",
            expected.text().trim(),
            got.text().trim()
        ));
    }
    Outcome::Agree
}

/// The `E` code of the first error rucc gave, which is what keeps a reduction the same refusal
/// rather than any refusal at all.
fn first_code(err: &str) -> Option<String> {
    let start = err.find("[E")?;
    let end = err[start..].find(']')?;
    Some(err[start + 1..start + end].to_owned())
}

/// What the file being reduced is called, which the test has to name since the reducer gives it
/// no arguments.
const WORKING: &str = "reduced.c";

/// The test the reducer runs, which says whether the file in hand is still the same failure. The
/// reducer runs it in an empty directory of its own holding only the file being reduced, so it
/// names that file and nothing else from the seed's directory.
fn interesting(case: &Case, settings: &Settings, include: &Path, dir: &Path) -> String {
    let cc = settings.cc.display();
    let rucc = settings.rucc.display();
    let inc = include.display();
    let opt = &settings.opt;
    let mut script = format!(
        "#!/bin/sh\n\
         # Written by rucc-compat csmith for seed {seed}: exits 0 while {WORKING} is still the failure.\n\
         ulimit -t 60\n\
         {cc} -O{opt} -w -I{inc} {WORKING} -o g >/dev/null 2>&1 || exit 1\n",
        seed = case.seed,
    );
    match &case.outcome {
        Outcome::Wrong(_) => {
            // The reference, again, with the sanitizers and with the warnings that a reducer's
            // favourite shortcut sets off, so that a file that only disagrees because it reads
            // something never written stops being the failure.
            script.push_str(&format!(
                "{cc} -O1 -c -o /dev/null -I{inc} -Werror=uninitialized -Werror=maybe-uninitialized \
                 -Werror=return-type -Werror=implicit-function-declaration -Werror=implicit-int \
                 -Werror=int-conversion -Werror=incompatible-pointer-types {WORKING} >/dev/null 2>&1 || exit 1\n\
                 {cc} -O{opt} -w -fsanitize=address,undefined -fno-sanitize-recover=all -I{inc} {WORKING} -o s \
                 >/dev/null 2>&1 || exit 1\n\
                 timeout 10 ./g >g.out 2>/dev/null; e=$?\n\
                 timeout 10 ./s >s.out 2>/dev/null; [ $? -eq $e ] || exit 1\n\
                 [ $e -ne 124 ] || exit 1\n\
                 cmp -s g.out s.out || exit 1\n\
                 {rucc} -O{opt} -w -I{inc} {WORKING} -o r >/dev/null 2>&1 || exit 1\n\
                 timeout 20 ./r >r.out 2>/dev/null; f=$?\n\
                 [ $f -ne $e ] && exit 0\n\
                 cmp -s g.out r.out && exit 1\n\
                 exit 0\n"
            ));
        }
        _ => {
            let err = fs::read_to_string(dir.join("rucc.err")).unwrap_or_default();
            let keep = first_code(&err)
                .or_else(|| err.contains("panicked").then(|| "panicked".to_owned()))
                .unwrap_or_else(|| "error".to_owned());
            script.push_str(&format!(
                "{rucc} -O{opt} -w -I{inc} {WORKING} -o r >r.err 2>&1 && exit 1\n\
                 grep -q -F -- '{keep}' r.err || exit 1\n\
                 exit 0\n"
            ));
        }
    }
    script
}

/// Reduces every failed case, writing what comes out under `out`.
///
/// # Errors
///
/// When `out` cannot be made. A reducer that fails on one case is said in that case and does not
/// stop the others.
pub fn reduce(
    done: &mut Done,
    settings: &Settings,
    scratch: &Path,
    out: &Path,
) -> Result<(), String> {
    let include = include_dir(settings)?;
    fs::create_dir_all(out).map_err(|e| format!("{}: {e}", out.display()))?;
    let jobs = work::jobs(settings.jobs).to_string();
    for case in done.cases.iter_mut().filter(|c| c.outcome.failed()) {
        let dir = scratch.join(case.seed.to_string());
        let test = dir.join("interesting.sh");
        let script = interesting(case, settings, &include, &dir);
        let written = fs::File::create(&test).and_then(|mut f| f.write_all(script.as_bytes()));
        if let Err(e) = written {
            eprintln!("seed {}: {}: {e}", case.seed, test.display());
            continue;
        }
        let _ = Command::new("chmod").arg("+x").arg(&test).status();
        let source = dir.join(WORKING);
        if let Err(e) = fs::copy(dir.join("p.c"), &source) {
            eprintln!("seed {}: {e}", case.seed);
            continue;
        }
        println!("  reducing seed {}, {}", case.seed, case.outcome.bucket());
        // What the reducer says goes beside the case rather than to the terminal: it is a great
        // deal of progress nobody needs while it works, and the one thing worth reading when it
        // gives up, which it does at once when the test fails on the file it started with.
        let log = dir.join("reduce.log");
        let status = fs::File::create(&log).and_then(|out| {
            let err = out.try_clone()?;
            Command::new(&settings.reducer)
                .args(["--n", &jobs])
                .arg(&test)
                // C-Vise refuses a file named with a directory in front of it, since it copies
                // the file by that name into a directory of its own, so it is named bare and
                // found from the directory the reducer starts in.
                .arg(WORKING)
                .current_dir(&dir)
                .stdout(out)
                .stderr(err)
                .status()
        });
        if !matches!(status, Ok(s) if s.success()) {
            eprintln!(
                "seed {}: {} gave up, see {}",
                case.seed,
                settings.reducer.display(),
                log.display()
            );
            continue;
        }
        let Ok(body) = fs::read_to_string(&source) else { continue };
        let path = out.join(format!("{}.c", case.seed));
        let header = format!(
            "/* Csmith seed {}, reduced. At -O{} the reference and rucc disagree: {}.\n   \
             The whole program again: csmith --seed {}. */\n",
            case.seed,
            settings.opt,
            case.outcome.detail(),
            case.seed
        );
        if fs::write(&path, header + &body).is_ok() {
            case.reduced = Some(path);
        }
    }
    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn the_seed_list_is_a_version_and_then_one_seed_a_line() {
        let list = parse("# comment\n\ncsmith 2.4.0 0cdc710\n1\n 2 \n# also a comment\n30\n")
            .expect("a list");
        assert_eq!(list.version, "csmith 2.4.0 0cdc710");
        assert_eq!(list.seeds, vec![1, 2, 30]);
    }

    #[test]
    fn a_seed_list_without_a_version_or_with_a_word_in_it_is_refused() {
        assert!(parse("1\n2\n").is_err());
        assert!(parse("csmith 2.4.0\n1\nfour\n").is_err());
    }

    #[test]
    fn the_first_error_code_is_what_a_refusal_is_reduced_against() {
        let err = "p.c:406:19: error: not supported yet [E0519]\np.c:9:1: error: [E0001]";
        assert_eq!(first_code(err), Some("E0519".to_owned()));
        assert_eq!(first_code("thread 'main' panicked at"), None);
    }

    #[test]
    fn the_reduction_test_names_only_the_file_being_reduced() {
        let settings = Settings::default();
        let dir = Path::new("/nonexistent");
        for outcome in [Outcome::Wrong(String::new()), Outcome::Refused(String::new())] {
            let case = Case { seed: 7, outcome, reduced: None };
            let script = interesting(&case, &settings, Path::new("/inc"), dir);
            assert!(script.contains(WORKING), "{script}");
            assert!(!script.contains("p.c"), "{script}");
        }
    }

    #[test]
    fn only_a_refusal_and_a_wrong_answer_count_against_the_compiler() {
        assert!(!Outcome::Agree.failed());
        assert!(!Outcome::NoAnswer(String::new()).failed());
        assert!(Outcome::Refused(String::new()).failed());
        assert!(Outcome::Wrong(String::new()).failed());
    }

    #[test]
    fn the_checked_in_list_reads() {
        let root = Path::new(env!("CARGO_MANIFEST_DIR")).join("../..");
        let text = fs::read_to_string(root.join(SEEDS)).expect("the seed list is checked in");
        let list = parse(&text).expect("the seed list reads");
        assert_eq!(list.seeds.len(), 10_000);
        let mut sorted = list.seeds.clone();
        sorted.sort_unstable();
        sorted.dedup();
        assert_eq!(sorted.len(), list.seeds.len(), "a seed is in the list twice");
    }
}
