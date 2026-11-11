/* plan9/const: the L suffix on a constant above ulong, which kencc truncates. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof(4294967296L), -(4294967296L) < 0, (vlong)(4294967296L));
	exits(nil);
}
