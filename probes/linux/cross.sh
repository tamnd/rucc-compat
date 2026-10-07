# The cross probes, read by run.sh. They fetch the sysroots into the rucc cache and run the aarch64
# programs under qemu-aarch64, so the machine needs qemu-user, the Ubuntu arm64 cross libc in
# /usr/aarch64-linux-gnu, and the network the first time.

run() {
	echo "# $($R --version | head -1)"
	echo "# $(uname -m), $(ldd --version 2>&1 | head -1)"

	for row in aarch64-linux-gnu x86_64-linux-musl aarch64-linux-musl i686-linux-gnu riscv64-linux-gnu x86_64-linux-gnu.2.28; do
		t "fetch-$row" "$R --fetch $row >/dev/null"
	done

	t x86_64-musl-static "$R --target=x86_64-linux-musl -static -O2 hello.c -o hm && ./hm"
	t x86_64-musl-pie "$R --target=x86_64-linux-musl -O2 hello.c -o hmd && ./hmd"
	t x86_64-musl-static-pie "$R --target=x86_64-linux-musl -static-pie -O2 hello.c -o hmsp && ./hmsp"
	t x86_64-musl-threads "$R --target=x86_64-linux-musl -static -O2 thr.c -o tm && ./tm"
	t x86_64-musl-cpu "$R --target=x86_64-linux-musl -static -O2 ifunc.c -o ifm && ./ifm"
	t aarch64-gnu "$R --target=aarch64-linux-gnu -O2 hello.c -o ha && qemu-aarch64 -L /usr/aarch64-linux-gnu ./ha"
	t aarch64-gnu-threads "$R --target=aarch64-linux-gnu -O2 thr.c -o tha -pthread && qemu-aarch64 -L /usr/aarch64-linux-gnu ./tha"
	t aarch64-gnu-bti-object "$R --target=aarch64-linux-gnu -O2 -mbranch-protection=standard -c hello.c -o hab.o && readelf -n hab.o | grep -o 'AArch64 feature: .*'"
	t aarch64-musl-static "$R --target=aarch64-linux-musl -static -O2 hello.c -o ham && qemu-aarch64 ./ham"
	t aarch64-musl-pie "$R --target=aarch64-linux-musl -O2 hello.c -o hamd"
	t aarch64-musl-threads "$R --target=aarch64-linux-musl -static -O2 thr.c -o tam && qemu-aarch64 ./tam"
	t i686-gnu "$R --target=i686-linux-gnu -O2 hello.c -o hi && ./hi"
	t m32 "$R -m32 -O2 hello.c -o h32 && ./h32"
	t i686-threads "$R -m32 -O2 thr.c -o t32 -pthread && ./t32"
	t riscv64-compile "$R --target=riscv64-linux-gnu -c hello.c -o hr.o"
	t glibc-2.28 "$R --target=x86_64-linux-gnu.2.28 -O2 hello.c -o h228 && ./h228 && objdump -T h228 | grep -o 'GLIBC_[0-9.]*' | sort -uV | tail -1"
	t aarch64-bigtls "$R --target=aarch64-linux-gnu -fPIC -shared bigtls.c -o libbiga.so"
}
