/* plan9/const: a comparison of a negative int with a ulong. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof(-1 < 0UL), -(-1 < 0UL) < 0, (vlong)(-1 < 0UL));
	exits(nil);
}
