//! What a corpus is, and the register of divergences we accept.

use std::env;
use std::fs;
use std::path::{Path, PathBuf};

use crate::toml::{self, Error, Fields};

/// The placeholder a manifest carries until somebody has verified the hash.
pub const UNRECORDED: &str = "unrecorded";

/// What an exclusion's `when` is allowed to name, which is what `std::env::consts::OS` says on
/// the three platforms this compiler is built for.
pub const PLATFORMS: &[&str] = &["linux", "macos", "windows"];

/// Where the code comes from.
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum Source {
    /// The header set of the machine the harness runs on. On an Ubuntu runner that is glibc
    /// and in an Alpine container it is musl, which is also the honest test: those are the
    /// headers a user compiles against.
    Installed,
    /// A tarball at a pinned version, fetched and verified before it is unpacked.
    Tarball(Tarball),
}

/// A tarball corpus, as the manifest describes it.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Tarball {
    /// Where to get it.
    pub upstream: String,
    /// The version, which is in the URL and in the directory it unpacks into.
    pub version: String,
    /// The digest of the tarball, or [`UNRECORDED`].
    pub sha256: String,
    /// The SPDX identifier of the license the code carries.
    pub license: String,
    /// The path inside the tarball to the license text. A tree that unpacks without it is
    /// refused, because vendored code with no license in it is not code we can keep.
    pub license_file: String,
    /// The directory the tarball unpacks into.
    pub root: String,
}

impl Tarball {
    /// Whether the hash has been verified by a person and committed.
    #[must_use]
    pub fn is_recorded(&self) -> bool {
        self.sha256 != UNRECORDED && self.sha256.len() == 64
    }
}

/// What one unit of the corpus is.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum UnitKind {
    /// Files preprocessed as they are.
    Source,
    /// Headers, each one included from a file of one line, which is how a header set is
    /// checked for being includable on its own.
    Headers,
}

/// One case the pipeline check is not expected to get through yet.
///
/// The list is checked in and it is meant to shrink, which is why every entry carries the
/// issue that will remove it and why an entry that no longer excludes anything is a failure.
/// Without those two rules an exclusion list becomes the place a regression goes to be quiet.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Exclusion {
    /// The case name, which is the unit and the file, the same string the report prints.
    pub case: String,
    /// The issue that will remove this entry.
    pub issue: String,
    /// What goes wrong, in one line, so the list can be read without opening anything.
    pub why: String,
    /// The operating systems this excuses the case on, empty meaning all of them.
    ///
    /// Some gaps are one platform's: a structure passed to a variadic function is lowered on a
    /// Mac and is not on Linux, so the same case fails on one machine and passes on the other.
    /// An entry with no `when` would then be stale wherever it passes, and the run would be red
    /// on one platform whichever way it was written.
    pub when: Vec<String>,
}

impl Exclusion {
    /// Whether this entry says anything about the machine it is being read on.
    #[must_use]
    pub fn here(&self) -> bool {
        self.when.is_empty() || self.when.iter().any(|os| os == env::consts::OS)
    }
}

/// One group of things to preprocess.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Unit {
    /// What it is called, which is what `--unit` selects and what the case names begin with.
    pub name: String,
    /// Which kind.
    pub kind: UnitKind,
    /// The files or the header names, when they are listed rather than walked.
    pub files: Vec<String>,
    /// A directory to walk for headers, relative to the tree.
    pub dir: Option<String>,
    /// Paths under `dir` that are not walked, each of which needs a reason in the manifest
    /// next to it.
    pub skip: Vec<String>,
    /// Flags passed to both compilers unchanged.
    pub flags: Vec<String>,
}

/// One body of code and what to do with it.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Corpus {
    /// The directory name under `corpus/`, which is what the harness calls it.
    pub name: String,
    /// Why it is worth the time it costs.
    pub summary: String,
    /// Where the code comes from.
    pub source: Source,
    /// Files, any one of which has to exist for this corpus to mean anything on this machine.
    ///
    /// An installed corpus is the header set of the machine it runs on, and glibc and musl
    /// are never both that machine. The probe is how a run on a glibc runner skips the musl
    /// corpus instead of quietly comparing glibc against itself under the wrong name.
    ///
    /// Several paths rather than one, because the same libc is laid out differently by
    /// different distributions and a probe that only knows one of them makes the corpus
    /// silently stop running on the others.
    pub probe: Vec<String>,
    /// What to preprocess.
    pub units: Vec<Unit>,
    /// The cases the pipeline check is not expected to get through, in file order.
    pub excluded: Vec<Exclusion>,
}

