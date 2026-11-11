#include <u.h>
#include <libc.h>
#include <plumb.h>

void
main(void)
{
	print("struct Plumbmsg %d\n", sizeof(struct Plumbmsg));
	print("struct Plumbmsg.src %lud\n", offsetof(struct Plumbmsg, src));
	print("struct Plumbmsg.dst %lud\n", offsetof(struct Plumbmsg, dst));
	print("struct Plumbmsg.wdir %lud\n", offsetof(struct Plumbmsg, wdir));
	print("struct Plumbmsg.type %lud\n", offsetof(struct Plumbmsg, type));
	print("struct Plumbmsg.attr %lud\n", offsetof(struct Plumbmsg, attr));
	print("struct Plumbmsg.ndata %lud\n", offsetof(struct Plumbmsg, ndata));
	print("struct Plumbmsg.data %lud\n", offsetof(struct Plumbmsg, data));
	print("struct Plumbattr %d\n", sizeof(struct Plumbattr));
	print("struct Plumbattr.name %lud\n", offsetof(struct Plumbattr, name));
	print("struct Plumbattr.value %lud\n", offsetof(struct Plumbattr, value));
	print("struct Plumbattr.next %lud\n", offsetof(struct Plumbattr, next));
	exits(nil);
}
