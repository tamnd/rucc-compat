#!/usr/bin/env python3
"""bsd-pp: the preprocessed text of the installed BSD headers under rucc, against the reference GCC.

    pp.py dump ROW --cc 'CMD' --sysroot DIR -o FILE [--keep DIR]   preprocess every unit with the reference CMD
    pp.py check --rucc RUCC --sets DIR [--keep DIR]                compare rucc with the expected files

The rows are the rows of bsd-abi (../bsd-abi/rows.txt): one release set of one system on one architecture.
abi.py fetch unpacks the headers of a row.

A unit is one header of the set in one mode.
modes.txt gives the modes: the flags of the world build and of the kernel build of each system, and the headers each mode takes.
pp.py runs -E on "#include <HEADER>" and keeps the text that comes from files under the sysroot.
The text from the compiler's own headers (stddef.h, stdarg.h and the others) is left out, because each compiler has its own.
The text is cut into tokens, so spaces and line breaks are not compared.

The expected file has one line for each unit: the exit status, the number of tokens and a digest of the tokens.
The files the text came from are not compared, because GCC marks a file that gives no text and rucc does not.
When the exit status is not 0, only the status is compared.
--keep writes the files and the tokens of each unit to a directory, so a difference can be read.
The units run at the same time, one for each CPU unless -j says otherwise.

accepted.txt lists the known differences, each with the issue that owns it.
check fails on a difference that is not in the list, and on a line of the list that matches no difference.
"""

import argparse
import concurrent.futures
import fnmatch
import hashlib
import os
import re
import shlex
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROWS = os.path.join(HERE, "..", "bsd-abi", "rows.txt")

TOKEN = re.compile(r"""
    [A-Za-z_$][A-Za-z0-9_$]*
  | \.?[0-9](?:[eEpP][+-]|[A-Za-z0-9_.'])*
  | (?:u8|[uUL])?"(?:\\.|[^"\\\n])*"
  | (?:u8|[uUL])?'(?:\\.|[^'\\\n])*'
  | %:%:|\.\.\.|<<=|>>=
  | ->|\+\+|--|<<|>>|<=|>=|==|!=|&&|\|\||\*=|/=|%=|\+=|-=|&=|\^=|\|=|\#\#|<:|:>|<%|%>|%:
  | \S
""", re.X)
MARKER = re.compile(r'#\s*(?:line\s+)?\d+\s+"((?:\\.|[^"\\])*)"')


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
        ident, system, arch, target, gnuc, reference, url, digest = r
        out.append(dict(id=ident, system=system, arch=arch, target=target, gnuc=gnuc, reference=reference))
    return out


def find_row(ident):
    for r in rows():
        if r["id"] == ident:
            return r
    sys.exit(f"pp.py: no row {ident} in {ROWS}")


def modes(system):
    """Return a list of (name, directories, flags) for a system."""
    out = []
    for r in table(os.path.join(HERE, "modes.txt")):
        name, sys_, dirs, flags = r[0], r[1], r[2], r[3:]
        if sys_ in ("all", system):
            out.append((name, dirs.split(","), flags))
    return out


def headers(sysroot, dirs):
    """The headers of the set in the directories, in name order. The directory . is usr/include itself."""
    top = os.path.join(sysroot, "usr", "include")
    out = []
    for d in dirs:
        path = os.path.join(top, d)
        if not os.path.isdir(path):
            continue
        for name in sorted(os.listdir(path)):
            if name.endswith(".h") and os.path.isfile(os.path.join(path, name)):
                out.append(name if d == "." else f"{d}/{name}")
    return out


def run(argv, text):
    try:
        p = subprocess.run(argv, input=text, capture_output=True, text=True, timeout=120, errors="replace",
                           env=dict(os.environ, LC_ALL="C"))
    except (OSError, subprocess.TimeoutExpired) as e:
        return 127, "", str(e)
    return p.returncode, p.stdout, p.stderr


def own(text, sysroot):
    """The files under the sysroot that the text came from, in order of first use, and the text from them."""
    root = os.path.realpath(sysroot) + os.sep
    files = []
    keep = []
    mine = False
    seen = set()
    for line in text.splitlines():
        m = MARKER.match(line)
        if m:
            path = m.group(1)
            real = os.path.realpath(path) if path.startswith("/") else ""
            mine = real.startswith(root)
            if mine:
                rel = real[len(root):]
                if rel not in seen:
                    seen.add(rel)
                    files.append(rel)
            continue
        if mine:
            keep.append(line)
    return files, keep


def short(data):
    return hashlib.sha256(data.encode()).hexdigest()[:16]


