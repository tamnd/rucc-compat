/* plan9/cpp: an empty macro argument. */
#include <u.h>
#include <libc.h>

#define PAIR(a, b) a 10 b

void
main(void)
{
	print("%d\n", PAIR(, + 1));
	exits(nil);
}
