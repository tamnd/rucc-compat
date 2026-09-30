#!/usr/bin/env python3
"""Writes the programs of the intrinsics corpus's `neon` unit from a table of intrinsics.

The table is `corpus/intrinsics/arm_neon.txt`, one prototype a line, exactly as rucc's own
`arm_neon.h` declares them. There are a couple of thousand of them, and a program written by hand
for each would be a corpus nobody keeps up with the header, so the programs are written from the
table instead and the table is checked against the header.

Each intrinsic gets a function that calls it over a few thousand inputs and prints a checksum of
everything it returned, and everything it stored for the ones that store. There is no plain C
beside it working the answer out a second way, which is what the SSE2 programs have. The answer
is gcc's: the reference builds the same program with its own `arm_neon.h`, whose intrinsics are
the instructions themselves, and the two outputs have to be the same line for line. That is the
definition a user of the header expects, and it is the only one that is right about the corners
nobody writes plain C for, such as what a conversion does with a value out of range or which
not-a-number a maximum returns.

An intrinsic that takes an immediate is called at the smallest value it allows, the largest and
one in between, and at every combination of those when it takes two. The ranges come from the
family of the intrinsic below, and an immediate in a family this does not know stops the script
rather than being guessed at, since gcc refuses a value out of range and the program would not
build.

One program a family, so `vadd.c` holds `vadd_s8` through `vaddq_f64`, and a family of more than
`CHUNK` is split. An intrinsic that an `[[exec-exclude]]` entry in the manifest names, as
`neon/<name>.c`, gets a program of its own instead, so a wrong answer from one intrinsic excuses
that intrinsic and not the thirty others it would have shared a file with.

Usage, from the root of the repository:

    python3 scripts/arm_neon.py                      write the programs from the table
    python3 scripts/arm_neon.py --check              fail if the programs are not what the table says
    python3 scripts/arm_neon.py --table HEADER       rewrite the table from a rucc arm_neon.h
    python3 scripts/arm_neon.py --check --table HEADER
                                                     fail if the table is not what the header ships
"""

import itertools
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CORPUS = os.path.join(ROOT, "corpus", "intrinsics")
TABLE = os.path.join(CORPUS, "arm_neon.txt")
OUT = os.path.join(CORPUS, "neon")
MANIFEST = os.path.join(CORPUS, "corpus.toml")

# The most intrinsics one program holds. `vreinterpret` is three hundred on its own, and a case
# that big is slow to build and says little when it goes red.
CHUNK = 64

# The first word of every intrinsic's name, which is what tells a `q` that means 128 bits from a
# `q` that is part of the name.
HEADS = set()

MARK = "Written by scripts/arm_neon.py"

TABLE_HEAD = """\
# Every intrinsic rucc's arm_neon.h ships, one prototype a line, in the header's order.
#
# scripts/arm_neon.py writes the programs of the neon unit from this file, and CI checks it against
# the header on rucc's main branch, so an intrinsic added there and not here fails the run. Refresh
# it with `python3 scripts/arm_neon.py --table path/to/rucc/crates/rucc-session/runtime/include/arm_neon.h`.
"""

VECTOR = re.compile(r"^(int|uint|float|poly)(8|16|32|64)x(\d+)(?:x([234]))?_t$")
SCALAR = re.compile(r"^(int|uint|float|poly)(8|16|32|64)_t$")


class Type:
    """What the program needs to know about a parameter or a result."""

    def __init__(self, text):
        self.text = text
        self.pointer = text.endswith("*")
        self.const = text.startswith("const ")
        base = text.replace("const ", "").rstrip("*").strip()
        self.base = base
        m = VECTOR.match(base)
        s = SCALAR.match(base)
        if m:
            self.kind, self.bits, self.lanes = m.group(1), int(m.group(2)), int(m.group(3))
            self.vector = True
        elif s:
            self.kind, self.bits, self.lanes = s.group(1), int(s.group(2)), 1
            self.vector = False
        elif base == "void":
            self.kind, self.bits, self.lanes, self.vector = "void", 0, 0, False
        else:
            raise SystemExit(f"arm_neon.py: no idea what `{text}` is")

    def float_bits(self):
        return self.bits if self.kind == "float" else 0


