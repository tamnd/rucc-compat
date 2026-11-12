#!/usr/bin/env python3
"""bsd-asm: the .S units of a BSD kernel and its modules under rucc, against the reference GCC and GNU as.

    asm.py fetch ROW DIR [--archive]      download the source set of ROW, check its digest, unpack the files the units read
    asm.py scan ROW --cc CC --sys DIR --work DIR -o FILE   assemble every .S unit with the reference and describe each object
    asm.py check --rucc RUCC --src DIR    assemble every unit with rucc and compare its object with the expected file

rows.txt gives the rows. Each row is one kernel configuration of one release on one architecture, with the
source set that holds sys/ and the digest of that set.

scan runs on the release itself. It configures the kernel with config(8) and builds the object of every file
of SFILES, the .S and .s files of the configuration. Then it walks sys/modules the way the kernel build does
and builds the object of every .S and .s file in the SRCS of each module. A wrapper in front of the reference
compiler writes down each call that assembles a file, with its directory. Then scan makes each object again
from those calls, with the dependency flags taken off, and describes it: each section with its type, flags,
alignment, entry size, size and contents, the relocations against it, and the symbols. The contents are
written as a digest of each 256 bytes, so a difference can be placed without keeping the bytes. The files
of the build directories that a unit includes, such as assym.inc and the opt_*.h files, go into the
expected file, and so do the links the build made, such as machine. The files of sys/ that the units read
are listed by path.

check unpacks those files in a scratch directory, runs rucc with the same flags in the same directory, with
the target and the -fgnuc-version of the row, and describes rucc's object the same way. rucc preprocesses
and assembles the file itself, as the reference driver did.

The comparison is the one of the kernel-asm corpus (crates/rucc-compat/src/elf.rs). A relocation against a
local symbol is read as one against its section plus the symbol's offset. The contents of .comment and
.note.gnu.property are not compared. Section and file symbols are not compared. The .debug_ sections are
left out, since what -g makes the assembler write names the directories of the build.
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
CHUNK = 256
STEP_TIME = 300

# The directory of sys/ that holds the kernel configurations of an arch.
MACHINE = {"x86_64": "amd64", "aarch64": "arm64", "riscv64": "riscv"}

WRAPPER = """#!/bin/sh
# Write down each call that assembles a .S or .s file, with its directory, then run the reference compiler.
for a in "$@"; do
\tcase $a in
\t*.S | *.s)
\t\t{ pwd; printf '%s\\n' "$@"; echo @@; } >> "$ASM_LOG"
\t\tbreak
\t\t;;
\tesac
done
exec "$ASM_CC" "$@"
"""


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
        ident, system, arch, target, gnuc, reference, kernconf, url, digest = r
        out.append(dict(id=ident, system=system, arch=arch, target=target, gnuc=gnuc, reference=reference,
                        kernconf=kernconf, url=url, digest=digest))
    return out


def find_row(ident):
    for r in rows():
        if r["id"] == ident:
            return r
    sys.exit(f"asm.py: no row {ident} in rows.txt")


def expected_path(row):
    return os.path.join(HERE, "expected", row["id"] + ".txt")


def run(argv, cwd=None, env=None, timeout=STEP_TIME):
    try:
        p = subprocess.run(argv, capture_output=True, text=True, cwd=cwd, env=env, timeout=timeout)
    except subprocess.TimeoutExpired:
        return 124, "", f"{argv[0]}: no answer in {timeout} seconds"
    return p.returncode, p.stdout, p.stderr


def first_line(text):
    for line in text.splitlines():
        if line.strip():
            return line.strip()
    return ""


# ELF


SHT_SYMTAB, SHT_STRTAB, SHT_RELA, SHT_NOBITS, SHT_REL, SHT_GROUP, SHT_SYMTAB_SHNDX = 2, 3, 4, 8, 9, 17, 18
SHF_INFO_LINK, SHF_LINK_ORDER = 0x40, 0x80
STB_LOCAL, STT_SECTION, STT_FILE = 0, 3, 4
SHN_UNDEF, SHN_ABS, SHN_COMMON, SHN_XINDEX = 0, 0xfff1, 0xfff2, 0xffff

# Sections whose contents are a note about the tool that wrote them rather than about the code.
TOOL_NOTES = (".comment", ".note.gnu.property")


def left_out(name):
    """The DWARF sections -g makes the assembler write, which name the directories of the build."""
    return name.startswith(".debug_") or name.startswith(".rela.debug_") or name.startswith(".rel.debug_")


def read_elf(data):
    """Read a little endian ELF64 relocatable object into sections and symbols, as elf.rs does."""
    if len(data) < 64 or data[:4] != b"\x7fELF" or data[4] != 2 or data[5] != 1:
        raise ValueError("not a little endian ELF64 file")
    if struct.unpack_from("<H", data, 16)[0] != 1:
        raise ValueError("not a relocatable object")
    shoff = struct.unpack_from("<Q", data, 40)[0]
    shentsize, shnum, shstrndx = struct.unpack_from("<HHH", data, 58)
    if shoff and shentsize >= 64:
        first = struct.unpack_from("<IIQQQQIIQQ", data, shoff)
        if shnum == 0:
            shnum = first[5]
        if shstrndx == SHN_XINDEX:
            shstrndx = first[6]
    headers = []
    for n in range(shnum):
        name, kind, flags, _, offset, size, link, info, align, entsize = struct.unpack_from(
            "<IIQQQQIIQQ", data, shoff + n * shentsize)
        headers.append(dict(name=name, kind=kind, flags=flags, offset=offset, size=size, link=link, info=info,
                            align=align, entsize=entsize))

    def contents(h):
        if h["kind"] == SHT_NOBITS:
            return b""
        if h["offset"] + h["size"] > len(data):
            raise ValueError("a section runs past the end of the file")
        return data[h["offset"]:h["offset"] + h["size"]]

    def string(table_, at):
        end = table_.find(b"\0", at)
        return table_[at:end if end >= 0 else len(table_)].decode("utf-8", "replace")

    names = contents(headers[shstrndx]) if shstrndx < len(headers) else b""

    def name_of(n):
        return string(names, headers[n]["name"]) if n < len(headers) else ""

    raw = []
    symtab = next((h for h in headers if h["kind"] == SHT_SYMTAB), None)
    if symtab:
        strings = contents(headers[symtab["link"]]) if symtab["link"] < len(headers) else b""
        shndx = next((contents(h) for h in headers if h["kind"] == SHT_SYMTAB_SHNDX), None)
        body = contents(symtab)
        for n in range(len(body) // 24):
            st_name, info, other, section, value, size = struct.unpack_from("<IBBHQQ", body, n * 24)
            if section == SHN_XINDEX and shndx is not None and len(shndx) >= n * 4 + 4:
                section = struct.unpack_from("<I", shndx, n * 4)[0]
            raw.append(dict(name=string(strings, st_name), section=section, value=value, size=size, info=info,
                            other=other))

    def place(section):
        return {SHN_UNDEF: "UND", SHN_ABS: "ABS", SHN_COMMON: "COM"}.get(section) or name_of(section)

    def target(index):
        if index >= len(raw):
            return f"#{index}", 0
        sym = raw[index]
        bind, kind = sym["info"] >> 4, sym["info"] & 0xf
        defined = sym["section"] not in (SHN_UNDEF, SHN_ABS, SHN_COMMON)
        if kind == STT_SECTION or (bind == STB_LOCAL and defined and index != 0):
            return f"[{place(sym['section'])}]", 0 if kind == STT_SECTION else sym["value"]
        return sym["name"], 0

    relocs = {}
    for h in headers:
        if h["kind"] not in (SHT_RELA, SHT_REL):
            continue
        rela = h["kind"] == SHT_RELA
        body = contents(h)
        step = 24 if rela else 16
        out = relocs.setdefault(h["info"], [])
        for at in range(0, len(body) - step + 1, step):
            offset, info = struct.unpack_from("<QQ", body, at)
            addend = struct.unpack_from("<q", body, at + 16)[0] if rela else 0
            name, more = target(info >> 32)
            out.append((offset, info & 0xffffffff, name, addend + more))

    sections = []
    for n, h in enumerate(headers):
        if n == 0 or h["kind"] in (SHT_SYMTAB, SHT_STRTAB, SHT_RELA, SHT_REL, SHT_SYMTAB_SHNDX):
            continue
        name = name_of(n)
        if left_out(name):
            continue
        body = contents(h)
        if h["kind"] == SHT_GROUP:
            signature = raw[h["info"]]["name"] if h["info"] < len(raw) else ""
            text = f"signature {signature}\n"
            for at in range(0, len(body) - 3, 4):
                word = struct.unpack_from("<I", body, at)[0]
                text += f"flags {word}\n" if at == 0 else name_of(word) + "\n"
            body = text.encode()
        sections.append(dict(
            name=name, type=h["kind"], flags=h["flags"] & ~SHF_INFO_LINK, align=h["align"], entsize=h["entsize"],
            size=h["size"], link=name_of(h["link"]) if h["flags"] & SHF_LINK_ORDER else "-",
            data=body, chunks=chunks(body) if h["kind"] != SHT_NOBITS else [],
            relocs=sorted(relocs.get(n, []))))
    symbols = sorted(
        (s["name"] or "-", place(s["section"]), s["value"], s["size"], s["info"] >> 4, s["info"] & 0xf, s["other"])
        for s in raw[1:] if (s["info"] & 0xf) not in (STT_SECTION, STT_FILE))
    return dict(sections=sections, symbols=symbols)


def chunks(data):
    return [hashlib.sha256(data[at:at + CHUNK]).hexdigest()[:8] for at in range(0, len(data), CHUNK)]


def describe(obj):
    """The lines of an object in the expected file."""
    out = []
    for s in obj["sections"]:
        note = s["name"] in TOOL_NOTES
        size = "-" if note else s["size"]
        data = "-" if note or not s["chunks"] else ",".join(s["chunks"])
        out.append(f"section {s['name']} type={s['type']} flags={s['flags']:#x} align={s['align']} "
                   f"entsize={s['entsize']} size={size} link={s['link']} bytes={data}")
        for offset, kind, name, addend in s["relocs"]:
            out.append(f"reloc {offset:#x} {kind} {name} {addend}")
    for name, section, value, size, bind, kind, other in obj["symbols"]:
        out.append(f"symbol {name} {section} {value:#x} {size} {bind} {kind} {other}")
    return out


def parse_description(lines):
    sections, symbols = [], []
    for line in lines:
        word, rest = line.split(" ", 1)
        if word == "section":
            name, *fields = rest.split(" ")
            f = dict(x.split("=", 1) for x in fields)
            note = f["size"] == "-"
            sections.append(dict(
                name=name, type=int(f["type"]), flags=int(f["flags"], 16), align=int(f["align"]),
                entsize=int(f["entsize"]), size=None if note else int(f["size"]), link=f["link"],
                chunks=[] if f["bytes"] == "-" else f["bytes"].split(","), data=None, relocs=[]))
        elif word == "reloc":
            offset, kind, name, addend = rest.split(" ")
            sections[-1]["relocs"].append((int(offset, 16), int(kind), name, int(addend)))
        elif word == "symbol":
            name, section, value, size, bind, kind, other = rest.split(" ")
            symbols.append((name, section, int(value, 16), int(size), int(bind), int(kind), int(other)))
    return dict(sections=sections, symbols=symbols)


def family(name):
    for prefix in (".text.", ".data.", ".rodata.", ".bss."):
        if name.startswith(prefix) and len(name) > len(prefix):
            return prefix[:-1]
    return name


def compare(theirs, ours):
    """Each way rucc's object differs from the reference, as (bucket, detail), in the order of elf.rs."""
    out = []

    def keyed(obj):
        seen, keys = {}, {}
        for at, s in enumerate(obj["sections"]):
            seen[s["name"]] = seen.get(s["name"], 0) + 1
            keys[(s["name"], seen[s["name"]])] = at
        return keys

    mine, yours = keyed(theirs), keyed(ours)
    for key in mine:
        if key not in yours:
            out.append((f"section missing: {family(key[0])}", f"{key[0]} is in the reference and not in rucc's object"))
    for key in yours:
        if key not in mine:
            out.append((f"extra section: {family(key[0])}", f"{key[0]} is in rucc's object and not in the reference"))
    for key, a in mine.items():
        if key in yours:
            section(theirs["sections"][a], ours["sections"][yours[key]], out)
    symbols(theirs["symbols"], ours["symbols"], out)
    if not out:
        order = [s["name"] for s in theirs["sections"]], [s["name"] for s in ours["sections"]]
        if order[0] != order[1]:
            out.append(("section order", f"{' '.join(order[0])} against {' '.join(order[1])}"))
    return out


