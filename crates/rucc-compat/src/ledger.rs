//! What the last run on this machine made of each case, so the next one can be pointed at what
//! is not green.
//!
//! Somebody fixing a compiler bug wants the thirty cases that failed, not the two thousand that
//! ran. Until there was a ledger the only way to find those thirty was to run all two thousand
//! and read the report, which for `gcc-torture` is thirty five minutes to learn a list that the
//! last run already knew.
//!
//! Only the cases that were not green go in the file. A corpus that is entirely green writes an
//! empty ledger, and an empty ledger is a different thing from no ledger at all: the first says
//! there is nothing to look at and the second says nobody has looked.
//!
//! A narrow run merges rather than overwrites. A run that saw thirty cases has an opinion about
//! those thirty and none at all about the rest, so it replaces its own rows and leaves every
//! other row where it was. That is what makes `--failed` twice in a row mean something: the
//! second one asks about what the first one did not fix.
//!
//! The file lives under `target` because it is a fact about this machine and this checkout. It
//! is not a report and it is not committed. `results/` is where the reports go.

use std::collections::{BTreeMap, BTreeSet};
use std::fs;
use std::io;
use std::path::{Path, PathBuf};

/// Where the ledger for one corpus and one command lives.
///
/// `tag` separates runs of the same command that are not comparable, which today is the
/// optimization level: a case that passes at `-O0` and fails at `-O2` has two different last
/// outcomes and one file could not hold both.
#[must_use]
pub fn path(repo: &Path, corpus: &str, command: &str, tag: Option<&str>) -> PathBuf {
    let name = match tag {
        Some(tag) => format!("{corpus}-{command}-O{tag}.txt"),
        None => format!("{corpus}-{command}.txt"),
    };
    repo.join("target").join("last").join(name)
}

/// The cases the last run did not call green, in name order.
///
/// `None` when there is no ledger, which is nobody having run this corpus here, and is a
/// different answer from an empty list.
#[must_use]
pub fn unpassed(path: &Path) -> Option<Vec<String>> {
    let text = fs::read_to_string(path).ok()?;
    Some(text.lines().filter_map(|line| line.split_once('\t')).map(|(_, c)| c.to_owned()).collect())
}

/// Records what this run saw, keeping what it did not.
///
/// `seen` is every case that ran, with the word it came out as and whether that word is a green
/// one. The green ones come out of the file and the rest go in, and a case this run never
/// reached is left exactly as it was.
///
/// # Errors
///
/// When the file cannot be written, which is a full disk or a `target` somebody made read only.
pub fn save(path: &Path, seen: &[(String, String, bool)]) -> io::Result<()> {
    let mut rows: BTreeMap<String, String> = match fs::read_to_string(path) {
        Ok(text) => text
            .lines()
            .filter_map(|line| line.split_once('\t'))
            .map(|(word, case)| (case.to_owned(), word.to_owned()))
            .collect(),
        Err(_) => BTreeMap::new(),
    };
    for (case, word, green) in seen {
        match green {
            true => rows.remove(case),
            false => rows.insert(case.clone(), word.clone()),
        };
    }
    let mut text = String::new();
    for (case, word) in &rows {
        text.push_str(word);
        text.push('\t');
        text.push_str(case);
        text.push('\n');
    }
    if let Some(dir) = path.parent() {
        fs::create_dir_all(dir)?;
    }
    fs::write(path, text)
}

/// Whether a case name is one of the ones asked for.
///
/// Empty patterns are nobody asking, so everything is. A pattern matches when the name contains
/// it: the names are paths, and a glob that does not cross a slash is the wrong tool for
/// `test/`, while one that does is a glob nobody can predict.
#[must_use]
pub fn wanted(name: &str, patterns: &[String]) -> bool {
    patterns.is_empty() || patterns.iter().any(|p| name.contains(p.as_str()))
}

