# bsd-asm

This probe compares rucc with the reference GCC and GNU as on the `.S` files of a BSD kernel and its modules. Each file is preprocessed and assembled with the flags the kernel build gives it, by the reference driver and by rucc. The two objects are compared section by section, the way the `kernel-asm` corpus compares them (`crates/rucc-compat/src/elf.rs`).

## The rows

`rows.txt` has one row for each kernel configuration: FreeBSD 15.1 `GENERIC` on x86_64 at the moment. Each row names the source set that holds `usr/src/sys` and the digest that the release's `MANIFEST` gives for it. The units are the `.S` and `.s` files of the configuration's `SFILES` and those in the `SRCS` of each module that `sys/modules` builds for the architecture. A unit is named by its owner and its path under `sys/`, as `kernel:amd64/amd64/locore.S` or `linux64:amd64/linux/linux_support.S`.

## How it works

`asm.py scan` runs on the release. It configures the kernel with `config(8)`, makes the generated headers and links of the build directory, and builds the object of each `.S` unit. Then it walks `sys/modules` by the `SUBDIR` lists and does the same in each module that has a `.S` file, with `KERNBUILDDIR` set to the kernel. A wrapper in front of the reference compiler writes down each call that assembles a file, with its directory. scan makes each object again from those calls without the dependency flags, and describes it:

- each section with its type, flags, alignment, entry size and size, and a digest of each 256 bytes of its contents, so a difference can be placed without keeping the bytes;
- the relocations against each section, with a relocation against a local symbol read as one against its section plus the symbol's offset, since gas nearly always writes it that way;
- the symbols, but not the section and file symbols.

The contents of `.comment` and `.note.gnu.property` are not compared. The `.debug_` sections are left out, because what `-g` makes the assembler write names the directories of the build. The files of the build directories that a unit includes, such as `assym.inc` and the `opt_*.h` files, go into the expected file, and so do the links the build made, such as `machine`. The files of `sys/` that the units read are listed by path. Paths are written with `$S` for `sys/` and `$W` for the build directories.

`asm.py check` writes the build files and links into a scratch directory, runs rucc with the same flags in the same directory, with the target and the `-fgnuc-version` of the row, and describes rucc's object the same way. rucc preprocesses and assembles the file itself, as the reference driver did. The report gives each unit that differs with its differences, and counts the units by their first difference.

## Where the reference files come from

No GitHub runner has a FreeBSD GCC, so the reference files are in `expected/`. The `bsd-reference` workflow made them, and the first lines of each file say how. `freebsd.sh` runs in the FreeBSD 15.1-RELEASE BASIC-CI VM with the cross GCC 15.2.0 package `amd64-gcc15` and its binutils, from `pkg+https://pkg.FreeBSD.org/FreeBSD:15:amd64/quarterly`. The sources come from `src.txz` of the release.

The check skips a row that has no file in `expected/`. To make the files again, run the `bsd-reference` workflow by hand. It fails if a file is different from the file in `expected/`. Download the artifacts and commit them.

## Running it

```
python3 probes/bsd-asm/asm.py fetch freebsd-15.1-x86_64 /tmp/bsd-src
python3 probes/bsd-asm/asm.py check --rucc path/to/rucc --src /tmp/bsd-src -v
python3 probes/bsd-asm/asm.py check --rucc path/to/rucc --src /tmp/bsd-src --units 'kernel:*locore*' -v
```

`fetch` downloads `src.txz` (about 250 MB), checks its digest and unpacks only the files of `sys/` that the expected file lists.

`accepted.txt` lists the known differences, each with the rucc issue that owns it. A line is a row glob, a unit glob and the issue. The check fails on a unit that differs and is not in the list. It also fails on a line of the list that matches no unit that differs. The `bsd probes` job of `ci.yml` runs the check with rucc from its main branch.
