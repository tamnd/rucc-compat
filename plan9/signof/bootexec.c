#include <u.h>
#include <libc.h>
#include <bootexec.h>

void
main(void)
{
	print("struct coffsect %.8lux\n", signof(struct coffsect));
	print("struct mipsexec %.8lux\n", signof(struct mipsexec));
	print("struct mips4kexec %.8lux\n", signof(struct mips4kexec));
	print("struct sparcexec %.8lux\n", signof(struct sparcexec));
	print("struct nextexec %.8lux\n", signof(struct nextexec));
	print("struct nexthdr %.8lux\n", signof(struct nexthdr));
	print("struct nextcmd %.8lux\n", signof(struct nextcmd));
	print("struct nextsect %.8lux\n", signof(struct nextsect));
	print("struct nextsym %.8lux\n", signof(struct nextsym));
	print("struct i386exec %.8lux\n", signof(struct i386exec));
	print("struct i386coff %.8lux\n", signof(struct i386coff));
	print("struct i386hdr %.8lux\n", signof(struct i386hdr));
	exits(nil);
}
