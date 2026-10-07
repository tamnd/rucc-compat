# Linux probes

These probes record what rucc does on Linux today. Each probe is one shell command: a program kind, a hardening flag, a distribution flag line, a TLS model, a debug option, a header, or a question that a build system asks. The probes are the evidence for the Linux plan in the rucc milestones L0 to L9 (tamnd/rucc#3275 to tamnd/rucc#3284).

## How to run them

```
probes/linux/run.sh native /path/to/rucc probes/linux/expected/x86_64-linux-gnu.txt
probes/linux/run.sh cross /path/to/rucc probes/linux/expected/cross.txt
```

Each probe prints one line: the name, the exit status and the standard output of the command. The error output goes to `log/<name>` in the scratch directory, because the words of a message change between releases and the result does not. When you give an expected file, the run compares the lines and fails if one is different. Lines that start with `#` are not compared.

The native probes need gcc, binutils, lld and the glibc development files. The cross probes fetch the sysroots into the rucc cache, so the first run needs the network. They also need `qemu-user` and the Ubuntu arm64 cross libc in `/usr/aarch64-linux-gnu`.

## When a result changes

A changed line is not a failure of the probe. It means that rucc changed. If the change is a fix, for example `fno-plt rc=1` becomes `fno-plt rc=0 hello linux 8 16`, update the expected file in the same pull request as the fix, and say which milestone item it closes. If the change is not expected, find the cause before you update the file.

The expected files say which machine and which rucc made them. A different distribution can give different lines, for example a different loader path or a different count of fortified calls. Make a new expected file for a new distribution. Do not edit the lines of another one.

## What the current results show

These are the faults that the expected files hold today, with the milestone that fixes each one.

| Probe | Result | Milestone |
|---|---|---|
| `fno-plt`, `leaf-fp`, `fhardened`, `grecord` | The flag is refused. | L3 |
| `ubuntu-flags`, `fedora-flags`, `arch-flags` | The flag line stops at a refused flag. | L3 |
| `ssp-macros` | No `__SSP_STRONG__` and no `__CET__`. | L3 |
| `build-id` | No build ID note. | L3 |
| `v-banner` | `-v` prints no "gcc version" line. | L2 |
| `print-libgcc`, `print-ld`, `multi-os` | A bare name, or the option is refused. | L2 |
| `MG`, `dumpspecs`, `gcc-toolchain`, `specs` | The option is refused. | L2 |
| `bigtls-dlopen` | "cannot allocate memory in static TLS block", because all TLS is initial exec. | L4 |
| `ftls-model`, `tls-gnu2` | The option is refused. | L4 |
| `coverage` | The program writes no `.gcda` file. | L5 |
| `tgmath`, `f128-macros` | `__builtin_tgmath` and `__builtin_huge_valf128` are not known. | L6 |
| `march-v3` | No `__AVX2__`, `__BMI2__` or `__FMA__`. | L6 |
| `x86_64-musl-pie`, `aarch64-musl-pie`, `x86_64-musl-static-pie` | The fetched musl sysroot links only with `-static`. | L7 |
| `x86_64-musl-cpu` | `__cpu_model` and `__cpu_indicator_init` are undefined in a musl link. | L7 |
| `riscv64-compile` | There is no RISC-V back end. | L9 |

`gsplit-dwarf`, `ubsan` and `asan` are refused on purpose, and each message names the reason. `openmp` is refused as an unknown option, and no milestone adds it.

## Build system fixtures

`buildsys/run.sh` is the test of milestone L2 item P3. Each fixture configures one project twice, once with `CC=gcc` and once with `CC=rucc`, and prints the lines of the two configurations that are different. Then it builds the project with each compiler and runs the result.

| Fixture | What it configures | The summary |
|---|---|---|
| `autotools` | A small autoconf, automake and libtool package. | The cache variables of `config.log`, and the compiler variables of `libtool --config`. |
| `cmake` | A small CMake project. | The compiler variables of CMake, and the result of each `check_*` call. |
| `meson` | A small meson project. | The compiler object: its id, version, headers, functions, arguments and attributes. |
| `zlib` | zlib 1.3.1. | What `configure` prints, the variables of the `Makefile`, and the changes to `zconf.h`. |
| `openssl` | OpenSSL 3.5.4. | `configdata.pm -o -m`. |
| `python` | Python 3.14.0. | `pyconfig.h`, and the compiler variables of the `Makefile`. |

Run it in a container that has the GCC that rucc copies, which is GCC 16. Arch Linux has it:

```
docker build -t rucc-buildsys - <<'END'
FROM archlinux:latest
RUN pacman -Syu --noconfirm --needed gcc make autoconf automake libtool cmake ninja meson perl python curl xz diffutils which pkgconf
END
docker run --rm -v /path/to/rucc-release:/opt/rucc:ro -v "$PWD/probes/linux/buildsys:/fx:ro" rucc-buildsys /fx/run.sh /opt/rucc/rucc /fx/expected/arch.txt
```

`FIXTURES="zlib cmake"` runs only some fixtures. `FULL=1` also builds OpenSSL and Python. The exit test of L2 is that each fixture writes the same configuration with each compiler, or that a line in `docs/DIVERGENCE.md` of tamnd/rucc names the difference.

`buildsys/expected/arch.txt` was made with rucc 0.28.0 and GCC 16.2.1 in Arch Linux. These are the differences in it:

| Fixture | Difference | Owner |
|---|---|---|
| `autotools` | `sys_lib_search_path_spec` has `/usr/lib64` and no GCC directory. | Fixed on main by tamnd/rucc#3309. |
| `zlib` | `configure` does not find GCC, so the shared library has no `-fPIC` and does not link. | Fixed on main by tamnd/rucc#3308. |
| `cmake` | The implicit link directories have the GCC directory last and `/usr/lib64` first. | tamnd/rucc#3326 |
| `cmake`, `meson` | The version is 16.0.0. GCC is 16.2.1. | `docs/DIVERGENCE.md` |
| `cmake` | The implicit include directories have no GCC directory, because the rucc headers are inside the binary. | `docs/DIVERGENCE.md` |
| `cmake` | The implicit link libraries have `librucc_builtins.a` and no `libatomic`. | `docs/DIVERGENCE.md` |
| `cmake`, `meson` | `-fno-plt` is refused. | L3 |
| `cmake`, `meson` | `-fopenmp` and `-fsanitize=address` are refused on purpose. | `docs/DIVERGENCE.md` |
| `python` | `_Py_HACL_CAN_COMPILE_VEC256` is not defined, because rucc has no AVX2 intrinsics. | L6 |

Make the file again with the next release, because main changes the `autotools` and `zlib` lines.
