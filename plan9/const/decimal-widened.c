/* plan9/const: a decimal constant above int, which kencc widens to vlong and not to long. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof(2147483648), -(2147483648) < 0, (vlong)(2147483648));
	exits(nil);
}
