#include <u.h>
#include <libc.h>
#include <mp.h>

void
main(void)
{
	print("struct mpint %d\n", sizeof(struct mpint));
	print("struct mpint.sign %lud\n", offsetof(struct mpint, sign));
	print("struct mpint.size %lud\n", offsetof(struct mpint, size));
	print("struct mpint.top %lud\n", offsetof(struct mpint, top));
	print("struct mpint.p %lud\n", offsetof(struct mpint, p));
	print("struct mpint.flags %lud\n", offsetof(struct mpint, flags));
	print("struct CRTres %d\n", sizeof(struct CRTres));
	print("struct CRTres.n %lud\n", offsetof(struct CRTres, n));
	print("struct CRTres.r %lud\n", offsetof(struct CRTres, r));
	print("struct Mfield %d\n", sizeof(struct Mfield));
	print("struct Mfield.reduce %lud\n", offsetof(struct Mfield, reduce));
	exits(nil);
}
