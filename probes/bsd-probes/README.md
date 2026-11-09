# bsd-probes

This probe asks rucc the questions that the BSD builds ask the compiler, and compares the answers with the reference GCC of each FreeBSD and NetBSD target. It is the standalone form of `rb probes` of tamnd/rucc-bsd.

## What it asks

`probes.txt` has the probes. Each is one run of the compiler.

- `bsd.compiler.mk` of FreeBSD: `--version` and `-v`, read as `COMPILER_TYPE` and `COMPILER_VERSION`, `echo __FreeBSD_cc_version | cc -E -` and `-print-resource-dir`.
- Configure scripts and libtool: `-dumpversion`, `-dumpfullversion`, `-dumpmachine`, the `-print-*` queries, `-V` and `-qversion`.
- The feature tests of `rb probes` (`__has_extension`, `__has_feature`, `__has_builtin` and `__has_attribute`) under `-std=gnu11` and `-std=gnu99`.
- `-dM -E` under the flags that change what the mk files and the headers test. The probe compares only the macros of `macros.txt`, because bsd-predef compares all of them.
- The code flags of the kernel and boot command lines, each on its own, on a one-line unit.
- The `freebsd_kprintf` format of the FreeBSD GCC ports (`%b`, `%D`, `%r` and `%y`), on the FreeBSD rows only. `kprintf.txt` has one call for each conversion, each length modifier and flag, and each wrong argument. The probe compares the exit status and the text of each warning, without the place and the option name. One group declares the function with `__printf__` and builds with `-D__printf__=__freebsd_kprintf__`, as the FreeBSD kernel does.
- `-Werror FLAG` for each warning flag of `warnings.txt`. These are the flags of FreeBSD's `bsd.sys.mk`, `kern.mk` and `kern.pre.mk` and of NetBSD's `bsd.sys.mk` and `bsd.own.mk`.

A probe compares what the build reads, not the whole output. The reads column of `probes.txt` says what that is for each probe. For example, the `-print-prog-name=ld` probe compares the exit status and the last part of the path, because the path is different on each host.

The rows are the rows of bsd-predef (`../bsd-predef/rows.txt`). rucc runs with the target and the `-fgnuc-version` of the row.

## Where the reference files come from

The `bsd-reference` workflow makes the files in `expected/` on the same systems as bsd-predef: the cross GCC packages in the FreeBSD 15.1 VM (`freebsd.sh`), and the in-tree GCC that `build.sh tools` builds for each pinned NetBSD branch. The first lines of each file say how it was made.

## Running it

```
python3 probes/bsd-probes/probes.py check --rucc path/to/rucc
python3 probes/bsd-probes/probes.py check --rucc path/to/rucc --rows 'netbsd-11-*' -v
```

`accepted.txt` lists the known differences, each with the rucc issue that owns it. The check fails on a difference that is not in the list, and on a line of the list that matches no difference. The `bsd probes` job of `ci.yml` runs the check with rucc from its main branch.
