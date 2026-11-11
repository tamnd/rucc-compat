# plan9

These are the cases of the Plan 9 C dialect, which only kencc and rucc under `-fkencc` compile. GCC does not compile the dialect, so the reference is `6c` or `7c` in a 9front guest, and these cases are not under `corpus/`. Each `exec` of a corpus builds the reference on the host, and here that is not possible.

Each case is a whole program for the guest. It includes `u.h` and `libc.h`, prints its result with `print`, and stops with `exits(nil)`. The file `NAME.expected` beside each case is what the case printed when `7c` built it on 9front arm64. A case that `7c` refuses has the line `did not build` there, and rucc must refuse it too.

- `const` has 32 cases of the type of an integer constant and of the usual arithmetic conversions. Each case prints the size of an expression, whether its negation is below zero, and its value as a `vlong`. These are the rules of `lex.c` of kencc, such as `2147483648L`, which is a `ulong`.
- `cpp` has 18 cases of the kencc preprocessor: a parameter in a string literal or a character constant of the body, `#` and `##` as text, `#line`, `#pragma varargck`, and the directives that kencc does not have. kencc has no `#if` and no `#elif`, and it stops on a macro that names itself.

## Running them

The runner is in the rucc-plan9 repository. `guest/compat/run.rc` builds, links and runs each `DIR/NAME.c` under the current directory and writes what it printed to `DIR/NAME.SIDE`. `smoke/compat.rc` runs it twice in a guest. The first run, G, uses the compiler of the image. The second run, R, is under `r9-build` with `r9ccd` set, so each compile goes to rucc on the host through `r9 ccd`.

1. Start `r9 ccd --rucc PATH` on the host.
2. Make an input directory with the `guest` directory of rucc-plan9 as `r9`, and this directory as `compat`.
3. Run `r9 boot --row arm64 --net --in DIR --run smoke/compat.rc --collect 16 --out OUT`.
4. Compare each `OUT/collected/compat/DIR/NAME.R` with `NAME.expected` here.

On 9front arm64 and amd64 at the pin of rucc-plan9, each of the 50 cases prints the same under G and R, and the same as its `NAME.expected`.
