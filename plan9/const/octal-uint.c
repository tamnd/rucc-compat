/* plan9/const: an octal constant above int. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof(020000000000), -(020000000000) < 0, (vlong)(020000000000));
	exits(nil);
}
