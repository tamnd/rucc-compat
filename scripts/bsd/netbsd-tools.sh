#!/usr/bin/env bash
# Build the NetBSD cross tools of one branch and one machine, with build.sh tools.
#
#   netbsd-tools.sh BRANCH ARCH ROOT
#
# BRANCH is current, 11 or 10. ARCH is x86_64, aarch64 or riscv64. The source goes to ROOT/src and the tools to
# ROOT/tools. The commits are the pins of tamnd/rucc-bsd (pins.toml), so the GCC is the GCC of that persona.
# The script prints the path of the gcc driver on its last line.
set -euo pipefail

branch=$1 arch=$2 root=$3
case "$branch" in
	current) commit=36eddebcc36cb0775aa2962005b9c05419a6ff01 ;;
	11) commit=4198f5370c187384b1de46b9b0fcd04462a420e0 ;;
	10) commit=a6a6e416dbc433befb1723794fbb058811e3ab64 ;;
	*) echo "netbsd-tools.sh: no pin for branch $branch" >&2; exit 2 ;;
esac
case "$arch" in
	x86_64) machine=(-m amd64) ;;
	aarch64) machine=(-m evbarm -a aarch64) ;;
	riscv64) machine=(-m riscv -a riscv64) ;;
	*) echo "netbsd-tools.sh: no machine for $arch" >&2; exit 2 ;;
esac

gcc="$root/tools/bin/$arch--netbsd-gcc"
if [ ! -x "$gcc" ]; then
	mkdir -p "$root/src" "$root/obj"
	if [ ! -f "$root/src/build.sh" ]; then
		git -C "$root/src" init -q
		git -C "$root/src" fetch -q --depth 1 https://github.com/NetBSD/src "$commit"
		git -C "$root/src" checkout -q FETCH_HEAD
	fi
	(cd "$root/src" && ./build.sh -U -N1 "${machine[@]}" -j "$(nproc)" -O "$root/obj" -T "$root/tools" tools) >&2
fi
echo "$commit" > "$root/tools/commit.txt"
echo "$gcc"
