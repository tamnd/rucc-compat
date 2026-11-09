#!/bin/sh
# Make the FreeBSD expected files of bsd-probes. Run it as root in the FreeBSD 15.1 VM of scripts/bsd/freebsd-vm.sh.
#
#   freebsd.sh OUTDIR
#
# It installs the cross GCC packages that the rows of bsd-predef name, from the default package repository of the release.
# Then it runs probes.py dump for each FreeBSD row.
# Each file records the package version and its SHA-256.
set -eu
out=$1
here=$(cd "$(dirname "$0")" && pwd)
rows=$here/../bsd-predef/rows.txt
mkdir -p "$out"
pkgs=$(awk '$2 == "freebsd" { print $7 }' "$rows" | sort -u)
pkg -N > /dev/null 2>&1 || env ASSUME_ALWAYS_YES=yes pkg bootstrap > /dev/null
env ASSUME_ALWAYS_YES=yes pkg update -q
# shellcheck disable=SC2086
env ASSUME_ALWAYS_YES=yes pkg install -q -y python3 $pkgs
awk '$2 == "freebsd" { print $1, $4, $7 }' "$rows" | while read -r id arch ref; do
	ver=${ref##*-gcc}
	cc=$(ls /usr/local/bin/"$arch"-unknown-freebsd*-gcc"$ver")
	v=$(pkg query %v "$ref")
	f=$(ls /var/cache/pkg/"$ref-$v"*.pkg 2> /dev/null | head -1)
	sum=$( [ -n "$f" ] && sha256 -q "$f" || echo unknown)
	python3 "$here/probes.py" dump "$id" --cc "$cc" -o "$out/$id.txt" \
		--note "package: $ref $v, sha256 $sum, from $(pkg -vv | awk '/url *:/ { print $3; exit }' | tr -d '",')" \
		--note "host: $(uname -sr)"
	echo "$id: $cc"
done
