#include <u.h>
#include <libc.h>
#include <keyboard.h>

void
main(void)
{
	print("Keyboardctl %.8lux\n", signof(Keyboardctl));
	print("struct Keyboardctl %.8lux\n", signof(struct Keyboardctl));
	print("initkeyboard %.8lux\n", signof initkeyboard);
	print("ctlkeyboard %.8lux\n", signof ctlkeyboard);
	print("closekeyboard %.8lux\n", signof closekeyboard);
	exits(nil);
}
