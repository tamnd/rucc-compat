#include <u.h>
#include <libc.h>
#include <ureg.h>

void
main(void)
{
	print("struct Ureg %d\n", sizeof(struct Ureg));
	print("struct Ureg.ax %lud\n", offsetof(struct Ureg, ax));
	print("struct Ureg.bx %lud\n", offsetof(struct Ureg, bx));
	print("struct Ureg.cx %lud\n", offsetof(struct Ureg, cx));
	print("struct Ureg.dx %lud\n", offsetof(struct Ureg, dx));
	print("struct Ureg.si %lud\n", offsetof(struct Ureg, si));
	print("struct Ureg.di %lud\n", offsetof(struct Ureg, di));
	print("struct Ureg.bp %lud\n", offsetof(struct Ureg, bp));
	print("struct Ureg.r8 %lud\n", offsetof(struct Ureg, r8));
	print("struct Ureg.r9 %lud\n", offsetof(struct Ureg, r9));
	print("struct Ureg.r10 %lud\n", offsetof(struct Ureg, r10));
	print("struct Ureg.r11 %lud\n", offsetof(struct Ureg, r11));
	print("struct Ureg.r12 %lud\n", offsetof(struct Ureg, r12));
	print("struct Ureg.r13 %lud\n", offsetof(struct Ureg, r13));
	print("struct Ureg.r14 %lud\n", offsetof(struct Ureg, r14));
	print("struct Ureg.r15 %lud\n", offsetof(struct Ureg, r15));
	print("struct Ureg.ds %lud\n", offsetof(struct Ureg, ds));
	print("struct Ureg.es %lud\n", offsetof(struct Ureg, es));
	print("struct Ureg.fs %lud\n", offsetof(struct Ureg, fs));
	print("struct Ureg.gs %lud\n", offsetof(struct Ureg, gs));
	print("struct Ureg.type %lud\n", offsetof(struct Ureg, type));
	print("struct Ureg.error %lud\n", offsetof(struct Ureg, error));
	print("struct Ureg.pc %lud\n", offsetof(struct Ureg, pc));
	print("struct Ureg.cs %lud\n", offsetof(struct Ureg, cs));
	print("struct Ureg.flags %lud\n", offsetof(struct Ureg, flags));
	print("struct Ureg.sp %lud\n", offsetof(struct Ureg, sp));
	print("struct Ureg.ss %lud\n", offsetof(struct Ureg, ss));
	exits(nil);
}
