//! The command line: list the corpora, fetch one, run the differential, run the programs.

use std::fs;
use std::path::{Path, PathBuf};
use std::process::ExitCode;

use rucc_compat::corpus::{self, Corpus, Source};
use rucc_compat::coverage::{self, Marks};
use rucc_compat::differ::{self, Settings};
use rucc_compat::exec::{self, Route};
use rucc_compat::pipeline;
use rucc_compat::{fetch, repo_root};

const USAGE: &str = "\
rucc-compat, the compatibility harness for rucc

usage:
  rucc-compat list
  rucc-compat fetch [corpus...] [--record]
  rucc-compat run [corpus...] [options]
  rucc-compat check [corpus...] [options]
  rucc-compat exec [corpus...] [options]
  rucc-compat coverage [file or directory...] [--report]

commands:
  list             what corpora there are and whether they are ready to run
  fetch            download a vendored corpus, check its hash and unpack it
  run              preprocess with rucc and with cc and report the differences
  check            take a corpus through rucc alone: tast, ir, and the ir round trip
  exec             build the programs, run them, and say whether they were right
  coverage         union what exec recorded and say which lowering rules nothing fired

options:
  --rucc PATH      the compiler under test, or $RUCC, or `rucc`
  --cc PATH        run and exec: the reference compiler, or $CC, or `cc`
  --markers        run only: compare line markers as well as tokens
  --path NAME      exec only: build this way, one of assembly, object, driver, repeatable
  --opt LEVEL      exec only: the level to pass both compilers after -O
  --machine NAME   exec only: what to call this machine in the report
  --timeout N      exec only: seconds per run, over what the manifest asks for
  --rule-coverage FILE
                   exec only: ask which lowering rules fired and union it into FILE
  --unit NAME      run only the unit of that name
  --limit N        stop after N cases, for a quick look
  --jobs N         how many cases to have in the air at once, default half the machine
  --only PATTERN   run only cases whose name contains PATTERN, may be given more than once
  --failed         run only cases the last run here did not call green
  --report         write results/<corpus>.md as well as printing the summary
  --record         fetch only: print the sha256 of the download and unpack nothing

Naming no corpus means all of them. The exit status is 1 when anything failed.

`--failed` reads what the last run of the same command on this machine recorded under
`target/last`, and a narrowed run updates only the cases it reached, so asking twice in a row
asks about what the first one did not fix.

`check` and `exec` fail on an exclusion that no longer excludes anything, so that the list in
a manifest tracks work rather than hiding it.

`exec` runs a corpus only when its manifest names an oracle, since without one there is
nothing to decide a run by. A corpus with no oracle is reported as such and passed over.

`--rule-coverage` writes one file holding the union over every corpus the command ran, in the
format the compiler's own `-Zrule-coverage` writes, so that `coverage` can be given several of
them from several sweeps and union those in turn.
";

fn main() -> ExitCode {
    match run() {
        Ok(code) => code,
        Err(message) => {
            eprintln!("rucc-compat: {message}");
            ExitCode::from(2)
        }
    }
}

fn run() -> Result<ExitCode, String> {
    let args: Vec<String> = std::env::args().skip(1).collect();
    let Some(command) = args.first() else {
        print!("{USAGE}");
        return Ok(ExitCode::from(2));
    };
    if command == "--help" || command == "-h" || command == "help" {
        print!("{USAGE}");
        return Ok(ExitCode::SUCCESS);
    }
    let here = std::env::current_dir().map_err(|e| e.to_string())?;
    let repo = repo_root(&here)
        .ok_or("this is not inside a rucc-compat checkout, so there are no corpora to read")?;
    let all = corpus::load_all(&repo).map_err(|e| e.to_string())?;
    let rest = &args[1..];
    match command.as_str() {
        "list" => list(&repo, &all),
        "fetch" => fetch_them(&repo, &all, rest),
        "run" => run_them(&repo, &all, rest),
        "check" => check_them(&repo, &all, rest),
        "exec" => exec_them(&repo, &all, rest),
        "coverage" => coverage_of(&repo, rest),
        other => Err(format!("`{other}` is not a command, try --help")),
    }
}

