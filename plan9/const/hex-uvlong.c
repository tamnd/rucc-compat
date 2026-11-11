/* plan9/const: a hexadecimal constant above vlong. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof(0x8000000000000000), -(0x8000000000000000) < 0, (vlong)(0x8000000000000000));
	exits(nil);
}
