#include <u.h>
#include <libc.h>

void
main(void)
{
	print("union FPdbleword %d\n", sizeof(union FPdbleword));
	print("union FPdbleword.x %lud\n", offsetof(union FPdbleword, x));
	print("union FPdbleword.lo %lud\n", offsetof(union FPdbleword, lo));
	print("union FPdbleword.hi %lud\n", offsetof(union FPdbleword, hi));
	exits(nil);
}
