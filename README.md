# rucc-compat

Compatibility for [rucc](https://github.com/tamnd/rucc), checked against a real GCC over real code rather than against the standard.

The compiler repository holds the compiler and nothing else. This one holds everything the compiler is tested against that somebody else wrote: the corpora, the licenses that come with them, and the harness that runs them. Keeping them apart is what stops a clone of the compiler from being a clone of glibc.

## The differential

`rucc-compat run` preprocesses the same file with `rucc -E` and with `cc -E`, normalizes both outputs the same way, and reports every difference. That is the exit criterion for milestone M1 of the compiler, stated as a program that can be run rather than as a paragraph somebody has to believe.

```
cargo build --release
./target/release/rucc-compat list
./target/release/rucc-compat run glibc --rucc ../rucc/target/release/rucc
./target/release/rucc-compat run sqlite --unit headers --report
./target/release/rucc-compat run --markers
```

Before either compiler runs, the harness makes them agree about everything a difference must not come from. It asks the reference where it looks for headers, what GCC version it claims to be and what language it thinks it is compiling, and passes all three to the compiler under test. The last two are not cosmetic. glibc gates most of `sys/cdefs.h` on `__GNUC_PREREQ`, and `stddef.h` and `uchar.h` gate on `__STDC_VERSION__`, so two compilers that disagree about either one are handed different headers and are no longer preprocessing the same program.

Both outputs are read back as preprocessing tokens and compared three ways, weakest last.

- `token-text` is the tokens themselves, in order. Whitespace does not count, and a missing space does, because `int x` and `intx` are not the same two tokens. This is the property that decides whether the output still compiles to the same program, and a difference here is a bug.
- `spacing` is where the spaces and the line breaks are, once runs of spaces are one space. Same tokens, printed differently.
- `markers` is the line markers, and it is only compared under `--markers`. It is the weakest of the three and it is reported on its own, because a marker difference and a token difference are not the same kind of bug and lumping them together hides the one that matters.

Every difference is a failure unless it is in the register. Nothing is normalized away quietly to make a number look better.

A case the reference compiler cannot preprocess either is reported as not compared rather than as a pass, which is what most of a header sweep turns out to be: headers that were never meant to be included on their own.

## The pipeline check

`rucc-compat check` asks a different question, one no reference compiler can answer: whether rucc gets a corpus through its own front end, its own lowering and its own verifier, and whether the IR it printed reads back as the IR it printed.

```
./target/release/rucc-compat check c-testsuite --rucc ../rucc/target/release/rucc
./target/release/rucc-compat check tcc --unit tests2 --report
```

Each case is three runs of the compiler. `--emit=tast` is parsing and semantic analysis. `--emit=ir` is lowering, and the verifier runs on the way out of it. Then the IR from the second run goes back in as input, which parses it and verifies it a second time, and the two texts have to be the same byte for byte.

The round trip is the step worth explaining. A printer and a parser that disagree can each look right on its own, and a text that does not survive being read back is not a record of what the compiler decided. Comparing the second print against the first is the cheapest way to find that out and it costs one more run of a compiler that is already fast.

Each manifest carries the cases that do not get through yet, as `[[exclude]]` entries. Every one of them names the issue that will take it off the list, and a manifest with an exclusion that has no issue on it does not load. The list is checked for going stale on every whole run: a case that starts passing while its entry is still there fails the run, and so does an entry naming a case the corpus does not have. That is what stops an exclusion list from becoming the place a regression goes to be quiet. An entry can carry a `when` naming the operating systems it applies to, for the gaps that are one platform's ABI rather than the compiler's everywhere.

## The corpora

Each directory under `corpus/` describes one body of code, in a `corpus.toml` that says where it comes from, what license it carries and what to do with it. There are two kinds and the difference is where the code lives.

An installed corpus is the header set of the machine the harness runs on, which is how the glibc and musl comparisons work: on an Ubuntu runner `/usr/include` is glibc, in an Alpine container it is musl, and neither has to be fetched or configured. This is also the honest test, because those are the headers a user will actually compile against. A corpus like that names a file that has to exist for it to mean anything, so a run on a glibc machine skips the musl corpus instead of comparing glibc against itself under the wrong name.

A vendored corpus is a tarball at a pinned version, fetched by `rucc-compat fetch` and checked against the sha256 in the manifest before it is unpacked into `vendor/`. The tarball is not committed. Its license file is, at the path the manifest names, and a fetch that unpacks a tree without that file fails. `vendor/` is ignored by git, so a corpus is reproducible from the manifest and nothing large ever lands in the history.

A corpus is made of named units, and `--unit` runs one of them. That is how the forty standard headers can be a quick check on every commit while the sweep over every header the machine has is something the nightly run does.

Adding one is a `corpus.toml` and nothing else. `CONTRIBUTING.md` says what the fields mean.

## The register

`divergences.toml` is the list of differences we have decided to live with, each with the reason written next to it and the issue it waits on. Anything in it is counted and not reported. Anything else fails the run.

The file is deliberately awkward to add to. A divergence with no reason on it does not load at all, so saying "we behave differently here and this is why" has to be a diff somebody wrote and somebody else read.

## Where it stands

The sqlite corpus passes on macOS. All four cases, the eight megabyte amalgamation included, preprocess the same as Apple's clang, and the only difference left is one the register covers: the availability attribute, which Apple puts on nearly every declaration and which rucc drops because it does not implement it yet.

Getting there took three compiler fixes, all found by running this and none of them guessed: Apple's spelling of the architecture, a signed `wint_t` on Darwin, and `__building_module`. The glibc and musl corpora are green too now, over their standard and posix units, measured against GCC 16 rather than against the GCC 13 the runner ships. Moving the reference is what found the last four compiler fixes: `__CHAR8_TYPE__` missing in C23, `__STDC_NO_VLA__` claimed falsely over a header that changes a declaration on it, a `#pragma` printing with the indent space it was written with, and a space inserted between two tokens the person wrote next to each other.

The pipeline check runs over two corpora. On macOS, c-testsuite is at 208 of 220 and tcc tests2 is at 74 of 87, with twelve and thirteen exclusions covering the rest, and the twenty five of them point at twelve issues between them. On Linux it is one case worse than the Mac, a structure passed in memory to a variadic function, which is what the `when` field on an exclusion is for. It used to be sixty worse, all for one reason: rucc claimed to be GCC 4.2.1 by default, so glibc took the branch of `bits/floatn-common.h` that typedefs `_Float32` and the rest over rucc's own keywords, and every case that included a system header stopped on that line. tamnd/rucc#142 raised the claim and the job is no longer advisory. Three of the issues behind the exclusions came out of the round trip and the verifier rather than out of a diagnostic: a stack restore whose saved pointer does not reach it, a flexible array member initializer that makes an image larger than the global it fills, and an identifier that is not ASCII surviving the printer and not the parser. None of the three shows up as an error message, and none of them would have been found by comparing preprocessor output.

Results land in `results/` as markdown, one file per corpus, written by `run --report`. CI keeps its own as an artifact, because a result is about the machine that produced it.

## License

The harness is MIT or Apache-2.0, at your option. Vendored code keeps its own license, which travels with the tree it came from and is named in the manifest that fetched it.
