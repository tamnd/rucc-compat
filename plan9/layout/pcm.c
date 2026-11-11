#include <u.h>
#include <libc.h>
#include <pcm.h>

void
main(void)
{
	print("struct Pcmdesc %d\n", sizeof(struct Pcmdesc));
	print("struct Pcmdesc.rate %lud\n", offsetof(struct Pcmdesc, rate));
	print("struct Pcmdesc.channels %lud\n", offsetof(struct Pcmdesc, channels));
	print("struct Pcmdesc.framesz %lud\n", offsetof(struct Pcmdesc, framesz));
	print("struct Pcmdesc.abits %lud\n", offsetof(struct Pcmdesc, abits));
	print("struct Pcmdesc.bits %lud\n", offsetof(struct Pcmdesc, bits));
	print("struct Pcmdesc.fmt %lud\n", offsetof(struct Pcmdesc, fmt));
	exits(nil);
}