/// Which cases a run has been narrowed to, worked out once before any of them runs.
///
/// Both narrowings at once are an intersection and not a union: `--only test/ --failed` is the
/// failing cases under `test/`, which is what somebody fixing one thing in one place wants.
#[derive(Debug, Clone, Default)]
pub struct Keep {
    /// What `--only` said, or empty for nobody saying.
    only: Vec<String>,
    /// The names the ledger had, or `None` for `--failed` not being asked for.
    failed: Option<BTreeSet<String>>,
}

impl Keep {
    /// Reads the ledger, if this run wants one.
    ///
    /// # Errors
    ///
    /// When `--failed` was asked for and there is no ledger, since the honest answer to "run
    /// what failed last time" on a machine where nothing has run is not "nothing failed".
    pub fn new(only: &[String], failed: Option<&Path>) -> Result<Keep, String> {
        let failed = match failed {
            None => None,
            Some(path) => {
                let names = unpassed(path).ok_or(
                    "there is no record of a run here, so there is nothing for --failed to \
                     narrow to. Run it once without --failed first.",
                )?;
                Some(names.into_iter().collect())
            }
        };
        Ok(Keep { only: only.to_vec(), failed })
    }

    /// Whether this run was narrowed at all.
    #[must_use]
    pub fn is_all(&self) -> bool {
        self.only.is_empty() && self.failed.is_none()
    }

    /// Whether this case is one of the ones asked for.
    #[must_use]
    pub fn wants(&self, name: &str) -> bool {
        wanted(name, &self.only) && self.failed.as_ref().is_none_or(|failed| failed.contains(name))
    }

    /// What to say when the narrowing left nothing to run.
    #[must_use]
    pub fn emptiness(&self) -> String {
        match (self.only.is_empty(), self.failed.is_some()) {
            (true, true) => "nothing failed last time, so --failed has nothing to run".to_owned(),
            (false, true) => format!(
                "nothing that failed last time matches {}",
                self.only.iter().map(|p| format!("`{p}`")).collect::<Vec<_>>().join(" or ")
            ),
            _ => format!(
                "no case matches {}",
                self.only.iter().map(|p| format!("`{p}`")).collect::<Vec<_>>().join(" or ")
            ),
        }
    }
}

#[cfg(test)]
mod tests {
    use std::fs;
    use std::path::PathBuf;

    use super::{Keep, path, save, unpassed, wanted};

    fn scratch(name: &str) -> PathBuf {
        let dir = std::env::temp_dir().join(format!("rucc-compat-ledger-{name}"));
        let _ = fs::remove_dir_all(&dir);
        fs::create_dir_all(&dir).expect("a temporary directory");
        dir.join("last.txt")
    }

    fn rows(cases: &[(&str, &str, bool)]) -> Vec<(String, String, bool)> {
        cases.iter().map(|(c, w, g)| ((*c).to_owned(), (*w).to_owned(), *g)).collect()
    }

    #[test]
    fn the_level_is_in_the_name_because_two_levels_are_two_answers() {
        let repo = PathBuf::from("/repo");
        assert!(path(&repo, "chibicc", "exec", None).ends_with("chibicc-exec.txt"));
        assert!(path(&repo, "chibicc", "exec", Some("2")).ends_with("chibicc-exec-O2.txt"));
    }

    #[test]
    fn no_ledger_at_all_is_not_an_empty_one() {
        let path = scratch("missing");
        assert_eq!(unpassed(&path), None);
        save(&path, &rows(&[("a.c", "passed", true)])).expect("it writes");
        assert_eq!(unpassed(&path), Some(Vec::new()));
    }

    #[test]
    fn only_what_was_not_green_is_kept() {
        let path = scratch("some");
        save(&path, &rows(&[("a.c", "passed", true), ("b.c", "wrong answer", false)]))
            .expect("it writes");
        assert_eq!(unpassed(&path), Some(vec!["b.c".to_owned()]));
    }

    #[test]
    fn a_case_that_starts_passing_comes_out_of_the_file() {
        let path = scratch("fixed");
        save(&path, &rows(&[("a.c", "did not build", false), ("b.c", "crashed", false)]))
            .expect("it writes");
        save(&path, &rows(&[("a.c", "passed", true)])).expect("it writes");
        assert_eq!(unpassed(&path), Some(vec!["b.c".to_owned()]));
    }

