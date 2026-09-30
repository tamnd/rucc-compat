//! The rows of a conformance corpus: which construct of the language each case is there for.
//!
//! A corpus of programs says how many programs pass, and that number is easy to read as more than
//! it is. Two hundred green cases can cover the language or cover `printf` two hundred times, and
//! nothing in the run tells those apart. A row is the other half of the claim. It names one
//! construct, the standard that brought it in and the clause that describes it, and then either
//! the case that exercises it or the issue that will make one pass. So the size of what is
//! measured is a number of its own, and "the corpus is green" and "the corpus is small" stop being
//! one statement.
//!
//! The rows live in `rows.toml` beside the manifest rather than in it, because there are hundreds
//! of them and they are read by different people for a different reason: the manifest says how
//! to build and judge the programs, and the rows say what the programs are for.
//!
//! Three rules keep the list honest in both directions. Every row has a case or an issue, so a
//! construct cannot be listed and then quietly left untested. Every case is named by some row, so
//! a program cannot be added without saying what it is there to show. And with the GNU matrix at
//! hand, every feature in it has a row, so the extensions rucc claims are measured against the
//! same list the compiler answers `__has_attribute` and `__has_builtin` from.

use std::collections::{BTreeMap, BTreeSet};
use std::fs;
use std::path::Path;

use crate::corpus::Corpus;
use crate::differ;
use crate::toml::{self, Error};

/// The standards a row can belong to, oldest first, with `gnu` for the extensions.
///
/// C17 is here although it added no construct of its own, because a row about a defect it
/// resolved belongs to it and a list that cannot say so files the row under the wrong year.
pub const STANDARDS: [&str; 6] = ["c89", "c99", "c11", "c17", "c23", "gnu"];

/// The file beside `corpus.toml` the rows are read from.
pub const FILE: &str = "rows.toml";

/// One construct of the language and what stands behind it.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Row {
    /// A name unique in the file, such as `c99/compound-literal`.
    pub id: String,
    /// Which of [`STANDARDS`] brought it in.
    pub standard: String,
    /// Where the standard describes it, such as `6.5.2.5`, or where GCC's manual does.
    pub clause: String,
    /// What the construct is, in a few words.
    pub what: String,
    /// The case that exercises it, named as `exec` names it.
    pub case: Option<String>,
    /// The issue that will make it pass, when no case does yet or the case is excluded.
    pub issue: Option<String>,
    /// The name the GNU matrix gives the feature, for a row that is about one.
    pub feature: Option<String>,
}

/// What a corpus's rows come to.
#[derive(Debug, Clone, Default, PartialEq, Eq)]
pub struct Count {
    /// The corpus.
    pub corpus: String,
    /// Every row.
    pub rows: usize,
    /// How many distinct cases the rows name.
    pub cases: usize,
    /// Rows per standard, in the order of [`STANDARDS`], leaving out the empty ones.
    pub by_standard: Vec<(String, usize)>,
    /// Rows with a case and no issue, which is the rows a green run proves.
    pub covered: usize,
    /// Rows with a case whose failure an issue admits to.
    pub excused: usize,
    /// Rows with an issue and no case yet.
    pub waiting: usize,
}

impl Count {
    /// One line, the way the other commands print theirs.
    #[must_use]
    pub fn summary(&self) -> String {
        let standards: Vec<String> =
            self.by_standard.iter().map(|(name, n)| format!("{name} {n}")).collect();
        format!(
            "{}: {} rows over {} cases ({}), {} covered, {} excused, {} waiting on an issue",
            self.corpus,
            self.rows,
            self.cases,
            standards.join(", "),
            self.covered,
            self.excused,
            self.waiting
        )
    }
}

/// Reads the rows of a corpus, or `None` when it keeps no `rows.toml`.
///
/// # Errors
///
/// When the file cannot be read or a row breaks one of the rules in the module comment that can
/// be checked without the cases: a missing field, a standard that is not one of [`STANDARDS`], a
/// row with neither a case nor an issue, or an id used twice.
pub fn load(repo: &Path, corpus: &Corpus) -> Result<Option<Vec<Row>>, Error> {
    let path = repo.join("corpus").join(&corpus.name).join(FILE);
    let Ok(text) = fs::read_to_string(&path) else {
        return Ok(None);
    };
    let whose = format!("{}/{FILE}", corpus.name);
    parse(&whose, &text).map(Some)
}

