#!/usr/bin/env python3
"""bsd-predef: the predefined macros and the feature answers of rucc against the reference GCC of each BSD target.

    predef.py dump ROW --cc 'CMD' -o FILE   run the reference CMD and write the expected file of ROW
    predef.py check --rucc RUCC             run rucc for every row and compare it with the expected files
    predef.py show ROW --cc 'CMD'           print what CMD gives for ROW, in the format of the expected files

rows.txt gives the rows, flags.txt the flag sets and features.txt the feature queries.
Each flag set is one run of `-dM -E` on an empty file, and one run of `-E` on a file of feature queries.
The expected file keeps the default set in full.
For each other set it keeps only the lines that the flags add (+) or remove (-), so a difference in the default set shows once and not once for each set.

The lines that name the compiler are not compared: __VERSION__ and every macro that starts with __rucc.
Spaces inside a line are not compared.
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
IGNORED = ("__VERSION__",)
IGNORED_PREFIX = ("__rucc",)


def table(name):
    rows = []
    with open(os.path.join(HERE, name)) as f:
        for line in f:
            line = line.strip()
            if line and not line.startswith("#"):
                rows.append(line.split())
    return rows


def rows():
    out = []
    for r in table("rows.txt"):
        ident, system, personas, arch, target, gnuc, reference = r
        out.append(dict(id=ident, system=system, personas=personas, arch=arch, target=target, gnuc=gnuc,
                        reference=reference))
    return out


def find_row(ident):
    for r in rows():
        if r["id"] == ident:
            return r
    sys.exit(f"predef.py: no row {ident} in rows.txt")


def flag_sets(system, arch):
    out = []
    for r in table("flags.txt"):
        name, sys_, arch_, flags = r[0], r[1], r[2], r[3:]
        if sys_ in ("all", system) and arch_ in ("all", arch):
            out.append((name, flags))
    return out


def features_source():
    lines = []
    for kind, name in table("features.txt"):
        lines.append(f"#ifdef __{kind}")
        lines.append(f"Q {kind} {name} __{kind}({name})")
        lines.append("#else")
        lines.append(f"Q {kind} {name} undefined")
        lines.append("#endif")
    return "\n".join(lines) + "\n"


def run(argv, text):
    p = subprocess.run(argv, input=text, capture_output=True, text=True)
    return p.returncode, p.stdout


def dump(cc, system, arch):
    """Return a list of (set name, flags, rc, lines). The lines are sorted."""
    src = features_source()
    out = []
    for name, flags in flag_sets(system, arch):
        rc, macros = run(cc + flags + ["-dM", "-E", "-x", "c", "-"], "")
        lines = []
        if rc == 0:
            lines = [l for l in macros.splitlines() if l.startswith("#define ")]
            rc, feats = run(cc + flags + ["-E", "-P", "-x", "c", "-"], src)
            if rc == 0:
                lines += [" ".join(l.split()) for l in feats.splitlines() if l.startswith("Q ")]
        out.append((name, flags, rc, sorted(set(lines))))
    return out


def pack(sets):
    text = []
    base = None
    for name, flags, rc, lines in sets:
        text.append(f"[{name}] rc={rc} {' '.join(flags)}".rstrip())
        if rc != 0:
            continue
        if base is None:
            base = set(lines)
            text += lines
        else:
            now = set(lines)
            text += sorted(["-" + l for l in base - now] + ["+" + l for l in now - base], key=lambda l: (l[1:], l[0]))
    return text


def parse(lines):
    """Return {set name: (rc, set of lines)}, with the delta of each set applied to the default set."""
    out = {}
    order = []
    cur = None
    for line in lines:
        if not line or (cur is None and line.startswith("#")):
            continue
        if line.startswith("["):
            head = line.split()
            cur = head[0][1:-1]
            order.append(cur)
            out[cur] = (int(head[1][3:]), set())
            continue
        # GCC ends an empty definition with a space and rucc does not. The spaces are not compared.
        out[cur][1].add(" ".join(line.split()))
    base = out[order[0]][1] if order else set()
    for name in order[1:]:
        rc, delta = out[name]
        if rc == 0:
            full = set(base)
            for l in delta:
                (full.add if l[0] == "+" else full.discard)(l[1:])
            out[name] = (rc, full)
    return out


def key(line):
    if line.startswith("#define "):
        return line.split()[1].split("(")[0]
    _, kind, name = line.split()[:3]
    return f"__{kind}({name})"


def ignored(name):
    return name in IGNORED or name.startswith(IGNORED_PREFIX)


def by_key(rl, gl):
    by = {}
    for side, lines in ((0, rl - gl), (1, gl - rl)):
        for l in lines:
            k = key(l)
            if not ignored(k):
                by.setdefault(k, ([], []))[side].append(l)
    return {k: (sorted(v[0]), sorted(v[1])) for k, v in by.items()}


def compare(ref, got):
    """Yield (set, key, reference lines, rucc lines) for each difference.

    A set other than the default one gives only the differences that the default set does not give.
    """
    base = None
    for name in list(ref) + [s for s in got if s not in ref]:
        rrc, rl = ref.get(name, (None, set()))
        grc, gl = got.get(name, (None, set()))
        if rrc != grc:
            yield name, "rc", [f"rc={rrc}"], [f"rc={grc}"]
            continue
        diffs = by_key(rl, gl)
        if base is None:
            base = diffs
        else:
            diffs = {k: v for k, v in diffs.items() if base.get(k) != v}
        for k in sorted(diffs):
            yield name, k, diffs[k][0], diffs[k][1]


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
                out.append(dict(line=n, row=parts[0], set=parts[1], key=parts[2], issue=parts[3], used=0))
    return out


def cmd_dump(a):
    row = find_row(a.row)
    cc = shlex.split(a.cc)
    rc, version = run(cc + ["--version"], "")
    text = [f"# {row['id']}: {row['system']} {row['arch']}, personas {row['personas']}, reference {row['reference']}",
            f"# command: {a.cc}",
            f"# version: {version.splitlines()[0] if version else 'unknown'}"]
    for note in a.note:
        text.append(f"# {note}")
    text += pack(dump(cc, row["system"], row["arch"]))
    with open(a.o, "w") as f:
        f.write("\n".join(text) + "\n")


def cmd_show(a):
    row = find_row(a.row)
    print("\n".join(pack(dump(shlex.split(a.cc), row["system"], row["arch"]))))


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
        got = parse(pack(dump(cc, row["system"], row["arch"])))
        new = known = 0
        for set_, k, rl, gl in compare(ref, got):
            hit = [e for e in acc if fnmatch.fnmatch(row["id"], e["row"]) and fnmatch.fnmatch(set_, e["set"])
                   and fnmatch.fnmatch(k, e["key"])]
            for e in hit:
                e["used"] += 1
            if hit:
                known += 1
                tag = hit[0]["issue"]
            else:
                new += 1
                tag = "NEW"
            report.append(f"{row['id']} [{set_}] {k} {tag}")
            for l in rl:
                report.append(f"    reference: {l}")
            for l in gl:
                report.append(f"    rucc:      {l}")
        print(f"{row['id']}: {len(ref)} sets, {new} new differences, {known} accepted")
        bad += new
    for e in acc:
        if not e["used"] and not a.rows:
            print(f"accepted.txt:{e['line']}: {e['row']} {e['set']} {e['key']} matches no difference")
            bad += 1
    if a.report:
        with open(a.report, "w") as f:
            f.write("\n".join(report) + "\n")
    elif report and a.verbose:
        print("\n".join(report))
    if bad:
        print(f"bsd-predef: {bad} problems")
        return 1
    print("bsd-predef: no new differences")
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
