#include <u.h>
#include <libc.h>
#include <disk.h>

void
main(void)
{
	print("Scsi %.8lux\n", signof(Scsi));
	print("Disk %.8lux\n", signof(Disk));
	print("struct Scsi %.8lux\n", signof(struct Scsi));
	print("struct Disk %.8lux\n", signof(struct Disk));
	print("scsierror %.8lux\n", signof scsierror);
	print("scsicmd %.8lux\n", signof scsicmd);
	print("scsi %.8lux\n", signof scsi);
	print("openscsi %.8lux\n", signof openscsi);
	print("closescsi %.8lux\n", signof closescsi);
	print("scsiready %.8lux\n", signof scsiready);
	print("scsiverbose %.8lux\n", signof scsiverbose);
	print("opendisk %.8lux\n", signof opendisk);
	print("rdproto %.8lux\n", signof rdproto);
	exits(nil);
}
