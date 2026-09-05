//! Which of the compiler's lowering rules the corpus ever reached.
//!
//! Design: `spec/20-execution-testing.md` section 20.9 in the compiler repository.
//!
//! Two things get called lowering coverage and only one of them lives here. Whether every IR
//! opcode has a rule to lower it is a property of the rule set, the compiler checks it when it is
//! built, and no corpus is needed to find the answer out. Whether every rule that is written ever
//! fires is a property of the corpus, and nothing but a corpus can answer it. A rule that is
//! written, proved and never selected has never run on a real machine, and a proof that has never
//! been checked against one is worth less than it looks. Rules nothing fires are also where dead
//! entries in the rule set collect, since nothing else would ever notice one.
//!
//! The compiler's side of this is `-Zrule-coverage=FILE`, which writes the whole rule set with
//! each rule marked `fired` or `unused`. This module reads those files and unions them, which is
//! what turns a run into a number about the corpus rather than about one program.
//!
//! A rule is identified by the file and the line it is written at, which is stable across a build
//! and readable in a report, and unlike an index into the generated table it does not change when
//! somebody adds a rule above it. Two files written by different builds of the compiler are
//! refused rather than unioned, because a union across two rule sets is a number about neither.

use std::fmt::Write as _;
use std::fs;
use std::path::{Path, PathBuf};

/// What the compiler writes on the first line of one of these files.
pub const HEADER: &str = "# rucc rule coverage:";

/// What the compiler names the files it writes, without the dot.
pub const EXTENSION: &str = "cov";

/// One rule of the table and whether anything fired it.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Rule {
    /// The rule file and the line it is written at, which is what identifies it.
    pub at: String,
    /// The pattern it matches, so a report can say what a rule is without anybody opening the
    /// rule file to find out.
    pub pattern: String,
    /// Whether any of the builds unioned here reached it.
    pub fired: bool,
}

/// A whole rule set and what was reached of it.
#[derive(Debug, Clone, Default, PartialEq, Eq)]
pub struct Marks {
    /// Which rule file this is about, as the compiler names it.
    pub source: String,
    /// Every rule in it, in the order the rule file writes them.
    pub rules: Vec<Rule>,
    /// How many coverage files went into this.
    ///
    /// Not part of the coverage number and worth having anyway: a percentage over four builds and
    /// the same percentage over four thousand are the same figure and not the same news. Files
    /// rather than compiler runs, because the compiler writes one file per run of it and the
    /// harness writes one holding a union of thousands, and nothing in the format says which of
    /// those a file in hand is. Counting what is actually there says something true either way.
    pub files: usize,
}

/// What a floor says about a coverage number.
///
/// Three answers rather than two, because a floor can be wrong in either direction and only one
/// of those is a failure. A number under the floor is the thing the floor exists to catch: rules
/// the corpus used to reach and no longer does, which is either a corpus that shrank or a rule set
/// that grew without anything to exercise the new part of it. A floor well behind the number is
/// bookkeeping that has gone stale, and it is reported rather than failed, because a floor that
/// is behind hides nothing and failing there would turn an improvement into a red build.
///
/// That is the one place this parts company with the exclusion lists, which do fail when they go
/// stale. An exclusion that no longer excludes anything is actively hiding a case that passes. A
/// floor that is behind is only under-claiming.
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum Verdict {
    /// Under the floor, with the line saying by how much.
    Under(String),
    /// A whole point or more above the floor, with the line saying what to raise it to.
    Over(String),
    /// At the floor, or above it by less than a rule or two, which is not worth a line.
    At,
}

impl Marks {
    /// How many rules something fired.
    #[must_use]
    pub fn fired(&self) -> usize {
        self.rules.iter().filter(|rule| rule.fired).count()
    }

    /// The rules nothing fired, which is the list this whole thing exists to produce.
    #[must_use]
    pub fn unused(&self) -> Vec<&Rule> {
        self.rules.iter().filter(|rule| !rule.fired).collect()
    }

    /// What fraction of the rule set was reached, out of a hundred.
    ///
    /// An empty rule set is a hundred percent covered, which is true and useless, and it is that
    /// way round because the alternative is a division by zero in a report.
    #[must_use]
    pub fn percent(&self) -> f64 {
        match self.rules.len() {
            0 => 100.0,
            total => {
                100.0 * f64::from(u32::try_from(self.fired()).unwrap_or(u32::MAX))
                    / f64::from(u32::try_from(total).unwrap_or(u32::MAX))
            }
        }
    }

