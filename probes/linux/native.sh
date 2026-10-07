# The native probes for x86_64-linux-gnu, read by run.sh. Each line is one probe: a name and a
# command for sh, run in the scratch directory with $R as the compiler.

run() {
	echo "# $($R --version | head -1)"
	echo "# $(uname -m), $(ldd --version 2>&1 | head -1)"

	# Program kinds.
	t hello-O0 "$R hello.c -o h0 && ./h0"
	t hello-O2 "$R -O2 hello.c -o h2 && ./h2"
	t elf-type "readelf -h h0 | awk '/Type:/ {print \$2}'"
	t interp "readelf -lW h0 | grep -o 'interpreter: [^]]*'"
	t relro "readelf -lW h0 | grep -c GNU_RELRO"
	t stack "readelf -lW h0 | awk '/GNU_STACK/ {print \$7}'"
	t static "$R -static hello.c -o hs && ./hs && readelf -h hs | awk '/Type:/ {print \$2}'"
	t static-pie "$R -static-pie hello.c -o hsp && ./hsp && readelf -h hsp | awk '/Type:/ {print \$2}'"
	t no-pie "$R -no-pie hello.c -o hnp && ./hnp && readelf -h hnp | awk '/Type:/ {print \$2}'"
	t shared-O0 "$R -fPIC -shared lib.c -o libfoo.so && $R use.c -L. -lfoo -Wl,-rpath,. -o use0 && ./use0"
	t shared-O2 "$R -fPIC -shared -O2 lib.c -o libfoo.so && $R -O2 use.c -L. -lfoo -Wl,-rpath,. -o use2 && ./use2"
	t shared-exports "nm -D --defined-only libfoo.so | awk '{print \$3}' | sort | tr '\n' ' '"
	t gcc-uses-rucc-so "gcc -O2 use.c -L. -lfoo -Wl,-rpath,. -o useg && ./useg"
	t threads-O0 "$R thr.c -o thr0 -pthread && ./thr0"
	t threads-O2 "$R -O2 thr.c -o thr2 -pthread && ./thr2"
	t ifunc "$R -O2 ifunc.c -o if && ./if"
	t symver "$R -fPIC -shared ver.c -Wl,--version-script=ver.map -o libver.so && readelf --dyn-syms -W libver.so | grep -oE ' f@@?VERS_[0-9]' | sort | tr '\n' ' '"

	# Hardening.
	t fortify3 "$R -O2 -D_FORTIFY_SOURCE=3 fort.c -o fo && ./fo x >/dev/null && nm -u fo | grep -c _chk"
	t ssp-strong "$R -O2 -fstack-protector-strong hello.c -o hp && ./hp >/dev/null && nm -u hp | grep -c __stack_chk_fail"
	t cf-protection "$R -O2 -fcf-protection=full hello.c -o hcf && ./hcf >/dev/null && readelf -n hcf | grep -oE 'IBT|SHSTK' | sort -u | tr '\n' ' '"
	t stack-clash "$R -O2 -fstack-clash-protection hello.c -o hcl && ./hcl"
	t fno-plt "$R -fno-plt -O2 hello.c -o np && ./np"
	t relr "$R -Wl,-z,pack-relative-relocs hello.c -o rr && ./rr >/dev/null && readelf -d rr | grep -c RELR"
	t fhardened "$R -fhardened -O2 hello.c -o fh && ./fh"
	t leaf-fp "$R -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer -O2 hello.c -o lf && ./lf"
	t ssp-macros "echo | $R -fstack-protector-strong -fcf-protection -dM -E - | grep -oE '__SSP[A-Z_]*__|__CET__' | sort | tr '\n' ' '"

	# The flag lines of the distributions, without the parts that are only warnings.
	t debian-flags "$R -g -O2 -Werror=implicit-function-declaration -ffile-prefix-map=/x=. -fstack-protector-strong -fstack-clash-protection -Wformat -Werror=format-security -fcf-protection -D_FORTIFY_SOURCE=3 -Wl,-z,relro -Wl,-z,now hello.c -o hd && ./hd"
	t ubuntu-flags "$R -g -O2 -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer -ffile-prefix-map=/x=. -flto=auto -ffat-lto-objects -fstack-protector-strong -fstack-clash-protection -Wformat -Werror=format-security -fcf-protection -fdebug-prefix-map=/x=/usr/src/x -Wdate-time -D_FORTIFY_SOURCE=3 -Wl,-Bsymbolic-functions -Wl,-z,relro -Wl,-z,now hello.c -o hu && ./hu"
	t fedora-flags "$R -O2 -flto=auto -ffat-lto-objects -fexceptions -g -grecord-gcc-switches -pipe -Wall -Werror=format-security -U_FORTIFY_SOURCE -Wp,-U_FORTIFY_SOURCE -Wp,-D_FORTIFY_SOURCE=3 -Wp,-D_GLIBCXX_ASSERTIONS -fstack-protector-strong -fasynchronous-unwind-tables -fstack-clash-protection -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer -mtune=generic -fcf-protection -Wl,-z,relro -Wl,--as-needed -Wl,-z,pack-relative-relocs -Wl,-z,now hello.c -o fe && ./fe"
	t arch-flags "$R -march=x86-64 -mtune=generic -O2 -pipe -fno-plt -fexceptions -Wp,-D_FORTIFY_SOURCE=3 -Wformat -Werror=format-security -fstack-clash-protection -fcf-protection -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer -Wl,-O1 -Wl,--sort-common -Wl,--as-needed -Wl,-z,relro -Wl,-z,now -Wl,-z,pack-relative-relocs hello.c -o ar && ./ar"

	# TLS.
	t bigtls-dlopen "$R -fPIC -shared bigtls.c -o libbig.so && $R dl.c -o dl -ldl && ./dl"
	t tls-relocs "$R -fPIC -c bigtls.c -o bt.o && readelf -rW bt.o | grep -oE 'R_X86_64_[A-Z0-9_]+' | sort -u | tr '\n' ' '"
	t ftls-model "$R -fPIC -ftls-model=initial-exec -c bigtls.c -o bti.o"
	t tls-gnu2 "$R -mtls-dialect=gnu2 -fPIC -shared lib.c -o l2.so"

	# Debug information and tools.
	t dwarf-version "$R -g dbg.c -o dg && ./dg && readelf --debug-dump=info dg | grep -m1 -oE 'Version: +[0-9]+' | tr -s ' '"
	t dwarf-sections "readelf -SW dg | grep -oE '\\.debug_[a-z_]+|\\.eh_frame[a-z_]*' | sort -u | tr '\n' ' '"
	t gsplit-dwarf "$R -g -gsplit-dwarf -c dbg.c -o dbs.o"
	t gz "$R -g -gz -c dbg.c -o dbz.o && readelf -SW dbz.o | grep -c ' C '"
	t grecord "$R -g -grecord-gcc-switches -c dbg.c -o dgr.o"
	t build-id "readelf -n h0 | grep -c 'Build ID'"
	t pg "$R -pg hello.c -o hpg && ./hpg >/dev/null && ls gmon.out"
	t coverage "$R --coverage hello.c -o hcov && ./hcov >/dev/null; ls *.gcda 2>/dev/null | wc -l"
	t ubsan "$R -fsanitize=undefined hello.c -o hub"
	t asan "$R -fsanitize=address hello.c -o has"
	t openmp "$R -fopenmp hello.c -o homp"

	# Headers.
	t tgmath "$R tg.c -o tg -lm && ./tg"
	t f128-macros "$R f128.c -o f128 -lm && ./f128"
	t march-v3 "echo | $R -march=x86-64-v3 -dM -E - | grep -oE '__(AVX2|BMI2|FMA)__' | sort | tr '\n' ' '"

	# What a build system asks.
	t gnuc "echo | $R -dM -E - | grep -E '^#define (__GNUC__|__GNUC_MINOR__|__STDC_VERSION__|__PIE__|__pic__|__clang__) ' | sort | tr '\n' ' '"
	t v-banner "$R -v 2>&1 | grep -c 'gcc version'"
	t dumpmachine "$R -dumpmachine"
	t dumpversion "$R -dumpversion"
	t print-libc "$full \$($R -print-file-name=libc.so)"
	t print-libgcc "$full \$($R -print-libgcc-file-name)"
	t print-ld "$full \$($R -print-prog-name=ld)"
	t multi-os "$R -print-multi-os-directory"
	t MG "$R -M -MG hello.c"
	t dumpspecs "$R -dumpspecs"
	t gcc-toolchain "$R --gcc-toolchain=/usr hello.c -o gt"
	t specs "$R -specs=/usr/share/dpkg/pie-compile.specs -c hello.c -o sp.o"
	t W-unknown "$R -Wno-such-warning-xyz -c hello.c -o /dev/null && echo no && $R -Wsuch-warning-xyz -c hello.c -o /dev/null"
	t implicit-fn "printf 'int main(void){ return undeclared_fn(); }\n' | $R -x c - -o /dev/null"
	t int-conversion "printf 'int main(void){ int *p = 5; return p != 0; }\n' | $R -x c - -o /dev/null"
	t response-file "echo '-O2 hello.c -o hr' > args.rsp && $R @args.rsp && ./hr"
	t MD "$R -MD -MF h.d -c hello.c -o hmd.o && head -1 h.d | cut -d: -f1"
	t save-temps "$R -save-temps -c hello.c -o hst.o && ls hst.i hst.s | tr '\n' ' '"
	t S-roundtrip "$R -O2 -S hello.c -o hs.s && as hs.s -o hs.o && gcc hs.o -o hsr && ./hsr"
	t lto "$R -flto -O2 hello.c -o hlto && ./hlto"
	t fuse-ld-lld "$R -fuse-ld=lld hello.c -o hl && ./hl"
	t fuse-ld-bfd "$R -fuse-ld=bfd hello.c -o hb && ./hb"
}