impl Corpus {
    /// The entry that excuses this case on this machine, if there is one.
    #[must_use]
    pub fn excuse(&self, case: &str) -> Option<&Exclusion> {
        self.excluded.iter().find(|e| e.case == case && e.here())
    }

    /// The directory the code is in, given the repository root.
    ///
    /// An installed corpus has no tree of its own and answers with the root, so that a unit
    /// naming an absolute directory such as `/usr/include` still works.
    #[must_use]
    pub fn tree(&self, repo: &Path) -> PathBuf {
        match &self.source {
            Source::Installed => repo.to_path_buf(),
            Source::Tarball(t) => repo.join("vendor").join(&self.name).join(&t.root),
        }
    }

    /// Whether this machine is one this corpus says anything about.
    #[must_use]
    pub fn applies(&self) -> bool {
        self.probe.is_empty() || self.probe.iter().any(|path| Path::new(path).exists())
    }

    /// Whether the tree is there, for [`Source::Tarball`].
    #[must_use]
    pub fn is_fetched(&self, repo: &Path) -> bool {
        match self.source {
            Source::Installed => true,
            Source::Tarball(_) => self.tree(repo).is_dir(),
        }
    }
}

/// Reads every manifest under `repo/corpus`, in name order.
///
/// # Errors
///
/// When a manifest is unreadable or is missing a field. One bad manifest fails the load
/// rather than being skipped, because a corpus that silently stops running is a corpus that
/// stops finding bugs and nobody notices.
pub fn load_all(repo: &Path) -> Result<Vec<Corpus>, Error> {
    let dir = repo.join("corpus");
    let mut names: Vec<String> = Vec::new();
    let listing =
        fs::read_dir(&dir).map_err(|e| Error { message: format!("{}: {e}", dir.display()) })?;
    for entry in listing.flatten() {
        if entry.path().join("corpus.toml").is_file() {
            names.push(entry.file_name().to_string_lossy().into_owned());
        }
    }
    names.sort();
    names.iter().map(|name| load(repo, name)).collect()
}

/// Reads one manifest.
///
/// # Errors
///
/// When it is unreadable, or a field is missing, or a field says something this does not know.
pub fn load(repo: &Path, name: &str) -> Result<Corpus, Error> {
    let path = repo.join("corpus").join(name).join("corpus.toml");
    let whose = format!("corpus/{name}/corpus.toml");
    let text = fs::read_to_string(&path)
        .map_err(|e| Error { message: format!("{}: {e}", path.display()) })?;
    let doc = toml::parse(&whose, &text)?;
    let root = &doc.root;
    let named = root.need("name", &whose)?;
    if named != name {
        return Err(Error {
            message: format!("{whose}: `name` is `{named}` but the directory is `{name}`"),
        });
    }
    let source = match root.need("source", &whose)? {
        "installed" => Source::Installed,
        "tarball" => Source::Tarball(Tarball {
            upstream: root.need("upstream", &whose)?.to_owned(),
            version: root.need("version", &whose)?.to_owned(),
            sha256: root.need("sha256", &whose)?.to_owned(),
            license: root.need("license", &whose)?.to_owned(),
            license_file: root.need("license-file", &whose)?.to_owned(),
            root: root.need("root", &whose)?.to_owned(),
        }),
        other => {
            return Err(Error {
                message: format!(
                    "{whose}: `source` is `{other}`, which is not `installed` or `tarball`"
                ),
            });
        }
    };
    let mut units = Vec::new();
    for fields in doc.named("unit") {
        units.push(unit(fields, &whose)?);
    }
    if units.is_empty() {
        return Err(Error { message: format!("{whose}: a corpus with no [[unit]] runs nothing") });
    }
    let mut excluded = Vec::new();
    for fields in doc.named("exclude") {
        let when = fields.list("when");
        // Checked here rather than left to match nothing, because an entry naming an operating
        // system that does not exist excuses a case on no machine at all and reads as though it
        // excuses it on one.
        for os in &when {
            if !PLATFORMS.contains(&os.as_str()) {
                return Err(Error {
                    message: format!(
                        "{whose}: `when` is `{os}`, which is not one of {}",
                        PLATFORMS.join(", ")
                    ),
                });
            }
        }
        excluded.push(Exclusion {
            case: fields.need("case", &whose)?.to_owned(),
            // Required, and this is the rule that makes the list shrink rather than grow. An
            // exclusion with nowhere to point at is a decision nobody has to defend.
            issue: fields.need("issue", &whose)?.to_owned(),
            why: fields.need("why", &whose)?.to_owned(),
            when,
        });
    }
    Ok(Corpus {
        name: name.to_owned(),
        summary: root.need("summary", &whose)?.to_owned(),
        source,
        probe: root.list("probe"),
        units,
        excluded,
    })
}

