#include <u.h>
#include <libc.h>
#include <draw.h>
#include <scribble.h>

void
main(void)
{
	print("struct pen_point %d\n", sizeof(struct pen_point));
	print("struct pen_point.chaincode %lud\n", offsetof(struct pen_point, chaincode));
	print("struct Stroke %d\n", sizeof(struct Stroke));
	print("struct Stroke.npts %lud\n", offsetof(struct Stroke, npts));
	print("struct Stroke.pts %lud\n", offsetof(struct Stroke, pts));
	print("struct Scribble %d\n", sizeof(struct Scribble));
	print("struct Scribble.pt %lud\n", offsetof(struct Scribble, pt));
	print("struct Scribble.ppasize %lud\n", offsetof(struct Scribble, ppasize));
	print("struct Scribble.ps %lud\n", offsetof(struct Scribble, ps));
	print("struct Scribble.graf %lud\n", offsetof(struct Scribble, graf));
	print("struct Scribble.capsLock %lud\n", offsetof(struct Scribble, capsLock));
	print("struct Scribble.puncShift %lud\n", offsetof(struct Scribble, puncShift));
	print("struct Scribble.tmpShift %lud\n", offsetof(struct Scribble, tmpShift));
	print("struct Scribble.ctrlShift %lud\n", offsetof(struct Scribble, ctrlShift));
	print("struct Scribble.curCharSet %lud\n", offsetof(struct Scribble, curCharSet));
	exits(nil);
}
