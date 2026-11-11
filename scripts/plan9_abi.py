"""Make the abi cases of rucc-compat/plan9: calls between two objects for many call shapes.

usage: python3 -I scripts/plan9_abi.py OUTDIR [FILES [SHAPES]]

Each case is one file. Built with -DCALLEE it is the half with the called functions, and built
without it is the half with main, the calls and the callbacks. The runner builds each half with
another compiler and links them, in both directions. Each half prints what it gets, so a value
that the two compilers pass in different places shows as a different line.
"""
import os
import random
import sys

outdir = sys.argv[1]
files = int(sys.argv[2]) if len(sys.argv) > 2 else 40
shapes = int(sys.argv[3]) if len(sys.argv) > 3 else 10
rnd = random.Random(9)

# name, format, kind
SCALARS = [
    ("char", "%d", "s"), ("uchar", "%ud", "u"), ("short", "%d", "s"), ("ushort", "%ud", "u"),
    ("int", "%d", "s"), ("uint", "%ud", "u"), ("long", "%ld", "s"), ("ulong", "%lud", "u"),
    ("vlong", "%lld", "s"), ("uvlong", "%llud", "u"), ("float", "%g", "f"), ("double", "%g", "f"),
]
SIZE = {"char": 1, "uchar": 1, "short": 2, "ushort": 2, "int": 4, "uint": 4, "long": 4,
        "ulong": 4, "vlong": 8, "uvlong": 8, "float": 4, "double": 8}
BITS = {"char": 7, "uchar": 8, "short": 15, "ushort": 16, "int": 31, "uint": 32, "long": 31,
        "ulong": 32, "vlong": 63, "uvlong": 64}


def value(t, n):
    """A constant of type t that depends on n."""
    kind = dict((s[0], s[2]) for s in SCALARS)[t]
    if kind == "f":
        return f"{(n % 97) - 40}.{(n * 7) % 8 * 125:03d}"
    bits = BITS[t]
    v = (n * 2654435761) % (1 << min(bits, 31))
    if kind == "s" and n % 3 == 0:
        v = -v
    suffix = {"vlong": "LL", "uvlong": "ULL", "ulong": "UL", "uint": "U", "long": "L"}.get(t, "")
    if bits > 32 and n % 2:
        v = v * 1000003 + 7
        if kind == "s":
            v %= 1 << 62
            if n % 3 == 0:
                v = -v
    return f"{v}{suffix}"


def bump(t, expr):
    kind = dict((s[0], s[2]) for s in SCALARS)[t]
    return f"{expr} * 2" if kind == "f" else f"{expr} + 3"


class Struct:
    def __init__(self, name, target):
        self.name = name
        self.fields = []
        size = 0
        i = 0
        while size < target:
            room = target - size
            pool = [s for s in SCALARS if SIZE[s[0]] <= room] or SCALARS[:2]
            t = rnd.choice(pool)
            n = 1
            if t[0] in ("char", "uchar") and room > 2 and rnd.random() < 0.4:
                n = rnd.randint(2, min(room, 9))
            self.fields.append((t, f"f{i}", n))
            size += SIZE[t[0]] * n
            i += 1

    def decl(self):
        body = " ".join(f"{t[0]} {f}{'[%d]' % n if n > 1 else ''};" for t, f, n in self.fields)
        return f"typedef struct {self.name} {self.name};\nstruct {self.name} {{ {body} }};"

    def printer(self):
        fmts, args = [], []
        for t, f, n in self.fields:
            for k in range(n) if n > 1 else [None]:
                fmts.append(t[1])
                args.append(f"s.{f}" + (f"[{k}]" if k is not None else ""))
        return (f"static void\np{self.name}(char *w, {self.name} s)\n{{\n"
                f"\tprint(\"%s {self.name} {' '.join(fmts)}\\n\", w, {', '.join(args)});\n}}")

    def setter(self, var, n):
        out = []
        for t, f, cnt in self.fields:
            for k in range(cnt) if cnt > 1 else [None]:
                out.append(f"\t{var}.{f}{'[%d]' % k if k is not None else ''} = {value(t[0], n)};")
                n += 1
        return out

    def bumper(self, var):
        out = []
        for t, f, cnt in self.fields:
            for k in range(cnt) if cnt > 1 else [None]:
                e = f"{var}.{f}{'[%d]' % k if k is not None else ''}"
                out.append(f"\t{e} = {bump(t[0], e)};")
        return out


