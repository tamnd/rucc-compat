/* plan9/const: a shift into the sign bit of long. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof(1L << 31), -(1L << 31) < 0, (vlong)(1L << 31));
	exits(nil);
}