fn list(repo: &Path, all: &[Corpus]) -> Result<ExitCode, String> {
    for corpus in all {
        let state = match &corpus.source {
            _ if !corpus.applies() => "not this machine".to_owned(),
            Source::Installed => "installed".to_owned(),
            Source::Tarball(t) if !t.is_recorded() => "hash unrecorded".to_owned(),
            Source::Tarball(t) if corpus.is_fetched(repo) => format!("vendored {}", t.version),
            Source::Tarball(t) => format!("not fetched, {}", t.version),
        };
        println!("{:<10} {:<20} {}", corpus.name, state, corpus.summary);
    }
    Ok(ExitCode::SUCCESS)
}

fn fetch_them(repo: &Path, all: &[Corpus], args: &[String]) -> Result<ExitCode, String> {
    let mut record = false;
    let mut names = Vec::new();
    for arg in args {
        match arg.as_str() {
            "--record" => record = true,
            other if other.starts_with('-') => {
                return Err(format!("`{other}` is not an option of fetch"));
            }
            other => names.push(other.to_owned()),
        }
    }
    let wanted = chosen(all, &names)?;
    let mut failed = false;
    for corpus in wanted {
        if corpus.source == Source::Installed {
            println!("{}: installed, nothing to fetch", corpus.name);
            continue;
        }
        match fetch::fetch(repo, corpus, record) {
            Ok(done) if record => println!("{}: sha256 {}", corpus.name, done.sha256),
            Ok(done) => {
                let tree = done.tree.unwrap_or_default();
                println!("{}: ready at {}", corpus.name, tree.display());
            }
            Err(e) => {
                eprintln!("{e}");
                failed = true;
            }
        }
    }
    Ok(if failed { ExitCode::FAILURE } else { ExitCode::SUCCESS })
}

fn run_them(repo: &Path, all: &[Corpus], args: &[String]) -> Result<ExitCode, String> {
    let mut settings = Settings {
        rucc: from_env("RUCC", "rucc"),
        cc: from_env("CC", "cc"),
        markers: false,
        limit: None,
        unit: None,
        only: Vec::new(),
        failed: false,
        jobs: None,
    };
    let mut report = false;
    let mut names = Vec::new();
    let mut at = 0;
    while at < args.len() {
        let arg = args[at].as_str();
        match arg {
            "--markers" => settings.markers = true,
            "--report" => report = true,
            "--rucc" => settings.rucc = PathBuf::from(value(args, &mut at, arg)?),
            "--cc" => settings.cc = PathBuf::from(value(args, &mut at, arg)?),
            "--unit" => settings.unit = Some(value(args, &mut at, arg)?),
            "--failed" => settings.failed = true,
            "--only" => settings.only.push(value(args, &mut at, arg)?),
            "--jobs" => {
                let text = value(args, &mut at, arg)?;
                let jobs = text.parse().map_err(|_| format!("`{text}` is not a number"))?;
                settings.jobs = Some(jobs);
            }
            "--limit" => {
                let text = value(args, &mut at, arg)?;
                let limit = text.parse().map_err(|_| format!("`{text}` is not a number"))?;
                settings.limit = Some(limit);
            }
            other if other.starts_with('-') => {
                return Err(format!("`{other}` is not an option of run"));
            }
            other => names.push(other.to_owned()),
        }
        at += 1;
    }
    let wanted = chosen(all, &names)?;
    let register = corpus::register(repo).map_err(|e| e.to_string())?;
    let scratch = repo.join("target").join("scratch");
    let mut failures = 0;
    for corpus in wanted {
        if !corpus.applies() {
            // Not a failure. The glibc corpus says nothing on a musl machine and the other
            // way round, and a run that reported that as a problem would be a run people
            // learn to ignore.
            println!("{}: not this machine, skipped", corpus.name);
            continue;
        }
        if !corpus.is_fetched(repo) {
            eprintln!("{}: not fetched, run `rucc-compat fetch {}`", corpus.name, corpus.name);
            failures += 1;
            continue;
        }
        let scratch = scratch.join(&corpus.name);
        let done =
            differ::run(repo, corpus, &settings, &register, &scratch).map_err(|e| e.to_string())?;
        println!("{}", done.summary());
        for outcome in done.outcomes.iter().filter(|o| o.is_failure()) {
            println!("  {} {}", outcome.status.word(), outcome.case);
        }
        if report {
            let dir = repo.join("results");
            fs::create_dir_all(&dir).map_err(|e| e.to_string())?;
            let path = dir.join(format!("{}.md", corpus.name));
            fs::write(&path, differ::markdown(&done, &settings, &register))
                .map_err(|e| e.to_string())?;
            println!("  wrote {}", path.display());
        }
        failures += done.failures();
    }
    Ok(if failures == 0 { ExitCode::SUCCESS } else { ExitCode::FAILURE })
}

