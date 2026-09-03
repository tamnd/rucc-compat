//! Running a program under limits, and saying honestly how it ended.
//!
//! Design: `spec/20-execution-testing.md` section 20.6, in the compiler repository.
//!
//! The programs this runs are compiler test programs built by a compiler under development, so
//! a fair number of them are going to loop forever, allocate until the machine gives up, or
//! die on a fault. None of those is an error in the harness and all three have to be told
//! apart, which is what this module is for.
//!
//! The one distinction worth naming here is the last one. A program killed by `SIGSEGV` and a
//! program that returned 139 from `main` look identical to a shell, and they are opposite
//! events: the first is nearly always a miscompilation and the second is nearly always the
//! test doing what it was written to do. So the end of a run is [`End`] rather than a number.

use std::ffi::OsStr;
use std::path::Path;
use std::process::{Command, ExitStatus, Stdio};
use std::thread;
use std::time::{Duration, Instant};

/// How much a run is allowed to take.
#[derive(Debug, Clone)]
pub struct Limits {
    /// How long it gets before it is killed.
    pub timeout: Duration,
    /// How much address space it gets, in kibibytes, or `None` for no limit.
    ///
    /// `None` is also what a machine with no way to set one gets, and the report says so rather
    /// than printing a number that was never applied. See [`memory_limit`].
    pub memory: Option<u64>,
}

impl Default for Limits {
    fn default() -> Limits {
        Limits { timeout: Duration::from_secs(10), memory: None }
    }
}

/// How a run ended.
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum End {
    /// It returned this from `main`, or called `exit` with it.
    Exited(i32),
    /// A signal killed it, which on this side of the fence is nearly always a miscompilation.
    Signalled {
        /// The number, since the name is not known for all of them.
        number: i32,
        /// The name, or `signal` when this does not have one for it.
        name: &'static str,
    },
    /// Windows has no signals and reports a fault as the status of the exception that killed
    /// the process, which is the same event under a different name.
    Faulted(u32),
    /// It was still running when its time ran out and was killed.
    TimedOut,
}

impl End {
    /// Whether it got to the end and said everything was fine.
    #[must_use]
    pub fn is_clean(&self) -> bool {
        *self == End::Exited(0)
    }

    /// Whether it died rather than finished, which is the distinction the report keeps.
    #[must_use]
    pub fn is_crash(&self) -> bool {
        matches!(self, End::Signalled { .. } | End::Faulted(_))
    }

    /// One phrase, for a table.
    #[must_use]
    pub fn said(&self) -> String {
        match self {
            End::Exited(code) => format!("exit {code}"),
            End::Signalled { number, name } => format!("{name} ({number})"),
            End::Faulted(status) => format!("fault {status:#010x}"),
            End::TimedOut => "the time ran out".to_owned(),
        }
    }
}

/// What came of one run.
#[derive(Debug, Clone)]
pub struct Ran {
    /// How it ended.
    pub end: End,
    /// Everything it wrote to standard output, in full.
    ///
    /// In full because a difference in the ten thousandth line is still a difference. The
    /// report is where it gets cut down, and only there.
    pub out: Vec<u8>,
    /// Everything it wrote to standard error, which is captured and never compared.
    pub err: Vec<u8>,
}

impl Ran {
    /// Standard output as text, with anything that is not UTF-8 replaced rather than refused.
    ///
    /// A program that prints a byte no encoding claims is a program whose output is still worth
    /// comparing, and the comparison this feeds is against another run of the same program.
    #[must_use]
    pub fn text(&self) -> String {
        String::from_utf8_lossy(&self.out).into_owned()
    }

    /// What it said on standard error, cut to the first few lines, for a report.
    #[must_use]
    pub fn complaint(&self) -> String {
        let text = String::from_utf8_lossy(&self.err);
        let lines: Vec<&str> = text.lines().map(str::trim).filter(|l| !l.is_empty()).collect();
        match lines.is_empty() {
            true => "it said nothing".to_owned(),
            false => {
                let mut kept = lines;
                kept.truncate(3);
                kept.join("; ")
            }
        }
    }
}

