#include <u.h>
#include <libc.h>
#include <bio.h>

void
main(void)
{
	print("struct Biobufhdr %d\n", sizeof(struct Biobufhdr));
	print("struct Biobufhdr.icount %lud\n", offsetof(struct Biobufhdr, icount));
	print("struct Biobufhdr.ocount %lud\n", offsetof(struct Biobufhdr, ocount));
	print("struct Biobufhdr.rdline %lud\n", offsetof(struct Biobufhdr, rdline));
	print("struct Biobufhdr.runesize %lud\n", offsetof(struct Biobufhdr, runesize));
	print("struct Biobufhdr.state %lud\n", offsetof(struct Biobufhdr, state));
	print("struct Biobufhdr.fid %lud\n", offsetof(struct Biobufhdr, fid));
	print("struct Biobufhdr.flag %lud\n", offsetof(struct Biobufhdr, flag));
	print("struct Biobufhdr.offset %lud\n", offsetof(struct Biobufhdr, offset));
	print("struct Biobufhdr.bsize %lud\n", offsetof(struct Biobufhdr, bsize));
	print("struct Biobufhdr.bbuf %lud\n", offsetof(struct Biobufhdr, bbuf));
	print("struct Biobufhdr.ebuf %lud\n", offsetof(struct Biobufhdr, ebuf));
	print("struct Biobufhdr.gbuf %lud\n", offsetof(struct Biobufhdr, gbuf));
	print("struct Biobufhdr.errorf %lud\n", offsetof(struct Biobufhdr, errorf));
	print("struct Biobufhdr.iof %lud\n", offsetof(struct Biobufhdr, iof));
	print("struct Biobufhdr.aux %lud\n", offsetof(struct Biobufhdr, aux));
	print("struct Biobuf %d\n", sizeof(struct Biobuf));
	print("struct Biobuf.b %lud\n", offsetof(struct Biobuf, b));
	print("struct Bstr %d\n", sizeof(struct Bstr));
	print("struct Bstr.b %lud\n", offsetof(struct Bstr, b));
	exits(nil);
}
