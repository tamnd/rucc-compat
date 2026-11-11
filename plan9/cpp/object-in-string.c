/* plan9/cpp: an object macro is not replaced in a string literal. */
#include <u.h>
#include <libc.h>

#define NAME other

void
main(void)
{
	print("%s\n", "NAME");
	exits(nil);
}
