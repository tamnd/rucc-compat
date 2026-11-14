"""Make and check the asm corpus of rucc-compat/plan9.

usage:
    python3 -I scripts/plan9_asm.py make COLLECTED ROOT > plan9/asm/manifest
    python3 -I scripts/plan9_asm.py check MANIFEST ROOT RUCC WORK

The manifest has one line for each run of an assembler on a file of the tree at the pin:

    ASM PATH SOURCE STATUS OBJECT MESSAGES

ASM is 6a or 7a, and PATH is the name of the .s file in the tree. SOURCE is the SHA-256 of the
file. STATUS is ok or error. OBJECT is the SHA-256 of the object, and MESSAGES is the SHA-256 of
the messages, or - when there are none.

make reads the output of guest/r9-asm of rucc-plan9 from COLLECTED, with the list of the runs in
COLLECTED/list. That script ran the assemblers of the guest, and the guest is the G build of the
pin. ROOT is the tree of the pin on the host, for the hash of each source.

check runs RUCC as the assembler on each file of ROOT, in the directory WORK, and compares the
status, the object and the messages with the manifest. It prints each difference, and the exit
status is 1 when there is a difference.
"""
import hashlib
import os
import subprocess
import sys

TARGET = {"6a": "x86_64-plan9", "7a": "aarch64-plan9"}


def sha(data):
    return hashlib.sha256(data).hexdigest() if data else "-"


def read(path):
    try:
        with open(path, "rb") as f:
            return f.read()
    except FileNotFoundError:
        return None


def make(collected, root):
    with open(os.path.join(collected, "list")) as f:
        runs = [line.split() for line in f if line.strip()]
    for asm, path in runs:
        out = os.path.join(collected, asm + path)
        status = read(out + ".status")
        if status is None:
            sys.exit(f"plan9_asm: no status for {asm} {path}")
        # rc gives an empty status for success, and a shell of the host gives 0.
        ok = status.strip() in (b"", b"0")
        obj = read(out + ".obj") if ok else None
        messages = read(out + ".err") or b""
        source = read(root + path)
        if source is None:
            sys.exit(f"plan9_asm: {root}{path} is not in the tree")
        print(asm, path, sha(source), "ok" if ok else "error", sha(obj), sha(messages))


def check(manifest, root, rucc, work):
    # rucc runs in WORK, so the names that it gets must be absolute.
    root = os.path.abspath(root)
    work = os.path.abspath(work)
    if os.sep in rucc:
        rucc = os.path.abspath(rucc)
    os.makedirs(work, exist_ok=True)
    out = os.path.join(work, "out")
    bad = 0
    n = 0
    with open(manifest) as f:
        lines = [line.split() for line in f if line.strip()]
    for asm, path, source, status, obj, messages in lines:
        n += 1
        if sha(read(root + path)) != source:
            print(f"{asm} {path}: the source is not the source of the pin")
            bad += 1
            continue
        if os.path.exists(out):
            os.remove(out)
        args = [
            rucc,
            "--driver=plan9-as",
            "--target=" + TARGET[asm],
            "--sysroot=" + root,
            "--cwd=" + os.path.dirname(path),
            "-o",
            out,
            os.path.basename(path),
        ]
        run = subprocess.run(args, cwd=work, capture_output=True, check=False)
        got = [
            "ok" if run.returncode == 0 else "error",
            sha(read(out)) if run.returncode == 0 else "-",
            sha(run.stdout + run.stderr),
        ]
        want = [status, obj, messages]
        names = ["status", "object", "messages"]
        diff = [names[i] for i in range(3) if got[i] != want[i]]
        if diff:
            print(f"{asm} {path}: the {' and the '.join(diff)} are not the same")
            bad += 1
    print(f"{n} runs, {n - bad} the same, {bad} different")
    return 1 if bad else 0


def main():
    if len(sys.argv) == 4 and sys.argv[1] == "make":
        make(*sys.argv[2:4])
        return 0
    if len(sys.argv) == 6 and sys.argv[1] == "check":
        return check(*sys.argv[2:6])
    sys.exit(__doc__)


if __name__ == "__main__":
    sys.exit(main())
