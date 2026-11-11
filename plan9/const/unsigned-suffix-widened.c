/* plan9/const: the u suffix on a constant above uint. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof(0x100000000u), -(0x100000000u) < 0, (vlong)(0x100000000u));
	exits(nil);
}
