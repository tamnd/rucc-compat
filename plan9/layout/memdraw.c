#include <u.h>
#include <libc.h>
#include <draw.h>
#include <memdraw.h>

void
main(void)
{
	print("struct Memdata %d\n", sizeof(struct Memdata));
	print("struct Memdata.base %lud\n", offsetof(struct Memdata, base));
	print("struct Memdata.bdata %lud\n", offsetof(struct Memdata, bdata));
	print("struct Memdata.ref %lud\n", offsetof(struct Memdata, ref));
	print("struct Memdata.imref %lud\n", offsetof(struct Memdata, imref));
	print("struct Memdata.allocd %lud\n", offsetof(struct Memdata, allocd));
	print("struct Memimage %d\n", sizeof(struct Memimage));
	print("struct Memimage.r %lud\n", offsetof(struct Memimage, r));
	print("struct Memimage.clipr %lud\n", offsetof(struct Memimage, clipr));
	print("struct Memimage.depth %lud\n", offsetof(struct Memimage, depth));
	print("struct Memimage.nchan %lud\n", offsetof(struct Memimage, nchan));
	print("struct Memimage.chan %lud\n", offsetof(struct Memimage, chan));
	print("struct Memimage.cmap %lud\n", offsetof(struct Memimage, cmap));
	print("struct Memimage.data %lud\n", offsetof(struct Memimage, data));
	print("struct Memimage.zero %lud\n", offsetof(struct Memimage, zero));
	print("struct Memimage.width %lud\n", offsetof(struct Memimage, width));
	print("struct Memimage.layer %lud\n", offsetof(struct Memimage, layer));
	print("struct Memimage.flags %lud\n", offsetof(struct Memimage, flags));
	print("struct Memimage.shift %lud\n", offsetof(struct Memimage, shift));
	print("struct Memimage.mask %lud\n", offsetof(struct Memimage, mask));
	print("struct Memimage.nbits %lud\n", offsetof(struct Memimage, nbits));
	print("struct Memcmap %d\n", sizeof(struct Memcmap));
	print("struct Memcmap.cmap2rgb %lud\n", offsetof(struct Memcmap, cmap2rgb));
	print("struct Memcmap.rgb2cmap %lud\n", offsetof(struct Memcmap, rgb2cmap));
	print("struct Memsubfont %d\n", sizeof(struct Memsubfont));
	print("struct Memsubfont.name %lud\n", offsetof(struct Memsubfont, name));
	print("struct Memsubfont.n %lud\n", offsetof(struct Memsubfont, n));
	print("struct Memsubfont.height %lud\n", offsetof(struct Memsubfont, height));
	print("struct Memsubfont.ascent %lud\n", offsetof(struct Memsubfont, ascent));
	print("struct Memsubfont.min %lud\n", offsetof(struct Memsubfont, min));
	print("struct Memsubfont.info %lud\n", offsetof(struct Memsubfont, info));
	print("struct Memsubfont.bits %lud\n", offsetof(struct Memsubfont, bits));
	print("struct Memdrawparam %d\n", sizeof(struct Memdrawparam));
	print("struct Memdrawparam.dst %lud\n", offsetof(struct Memdrawparam, dst));
	print("struct Memdrawparam.r %lud\n", offsetof(struct Memdrawparam, r));
	print("struct Memdrawparam.src %lud\n", offsetof(struct Memdrawparam, src));
	print("struct Memdrawparam.sr %lud\n", offsetof(struct Memdrawparam, sr));
	print("struct Memdrawparam.mask %lud\n", offsetof(struct Memdrawparam, mask));
	print("struct Memdrawparam.mr %lud\n", offsetof(struct Memdrawparam, mr));
	print("struct Memdrawparam.op %lud\n", offsetof(struct Memdrawparam, op));
	print("struct Memdrawparam.state %lud\n", offsetof(struct Memdrawparam, state));
	print("struct Memdrawparam.mval %lud\n", offsetof(struct Memdrawparam, mval));
	print("struct Memdrawparam.mrgba %lud\n", offsetof(struct Memdrawparam, mrgba));
	print("struct Memdrawparam.sval %lud\n", offsetof(struct Memdrawparam, sval));
	print("struct Memdrawparam.srgba %lud\n", offsetof(struct Memdrawparam, srgba));
	print("struct Memdrawparam.sdval %lud\n", offsetof(struct Memdrawparam, sdval));
	exits(nil);
}