    /// What a floor has to say about this number.
    ///
    /// The floor is a percentage, because the percentage is the figure everything else here
    /// quotes and a floor written in some other unit would be a second number to keep in step
    /// with the first. It is compared against the figure as printed rather than against the exact
    /// quotient, so that a run whose report says the floor and a run whose report says less than
    /// the floor are the two cases and there is no third one where the report reads as though it
    /// passed and the exit status says otherwise.
    #[must_use]
    pub fn against(&self, floor: f64) -> Verdict {
        let mine = (self.percent() * 10.0).round() / 10.0;
        if mine < floor {
            return Verdict::Under(format!(
                "{:.1} percent of {} is under the floor of {floor:.1} percent, and {} of the {} \
                 rules fired",
                mine,
                self.source,
                self.fired(),
                self.rules.len()
            ));
        }
        if mine - floor >= 1.0 {
            return Verdict::Over(format!(
                "the floor of {floor:.1} percent is {:.1} behind the {mine:.1} percent this \
                 reached, so it is worth raising to {mine:.1}",
                mine - floor
            ));
        }
        Verdict::At
    }

    /// Takes in what another set of builds reached.
    ///
    /// # Errors
    ///
    /// When the other file is about a different rule set, which means one of the two was written
    /// by a different build of the compiler and a union over both would be a number about
    /// neither. `whose` names the file in the message, since the whole point is finding out which
    /// of them is the odd one.
    pub fn merge(&mut self, other: &Marks, whose: &str) -> Result<(), String> {
        if self.rules.is_empty() {
            *self = other.clone();
            return Ok(());
        }
        if self.source != other.source {
            return Err(format!(
                "{whose} is about `{}` and the others are about `{}`, so a union over both would \
                 be a number about neither",
                other.source, self.source
            ));
        }
        if self.rules.len() != other.rules.len() {
            return Err(format!(
                "{whose} has {} rules in it and the others have {}, so it was written by a \
                 different build of the compiler",
                other.rules.len(),
                self.rules.len()
            ));
        }
        for (mine, theirs) in self.rules.iter_mut().zip(&other.rules) {
            if mine.at != theirs.at {
                return Err(format!(
                    "{whose} has `{}` where the others have `{}`, so it was written by a \
                     different build of the compiler",
                    theirs.at, mine.at
                ));
            }
            mine.fired |= theirs.fired;
        }
        self.files += other.files;
        Ok(())
    }

    /// The same thing back in the form the compiler wrote it, so that a union can be saved and
    /// then unioned with the next one.
    ///
    /// That round trip is the whole reason this is the compiler's format rather than a format of
    /// the harness's own. A nightly sweep writes one of these per corpus per level, and the
    /// number anybody quotes is the union of all of them.
    #[must_use]
    pub fn listing(&self) -> String {
        let mut out = format!(
            "{HEADER} {} of {} rules in {} fired\n",
            self.fired(),
            self.rules.len(),
            self.source
        );
        for rule in &self.rules {
            let word = match rule.fired {
                true => "fired",
                false => "unused",
            };
            let _ = writeln!(out, "{word} {} {}", rule.at, rule.pattern);
        }
        out
    }

    /// One line, for the terminal.
    #[must_use]
    pub fn summary(&self) -> String {
        format!(
            "rules: {} of {} fired over {} coverage files, {:.1} percent of {}",
            self.fired(),
            self.rules.len(),
            self.files,
            self.percent(),
            self.source
        )
    }

    /// The report, as the markdown that lands in `results/`.
    #[must_use]
    pub fn markdown(&self) -> String {
        let mut out = String::new();
        let _ = writeln!(out, "# Lowering rule coverage\n");
        let _ = writeln!(
            out,
            "Rule set: `{}`, {} rules. Unioned over {} coverage files.\n",
            self.source,
            self.rules.len(),
            self.files
        );
        let _ = writeln!(
            out,
            "Fired: {} of {}, which is {:.1} percent.\n",
            self.fired(),
            self.rules.len(),
            self.percent()
        );
        let unused = self.unused();
        if unused.is_empty() {
            let _ = writeln!(out, "Every rule in the set fired at least once.\n");
            return out;
        }
        let _ = writeln!(out, "## Rules nothing fired\n");
        let _ = writeln!(out, "| rule | pattern |");
        let _ = writeln!(out, "| --- | --- |");
        for rule in unused {
            let pattern = rule.pattern.replace('|', "\\|");
            let _ = writeln!(out, "| {} | `{pattern}` |", rule.at);
        }
        let _ = writeln!(out);
        out
    }
}

