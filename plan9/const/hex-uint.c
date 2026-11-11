/* plan9/const: a hexadecimal constant above int, which goes to uint before it widens. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof(0x80000000), -(0x80000000) < 0, (vlong)(0x80000000));
	exits(nil);
}
