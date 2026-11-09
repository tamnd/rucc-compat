#!/usr/bin/env python3
"""bsd-probes: the questions that the BSD builds and configure scripts ask the compiler, for rucc and the reference GCC.

    probes.py dump ROW --cc 'CMD' -o FILE   run the reference CMD and write the expected file of ROW
    probes.py check --rucc RUCC             run rucc for every row and compare it with the expected files
    probes.py show ROW --cc 'CMD'           print what CMD gives for ROW, in the format of the expected files

The rows are the rows of bsd-predef (../bsd-predef/rows.txt).
probes.txt gives the probes, warnings.txt the warning flags and macros.txt the macros that the macros probes compare.
kprintf.txt gives the calls of the freebsd_kprintf probes, which only the FreeBSD rows have.
Each probe gives one or more answers, and each answer is one line of the expected file: a key and a value.
The probes compare what the build reads, not the whole output.
For example, bsd.compiler.mk reads the compiler type and a version number from --version, so the version probe compares those two and not the text.

accepted.txt lists the known differences, each with the issue that owns it.
check fails on a difference that is not in the list, and on a line of the list that matches no difference.
"""

import argparse
import fnmatch
import os
import shlex
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROWS = os.path.join(HERE, "..", "bsd-predef", "rows.txt")

UNIT = "int rb_probe(int x);\nint rb_probe(int x) { return x + 1; }\n"
FEATURES = """\
#ifdef __has_extension
ext_c_static_assert=__has_extension(c_static_assert)
ext_c_alignas=__has_extension(c_alignas)
ext_c_atomic=__has_extension(c_atomic)
ext_c_generic_selections=__has_extension(c_generic_selections)
ext_c_thread_local=__has_extension(c_thread_local)
#else
no_has_extension
#endif
#ifdef __has_feature
feature_c_static_assert=__has_feature(c_static_assert)
feature_c_generic_selections=__has_feature(c_generic_selections)
feature_address_sanitizer=__has_feature(address_sanitizer)
feature_nullability=__has_feature(nullability)
#else
no_has_feature
#endif
builtin_align_up=__has_builtin(__builtin_align_up)
attribute_nonstring=__has_attribute(__nonstring__)
attribute_no_stack_protector=__has_attribute(no_stack_protector)
"""
INPUTS = {"none": "", "ccv": "__FreeBSD_cc_version\n", "features": FEATURES, "unit": UNIT}

# The unit of a freebsd_kprintf probe. The call goes where CALL is.
KPRINTF_UNIT = """\
typedef __SIZE_TYPE__ size_t;
int rb_kp(const char *, ...) __attribute__((__format__(ARCHETYPE, 1, 2)));
void rb_probe(char c, short s, int i, unsigned int u, long l, long long ll, size_t z, void *p,
    const unsigned char *b, const char *n);
void rb_probe(char c, short s, int i, unsigned int u, long l, long long ll, size_t z, void *p,
    const unsigned char *b, const char *n)
{
\t(void)c; (void)s; (void)i; (void)u; (void)l; (void)ll; (void)z; (void)p; (void)b; (void)n;
\trb_kp(CALL);
}
"""
KPRINTF_FLAGS = ["-Wall", "-Wformat=2", "-c", "-o", os.devnull, "-x", "c", "-"]


def table(path):
    out = []
    with open(path) as f:
        for line in f:
            line = line.strip()
            if line and not line.startswith("#"):
                out.append(line.split())
    return out


def rows():
    out = []
    for r in table(ROWS):
        ident, system, personas, arch, target, gnuc, reference = r
        out.append(dict(id=ident, system=system, personas=personas, arch=arch, target=target, gnuc=gnuc,
                        reference=reference))
    return out


def find_row(ident):
    for r in rows():
        if r["id"] == ident:
            return r
    sys.exit(f"probes.py: no row {ident} in {ROWS}")


def probes(system, arch):
    """Return a list of (name, input, reads, arguments) for a system and an architecture."""
    out = []
    for r in table(os.path.join(HERE, "probes.txt")):
        name, sys_, arch_, inp, reads, args = r[0], r[1], r[2], r[3], r[4], r[5:]
        if sys_ in ("all", system) and arch_ in ("all", arch):
            out.append((name, inp, reads, args))
    for sys_, flag in table(os.path.join(HERE, "warnings.txt")):
        if sys_ in ("all", system):
            out.append(("werror" + flag, "unit", "status", ["-Werror", flag]))
    if system == "freebsd":
        for name, decl, call in kprintf_calls():
            out.append(("kprintf-" + name, "kprintf", "diag", [decl, call]))
    return out


