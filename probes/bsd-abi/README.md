# bsd-abi

This probe compares the type layouts of the installed FreeBSD and NetBSD headers under rucc with the reference GCC. For each type it compares the size and the alignment. For each named member of a struct or union that is not a bit field, it compares the offset.

## The rows

`rows.txt` has one row for each release and architecture: FreeBSD 15.1 and NetBSD 11.1, each on x86_64, aarch64 and riscv64. Each row names the release set that holds `usr/include` and the digest that the release publishes for it. `headers.txt` gives the headers to include. A header that a release does not have is left out of its row.

## How it works

`abi.py fetch` downloads the set of a row, checks its digest and unpacks `usr/include`.

`abi.py scan` runs on the reference. It preprocesses each header and finds each struct, union and enum with a tag, and each typedef, that a file under the sysroot defines. Each question (`sizeof`, `_Alignof` or `__builtin_offsetof`) becomes a char array whose size is the answer plus one. The reference compiles them all to one object file, and the sizes of the symbols are the answers. A question that the reference rejects, such as the size of an incomplete type, is left out.

`abi.py check` runs on rucc. It writes each answer as a `_Static_assert` and gives the file to rucc with `-fsyntax-only`, the target and the `-fgnuc-version` of the row. Each assertion that fails is a difference. rucc does not have to generate code for the architecture.

## Where the reference files come from

No GitHub runner has a BSD GCC, so the reference files are in `expected/`. The `bsd-reference` workflow made them, and the first lines of each file say how.

- FreeBSD: `freebsd.sh` runs in the FreeBSD 15.1-RELEASE BASIC-CI VM with the cross GCC 15.2.0 packages (`amd64-gcc15`, `aarch64-gcc15`, `riscv64-gcc15`) from `pkg+https://pkg.FreeBSD.org/FreeBSD:15:amd64/quarterly`. The headers come from `base.txz` of each architecture.
- NetBSD: the GCC 12.5.0 that `build.sh tools` builds at the netbsd-11 commit that tamnd/rucc-bsd pins. The headers come from `comp.tar.xz` (`comp.tgz` on riscv64) of NetBSD 11.1. The comp set does not hold the `usr/include/machine` link. The base set holds it, so `fetch` makes the link with the same target.

The check skips a row that has no file in `expected/`. To make the files again, run the `bsd-reference` workflow by hand. It fails if a file is different from the file in `expected/`. Download the artifacts and commit them.

## Running it

```
python3 probes/bsd-abi/abi.py fetch freebsd-15.1-x86_64 /tmp/bsd-sets
python3 probes/bsd-abi/abi.py check --rucc path/to/rucc --sets /tmp/bsd-sets --rows freebsd-15.1-x86_64 -v
```

`accepted.txt` lists the known differences, each with the rucc issue that owns it. At the moment it is empty. A line is a row glob, a question glob and the issue. The check fails on a difference that is not in the list. It also fails on a line of the list that matches no difference. The `bsd probes` job of `ci.yml` runs the check with rucc from its main branch.
