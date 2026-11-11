/* plan9/const: a hexadecimal constant above uint, which kencc widens to vlong. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof(0x100000000), -(0x100000000) < 0, (vlong)(0x100000000));
	exits(nil);
}