/// Reads rows out of the text of a `rows.toml`.
///
/// # Errors
///
/// As [`load`].
pub fn parse(whose: &str, text: &str) -> Result<Vec<Row>, Error> {
    let doc = toml::parse(whose, text)?;
    let mut rows: Vec<Row> = Vec::new();
    let mut seen = BTreeSet::new();
    for fields in doc.named("row") {
        let id = fields.need("id", whose)?.to_owned();
        let row = Row {
            standard: fields.need("standard", whose)?.to_owned(),
            clause: fields.need("clause", whose)?.to_owned(),
            what: fields.need("what", whose)?.to_owned(),
            case: fields.str("case").map(str::to_owned),
            issue: fields.str("issue").map(str::to_owned),
            feature: fields.str("feature").map(str::to_owned),
            id,
        };
        if !STANDARDS.contains(&row.standard.as_str()) {
            return Err(Error {
                message: format!(
                    "{whose}: row `{}` is in `{}`, which is not one of {}",
                    row.id,
                    row.standard,
                    STANDARDS.join(", ")
                ),
            });
        }
        // A row that names nothing is a construct somebody listed and nobody measures, which is
        // the one thing the list exists to make impossible.
        if row.case.is_none() && row.issue.is_none() {
            return Err(Error {
                message: format!(
                    "{whose}: row `{}` names neither a case nor an issue, so nothing stands behind it",
                    row.id
                ),
            });
        }
        if !seen.insert(row.id.clone()) {
            return Err(Error {
                message: format!("{whose}: there are two rows called `{}`", row.id),
            });
        }
        rows.push(row);
    }
    Ok(rows)
}

/// Checks the rows against the cases the corpus has and counts them.
///
/// # Errors
///
/// When a row names a case the corpus does not have, which is usually a case that was renamed,
/// or a case is named by no row, which is a program nobody said the purpose of.
pub fn check(rows: &[Row], cases: &[String], corpus: &str) -> Result<Count, Error> {
    let have: BTreeSet<&str> = cases.iter().map(String::as_str).collect();
    let mut problems = Vec::new();
    for row in rows {
        if let Some(case) = &row.case {
            if !have.contains(case.as_str()) {
                problems.push(format!("row `{}` names `{case}`, which is not a case", row.id));
            }
        }
    }
    let named: BTreeSet<&str> = rows.iter().filter_map(|r| r.case.as_deref()).collect();
    for case in cases {
        if !named.contains(case.as_str()) {
            problems.push(format!("`{case}` is named by no row"));
        }
    }
    if !problems.is_empty() {
        return Err(Error { message: format!("{corpus}: {}", problems.join("; ")) });
    }
    let mut per: BTreeMap<&str, usize> = BTreeMap::new();
    for row in rows {
        *per.entry(row.standard.as_str()).or_default() += 1;
    }
    let by_standard =
        STANDARDS.iter().filter_map(|s| per.get(s).map(|n| ((*s).to_owned(), *n))).collect();
    Ok(Count {
        corpus: corpus.to_owned(),
        rows: rows.len(),
        cases: named.len(),
        by_standard,
        covered: rows.iter().filter(|r| r.case.is_some() && r.issue.is_none()).count(),
        excused: rows.iter().filter(|r| r.case.is_some() && r.issue.is_some()).count(),
        waiting: rows.iter().filter(|r| r.case.is_none()).count(),
    })
}

/// The cases of a corpus the way `exec` names them, helpers left out.
///
/// # Errors
///
/// When the tree is not there.
pub fn cases_of(repo: &Path, corpus: &Corpus, scratch: &Path) -> Result<Vec<String>, Error> {
    let found = differ::without_helpers(differ::cases(repo, corpus, scratch)?, corpus);
    Ok(found.cases.into_iter().map(|c| c.name).collect())
}

/// The feature names in rucc's GNU matrix, `crates/rucc-gnu/features.toml`.
///
/// Read line by line rather than through [`toml::parse`], because the file is rucc's and not
/// ours and the only thing wanted from it is the `name` of each `[[feature]]` block. A reader
/// that took the whole file would stop working the day rucc writes something this repository's
/// subset of TOML does not cover, over fields nothing here looks at.
#[must_use]
pub fn matrix_names(text: &str) -> Vec<String> {
    let mut names = Vec::new();
    let mut inside = false;
    for line in text.lines() {
        let line = line.trim();
        if line.starts_with('[') {
            inside = line == "[[feature]]";
            continue;
        }
        if !inside {
            continue;
        }
        let Some(rest) = line.strip_prefix("name") else { continue };
        let Some(value) = rest.trim_start().strip_prefix('=') else { continue };
        let value = value.trim();
        if let Some(name) = value.strip_prefix('"').and_then(|v| v.strip_suffix('"')) {
            names.push(name.to_owned());
            inside = false;
        }
    }
    names
}