def section(a, b, out):
    name, here = a["name"], family(a["name"])
    for what, key, show in (("type", "type", str), ("flags", "flags", hex), ("alignment", "align", str),
                            ("entry size", "entsize", str), ("link", "link", str)):
        if a[key] != b[key]:
            out.append((f"section {what}: {here}", f"{name}: {show(a[key])} against {show(b[key])}"))
    if name in TOOL_NOTES:
        return
    if a["size"] != b["size"]:
        out.append((f"section size: {here}", f"{name}: {a['size']} bytes against {b['size']}"))
    elif a["chunks"] != b["chunks"]:
        at = next(n for n, (x, y) in enumerate(zip(a["chunks"], b["chunks"])) if x != y) * CHUNK
        data = b["data"] or b""
        shown = " ".join(f"{x:02x}" for x in data[at:at + 16])
        out.append((f"section bytes: {here}",
                    f"{name}: the {CHUNK} bytes at {at:#x} differ, rucc has {shown} ..."))
    if a["relocs"] != b["relocs"]:
        first = next(((x, y) for x, y in zip(a["relocs"], b["relocs"]) if x != y), None)
        if first:
            detail = f"{name}: {reloc(first[0])} against {reloc(first[1])}"
        else:
            detail = f"{name}: {len(a['relocs'])} relocations against {len(b['relocs'])}"
        out.append((f"relocations: {here}", detail))


