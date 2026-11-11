#include <u.h>
#include <libc.h>
#include <draw.h>
#include <event.h>

void
main(void)
{
	print("struct Mouse %d\n", sizeof(struct Mouse));
	print("struct Mouse.buttons %lud\n", offsetof(struct Mouse, buttons));
	print("struct Mouse.xy %lud\n", offsetof(struct Mouse, xy));
	print("struct Mouse.msec %lud\n", offsetof(struct Mouse, msec));
	print("struct Event %d\n", sizeof(struct Event));
	print("struct Event.kbdc %lud\n", offsetof(struct Event, kbdc));
	print("struct Event.mouse %lud\n", offsetof(struct Event, mouse));
	print("struct Event.n %lud\n", offsetof(struct Event, n));
	print("struct Event.v %lud\n", offsetof(struct Event, v));
	print("struct Event.data %lud\n", offsetof(struct Event, data));
	print("struct Menu %d\n", sizeof(struct Menu));
	print("struct Menu.item %lud\n", offsetof(struct Menu, item));
	print("struct Menu.gen %lud\n", offsetof(struct Menu, gen));
	print("struct Menu.lasthit %lud\n", offsetof(struct Menu, lasthit));
	exits(nil);
}
