/* plan9/cpp: the pragmas of libc.h, and an unknown pragma. */
#include <u.h>
#include <libc.h>

#pragma varargck argpos myprint 1
#pragma unknownpragma something

static void
myprint(char *fmt, ...)
{
	va_list arg;

	va_start(arg, fmt);
	vfprint(1, fmt, arg);
	va_end(arg);
}

void
main(void)
{
	myprint("%d %s\n", 4, "four");
	exits(nil);
}
