#include <u.h>
#include <libc.h>
#include <draw.h>
#include <html.h>

void
main(void)
{
	print("Item %.8lux\n", signof(Item));
	print("Itext %.8lux\n", signof(Itext));
	print("Irule %.8lux\n", signof(Irule));
	print("Iimage %.8lux\n", signof(Iimage));
	print("Iformfield %.8lux\n", signof(Iformfield));
	print("Itable %.8lux\n", signof(Itable));
	print("Ifloat %.8lux\n", signof(Ifloat));
	print("Ispacer %.8lux\n", signof(Ispacer));
	print("Genattr %.8lux\n", signof(Genattr));
	print("SEvent %.8lux\n", signof(SEvent));
	print("Formfield %.8lux\n", signof(Formfield));
	print("Option %.8lux\n", signof(Option));
	print("Form %.8lux\n", signof(Form));
	print("Table %.8lux\n", signof(Table));
	print("Tablecol %.8lux\n", signof(Tablecol));
	print("Tablerow %.8lux\n", signof(Tablerow));
	print("Tablecell %.8lux\n", signof(Tablecell));
	print("Align %.8lux\n", signof(Align));
	print("Dimen %.8lux\n", signof(Dimen));
	print("Anchor %.8lux\n", signof(Anchor));
	print("DestAnchor %.8lux\n", signof(DestAnchor));
	print("Map %.8lux\n", signof(Map));
	print("Area %.8lux\n", signof(Area));
	print("Background %.8lux\n", signof(Background));
	print("Kidinfo %.8lux\n", signof(Kidinfo));
	print("Docinfo %.8lux\n", signof(Docinfo));
	print("struct Align %.8lux\n", signof(struct Align));
	print("struct Dimen %.8lux\n", signof(struct Dimen));
	print("struct Background %.8lux\n", signof(struct Background));
	print("struct Item %.8lux\n", signof(struct Item));
	print("struct Itext %.8lux\n", signof(struct Itext));
	print("struct Irule %.8lux\n", signof(struct Irule));
	print("struct Iimage %.8lux\n", signof(struct Iimage));
	print("struct Iformfield %.8lux\n", signof(struct Iformfield));
	print("struct Itable %.8lux\n", signof(struct Itable));
	print("struct Ifloat %.8lux\n", signof(struct Ifloat));
	print("struct Ispacer %.8lux\n", signof(struct Ispacer));
	print("struct Genattr %.8lux\n", signof(struct Genattr));
	print("struct SEvent %.8lux\n", signof(struct SEvent));
	print("struct Formfield %.8lux\n", signof(struct Formfield));
	print("struct Option %.8lux\n", signof(struct Option));
	print("struct Form %.8lux\n", signof(struct Form));
	print("struct Table %.8lux\n", signof(struct Table));
	print("struct Tablecol %.8lux\n", signof(struct Tablecol));
	print("struct Tablerow %.8lux\n", signof(struct Tablerow));
	print("struct Tablecell %.8lux\n", signof(struct Tablecell));
	print("struct Anchor %.8lux\n", signof(struct Anchor));
	print("struct DestAnchor %.8lux\n", signof(struct DestAnchor));
	print("struct Map %.8lux\n", signof(struct Map));
	print("struct Area %.8lux\n", signof(struct Area));
	print("struct Kidinfo %.8lux\n", signof(struct Kidinfo));
	print("struct Docinfo %.8lux\n", signof(struct Docinfo));
	print("fromStr %.8lux\n", signof fromStr);
	print("toStr %.8lux\n", signof toStr);
	print("dimenkind %.8lux\n", signof dimenkind);
	print("dimenspec %.8lux\n", signof dimenspec);
	print("freedocinfo %.8lux\n", signof freedocinfo);
	print("freeitems %.8lux\n", signof freeitems);
	print("parsehtml %.8lux\n", signof parsehtml);
	print("printitems %.8lux\n", signof printitems);
	print("targetid %.8lux\n", signof targetid);
	print("targetname %.8lux\n", signof targetname);
	print("validitems %.8lux\n", signof validitems);
	print("warn %.8lux\n", signof warn);
	print("dbglex %.8lux\n", signof dbglex);
	print("dbgbuild %.8lux\n", signof dbgbuild);
	print("emalloc %.8lux\n", signof emalloc);
	print("erealloc %.8lux\n", signof erealloc);
	exits(nil);
}
