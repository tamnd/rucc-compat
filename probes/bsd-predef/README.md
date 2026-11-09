# bsd-predef

This probe compares the predefined macros of rucc with the reference GCC of each FreeBSD and NetBSD target. It also compares the answers to the feature queries (`__has_attribute`, `__has_builtin` and the others) that the installed headers ask.

## The rows and the sets

`rows.txt` has one row for each reference compiler and architecture: FreeBSD with GCC 15 and GCC 14, and NetBSD current, 11 and 10. Each has x86_64, aarch64 and riscv64. The personas and the GCC versions come from `personas.toml` of tamnd/rucc-bsd. rucc runs with the target and the `-fgnuc-version` of the row.

`flags.txt` has the flag sets. Each set is one run of `-dM -E` on an empty file. There are sets for the dialects, the optimization levels, PIC and PIE, the stack protector, `-m32`, the i386 boot code and the kernel flag lines.

## Where the reference files come from

No GitHub runner has a FreeBSD GCC or a NetBSD GCC, so the reference files are in `expected/`. The `bsd-reference` workflow made them, and the first lines of each file say how.

- FreeBSD: the FreeBSD 15.1-RELEASE BASIC-CI image boots under QEMU with KVM. `freebsd.sh` installs the cross GCC packages (`amd64-gcc15`, `aarch64-gcc15`, `riscv64-gcc15` and the `gcc14` set, 15.2.0_1 and 14.2.0_1) from `pkg+https://pkg.FreeBSD.org/FreeBSD:15:amd64/quarterly`. Each file records the package version and its SHA-256.
- NetBSD: `scripts/bsd/netbsd-tools.sh` builds the in-tree GCC with `build.sh tools` at the commit that tamnd/rucc-bsd pins for the branch. These are GCC 14.4.0 for current, 12.5.0 for 11 and 10.5.0 for 10. Each file records the commit.

To make the files again, run the `bsd-reference` workflow by hand. It fails if a file is different from the file in `expected/`. Download the artifacts and commit them.

## Running it

```
python3 probes/bsd-predef/predef.py check --rucc path/to/rucc
python3 probes/bsd-predef/predef.py check --rucc path/to/rucc --rows 'netbsd-11-*' -v
```

`accepted.txt` lists the known differences, each with the rucc issue that owns it. The check fails on a difference that is not in the list. It also fails on a line of the list that matches no difference, so the list cannot go stale. The `bsd probes` job of `ci.yml` runs the check on every pull request with rucc from its main branch.
