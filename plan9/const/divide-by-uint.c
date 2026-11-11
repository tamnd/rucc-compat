/* plan9/const: a negative int divided by a uint. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof(-7 / 2u), -(-7 / 2u) < 0, (vlong)(-7 / 2u));
	exits(nil);
}
