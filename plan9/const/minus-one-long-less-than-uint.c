/* plan9/const: a comparison of a negative long with a uint. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof(-1L < 0u), -(-1L < 0u) < 0, (vlong)(-1L < 0u));
	exits(nil);
}
