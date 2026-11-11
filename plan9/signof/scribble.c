#include <u.h>
#include <libc.h>
#include <draw.h>
#include <scribble.h>

void
main(void)
{
	print("Scribble %.8lux\n", signof(Scribble));
	print("pen_point %.8lux\n", signof(pen_point));
	print("Stroke %.8lux\n", signof(Stroke));
	print("struct pen_point %.8lux\n", signof(struct pen_point));
	print("struct Stroke %.8lux\n", signof(struct Stroke));
	print("struct Scribble %.8lux\n", signof(struct Scribble));
	print("recognize %.8lux\n", signof recognize);
	print("scribblealloc %.8lux\n", signof scribblealloc);
	print("ScribbleDebug %.8lux\n", signof ScribbleDebug);
	exits(nil);
}
