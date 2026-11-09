#!/usr/bin/env python3
"""bsd-abi: the type layouts of the installed BSD headers under rucc, against the reference GCC.

    abi.py fetch ROW DIR                      download the release set of ROW, check its digest, unpack usr/include
    abi.py scan ROW --cc 'CMD' --sysroot DIR -o FILE   measure every type with the reference CMD
    abi.py check --rucc RUCC --sets DIR       compare rucc with the expected files

rows.txt gives the rows.
Each row is one release of one system on one architecture, with the release set that holds its headers and the digest of that set.
headers.txt gives the headers to include.

scan preprocesses each header with line markers and finds the types that the files under the sysroot define: each struct, union and enum with a tag, and each typedef.
For each type it asks for the size and the alignment.
For each named member of a struct or union that is not a bit field, it asks for the offset.
Each question is a char array whose size is the answer, in an object file that the reference compiles.
The sizes of the symbols are the answers.
A question that the reference rejects (an incomplete type, a function type) is left out.

check writes each answer as a _Static_assert and gives the file to rucc with -fsyntax-only.
Each assertion that fails is a difference.
rucc's back end does not have to know the architecture for this.
accepted.txt lists the known differences, each with the issue that owns it.
"""

import argparse
import fnmatch
import hashlib
import os
import re
import shlex
import struct
import subprocess
import sys
import tarfile
import tempfile
import urllib.request

HERE = os.path.dirname(os.path.abspath(__file__))
STD = "-std=gnu11"


def table(name):
    out = []
    with open(os.path.join(HERE, name)) as f:
        for line in f:
            line = line.strip()
            if line and not line.startswith("#"):
                out.append(line.split())
    return out


def rows():
    out = []
    for r in table("rows.txt"):
        ident, system, arch, target, gnuc, reference, url, digest = r
        out.append(dict(id=ident, system=system, arch=arch, target=target, gnuc=gnuc, reference=reference, url=url,
                        digest=digest))
    return out


def find_row(ident):
    for r in rows():
        if r["id"] == ident:
            return r
    sys.exit(f"abi.py: no row {ident} in rows.txt")


def headers(system):
    return [h for s, h in table("headers.txt") if s in ("all", system)]


def run(argv, text=None, cwd=None):
    p = subprocess.run(argv, input=text, capture_output=True, text=True, cwd=cwd)
    return p.returncode, p.stdout, p.stderr


# fetch


def cmd_fetch(a):
    row = find_row(a.row)
    os.makedirs(a.dir, exist_ok=True)
    root = os.path.join(a.dir, row["id"])
    if os.path.isdir(os.path.join(root, "usr", "include")):
        # Unpacked before, from a set with the right digest.
        print(root)
        return
    name = os.path.join(a.dir, os.path.basename(row["url"]))
    algo, want = row["digest"].split(":")
    if not os.path.exists(name) or digest(name, algo) != want:
        print(f"fetch {row['url']}")
        urllib.request.urlretrieve(row["url"], name)
    got = digest(name, algo)
    if got != want:
        sys.exit(f"abi.py: {name}: {algo} is {got}, rows.txt says {want}")
    with tarfile.open(name) as t:
        wanted = [m for m in t.getmembers() if m.name.lstrip("./").startswith("usr/include/")
                  and (m.isfile() or m.isdir() or m.issym())]
        try:
            t.extractall(root, members=wanted, filter="tar")
        except TypeError:
            t.extractall(root, members=wanted)
    print(root)


def digest(path, algo):
    h = hashlib.new(algo)
    with open(path, "rb") as f:
        for block in iter(lambda: f.read(1 << 20), b""):
            h.update(block)
    return h.hexdigest()


# finding the types


def own_text(text, sysroot):
    """The preprocessed text that comes from files under the sysroot, without the line markers."""
    keep = []
    mine = False
    root = os.path.realpath(sysroot)
    for line in text.splitlines():
        m = re.match(r'#\s*\d+\s+"([^"]*)"', line)
        if m:
            path = m.group(1)
            mine = os.path.realpath(path).startswith(root + os.sep) if path.startswith("/") else False
            continue
        if mine:
            keep.append(line)
    return "\n".join(keep)


def strip_attributes(text):
    """Remove __attribute__((...)), __asm__(...) and __declspec-like groups, which hide the names."""
    out = []
    i = 0
    pat = re.compile(r"\b(__attribute__|__attribute|__asm__|__asm|asm|__extension__|__restrict|__inline)\b")
    while True:
        m = pat.search(text, i)
        if not m:
            out.append(text[i:])
            break
        out.append(text[i:m.start()])
        j = m.end()
        if m.group(1) in ("__extension__", "__restrict", "__inline"):
            i = j
            continue
        while j < len(text) and text[j].isspace():
            j += 1
        if j < len(text) and text[j] == "(":
            depth = 0
            while j < len(text):
                if text[j] == "(":
                    depth += 1
                elif text[j] == ")":
                    depth -= 1
                    if depth == 0:
                        j += 1
                        break
                j += 1
        i = j
    return " ".join(out)


