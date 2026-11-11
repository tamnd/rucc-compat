#include <u.h>
#include <libc.h>
#include <ar.h>

void
main(void)
{
	print("struct ar_hdr %.8lux\n", signof(struct ar_hdr));
	exits(nil);
}
