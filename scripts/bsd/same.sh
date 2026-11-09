#!/usr/bin/env bash
# Compare the files that a reference job made with the expected files in the repository.
#
#   same.sh MADE EXPECTED
#
# For each file in MADE, the file of the same name in EXPECTED must have the same lines.
# The comment lines at the top of a file name the host and the package, so they are not compared.
set -euo pipefail
made=$1 expected=$2
body() { awk 'done || !/^# / { done = 1; print }' "$1"; }
bad=0
for f in "$made"/*; do
	n=$(basename "$f")
	if [ ! -f "$expected/$n" ]; then
		echo "$n: not in $expected"
		bad=1
	elif ! diff -u <(body "$expected/$n") <(body "$f") > "$f.diff"; then
		echo "$n: different, $(grep -c '^[-+][^-+]' "$f.diff") lines"
		head -40 "$f.diff"
		bad=1
	else
		echo "$n: same"
		rm "$f.diff"
	fi
done
exit $bad
