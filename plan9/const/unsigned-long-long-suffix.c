/* plan9/const: the ULL suffix. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof(1ULL), -(1ULL) < 0, (vlong)(1ULL));
	exits(nil);
}