def reloc(r):
    return f"{r[0]:#x} type {r[1]} {r[2]}{r[3]:+d}"


def symbols(a, b, out):
    def by_name(syms):
        m = {}
        for s in syms:
            m.setdefault(s[0], []).append(s)
        return m

    mine, yours = by_name(a), by_name(b)
    for name, items in mine.items():
        if name not in yours:
            out.append(("symbol missing", f"{name} is in the reference and not in rucc's object"))
        elif yours[name] != items:
            out.append(("symbol differs", f"{name}: {symbol(items[0])} against {symbol(yours[name][0])}"))
    for name in yours:
        if name not in mine:
            out.append(("extra symbol", f"{name} is in rucc's object and not in the reference"))


def symbol(s):
    return f"{s[1]} {s[2]:#x} size {s[3]} bind {s[4]} type {s[5]} other {s[6]}"


# fetch


def cmd_fetch(a):
    row = find_row(a.row)
    os.makedirs(a.dir, exist_ok=True)
    root = os.path.join(a.dir, row["id"])
    sysdir = os.path.join(root, "usr", "src", "sys")
    if a.archive:
        print(archive(row, a.dir))
        return
    path = expected_path(row)
    if not os.path.exists(path):
        print(f"{row['id']}: no reference file in expected/, nothing to fetch")
        return
    want = set(read_expected(path)["src"])
    missing = {p for p in want if not os.path.isfile(os.path.join(sysdir, p))}
    if missing:
        name = archive(row, a.dir)
        prefix = "usr/src/sys/"
        with tarfile.open(name, "r|xz") as t:
            for m in t:
                n = m.name.lstrip("./")
                if n.startswith(prefix) and n[len(prefix):] in missing and m.isfile():
                    try:
                        t.extract(m, root, filter="tar")
                    except TypeError:
                        t.extract(m, root)
                    missing.discard(n[len(prefix):])
        if missing:
            sys.exit(f"asm.py: {len(missing)} files are not in {name}, such as {sorted(missing)[0]}")
    print(sysdir)