def kprintf_calls():
    out = []
    with open(os.path.join(HERE, "kprintf.txt")) as f:
        for line in f:
            if line.strip() and not line.startswith("#"):
                name, decl, call = line.split(None, 2)
                out.append((name, decl, call.strip()))
    return out


def diagnostics(text):
    """The text of each warning and error, without the place and the option, in the C locale."""
    out = []
    for line in text.splitlines():
        for kind in ("warning: ", "error: "):
            at = line.find(kind)
            if at >= 0:
                msg = line[at:]
                if msg.endswith("]") and " [" in msg:
                    msg = msg[:msg.rindex(" [")]
                out.append(" ".join(msg.replace("\u2018", "'").replace("\u2019", "'").split()))
                break
    return out


def macro_names():
    return [r[0] for r in table(os.path.join(HERE, "macros.txt"))]


def run(argv, text):
    try:
        p = subprocess.run(argv, input=text, capture_output=True, text=True, timeout=120,
                           env=dict(os.environ, LC_ALL="C"))
    except (OSError, subprocess.TimeoutExpired) as e:
        return 127, "", str(e)
    return p.returncode, p.stdout, p.stderr


def first(text):
    lines = text.splitlines()
    return " ".join(lines[0].split()) if lines else ""


def version_word(w):
    """Whether a word matches the make pattern [1-9]*.[0-9]* of bsd.compiler.mk."""
    if not w or w[0] not in "123456789":
        return False
    return any(w[i] == "." and w[i + 1].isdigit() for i in range(1, len(w) - 1))


def awk_number(field):
    digits = ""
    for c in field.lstrip():
        if not c.isdigit():
            break
        digits += c
    return int(digits) if digits else 0


def identity(cc):
    """COMPILER_TYPE and COMPILER_VERSION as bsd.compiler.mk computes them.

    The name of the command is not read, because rucc and the reference have different names.
    """
    rc, out, _ = run(cc + ["--version"], "")
    if rc != 0:
        out = "0.0.0"
    words = out.split()
    if "gcc" in words or "(GCC)" in words or any(w.endswith("GNU") for w in words):
        kind = "gcc"
    elif "clang" in words:
        kind = "clang"
    else:
        _, o, e = run(cc + ["-v"], "")
        kind = "gcc" if "gcc version" in o + e else "unknown"
    fields = " ".join(w for w in words if version_word(w)).split(".")
    num = [awk_number(fields[i]) if i < len(fields) else 0 for i in range(3)]
    return f"{kind} {num[0] * 10000 + num[1] * 100 + num[2]}"


def answers(cc, system, arch):
    """Return a list of (key, value) for every probe."""
    out = []
    macros = macro_names()
    for name, inp, reads, args in probes(system, arch):
        if reads == "identity":
            out.append((name, identity(cc)))
            continue
        if reads == "diag":
            decl, call = args
            if decl == "p":
                src = KPRINTF_UNIT.replace("ARCHETYPE", "__printf__")
                argv = cc + ["-D__printf__=__freebsd_kprintf__"] + KPRINTF_FLAGS
            else:
                src = KPRINTF_UNIT.replace("ARCHETYPE", "__freebsd_kprintf__")
                argv = cc + KPRINTF_FLAGS
            rc, _, se = run(argv, src.replace("CALL", call))
            out.append((name, " | ".join([f"rc={rc}"] + diagnostics(se))))
            continue
        argv = cc + args
        if inp == "unit":
            argv += ["-c", "-o", os.devnull, "-x", "c", "-"]
        rc, so, se = run(argv, INPUTS[inp])
        if reads == "vline":
            words = (so + se).split()
            v = "none"
            for i in range(len(words) - 2):
                if words[i].lstrip("(") == "gcc" and words[i + 1] == "version":
                    v = words[i + 2]
                    break
            out.append((name, v))
        elif reads == "line":
            out.append((name, f"rc={rc} {first(so)}".rstrip()))
        elif reads == "base":
            out.append((name, f"rc={rc} {os.path.basename(first(so))}".rstrip()))
        elif reads == "lines":
            kept = [" ".join(l.split()) for l in so.splitlines() if l.strip() and not l.startswith("# ")]
            out.append((name, f"rc={rc} {' | '.join(kept)}".rstrip()))
        elif reads == "macros":
            if rc != 0:
                out.append((name, f"rc={rc}"))
                continue
            defs = {}
            for l in so.splitlines():
                if l.startswith("#define "):
                    parts = l[8:].split(None, 1)
                    defs[parts[0]] = " ".join(parts[1].split()) if len(parts) > 1 else ""
            for m in macros:
                out.append((f"{name}/{m}", defs.get(m, "undefined")))
        elif reads == "status":
            out.append((name, f"rc={rc}"))
        else:
            sys.exit(f"probes.py: probe {name} reads {reads}, which is not known")
    return out


