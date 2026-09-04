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

## The execution check

`rucc-compat exec` is the one that runs the program. Everything above it is a claim about compiling, and a compiler that gets a file through the front end, the lowering and the verifier has still not been asked the only question a user has, which is whether the executable does what the C said.

```
./target/release/rucc-compat exec c-testsuite --rucc ../rucc/target/release/rucc
./target/release/rucc-compat exec chibicc --report
```

Every case is built three ways, because the three depend on different amounts of the compiler. `-S` and then the system assembler and linker needs no encoder, no object writer and no relocations, and what it produces in the middle is text somebody can read. `-c` and then the system linker is the encoder and the relocations and nothing else. The driver on its own is the whole of it, including finding a linker. A case that passes one way and fails another is reported as exactly that, which is what checks the encoder against the assembly printer without anybody writing a byte level differential: the two come out of one instruction description, so a disagreement between them is a disagreement inside that description and it turns up as a wrong answer rather than as a diff nobody reads.

How a run is judged is the corpus's business and is one of three. A self checking program says so in its exit status. A recorded corpus ships the output each program is supposed to print. Anything else is compared against what the same program built by the reference compiler does, which is the oracle that needs no corpus support at all.

The outcomes are reported separately rather than as a pass rate, because a compiler that is wrong and a compiler that is unfinished are not the same news and a summary that adds them together hides the one that matters. A case that does not build, one that builds and gives the wrong answer, one that dies on a signal and one that runs out of time are four different lines. Each case gets a fresh working directory, a timeout and a memory limit, and a program killed by a signal is reported as a signal rather than as whatever exit status a shell would have turned it into.

The exclusions work the way the pipeline check's do, in a separate `[[exec-exclude]]` list, and carry two things more. The first is the outcome they cover: an entry that says a case does not build and a case that now builds and prints the wrong answer are not the same entry, so the run fails rather than counting it as covered. The second is an optional `opt`, naming the optimization levels the entry speaks at, for the gaps that are one level's rather than every level's.

Every level is run, and not as a setting on one answer. `-O0` and `-O2` run different passes over different code, and the headers change underneath them as well, since glibc defines a family of functions inline behind `__OPTIMIZE__` being set and `__OPTIMIZE_SIZE__` not being set. A sweep at one level says nothing about the other five.

## How long a sweep takes

Every one of the three commands is a map over cases that do not look at each other. Each case gets a scratch directory named after itself, reads nothing another case wrote, and the only things any of them share are the two compiler binaries, which nobody writes to. So they run several at a time, and `--jobs N` says how many.

The default is half of what the machine reports, at least one. Not all of it, for two reasons that are both about the answer being right rather than about being polite. A case in `exec` is run against a wall clock, and a machine with more work in flight than it can do makes a slow program slower, so a run that took every core would report oversubscription as a timeout and send somebody looking for a performance bug that is not there. And the machines these sweeps run on have a CI runner on them, so a harness that took the whole machine would be measuring a compiler that is being starved.

`--jobs 1` is the serial path, and a real one rather than a pool of one, for when a number is being held against an older number.

The order of the report does not depend on this. Answers come back in the order the cases were in whatever the setting is, because a report whose rows move between two runs of the same corpus is a report nobody can diff.

The other half of it is running fewer cases. `--only PATTERN` keeps the cases whose name contains the pattern and can be given more than once, which is how somebody fixing structure returns asks for the seventeen chibicc cases rather than the six hundred and thirty nine in c-testsuite. `--failed` keeps the cases the last run of the same command on this machine did not call green, which is the set a fix is usually aimed at. Both at once is the overlap and not the sum.

```
./target/release/rucc-compat exec gcc-torture --failed
./target/release/rucc-compat exec chibicc --only test/cast --only test/struct
```

What `--failed` reads is a small file under `target/last`, one line per case that was not green, written by every run. It is under `target` because it is a fact about this machine and this checkout rather than a report, and the reports still go to `results/`. A narrowed run updates only the rows for the cases it reached and leaves the rest where they were, because a run that saw thirty cases has no opinion about the other two thousand. That is what makes asking twice in a row mean something: the second one asks about what the first one did not fix.

Green there means what green means for the run as a whole, which is neither a failure nor a stale exclusion. An excluded case is not green, because an exclusion is a case that is still broken and is where the work is. An exclusion that has started passing is not green either, because that is a thing somebody has to act on and a rerun that called it green would be the one rerun where the only check for it cannot fire.