def archive(row, top):
    name = os.path.join(top, row["id"] + "-" + os.path.basename(row["url"]))
    algo, want = row["digest"].split(":")
    if not os.path.exists(name) or digest(name, algo) != want:
        print(f"fetch {row['url']}", file=sys.stderr)
        urllib.request.urlretrieve(row["url"], name)
    got = digest(name, algo)
    if got != want:
        sys.exit(f"asm.py: {name}: {algo} is {got}, rows.txt says {want}")
    return name


def digest(path, algo):
    h = hashlib.new(algo)
    with open(path, "rb") as f:
        for block in iter(lambda: f.read(1 << 20), b""):
            h.update(block)
    return h.hexdigest()


# scan


DROP = {"-MD", "-MMD", "-MP", "-M", "-MM"}
DROP_WITH_ARG = {"-o", "-MF", "-MT", "-MQ"}


def clean_flags(args):
    """The flags of a call without the compiler, the object and the dependency file."""
    out, skip = [], False
    for x in args:
        if skip:
            skip = False
        elif x in DROP_WITH_ARG:
            skip = True
        elif x in DROP or (x[:3] in ("-MF", "-MT", "-MQ") and len(x) > 3) or (x.startswith("-o") and len(x) > 2):
            continue
        else:
            out.append(x)
    return out


