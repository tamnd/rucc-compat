#include <u.h>
#include <libc.h>
#include <regexp.h>

void
main(void)
{
	print("Resub %.8lux\n", signof(Resub));
	print("Reprog %.8lux\n", signof(Reprog));
	print("struct Resub %.8lux\n", signof(struct Resub));
	print("struct Reprog %.8lux\n", signof(struct Reprog));
	print("regcomp %.8lux\n", signof regcomp);
	print("regcomplit %.8lux\n", signof regcomplit);
	print("regcompnl %.8lux\n", signof regcompnl);
	print("regerror %.8lux\n", signof regerror);
	print("regexec %.8lux\n", signof regexec);
	print("regsub %.8lux\n", signof regsub);
	print("rregexec %.8lux\n", signof rregexec);
	print("rregsub %.8lux\n", signof rregsub);
	print("reprogfmt %.8lux\n", signof reprogfmt);
	exits(nil);
}
