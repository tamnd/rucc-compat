#include <u.h>
#include <libc.h>
#include <draw.h>
#include <mouse.h>

void
main(void)
{
	print("Menu %.8lux\n", signof(Menu));
	print("Mousectl %.8lux\n", signof(Mousectl));
	print("struct Mouse %.8lux\n", signof(struct Mouse));
	print("struct Mousectl %.8lux\n", signof(struct Mousectl));
	print("struct Menu %.8lux\n", signof(struct Menu));
	print("initmouse %.8lux\n", signof initmouse);
	print("moveto %.8lux\n", signof moveto);
	print("readmouse %.8lux\n", signof readmouse);
	print("closemouse %.8lux\n", signof closemouse);
	print("setcursor %.8lux\n", signof setcursor);
	print("drawgetrect %.8lux\n", signof drawgetrect);
	print("getrect %.8lux\n", signof getrect);
	print("menuhit %.8lux\n", signof menuhit);
	print("enter %.8lux\n", signof enter);
	exits(nil);
}
