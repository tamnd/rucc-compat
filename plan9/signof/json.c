#include <u.h>
#include <libc.h>
#include <json.h>

void
main(void)
{
	print("JSONEl %.8lux\n", signof(JSONEl));
	print("JSON %.8lux\n", signof(JSON));
	print("struct JSONEl %.8lux\n", signof(struct JSONEl));
	print("struct JSON %.8lux\n", signof(struct JSON));
	print("jsonparse %.8lux\n", signof jsonparse);
	print("jsonfree %.8lux\n", signof jsonfree);
	print("jsonbyname %.8lux\n", signof jsonbyname);
	print("jsonstr %.8lux\n", signof jsonstr);
	print("JSONfmt %.8lux\n", signof JSONfmt);
	print("JSONfmtinstall %.8lux\n", signof JSONfmtinstall);
	exits(nil);
}
