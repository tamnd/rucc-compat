/* plan9/cpp: a function macro named with no parenthesis is not replaced. */
#include <u.h>
#include <libc.h>

#define f(x) ((x)+1)

static int
f1(int (*g)(int))
{
	return g(1);
}

static int
(f)(int x)
{
	return x*10;
}

void
main(void)
{
	print("%d %d\n", f(1), f1(f));
	exits(nil);
}
