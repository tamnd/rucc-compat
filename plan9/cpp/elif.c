/* plan9/cpp: #elif. */
#include <u.h>
#include <libc.h>

#define V 2
#if V == 1
#define R "one"
#elif V == 2
#define R "two"
#else
#define R "other"
#endif

void
main(void)
{
	print("%s\n", R);
	exits(nil);
}
