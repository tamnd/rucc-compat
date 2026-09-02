//! Fetching a vendored corpus, and refusing to unpack one we cannot recognise.

use std::fs;
use std::path::{Path, PathBuf};
use std::process::Command;

use crate::corpus::{Corpus, Source, Tarball};
use crate::sha256;
use crate::toml::Error;

/// What a fetch did.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Fetched {
    /// The digest of the bytes that were downloaded.
    pub sha256: String,
    /// The tree, once it is unpacked. Absent in `--record` mode, which unpacks nothing.
    pub tree: Option<PathBuf>,
    /// Whether the tarball was already there and was not downloaded again.
    pub cached: bool,
}

/// Downloads, verifies and unpacks a corpus.
///
/// With `record` set it stops after the hash and prints nothing to disk that git would see,
/// which is how a new manifest gets the digest a person then checks against upstream.
///
/// # Errors
///
/// When the corpus is not a tarball, when the download fails, when the digest is not the one
/// the manifest names, or when the unpacked tree does not carry its license file.
pub fn fetch(repo: &Path, corpus: &Corpus, record: bool) -> Result<Fetched, Error> {
    let Source::Tarball(tarball) = &corpus.source else {
        return Err(Error {
            message: format!("{}: an installed corpus has nothing to fetch", corpus.name),
        });
    };
    let into = repo.join("vendor").join(&corpus.name);
    fs::create_dir_all(&into).map_err(|e| fail(&into, &e))?;
    let archive = into.join(file_name(&tarball.upstream));

    let cached = archive.is_file();
    if !cached {
        download(&tarball.upstream, &archive)?;
    }
    let bytes = fs::read(&archive).map_err(|e| fail(&archive, &e))?;
    let digest = sha256::hex(&bytes);

    if record {
        return Ok(Fetched { sha256: digest, tree: None, cached });
    }
    if !tarball.is_recorded() {
        return Err(Error {
            message: format!(
                "{}: the manifest has no verified sha256, so there is nothing to check this download against. It came out as {digest}. Check that against what upstream publishes and put it in corpus/{}/corpus.toml.",
                corpus.name, corpus.name
            ),
        });
    }
    if digest != tarball.sha256 {
        // The file stays where it is. Deleting the evidence of a bad download is how a
        // mismatch turns into a retry loop that eventually succeeds against nothing.
        return Err(Error {
            message: format!(
                "{}: the download is not the tarball the manifest names.\n  manifest {}\n  download {digest}\n  file     {}",
                corpus.name,
                tarball.sha256,
                archive.display()
            ),
        });
    }
    unpack(&archive, &into, &tarball.extract)?;
    let tree = corpus.tree(repo);
    if !tree.is_dir() {
        return Err(Error {
            message: format!(
                "{}: the tarball did not unpack into `{}`, which is what `root` says",
                corpus.name, tarball.root
            ),
        });
    }
    licensed(&into, tarball, &corpus.name)?;
    Ok(Fetched { sha256: digest, tree: Some(tree), cached })
}

/// The license text has to be in the tree we keep, at the path the manifest names.
fn licensed(into: &Path, tarball: &Tarball, name: &str) -> Result<(), Error> {
    let license = into.join(&tarball.license_file);
    if license.is_file() {
        return Ok(());
    }
    Err(Error {
        message: format!(
            "{name}: the unpacked tree has no `{}` in it. The manifest says this code is {}, and code we cannot show the license of is code we cannot vendor.",
            tarball.license_file, tarball.license
        ),
    })
}

fn download(url: &str, into: &Path) -> Result<(), Error> {
    // Written to a `.part` and moved, so that an interrupted download is never mistaken for a
    // cached one on the next run. A truncated tarball that sits in the cache is a hash
    // mismatch every time and no obvious reason why.
    let part = PathBuf::from(format!("{}.part", into.display()));
    let status = Command::new("curl")
        .args(["--fail", "--location", "--silent", "--show-error", "--retry", "3", "--output"])
        .arg(&part)
        .arg(url)
        .status()
        .map_err(|e| Error { message: format!("curl: {e}") })?;
    if !status.success() {
        let _ = fs::remove_file(&part);
        return Err(Error { message: format!("curl failed on {url}") });
    }
    fs::rename(&part, into).map_err(|e| fail(into, &e))
}

/// Unpacks the archive, or the named paths inside it when the manifest names any.
///
/// `tar` takes the paths to extract after the options and reads the whole archive either way,
/// so this is about what lands on disk rather than about how long it takes. For a tarball that
/// is a whole compiler and a corpus that is one directory inside it, that is the difference
/// between eight hundred megabytes and eight.
fn unpack(archive: &Path, into: &Path, only: &[String]) -> Result<(), Error> {
    let status = Command::new("tar")
        .arg("-xf")
        .arg(archive)
        .arg("-C")
        .arg(into)
        .args(only)
        .status()
        .map_err(|e| Error { message: format!("tar: {e}") })?;
    if status.success() {
        return Ok(());
    }
    Err(Error { message: format!("tar failed on {}", archive.display()) })
}

/// The last path element of a URL, which is what the tarball is called.
fn file_name(url: &str) -> String {
    url.rsplit('/').next().unwrap_or("archive.tar").to_owned()
}

fn fail(path: &Path, e: &std::io::Error) -> Error {
    Error { message: format!("{}: {e}", path.display()) }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::corpus::{Unit, UnitKind};

    fn corpus(source: Source) -> Corpus {
        Corpus {
            name: "t".to_owned(),
            summary: "s".to_owned(),
            source,
            probe: Vec::new(),
            units: vec![Unit {
                name: "amalgamation".to_owned(),
                kind: UnitKind::Source,
                files: vec!["a.c".to_owned()],
                dir: None,
                skip: Vec::new(),
                flags: Vec::new(),
            }],
            excluded: Vec::new(),
        }
    }

    #[test]
    fn an_installed_corpus_says_it_has_nothing_to_fetch() {
        let e = fetch(Path::new("/nowhere"), &corpus(Source::Installed), false).unwrap_err();
        assert!(e.message.contains("nothing to fetch"), "{}", e.message);
    }

    #[test]
    fn the_file_name_is_the_last_element_of_the_url() {
        assert_eq!(
            file_name("https://sqlite.org/2026/sqlite-autoconf-3530400.tar.gz"),
            "sqlite-autoconf-3530400.tar.gz"
        );
        assert_eq!(file_name("t.tar.xz"), "t.tar.xz");
    }

    #[test]
    fn a_tree_with_no_license_in_it_is_refused_and_says_which_file() {
        let dir = std::env::temp_dir().join(format!("rucc-compat-license-{}", std::process::id()));
        let _ = fs::remove_dir_all(&dir);
        fs::create_dir_all(dir.join("t-1")).unwrap();
        let tarball = Tarball {
            upstream: "https://example.invalid/t.tar.gz".to_owned(),
            version: "1".to_owned(),
            sha256: "0".repeat(64),
            license: "MIT".to_owned(),
            license_file: "t-1/COPYING".to_owned(),
            root: "t-1".to_owned(),
            extract: Vec::new(),
        };
        let e = licensed(&dir, &tarball, "t").unwrap_err();
        assert!(e.message.contains("t-1/COPYING"), "{}", e.message);
        fs::write(dir.join("t-1/COPYING"), "a license").unwrap();
        assert!(licensed(&dir, &tarball, "t").is_ok());
        let _ = fs::remove_dir_all(&dir);
    }
}
