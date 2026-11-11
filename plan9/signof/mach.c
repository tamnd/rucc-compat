#include <u.h>
#include <libc.h>
#include <bio.h>
#include <mach.h>

void
main(void)
{
	print("Map %.8lux\n", signof(Map));
	print("Symbol %.8lux\n", signof(Symbol));
	print("Reglist %.8lux\n", signof(Reglist));
	print("Mach %.8lux\n", signof(Mach));
	print("Machdata %.8lux\n", signof(Machdata));
	print("Rgetter %.8lux\n", signof(Rgetter));
	print("Tracer %.8lux\n", signof(Tracer));
	print("Fhdr %.8lux\n", signof(Fhdr));
	print("struct Map %.8lux\n", signof(struct Map));
	print("struct segment %.8lux\n", signof(struct segment));
	print("struct Symbol %.8lux\n", signof(struct Symbol));
	print("struct Reglist %.8lux\n", signof(struct Reglist));
	print("struct Mach %.8lux\n", signof(struct Mach));
	print("struct Machdata %.8lux\n", signof(struct Machdata));
	print("struct Fhdr %.8lux\n", signof(struct Fhdr));
	print("mach %.8lux\n", signof mach);
	print("asstype %.8lux\n", signof asstype);
	print("machdata %.8lux\n", signof machdata);
	print("attachproc %.8lux\n", signof attachproc);
	print("beieee80ftos %.8lux\n", signof beieee80ftos);
	print("beieeesftos %.8lux\n", signof beieeesftos);
	print("beieeedftos %.8lux\n", signof beieeedftos);
	print("beswab %.8lux\n", signof beswab);
	print("beswal %.8lux\n", signof beswal);
	print("beswav %.8lux\n", signof beswav);
	print("ciscframe %.8lux\n", signof ciscframe);
	print("cisctrace %.8lux\n", signof cisctrace);
	print("crackhdr %.8lux\n", signof crackhdr);
	print("file2pc %.8lux\n", signof file2pc);
	print("fileelem %.8lux\n", signof fileelem);
	print("fileline %.8lux\n", signof fileline);
	print("filesym %.8lux\n", signof filesym);
	print("findlocal %.8lux\n", signof findlocal);
	print("findseg %.8lux\n", signof findseg);
	print("findsym %.8lux\n", signof findsym);
	print("fnbound %.8lux\n", signof fnbound);
	print("fpformat %.8lux\n", signof fpformat);
	print("get1 %.8lux\n", signof get1);
	print("get2 %.8lux\n", signof get2);
	print("get4 %.8lux\n", signof get4);
	print("get8 %.8lux\n", signof get8);
	print("geta %.8lux\n", signof geta);
	print("getauto %.8lux\n", signof getauto);
	print("getsym %.8lux\n", signof getsym);
	print("globalsym %.8lux\n", signof globalsym);
	print("_hexify %.8lux\n", signof _hexify);
	print("ieeesftos %.8lux\n", signof ieeesftos);
	print("ieeedftos %.8lux\n", signof ieeedftos);
	print("isar %.8lux\n", signof isar);
	print("leieee80ftos %.8lux\n", signof leieee80ftos);
	print("leieeesftos %.8lux\n", signof leieeesftos);
	print("leieeedftos %.8lux\n", signof leieeedftos);
	print("leswab %.8lux\n", signof leswab);
	print("leswal %.8lux\n", signof leswal);
	print("leswav %.8lux\n", signof leswav);
	print("line2addr %.8lux\n", signof line2addr);
	print("loadmap %.8lux\n", signof loadmap);
	print("localaddr %.8lux\n", signof localaddr);
	print("localsym %.8lux\n", signof localsym);
	print("lookup %.8lux\n", signof lookup);
	print("machbytype %.8lux\n", signof machbytype);
	print("machbyname %.8lux\n", signof machbyname);
	print("nextar %.8lux\n", signof nextar);
	print("newmap %.8lux\n", signof newmap);
	print("objtraverse %.8lux\n", signof objtraverse);
	print("objtype %.8lux\n", signof objtype);
	print("pc2sp %.8lux\n", signof pc2sp);
	print("pc2line %.8lux\n", signof pc2line);
	print("put1 %.8lux\n", signof put1);
	print("put2 %.8lux\n", signof put2);
	print("put4 %.8lux\n", signof put4);
	print("put8 %.8lux\n", signof put8);
	print("puta %.8lux\n", signof puta);
	print("readar %.8lux\n", signof readar);
	print("readobj %.8lux\n", signof readobj);
	print("riscframe %.8lux\n", signof riscframe);
	print("risctrace %.8lux\n", signof risctrace);
	print("setmap %.8lux\n", signof setmap);
	print("symbase %.8lux\n", signof symbase);
	print("syminit %.8lux\n", signof syminit);
	print("symoff %.8lux\n", signof symoff);
	print("textseg %.8lux\n", signof textseg);
	print("textsym %.8lux\n", signof textsym);
	print("thumbpctab %.8lux\n", signof thumbpctab);
	print("thumbpclookup %.8lux\n", signof thumbpclookup);
	print("unusemap %.8lux\n", signof unusemap);
	exits(nil);
}
