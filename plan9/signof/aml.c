#include <u.h>
#include <libc.h>
#include <aml.h>

void
main(void)
{
	print("Amlio %.8lux\n", signof(Amlio));
	print("struct Amlio %.8lux\n", signof(struct Amlio));
	print("amltag %.8lux\n", signof amltag);
	print("amlval %.8lux\n", signof amlval);
	print("amlint %.8lux\n", signof amlint);
	print("amllen %.8lux\n", signof amllen);
	print("amleisaid %.8lux\n", signof amleisaid);
	print("amlnew %.8lux\n", signof amlnew);
	print("amlinit %.8lux\n", signof amlinit);
	print("amlexit %.8lux\n", signof amlexit);
	print("amlload %.8lux\n", signof amlload);
	print("amlwalk %.8lux\n", signof amlwalk);
	print("amleval %.8lux\n", signof amleval);
	print("amlenum %.8lux\n", signof amlenum);
	print("amltake %.8lux\n", signof amltake);
	print("amldrop %.8lux\n", signof amldrop);
	print("amlroot %.8lux\n", signof amlroot);
	print("amldebug %.8lux\n", signof amldebug);
	print("amlintmask %.8lux\n", signof amlintmask);
	print("amlalloc %.8lux\n", signof amlalloc);
	print("amlfree %.8lux\n", signof amlfree);
	print("amldelay %.8lux\n", signof amldelay);
	print("amltime %.8lux\n", signof amltime);
	print("amlmapio %.8lux\n", signof amlmapio);
	print("amlunmapio %.8lux\n", signof amlunmapio);
	exits(nil);
}