def split_top(text, sep):
    """Split at sep where no bracket is open."""
    parts, depth, cur = [], 0, []
    for ch in text:
        if ch in "({[":
            depth += 1
        elif ch in ")}]":
            depth -= 1
        if ch == sep and depth == 0:
            parts.append("".join(cur))
            cur = []
        else:
            cur.append(ch)
    parts.append("".join(cur))
    return parts


def matching(text, at):
    """The index after the bracket that closes the one at text[at]."""
    depth = 0
    for i in range(at, len(text)):
        if text[i] in "({[":
            depth += 1
        elif text[i] in ")}]":
            depth -= 1
            if depth == 0:
                return i + 1
    return len(text)


def declarator_name(decl):
    decl = decl.split("=")[0].strip()
    m = re.search(r"\(\s*\*+\s*(?:const\s+)?(\w+)\s*(\[[^\]]*\]\s*)*\)", decl)
    if m:
        return m.group(1)
    m = re.search(r"(\w+)\s*(\[[^\]]*\]\s*)*$", decl)
    if m and m.group(1) not in KEYWORDS:
        return m.group(1)
    return None


KEYWORDS = {"int", "char", "short", "long", "unsigned", "signed", "float", "double", "void", "const", "volatile",
            "struct", "union", "enum", "_Bool", "__int128", "_Complex", "__complex__"}


def members(body):
    """The names of the members of a struct or union body that offsetof can take."""
    names = []
    for part in split_top(body, ";"):
        part = part.strip()
        if not part or part.startswith("_Static_assert"):
            continue
        # A member whose type is a struct or union written out in place: drop the body, keep the declarators.
        brace = part.find("{")
        if brace >= 0:
            end = matching(part, brace)
            part = part[:brace] + " " + part[end:]
            if re.fullmatch(r"\s*(struct|union)(\s+\w+)?\s*", part):
                continue  # an anonymous member
        for decl in split_top(part, ","):
            if ":" in decl:
                continue  # a bit field
            name = declarator_name(decl)
            if name:
                names.append(name)
    return names


def find_types(text):
    """Return {type: [members]} for the types the text defines."""
    text = strip_attributes(text)
    types = {}
    for m in re.finditer(r"\b(struct|union|enum)\s+(\w+)\s*\{", text):
        kind, tag = m.group(1), m.group(2)
        open_ = m.end() - 1
        body = text[open_ + 1:matching(text, open_) - 1]
        types[f"{kind} {tag}"] = members(body) if kind != "enum" else []
    # The file scope statements, with the bodies of the definitions kept for the typedefs.
    depth = 0
    start = 0
    for i, ch in enumerate(text):
        if ch in "({[":
            depth += 1
        elif ch in ")}]":
            depth -= 1
        elif ch == ";" and depth == 0:
            stmt = text[start:i].strip()
            start = i + 1
            if not stmt.startswith("typedef"):
                continue
            stmt = stmt[len("typedef"):]
            body_members = None
            brace = stmt.find("{")
            if brace >= 0:
                head = stmt[:brace]
                end = matching(stmt, brace)
                if re.search(r"\b(struct|union)\b", head):
                    body_members = members(stmt[brace + 1:end - 1])
                stmt = head + " " + stmt[end:]
            for decl in split_top(stmt, ","):
                name = declarator_name(decl)
                if name:
                    types[name] = body_members if body_members is not None and "*" not in decl else []
    return types


def questions(types):
    """The list of (expression) that scan measures, in a fixed order."""
    out = []
    for t in sorted(types):
        out.append(f"sizeof({t})")
        out.append(f"_Alignof({t})")
        for name in sorted(set(types[t])):
            out.append(f"__builtin_offsetof({t}, {name})")
    return out


# measuring


def probe_source(hdrs, qs):
    lines = [f"#include <{h}>" for h in hdrs]
    first = len(lines) + 1
    for n, q in enumerate(qs):
        lines.append(f"char abi_{n}[({q}) + 1];")
    return "\n".join(lines) + "\n", first


