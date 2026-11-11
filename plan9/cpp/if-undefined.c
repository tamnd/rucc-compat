/* plan9/cpp: an undefined name in #if is 0. */
#include <u.h>
#include <libc.h>

#if UNDEFINED
#define R "defined"
#else
#define R "zero"
#endif
#ifdef UNDEFINED
#define D "yes"
#else
#define D "no"
#endif

void
main(void)
{
	print("%s %s\n", R, D);
	exits(nil);
}
