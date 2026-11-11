#include <u.h>
#include <libc.h>
#include <draw.h>
#include <cursor.h>

void
main(void)
{
	print("struct Cursor %.8lux\n", signof(struct Cursor));
	exits(nil);
}
