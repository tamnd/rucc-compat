/* plan9/const: a shift into the sign bit of int. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof(1 << 31), -(1 << 31) < 0, (vlong)(1 << 31));
	exits(nil);
}
