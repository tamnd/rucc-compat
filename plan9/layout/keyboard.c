#include <u.h>
#include <libc.h>
#include <keyboard.h>

void
main(void)
{
	print("struct Keyboardctl %d\n", sizeof(struct Keyboardctl));
	print("struct Keyboardctl.c %lud\n", offsetof(struct Keyboardctl, c));
	print("struct Keyboardctl.file %lud\n", offsetof(struct Keyboardctl, file));
	print("struct Keyboardctl.consfd %lud\n", offsetof(struct Keyboardctl, consfd));
	print("struct Keyboardctl.ctlfd %lud\n", offsetof(struct Keyboardctl, ctlfd));
	print("struct Keyboardctl.pid %lud\n", offsetof(struct Keyboardctl, pid));
	exits(nil);
}
