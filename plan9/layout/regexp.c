#include <u.h>
#include <libc.h>
#include <regexp.h>

void
main(void)
{
	print("struct Resub %d\n", sizeof(struct Resub));
	print("struct Resub.sp %lud\n", offsetof(struct Resub, sp));
	print("struct Resub.rsp %lud\n", offsetof(struct Resub, rsp));
	print("struct Resub.ep %lud\n", offsetof(struct Resub, ep));
	print("struct Resub.rep %lud\n", offsetof(struct Resub, rep));
	print("struct Reprog %d\n", sizeof(struct Reprog));
	print("struct Reprog.startinst %lud\n", offsetof(struct Reprog, startinst));
	print("struct Reprog.threads %lud\n", offsetof(struct Reprog, threads));
	print("struct Reprog.regstr %lud\n", offsetof(struct Reprog, regstr));
	print("struct Reprog.len %lud\n", offsetof(struct Reprog, len));
	print("struct Reprog.nthr %lud\n", offsetof(struct Reprog, nthr));
	exits(nil);
}