def source_of(cwd, args):
    files = [x for x in args if x.endswith((".S", ".s")) and not x.startswith("-")
             and os.path.isfile(os.path.join(cwd, x))]
    return os.path.realpath(os.path.join(cwd, files[-1])) if files else None


def make_values(cwd, exprs, env, extra=()):
    """The values of make expressions in a directory, each split into words, or None when make fails."""
    argv = ["make", *extra]
    for e in exprs:
        argv += ["-V", e]
    rc, out, err = run(argv, cwd=cwd, env=env)
    if rc != 0:
        print(f"  make -V in {cwd}: exit {rc}: " + " | ".join((out + err).strip().splitlines()[-3:]))
        return None
    lines = out.split("\n")
    return [(lines[n] if n < len(lines) else "").split() for n in range(len(exprs))]


def make(cwd, targets, env, extra=()):
    if not targets:
        return
    rc, out, err = run(["make", "-k", *extra, *targets], cwd=cwd, env=env, timeout=3600)
    if rc != 0:
        print(f"  make {' '.join(targets)} in {cwd}: exit {rc}: " + " | ".join((out + err).strip().splitlines()[-6:]))


def build_kernel(row, sysdir, work, env, wrapper):
    kdir = os.path.join(work, "K")
    conf = os.path.join(sysdir, MACHINE[row["arch"]], "conf")
    rc, out, err = run(["config", "-d", kdir, "-s", sysdir, "-I", conf, os.path.join(conf, row["kernconf"])], cwd=conf)
    if rc != 0:
        sys.exit(f"asm.py: config {row['kernconf']}: {err.strip()}")
    sfiles, ilinks, headers = make_values(kdir, ["${SFILES}", "${_ILINKS}", "${BEFORE_DEPEND:M*.h}"], env)
    print(f"kernel {row['kernconf']}: {len(sfiles)} files in SFILES")
    make(kdir, ilinks + headers, env)
    objects = sorted({os.path.basename(f).rsplit(".", 1)[0] + ".o" for f in sfiles})
    make(kdir, objects, env, [f"CC={wrapper}"])
    return kdir


def module_dirs(sysdir, env, extra):
    """The module directories of sys/modules with .S or .s files, by the SUBDIR lists from the top."""
    todo, seen, out = [os.path.join(sysdir, "modules")], set(), []
    while todo:
        d = os.path.realpath(todo.pop())
        if d in seen or not os.path.isfile(os.path.join(d, "Makefile")):
            continue
        seen.add(d)
        values = make_values(d, ["${SUBDIR}", "${KMOD}", "${SRCS:M*.[Ss]}"], env, extra)
        if values is None:
            print(f"  make -V in {d} failed, passed over")
            continue
        subdir, kmod, files = values
        todo += [os.path.join(d, s) for s in subdir if s != ".WAIT"]
        if kmod and files:
            out.append(d)
    return sorted(out)


