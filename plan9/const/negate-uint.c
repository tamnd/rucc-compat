/* plan9/const: the negation of a uint constant. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof(-0x80000000), -(-0x80000000) < 0, (vlong)(-0x80000000));
	exits(nil);
}
