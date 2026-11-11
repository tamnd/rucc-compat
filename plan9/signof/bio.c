#include <u.h>
#include <libc.h>
#include <bio.h>

void
main(void)
{
	print("Bstr %.8lux\n", signof(Bstr));
	print("Biobuf %.8lux\n", signof(Biobuf));
	print("Biobufhdr %.8lux\n", signof(Biobufhdr));
	print("struct Biobufhdr %.8lux\n", signof(struct Biobufhdr));
	print("struct Biobuf %.8lux\n", signof(struct Biobuf));
	print("struct Bstr %.8lux\n", signof(struct Bstr));
	print("Bbuffered %.8lux\n", signof Bbuffered);
	print("Bfildes %.8lux\n", signof Bfildes);
	print("Bflush %.8lux\n", signof Bflush);
	print("Bgetc %.8lux\n", signof Bgetc);
	print("Bgetd %.8lux\n", signof Bgetd);
	print("Bgetrune %.8lux\n", signof Bgetrune);
	print("Binit %.8lux\n", signof Binit);
	print("Binits %.8lux\n", signof Binits);
	print("Blinelen %.8lux\n", signof Blinelen);
	print("Boffset %.8lux\n", signof Boffset);
	print("Bopen %.8lux\n", signof Bopen);
	print("Bfdopen %.8lux\n", signof Bfdopen);
	print("Bstropen %.8lux\n", signof Bstropen);
	print("Bprint %.8lux\n", signof Bprint);
	print("Bvprint %.8lux\n", signof Bvprint);
	print("Bputc %.8lux\n", signof Bputc);
	print("Bputrune %.8lux\n", signof Bputrune);
	print("Brdline %.8lux\n", signof Brdline);
	print("Brdstr %.8lux\n", signof Brdstr);
	print("Bread %.8lux\n", signof Bread);
	print("Bseek %.8lux\n", signof Bseek);
	print("Bterm %.8lux\n", signof Bterm);
	print("Bungetc %.8lux\n", signof Bungetc);
	print("Bungetrune %.8lux\n", signof Bungetrune);
	print("Bwrite %.8lux\n", signof Bwrite);
	print("Blethal %.8lux\n", signof Blethal);
	print("Berror %.8lux\n", signof Berror);
	print("Biofn %.8lux\n", signof Biofn);
	exits(nil);
}