def build_modules(sysdir, work, kdir, env, wrapper):
    extra = [f"SYSDIR={sysdir}", f"KERNBUILDDIR={kdir}"]
    dirs = module_dirs(sysdir, env, extra)
    print(f"modules: {len(dirs)} with .S or .s files")
    for d in dirs:
        rel = os.path.relpath(d, os.path.join(sysdir, "modules"))
        obj = os.path.join(work, "M", rel)
        os.makedirs(obj, exist_ok=True)
        menv = dict(env, MAKEOBJDIR=obj)
        values = make_values(d, ["${_ILINKS}", "${SRCS:M*.h}", "${SRCS:M*.[Ss]:T:R:S/$/.o/}"], menv, extra)
        if values is None:
            print(f"  {rel}: make -V failed, passed over")
            continue
        ilinks, headers, objects = values
        make(d, ilinks + headers, menv, extra)
        make(d, objects, menv, extra + [f"CC={wrapper}"])


def read_log(path):
    calls, cur = [], None
    if not os.path.exists(path):
        return calls
    with open(path) as f:
        for line in f:
            line = line.rstrip("\n")
            if cur is None:
                cur = [line]
            elif line == "@@":
                calls.append((cur[0], cur[1:]))
                cur = None
            else:
                cur.append(line)
    return calls


def read_deps(path):
    with open(path) as f:
        text = f.read().replace("\\\n", " ")
    words = []
    for line in text.splitlines():
        if ":" in line:
            words += line.split(":", 1)[1].split()
    return words


class Paths:
    """Writes the paths of the scan as $S and $W, and reads them back."""

    def __init__(self, sysdir, work):
        self.pairs = sorted({(os.path.abspath(work), "$W"), (os.path.realpath(work), "$W"),
                             (os.path.abspath(sysdir), "$S"), (os.path.realpath(sysdir), "$S")},
                            key=lambda p: -len(p[0]))

    def short(self, text):
        for long, mark in self.pairs:
            text = text.replace(long, mark)
        return text


def cmd_scan(a):
    row = find_row(a.row)
    sysdir, work = os.path.realpath(a.sys), os.path.abspath(a.work)
    os.makedirs(work, exist_ok=True)
    work = os.path.realpath(work)
    log = os.path.join(work, "calls.log")
    if os.path.exists(log):
        os.remove(log)
    wrapper = os.path.join(work, "cc")
    with open(wrapper, "w") as f:
        f.write(WRAPPER)
    os.chmod(wrapper, 0o755)
    env = dict(os.environ, ASM_LOG=log, ASM_CC=a.cc)
    kdir = build_kernel(row, sysdir, work, env, wrapper)
    build_modules(sysdir, work, kdir, env, wrapper)

    paths = Paths(sysdir, work)
    units, src, files, links, outside = {}, set(), set(), {}, set()
    scratch = os.path.join(work, "scratch")
    os.makedirs(scratch, exist_ok=True)
    calls = read_log(log)
    print(f"{len(calls)} calls assembled a file")
    for cwd, args in calls:
        source = source_of(cwd, args)
        if source is None or not source.startswith(sysdir + "/"):
            print(f"  passed over a call in {cwd}: no source file under sys/")
            continue
        where = os.path.relpath(cwd, work)
        owner = "kernel" if where == "K" else where.split(os.sep, 1)[1] if where.startswith("M" + os.sep) else where
        name = f"{owner}:{os.path.relpath(source, sysdir)}"
        if name in units:
            continue
        flags = clean_flags(args)
        obj = os.path.join(scratch, "unit.o")
        dep = os.path.join(scratch, "unit.d")
        for p in (obj, dep):
            if os.path.exists(p):
                os.remove(p)
        rc, _, err = run([a.cc, *flags, "-o", obj], cwd=cwd)
        if rc != 0:
            print(f"  {name}: the reference did not assemble it, left out: " + " | ".join(err.strip().splitlines()[:6]))
            continue
        rc, _, err = run([a.cc, *[x for x in flags if x != "-c"], "-M", "-MF", dep], cwd=cwd)
        if rc != 0:
            print(f"  {name}: no dependency list, left out: {first_line(err)}")
            continue
        with open(obj, "rb") as f:
            lines = describe(read_elf(f.read()))
        for d in read_deps(dep):
            full = os.path.normpath(os.path.join(cwd, d))
            real = os.path.realpath(full)
            if real.startswith(sysdir + "/"):
                src.add(os.path.relpath(real, sysdir))
            elif real.startswith(work + "/"):
                files.add(os.path.relpath(real, work))
            else:
                outside.add(real)
            # Each link under the work directory on the way to the file, such as K/machine.
            at = full
            while at.startswith(work + "/"):
                if os.path.islink(at):
                    links[os.path.relpath(at, work)] = paths.short(os.path.realpath(at))
                at = os.path.dirname(at)
        units[name] = [f"dir {paths.short(cwd)}", "flags " + shlex.join(paths.short(x) for x in flags)] + lines
    for p in sorted(outside):
        print(f"  {p} is read from outside sys/ and the build directories")

    rc, version, _ = run([a.cc, "--version"])
    rc, prog, _ = run([a.cc, "-print-prog-name=as"])
    rc, as_version, _ = run([prog.strip() or "as", "--version"])
    text = [f"# bsd-asm {row['id']}: the .S units of {row['kernconf']} and of its modules, "
            f"assembled by {os.path.basename(a.cc)}",
            f"# version: {first_line(version) or 'unknown'}",
            f"# assembler: {prog.strip()}, {first_line(as_version) or 'unknown'}",
            f"# source: {row['url']} {row['digest']}"]
    text += [f"# {note}" for note in a.note]
    text += [f"src {p}" for p in sorted(src)]
    text += [f"link $W/{p} {links[p]}" for p in sorted(links)]
    for p in sorted(files):
        if p in links:
            continue
        text.append(f"file $W/{p}")
        with open(os.path.join(work, p), encoding="utf-8") as f:
            text += ["| " + line.rstrip("\n") for line in f]
    for name in sorted(units):
        text.append(f"unit {name}")
        text += units[name]
    with open(a.o, "w") as f:
        f.write("\n".join(text) + "\n")
    print(f"{row['id']}: {len(units)} units, {len(src)} files of sys/, {len(files)} build files, {len(links)} links")


