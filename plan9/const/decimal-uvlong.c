/* plan9/const: a decimal constant above vlong, which kencc makes uvlong. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof(9223372036854775808), -(9223372036854775808) < 0, (vlong)(9223372036854775808));
	exits(nil);
}
