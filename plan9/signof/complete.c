#include <u.h>
#include <libc.h>
#include <complete.h>

void
main(void)
{
	print("Completion %.8lux\n", signof(Completion));
	print("struct Completion %.8lux\n", signof(struct Completion));
	print("complete %.8lux\n", signof complete);
	print("freecompletion %.8lux\n", signof freecompletion);
	exits(nil);
}