/// Reads one of the files the compiler wrote.
///
/// # Errors
///
/// When it is not one of those files, which is worth an error rather than an empty result: a
/// harness that read a truncated or half written file as no coverage would quietly report a
/// number that is too low and send somebody looking for corpus gaps that are not there.
pub fn parse(text: &str, whose: &str) -> Result<Marks, String> {
    let mut lines = text.lines();
    let head = lines.next().unwrap_or_default();
    let rest = head
        .strip_prefix(HEADER)
        .ok_or_else(|| format!("{whose}: the first line is not `{HEADER} ...`"))?;
    // `6 of 256 rules in rules/x86-64.rules fired`, and the rule file is the part worth keeping.
    let source = rest
        .split_once(" in ")
        .and_then(|(_, tail)| tail.trim_end().strip_suffix(" fired"))
        .ok_or_else(|| format!("{whose}: the first line does not name a rule file"))?
        .trim()
        .to_owned();
    let mut rules = Vec::new();
    for (index, line) in lines.enumerate() {
        if line.trim().is_empty() {
            continue;
        }
        let number = index + 2;
        let (word, tail) = line
            .split_once(' ')
            .ok_or_else(|| format!("{whose} line {number}: `{line}` is not a rule"))?;
        let fired = match word {
            "fired" => true,
            "unused" => false,
            other => {
                return Err(format!(
                    "{whose} line {number}: `{other}` is neither `fired` nor `unused`"
                ));
            }
        };
        let (at, pattern) = tail.split_once(' ').ok_or_else(|| {
            format!("{whose} line {number}: nothing after the rule's line number")
        })?;
        rules.push(Rule { at: at.to_owned(), pattern: pattern.to_owned(), fired });
    }
    if rules.is_empty() {
        return Err(format!("{whose}: no rules in it, so it says nothing about coverage"));
    }
    Ok(Marks { source, rules, files: 1 })
}

/// Unions the files at these paths.
///
/// # Errors
///
/// When one of them cannot be read or is not a coverage file, or when two of them are about
/// different rule sets.
pub fn union(paths: &[PathBuf]) -> Result<Marks, String> {
    let mut all = Marks::default();
    for path in paths {
        let whose = path.display().to_string();
        let text = fs::read_to_string(path).map_err(|e| format!("{whose}: {e}"))?;
        let mine = parse(&text, &whose)?;
        all.merge(&mine, &whose)?;
    }
    Ok(all)
}

/// Unions every coverage file under a directory, however deep.
///
/// # Errors
///
/// The same ways [`union`] does. A directory with none of them in it is not an error and comes
/// back as `None`, since the caller knows whether it asked for any.
pub fn gather(dir: &Path) -> Result<Option<Marks>, String> {
    let mut found = Vec::new();
    walk(dir, &mut found)?;
    if found.is_empty() {
        return Ok(None);
    }
    // Sorted, so that a file that is not like the others is named the same way twice running and
    // the error somebody reads is the same error their colleague read.
    found.sort();
    union(&found).map(Some)
}

/// Every coverage file under `dir`, added to `found`.
fn walk(dir: &Path, found: &mut Vec<PathBuf>) -> Result<(), String> {
    let entries = match fs::read_dir(dir) {
        Ok(entries) => entries,
        // A case that was thrown away after it passed is a directory that is not there, which is
        // the normal thing rather than a problem.
        Err(_) => return Ok(()),
    };
    for entry in entries {
        let entry = entry.map_err(|e| format!("{}: {e}", dir.display()))?;
        let path = entry.path();
        if path.is_dir() {
            walk(&path, found)?;
        } else if path.extension().is_some_and(|e| e == EXTENSION) {
            found.push(path);
        }
    }
    Ok(())
}

/// What to call the file one run of the compiler writes, under the directory it builds in.
///
/// One per invocation rather than one per case, because a case built through assembly runs the
/// compiler once per input file and the second run would otherwise write over the first.
#[must_use]
pub fn file_name(what: &str) -> String {
    format!("{what}.{EXTENSION}")
}

#[cfg(test)]
mod tests {
    use super::*;

