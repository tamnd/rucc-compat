#include <u.h>
#include <libc.h>
#include <bin.h>

void
main(void)
{
	print("binalloc %.8lux\n", signof binalloc);
	print("bingrow %.8lux\n", signof bingrow);
	print("binfree %.8lux\n", signof binfree);
	exits(nil);
}