def gen(index):
    structs = []
    sizes = [rnd.choice([1, 2, 3, 4, 5, 6, 7, 8, 9, 12, 15, 16, 17, 24, 31, 32, 40, 48, 63, 64])
             for _ in range(4)]
    for k, sz in enumerate(sizes):
        structs.append(Struct(f"S{k}", sz))
    types = [("s", s) for s in structs] + [("t", t) for t in SCALARS]

    def tname(t):
        return t[1].name if t[0] == "s" else t[1][0]

    def show(t, expr, w):
        if t[0] == "s":
            return f"\tp{t[1].name}(\"{w}\", {expr});"
        return f"\tprint(\"{w} {t[1][0]} {t[1][1]}\\n\", {expr});"

    protos, callee, caller = [], [], []
    n = index * 1000
    for k in range(shapes):
        nargs = rnd.choice([1, 2, 3, 4, 6, 8])
        args = [rnd.choice(types) for _ in range(nargs)]
        ret = rnd.choice(types + [("v", None)])
        rt = "void" if ret[0] == "v" else tname(ret)
        params = ", ".join(f"{tname(a)} a{j}" for j, a in enumerate(args))
        protos.append(f"{rt} f{k}({params});")
        body = [f"{rt}\nf{k}({params})\n{{"]
        if ret[0] == "s":
            body += [f"\t{rt} r;", ""]
        body.append(f"\tprint(\"in f{k}\\n\");")
        for j, a in enumerate(args):
            body.append(show(a, f"a{j}", f"a{j}"))
        if ret[0] == "s":
            src = next((j for j, a in enumerate(args) if a == ret), None)
            if src is None:
                body += ret[1].setter("r", n + 500)
            else:
                body.append(f"\tr = a{src};")
                body += ret[1].bumper("r")
            body.append("\treturn r;")
        elif ret[0] == "t":
            body.append(f"\treturn {value(ret[1][0], n + 600)};")
        body.append("}")
        callee.append("\n".join(body))
        call = [f"\t{{"]
        for j, a in enumerate(args):
            if a[0] == "s":
                call.append(f"\t{tname(a)} v{j};")
        if ret[0] != "v":
            call.append(f"\t{rt} r;")
        for j, a in enumerate(args):
            if a[0] == "s":
                call += a[1].setter(f"v{j}", n)
                n += 20
        vals = []
        for j, a in enumerate(args):
            if a[0] == "s":
                vals.append(f"v{j}")
            else:
                vals.append(f"({a[1][0]}){value(a[1][0], n)}")
                n += 1
        callexpr = f"f{k}({', '.join(vals)})"
        if ret[0] == "v":
            call.append(f"\t{callexpr};")
        else:
            call.append(f"\tr = {callexpr};")
            call.append(show(ret, "r", f"ret f{k}"))
        call.append("\t}")
        caller.append("\n".join(call))
        n += 37

    # a variadic function: the callee reads the arguments with va_arg
    vtypes = [rnd.choice(types) for _ in range(rnd.randint(2, 7))]
    vtypes = [t for t in vtypes if t[0] == "t" and t[1][0] not in ("char", "uchar", "short",
                                                                    "ushort", "float")]
    vtypes = vtypes or [("t", SCALARS[8])]
    protos.append("void vf(int n, ...);")
    body = ["void\nvf(int n, ...)\n{", "\tva_list ap;", "", "\tva_start(ap, n);",
            "\tprint(\"in vf %d\\n\", n);"]
    for j, t in enumerate(vtypes):
        body.append(f"\tprint(\"v{j} {t[1][1]}\\n\", va_arg(ap, {t[1][0]}));")
    body.append("\tva_end(ap);")
    body.append("}")
    callee.append("\n".join(body))
    vals = [f"({t[1][0]}){value(t[1][0], n + j)}" for j, t in enumerate(vtypes)]
    caller.append(f"\tvf({len(vtypes)}, {', '.join(vals)});")

    # a callback: the callee calls a function of the caller through a pointer
    s = structs[rnd.randrange(len(structs))]
    st = ("s", s)
    protos.append(f"{s.name} cb({s.name} (*fn)({s.name}, double, vlong), {s.name} x);")
    callee.append("\n".join([f"{s.name}\ncb({s.name} (*fn)({s.name}, double, vlong), {s.name} x)\n{{",
                             f"\t{s.name} r;", "", "\tr = fn(x, 2.5, -7LL);", show(st, "r", "cb got"),
                             "\treturn fn(r, -1.25, 1LL<<40);", "}"]))
    caller_cb = "\n".join([f"static {s.name}\nback({s.name} x, double d, vlong v)\n{{",
                           show(st, "x", "back x"), "\tprint(\"back %g %lld\\n\", d, v);"]
                          + s.bumper("x") + ["\treturn x;", "}"])
    caller.append("\n".join(["\t{", f"\t{s.name} x, r;", ""] + s.setter("x", n + 900)
                            + ["\tr = cb(back, x);", show(st, "r", "ret cb"), "\t}"]))

    lines = ["#include <u.h>", "#include <libc.h>", ""]
    lines += [s.decl() for s in structs]
    lines.append("")
    lines += protos
    lines.append("")
    lines.append("#ifdef CALLEE")
    lines += [s.printer() + "\n" for s in structs]
    lines += [c + "\n" for c in callee]
    lines.append("#else")
    lines += [s.printer() + "\n" for s in structs]
    lines.append(caller_cb + "\n")
    lines += ["void", "main(void)", "{"]
    lines += caller
    lines += ["\texits(nil);", "}"]
    lines.append("#endif")
    return "\n".join(lines) + "\n"


os.makedirs(outdir, exist_ok=True)
for i in range(files):
    open(os.path.join(outdir, f"call{i:02d}.c"), "w").write(gen(i))
print(f"{files} files, {files * (shapes + 2)} shapes")
