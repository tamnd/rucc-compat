#include <u.h>
#include <libc.h>
#include <aml.h>

void
main(void)
{
	print("struct Amlio %d\n", sizeof(struct Amlio));
	print("struct Amlio.space %lud\n", offsetof(struct Amlio, space));
	print("struct Amlio.off %lud\n", offsetof(struct Amlio, off));
	print("struct Amlio.len %lud\n", offsetof(struct Amlio, len));
	print("struct Amlio.name %lud\n", offsetof(struct Amlio, name));
	print("struct Amlio.va %lud\n", offsetof(struct Amlio, va));
	print("struct Amlio.aux %lud\n", offsetof(struct Amlio, aux));
	print("struct Amlio.read %lud\n", offsetof(struct Amlio, read));
	print("struct Amlio.write %lud\n", offsetof(struct Amlio, write));
	exits(nil);
}
