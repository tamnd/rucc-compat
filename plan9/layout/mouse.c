#include <u.h>
#include <libc.h>
#include <draw.h>
#include <mouse.h>

void
main(void)
{
	print("struct Mouse %d\n", sizeof(struct Mouse));
	print("struct Mouse.buttons %lud\n", offsetof(struct Mouse, buttons));
	print("struct Mouse.xy %lud\n", offsetof(struct Mouse, xy));
	print("struct Mouse.msec %lud\n", offsetof(struct Mouse, msec));
	print("struct Mousectl %d\n", sizeof(struct Mousectl));
	print("struct Mousectl.c %lud\n", offsetof(struct Mousectl, c));
	print("struct Mousectl.resizec %lud\n", offsetof(struct Mousectl, resizec));
	print("struct Mousectl.file %lud\n", offsetof(struct Mousectl, file));
	print("struct Mousectl.mfd %lud\n", offsetof(struct Mousectl, mfd));
	print("struct Mousectl.cfd %lud\n", offsetof(struct Mousectl, cfd));
	print("struct Mousectl.pid %lud\n", offsetof(struct Mousectl, pid));
	print("struct Mousectl.image %lud\n", offsetof(struct Mousectl, image));
	print("struct Menu %d\n", sizeof(struct Menu));
	print("struct Menu.item %lud\n", offsetof(struct Menu, item));
	print("struct Menu.gen %lud\n", offsetof(struct Menu, gen));
	print("struct Menu.lasthit %lud\n", offsetof(struct Menu, lasthit));
	exits(nil);
}
