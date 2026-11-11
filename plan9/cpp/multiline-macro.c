/* plan9/cpp: a macro body continued with a backslash. */
#include <u.h>
#include <libc.h>

#define SUM(a, b) \
	((a) + \
	 (b))

void
main(void)
{
	print("%d\n", SUM(2, 3));
	exits(nil);
}
