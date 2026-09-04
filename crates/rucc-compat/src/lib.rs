//! The compatibility harness for [rucc](https://github.com/tamnd/rucc).
//!
//! The compiler repository holds the compiler. This one holds the code it is tested against
//! that somebody else wrote, the licenses that came with it, and this harness, which
//! preprocesses the same file with rucc and with a real compiler and reports what came out
//! different.
//!
//! The pieces:
//!
//! - [`corpus`] reads the manifests under `corpus/` and the register in `divergences.toml`.
//! - [`fetch`] downloads a vendored corpus, checks it against its hash and unpacks it.
//! - [`differ`] runs both preprocessors and compares the output three ways.
//! - [`pipeline`] takes the same corpora all the way through rucc on their own, which is the
//!   question no reference compiler can be asked: whether rucc parses, lowers, verifies and
//!   round trips its own IR.
//! - [`exec`] builds the programs and runs them, which is the only question that covers the
//!   back half of the compiler, since everything above it is a question about compiling and all
//!   of them can be green while the executable prints the wrong answer.
//! - [`lexer`] splits an output back into preprocessing tokens, which is what the first and
//!   strictest of those three comparisons is over.
//! - [`ledger`] remembers which cases were not green, so the next run can be pointed at those
//!   and nothing else.
//! - [`sandbox`] runs a program under a timeout and a memory limit and says how it ended.
//! - [`work`] runs several cases at once, since each of the three commands above is a map over
//!   cases that do not look at each other.
//! - [`sha256`] and [`toml`] are the two small things the above would otherwise depend on.

use std::path::{Path, PathBuf};

pub mod corpus;
pub mod differ;
pub mod exec;
pub mod fetch;
pub mod ledger;
pub mod lexer;
pub mod pipeline;
pub mod sandbox;
pub mod sha256;
pub mod toml;
pub mod work;

/// The repository root, found by walking up from `start` until something has a `corpus`
/// directory in it.
///
/// The harness reads manifests and writes reports, so it has to know where it is regardless
/// of which directory it was run from.
#[must_use]
pub fn repo_root(start: &Path) -> Option<PathBuf> {
    let mut at = Some(start);
    while let Some(dir) = at {
        if dir.join("corpus").is_dir() && dir.join("Cargo.toml").is_file() {
            return Some(dir.to_path_buf());
        }
        at = dir.parent();
    }
    None
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn the_root_is_found_from_inside_the_tree() {
        let here = Path::new(env!("CARGO_MANIFEST_DIR"));
        let root = repo_root(here).expect("this crate is inside the repository");
        assert!(root.join("corpus").is_dir());
    }

    #[test]
    fn somewhere_else_is_not_the_root() {
        assert_eq!(repo_root(Path::new("/")), None);
    }
}