fn unit(fields: &Fields, whose: &str) -> Result<Unit, Error> {
    let name = fields.need("name", whose)?.to_owned();
    let kind = match fields.need("kind", whose)? {
        "source" => UnitKind::Source,
        "headers" => UnitKind::Headers,
        other => {
            return Err(Error {
                message: format!(
                    "{whose}: unit `kind` is `{other}`, which is not `source` or `headers`"
                ),
            });
        }
    };
    let files = fields.list("files");
    let dir = fields.str("dir").map(str::to_owned);
    if files.is_empty() && dir.is_none() {
        return Err(Error { message: format!("{whose}: a unit needs `files` or `dir`") });
    }
    Ok(Unit { name, kind, files, dir, skip: fields.list("skip"), flags: fields.list("flags") })
}

/// One difference we have decided to live with.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Divergence {
    /// The short name it is reported under.
    pub id: String,
    /// What the difference is.
    pub what: String,
    /// Why it is acceptable for now.
    pub why: String,
    /// The issue that will remove it.
    pub issue: String,
    /// Which comparison rule it suppresses.
    pub rule: String,
    /// The corpus it is about, or every corpus when it is not set.
    pub corpus: Option<String>,
    /// The unit it is about, or every unit when it is not set.
    pub unit: Option<String>,
    /// Text that has to be somewhere in the differing line for the entry to cover it.
    pub matches: Option<String>,
}

impl Divergence {
    /// Whether this entry covers what is being asked about.
    ///
    /// Every condition the entry states has to hold, and a condition it does not state is not
    /// a condition. An entry with none of the three is a statement about the whole run, which
    /// is only ever right for a difference that is systematic.
    #[must_use]
    pub fn covers(&self, q: Question<'_>) -> bool {
        self.rule == q.rule
            && self.corpus.as_deref().is_none_or(|name| name == q.corpus)
            && self.unit.as_deref().is_none_or(|name| name == q.unit)
            && self.matches.as_deref().is_none_or(|text| q.text.contains(text))
    }

    /// Whether the entry says anything about where it applies.
    #[must_use]
    pub fn is_scoped(&self) -> bool {
        self.corpus.is_some() || self.unit.is_some() || self.matches.is_some()
    }
}

/// A difference, put to the register.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct Question<'a> {
    /// The comparison rule that fired.
    pub rule: &'a str,
    /// The corpus the case is in.
    pub corpus: &'a str,
    /// The unit the case is in.
    pub unit: &'a str,
    /// Both sides of the first differing line, which is what `matches` looks in.
    pub text: &'a str,
}

/// The register.
#[derive(Debug, Default, Clone, PartialEq, Eq)]
pub struct Register {
    /// Every entry, in file order.
    pub entries: Vec<Divergence>,
}

impl Register {
    /// The first entry that covers the question, if there is one.
    #[must_use]
    pub fn accepts(&self, q: Question<'_>) -> Option<&Divergence> {
        self.entries.iter().find(|d| d.covers(q))
    }
}

