/* plan9/const: the u suffix on a small constant. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof(1u), -(1u) < 0, (vlong)(1u));
	exits(nil);
}