# check


def read_expected(path):
    exp = dict(src=[], links=[], files={}, units={})
    cur_file = cur_unit = None
    with open(path) as f:
        for line in f:
            line = line.rstrip("\n")
            if not line or line.startswith("# "):
                continue
            if line.startswith("| ") or line == "|":
                exp["files"][cur_file].append(line[2:])
                continue
            word, rest = line.split(" ", 1)
            if word == "src":
                exp["src"].append(rest)
            elif word == "link":
                exp["links"].append(rest.split(" ", 1))
            elif word == "file":
                cur_file = rest
                exp["files"][cur_file] = []
            elif word == "unit":
                cur_unit = dict(dir=None, flags=[], lines=[])
                exp["units"][rest] = cur_unit
            elif word == "dir":
                cur_unit["dir"] = rest
            elif word == "flags":
                cur_unit["flags"] = shlex.split(rest)
            else:
                cur_unit["lines"].append(line)
    return exp


def accepted():
    out = []
    path = os.path.join(HERE, "accepted.txt")
    if not os.path.exists(path):
        return out
    with open(path) as f:
        for n, line in enumerate(f, 1):
            line = line.strip()
            if line and not line.startswith("#"):
                row, unit, issue = line.split()
                out.append(dict(line=n, row=row, unit=unit, issue=issue, used=0))
    return out


def message(line):
    """A compiler's message with the file, line and column taken off, for grouping."""
    return re.sub(r"^\S+?:\d+:(\d+:)?\s*", "", line.strip())


