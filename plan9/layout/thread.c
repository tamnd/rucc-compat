#include <u.h>
#include <libc.h>
#include <thread.h>

void
main(void)
{
	print("struct Channel %d\n", sizeof(struct Channel));
	print("struct Channel.s %lud\n", offsetof(struct Channel, s));
	print("struct Channel.f %lud\n", offsetof(struct Channel, f));
	print("struct Channel.n %lud\n", offsetof(struct Channel, n));
	print("struct Channel.e %lud\n", offsetof(struct Channel, e));
	print("struct Channel.freed %lud\n", offsetof(struct Channel, freed));
	print("struct Channel.qentry %lud\n", offsetof(struct Channel, qentry));
	print("struct Channel.nentry %lud\n", offsetof(struct Channel, nentry));
	print("struct Channel.closed %lud\n", offsetof(struct Channel, closed));
	print("struct Channel.v %lud\n", offsetof(struct Channel, v));
	print("struct Alt %d\n", sizeof(struct Alt));
	print("struct Alt.c %lud\n", offsetof(struct Alt, c));
	print("struct Alt.v %lud\n", offsetof(struct Alt, v));
	print("struct Alt.op %lud\n", offsetof(struct Alt, op));
	print("struct Alt.err %lud\n", offsetof(struct Alt, err));
	print("struct Alt.tag %lud\n", offsetof(struct Alt, tag));
	print("struct Alt.entryno %lud\n", offsetof(struct Alt, entryno));
	print("struct Ref %d\n", sizeof(struct Ref));
	print("struct Ref.ref %lud\n", offsetof(struct Ref, ref));
	exits(nil);
}
