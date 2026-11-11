/* plan9/const: a character constant. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof('a'), -('a') < 0, (vlong)('a'));
	exits(nil);
}
