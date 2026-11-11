#include <u.h>
#include <libc.h>
#include <fcall.h>

void
main(void)
{
	print("struct Fcall %d\n", sizeof(struct Fcall));
	print("struct Fcall.type %lud\n", offsetof(struct Fcall, type));
	print("struct Fcall.fid %lud\n", offsetof(struct Fcall, fid));
	print("struct Fcall.tag %lud\n", offsetof(struct Fcall, tag));
	print("struct Fcall.msize %lud\n", offsetof(struct Fcall, msize));
	print("struct Fcall.version %lud\n", offsetof(struct Fcall, version));
	print("struct Fcall.oldtag %lud\n", offsetof(struct Fcall, oldtag));
	print("struct Fcall.ename %lud\n", offsetof(struct Fcall, ename));
	print("struct Fcall.qid %lud\n", offsetof(struct Fcall, qid));
	print("struct Fcall.iounit %lud\n", offsetof(struct Fcall, iounit));
	print("struct Fcall.aqid %lud\n", offsetof(struct Fcall, aqid));
	print("struct Fcall.afid %lud\n", offsetof(struct Fcall, afid));
	print("struct Fcall.uname %lud\n", offsetof(struct Fcall, uname));
	print("struct Fcall.aname %lud\n", offsetof(struct Fcall, aname));
	print("struct Fcall.perm %lud\n", offsetof(struct Fcall, perm));
	print("struct Fcall.name %lud\n", offsetof(struct Fcall, name));
	print("struct Fcall.mode %lud\n", offsetof(struct Fcall, mode));
	print("struct Fcall.newfid %lud\n", offsetof(struct Fcall, newfid));
	print("struct Fcall.nwname %lud\n", offsetof(struct Fcall, nwname));
	print("struct Fcall.wname %lud\n", offsetof(struct Fcall, wname));
	print("struct Fcall.nwqid %lud\n", offsetof(struct Fcall, nwqid));
	print("struct Fcall.wqid %lud\n", offsetof(struct Fcall, wqid));
	print("struct Fcall.offset %lud\n", offsetof(struct Fcall, offset));
	print("struct Fcall.count %lud\n", offsetof(struct Fcall, count));
	print("struct Fcall.data %lud\n", offsetof(struct Fcall, data));
	print("struct Fcall.nstat %lud\n", offsetof(struct Fcall, nstat));
	print("struct Fcall.stat %lud\n", offsetof(struct Fcall, stat));
	exits(nil);
}
