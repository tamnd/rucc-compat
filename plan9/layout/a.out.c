#include <u.h>
#include <libc.h>
#include <a.out.h>

void
main(void)
{
	print("struct Exec %d\n", sizeof(struct Exec));
	print("struct Exec.magic %lud\n", offsetof(struct Exec, magic));
	print("struct Exec.text %lud\n", offsetof(struct Exec, text));
	print("struct Exec.data %lud\n", offsetof(struct Exec, data));
	print("struct Exec.bss %lud\n", offsetof(struct Exec, bss));
	print("struct Exec.syms %lud\n", offsetof(struct Exec, syms));
	print("struct Exec.entry %lud\n", offsetof(struct Exec, entry));
	print("struct Exec.spsz %lud\n", offsetof(struct Exec, spsz));
	print("struct Exec.pcsz %lud\n", offsetof(struct Exec, pcsz));
	print("struct Sym %d\n", sizeof(struct Sym));
	print("struct Sym.value %lud\n", offsetof(struct Sym, value));
	print("struct Sym.sig %lud\n", offsetof(struct Sym, sig));
	print("struct Sym.type %lud\n", offsetof(struct Sym, type));
	print("struct Sym.name %lud\n", offsetof(struct Sym, name));
	exits(nil);
}
