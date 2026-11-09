# bsd-pp

This probe compares the preprocessor output of the installed FreeBSD and NetBSD headers under rucc with the reference GCC. A BSD header chooses its declarations with the macros of the compiler: `__GNUC__`, `__OPTIMIZE__`, `__STDC_VERSION__`, `_KERNEL` and many more. If rucc and GCC take a different branch, a unit sees different declarations. bsd-predef compares the macros one by one. This probe compares what the headers make of them.

## The rows and the units

The rows are the rows of bsd-abi (`../bsd-abi/rows.txt`): FreeBSD 15.1 and NetBSD 11.1, each on x86_64, aarch64 and riscv64. The headers come from the same release sets, and `abi.py fetch` unpacks them.

A unit is one header in one mode. `modes.txt` gives the modes:

- `world` is the C of the base system. It has the `-std` of each system's `bsd.sys.mk` and `-O2`, on the headers in `usr/include`, `sys` and `arpa`.
- `kernel` is the C of the kernel. It adds `-D_KERNEL` and `-ffreestanding`, on the headers in `sys`.

## How it works

For each unit, `pp.py` runs `-E` on `#include <HEADER>` with `--sysroot` set to the set of the row. It keeps the text that comes from files under the sysroot, and it uses the line markers to find them. The text from the compiler's own headers (`stddef.h`, `stdarg.h` and the others) is left out, because each compiler has its own. The text is cut into C tokens, so spaces and line breaks are not compared.

The answer of a unit is the exit status, the number of tokens and a digest of the tokens. When the exit status is not 0, only the status is compared. The names of the files are not compared, because GCC marks a file that gives no text and rucc does not.

`pp.py dump` runs on the reference and writes the answers. `pp.py check` runs rucc with the target and the `-fgnuc-version` of each row, and compares. `--keep DIR` writes the files and the tokens of each unit under DIR, so a difference can be read with `diff`. The units run at the same time, one for each CPU.

## Where the reference files come from

No GitHub runner has a BSD GCC, so the reference files are in `expected/`. The `bsd-reference` workflow made them, and the first lines of each file say how.

- FreeBSD: `freebsd.sh` runs in the FreeBSD 15.1-RELEASE BASIC-CI VM with the cross GCC 15.2.0 packages (`amd64-gcc15`, `aarch64-gcc15`, `riscv64-gcc15`).
- NetBSD: the GCC 12.5.0 that `build.sh tools` builds at the netbsd-11 commit that tamnd/rucc-bsd pins.

The check skips a row that has no file in `expected/`. To make the files again, run the `bsd-reference` workflow by hand, download the artifacts and commit them.

## Running it

```
python3 probes/bsd-abi/abi.py fetch freebsd-15.1-x86_64 /tmp/bsd-sets
python3 probes/bsd-pp/pp.py check --rucc path/to/rucc --sets /tmp/bsd-sets --rows freebsd-15.1-x86_64 --keep /tmp/pp-rucc -v
python3 probes/bsd-pp/pp.py dump freebsd-15.1-x86_64 --cc gcc --sysroot /tmp/bsd-sets/freebsd-15.1-x86_64 -o /tmp/pp-gcc.txt --keep /tmp/pp-gcc
diff /tmp/pp-gcc/freebsd-15.1-x86_64/world/aio.h.txt /tmp/pp-rucc/freebsd-15.1-x86_64/world/aio.h.txt
```

`accepted.txt` lists the known differences, each with the rucc issue that owns it. A line is a row glob, a unit glob and the issue. The check fails on a difference that is not in the list. It also fails on a line of the list that matches no difference. The `bsd probes` job of `ci.yml` runs the check with rucc from its main branch.

## Is the method sound

A host GCC is not a reference for a BSD target, but it tests the method. GCC 16 on Linux and rucc for the Linux target, on the FreeBSD 15.1 x86_64 set, give the same exit status on all 1007 units. 789 units have the same tokens. Of the other 218, 214 differ because Ubuntu's GCC turns on `_FORTIFY_SOURCE` at `-O2` and so takes the `ssp/ssp.h` branches. The last 4 differ because of the compiler's own headers. GCC's `omp.h` hides the one in the set. GCC's `stddef.h` defines `__size_t` as an empty guard macro, so `typedef __uint64_t __size_t;` in `sys/_types.h` loses its name under GCC and not under rucc.
