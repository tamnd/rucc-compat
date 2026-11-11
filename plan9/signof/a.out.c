#include <u.h>
#include <libc.h>
#include <a.out.h>

void
main(void)
{
	print("Exec %.8lux\n", signof(Exec));
	print("Sym %.8lux\n", signof(Sym));
	print("struct Exec %.8lux\n", signof(struct Exec));
	print("struct Sym %.8lux\n", signof(struct Sym));
	exits(nil);
}