/// Runs `program` in `dir`, waits for it under `limits`, and captures what it wrote.
///
/// # Errors
///
/// When the program could not be started at all, which is a fact about the harness or the
/// build rather than about the program, and is why it is an error here and an outcome above.
pub fn run<A: AsRef<OsStr>>(
    program: &Path,
    args: &[A],
    dir: &Path,
    limits: &Limits,
) -> Result<Ran, String> {
    let mut command = wrap(program, args, limits);
    command.current_dir(dir).stdin(Stdio::null()).stdout(Stdio::piped()).stderr(Stdio::piped());
    let mut child =
        command.spawn().map_err(|e| format!("could not run {}: {e}", program.display()))?;

    // Threads rather than reading the pipes here, because a program that fills the output pipe
    // while this waits for it to exit, and this waiting for it to exit before reading the pipe,
    // is a deadlock that shows up as a timeout on exactly the programs that print the most.
    let out = child.stdout.take().map(drain);
    let err = child.stderr.take().map(drain);

    let started = Instant::now();
    let mut nap = Duration::from_micros(200);
    let end = loop {
        match child.try_wait() {
            Err(e) => return Err(format!("could not wait for {}: {e}", program.display())),
            Ok(Some(status)) => break end_of(status),
            Ok(None) => {}
        }
        if started.elapsed() >= limits.timeout {
            let _ = child.kill();
            let _ = child.wait();
            break End::TimedOut;
        }
        thread::sleep(nap);
        // A program that ends immediately is noticed almost at once, and one that is going to
        // take its ten seconds is not asked ten thousand times whether it is done yet.
        nap = (nap * 2).min(Duration::from_millis(20));
    };

    let taken = |handle: Option<thread::JoinHandle<Vec<u8>>>| {
        handle.and_then(|h| h.join().ok()).unwrap_or_default()
    };
    Ok(Ran { end, out: taken(out), err: taken(err) })
}

/// A thread that reads one pipe to its end.
fn drain<R: std::io::Read + Send + 'static>(mut pipe: R) -> thread::JoinHandle<Vec<u8>> {
    thread::spawn(move || {
        let mut buffer = Vec::new();
        let _ = pipe.read_to_end(&mut buffer);
        buffer
    })
}

/// The command to spawn, which is the program itself unless a memory limit has to be put on it.
///
/// A limit on address space is a thing the shell sets and the standard library does not, so a
/// limited run goes through `sh`. The `exec` matters: it makes the program replace the shell
/// rather than run under it, so the process that is waited for is the program and a signal that
/// kills it is reported as a signal rather than as the 128 plus something a shell would return.
#[cfg(unix)]
fn wrap<A: AsRef<OsStr>>(program: &Path, args: &[A], limits: &Limits) -> Command {
    let Some(kib) = limits.memory else { return plain(program, args) };
    let mut command = Command::new("sh");
    command.arg("-c").arg(format!("ulimit -v {kib}; exec \"$0\" \"$@\"")).arg(program);
    command.args(args);
    command
}

#[cfg(not(unix))]
fn wrap<A: AsRef<OsStr>>(program: &Path, args: &[A], _limits: &Limits) -> Command {
    plain(program, args)
}

fn plain<A: AsRef<OsStr>>(program: &Path, args: &[A]) -> Command {
    let mut command = Command::new(program);
    command.args(args);
    command
}

#[cfg(unix)]
fn end_of(status: ExitStatus) -> End {
    use std::os::unix::process::ExitStatusExt as _;
    match status.signal() {
        Some(number) => End::Signalled { number, name: signal_name(number) },
        None => End::Exited(status.code().unwrap_or(-1)),
    }
}

#[cfg(not(unix))]
fn end_of(status: ExitStatus) -> End {
    let code = status.code().unwrap_or(-1);
    // Windows has no signals and kills a faulting process with the status of the exception that
    // killed it. Those all have the top two bits set, which is a range no program returns from
    // `main`, so a negative code here is the fault it looks like.
    match code < 0 {
        true => End::Faulted(code.cast_unsigned()),
        false => End::Exited(code),
    }
}

/// The name of a signal, or `signal` for one this does not know.
///
/// The list is the ones a miscompiled program actually dies on, rather than every number the
/// platform defines, because a name nobody recognises is no better than the number.
#[must_use]
pub fn signal_name(number: i32) -> &'static str {
    match number {
        1 => "SIGHUP",
        2 => "SIGINT",
        3 => "SIGQUIT",
        4 => "SIGILL",
        5 => "SIGTRAP",
        6 => "SIGABRT",
        7 => "SIGBUS",
        8 => "SIGFPE",
        9 => "SIGKILL",
        11 => "SIGSEGV",
        13 => "SIGPIPE",
        14 => "SIGALRM",
        15 => "SIGTERM",
        24 => "SIGXCPU",
        25 => "SIGXFSZ",
        _ => "signal",
    }
}

/// The memory limit this machine can actually apply, given the one that was wanted.
///
/// `None` when there is no way to set one here, which is a thing the report says out loud. A
/// macOS shell takes `ulimit -v` and does nothing with it, so asking the shell whether the
/// setting took is the only answer that is not a guess about the platform.
#[must_use]
pub fn memory_limit(kib: u64) -> Option<u64> {
    if cfg!(not(unix)) {
        return None;
    }
    let script = format!("ulimit -v {kib} 2>/dev/null && ulimit -v");
    let out = Command::new("sh").arg("-c").arg(script).output().ok()?;
    let said = String::from_utf8_lossy(&out.stdout);
    match said.trim().parse::<u64>() {
        Ok(got) if got == kib => Some(kib),
        _ => None,
    }
}

#[cfg(test)]
mod tests {
    use std::env;
    use std::fs;

    use super::*;

