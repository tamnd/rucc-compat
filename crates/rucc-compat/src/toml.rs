//! A reader for the subset of TOML this repository writes.
//!
//! Not a TOML implementation. It reads key and value lines, `[table]` headers and
//! `[[array]]` headers, with strings, lists of strings, booleans and whole numbers as values.
//! That is everything `corpus.toml` and `divergences.toml` use, and the files it has to read
//! are files in this repository rather than files a stranger sends us.
//!
//! The alternative was a dependency, and a harness with a dependency is a harness that stops
//! building on the day the compiler it tests is the thing that needs looking at.

use std::fmt;

/// One value.
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum Value {
    /// A quoted string.
    Str(String),
    /// A list of quoted strings, written on one line.
    List(Vec<String>),
    /// `true` or `false`.
    Bool(bool),
    /// A whole number, written without quotes around it.
    ///
    /// Here because a timeout in seconds is a number, and writing one as a string would make
    /// every reader of the manifest wonder what else about it is not what it looks like.
    Int(i64),
}

/// The keys of one table, in the order they were written.
///
/// A list rather than a map. These tables have a handful of keys, the order is the order
/// somebody chose to write them in, and an error message that follows the file reads better.
#[derive(Debug, Default, Clone, PartialEq, Eq)]
pub struct Fields {
    entries: Vec<(String, Value)>,
}

impl Fields {
    /// The value of `key`, if it is a string.
    #[must_use]
    pub fn str(&self, key: &str) -> Option<&str> {
        match self.get(key) {
            Some(Value::Str(s)) => Some(s),
            _ => None,
        }
    }

    /// The value of `key`, or an error naming the file it should have been in.
    ///
    /// # Errors
    ///
    /// When the key is missing or is not a string.
    pub fn need(&self, key: &str, whose: &str) -> Result<&str, Error> {
        self.str(key).filter(|v| !v.is_empty()).ok_or_else(|| Error {
            message: format!("{whose}: `{key}` is required and has to be a non empty string"),
        })
    }

    /// The value of `key` as a list, which a single string also satisfies.
    #[must_use]
    pub fn list(&self, key: &str) -> Vec<String> {
        match self.get(key) {
            Some(Value::List(items)) => items.clone(),
            Some(Value::Str(s)) => vec![s.clone()],
            _ => Vec::new(),
        }
    }

    /// The value of `key` as a boolean, or `fallback` when it is not there.
    #[must_use]
    pub fn bool(&self, key: &str, fallback: bool) -> bool {
        match self.get(key) {
            Some(Value::Bool(b)) => *b,
            _ => fallback,
        }
    }

    /// The value of `key` as a whole number, or `None` when it is not there or is not one.
    #[must_use]
    pub fn int(&self, key: &str) -> Option<i64> {
        match self.get(key) {
            Some(Value::Int(n)) => Some(*n),
            _ => None,
        }
    }

    fn get(&self, key: &str) -> Option<&Value> {
        self.entries.iter().find(|(k, _)| k == key).map(|(_, v)| v)
    }

    fn set(&mut self, key: String, value: Value) {
        self.entries.push((key, value));
    }
}

/// A parsed file: the keys before any header, and the tables after.
#[derive(Debug, Default, Clone, PartialEq, Eq)]
pub struct Doc {
    /// The keys written before the first header.
    pub root: Fields,
    /// Every table, as the name in its header and its keys. A `[[name]]` header appears once
    /// per block, so the two forms read the same way and the caller decides which it wanted.
    pub tables: Vec<(String, Fields)>,
}

impl Doc {
    /// Every table with this name, in file order.
    pub fn named<'a>(&'a self, name: &'a str) -> impl Iterator<Item = &'a Fields> {
        self.tables.iter().filter(move |(n, _)| n == name).map(|(_, f)| f)
    }
}

/// A file that could not be read.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Error {
    /// What was wrong, with the line number when there is one.
    pub message: String,
}

impl fmt::Display for Error {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.write_str(&self.message)
    }
}

impl std::error::Error for Error {}