A run narrowed by any of `--unit`, `--only`, `--failed` or `--limit` is not a whole corpus, so it does not check for exclusions that name a case nobody ran. That check needs the whole corpus and stays where it belongs, in the sweep.

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

The pipeline check runs over five corpora. On macOS, c-testsuite is at 218 of 220, tcc tests2 is at 82 of 87, chibicc is at 18 of 18, sqlite is at 4 of 4 and the gcc.c-torture execution suite is at 1186 of 1773, with five hundred and eighty seven exclusions covering the rest and pointing at ten issues between them. Linux gives the same numbers. It used to be one case worse, a structure passed in memory to a variadic function, which is a gap that has since been closed, and before that it was sixty worse, all for one reason: rucc claimed to be GCC 4.2.1 by default, so glibc took the branch of `bits/floatn-common.h` that typedefs `_Float32` and the rest over rucc's own keywords, and every case that included a system header stopped on that line. tamnd/rucc#142 raised the claim and the job is no longer advisory. Four of the compiler bugs behind these lists came out of the round trip and the verifier rather than out of a diagnostic, which is to say that no error message would have found them: a stack restore whose saved pointer does not reach it, a flexible array member initializer that makes an image larger than the global it fills, a name that is not ASCII surviving the printer and not the parser, and an object of no size at all printing in a form the reader would not take. All four are fixed.

The chibicc corpus is a different shape from the collections. It is forty one programs written one per language feature by somebody building a C compiler, so the cases sit on the parts that are easy to get wrong and nowhere else, and the overlap with a collection of programs is small. Twenty three of them are skipped because gcc 16 refuses them too: chibicc is from 2020 and gcc 14 turned four permissive rules into errors, so more than half of the suite is on the wrong side of a change that came after it. The eighteen that are left found two things in a week. `#pragma once` in the file named on the command line was warned about and then dropped, which broke the one file in the suite that includes itself, and `-E` does not mark an expansion of a macro defined in a system header, which is the register's newest entry.

The gcc.c-torture execution suite is the largest of them and the newest here. It is 1907 programs written over forty years, every one of them a bug report that was once a wrong answer from a released compiler, reduced and kept. `spec/14-target-ladder.md` section 14.1 names it as part of rung 0 of the compiler's target ladder, and the exit criterion there is every one of these programs that does not need an extension nobody has written yet, with the list of the rest checked in and shrinking. This manifest is that list. One hundred and thirty four files are skipped rather than excluded: one hundred and eleven because gcc 16 refuses them itself, mostly on the three permissive rules gcc 14 promoted to errors, and twenty three because they are GNU's nested functions, which this compiler has decided it will not have. The six hundred and twenty three exclusions point at twelve issues, and five hundred and eight of them are one thing, a call to a `__builtin_` the compiler has never heard of.

The tarball this comes in is the whole of GCC, a hundred and seven megabytes, and the tests are eight. The `extract` field in a manifest is what keeps the other ninety nine off every machine that runs the harness.

The execution check is younger and its number is the one that moves. c-testsuite is at 202 of 220 on a linux x86-64 host, over all three build paths, measured against gcc 16.2.0. It was at 95 a fortnight ago, and three gaps in the back end are the whole of the difference. The first was the address of a name at file scope, which is where every string literal and every use of a global variable starts, and the definitions those names refer to: ninety six cases were waiting on it and eighty two of them run now. The second was that a one bit value, which is what a comparison produces, was not a width the lowering rules were written at, so a comparison used as a number rather than as a branch stopped the file. Twenty cases were waiting on that and eighteen of them run now, the other two having a second gap behind the first. The third was a call through a function pointer, which was seven cases and all seven run. What is left is eighteen cases and seven issues, and no block is larger than six. The chibicc suite is at none of its eighteen for a reason worth writing down: every case there is built with one helper file, that file has a variadic function in it, and nothing lowers `va_start`, so one gap holds the whole corpus and the first case to run will be all of them.

Results land in `results/` as markdown, one file per corpus, written by `run --report`. CI keeps its own as an artifact, because a result is about the machine that produced it.

## License

The harness is MIT or Apache-2.0, at your option. Vendored code keeps its own license, which travels with the tree it came from and is named in the manifest that fetched it.
