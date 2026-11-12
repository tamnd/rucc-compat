#!/bin/sh
# Make the FreeBSD expected files of bsd-asm. Run it as root in the FreeBSD 15.1 VM of scripts/bsd/freebsd-vm.sh.
#
#   freebsd.sh SRC OUTDIR
#
# SRC holds the source set of each FreeBSD row, unpacked as SRC/ROW/usr/src/sys.
# It installs the cross GCC packages that rows.txt names, from the default package repository of the release.
# Then it runs asm.py scan for each FreeBSD row, which configures the kernel and builds its .S units and those of the modules.
# Each file records the package version and its SHA-256.
set -eu
src=$1
out=$2
here=$(cd "$(dirname "$0")" && pwd)
mkdir -p "$out"
pkgs=$(awk '$2 == "freebsd" { print $6 }' "$here/rows.txt" | sort -u)
pkg -N > /dev/null 2>&1 || env ASSUME_ALWAYS_YES=yes pkg bootstrap > /dev/null
env ASSUME_ALWAYS_YES=yes pkg update -q
# shellcheck disable=SC2086
env ASSUME_ALWAYS_YES=yes pkg install -q -y python3 $pkgs
awk '$2 == "freebsd" { print $1, $3, $6 }' "$here/rows.txt" | while read -r id arch ref; do
	ver=${ref##*-gcc}
	cc=$(ls /usr/local/bin/"$arch"-unknown-freebsd*-gcc"$ver")
	v=$(pkg query %v "$ref")
	f=$(ls /var/cache/pkg/"$ref-$v"*.pkg 2> /dev/null | head -1)
	sum=$( [ -n "$f" ] && sha256 -q "$f" || echo unknown)
	rm -rf "/root/asm-work/$id"
	python3 "$here/asm.py" scan "$id" --cc "$cc" --sys "$src/$id/usr/src/sys" --work "/root/asm-work/$id" -o "$out/$id.txt" \
		--note "package: $ref $v, sha256 $sum, from $(pkg -vv | awk '/url *:/ { print $3; exit }' | tr -d '",')" \
		--note "host: $(uname -sr)"
done
