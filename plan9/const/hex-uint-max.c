/* plan9/const: the largest hexadecimal constant of type uint. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof(0xFFFFFFFF), -(0xFFFFFFFF) < 0, (vlong)(0xFFFFFFFF));
	exits(nil);
}
