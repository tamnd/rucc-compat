/* plan9/cpp: a macro body that names other macros. */
#include <u.h>
#include <libc.h>

#define A B+1
#define B C*2
#define C 3

void
main(void)
{
	print("%d\n", A);
	exits(nil);
}