    const TWO: &str = "\
# rucc rule coverage: 1 of 2 rules in rules/x86-64.rules fired
fired rules/x86-64.rules:12 (add.i32 x y)
unused rules/x86-64.rules:19 (sub.i32 x y)
";

    const OTHER: &str = "\
# rucc rule coverage: 1 of 2 rules in rules/x86-64.rules fired
unused rules/x86-64.rules:12 (add.i32 x y)
fired rules/x86-64.rules:19 (sub.i32 x y)
";

    #[test]
    fn a_file_says_what_the_rule_set_is_as_well_as_what_was_reached_of_it() {
        let marks = parse(TWO, "a.cov").expect("this is one of those files");
        assert_eq!(marks.source, "rules/x86-64.rules");
        assert_eq!(marks.rules.len(), 2);
        assert_eq!(marks.fired(), 1);
        assert_eq!(marks.files, 1);
        assert_eq!(marks.rules[0].at, "rules/x86-64.rules:12");
        assert_eq!(marks.rules[0].pattern, "(add.i32 x y)");
        assert!(marks.rules[0].fired);
        let unused: Vec<&str> = marks.unused().iter().map(|r| r.at.as_str()).collect();
        assert_eq!(unused, ["rules/x86-64.rules:19"]);
    }

    /// The union is what makes this a number about the corpus rather than about one program, so
    /// it is what has to be right. Either one having fired a rule is the rule having fired.
    #[test]
    fn what_two_runs_reached_is_what_either_of_them_reached() {
        let mut mine = parse(TWO, "a.cov").unwrap();
        let theirs = parse(OTHER, "b.cov").unwrap();
        mine.merge(&theirs, "b.cov").expect("the same rule set both times");
        assert_eq!(mine.fired(), 2);
        assert!(mine.unused().is_empty());
        assert_eq!(mine.files, 2);
        assert_eq!(mine.percent(), 100.0);
    }

    #[test]
    fn nothing_unioned_yet_takes_the_first_one_whole() {
        let mut all = Marks::default();
        let mine = parse(TWO, "a.cov").unwrap();
        all.merge(&mine, "a.cov").unwrap();
        assert_eq!(all, mine);
    }

    /// Two builds of the compiler are two rule sets, and a percentage over both is a percentage
    /// of nothing. The message has to name the file, since finding which of five hundred of them
    /// is the stale one is the whole job.
    #[test]
    fn a_file_from_another_build_of_the_compiler_is_refused_rather_than_unioned() {
        let mut mine = parse(TWO, "a.cov").unwrap();

        let shorter = "\
# rucc rule coverage: 0 of 1 rules in rules/x86-64.rules fired
unused rules/x86-64.rules:12 (add.i32 x y)
";
        let why = mine.merge(&parse(shorter, "b.cov").unwrap(), "b.cov").unwrap_err();
        assert!(why.contains("b.cov"), "{why}");
        assert!(why.contains("different build"), "{why}");

        let moved = TWO.replace(":19", ":23");
        let why = mine.merge(&parse(&moved, "c.cov").unwrap(), "c.cov").unwrap_err();
        assert!(why.contains("c.cov"), "{why}");

        let elsewhere = TWO.replace("x86-64", "aarch64");
        let why = mine.merge(&parse(&elsewhere, "d.cov").unwrap(), "d.cov").unwrap_err();
        assert!(why.contains("about neither"), "{why}");
    }

    /// A nightly sweep writes one of these per corpus per level and the number anybody quotes is
    /// the union of all of them, so a union has to be a thing that can be unioned again.
    #[test]
    fn a_union_written_back_out_is_a_file_this_can_read() {
        let mut mine = parse(TWO, "a.cov").unwrap();
        mine.merge(&parse(OTHER, "b.cov").unwrap(), "b.cov").unwrap();
        let again = parse(&mine.listing(), "union.cov").expect("its own format");
        assert_eq!(again.source, mine.source);
        assert_eq!(again.rules, mine.rules);
        assert!(mine.listing().starts_with("# rucc rule coverage: 2 of 2 rules"));
    }

