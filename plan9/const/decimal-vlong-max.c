/* plan9/const: the largest decimal constant of type vlong. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof(9223372036854775807), -(9223372036854775807) < 0, (vlong)(9223372036854775807));
	exits(nil);
}
