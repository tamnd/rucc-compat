#include <u.h>
#include <libc.h>
#include <draw.h>
#include <memdraw.h>

void
main(void)
{
	print("Memimage %.8lux\n", signof(Memimage));
	print("Memdata %.8lux\n", signof(Memdata));
	print("Memsubfont %.8lux\n", signof(Memsubfont));
	print("Memcmap %.8lux\n", signof(Memcmap));
	print("Memdrawparam %.8lux\n", signof(Memdrawparam));
	print("struct Memdata %.8lux\n", signof(struct Memdata));
	print("struct Memimage %.8lux\n", signof(struct Memimage));
	print("struct Memcmap %.8lux\n", signof(struct Memcmap));
	print("struct Memsubfont %.8lux\n", signof(struct Memsubfont));
	print("struct Memdrawparam %.8lux\n", signof(struct Memdrawparam));
	print("allocmemimage %.8lux\n", signof allocmemimage);
	print("allocmemimaged %.8lux\n", signof allocmemimaged);
	print("readmemimage %.8lux\n", signof readmemimage);
	print("creadmemimage %.8lux\n", signof creadmemimage);
	print("writememimage %.8lux\n", signof writememimage);
	print("freememimage %.8lux\n", signof freememimage);
	print("loadmemimage %.8lux\n", signof loadmemimage);
	print("cloadmemimage %.8lux\n", signof cloadmemimage);
	print("unloadmemimage %.8lux\n", signof unloadmemimage);
	print("wordaddr %.8lux\n", signof wordaddr);
	print("byteaddr %.8lux\n", signof byteaddr);
	print("_drawclipnorepl %.8lux\n", signof _drawclipnorepl);
	print("drawclipnorepl %.8lux\n", signof drawclipnorepl);
	print("drawclip %.8lux\n", signof drawclip);
	print("memfillcolor %.8lux\n", signof memfillcolor);
	print("memsetchan %.8lux\n", signof memsetchan);
	print("memdraw %.8lux\n", signof memdraw);
	print("memline %.8lux\n", signof memline);
	print("mempoly %.8lux\n", signof mempoly);
	print("memfillpoly %.8lux\n", signof memfillpoly);
	print("_memfillpolysc %.8lux\n", signof _memfillpolysc);
	print("memimagedraw %.8lux\n", signof memimagedraw);
	print("hwdraw %.8lux\n", signof hwdraw);
	print("memimageline %.8lux\n", signof memimageline);
	print("_memimageline %.8lux\n", signof _memimageline);
	print("memimagestring %.8lux\n", signof memimagestring);
	print("memellipse %.8lux\n", signof memellipse);
	print("memarc %.8lux\n", signof memarc);
	print("memlinebbox %.8lux\n", signof memlinebbox);
	print("memlineendsize %.8lux\n", signof memlineendsize);
	print("memaffinewarp %.8lux\n", signof memaffinewarp);
	print("memlaffinewarp %.8lux\n", signof memlaffinewarp);
	print("allocmemimagekernel %.8lux\n", signof allocmemimagekernel);
	print("memimagecorrelate %.8lux\n", signof memimagecorrelate);
	print("_memmkcmap %.8lux\n", signof _memmkcmap);
	print("memimageinit %.8lux\n", signof memimageinit);
	print("allocmemsubfont %.8lux\n", signof allocmemsubfont);
	print("openmemsubfont %.8lux\n", signof openmemsubfont);
	print("freememsubfont %.8lux\n", signof freememsubfont);
	print("memsubfontwidth %.8lux\n", signof memsubfontwidth);
	print("getmemdefont %.8lux\n", signof getmemdefont);
	print("memwhite %.8lux\n", signof memwhite);
	print("memblack %.8lux\n", signof memblack);
	print("memopaque %.8lux\n", signof memopaque);
	print("memtransparent %.8lux\n", signof memtransparent);
	print("memdefcmap %.8lux\n", signof memdefcmap);
	print("memimagemove %.8lux\n", signof memimagemove);
	exits(nil);
}
