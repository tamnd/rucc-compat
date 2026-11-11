"""Make the layout cases of rucc-compat/plan9: one case per header of /sys/include.

usage: python3 -I scripts/plan9_layout.py SYSINCLUDE ARCHINCLUDE RUCC6C OUTDIR

Each case includes the header and what it needs, and prints the size of each struct and union
that the header defines, and the offset of each named member. Lines that rucc refuses are dropped.
"""
import os
import re
import subprocess
import sys

sysinc, archinc, cc, outdir = sys.argv[1:5]

SKIP = {"stdio.h", "ape", "pool.h", "tos.h", "trace.h", "dtracy.h", "rdbg.h"}
PREFIXES = [
    [],
    ["bio.h"],
    ["draw.h"],
    ["thread.h"],
    ["draw.h", "mouse.h"],
    ["draw.h", "thread.h", "mouse.h", "keyboard.h"],
    ["fcall.h"],
    ["fcall.h", "thread.h"],
    ["mp.h"],
    ["mp.h", "libsec.h"],
    ["draw.h", "memdraw.h"],
    ["bio.h", "mach.h"],
    ["thread.h", "sunrpc.h"],
    ["ip.h"],
    ["auth.h"],
    ["draw.h", "event.h"],
    ["draw.h", "thread.h", "mouse.h", "keyboard.h", "control.h"],
]
KEY = {"struct", "union", "enum", "typedef", "extern", "static", "const", "volatile", "void",
       "char", "short", "int", "long", "float", "double", "unsigned", "signed", "register"}


def strip(text):
    text = re.sub(r"/\*.*?\*/", " ", text, flags=re.S)
    text = re.sub(r"//[^\n]*", " ", text)
    return "\n".join("" if l.lstrip().startswith("#") else l for l in text.split("\n"))


def close(text, i):
    """The index after the brace that closes the brace at text[i]."""
    depth = 0
    for j in range(i, len(text)):
        if text[j] == "{":
            depth += 1
        elif text[j] == "}":
            depth -= 1
            if depth == 0:
                return j + 1
    return len(text)


def members(body):
    """The named members at depth 0 of a record body, and those of its anonymous records."""
    out = []
    depth = paren = 0
    cur = []
    inner = []
    start = 0
    for i, ch in enumerate(body):
        if ch == "{":
            depth += 1
            if depth == 1:
                start = i + 1
        elif ch == "}":
            depth -= 1
            if depth == 0:
                inner.append(body[start:i])
                cur.append(f" @{len(inner) - 1} ")
                continue
        if depth > 0:
            continue
        if ch == "(":
            paren += 1
        elif ch == ")":
            paren -= 1
        if ch == ";" and paren == 0:
            out.extend(declarators(" ".join("".join(cur).split()), inner))
            cur = []
        else:
            cur.append(ch)
    return out


def declarators(st, inner):
    if not st:
        return []
    st = re.sub(r":\s*\w+", "", st)
    m = re.search(r"\(\s*\*\s*(\w+)\s*\)", st)
    if m:
        return [m.group(1)]
    m = re.search(r"@(\d+)", st)
    if m:
        rest = st[m.end():].strip()
        if not rest:
            return members(inner[int(m.group(1))])
        parts = rest.split(",")
    else:
        parts = st.split(",")
        words = re.findall(r"\w+", parts[0])
        if len(words) < 2 and "*" not in parts[0]:
            return []
    names = []
    for p in parts:
        m = re.search(r"(\w+)\s*(\[[^\]]*\]\s*)*$", p.strip())
        if m and m.group(1) not in KEY:
            names.append(m.group(1))
    return names


def records(text):
    out = []
    for m in re.finditer(r"\b(struct|union)\s+(\w+)\s*\{", text):
        start = m.end() - 1
        out.append((f"{m.group(1)} {m.group(2)}", members(text[start + 1:close(text, start) - 1])))
    return out


def compile_case(path):
    env = dict(os.environ, INCLUDE=f"{archinc} {sysinc}")
    r = subprocess.run([cc, "-w", os.path.basename(path)], cwd=os.path.dirname(path), env=env,
                       capture_output=True, text=True)
    obj = os.path.splitext(path)[0] + ".6"
    if os.path.exists(obj):
        os.remove(obj)
    return r.returncode, r.stderr


def source(prefix, header, entries):
    lines = ["#include <u.h>", "#include <libc.h>"]
    for h in prefix + [header]:
        if h not in ("u.h", "libc.h"):
            lines.append(f"#include <{h}>")
    lines += ["", "void", "main(void)", "{"]
    for tag, m in entries:
        if m is None:
            lines.append(f'\tprint("{tag} %d\\n", sizeof({tag}));')
        else:
            lines.append(f'\tprint("{tag}.{m} %lud\\n", offsetof({tag}, {m}));')
    lines += ["\texits(nil);", "}", ""]
    return "\n".join(lines)


os.makedirs(outdir, exist_ok=True)
total = 0
for header in sorted(os.listdir(sysinc)) + ["u.h", "ureg.h"]:
    if header in SKIP or not header.endswith(".h"):
        continue
    where = archinc if header in ("u.h", "ureg.h") else sysinc
    recs = records(strip(open(os.path.join(where, header)).read()))
    if not recs:
        continue
    base = header[:-2].lower()
    path = os.path.join(outdir, base + ".c")
    prefix = None
    for p in PREFIXES:
        if header in p:
            continue
        open(path, "w").write(source(p, header, []))
        if compile_case(path)[0] == 0:
            prefix = p
            break
    if prefix is None:
        print(f"{header}: no prefix", file=sys.stderr)
        os.remove(path)
        continue
    entries = []
    for tag, ms in recs:
        entries.append((tag, None))
        entries.extend((tag, m) for m in ms)
    for _ in range(20):
        text = source(prefix, header, entries)
        open(path, "w").write(text)
        rc, err = compile_case(path)
        if rc == 0:
            break
        first = text.split("\n").index("{") + 2
        bad = {int(m.group(1)) - first for m in re.finditer(r":(\d+)(?::\d+)?: error", err)}
        if not bad:
            print(f"{header}: cannot read errors: {err[:300]}", file=sys.stderr)
            entries = []
            break
        dropped = [entries[i] for i in sorted(bad) if 0 <= i < len(entries)]
        print(f"{header}: drop {dropped}", file=sys.stderr)
        entries = [e for i, e in enumerate(entries) if i not in bad]
    if not entries:
        os.remove(path)
        continue
    total += len(entries)
    print(f"{header}: {len(entries)} with {prefix}")
print(f"total {total}")
