#include <u.h>
#include <libc.h>
#include <String.h>

void
main(void)
{
	print("struct String %d\n", sizeof(struct String));
	print("struct String.base %lud\n", offsetof(struct String, base));
	print("struct String.end %lud\n", offsetof(struct String, end));
	print("struct String.ptr %lud\n", offsetof(struct String, ptr));
	print("struct String.ref %lud\n", offsetof(struct String, ref));
	print("struct String.fixed %lud\n", offsetof(struct String, fixed));
	exits(nil);
}
