/* plan9/const: the L suffix on a decimal constant above long, which kencc makes ulong. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof(2147483648L), -(2147483648L) < 0, (vlong)(2147483648L));
	exits(nil);
}
