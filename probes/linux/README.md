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