/// Checks the rows against the GNU matrix: every feature in it has a row, and every row that
/// names a feature names one the matrix has.
///
/// # Errors
///
/// With every feature that has no row and every row whose feature is not in the matrix, since
/// the first run of this over a new matrix is going to find many and a list of one at a time
/// would take many runs to get through.
pub fn check_matrix(rows: &[Row], names: &[String], corpus: &str) -> Result<(), Error> {
    let known: BTreeSet<&str> = names.iter().map(String::as_str).collect();
    let claimed: BTreeSet<&str> = rows.iter().filter_map(|r| r.feature.as_deref()).collect();
    let mut problems: Vec<String> = Vec::new();
    for row in rows {
        if let Some(feature) = &row.feature {
            if !known.contains(feature.as_str()) {
                problems.push(format!(
                    "row `{}` is about `{feature}`, which the matrix does not have",
                    row.id
                ));
            }
        }
    }
    let missing: Vec<&str> =
        names.iter().map(String::as_str).filter(|n| !claimed.contains(n)).collect();
    if !missing.is_empty() {
        problems.push(format!("{} features have no row: {}", missing.len(), missing.join(", ")));
    }
    match problems.is_empty() {
        true => Ok(()),
        false => Err(Error { message: format!("{corpus}: {}", problems.join("; ")) }),
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    const ONE: &str = "[[row]]\nid = \"c89/if\"\nstandard = \"c89\"\nclause = \"6.8.4.1\"\nwhat = \"the if statement\"\ncase = \"c89/if.c\"\n";

    #[test]
    fn a_row_says_what_it_is_and_what_stands_behind_it() {
        let rows = parse("t", ONE).unwrap();
        assert_eq!(rows.len(), 1);
        assert_eq!(rows[0].case.as_deref(), Some("c89/if.c"));
        let count = check(&rows, &["c89/if.c".to_owned()], "t").unwrap();
        assert_eq!(
            count.summary(),
            "t: 1 rows over 1 cases (c89 1), 1 covered, 0 excused, 0 waiting on an issue"
        );
    }

    #[test]
    fn a_row_with_nothing_behind_it_or_a_standard_nobody_wrote_is_refused() {
        let bare = "[[row]]\nid = \"a\"\nstandard = \"c89\"\nclause = \"1\"\nwhat = \"x\"\n";
        assert!(parse("t", bare).is_err());
        let year = "[[row]]\nid = \"a\"\nstandard = \"c95\"\nclause = \"1\"\nwhat = \"x\"\nissue = \"#1\"\n";
        assert!(parse("t", year).is_err());
        assert!(parse("t", &format!("{ONE}{ONE}")).is_err(), "two rows with one id");
    }

    #[test]
    fn a_waiting_row_counts_apart_and_a_case_with_no_row_is_refused() {
        let text = format!(
            "{ONE}[[row]]\nid = \"c23/embed\"\nstandard = \"c23\"\nclause = \"6.10.4\"\nwhat = \"#embed\"\nissue = \"tamnd/rucc#1\"\n"
        );
        let rows = parse("t", &text).unwrap();
        let count = check(&rows, &["c89/if.c".to_owned()], "t").unwrap();
        assert_eq!((count.rows, count.covered, count.waiting), (2, 1, 1));
        assert_eq!(count.by_standard, [("c89".to_owned(), 1), ("c23".to_owned(), 1)]);

        let stray = check(&rows, &["c89/if.c".to_owned(), "c89/else.c".to_owned()], "t");
        assert!(stray.unwrap_err().message.contains("`c89/else.c` is named by no row"));
        let gone = check(&rows, &[], "t");
        assert!(gone.unwrap_err().message.contains("which is not a case"));
    }

    #[test]
    fn the_matrix_is_read_for_its_names_and_every_one_needs_a_row() {
        let matrix = "# a comment\n[[feature]]\nname = \"attribute:cleanup\"\nkind = \"attribute\"\nnotes = \"name = \\\"not this\\\"\"\n\n[[feature]]\nname = \"__builtin_expect\"\n";
        let names = matrix_names(matrix);
        assert_eq!(names, ["attribute:cleanup", "__builtin_expect"]);

        let text = "[[row]]\nid = \"gnu/cleanup\"\nstandard = \"gnu\"\nclause = \"attributes\"\nwhat = \"cleanup\"\nissue = \"#1\"\nfeature = \"attribute:cleanup\"\n";
        let rows = parse("t", text).unwrap();
        let short = check_matrix(&rows, &names, "t").unwrap_err();
        assert!(short.message.contains("1 features have no row: __builtin_expect"));
        let all = [names[0].clone()];
        assert!(check_matrix(&rows, &all, "t").is_ok());
        let odd = check_matrix(&rows, &["__builtin_trap".to_owned()], "t").unwrap_err();
        assert!(odd.message.contains("which the matrix does not have"));
    }
}
