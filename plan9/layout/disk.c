#include <u.h>
#include <libc.h>
#include <disk.h>

void
main(void)
{
	print("struct Scsi %d\n", sizeof(struct Scsi));
	print("struct Scsi.inquire %lud\n", offsetof(struct Scsi, inquire));
	print("struct Scsi.rawfd %lud\n", offsetof(struct Scsi, rawfd));
	print("struct Scsi.nchange %lud\n", offsetof(struct Scsi, nchange));
	print("struct Scsi.changetime %lud\n", offsetof(struct Scsi, changetime));
	print("struct Disk %d\n", sizeof(struct Disk));
	print("struct Disk.prefix %lud\n", offsetof(struct Disk, prefix));
	print("struct Disk.part %lud\n", offsetof(struct Disk, part));
	print("struct Disk.fd %lud\n", offsetof(struct Disk, fd));
	print("struct Disk.wfd %lud\n", offsetof(struct Disk, wfd));
	print("struct Disk.ctlfd %lud\n", offsetof(struct Disk, ctlfd));
	print("struct Disk.rdonly %lud\n", offsetof(struct Disk, rdonly));
	print("struct Disk.type %lud\n", offsetof(struct Disk, type));
	print("struct Disk.secs %lud\n", offsetof(struct Disk, secs));
	print("struct Disk.secsize %lud\n", offsetof(struct Disk, secsize));
	print("struct Disk.size %lud\n", offsetof(struct Disk, size));
	print("struct Disk.offset %lud\n", offsetof(struct Disk, offset));
	print("struct Disk.width %lud\n", offsetof(struct Disk, width));
	print("struct Disk.psecsize %lud\n", offsetof(struct Disk, psecsize));
	print("struct Disk.physalign %lud\n", offsetof(struct Disk, physalign));
	print("struct Disk.c %lud\n", offsetof(struct Disk, c));
	print("struct Disk.h %lud\n", offsetof(struct Disk, h));
	print("struct Disk.s %lud\n", offsetof(struct Disk, s));
	print("struct Disk.chssrc %lud\n", offsetof(struct Disk, chssrc));
	exits(nil);
}
