#include <u.h>
#include <libc.h>
#include <draw.h>
#include <memdraw.h>
#include <memlayer.h>

void
main(void)
{
	print("Memscreen %.8lux\n", signof(Memscreen));
	print("Refreshfn %.8lux\n", signof(Refreshfn));
	print("struct Memscreen %.8lux\n", signof(struct Memscreen));
	print("struct Memlayer %.8lux\n", signof(struct Memlayer));
	print("memload %.8lux\n", signof memload);
	print("memunload %.8lux\n", signof memunload);
	print("_memlayerop %.8lux\n", signof _memlayerop);
	print("memlalloc %.8lux\n", signof memlalloc);
	print("memldelete %.8lux\n", signof memldelete);
	print("memlfree %.8lux\n", signof memlfree);
	print("memltofront %.8lux\n", signof memltofront);
	print("memltofrontn %.8lux\n", signof memltofrontn);
	print("_memltofrontfill %.8lux\n", signof _memltofrontfill);
	print("memltorear %.8lux\n", signof memltorear);
	print("memltorearn %.8lux\n", signof memltorearn);
	print("memlsetrefresh %.8lux\n", signof memlsetrefresh);
	print("memlhide %.8lux\n", signof memlhide);
	print("memlexpose %.8lux\n", signof memlexpose);
	print("_memlsetclear %.8lux\n", signof _memlsetclear);
	print("memlorigin %.8lux\n", signof memlorigin);
	print("memlnorefresh %.8lux\n", signof memlnorefresh);
	exits(nil);
}
