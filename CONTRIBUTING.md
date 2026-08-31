# Contributing

## Adding a corpus

A corpus is a directory under `corpus/` with a `corpus.toml` in it. The directory name is the name the harness knows it by.

```toml
name = "sqlite"
summary = "The SQLite amalgamation, one translation unit of about eight megabytes."
source = "tarball"
upstream = "https://sqlite.org/2026/sqlite-autoconf-3530400.tar.gz"
version = "3.53.4"
sha256 = "0e9483900e92cd5de8fd48d16bf9200145a61f7fd5be542a5ac81d8a9516eb9c"
license = "blessing"
license-file = "sqlite-autoconf-3530400/sqlite3.h"
root = "sqlite-autoconf-3530400"

[[unit]]
name = "amalgamation"
kind = "source"
files = ["sqlite3.c"]
flags = ["-DSQLITE_THREADSAFE=0"]
```

The fields:

- `name` and `summary`. The summary says why this corpus is worth the time it costs, in one sentence.
- `source` is `tarball` or `installed`. A tarball is fetched and verified. An installed corpus is the header set of the machine the harness runs on, and has no upstream and no hash.
- `probe` is optional and is a file, or a list of files, one of which has to exist for the corpus to apply. An installed corpus needs one, because glibc and musl are never the same machine and a corpus that quietly compares the wrong headers is worse than one that does not run. Write a list when the same library is laid out differently by different distributions, which is the usual case: Debian and Ubuntu put half of glibc under an architecture triplet and a probe that only knows the plain path skips the corpus on every machine that has it.
- `upstream`, `version` and `sha256` for a tarball. The version is in the URL and in the directory name, and it is pinned so that a run today and a run in a year compare the same bytes.
- `license` is the SPDX identifier. `license-file` is the path inside the tarball to the license text that came with it, and a fetch that unpacks a tree without that file fails, because vendored code with no license in it is not code we can keep. Some projects have no separate license file and put the terms at the top of every source file, and then this points at one of those files.
- `root` is the directory the tarball unpacks into.
- One `[[unit]]` block per thing to preprocess, each with a `name` that `--unit` selects and that the case names begin with. `kind = "source"` names files. `kind = "headers"` takes the headers in `files`, or every header under `dir`, and includes each one from a file of its own, which is how a header set is checked for standing up on its own. `skip` drops paths under `dir`, and each one wants a comment next to it saying why. `flags` are passed to both compilers unchanged, and a relative include path in them is resolved against the tree.

Keep the units small and named for what they are. A unit is the unit of a CI job: the standard headers are worth running on every commit and a sweep over every header the machine has is worth running once a night, and that is only possible if they are not the same unit.

### Recording the hash

`rucc-compat fetch <name> --record` downloads the tarball, prints the sha256 it computed and unpacks nothing. Check that against what upstream publishes, then commit it. A hash recorded by a machine nobody checked is not a hash, it is a record of what that machine downloaded once, which is exactly what an interrupted download looks like.

A manifest whose `sha256` is `unrecorded` loads, and every command that would use the tree refuses to run. That is the state a corpus sits in between somebody proposing it and somebody verifying it.

## Adding a divergence

`divergences.toml` is the register of differences we accept for now.

```toml
[[divergence]]
id = "darwin-availability"
what = "A declaration in an Apple system header comes out without its availability attribute."
why = "The attribute is not implemented, so __has_attribute answers no and the header takes its fallback path."
issue = "https://github.com/tamnd/rucc/issues/31"
rule = "token-text"
matches = "__attribute__((availability("
```

`id`, `what`, `why`, `issue` and `rule` are required and the file does not load without them. `rule` names the comparison rule the entry suppresses, and the rules are in the harness rather than in the file, so an entry cannot quietly widen itself into ignoring something else. There are three rules and they are `token-text`, `spacing` and `markers`, in that order of severity.

`corpus`, `unit` and `matches` say where the entry applies, and every one an entry states has to hold for it to cover a difference. `matches` is text that has to appear in the differing line, either in what we printed or in what the reference printed. A `token-text` entry has to state at least one of the three, and the file does not load otherwise: an unscoped one would silence the rule that decides whether the output still compiles to the same program, in every corpus at once, and the run would go green while finding nothing.

An entry is a promise to remove the entry. When the issue closes, the entry goes with it and the run gets stricter on its own.

## The harness

`cargo test` is the whole check, and `cargo fmt --all --check` and `cargo clippy --workspace --all-targets` are what CI adds to it. The crate is one binary and one library:

- `toml.rs` and `sha256.rs` are the two things a dependency would otherwise provide.
- `corpus.rs` reads the manifests and the register.
- `fetch.rs` downloads, verifies and unpacks.
- `lexer.rs` splits an output back into preprocessing tokens.
- `differ.rs` runs both compilers and compares.
- `main.rs` is the command line and nothing else.

Before either compiler runs, the harness makes them agree about the things a difference must not come from. It asks the reference for its system include directories and passes them to the compiler under test as `-isystem`, so the two cannot be reading different headers. It asks the reference what `__GNUC__`, `__GNUC_MINOR__` and `__GNUC_PATCHLEVEL__` it defines and passes that as `-fgnuc-version=`, so the two cannot be handed different halves of a header that gates on `__GNUC_PREREQ`. glibc gates most of `sys/cdefs.h` that way, and a run without this measures the version claim rather than the preprocessor.

Both are read off the reference rather than written down anywhere, because a value written down is a value that is right on the machine somebody wrote it on.

## Style

The same rules as the compiler repository. Plain English, no em dashes, no hard wrapped prose, comments that say why rather than what. The harness has no dependencies, for the same reason the compiler has none: a test harness that cannot build is a test harness nobody runs.
