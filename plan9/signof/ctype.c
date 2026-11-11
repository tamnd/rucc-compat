#include <u.h>
#include <libc.h>
#include <ctype.h>

void
main(void)
{
	print("_ctype %.8lux\n", signof _ctype);
	exits(nil);
}
