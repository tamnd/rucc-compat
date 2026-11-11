/* plan9/const: the largest decimal constant of type int. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof(2147483647), -(2147483647) < 0, (vlong)(2147483647));
	exits(nil);
}