/// Reads `text`, which came from `name`.
///
/// # Errors
///
/// On anything this subset does not cover, rather than on a guess at what was meant.
pub fn parse(name: &str, text: &str) -> Result<Doc, Error> {
    let mut doc = Doc::default();
    let mut current: Option<(String, Fields)> = None;
    for (at, line) in logical(text) {
        let line = line.as_str();
        let fail = |what: &str| Error { message: format!("{name}:{}: {what}", at + 1) };
        if let Some(rest) = line.strip_prefix("[[") {
            let header = rest.strip_suffix("]]").ok_or_else(|| fail("unterminated [[ header"))?;
            if let Some(table) = current.take() {
                doc.tables.push(table);
            }
            current = Some((header.trim().to_owned(), Fields::default()));
            continue;
        }
        if let Some(rest) = line.strip_prefix('[') {
            let header = rest.strip_suffix(']').ok_or_else(|| fail("unterminated [ header"))?;
            if let Some(table) = current.take() {
                doc.tables.push(table);
            }
            current = Some((header.trim().to_owned(), Fields::default()));
            continue;
        }
        let (key, value) = line.split_once('=').ok_or_else(|| fail("expected `key = value`"))?;
        let key = key.trim().to_owned();
        let value = read_value(value.trim()).ok_or_else(|| fail("value is not one this reads"))?;
        match current.as_mut() {
            Some((_, fields)) => fields.set(key, value),
            None => doc.root.set(key, value),
        }
    }
    if let Some(table) = current.take() {
        doc.tables.push(table);
    }
    Ok(doc)
}

/// The lines, with comments gone, blank ones dropped, and a list that runs over several
/// lines joined into the one line the rest of this reads.
///
/// A header list is forty entries long and putting it on one line would make it unreadable,
/// which is the sort of thing that ends with somebody not adding the header.
fn logical(text: &str) -> Vec<(usize, String)> {
    let mut out: Vec<(usize, String)> = Vec::new();
    let mut open: Option<(usize, String)> = None;
    for (at, raw) in text.lines().enumerate() {
        let line = strip_comment(raw).trim();
        if line.is_empty() {
            continue;
        }
        match open.take() {
            Some((started, mut joined)) => {
                if !joined.ends_with('[') && !line.starts_with(']') {
                    joined.push(' ');
                }
                joined.push_str(line);
                if depth(&joined) > 0 {
                    open = Some((started, joined));
                } else {
                    out.push((started, joined));
                }
            }
            None => {
                if depth(line) > 0 {
                    open = Some((at, line.to_owned()));
                } else {
                    out.push((at, line.to_owned()));
                }
            }
        }
    }
    // An unterminated list is left as it is, so the value reader is the one that complains
    // and it does so with the line the list started on.
    if let Some(unterminated) = open {
        out.push(unterminated);
    }
    out
}

/// How many list brackets are open at the end of the line, ignoring brackets inside strings.
///
/// A `[table]` header opens and closes on the same line, so it counts as nothing, and that is
/// what keeps this from swallowing the rest of the file.
fn depth(line: &str) -> isize {
    let mut depth = 0;
    let mut quotes = Quotes::default();
    for ch in line.chars() {
        if quotes.step(ch) {
            continue;
        }
        match ch {
            '[' => depth += 1,
            ']' => depth -= 1,
            _ => {}
        }
    }
    depth
}

/// The line without its comment.
///
/// A `#` inside a string is not a comment, which matters because a flag list holds
/// `-D__GNUC__=4` today and will hold something with a `#` in it eventually.
fn strip_comment(line: &str) -> &str {
    let mut quotes = Quotes::default();
    for (at, ch) in line.char_indices() {
        if quotes.step(ch) {
            continue;
        }
        if ch == '#' {
            return &line[..at];
        }
    }
    line
}

/// Whether we are inside a string, which is the one thing every scan over a line here needs
/// to agree about.
#[derive(Debug, Default)]
struct Quotes {
    inside: bool,
    escaped: bool,
}

impl Quotes {
    /// Takes the next character and says whether it is inside a string or is the quote or the
    /// backslash that delimits one, all of which mean the caller should look past it.
    ///
    /// The escape matters: a manifest that writes `"-DA=\"#1\""` has a `#` in it that is not a
    /// comment and a `"` in it that does not end the string.
    fn step(&mut self, ch: char) -> bool {
        if self.escaped {
            self.escaped = false;
            return true;
        }
        if self.inside && ch == '\\' {
            self.escaped = true;
            return true;
        }
        if ch == '"' {
            self.inside = !self.inside;
            return true;
        }
        self.inside
    }
}

fn read_value(text: &str) -> Option<Value> {
    match text {
        "true" => return Some(Value::Bool(true)),
        "false" => return Some(Value::Bool(false)),
        _ => {}
    }
    if let Some(inner) = text.strip_prefix('[').and_then(|t| t.strip_suffix(']')) {
        let mut items = Vec::new();
        for part in split_items(inner) {
            let part = part.trim();
            if part.is_empty() {
                continue;
            }
            items.push(read_string(part)?);
        }
        return Some(Value::List(items));
    }
    // Before the string, because a string is quoted and a number is not, so nothing that reads
    // as one reads as the other and the order only decides which of the two is tried first.
    if let Ok(number) = text.parse::<i64>() {
        return Some(Value::Int(number));
    }
    Some(Value::Str(read_string(text)?))
}

