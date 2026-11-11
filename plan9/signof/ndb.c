#include <u.h>
#include <libc.h>
#include <bio.h>
#include <ndb.h>

void
main(void)
{
	print("Ndb %.8lux\n", signof(Ndb));
	print("Ndbtuple %.8lux\n", signof(Ndbtuple));
	print("Ndbs %.8lux\n", signof(Ndbs));
	print("struct Ndb %.8lux\n", signof(struct Ndb));
	print("struct Ndbtuple %.8lux\n", signof(struct Ndbtuple));
	print("struct Ndbs %.8lux\n", signof(struct Ndbs));
	print("csgetvalue %.8lux\n", signof csgetvalue);
	print("csipinfo %.8lux\n", signof csipinfo);
	print("dnsquery %.8lux\n", signof dnsquery);
	print("ipattr %.8lux\n", signof ipattr);
	print("mkptrname %.8lux\n", signof mkptrname);
	print("ndbcat %.8lux\n", signof ndbcat);
	print("ndbchanged %.8lux\n", signof ndbchanged);
	print("ndbclose %.8lux\n", signof ndbclose);
	print("ndbconcatenate %.8lux\n", signof ndbconcatenate);
	print("ndbdiscard %.8lux\n", signof ndbdiscard);
	print("ndbfree %.8lux\n", signof ndbfree);
	print("ndbgetipaddr %.8lux\n", signof ndbgetipaddr);
	print("ndbgetvalue %.8lux\n", signof ndbgetvalue);
	print("ndbfindattr %.8lux\n", signof ndbfindattr);
	print("ndbhash %.8lux\n", signof ndbhash);
	print("ndbipinfo %.8lux\n", signof ndbipinfo);
	print("ndbnew %.8lux\n", signof ndbnew);
	print("ndbopen %.8lux\n", signof ndbopen);
	print("ndbparse %.8lux\n", signof ndbparse);
	print("ndbreopen %.8lux\n", signof ndbreopen);
	print("ndbreorder %.8lux\n", signof ndbreorder);
	print("ndbsearch %.8lux\n", signof ndbsearch);
	print("ndbsetval %.8lux\n", signof ndbsetval);
	print("ndbsnext %.8lux\n", signof ndbsnext);
	print("ndbsubstitute %.8lux\n", signof ndbsubstitute);
	print("ndbdedup %.8lux\n", signof ndbdedup);
	print("ndbsetmalloctag %.8lux\n", signof ndbsetmalloctag);
	print("ndbvalfmt %.8lux\n", signof ndbvalfmt);
	exits(nil);
}
