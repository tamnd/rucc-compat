/* plan9/cpp: a comment in a directive. */
#include <u.h>
#include <libc.h>

#define N /* a comment */ 7 /* another */

void
main(void)
{
	print("%d\n", N);
	exits(nil);
}
