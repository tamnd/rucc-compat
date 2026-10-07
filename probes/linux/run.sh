#!/bin/sh
# The Linux probes: what rucc does on an x86-64 Linux machine with glibc, one line per probe.
#
# usage: probes/linux/run.sh native|cross RUCC [EXPECTED]
#
# Each probe runs one command in a scratch directory and prints its name, the exit status and what
# the command wrote to standard output, on one line. Standard error goes to log/<name> in the scratch
# directory, because the messages change from one release to the next and the result does not. With
# EXPECTED, the lines are compared with that file and any difference fails the run. Lines that start
# with # are not compared.
#
# The machine needs gcc, binutils, lld and the glibc development files. The expected files say which
# distribution they were made on.

set -u

kind=${1:?usage: run.sh native|cross RUCC [EXPECTED]}
case $kind in
native | cross) ;;
*) echo "run.sh: the first argument is native or cross, not $kind" >&2; exit 2 ;;
esac
rucc=${2:?usage: run.sh native|cross RUCC [EXPECTED]}
expected=${3:-}
here=$(CDPATH='' cd -- "$(dirname -- "$0")" && pwd)
case $rucc in
/*) ;;
*) rucc=$(pwd)/$rucc ;;
esac
case $expected in
/* | '') ;;
*) expected=$(pwd)/$expected ;;
esac

work=$(mktemp -d "${TMPDIR:-/tmp}/rucc-probes.XXXXXX")
cp "$here"/src/* "$work"/
mkdir "$work/log"
cd "$work" || exit 1
R=$rucc

t() {
	out=$(sh -c "$2" 2>"log/$1")
	rc=$?
	printf '%s rc=%s %s\n' "$1" "$rc" "$(printf '%s' "$out" | tr '\n' '|' | cut -c1-200)"
}

# Whether a path that a -print option gave is a full path, which is what a build system needs.
full='full() { case $1 in /*) echo full ;; *) echo "bare $1" ;; esac; }; full'

. "$here/$kind.sh"

result=$work/result.txt
run | tee "$result"
status=0
if [ -n "$expected" ]; then
	grep -v '^#' "$expected" >"$work/want.txt"
	grep -v '^#' "$result" >"$work/got.txt"
	if cmp -s "$work/want.txt" "$work/got.txt"; then
		echo "probes: the same as $expected"
	else
		echo "probes: different from $expected"
		diff "$work/want.txt" "$work/got.txt" | grep '^[<>]'
		status=1
	fi
fi
echo "probes: the logs are in $work/log"
exit $status
