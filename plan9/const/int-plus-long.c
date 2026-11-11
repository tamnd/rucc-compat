/* plan9/const: an int and a long. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof(1 + 1L), -(1 + 1L) < 0, (vlong)(1 + 1L));
	exits(nil);
}