/// Splits a list body on the commas that are not inside a string.
fn split_items(text: &str) -> Vec<&str> {
    let mut items = Vec::new();
    let mut quotes = Quotes::default();
    let mut start = 0;
    for (at, ch) in text.char_indices() {
        if quotes.step(ch) {
            continue;
        }
        if ch == ',' {
            items.push(&text[start..at]);
            start = at + 1;
        }
    }
    items.push(&text[start..]);
    items
}

/// A quoted string, with `\"` and `\\` unescaped.
fn read_string(text: &str) -> Option<String> {
    let inner = text.strip_prefix('"')?.strip_suffix('"')?;
    let mut out = String::with_capacity(inner.len());
    let mut chars = inner.chars();
    while let Some(ch) = chars.next() {
        if ch == '\\' {
            match chars.next() {
                Some('n') => out.push('\n'),
                Some(other) => out.push(other),
                None => return None,
            }
        } else {
            out.push(ch);
        }
    }
    Some(out)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn keys_before_a_header_are_the_root() {
        let doc = parse("t.toml", "name = \"musl\"\nsource = \"installed\"\n").unwrap();
        assert_eq!(doc.root.str("name"), Some("musl"));
        assert!(doc.tables.is_empty());
    }

    #[test]
    fn a_repeated_header_is_a_table_each_time() {
        let text = "[[unit]]\nkind = \"source\"\n[[unit]]\nkind = \"headers\"\n";
        let doc = parse("t.toml", text).unwrap();
        let kinds: Vec<&str> = doc.named("unit").filter_map(|u| u.str("kind")).collect();
        assert_eq!(kinds, ["source", "headers"]);
    }

    #[test]
    fn a_number_written_without_quotes_reads_as_a_number() {
        let doc = parse("t.toml", "timeout = 20\nback = -3\nname = \"20\"\n").unwrap();
        assert_eq!(doc.root.int("timeout"), Some(20));
        assert_eq!(doc.root.int("back"), Some(-3));
        // A quoted one is the string it was written as, so a manifest cannot mean a number and
        // get a string by accident, or the other way round.
        assert_eq!(doc.root.int("name"), None);
        assert_eq!(doc.root.str("name"), Some("20"));
        assert_eq!(doc.root.int("missing"), None);
    }

    #[test]
    fn a_list_reads_as_a_list_and_a_string_reads_as_one_item() {
        let doc = parse("t.toml", "flags = [\"-I\", \"include\"]\none = \"just\"\n").unwrap();
        assert_eq!(doc.root.list("flags"), ["-I", "include"]);
        assert_eq!(doc.root.list("one"), ["just"]);
        assert!(doc.root.list("missing").is_empty());
    }

    #[test]
    fn a_list_can_run_over_several_lines_with_comments_in_it() {
        let text =
            "files = [\n  \"a.h\", \"b.h\", # two of them\n  \"c.h\",\n]\nkind = \"headers\"\n";
        let doc = parse("t.toml", text).unwrap();
        assert_eq!(doc.root.list("files"), ["a.h", "b.h", "c.h"]);
        assert_eq!(doc.root.str("kind"), Some("headers"));
    }

    #[test]
    fn a_header_is_not_the_start_of_a_list() {
        let text = "[[unit]]\nkind = \"source\"\n[table]\nname = \"x\"\n";
        let doc = parse("t.toml", text).unwrap();
        assert_eq!(doc.tables.len(), 2);
    }

    #[test]
    fn a_hash_inside_a_string_is_not_a_comment() {
        let doc = parse("t.toml", "flags = [\"-DA=\\\"#1\\\"\"] # a real comment\n").unwrap();
        assert_eq!(doc.root.list("flags"), ["-DA=\"#1\""]);
    }

    #[test]
    fn a_missing_key_names_the_file_it_was_missing_from() {
        let doc = parse("t.toml", "name = \"x\"\n").unwrap();
        let e = doc.root.need("summary", "corpus/x").unwrap_err();
        assert!(e.message.contains("corpus/x"), "{}", e.message);
        assert!(e.message.contains("summary"), "{}", e.message);
    }

    #[test]
    fn a_line_that_is_not_a_pair_says_which_line_it_was() {
        let e = parse("t.toml", "name = \"x\"\nnonsense\n").unwrap_err();
        assert!(e.message.starts_with("t.toml:2:"), "{}", e.message);
    }

    #[test]
    fn a_boolean_is_a_boolean_and_a_missing_one_is_the_fallback() {
        let doc = parse("t.toml", "system = true\n").unwrap();
        assert!(doc.root.bool("system", false));
        assert!(doc.root.bool("absent", true));
    }
}