    #[test]
    fn something_that_is_not_one_of_these_files_is_an_error_and_not_an_empty_answer() {
        assert!(parse("", "a.cov").is_err());
        assert!(parse("hello\n", "a.cov").is_err());
        // The header and nothing under it says nothing about coverage, and reading it as no
        // coverage at all would drag every number that touched it down.
        let why =
            parse("# rucc rule coverage: 0 of 0 rules in rules/x86-64.rules fired\n", "a.cov")
                .unwrap_err();
        assert!(why.contains("says nothing"), "{why}");
        let why = parse(
            "# rucc rule coverage: 1 of 2 rules in rules/x86-64.rules fired\nmaybe x\n",
            "a.cov",
        )
        .unwrap_err();
        assert!(why.contains("line 2"), "{why}");
    }

    #[test]
    fn the_report_lists_what_nothing_reached_and_says_so_when_that_is_nothing() {
        let marks = parse(TWO, "a.cov").unwrap();
        let text = marks.markdown();
        assert!(text.contains("1 of 2, which is 50.0 percent"), "{text}");
        assert!(text.contains("rules/x86-64.rules:19"), "{text}");
        assert!(text.contains("(sub.i32 x y)"), "{text}");
        // The rule that did fire is not in the table, since the table is the list of work.
        assert!(!text.contains("rules/x86-64.rules:12 |"), "{text}");

        let mut all = marks;
        all.merge(&parse(OTHER, "b.cov").unwrap(), "b.cov").unwrap();
        assert!(all.markdown().contains("Every rule in the set fired"), "{}", all.markdown());
    }

    #[test]
    fn a_tree_with_no_coverage_in_it_is_not_an_error() {
        let dir = std::env::temp_dir().join(format!("rucc-compat-cov-{}", std::process::id()));
        let _ = fs::remove_dir_all(&dir);
        fs::create_dir_all(dir.join("object")).unwrap();
        assert_eq!(gather(&dir).unwrap(), None);
        assert_eq!(gather(&dir.join("nowhere")).unwrap(), None);

        fs::write(dir.join("driver.cov"), TWO).unwrap();
        fs::write(dir.join("object").join("part0.cov"), OTHER).unwrap();
        fs::write(dir.join("object").join("part0.o"), "not a coverage file").unwrap();
        let all = gather(&dir).unwrap().expect("two of them are under there");
        assert_eq!(all.fired(), 2);
        assert_eq!(all.files, 2);
        let _ = fs::remove_dir_all(&dir);
    }

    /// The floor is the thing that keeps the number from falling back, so what it has to get
    /// right is the boundary. Equal to the floor passes, since a floor is a floor and not a
    /// target, and anything under it fails however little the difference is.
    #[test]
    fn a_number_at_the_floor_passes_and_a_number_under_it_does_not() {
        let mut marks = parse(TWO, "a.cov").unwrap();
        assert_eq!(marks.percent(), 50.0);
        assert_eq!(marks.against(50.0), Verdict::At);
        assert_eq!(marks.against(49.9), Verdict::At);
        let Verdict::Under(why) = marks.against(50.1) else {
            panic!("half of two is under any floor over fifty")
        };
        assert!(why.contains("50.0 percent"), "{why}");
        assert!(why.contains("floor of 50.1"), "{why}");
        assert!(why.contains("1 of the 2 rules"), "{why}");

        marks.merge(&parse(OTHER, "b.cov").unwrap(), "b.cov").unwrap();
        assert_eq!(marks.against(100.0), Verdict::At);
    }

    /// A floor the number has left behind is stale bookkeeping and not a failure, which is the
    /// one place this parts company with the exclusion lists. The line has to name the number to
    /// raise it to, since otherwise the reader goes and works it out from the summary.
    #[test]
    fn a_floor_the_number_has_left_a_whole_point_behind_is_said_and_not_failed() {
        let mut marks = parse(TWO, "a.cov").unwrap();
        marks.merge(&parse(OTHER, "b.cov").unwrap(), "b.cov").unwrap();
        assert_eq!(marks.percent(), 100.0);
        // Under a point behind is not worth a line, since one rule of a set this size moves the
        // number by more than that on its own.
        assert_eq!(marks.against(99.5), Verdict::At);
        let Verdict::Over(why) = marks.against(71.1) else {
            panic!("a hundred is well over seventy one")
        };
        assert!(why.contains("floor of 71.1"), "{why}");
        assert!(why.contains("raising to 100.0"), "{why}");
    }

    #[test]
    fn one_file_per_run_of_the_compiler_and_not_per_case() {
        assert_eq!(file_name("part0"), "part0.cov");
        assert_ne!(file_name("part0"), file_name("part1"));
    }
}
