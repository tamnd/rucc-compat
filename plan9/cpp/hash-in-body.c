/* plan9/cpp: a # in a macro body is not an operator in kencc. */
#include <u.h>
#include <libc.h>

#define H(x) "#x"

void
main(void)
{
	print("%s\n", H(y));
	exits(nil);
}
