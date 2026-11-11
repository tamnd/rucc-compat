#include <u.h>
#include <libc.h>
#include <fis.h>

void
main(void)
{
	print("struct Sfis %d\n", sizeof(struct Sfis));
	print("struct Sfis.feat %lud\n", offsetof(struct Sfis, feat));
	print("struct Sfis.udma %lud\n", offsetof(struct Sfis, udma));
	print("struct Sfis.speeds %lud\n", offsetof(struct Sfis, speeds));
	print("struct Sfis.sig %lud\n", offsetof(struct Sfis, sig));
	print("struct Sfis.lsectsz %lud\n", offsetof(struct Sfis, lsectsz));
	print("struct Sfis.physshift %lud\n", offsetof(struct Sfis, physshift));
	print("struct Sfis.physalign %lud\n", offsetof(struct Sfis, physalign));
	print("struct Sfis.c %lud\n", offsetof(struct Sfis, c));
	print("struct Sfis.h %lud\n", offsetof(struct Sfis, h));
	print("struct Sfis.s %lud\n", offsetof(struct Sfis, s));
	print("struct Cfis %d\n", sizeof(struct Cfis));
	print("struct Cfis.phyid %lud\n", offsetof(struct Cfis, phyid));
	print("struct Cfis.encid %lud\n", offsetof(struct Cfis, encid));
	print("struct Cfis.tsasaddr %lud\n", offsetof(struct Cfis, tsasaddr));
	print("struct Cfis.ssasaddr %lud\n", offsetof(struct Cfis, ssasaddr));
	print("struct Cfis.ict %lud\n", offsetof(struct Cfis, ict));
	exits(nil);
}
