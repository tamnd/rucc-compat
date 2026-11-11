#include <u.h>
#include <libc.h>
#include <draw.h>
#include <event.h>

void
main(void)
{
	print("Event %.8lux\n", signof(Event));
	print("Menu %.8lux\n", signof(Menu));
	print("struct Mouse %.8lux\n", signof(struct Mouse));
	print("struct Event %.8lux\n", signof(struct Event));
	print("struct Menu %.8lux\n", signof(struct Menu));
	print("einit %.8lux\n", signof einit);
	print("estart %.8lux\n", signof estart);
	print("estartfn %.8lux\n", signof estartfn);
	print("etimer %.8lux\n", signof etimer);
	print("event %.8lux\n", signof event);
	print("eread %.8lux\n", signof eread);
	print("emouse %.8lux\n", signof emouse);
	print("ekbd %.8lux\n", signof ekbd);
	print("ecanread %.8lux\n", signof ecanread);
	print("ecanmouse %.8lux\n", signof ecanmouse);
	print("ecankbd %.8lux\n", signof ecankbd);
	print("eresized %.8lux\n", signof eresized);
	print("emenuhit %.8lux\n", signof emenuhit);
	print("eatomouse %.8lux\n", signof eatomouse);
	print("getrect %.8lux\n", signof getrect);
	print("esetcursor %.8lux\n", signof esetcursor);
	print("emoveto %.8lux\n", signof emoveto);
	print("egetrect %.8lux\n", signof egetrect);
	print("edrawgetrect %.8lux\n", signof edrawgetrect);
	print("ereadmouse %.8lux\n", signof ereadmouse);
	print("eenter %.8lux\n", signof eenter);
	exits(nil);
}