    #[test]
    fn a_case_this_run_never_reached_is_left_where_it_was() {
        let path = scratch("narrow");
        save(&path, &rows(&[("a.c", "did not build", false), ("b.c", "crashed", false)]))
            .expect("it writes");
        // A run narrowed to `a.c`, which says nothing at all about `b.c`.
        save(&path, &rows(&[("a.c", "wrong answer", false)])).expect("it writes");
        assert_eq!(unpassed(&path), Some(vec!["a.c".to_owned(), "b.c".to_owned()]));
        let text = fs::read_to_string(&path).expect("it reads");
        assert!(text.contains("wrong answer\ta.c"), "the word is the newer one: {text}");
    }

    #[test]
    fn the_rows_are_in_name_order_so_two_ledgers_can_be_diffed() {
        let path = scratch("order");
        save(&path, &rows(&[("z.c", "crashed", false), ("a.c", "crashed", false)]))
            .expect("it writes");
        assert_eq!(unpassed(&path), Some(vec!["a.c".to_owned(), "z.c".to_owned()]));
    }

    #[test]
    fn nobody_asking_for_a_name_wants_all_of_them() {
        assert!(wanted("test/alignof.c", &[]));
    }

    #[test]
    fn a_pattern_is_a_substring_of_the_whole_name() {
        let patterns = vec!["test/".to_owned()];
        assert!(wanted("chibicc/test/alignof.c", &patterns));
        assert!(!wanted("c-testsuite/single-exec/00204.c", &patterns));
    }

    #[test]
    fn asking_for_what_failed_where_nothing_has_run_is_an_error() {
        let path = scratch("never").with_file_name("nothing-here.txt");
        let refused = Keep::new(&[], Some(&path)).expect_err("there is no ledger");
        assert!(refused.contains("without --failed first"), "{refused}");
    }

    #[test]
    fn narrowing_by_neither_keeps_everything() {
        let keep = Keep::new(&[], None).expect("no ledger is wanted");
        assert!(keep.is_all());
        assert!(keep.wants("anything at all"));
    }

    #[test]
    fn narrowing_by_both_is_the_overlap_and_not_the_sum() {
        let path = scratch("both");
        save(
            &path,
            &rows(&[("chibicc/test/cast.c", "crashed", false), ("other/a.c", "crashed", false)]),
        )
        .expect("it writes");
        let keep = Keep::new(&["test/".to_owned()], Some(&path)).expect("the ledger is there");
        assert!(!keep.is_all());
        assert!(keep.wants("chibicc/test/cast.c"));
        assert!(!keep.wants("other/a.c"), "it failed but it does not match");
        assert!(!keep.wants("chibicc/test/passing.c"), "it matches but it did not fail");
    }

    #[test]
    fn what_is_said_when_nothing_is_left_names_which_narrowing_did_it() {
        let path = scratch("empty");
        save(&path, &rows(&[("a.c", "passed", true)])).expect("it writes");
        let all = Keep::new(&[], Some(&path)).expect("the ledger is there");
        assert!(all.emptiness().contains("nothing failed last time"), "{}", all.emptiness());
        let some = Keep::new(&["zzz".to_owned()], Some(&path)).expect("the ledger is there");
        assert!(some.emptiness().contains("`zzz`"), "{}", some.emptiness());
        let only = Keep::new(&["zzz".to_owned()], None).expect("no ledger is wanted");
        assert_eq!(only.emptiness(), "no case matches `zzz`");
    }

    #[test]
    fn any_of_the_patterns_is_enough() {
        let patterns = vec!["alignof".to_owned(), "00204".to_owned()];
        assert!(wanted("chibicc/test/alignof.c", &patterns));
        assert!(wanted("c-testsuite/single-exec/00204.c", &patterns));
        assert!(!wanted("c-testsuite/single-exec/00140.c", &patterns));
    }
}
