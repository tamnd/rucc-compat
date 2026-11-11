#include <u.h>
#include <libc.h>
#include <fis.h>

void
main(void)
{
	print("Sfis %.8lux\n", signof(Sfis));
	print("Cfis %.8lux\n", signof(Cfis));
	print("struct Sfis %.8lux\n", signof(struct Sfis));
	print("struct Cfis %.8lux\n", signof(struct Cfis));
	print("setfissig %.8lux\n", signof setfissig);
	print("txmodefis %.8lux\n", signof txmodefis);
	print("atapirwfis %.8lux\n", signof atapirwfis);
	print("featfis %.8lux\n", signof featfis);
	print("flushcachefis %.8lux\n", signof flushcachefis);
	print("identifyfis %.8lux\n", signof identifyfis);
	print("nopfis %.8lux\n", signof nopfis);
	print("rwfis %.8lux\n", signof rwfis);
	print("skelfis %.8lux\n", signof skelfis);
	print("sigtofis %.8lux\n", signof sigtofis);
	print("fisrw %.8lux\n", signof fisrw);
	print("idmove %.8lux\n", signof idmove);
	print("idfeat %.8lux\n", signof idfeat);
	print("idwwn %.8lux\n", signof idwwn);
	print("idss %.8lux\n", signof idss);
	print("idpuis %.8lux\n", signof idpuis);
	print("id16 %.8lux\n", signof id16);
	print("id32 %.8lux\n", signof id32);
	print("id64 %.8lux\n", signof id64);
	print("pflag %.8lux\n", signof pflag);
	print("fistosig %.8lux\n", signof fistosig);
	print("smpskelframe %.8lux\n", signof smpskelframe);
	print("sashash %.8lux\n", signof sashash);
	print("sasbhash %.8lux\n", signof sasbhash);
	exits(nil);
}
