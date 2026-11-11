#include <u.h>
#include <libc.h>
#include <draw.h>
#include <cursor.h>

void
main(void)
{
	print("struct Cursor %d\n", sizeof(struct Cursor));
	print("struct Cursor.offset %lud\n", offsetof(struct Cursor, offset));
	print("struct Cursor.clr %lud\n", offsetof(struct Cursor, clr));
	print("struct Cursor.set %lud\n", offsetof(struct Cursor, set));
	exits(nil);
}
