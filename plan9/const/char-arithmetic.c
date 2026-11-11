/* plan9/const: a char converted back to int, which is signed in kencc. */
#include <u.h>
#include <libc.h>

void
main(void)
{
	print("%d %d %lld\n", sizeof((char)200 + 0), -((char)200 + 0) < 0, (vlong)((char)200 + 0));
	exits(nil);
}