/// Reads `divergences.toml`.
///
/// # Errors
///
/// When an entry is missing any of its four required fields. That is the point of the file:
/// an entry with no reason on it does not load, so accepting a difference has to be a diff
/// somebody wrote and somebody else read.
pub fn register(repo: &Path) -> Result<Register, Error> {
    let path = repo.join("divergences.toml");
    let text = match fs::read_to_string(&path) {
        Ok(text) => text,
        // No register is the same as an empty one, and it is what a fresh clone has before
        // anybody has accepted anything.
        Err(_) => return Ok(Register::default()),
    };
    let doc = toml::parse("divergences.toml", &text)?;
    let mut entries = Vec::new();
    for fields in doc.named("divergence") {
        let entry = Divergence {
            id: fields.need("id", "divergences.toml")?.to_owned(),
            what: fields.need("what", "divergences.toml")?.to_owned(),
            why: fields.need("why", "divergences.toml")?.to_owned(),
            issue: fields.need("issue", "divergences.toml")?.to_owned(),
            rule: fields.need("rule", "divergences.toml")?.to_owned(),
            corpus: fields.str("corpus").map(str::to_owned),
            unit: fields.str("unit").map(str::to_owned),
            matches: fields.str("matches").map(str::to_owned),
        };
        // An unscoped entry is a statement about every case in every corpus. That is a fair
        // thing to say about a printer difference, which is systematic by nature, and it is
        // never a fair thing to say about a token difference: one line in one header would
        // silence the rule that decides whether the output still compiles to the same
        // program, everywhere, and the run would go green while finding nothing.
        if entry.rule == "token-text" && !entry.is_scoped() {
            return Err(Error {
                message: format!(
                    "divergences.toml: `{}` suppresses `token-text` everywhere. Give it a `corpus`, a `unit` or a `matches`.",
                    entry.id
                ),
            });
        }
        entries.push(entry);
    }
    Ok(Register { entries })
}

#[cfg(test)]
mod tests {
    use std::fs;

    use super::*;

    /// A repository laid out in a temporary directory, removed when the test ends.
    struct Fake {
        root: PathBuf,
    }

    impl Fake {
        fn new(name: &str) -> Fake {
            let root = env::temp_dir().join(format!("rucc-compat-{name}-{}", std::process::id()));
            let _ = fs::remove_dir_all(&root);
            fs::create_dir_all(root.join("corpus")).unwrap();
            Fake { root }
        }

        fn corpus(&self, name: &str, text: &str) {
            let dir = self.root.join("corpus").join(name);
            fs::create_dir_all(&dir).unwrap();
            fs::write(dir.join("corpus.toml"), text).unwrap();
        }
    }

    impl Drop for Fake {
        fn drop(&mut self) {
            let _ = fs::remove_dir_all(&self.root);
        }
    }

    const INSTALLED: &str = "name = \"sys\"\nsummary = \"the headers on this machine\"\nsource = \"installed\"\n\n[[unit]]\nname = \"standard\"\nkind = \"headers\"\nfiles = [\"stdio.h\"]\n";

    #[test]
    fn an_installed_corpus_needs_no_tarball_fields() {
        let fake = Fake::new("installed");
        fake.corpus("sys", INSTALLED);
        let corpus = load(&fake.root, "sys").unwrap();
        assert_eq!(corpus.source, Source::Installed);
        assert_eq!(corpus.units[0].kind, UnitKind::Headers);
        assert!(corpus.is_fetched(&fake.root));
    }

    #[test]
    fn a_corpus_with_a_probe_that_is_not_there_does_not_apply() {
        let fake = Fake::new("probe");
        let text = INSTALLED.replace(
            "source = \"installed\"",
            "source = \"installed\"\nprobe = \"/there/is/no/such/file\"",
        );
        fake.corpus("sys", &text);
        assert!(!load(&fake.root, "sys").unwrap().applies());
        fake.corpus("sys", INSTALLED);
        assert!(load(&fake.root, "sys").unwrap().applies());
    }

    #[test]
    fn a_probe_applies_when_any_one_of_its_paths_is_there() {
        let fake = Fake::new("probe-list");
        // Forward slashes even on Windows, which opens them either way, because a backslash
        // in a quoted string is an escape and this test is about the probe, not about that.
        let here = fake.root.join("corpus").display().to_string().replace('\\', "/");
        let text = INSTALLED.replace(
            "source = \"installed\"",
            &format!(
                "source = \"installed\"\nprobe = [\n  \"/there/is/no/such/file\",\n  \"{here}\",\n]"
            ),
        );
        fake.corpus("sys", &text);
        let corpus = load(&fake.root, "sys").unwrap();
        assert_eq!(corpus.probe.len(), 2);
        assert!(corpus.applies());
    }