def elf_symbol_sizes(path):
    """{name: size} for the symbols of a little endian ELF64 or ELF32 object."""
    with open(path, "rb") as f:
        data = f.read()
    if data[:4] != b"\x7fELF":
        sys.exit(f"abi.py: {path} is not ELF")
    wide = data[4] == 2
    if wide:
        shoff, = struct.unpack_from("<Q", data, 0x28)
        shentsize, shnum = struct.unpack_from("<HH", data, 0x3A)
    else:
        shoff, = struct.unpack_from("<I", data, 0x20)
        shentsize, shnum = struct.unpack_from("<HH", data, 0x2E)
    sections = []
    for i in range(shnum):
        at = shoff + i * shentsize
        if wide:
            name, kind, flags, addr, off, size, link, info, align, entsize = struct.unpack_from("<IIQQQQIIQQ", data, at)
        else:
            name, kind, flags, addr, off, size, link, info, align, entsize = struct.unpack_from("<IIIIIIIIII", data, at)
        sections.append((kind, off, size, link, entsize))
    out = {}
    for kind, off, size, link, entsize in sections:
        if kind != 2:  # SHT_SYMTAB
            continue
        strtab = sections[link]
        for at in range(off, off + size, entsize):
            if wide:
                name, info, other, shndx, value, sz = struct.unpack_from("<IBBHQQ", data, at)
            else:
                name, value, sz, info, other, shndx = struct.unpack_from("<IIIBBH", data, at)
            s = data[strtab[1] + name:data.index(b"\0", strtab[1] + name)].decode()
            out[s] = sz
    return out


def measure(cc, sysroot, hdrs, qs):
    """Return {question: value} for every question cc answers."""
    with tempfile.TemporaryDirectory() as tmp:
        src = os.path.join(tmp, "probe.c")
        obj = os.path.join(tmp, "probe.o")
        live = list(qs)
        for _ in range(8):
            text, first = probe_source(hdrs, live)
            with open(src, "w") as f:
                f.write(text)
            rc, _, err = run(cc + [f"--sysroot={sysroot}", STD, "-fno-common", "-c", src, "-o", obj])
            if rc == 0:
                sizes = elf_symbol_sizes(obj)
                return {q: sizes[f"abi_{n}"] - 1 for n, q in enumerate(live) if f"abi_{n}" in sizes}
            bad = {int(m.group(1)) - first for m in re.finditer(r"probe\.c:(\d+):\d+: error:", err)}
            bad = {b for b in bad if 0 <= b < len(live)}
            if not bad:
                sys.exit("abi.py: the headers do not compile:\n" + err[:4000])
            live = [q for n, q in enumerate(live) if n not in bad]
        sys.exit("abi.py: still rejected after eight rounds:\n" + err[:4000])


def cmd_scan(a):
    row = find_row(a.row)
    cc = shlex.split(a.cc)
    hdrs = []
    types = {}
    for h in headers(row["system"]):
        rc, out, err = run(cc + [f"--sysroot={a.sysroot}", STD, "-E", "-x", "c", "-"], f"#include <{h}>\n")
        if rc != 0:
            lines = [line for line in err.splitlines() if line.strip()]
            first = next((line for line in lines if "error" in line), lines[0] if lines else "no message")
            print(f"{row['id']}: {h} does not preprocess, left out: {first}")
            continue
        hdrs.append(h)
        types.update(find_types(own_text(out, a.sysroot)))
    if not hdrs:
        sys.exit(f"abi.py: {row['id']}: no header preprocesses")
    answers = measure(cc, a.sysroot, hdrs, questions(types))
    _, version, _ = run(cc + ["--version"])
    text = [f"# {row['id']}: {row['system']} {row['arch']}, reference {row['reference']}",
            f"# command: {a.cc} --sysroot=SET {STD}",
            f"# version: {version.splitlines()[0] if version else 'unknown'}",
            f"# headers: {row['url']} {row['digest']}"]
    for note in a.note:
        text.append(f"# {note}")
    text.append("[headers] " + " ".join(hdrs))
    text += [f"{q} = {v}" for q, v in sorted(answers.items())]
    with open(a.o, "w") as f:
        f.write("\n".join(text) + "\n")
    print(f"{row['id']}: {len(hdrs)} headers, {len(types)} types, {len(answers)} answers")


# checking


def read_expected(path):
    hdrs, answers = [], []
    with open(path) as f:
        for line in f:
            line = line.rstrip("\n")
            if not line or line.startswith("#"):
                continue
            if line.startswith("[headers]"):
                hdrs = line.split()[1:]
                continue
            q, v = line.rsplit(" = ", 1)
            answers.append((q, int(v)))
    return hdrs, answers


