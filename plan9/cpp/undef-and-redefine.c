/* plan9/cpp: #undef and a new definition. */
#include <u.h>
#include <libc.h>

#define V 1
#undef V
#define V 2

void
main(void)
{
	print("%d\n", V);
	exits(nil);
}