def pack(ans):
    return [f"{k} {v}".rstrip() for k, v in ans]


def parse(lines):
    out = {}
    for line in lines:
        if not line or line.startswith("#"):
            continue
        k, _, v = line.partition(" ")
        out[k] = v
    return out


def accepted():
    out = []
    path = os.path.join(HERE, "accepted.txt")
    if not os.path.exists(path):
        return out
    with open(path) as f:
        for n, line in enumerate(f, 1):
            line = line.strip()
            if line and not line.startswith("#"):
                parts = line.split()
                out.append(dict(line=n, row=parts[0], key=parts[1], issue=parts[2], used=0))
    return out


def header(row, a, version):
    text = [f"# {row['id']}: {row['system']} {row['arch']}, personas {row['personas']}, reference {row['reference']}",
            f"# command: {a.cc}",
            f"# version: {version.splitlines()[0] if version else 'unknown'}"]
    for note in a.note:
        text.append(f"# {note}")
    return text


def cmd_dump(a):
    row = find_row(a.row)
    cc = shlex.split(a.cc)
    _, version, _ = run(cc + ["--version"], "")
    text = header(row, a, version) + pack(answers(cc, row["system"], row["arch"]))
    with open(a.o, "w") as f:
        f.write("\n".join(text) + "\n")


def cmd_show(a):
    row = find_row(a.row)
    print("\n".join(pack(answers(shlex.split(a.cc), row["system"], row["arch"]))))


def cmd_check(a):
    acc = accepted()
    bad = 0
    report = []
    for row in rows():
        if a.rows and not any(fnmatch.fnmatch(row["id"], g) for g in a.rows):
            continue
        path = os.path.join(HERE, "expected", row["id"] + ".txt")
        if not os.path.exists(path):
            print(f"{row['id']}: no expected file")
            bad += 1
            continue
        with open(path) as f:
            ref = parse(f.read().splitlines())
        cc = [a.rucc, f"--target={row['target']}", f"-fgnuc-version={row['gnuc']}"]
        got = dict(answers(cc, row["system"], row["arch"]))
        new = known = 0
        for k in list(ref) + [k for k in got if k not in ref]:
            r, g = ref.get(k, "(no probe)"), got.get(k, "(no probe)")
            if r == g:
                continue
            hit = [e for e in acc if fnmatch.fnmatch(row["id"], e["row"]) and fnmatch.fnmatch(k, e["key"])]
            for e in hit:
                e["used"] += 1
            if hit:
                known += 1
                tag = hit[0]["issue"]
            else:
                new += 1
                tag = "NEW"
            report.append(f"{row['id']} {k} {tag}")
            report.append(f"    reference: {r}")
            report.append(f"    rucc:      {g}")
        print(f"{row['id']}: {len(ref)} answers, {new} new differences, {known} accepted")
        bad += new
    for e in acc:
        if not e["used"] and not a.rows:
            print(f"accepted.txt:{e['line']}: {e['row']} {e['key']} matches no difference")
            bad += 1
    if a.report:
        with open(a.report, "w") as f:
            f.write("\n".join(report) + "\n")
    elif report and a.verbose:
        print("\n".join(report))
    if bad:
        print(f"bsd-probes: {bad} problems")
        return 1
    print("bsd-probes: no new differences")
    return 0


def main():
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = p.add_subparsers(dest="cmd", required=True)
    d = sub.add_parser("dump")
    d.add_argument("row")
    d.add_argument("--cc", required=True)
    d.add_argument("--note", action="append", default=[])
    d.add_argument("-o", required=True)
    s = sub.add_parser("show")
    s.add_argument("row")
    s.add_argument("--cc", required=True)
    c = sub.add_parser("check")
    c.add_argument("--rucc", required=True)
    c.add_argument("--rows", action="append", default=[], help="only the rows that match this glob")
    c.add_argument("--report", help="write each difference to this file")
    c.add_argument("-v", "--verbose", action="store_true", help="print each difference")
    a = p.parse_args()
    if a.cmd == "dump":
        cmd_dump(a)
    elif a.cmd == "show":
        cmd_show(a)
    else:
        sys.exit(cmd_check(a))


if __name__ == "__main__":
    main()
