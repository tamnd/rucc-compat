#include <u.h>
#include <libc.h>
#include <plumb.h>

void
main(void)
{
	print("Plumbattr %.8lux\n", signof(Plumbattr));
	print("Plumbmsg %.8lux\n", signof(Plumbmsg));
	print("struct Plumbmsg %.8lux\n", signof(struct Plumbmsg));
	print("struct Plumbattr %.8lux\n", signof(struct Plumbattr));
	print("plumbsend %.8lux\n", signof plumbsend);
	print("plumbsendtext %.8lux\n", signof plumbsendtext);
	print("plumbrecv %.8lux\n", signof plumbrecv);
	print("plumbpack %.8lux\n", signof plumbpack);
	print("plumbunpack %.8lux\n", signof plumbunpack);
	print("plumbunpackpartial %.8lux\n", signof plumbunpackpartial);
	print("plumbpackattr %.8lux\n", signof plumbpackattr);
	print("plumbunpackattr %.8lux\n", signof plumbunpackattr);
	print("plumbaddattr %.8lux\n", signof plumbaddattr);
	print("plumbdelattr %.8lux\n", signof plumbdelattr);
	print("plumbfree %.8lux\n", signof plumbfree);
	print("plumblookup %.8lux\n", signof plumblookup);
	print("plumbopen %.8lux\n", signof plumbopen);
	print("eplumb %.8lux\n", signof eplumb);
	exits(nil);
}