    #[test]
    fn an_exclusion_is_read_and_found_by_the_case_it_names() {
        let fake = Fake::new("exclude");
        let text = format!(
            "{INSTALLED}\n[[exclude]]\ncase = \"standard/stdio.h\"\nissue = \"#142\"\nwhy = \"an initializer that writes over an earlier one\"\n"
        );
        fake.corpus("sys", &text);
        let corpus = load(&fake.root, "sys").unwrap();
        assert_eq!(corpus.excluded.len(), 1);
        assert_eq!(corpus.excuse("standard/stdio.h").unwrap().issue, "#142");
        assert_eq!(corpus.excuse("standard/stdlib.h"), None);
        assert!(corpus.excluded[0].when.is_empty(), "no `when` is every platform");
    }

    #[test]
    fn an_exclusion_naming_a_platform_excuses_the_case_on_that_one_and_nowhere_else() {
        let fake = Fake::new("exclude-when");
        let other = PLATFORMS.iter().find(|os| **os != env::consts::OS).expect("three of them");
        let entry = |os: &str| {
            format!(
                "[[exclude]]\ncase = \"standard/stdio.h\"\nissue = \"#159\"\nwhy = \"one platform's ABI\"\nwhen = [\"{os}\"]\n"
            )
        };

        fake.corpus("sys", &format!("{INSTALLED}\n{}", entry(env::consts::OS)));
        let corpus = load(&fake.root, "sys").unwrap();
        assert!(corpus.excluded[0].here());
        assert_eq!(corpus.excuse("standard/stdio.h").unwrap().issue, "#159");

        fake.corpus("sys", &format!("{INSTALLED}\n{}", entry(other)));
        let corpus = load(&fake.root, "sys").unwrap();
        assert!(!corpus.excluded[0].here(), "still read, and it says nothing here");
        assert_eq!(corpus.excuse("standard/stdio.h"), None);
    }

    #[test]
    fn an_exclusion_naming_a_platform_that_does_not_exist_is_refused() {
        let fake = Fake::new("exclude-when-unknown");
        let text = format!(
            "{INSTALLED}\n[[exclude]]\ncase = \"standard/stdio.h\"\nissue = \"#159\"\nwhy = \"it does not work\"\nwhen = [\"lunix\"]\n"
        );
        fake.corpus("sys", &text);
        let said = load(&fake.root, "sys").unwrap_err().message;
        assert!(said.contains("`lunix`"), "{said}");
    }

    #[test]
    fn an_exclusion_with_no_issue_to_point_at_is_refused() {
        let fake = Fake::new("exclude-no-issue");
        let text = format!(
            "{INSTALLED}\n[[exclude]]\ncase = \"standard/stdio.h\"\nwhy = \"it does not work\"\n"
        );
        fake.corpus("sys", &text);
        let e = load(&fake.root, "sys").unwrap_err();
        assert!(e.message.contains("issue"), "{}", e.message);
    }

    #[test]
    fn a_corpus_with_nothing_excluded_has_an_empty_list_rather_than_no_list() {
        let fake = Fake::new("exclude-none");
        fake.corpus("sys", INSTALLED);
        assert!(load(&fake.root, "sys").unwrap().excluded.is_empty());
    }

    #[test]
    fn a_manifest_whose_name_is_not_its_directory_is_refused() {
        let fake = Fake::new("misnamed");
        fake.corpus("other", INSTALLED);
        let e = load(&fake.root, "other").unwrap_err();
        assert!(e.message.contains("but the directory is"), "{}", e.message);
    }

    #[test]
    fn a_corpus_with_no_units_runs_nothing_and_says_so() {
        let fake = Fake::new("empty");
        fake.corpus("sys", "name = \"sys\"\nsummary = \"s\"\nsource = \"installed\"\n");
        let e = load(&fake.root, "sys").unwrap_err();
        assert!(e.message.contains("no [[unit]]"), "{}", e.message);
    }