fn check_them(repo: &Path, all: &[Corpus], args: &[String]) -> Result<ExitCode, String> {
    let mut settings =
        pipeline::Settings { rucc: from_env("RUCC", "rucc"), ..pipeline::Settings::default() };
    let mut report = false;
    let mut names = Vec::new();
    let mut at = 0;
    while at < args.len() {
        let arg = args[at].as_str();
        match arg {
            "--report" => report = true,
            "--rucc" => settings.rucc = PathBuf::from(value(args, &mut at, arg)?),
            "--unit" => settings.unit = Some(value(args, &mut at, arg)?),
            "--failed" => settings.failed = true,
            "--only" => settings.only.push(value(args, &mut at, arg)?),
            "--jobs" => {
                let text = value(args, &mut at, arg)?;
                let jobs = text.parse().map_err(|_| format!("`{text}` is not a number"))?;
                settings.jobs = Some(jobs);
            }
            "--limit" => {
                let text = value(args, &mut at, arg)?;
                let limit = text.parse().map_err(|_| format!("`{text}` is not a number"))?;
                settings.limit = Some(limit);
            }
            other if other.starts_with('-') => {
                return Err(format!("`{other}` is not an option of check"));
            }
            other => names.push(other.to_owned()),
        }
        at += 1;
    }
    let wanted = chosen(all, &names)?;
    let scratch = repo.join("target").join("pipeline");
    let mut failures = 0;
    for corpus in wanted {
        if !corpus.applies() {
            println!("{}: not this machine, skipped", corpus.name);
            continue;
        }
        if !corpus.is_fetched(repo) {
            eprintln!("{}: not fetched, run `rucc-compat fetch {}`", corpus.name, corpus.name);
            failures += 1;
            continue;
        }
        let scratch = scratch.join(&corpus.name);
        let done = pipeline::run(repo, corpus, &settings, &scratch).map_err(|e| e.to_string())?;
        println!("{}", done.summary());
        for outcome in done.outcomes.iter().filter(|o| o.is_failure()) {
            println!("  {} {}", outcome.status.word(), outcome.case);
        }
        for outcome in done.outcomes.iter().filter(|o| o.is_stale()) {
            println!("  passes now, take the exclusion out: {}", outcome.case);
        }
        for entry in &done.unmatched {
            println!("  excluded but not a case of this corpus: {}", entry.case);
        }
        if report {
            let dir = repo.join("results");
            fs::create_dir_all(&dir).map_err(|e| e.to_string())?;
            let path = dir.join(format!("{}-pipeline.md", corpus.name));
            fs::write(&path, pipeline::markdown(&done, &settings)).map_err(|e| e.to_string())?;
            println!("  wrote {}", path.display());
        }
        failures += done.failures();
    }
    Ok(if failures == 0 { ExitCode::SUCCESS } else { ExitCode::FAILURE })
}

