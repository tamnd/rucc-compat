/* plan9/const: the L suffix, which gives a 32 bit long. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof(1L), -(1L) < 0, (vlong)(1L));
	exits(nil);
}