def check_row(a, row, sysdir):
    """Return {unit: [(bucket, detail)]} for the units that differ, and the number of units."""
    exp = read_expected(expected_path(row))
    out = {}
    with tempfile.TemporaryDirectory() as work:
        expand = lambda s: s.replace("$W", work).replace("$S", sysdir)  # noqa: E731
        for p, lines in exp["files"].items():
            path = expand(p)
            os.makedirs(os.path.dirname(path), exist_ok=True)
            with open(path, "w") as f:
                f.write("".join(line + "\n" for line in lines))
        for p, to in exp["links"]:
            path = expand(p)
            os.makedirs(os.path.dirname(path), exist_ok=True)
            os.symlink(expand(to), path)
        obj = os.path.join(work, "rucc-unit.o")
        for name, unit in exp["units"].items():
            if a.units and not any(fnmatch.fnmatch(name, g) for g in a.units):
                continue
            cwd = expand(unit["dir"])
            os.makedirs(cwd, exist_ok=True)
            if os.path.exists(obj):
                os.remove(obj)
            argv = [a.rucc, f"--target={row['target']}", f"-fgnuc-version={row['gnuc']}",
                    *[expand(x) for x in unit["flags"]], "-o", obj]
            rc, _, err = run(argv, cwd=cwd)
            if rc != 0:
                said = first_line(err) or f"exit {rc}"
                out[name] = [(f"rucc: {message(said)}", said)]
                continue
            try:
                with open(obj, "rb") as f:
                    ours = read_elf(f.read())
            except (OSError, ValueError, struct.error) as e:
                out[name] = [("rucc's object", str(e))]
                continue
            found = compare(parse_description(unit["lines"]), ours)
            if found:
                out[name] = found
    return out, len(exp["units"])


def cmd_check(a):
    acc = accepted()
    bad = 0
    report = []
    groups = {}
    for row in rows():
        if a.rows and not any(fnmatch.fnmatch(row["id"], g) for g in a.rows):
            continue
        if not os.path.exists(expected_path(row)):
            print(f"{row['id']}: no reference file in expected/, skipped")
            continue
        sysdir = os.path.realpath(os.path.join(a.src, row["id"], "usr", "src", "sys"))
        missing = [p for p in read_expected(expected_path(row))["src"]
                   if not os.path.isfile(os.path.join(sysdir, p))]
        if missing:
            print(f"{row['id']}: {len(missing)} files of sys/ are not in {sysdir}, run asm.py fetch first")
            bad += 1
            continue
        differ, total = check_row(a, row, sysdir)
        new = known = 0
        for name, found in sorted(differ.items()):
            hit = [e for e in acc if fnmatch.fnmatch(row["id"], e["row"]) and fnmatch.fnmatch(name, e["unit"])]
            for e in hit:
                e["used"] += 1
            if hit:
                known += 1
                tag = hit[0]["issue"]
            else:
                new += 1
                tag = "NEW"
            groups.setdefault(found[0][0], []).append(name)
            report.append(f"{row['id']} {name} {tag}")
            report += [f"    {bucket}: {detail}" for bucket, detail in found[:8]]
            if len(found) > 8:
                report.append(f"    and {len(found) - 8} more")
        print(f"{row['id']}: {total} units, {total - len(differ)} the same, {new} new differences, {known} accepted")
        bad += new
    for e in acc:
        if not e["used"] and not a.rows and not a.units:
            print(f"accepted.txt:{e['line']}: {e['row']} {e['unit']} matches no difference")
            bad += 1
    if groups:
        print("by the first difference:")
        for bucket, names in sorted(groups.items(), key=lambda g: (-len(g[1]), g[0])):
            print(f"  {len(names):4} {bucket}")
    if a.report:
        with open(a.report, "w") as f:
            f.write("\n".join(report) + "\n")
    elif report and a.verbose:
        print("\n".join(report))
    if bad:
        print(f"bsd-asm: {bad} problems")
        return 1
    print("bsd-asm: no new differences")
    return 0


def main():
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = p.add_subparsers(dest="cmd", required=True)
    f = sub.add_parser("fetch")
    f.add_argument("row")
    f.add_argument("dir")
    f.add_argument("--archive", action="store_true", help="only download and check the source set, and print its path")
    s = sub.add_parser("scan")
    s.add_argument("row")
    s.add_argument("--cc", required=True, help="the reference compiler")
    s.add_argument("--sys", required=True, help="the sys/ directory of the source set")
    s.add_argument("--work", required=True, help="an empty directory for the kernel and module builds")
    s.add_argument("--note", action="append", default=[])
    s.add_argument("-o", required=True)
    c = sub.add_parser("check")
    c.add_argument("--rucc", required=True)
    c.add_argument("--src", required=True, help="the directory asm.py fetch unpacked the sources in")
    c.add_argument("--rows", action="append", default=[], help="only the rows that match this glob")
    c.add_argument("--units", action="append", default=[], help="only the units that match this glob")
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
