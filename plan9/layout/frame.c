#include <u.h>
#include <libc.h>
#include <draw.h>
#include <mouse.h>
#include <frame.h>

void
main(void)
{
	print("struct Frbox %d\n", sizeof(struct Frbox));
	print("struct Frbox.wid %lud\n", offsetof(struct Frbox, wid));
	print("struct Frbox.nrune %lud\n", offsetof(struct Frbox, nrune));
	print("struct Frbox.ptr %lud\n", offsetof(struct Frbox, ptr));
	print("struct Frbox.bc %lud\n", offsetof(struct Frbox, bc));
	print("struct Frbox.minwid %lud\n", offsetof(struct Frbox, minwid));
	print("struct Frame %d\n", sizeof(struct Frame));
	print("struct Frame.font %lud\n", offsetof(struct Frame, font));
	print("struct Frame.display %lud\n", offsetof(struct Frame, display));
	print("struct Frame.b %lud\n", offsetof(struct Frame, b));
	print("struct Frame.cols %lud\n", offsetof(struct Frame, cols));
	print("struct Frame.r %lud\n", offsetof(struct Frame, r));
	print("struct Frame.entire %lud\n", offsetof(struct Frame, entire));
	print("struct Frame.scroll %lud\n", offsetof(struct Frame, scroll));
	print("struct Frame.box %lud\n", offsetof(struct Frame, box));
	print("struct Frame.p0 %lud\n", offsetof(struct Frame, p0));
	print("struct Frame.p1 %lud\n", offsetof(struct Frame, p1));
	print("struct Frame.nbox %lud\n", offsetof(struct Frame, nbox));
	print("struct Frame.nalloc %lud\n", offsetof(struct Frame, nalloc));
	print("struct Frame.maxtab %lud\n", offsetof(struct Frame, maxtab));
	print("struct Frame.nchars %lud\n", offsetof(struct Frame, nchars));
	print("struct Frame.nlines %lud\n", offsetof(struct Frame, nlines));
	print("struct Frame.maxlines %lud\n", offsetof(struct Frame, maxlines));
	print("struct Frame.lastlinefull %lud\n", offsetof(struct Frame, lastlinefull));
	print("struct Frame.modified %lud\n", offsetof(struct Frame, modified));
	print("struct Frame.tick %lud\n", offsetof(struct Frame, tick));
	print("struct Frame.tickback %lud\n", offsetof(struct Frame, tickback));
	print("struct Frame.ticked %lud\n", offsetof(struct Frame, ticked));
	exits(nil);
}
