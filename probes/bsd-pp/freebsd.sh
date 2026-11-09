#!/bin/sh
# Make the FreeBSD expected files of bsd-pp. Run it as root in the FreeBSD 15.1 VM of scripts/bsd/freebsd-vm.sh.
#
#   freebsd.sh SETS OUTDIR
#
# SETS is the directory that abi.py fetch unpacked the FreeBSD rows in.
# It installs the cross GCC packages that the rows of bsd-abi name, from the default package repository of the release.
# Then it runs pp.py dump for each FreeBSD row.
# Each file records the package version and its SHA-256.
set -eu
sets=$1
out=$2
here=$(cd "$(dirname "$0")" && pwd)
rows=$here/../bsd-abi/rows.txt
mkdir -p "$out"
pkgs=$(awk '$2 == "freebsd" { print $6 }' "$rows" | sort -u)
pkg -N > /dev/null 2>&1 || env ASSUME_ALWAYS_YES=yes pkg bootstrap > /dev/null
env ASSUME_ALWAYS_YES=yes pkg update -q
# shellcheck disable=SC2086
env ASSUME_ALWAYS_YES=yes pkg install -q -y python3 $pkgs
awk '$2 == "freebsd" { print $1, $3, $6 }' "$rows" | while read -r id arch ref; do
	ver=${ref##*-gcc}
	cc=$(ls /usr/local/bin/"$arch"-unknown-freebsd*-gcc"$ver")
	v=$(pkg query %v "$ref")
	f=$(ls /var/cache/pkg/"$ref-$v"*.pkg 2> /dev/null | head -1)
	sum=$( [ -n "$f" ] && sha256 -q "$f" || echo unknown)
	python3 "$here/pp.py" dump "$id" --cc "$cc" --sysroot "$sets/$id" -o "$out/$id.txt" \
		--note "package: $ref $v, sha256 $sum, from $(pkg -vv | awk '/url *:/ { print $3; exit }' | tr -d '",')" \
		--note "host: $(uname -sr)"
	echo "$id: $cc"
done
