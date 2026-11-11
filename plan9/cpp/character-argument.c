/* plan9/cpp: kencc replaces a macro argument in a character constant of the body. */
#include <u.h>
#include <libc.h>

#define C(x) 'x'

void
main(void)
{
	print("%c\n", C(q));
	exits(nil);
}
