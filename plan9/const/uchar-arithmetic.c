/* plan9/const: a uchar converted back to int. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof((uchar)200 + 0), -((uchar)200 + 0) < 0, (vlong)((uchar)200 + 0));
	exits(nil);
}
