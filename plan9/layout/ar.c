#include <u.h>
#include <libc.h>
#include <ar.h>

void
main(void)
{
	print("struct ar_hdr %d\n", sizeof(struct ar_hdr));
	print("struct ar_hdr.name %lud\n", offsetof(struct ar_hdr, name));
	print("struct ar_hdr.date %lud\n", offsetof(struct ar_hdr, date));
	print("struct ar_hdr.uid %lud\n", offsetof(struct ar_hdr, uid));
	print("struct ar_hdr.gid %lud\n", offsetof(struct ar_hdr, gid));
	print("struct ar_hdr.mode %lud\n", offsetof(struct ar_hdr, mode));
	print("struct ar_hdr.size %lud\n", offsetof(struct ar_hdr, size));
	print("struct ar_hdr.fmag %lud\n", offsetof(struct ar_hdr, fmag));
	exits(nil);
}
