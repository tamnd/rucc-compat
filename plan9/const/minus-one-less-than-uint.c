/* plan9/const: a comparison of a negative int with a uint. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof(-1 < 0u), -(-1 < 0u) < 0, (vlong)(-1 < 0u));
	exits(nil);
}
