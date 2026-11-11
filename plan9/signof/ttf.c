#include <u.h>
#include <libc.h>
#include <ttf.h>

void
main(void)
{
	print("TTTable %.8lux\n", signof(TTTable));
	print("TTChMap %.8lux\n", signof(TTChMap));
	print("TTPoint %.8lux\n", signof(TTPoint));
	print("TTGlyph %.8lux\n", signof(TTGlyph));
	print("TTGlyphInfo %.8lux\n", signof(TTGlyphInfo));
	print("TTFontU %.8lux\n", signof(TTFontU));
	print("TTFont %.8lux\n", signof(TTFont));
	print("TTFunction %.8lux\n", signof(TTFunction));
	print("TTGState %.8lux\n", signof(TTGState));
	print("TTBitmap %.8lux\n", signof(TTBitmap));
	print("TTKern %.8lux\n", signof(TTKern));
	print("struct TTTable %.8lux\n", signof(struct TTTable));
	print("struct TTChMap %.8lux\n", signof(struct TTChMap));
	print("struct TTPoint %.8lux\n", signof(struct TTPoint));
	print("struct TTBitmap %.8lux\n", signof(struct TTBitmap));
	print("struct TTGlyph %.8lux\n", signof(struct TTGlyph));
	print("struct TTGlyphInfo %.8lux\n", signof(struct TTGlyphInfo));
	print("struct TTFunction %.8lux\n", signof(struct TTFunction));
	print("struct TTGState %.8lux\n", signof(struct TTGState));
	print("struct TTKern %.8lux\n", signof(struct TTKern));
	print("struct TTFontU %.8lux\n", signof(struct TTFontU));
	print("struct TTFont %.8lux\n", signof(struct TTFont));
	print("ttfopen %.8lux\n", signof ttfopen);
	print("ttfscale %.8lux\n", signof ttfscale);
	print("ttfclose %.8lux\n", signof ttfclose);
	print("ttffindchar %.8lux\n", signof ttffindchar);
	print("ttfenumchar %.8lux\n", signof ttfenumchar);
	print("ttfgetglyph %.8lux\n", signof ttfgetglyph);
	print("ttfputglyph %.8lux\n", signof ttfputglyph);
	print("ttfgetcontour %.8lux\n", signof ttfgetcontour);
	print("ttfrender %.8lux\n", signof ttfrender);
	print("ttfrunerender %.8lux\n", signof ttfrunerender);
	print("ttfnewbitmap %.8lux\n", signof ttfnewbitmap);
	print("ttffreebitmap %.8lux\n", signof ttffreebitmap);
	print("ttfblit %.8lux\n", signof ttfblit);
	exits(nil);
}