class Intrinsic:
    def __init__(self, line):
        m = re.match(r"^(.*?)\b(v\w+)\((.*)\)$", line)
        if not m:
            raise SystemExit(f"arm_neon.py: cannot read `{line}`")
        self.line = line
        self.result = Type(m.group(1).strip())
        self.name = m.group(2)
        self.params = []
        for p in m.group(3).split(","):
            p = p.strip()
            pm = re.match(r"^(.*?)\s*(__\w+)$", p)
            if not pm:
                raise SystemExit(f"arm_neon.py: cannot read the parameter `{p}` of {self.name}")
            text, name = pm.group(1).strip(), pm.group(2)
            if text == "const int":
                self.params.append(("imm", name, None))
            else:
                self.params.append(("arg", name, Type(text)))

    def family(self, heads):
        """The name without its lane types and without the `q` of the 128 bit form, so that
        `vaddq_u8` is `vadd` and `vdupq_laneq_s8` is `vdup_laneq`. The `q` goes only when the
        name without it is an intrinsic too, since `vceq` is not the 128 bit form of `vce`."""
        f = re.sub(r"_[supf](8|16|32|64)", "", self.name)
        f = re.sub(r"_x[234]$", "", f)
        head, _, tail = f.partition("_")
        if head.endswith("q") and head[:-1] in heads:
            head = head[:-1]
        return head + ("_" + tail if tail else "")

    def ranges(self):
        """The values each immediate is called at, in parameter order."""
        fam = self.family(HEADS)
        out = []
        for i, (what, name, _) in enumerate(self.params):
            if what != "imm":
                continue
            # The nearest vector before the immediate is the one it indexes or shifts, which is
            # true of every family below: `vset_lane(x, v, lane)`, `vcopy_lane(a, la, b, lb)`.
            before = [t for (w, _, t) in self.params[:i] if w == "arg" and t.vector]
            if not before:
                raise SystemExit(f"arm_neon.py: {self.name} has an immediate before any vector")
            v = before[-1]
            first = next(t for (w, _, t) in self.params if w == "arg" and t.vector)
            if name in ("__lane", "__la", "__lb") or fam == "vext":
                lo, hi = 0, v.lanes - 1
            elif fam in ("vshl_n", "vsli_n"):
                lo, hi = 0, first.bits - 1
            elif fam in ("vshr_n", "vsra_n", "vsri_n"):
                lo, hi = 1, first.bits
            elif fam in ("vshrn_n", "vrshrn_n"):
                lo, hi = 1, first.bits // 2
            elif fam in ("vshll_n", "vshll_high_n"):
                lo, hi = 0, first.bits
            else:
                raise SystemExit(
                    f"arm_neon.py: {self.name} takes an immediate `{name}` and the family "
                    f"`{fam}` has no range here yet"
                )
            out.append(sorted({lo, (lo + hi) // 2, hi}))
        return out


def read_table():
    lines = []
    with open(TABLE) as f:
        for line in f:
            line = line.strip()
            if line and not line.startswith("#"):
                lines.append(line)
    return lines


def read_header(path):
    with open(path) as f:
        text = f.read()
    found = re.findall(r"^static __inline__ ([^{;]*?)\s*\{", text, re.M | re.S)
    return [" ".join(p.split()) for p in found]


def apart():
    """The intrinsics the manifest excuses by name, which get a program each."""
    with open(MANIFEST) as f:
        text = f.read()
    return set(re.findall(r'"neon/(v\w+)\.c"', text))


def test(intr):
    """One function calling one intrinsic every way the table allows."""
    lines = [f"static void t_{intr.name}(void)", "{", "    uint64_t sum = 0;"]
    lines.append("    for (int r = 0; r < ROUNDS; r++) {")
    args = []
    stored = []
    k = 0
    for what, name, t in intr.params:
        if what == "imm":
            args.append(None)
            continue
        var = f"a{k}"
        if t.pointer:
            lines.append(f"        BUF({t.base}, {var}, {k}, {t.float_bits()});")
            if not t.const:
                stored.append(var)
        else:
            lines.append(f"        ARG({t.base}, {var}, {k}, {t.float_bits()});")
        args.append(var)
        k += 1
    for combo in itertools.product(*intr.ranges()):
        values = iter(combo)
        call = ", ".join(a if a is not None else str(next(values)) for a in args)
        if intr.result.kind == "void":
            lines.append(f"        STORE({intr.name}({call}), {', '.join(stored)});")
        else:
            lines.append(f"        KEEP({intr.result.base}, {intr.name}({call}));")
    lines.append("    }")
    lines.append(f'    SUM("{intr.name}", sum);')
    lines.append("}")
    return "\n".join(lines)


def program(title, intrinsics):
    head = f"""/* {title}
 *
 * {MARK} from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"
"""
    body = "\n\n".join(test(i) for i in intrinsics)
    calls = "\n".join(f"    t_{i.name}();" for i in intrinsics)
    return f"{head}\n{body}\n\nint main(void)\n{{\n{calls}\n    return 0;\n}}\n"


def programs(intrinsics):
    alone = apart()
    unknown = alone - {i.name for i in intrinsics}
    if unknown:
        raise SystemExit(
            f"arm_neon.py: the manifest excuses {', '.join(sorted(unknown))}, which the table does not have"
        )
    families = {}
    for i in intrinsics:
        if i.name in alone:
            continue
        families.setdefault(i.family(HEADS), []).append(i)
    out = {}
    for fam, members in families.items():
        chunks = [members[n : n + CHUNK] for n in range(0, len(members), CHUNK)]
        for n, chunk in enumerate(chunks):
            name = fam if len(chunks) == 1 else f"{fam}-{n + 1}"
            title = f"The {fam} family of arm_neon.h"
            if len(chunks) > 1:
                title += f", part {n + 1} of {len(chunks)}"
            out[f"{name}.c"] = program(title + ".", chunk)
    for i in intrinsics:
        if i.name in alone:
            title = f"{i.name} on its own, because the manifest excuses it by name."
            out[f"{i.name}.c"] = program(title, [i])
    return out


def main(argv):
    check = "--check" in argv
    header = None
    if "--table" in argv:
        at = argv.index("--table")
        if at + 1 >= len(argv):
            raise SystemExit("arm_neon.py: --table wants the path to an arm_neon.h")
        header = argv[at + 1]

    if header:
        shipped = read_header(header)
        if check:
            have = read_table()
            missing = [p for p in shipped if p not in have]
            extra = [p for p in have if p not in shipped]
            for p in missing:
                print(f"shipped and not in the table: {p}")
            for p in extra:
                print(f"in the table and not shipped: {p}")
            if missing or extra:
                print(
                    f"{len(missing)} missing, {len(extra)} gone. Rewrite the table with "
                    "`python3 scripts/arm_neon.py --table HEADER` and the programs with "
                    "`python3 scripts/arm_neon.py`."
                )
                return 1
            print(f"the table has every one of the {len(shipped)} intrinsics the header ships")
            return 0
        with open(TABLE, "w") as f:
            f.write(TABLE_HEAD + "\n" + "\n".join(shipped) + "\n")
        print(f"wrote {len(shipped)} intrinsics to {os.path.relpath(TABLE, ROOT)}")
        return 0

    intrinsics = [Intrinsic(line) for line in read_table()]
    HEADS.update(i.name.partition("_")[0] for i in intrinsics)
    names = [i.name for i in intrinsics]
    if len(set(names)) != len(names):
        raise SystemExit("arm_neon.py: the table names an intrinsic twice")
    want = programs(intrinsics)
    have = {}
    if os.path.isdir(OUT):
        for name in os.listdir(OUT):
            if name.endswith(".c"):
                with open(os.path.join(OUT, name)) as f:
                    have[name] = f.read()
    if check:
        wrong = sorted(n for n in want if have.get(n) != want[n])
        gone = sorted(n for n in have if n not in want)
        for n in wrong:
            print(f"neon/{n} is not what the table says")
        for n in gone:
            print(f"neon/{n} is not in the table")
        if wrong or gone:
            print("Run `python3 scripts/arm_neon.py` and commit what it writes.")
            return 1
        print(f"{len(want)} programs over {len(intrinsics)} intrinsics, all up to date")
        return 0
    os.makedirs(OUT, exist_ok=True)
    for n in have:
        if n not in want:
            os.remove(os.path.join(OUT, n))
    for n, text in want.items():
        if have.get(n) != text:
            with open(os.path.join(OUT, n), "w") as f:
                f.write(text)
    print(f"wrote {len(want)} programs over {len(intrinsics)} intrinsics to {os.path.relpath(OUT, ROOT)}")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