def accepted():
    out = []
    path = os.path.join(HERE, "accepted.txt")
    if not os.path.exists(path):
        return out
    with open(path) as f:
        for n, line in enumerate(f, 1):
            line = line.strip()
            if line and not line.startswith("#"):
                row, rest = line.split(None, 1)
                q, issue = rest.rsplit(None, 1)
                out.append(dict(line=n, row=row, q=q, issue=issue, used=0))
    return out


def check_row(rucc, row, sysroot):
    """Return a list of (question, reference value, what rucc said)."""
    hdrs, answers = read_expected(os.path.join(HERE, "expected", row["id"] + ".txt"))
    lines = [f"#include <{h}>" for h in hdrs]
    first = len(lines) + 1
    for n, (q, v) in enumerate(answers):
        lines.append(f'_Static_assert(({q}) == {v}, "abi {n}");')
    with tempfile.TemporaryDirectory() as tmp:
        src = os.path.join(tmp, "abi.c")
        with open(src, "w") as f:
            f.write("\n".join(lines) + "\n")
        cc = [rucc, f"--target={row['target']}", f"-fgnuc-version={row['gnuc']}", f"--sysroot={sysroot}", STD]
        rc, _, err = run(cc + ["-fsyntax-only", src])
    out = []
    seen = set()
    for line in err.splitlines():
        m = re.match(r".*abi\.c:(\d+):\d+: error: (.*)", line)
        if not m:
            continue
        n = int(m.group(1)) - first
        if 0 <= n < len(answers) and n not in seen:
            seen.add(n)
            q, v = answers[n]
            said = "a different value" if "static assertion failed" in m.group(2) else m.group(2)
            out.append((q, v, said))
        elif n < 0:
            out.append(("#include", 0, m.group(2)))
    if rc != 0 and not out:
        out.append(("rucc", 0, err.strip().splitlines()[-1] if err.strip() else f"exit {rc}"))
    return out, len(answers)


def cmd_check(a):
    acc = accepted()
    bad = 0
    report = []
    for row in rows():
        if a.rows and not any(fnmatch.fnmatch(row["id"], g) for g in a.rows):
            continue
        if not os.path.exists(os.path.join(HERE, "expected", row["id"] + ".txt")):
            print(f"{row['id']}: no reference file in expected/, skipped")
            continue
        sysroot = os.path.join(a.sets, row["id"])
        if not os.path.isdir(os.path.join(sysroot, "usr", "include")):
            print(f"{row['id']}: no headers in {sysroot}, run abi.py fetch first")
            bad += 1
            continue
        diffs, total = check_row(a.rucc, row, sysroot)
        new = known = 0
        for q, v, said in diffs:
            hit = [e for e in acc if fnmatch.fnmatch(row["id"], e["row"]) and fnmatch.fnmatch(q, e["q"])]
            for e in hit:
                e["used"] += 1
            if hit:
                known += 1
                tag = hit[0]["issue"]
            else:
                new += 1
                tag = "NEW"
            report.append(f"{row['id']} {q} {tag}")
            report.append(f"    reference: {v}")
            report.append(f"    rucc:      {said}")
        print(f"{row['id']}: {total} answers, {new} new differences, {known} accepted")
        bad += new
    for e in acc:
        if not e["used"] and not a.rows:
            print(f"accepted.txt:{e['line']}: {e['row']} {e['q']} matches no difference")
            bad += 1
    if a.report:
        with open(a.report, "w") as f:
            f.write("\n".join(report) + "\n")
    elif report and a.verbose:
        print("\n".join(report))
    if bad:
        print(f"bsd-abi: {bad} problems")
        return 1
    print("bsd-abi: no new differences")
    return 0


def main():
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = p.add_subparsers(dest="cmd", required=True)
    f = sub.add_parser("fetch")
    f.add_argument("row")
    f.add_argument("dir")
    s = sub.add_parser("scan")
    s.add_argument("row")
    s.add_argument("--cc", required=True)
    s.add_argument("--sysroot", required=True)
    s.add_argument("--note", action="append", default=[])
    s.add_argument("-o", required=True)
    c = sub.add_parser("check")
    c.add_argument("--rucc", required=True)
    c.add_argument("--sets", required=True, help="the directory abi.py fetch unpacked the sets in")
    c.add_argument("--rows", action="append", default=[], help="only the rows that match this glob")
    c.add_argument("--report", help="write each difference to this file")
    c.add_argument("-v", "--verbose", action="store_true", help="print each difference")
    a = p.parse_args()
    if a.cmd == "fetch":
        cmd_fetch(a)
    elif a.cmd == "scan":
        cmd_scan(a)
    else:
        sys.exit(cmd_check(a))


if __name__ == "__main__":
    main()