def preprocess(cc, sysroot, mode_flags, header):
    """Return (answer, files, tokens) for one unit."""
    rc, out, err = run(cc + [f"--sysroot={sysroot}"] + mode_flags + ["-E", "-x", "c", "-"], f"#include <{header}>\n")
    if rc != 0:
        first = next((l for l in err.splitlines() if "error" in l), "")
        return f"rc={rc}", [], [first]
    files, text = own(out, sysroot)
    tokens = TOKEN.findall("\n".join(text))
    answer = f"rc=0 tokens={len(tokens)} text={short(chr(10).join(tokens))}"
    return answer, files, tokens


def answers(cc, row, sysroot, keep=None, jobs=None):
    # A compiler writes the line markers with the sysroot as it was given, and own() keeps only the absolute paths.
    sysroot = os.path.abspath(sysroot)
    units =[(name, flags, h) for name, dirs, flags in modes(row["system"]) for h in headers(sysroot, dirs)]
    with concurrent.futures.ThreadPoolExecutor(jobs or os.cpu_count()) as pool:
        done = list(pool.map(lambda u: preprocess(cc, sysroot, u[1], u[2]), units))
    out = []
    for (name, _, h), (answer, files, tokens) in zip(units, done):
        out.append((f"{name}:{h}", answer))
        if keep:
            path = os.path.join(keep, row["id"], name, h + ".txt")
            os.makedirs(os.path.dirname(path), exist_ok=True)
            with open(path, "w") as f:
                f.write("".join(f"# {x}\n" for x in files))
                f.write("\n".join(tokens) + "\n")
    return out


def parse(lines):
    out = {}
    for line in lines:
        if line and not line.startswith("#"):
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


def cmd_dump(a):
    row = find_row(a.row)
    cc = shlex.split(a.cc)
    _, version, _ = run(cc + ["--version"], "")
    text = [f"# {row['id']}: {row['system']} {row['arch']}, reference {row['reference']}",
            f"# command: {a.cc} --sysroot=SET",
            f"# version: {version.splitlines()[0] if version else 'unknown'}"]
    for note in a.note:
        text.append(f"# {note}")
    text += [f"{k} {v}" for k, v in answers(cc, row, a.sysroot, a.keep, a.jobs)]
    with open(a.o, "w") as f:
        f.write("\n".join(text) + "\n")


def cmd_check(a):
    acc = accepted()
    bad = 0
    report = []
    for row in rows():
        if a.rows and not any(fnmatch.fnmatch(row["id"], g) for g in a.rows):
            continue
        path = os.path.join(HERE, "expected", row["id"] + ".txt")
        if not os.path.exists(path):
            print(f"{row['id']}: no reference file in expected/, skipped")
            continue
        sysroot = os.path.join(a.sets, row["id"])
        if not os.path.isdir(os.path.join(sysroot, "usr", "include")):
            print(f"{row['id']}: no headers in {sysroot}, run abi.py fetch first")
            bad += 1
            continue
        with open(path) as f:
            ref = parse(f.read().splitlines())
        cc = [a.rucc, f"--target={row['target']}", f"-fgnuc-version={row['gnuc']}"]
        got = dict(answers(cc, row, sysroot, a.keep, a.jobs))
        new = known = 0
        for k in list(ref) + [k for k in got if k not in ref]:
            r, g = ref.get(k, "(no unit)"), got.get(k, "(no unit)")
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
        print(f"{row['id']}: {len(ref)} units, {new} new differences, {known} accepted")
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
        print(f"bsd-pp: {bad} problems")
        return 1
    print("bsd-pp: no new differences")
    return 0


def main():
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = p.add_subparsers(dest="cmd", required=True)
    d = sub.add_parser("dump")
    d.add_argument("row")
    d.add_argument("--cc", required=True)
    d.add_argument("--sysroot", required=True)
    d.add_argument("--note", action="append", default=[])
    d.add_argument("--keep", help="write the files and the tokens of each unit under this directory")
    d.add_argument("-o", required=True)
    d.add_argument("-j", "--jobs", type=int, help="run this many compilers at once (default: one for each CPU)")
    c = sub.add_parser("check")
    c.add_argument("--rucc", required=True)
    c.add_argument("--sets", required=True, help="the directory that abi.py fetch unpacked the rows in")
    c.add_argument("--rows", action="append", default=[], help="only the rows that match this glob")
    c.add_argument("--keep", help="write the files and the tokens of each unit under this directory")
    c.add_argument("--report", help="write each difference to this file")
    c.add_argument("-j", "--jobs", type=int, help="run this many compilers at once (default: one for each CPU)")
    c.add_argument("-v", "--verbose", action="store_true", help="print each difference")
    a = p.parse_args()
    if a.cmd == "dump":
        cmd_dump(a)
    else:
        sys.exit(cmd_check(a))


if __name__ == "__main__":
    main()
