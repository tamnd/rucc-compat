/* plan9/const: a long and a uint, which have the same width. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof(1L + 0x80000000), -(1L + 0x80000000) < 0, (vlong)(1L + 0x80000000));
	exits(nil);
}
