#include <u.h>
#include <libc.h>
#include <pcm.h>

void
main(void)
{
	print("Pcmdesc %.8lux\n", signof(Pcmdesc));
	print("struct Pcmdesc %.8lux\n", signof(struct Pcmdesc));
	print("pcmdescdef %.8lux\n", signof pcmdescdef);
	print("pcmdescfmt %.8lux\n", signof pcmdescfmt);
	print("mkpcmdesc %.8lux\n", signof mkpcmdesc);
	print("allocpcmconv %.8lux\n", signof allocpcmconv);
	print("freepcmconv %.8lux\n", signof freepcmconv);
	print("pcmconv %.8lux\n", signof pcmconv);
	print("pcmratio %.8lux\n", signof pcmratio);
	exits(nil);
}
