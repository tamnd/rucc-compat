/* plan9/cpp: a macro that names itself is not replaced again. */
#include <u.h>
#include <libc.h>

static int x = 5;
#define x (x+1)

void
main(void)
{
	print("%d\n", x);
	exits(nil);
}
