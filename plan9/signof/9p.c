#include <u.h>
#include <libc.h>
#include <fcall.h>
#include <thread.h>
#include <9p.h>

void
main(void)
{
	print("Fid %.8lux\n", signof(Fid));
	print("Req %.8lux\n", signof(Req));
	print("Fidpool %.8lux\n", signof(Fidpool));
	print("Reqpool %.8lux\n", signof(Reqpool));
	print("File %.8lux\n", signof(File));
	print("Tree %.8lux\n", signof(Tree));
	print("Srv %.8lux\n", signof(Srv));
	print("Reqqueue %.8lux\n", signof(Reqqueue));
	print("Queueelem %.8lux\n", signof(Queueelem));
	print("Cmdbuf %.8lux\n", signof(Cmdbuf));
	print("Cmdtab %.8lux\n", signof(Cmdtab));
	print("struct Queueelem %.8lux\n", signof(struct Queueelem));
	print("struct Reqqueue %.8lux\n", signof(struct Reqqueue));
	print("struct Fid %.8lux\n", signof(struct Fid));
	print("struct Req %.8lux\n", signof(struct Req));
	print("struct Fidpool %.8lux\n", signof(struct Fidpool));
	print("struct Reqpool %.8lux\n", signof(struct Reqpool));
	print("struct File %.8lux\n", signof(struct File));
	print("struct Tree %.8lux\n", signof(struct Tree));
	print("struct Cmdbuf %.8lux\n", signof(struct Cmdbuf));
	print("struct Cmdtab %.8lux\n", signof(struct Cmdtab));
	print("struct Srv %.8lux\n", signof(struct Srv));
	print("allocmap %.8lux\n", signof allocmap);
	print("freemap %.8lux\n", signof freemap);
	print("lookupkey %.8lux\n", signof lookupkey);
	print("insertkey %.8lux\n", signof insertkey);
	print("caninsertkey %.8lux\n", signof caninsertkey);
	print("deletekey %.8lux\n", signof deletekey);
	print("allocfidpool %.8lux\n", signof allocfidpool);
	print("freefidpool %.8lux\n", signof freefidpool);
	print("allocfid %.8lux\n", signof allocfid);
	print("lookupfid %.8lux\n", signof lookupfid);
	print("closefid %.8lux\n", signof closefid);
	print("removefid %.8lux\n", signof removefid);
	print("allocreqpool %.8lux\n", signof allocreqpool);
	print("freereqpool %.8lux\n", signof freereqpool);
	print("allocreq %.8lux\n", signof allocreq);
	print("lookupreq %.8lux\n", signof lookupreq);
	print("closereq %.8lux\n", signof closereq);
	print("removereq %.8lux\n", signof removereq);
	print("dirread9p %.8lux\n", signof dirread9p);
	print("alloctree %.8lux\n", signof alloctree);
	print("freetree %.8lux\n", signof freetree);
	print("createfile %.8lux\n", signof createfile);
	print("removefile %.8lux\n", signof removefile);
	print("closefile %.8lux\n", signof closefile);
	print("walkfile %.8lux\n", signof walkfile);
	print("opendirfile %.8lux\n", signof opendirfile);
	print("readdirfile %.8lux\n", signof readdirfile);
	print("closedirfile %.8lux\n", signof closedirfile);
	print("parsecmd %.8lux\n", signof parsecmd);
	print("respondcmderror %.8lux\n", signof respondcmderror);
	print("lookupcmd %.8lux\n", signof lookupcmd);
	print("srvforker %.8lux\n", signof srvforker);
	print("threadsrvforker %.8lux\n", signof threadsrvforker);
	print("srv %.8lux\n", signof srv);
	print("postsrv %.8lux\n", signof postsrv);
	print("postmountsrv %.8lux\n", signof postmountsrv);
	print("postsharesrv %.8lux\n", signof postsharesrv);
	print("listensrv %.8lux\n", signof listensrv);
	print("threadsrv %.8lux\n", signof threadsrv);
	print("threadpostsrv %.8lux\n", signof threadpostsrv);
	print("threadpostmountsrv %.8lux\n", signof threadpostmountsrv);
	print("threadpostsharesrv %.8lux\n", signof threadpostsharesrv);
	print("threadlistensrv %.8lux\n", signof threadlistensrv);
	print("chatty9p %.8lux\n", signof chatty9p);
	print("respond %.8lux\n", signof respond);
	print("responderror %.8lux\n", signof responderror);
	print("hasperm %.8lux\n", signof hasperm);
	print("emalloc9p %.8lux\n", signof emalloc9p);
	print("erealloc9p %.8lux\n", signof erealloc9p);
	print("estrdup9p %.8lux\n", signof estrdup9p);
	print("readstr %.8lux\n", signof readstr);
	print("readbuf %.8lux\n", signof readbuf);
	print("walkandclone %.8lux\n", signof walkandclone);
	print("auth9p %.8lux\n", signof auth9p);
	print("authread %.8lux\n", signof authread);
	print("authwrite %.8lux\n", signof authwrite);
	print("authdestroy %.8lux\n", signof authdestroy);
	print("authattach %.8lux\n", signof authattach);
	print("srvacquire %.8lux\n", signof srvacquire);
	print("srvrelease %.8lux\n", signof srvrelease);
	print("reqqueuecreate %.8lux\n", signof reqqueuecreate);
	print("reqqueuepush %.8lux\n", signof reqqueuepush);
	print("reqqueueflush %.8lux\n", signof reqqueueflush);
	print("reqqueuefree %.8lux\n", signof reqqueuefree);
	exits(nil);
}