fn exec_them(repo: &Path, all: &[Corpus], args: &[String]) -> Result<ExitCode, String> {
    let mut settings = exec::Settings {
        rucc: from_env("RUCC", "rucc"),
        cc: from_env("CC", "cc"),
        ..exec::Settings::default()
    };
    let mut routes = Vec::new();
    let mut report = false;
    let mut written = None;
    let mut names = Vec::new();
    let mut at = 0;
    while at < args.len() {
        let arg = args[at].as_str();
        match arg {
            "--report" => report = true,
            "--rucc" => settings.rucc = PathBuf::from(value(args, &mut at, arg)?),
            "--cc" => settings.cc = PathBuf::from(value(args, &mut at, arg)?),
            "--unit" => settings.unit = Some(value(args, &mut at, arg)?),
            "--opt" => settings.opt = Some(value(args, &mut at, arg)?),
            "--rule-coverage" => {
                written = Some(PathBuf::from(value(args, &mut at, arg)?));
                settings.coverage = true;
            }
            "--machine" => settings.machine = Some(value(args, &mut at, arg)?),
            "--path" => {
                let word = value(args, &mut at, arg)?;
                let route = Route::named(&word).ok_or_else(|| {
                    format!("`{word}` is not a build path, try assembly, object or driver")
                })?;
                routes.push(route);
            }
            "--timeout" => {
                let text = value(args, &mut at, arg)?;
                let seconds = text.parse().map_err(|_| format!("`{text}` is not a number"))?;
                settings.timeout = Some(seconds);
            }
            "--failed" => settings.failed = true,
            "--only" => settings.only.push(value(args, &mut at, arg)?),
            "--jobs" => {
                let text = value(args, &mut at, arg)?;
                let jobs = text.parse().map_err(|_| format!("`{text}` is not a number"))?;
                settings.jobs = Some(jobs);
            }
            "--limit" => {
                let text = value(args, &mut at, arg)?;
                let limit = text.parse().map_err(|_| format!("`{text}` is not a number"))?;
                settings.limit = Some(limit);
            }
            other if other.starts_with('-') => {
                return Err(format!("`{other}` is not an option of exec"));
            }
            other => names.push(other.to_owned()),
        }
        at += 1;
    }
    if !routes.is_empty() {
        settings.routes = routes;
    }
    let wanted = chosen(all, &names)?;
    // The level is part of the path rather than only part of the command, so that two sweeps at
    // two levels can run at the same time. Without it they share a directory and write over each
    // other's objects, and what comes out is not a failure either of them would get on its own:
    // wrong answers and link errors scattered over cases that pass when the sweep is run alone.
    // Six levels in parallel is the difference between half an hour and five minutes on a
    // machine with the cores for it.
    let scratch =
        repo.join("target").join("exec").join(settings.opt.as_deref().unwrap_or("default"));
    let mut failures = 0;
    let mut fired = Marks::default();
    for corpus in wanted {
        if corpus.oracle.is_none() {
            // Not a failure. A header set has no program in it to run, and a corpus of real
            // projects has none until somebody has written down what a right answer is.
            println!("{}: no oracle, nothing to run", corpus.name);
            continue;
        }
        if !corpus.applies() {
            println!("{}: not this machine, skipped", corpus.name);
            continue;
        }
        if !corpus.is_fetched(repo) {
            eprintln!("{}: not fetched, run `rucc-compat fetch {}`", corpus.name, corpus.name);
            failures += 1;
            continue;
        }
        let scratch = scratch.join(&corpus.name);
        let done = exec::run(repo, corpus, &settings, &scratch).map_err(|e| e.to_string())?;
        println!("{}", done.summary());
        for outcome in done.outcomes.iter().filter(|o| o.is_failure()) {
            println!("  {} on {}: {}", outcome.status.word(), outcome.route.word(), outcome.case);
        }
        for outcome in done.outcomes.iter().filter(|o| o.is_stale()) {
            println!("  passes now, take the exclusion out: {}", outcome.case);
        }
        for entry in &done.unmatched {
            println!("  excluded but not a case of this corpus: {}", entry.case);
        }
        if report {
            let dir = repo.join("results");
            fs::create_dir_all(&dir).map_err(|e| e.to_string())?;
            let path = dir.join(exec::result_file(&corpus.name, settings.opt.as_deref()));
            fs::write(&path, exec::markdown(&done, &settings)).map_err(|e| e.to_string())?;
            println!("  wrote {}", path.display());
        }
        if let Some(marks) = &done.fired {
            fired.merge(marks, &corpus.name)?;
        }
        failures += done.failures();
    }
    if let Some(path) = written {
        if fired.rules.is_empty() {
            // Asking for a number and being given an empty file is how somebody ends up quoting
            // one that was never measured, so this says what happened instead.
            return Err(format!(
                "nothing recorded which rules it fired, so there is nothing to write to {}. \
                 Either nothing was built or this compiler does not have -Zrule-coverage",
                path.display()
            ));
        }
        if let Some(dir) = path.parent().filter(|d| !d.as_os_str().is_empty()) {
            fs::create_dir_all(dir).map_err(|e| e.to_string())?;
        }
        fs::write(&path, fired.listing()).map_err(|e| format!("{}: {e}", path.display()))?;
        println!("{}", fired.summary());
        println!("  wrote {}", path.display());
    }
    Ok(if failures == 0 { ExitCode::SUCCESS } else { ExitCode::FAILURE })
}

