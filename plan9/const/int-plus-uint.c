/* plan9/const: an int and a uint. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof(1 + 0x80000000), -(1 + 0x80000000) < 0, (vlong)(1 + 0x80000000));
	exits(nil);
}
