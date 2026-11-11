#include <u.h>
#include <libc.h>
#include <draw.h>
#include <memdraw.h>
#include <memlayer.h>

void
main(void)
{
	print("struct Memscreen %d\n", sizeof(struct Memscreen));
	print("struct Memscreen.frontmost %lud\n", offsetof(struct Memscreen, frontmost));
	print("struct Memscreen.rearmost %lud\n", offsetof(struct Memscreen, rearmost));
	print("struct Memscreen.image %lud\n", offsetof(struct Memscreen, image));
	print("struct Memscreen.fill %lud\n", offsetof(struct Memscreen, fill));
	print("struct Memlayer %d\n", sizeof(struct Memlayer));
	print("struct Memlayer.screenr %lud\n", offsetof(struct Memlayer, screenr));
	print("struct Memlayer.delta %lud\n", offsetof(struct Memlayer, delta));
	print("struct Memlayer.screen %lud\n", offsetof(struct Memlayer, screen));
	print("struct Memlayer.front %lud\n", offsetof(struct Memlayer, front));
	print("struct Memlayer.rear %lud\n", offsetof(struct Memlayer, rear));
	print("struct Memlayer.clear %lud\n", offsetof(struct Memlayer, clear));
	print("struct Memlayer.save %lud\n", offsetof(struct Memlayer, save));
	print("struct Memlayer.refreshfn %lud\n", offsetof(struct Memlayer, refreshfn));
	print("struct Memlayer.refreshptr %lud\n", offsetof(struct Memlayer, refreshptr));
	exits(nil);
}
