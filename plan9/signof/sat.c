#include <u.h>
#include <libc.h>
#include <sat.h>

void
main(void)
{
	print("SATParam %.8lux\n", signof(SATParam));
	print("SATSolve %.8lux\n", signof(SATSolve));
	print("SATBlock %.8lux\n", signof(SATBlock));
	print("struct SATParam %.8lux\n", signof(struct SATParam));
	print("struct SATBlock %.8lux\n", signof(struct SATBlock));
	print("struct SATSolve %.8lux\n", signof(struct SATSolve));
	print("satnew %.8lux\n", signof satnew);
	print("satadd1 %.8lux\n", signof satadd1);
	print("sataddv %.8lux\n", signof sataddv);
	print("satrange1 %.8lux\n", signof satrange1);
	print("satrangev %.8lux\n", signof satrangev);
	print("satsolve %.8lux\n", signof satsolve);
	print("satmore %.8lux\n", signof satmore);
	print("satval %.8lux\n", signof satval);
	print("satfree %.8lux\n", signof satfree);
	print("satreset %.8lux\n", signof satreset);
	print("satget %.8lux\n", signof satget);
	print("satvafix %.8lux\n", signof satvafix);
	exits(nil);
}
