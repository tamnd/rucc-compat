#include <u.h>
#include <libc.h>
#include <fcall.h>

void
main(void)
{
	print("Fcall %.8lux\n", signof(Fcall));
	print("struct Fcall %.8lux\n", signof(struct Fcall));
	exits(nil);
}
