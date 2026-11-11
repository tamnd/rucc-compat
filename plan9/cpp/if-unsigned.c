/* plan9/cpp: the arithmetic of #if. */
#include <u.h>
#include <libc.h>

#if -1 < 0u
#define R "unsigned"
#else
#define R "signed"
#endif
#if 0x7fffffff + 1 > 0
#define W "wide"
#else
#define W "narrow"
#endif

void
main(void)
{
	print("%s %s\n", R, W);
	exits(nil);
}