    fn here() -> std::path::PathBuf {
        env::temp_dir()
    }

    #[cfg(unix)]
    fn sh(script: &str, limits: &Limits) -> Ran {
        run(Path::new("/bin/sh"), &["-c", script], &here(), limits).expect("sh is on the machine")
    }

    #[test]
    #[cfg(unix)]
    fn a_program_that_finishes_is_reported_with_what_it_returned_and_what_it_printed() {
        let ran = sh("printf hello; printf oops 1>&2; exit 3", &Limits::default());
        assert_eq!(ran.end, End::Exited(3));
        assert_eq!(ran.text(), "hello");
        assert_eq!(ran.complaint(), "oops");
        assert!(!ran.end.is_clean());
        assert!(!ran.end.is_crash());
    }

    /// The distinction the whole module is written around, checked rather than asserted.
    #[test]
    #[cfg(unix)]
    fn a_signal_is_not_the_exit_status_that_looks_like_it() {
        let killed = sh("kill -SEGV $$", &Limits::default());
        assert_eq!(killed.end, End::Signalled { number: 11, name: "SIGSEGV" });
        assert!(killed.end.is_crash());

        let returned = sh("exit 139", &Limits::default());
        assert_eq!(returned.end, End::Exited(139));
        assert!(!returned.end.is_crash());

        assert_ne!(killed.end, returned.end);
    }

    #[test]
    #[cfg(unix)]
    fn a_program_that_does_not_stop_is_stopped_and_is_its_own_outcome() {
        let limits = Limits { timeout: Duration::from_millis(300), ..Limits::default() };
        let started = Instant::now();
        let ran = sh("while : ; do : ; done", &limits);
        assert_eq!(ran.end, End::TimedOut);
        assert!(!ran.end.is_crash(), "a program that ran too long is not a program that crashed");
        assert!(started.elapsed() < Duration::from_secs(5), "it was killed rather than waited for");
    }

    /// The reason the output is read on threads. A pipe holds sixty four kilobytes and then the
    /// writer blocks, so a program printing more than that deadlocks anything that waits for it
    /// to exit before reading, and it does so only on the programs that print the most.
    #[test]
    #[cfg(unix)]
    fn a_program_that_prints_more_than_a_pipe_holds_still_finishes() {
        let limits = Limits { timeout: Duration::from_secs(30), ..Limits::default() };
        let ran = sh(
            "i=0; while [ $i -lt 4000 ]; do echo 0123456789012345678901234567890123456789012345678901234567890123456789; i=$((i+1)); done",
            &limits,
        );
        assert_eq!(ran.end, End::Exited(0));
        assert_eq!(ran.out.len(), 4000 * 71);
    }

    #[test]
    #[cfg(unix)]
    fn the_run_happens_in_the_directory_it_was_given() {
        let dir = here().join(format!("rucc-compat-sandbox-{}", std::process::id()));
        let _ = fs::remove_dir_all(&dir);
        fs::create_dir_all(&dir).unwrap();
        let ran =
            run(Path::new("/bin/sh"), &["-c", "printf mine > made"], &dir, &Limits::default())
                .unwrap();
        assert_eq!(ran.end, End::Exited(0));
        assert_eq!(fs::read_to_string(dir.join("made")).unwrap(), "mine");
        let _ = fs::remove_dir_all(&dir);
    }

    #[test]
    fn a_program_that_is_not_there_is_the_harness_being_wrong_rather_than_an_outcome() {
        let missing = here().join("no-such-program-at-all");
        let e = run(&missing, &[] as &[&str], &here(), &Limits::default()).unwrap_err();
        assert!(e.contains("could not run"), "{e}");
    }

    #[test]
    fn a_memory_limit_is_reported_as_set_only_where_it_took() {
        // Whatever this answers, it answered it by asking the shell rather than by guessing from
        // the platform, and either answer is one the report can print without lying.
        let got = memory_limit(1_048_576);
        assert!(got.is_none() || got == Some(1_048_576));
    }

    #[test]
    #[cfg(unix)]
    fn a_run_under_a_memory_limit_is_still_the_program_and_not_the_shell_that_set_it() {
        let Some(kib) = memory_limit(1_048_576) else { return };
        let limits = Limits { memory: Some(kib), ..Limits::default() };
        // `exec` is what makes this the program's own signal rather than the 139 a shell would
        // return for a child of its own that died on one.
        assert_eq!(
            sh("kill -SEGV $$", &limits).end,
            End::Signalled { number: 11, name: "SIGSEGV" }
        );
        assert_eq!(sh("printf under", &limits).text(), "under");
    }

    #[test]
    fn an_unknown_signal_is_still_reported_with_its_number() {
        assert_eq!(signal_name(11), "SIGSEGV");
        assert_eq!(signal_name(60), "signal");
        let end = End::Signalled { number: 60, name: signal_name(60) };
        assert_eq!(end.said(), "signal (60)");
    }
}
