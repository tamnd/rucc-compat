/* plan9/cpp: kencc replaces a macro argument in a string literal of the body. */
#include <u.h>
#include <libc.h>

#define S(x) "x is x"

void
main(void)
{
	print("%s\n", S(abc));
	exits(nil);
}
