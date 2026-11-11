/* plan9/const: a character constant with the high bit set. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof('\377'), -('\377') < 0, (vlong)('\377'));
	exits(nil);
}
