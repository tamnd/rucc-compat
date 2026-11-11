/* plan9/const: a long and a vlong. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof(1L + 2147483648), -(1L + 2147483648) < 0, (vlong)(1L + 2147483648));
	exits(nil);
}