    #[test]
    fn an_unrecorded_hash_loads_and_says_it_is_not_recorded() {
        let fake = Fake::new("unrecorded");
        let text = format!(
            "name = \"t\"\nsummary = \"s\"\nsource = \"tarball\"\nupstream = \"https://example.invalid/t.tar.gz\"\nversion = \"1\"\nsha256 = \"{UNRECORDED}\"\nlicense = \"MIT\"\nlicense-file = \"t-1/COPYING\"\nroot = \"t-1\"\n\n[[unit]]\nname = \"amalgamation\"\nkind = \"source\"\nfiles = [\"a.c\"]\n"
        );
        fake.corpus("t", &text);
        let corpus = load(&fake.root, "t").unwrap();
        let Source::Tarball(tarball) = &corpus.source else { panic!("expected a tarball") };
        assert!(!tarball.is_recorded());
        assert!(!corpus.is_fetched(&fake.root));
        assert!(corpus.tree(&fake.root).ends_with("vendor/t/t-1"));
    }

    #[test]
    fn every_corpus_in_this_repository_loads() {
        // The manifests are data, and data that does not load is data nobody finds out about
        // until the day they need it.
        let repo = Path::new(env!("CARGO_MANIFEST_DIR")).join("../..");
        let corpora = load_all(&repo).unwrap();
        assert!(!corpora.is_empty(), "there should be corpora in corpus/");
    }

    #[test]
    fn the_register_in_this_repository_loads_and_every_entry_has_a_reason() {
        let repo = Path::new(env!("CARGO_MANIFEST_DIR")).join("../..");
        let register = register(&repo).unwrap();
        for entry in &register.entries {
            assert!(!entry.why.is_empty(), "{} has no reason", entry.id);
            assert!(entry.issue.starts_with("https://"), "{} has no issue", entry.id);
        }
    }

    /// A register file in a fake repository.
    fn register_from(name: &str, text: &str) -> Result<Register, Error> {
        let fake = Fake::new(name);
        fs::write(fake.root.join("divergences.toml"), text).unwrap();
        register(&fake.root)
    }

    const ENTRY: &str = "[[divergence]]\nid = \"e\"\nwhat = \"w\"\nwhy = \"y\"\nissue = \"https://example.invalid/1\"\n";

    #[test]
    fn an_unscoped_token_text_entry_would_silence_the_whole_run_and_is_refused() {
        let text = format!("{ENTRY}rule = \"token-text\"\n");
        let e = register_from("unscoped", &text).unwrap_err();
        assert!(e.message.contains("everywhere"), "{}", e.message);
        // Scoped any of the three ways, it loads.
        for scope in ["corpus = \"glibc\"", "unit = \"standard\"", "matches = \"__attribute__\""] {
            let text = format!("{ENTRY}rule = \"token-text\"\n{scope}\n");
            assert!(register_from("scoped", &text).is_ok(), "{scope} should be enough");
        }
    }

    #[test]
    fn a_printer_difference_is_systematic_so_an_unscoped_entry_is_allowed() {
        let text = format!("{ENTRY}rule = \"spacing\"\n");
        assert_eq!(register_from("spacing", &text).unwrap().entries.len(), 1);
    }

    #[test]
    fn every_condition_an_entry_states_has_to_hold() {
        let text = format!(
            "{ENTRY}rule = \"token-text\"\ncorpus = \"sqlite\"\nunit = \"shell\"\nmatches = \"availability\"\n"
        );
        let register = register_from("conditions", &text).unwrap();
        let ask = |corpus, unit, text| {
            register.accepts(Question { rule: "token-text", corpus, unit, text }).is_some()
        };
        assert!(ask("sqlite", "shell", "int f(void) __attribute__((availability(x)));"));
        assert!(!ask("glibc", "shell", "int f(void) __attribute__((availability(x)));"));
        assert!(!ask("sqlite", "headers", "int f(void) __attribute__((availability(x)));"));
        assert!(!ask("sqlite", "shell", "int f(void);"), "the text has to be in the line");
        assert!(
            register
                .accepts(Question {
                    rule: "spacing",
                    corpus: "sqlite",
                    unit: "shell",
                    text: "availability"
                })
                .is_none(),
            "an entry covers the one rule it names"
        );
    }
}
