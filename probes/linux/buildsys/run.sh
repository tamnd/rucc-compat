#!/bin/sh
# The build system fixtures: what each build system finds out about rucc, compared with what it finds
# out about gcc on the same machine.
#
# usage: probes/linux/buildsys/run.sh RUCC [EXPECTED]
#
# Each fixture configures one project twice, once with CC=gcc and once with CC=RUCC, and writes a
# summary of the configuration for each one. The run prints the lines of the two summaries that are
# different, and then builds and runs the project with each compiler. With EXPECTED, the output is
# compared with that file and any difference fails the run. Lines that start with # are not compared.
#
# GCC=<path> selects the gcc (default: gcc on PATH). FIXTURES selects the fixtures (default: all of
# them). FULL=1 also builds OpenSSL and Python, which takes a long time. The source archives go in
# BUILDSYS_CACHE (default: ~/.cache/rucc-buildsys), so the first run needs the network.
#
# The machine needs gcc, make, autoconf, automake, libtool, cmake, ninja, meson, perl, python3, curl
# and xz. The expected files say which distribution and which GCC they were made with.

set -u

rucc=${1:?usage: run.sh RUCC [EXPECTED]}
expected=${2:-}
here=$(CDPATH='' cd -- "$(dirname -- "$0")" && pwd)
case $rucc in
/*) ;;
*) rucc=$(pwd)/$rucc ;;
esac
case $expected in
/* | '') ;;
*) expected=$(pwd)/$expected ;;
esac
gcc=$(command -v "${GCC:-gcc}") || { echo "run.sh: no gcc" >&2; exit 2; }
fixtures=${FIXTURES:-autotools cmake meson zlib openssl python}
full=${FULL:-0}
cache=${BUILDSYS_CACHE:-${XDG_CACHE_HOME:-$HOME/.cache}/rucc-buildsys}
jobs=$(nproc 2>/dev/null || echo 2)

work=$(mktemp -d "${TMPDIR:-/tmp}/rucc-buildsys.XXXXXX")
mkdir "$work/log"
cd "$work" || exit 1

# fetch FILE URL SHA256: put the archive in the cache once and check it each time.
fetch() {
	mkdir -p "$cache"
	if [ ! -f "$cache/$1" ]; then
		curl -fsSL -o "$cache/$1.part" "$2" && mv "$cache/$1.part" "$cache/$1" || return 1
	fi
	echo "$3  $cache/$1" | sha256sum -c --quiet - >/dev/null 2>&1
}

# A copy of a fixture directory with the shared sources in it.
fixture() {
	mkdir "$1-src"
	cp -R "$here/$1/." "$here/src/." "$1-src/"
}

# The output of a built program: ok when it prints what the sources say it prints.
ran() {
	out=$("$@" 2>&1)
	if [ "$out" = "1 5.0" ]; then echo ok; else echo "wrong:$(printf '%s' "$out" | head -1 | cut -c1-60)"; fi
}

autotools_prepare() {
	fixture autotools
	(cd autotools-src && autoreconf -fi) >log/autotools-prepare 2>&1
}
autotools_configure() {
	(cd "$1" && ../autotools-src/configure CC="$2") >&2 || return 1
	sed -n '/^## Cache variables/,/^## Output variables/p' "$1/config.log" | grep -E '^[a-z]+_cv_' | grep -vE '^ac_cv_env_|^ac_cv_prog_(ac_ct_)?CC='
	"$1/libtool" --config | grep -E '^(GCC|with_gcc|LD|wl|pic_flag|link_static_flag|no_builtin_flag|export_dynamic_flag_spec|whole_archive_flag_spec|archive_cmds|hardcode_libdir_flag_spec|thread_safe_flag_spec|build_libtool_libs|build_old_libs|sys_lib_search_path_spec|sys_lib_dlsearch_path_spec|predep_objects|postdep_objects|predeps|postdeps|compiler_lib_search_path)=' | awk -F= '!seen[$1]++'
}
autotools_build() {
	(cd "$1" && make -s) >&2 || return 1
	ran "$1/main"
}

cmake_prepare() {
	fixture cmake
}
cmake_configure() {
	cmake -S cmake-src -B "$1" -G Ninja -DCMAKE_C_COMPILER="$2" >&2 || return 1
	cat "$1/summary.txt"
}
cmake_build() {
	cmake --build "$1" >&2 || return 1
	ran "$1/main"
}

meson_prepare() {
	fixture meson
}
meson_configure() {
	CC=$2 meson setup "$1" meson-src >&2 || return 1
	cat "$1/summary.txt"
}
meson_build() {
	meson compile -C "$1" >&2 || return 1
	ran "$1/main"
}

zlib_prepare() {
	fetch zlib-1.3.1.tar.gz https://zlib.net/fossils/zlib-1.3.1.tar.gz 9a93b2b7dfdac77ceba5a558a580e74667dd6fede4585b91eefb60f03b72df23
}
zlib_configure() {
	tar -xzf "$cache/zlib-1.3.1.tar.gz" -C "$1" || return 1
	# What configure prints is the summary: one line for each check, and the shared library line.
	(cd "$1/zlib-1.3.1" && CC=$2 ./configure) || return 1
	grep -E '^(CFLAGS|SFLAGS|LDFLAGS|TEST_LIBS|LDSHARED|LDSHAREDLIBC|CPP|STATICLIB|SHAREDLIB|SHAREDLIBV|SHAREDLIBM|LIBS|AR|ARFLAGS|RANLIB|EXE|ALL|TEST)=' "$1/zlib-1.3.1/Makefile"
	grep 'by \./configure' "$1/zlib-1.3.1/zconf.h"
}
zlib_build() {
	(cd "$1/zlib-1.3.1" && make -s test) >"$1/test.txt" 2>&1
	kinds=
	grep -q 'zlib test OK' "$1/test.txt" && kinds=static
	grep -q 'zlib shared test OK' "$1/test.txt" && kinds=${kinds:+$kinds,}shared
	echo "${kinds:-fail}"
}

openssl_prepare() {
	fetch openssl-3.5.4.tar.gz https://github.com/openssl/openssl/releases/download/openssl-3.5.4/openssl-3.5.4.tar.gz 967311f84955316969bdb1d8d4b983718ef42338639c621ec4c34fddef355e99 || return 1
	tar -xzf "$cache/openssl-3.5.4.tar.gz"
}
openssl_configure() {
	(cd "$1" && CC=$2 perl ../openssl-3.5.4/Configure) >&2 || return 1
	(cd "$1" && perl configdata.pm -o -m) | grep -vE '^ *(CC|SRCDIR|BLDDIR) *=' | grep -vE '^Command line|^ *perl'
}
openssl_build() {
	[ "$full" = 1 ] || { echo skipped; return 0; }
	(cd "$1" && make -s -j"$jobs") >&2 || return 1
	"$1/util/wrap.pl" "$1/apps/openssl" version | head -1 | cut -d' ' -f1,2
}

python_prepare() {
	fetch Python-3.14.0.tar.xz https://www.python.org/ftp/python/3.14.0/Python-3.14.0.tar.xz 2299dae542d395ce3883aca00d3c910307cd68e0b2f7336098c8e7b7eee9f3e9 || return 1
	tar -xJf "$cache/Python-3.14.0.tar.xz"
}
python_configure() {
	(cd "$1" && CC=$2 ../Python-3.14.0/configure --without-ensurepip) >&2 || return 1
	grep -E '^#define ' "$1/pyconfig.h" | sort
	grep -E '^(CC|CFLAGS|CFLAGS_NODIST|CONFIGURE_CFLAGS|CONFIGURE_CFLAGS_NODIST|CONFIGURE_LDFLAGS|OPT|CCSHARED|LDSHARED|BLDSHARED|LINKFORSHARED|LDLIBRARY|LIBS|SYSLIBS|MODLIBS|MULTIARCH|PLATFORM_TRIPLET|SOABI|EXT_SUFFIX|LIBM|LIBC|LIBFFI_INCLUDEDIR|PY_ENABLE_SHARED|THREADHEADERS|LTOFLAGS)[[:space:]]*=' "$1/Makefile" | grep -vE '^CC[[:space:]]*='
}
python_build() {
	[ "$full" = 1 ] || { echo skipped; return 0; }
	(cd "$1" && make -s -j"$jobs") >&2 || return 1
	"$1/python" -c 'import sys, ssl, zlib, ctypes; print(*sys.version_info[:2])'
}

run() {
	echo "# $($rucc --version | head -1)"
	echo "# $($gcc --version | head -1)"
	echo "# $(. /etc/os-release && echo "$PRETTY_NAME"), $(uname -m)"
	for f in $fixtures; do
		if ! "${f}_prepare" >>"log/$f-prepare" 2>&1; then
			echo "$f prepare failed"
			continue
		fi
		for cc in gcc rucc; do
			eval "path=\$$cc"
			mkdir "$f-$cc"
			if "${f}_configure" "$work/$f-$cc" "$path" >"$f-$cc.raw" 2>"log/$f-$cc-configure"; then
				sed -e "s#$path\([^-_[:alnum:]]\)#CC\1#g" -e "s#$path\$#CC#" -e "s#$work#WORK#g" "$f-$cc.raw" >"$f-$cc.txt"
				eval "conf_$cc=ok"
				if b=$("${f}_build" "$work/$f-$cc" 2>"log/$f-$cc-build"); then eval "build_$cc=\$b"; else eval "build_$cc=fail"; fi
			else
				eval "conf_$cc=fail build_$cc=none"
			fi
		done
		echo "$f configure gcc=$conf_gcc rucc=$conf_rucc"
		if [ "$conf_gcc" = ok ] && [ "$conf_rucc" = ok ]; then
			diff "$f-gcc.txt" "$f-rucc.txt" | grep '^[<>]' | cut -c1-300 | sed "s/^/$f /"
		fi
		echo "$f build gcc=$build_gcc rucc=$build_rucc"
	done
}

result=$work/result.txt
run | tee "$result"
status=0
if [ -n "$expected" ]; then
	grep -v '^#' "$expected" >"$work/want.txt"
	grep -v '^#' "$result" >"$work/got.txt"
	if cmp -s "$work/want.txt" "$work/got.txt"; then
		echo "buildsys: the same as $expected"
	else
		echo "buildsys: different from $expected"
		diff "$work/want.txt" "$work/got.txt" | grep '^[<>]'
		status=1
	fi
fi
echo "buildsys: the logs are in $work/log"
exit $status
