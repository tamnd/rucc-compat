#include <u.h>
#include <libc.h>
#include <httpd.h>

void
main(void)
{
	print("HConnect %.8lux\n", signof(HConnect));
	print("HContent %.8lux\n", signof(HContent));
	print("HContents %.8lux\n", signof(HContents));
	print("HETag %.8lux\n", signof(HETag));
	print("HFields %.8lux\n", signof(HFields));
	print("Hio %.8lux\n", signof(Hio));
	print("Htmlesc %.8lux\n", signof(Htmlesc));
	print("HttpHead %.8lux\n", signof(HttpHead));
	print("HttpReq %.8lux\n", signof(HttpReq));
	print("HRange %.8lux\n", signof(HRange));
	print("HSPairs %.8lux\n", signof(HSPairs));
	print("struct Htmlesc %.8lux\n", signof(struct Htmlesc));
	print("struct HContent %.8lux\n", signof(struct HContent));
	print("struct HContents %.8lux\n", signof(struct HContents));
	print("struct HFields %.8lux\n", signof(struct HFields));
	print("struct HSPairs %.8lux\n", signof(struct HSPairs));
	print("struct HRange %.8lux\n", signof(struct HRange));
	print("struct HETag %.8lux\n", signof(struct HETag));
	print("struct Hio %.8lux\n", signof(struct Hio));
	print("struct HttpReq %.8lux\n", signof(struct HttpReq));
	print("struct HttpHead %.8lux\n", signof(struct HttpHead));
	print("struct HConnect %.8lux\n", signof(struct HConnect));
	print("hmydomain %.8lux\n", signof hmydomain);
	print("hversion %.8lux\n", signof hversion);
	print("htmlesc %.8lux\n", signof htmlesc);
	print("halloc %.8lux\n", signof halloc);
	print("hbodypush %.8lux\n", signof hbodypush);
	print("hbuflen %.8lux\n", signof hbuflen);
	print("hcheckcontent %.8lux\n", signof hcheckcontent);
	print("hclose %.8lux\n", signof hclose);
	print("hdate2sec %.8lux\n", signof hdate2sec);
	print("hdatefmt %.8lux\n", signof hdatefmt);
	print("hfail %.8lux\n", signof hfail);
	print("hflush %.8lux\n", signof hflush);
	print("hgetc %.8lux\n", signof hgetc);
	print("hgethead %.8lux\n", signof hgethead);
	print("hinit %.8lux\n", signof hinit);
	print("hiserror %.8lux\n", signof hiserror);
	print("hlflush %.8lux\n", signof hlflush);
	print("hload %.8lux\n", signof hload);
	print("hlower %.8lux\n", signof hlower);
	print("hmkcontent %.8lux\n", signof hmkcontent);
	print("hmkhfields %.8lux\n", signof hmkhfields);
	print("hmkmimeboundary %.8lux\n", signof hmkmimeboundary);
	print("hmkspairs %.8lux\n", signof hmkspairs);
	print("hmoved %.8lux\n", signof hmoved);
	print("hokheaders %.8lux\n", signof hokheaders);
	print("hparseheaders %.8lux\n", signof hparseheaders);
	print("hparsequery %.8lux\n", signof hparsequery);
	print("hparsereq %.8lux\n", signof hparsereq);
	print("hprint %.8lux\n", signof hprint);
	print("hputc %.8lux\n", signof hputc);
	print("hreadbuf %.8lux\n", signof hreadbuf);
	print("hredirected %.8lux\n", signof hredirected);
	print("hreqcleanup %.8lux\n", signof hreqcleanup);
	print("hrevhfields %.8lux\n", signof hrevhfields);
	print("hrevspairs %.8lux\n", signof hrevspairs);
	print("hstrdup %.8lux\n", signof hstrdup);
	print("http11 %.8lux\n", signof http11);
	print("httpfmt %.8lux\n", signof httpfmt);
	print("httpunesc %.8lux\n", signof httpunesc);
	print("hunallowed %.8lux\n", signof hunallowed);
	print("hungetc %.8lux\n", signof hungetc);
	print("hunload %.8lux\n", signof hunload);
	print("hurlfmt %.8lux\n", signof hurlfmt);
	print("hurlunesc %.8lux\n", signof hurlunesc);
	print("hvprint %.8lux\n", signof hvprint);
	print("hwrite %.8lux\n", signof hwrite);
	print("hxferenc %.8lux\n", signof hxferenc);
	exits(nil);
}
