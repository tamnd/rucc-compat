/* plan9/cpp: a macro argument with a comma in parentheses. */
#include <u.h>
#include <libc.h>

#define FIRST(a, b) (a)

static int
add(int x, int y)
{
	return x + y;
}

void
main(void)
{
	print("%d\n", FIRST(add(1, 2), 9));
	exits(nil);
}