/// Unions what one or more sweeps recorded and says which lowering rules nothing fired.
fn coverage_of(repo: &Path, args: &[String]) -> Result<ExitCode, String> {
    let mut report = false;
    let mut given = Vec::new();
    for arg in args {
        match arg.as_str() {
            "--report" => report = true,
            other if other.starts_with('-') => {
                return Err(format!("`{other}` is not an option of coverage"));
            }
            other => given.push(PathBuf::from(other)),
        }
    }
    if given.is_empty() {
        return Err("coverage needs a file or a directory to read, see --help".to_owned());
    }
    let mut all = Marks::default();
    for path in &given {
        let whose = path.display().to_string();
        // A directory is every coverage file under it, however deep, which is what a scratch tree
        // left behind by a sweep looks like. A file is itself.
        let mine = match path.is_dir() {
            true => coverage::gather(path)?
                .ok_or_else(|| format!("{whose}: no coverage files anywhere under it"))?,
            false => {
                let text = fs::read_to_string(path).map_err(|e| format!("{whose}: {e}"))?;
                coverage::parse(&text, &whose)?
            }
        };
        all.merge(&mine, &whose)?;
    }
    println!("{}", all.summary());
    for rule in all.unused() {
        println!("  nothing fired {} {}", rule.at, rule.pattern);
    }
    if report {
        let dir = repo.join("results");
        fs::create_dir_all(&dir).map_err(|e| e.to_string())?;
        let path = dir.join("rule-coverage.md");
        fs::write(&path, all.markdown()).map_err(|e| e.to_string())?;
        println!("  wrote {}", path.display());
    }
    Ok(ExitCode::SUCCESS)
}

/// The corpora the names ask for, or every one of them when no name was given.
fn chosen<'a>(all: &'a [Corpus], names: &[String]) -> Result<Vec<&'a Corpus>, String> {
    if names.is_empty() {
        return Ok(all.iter().collect());
    }
    let mut wanted = Vec::with_capacity(names.len());
    for name in names {
        let found = all
            .iter()
            .find(|c| c.name == *name)
            .ok_or_else(|| format!("there is no corpus called `{name}`, try `list`"))?;
        wanted.push(found);
    }
    Ok(wanted)
}

fn value(args: &[String], at: &mut usize, flag: &str) -> Result<String, String> {
    *at += 1;
    args.get(*at).cloned().ok_or_else(|| format!("{flag} needs a value after it"))
}

fn from_env(name: &str, fallback: &str) -> PathBuf {
    match std::env::var(name) {
        Ok(value) if !value.is_empty() => PathBuf::from(value),
        _ => PathBuf::from(fallback),
    }
}
