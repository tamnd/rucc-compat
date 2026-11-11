/* plan9/const: the LL suffix. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof(1LL), -(1LL) < 0, (vlong)(1LL));
	exits(nil);
}
