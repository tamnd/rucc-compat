/* plan9/const: an octal constant above uint. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof(040000000000), -(040000000000) < 0, (vlong)(040000000000));
	exits(nil);
}
