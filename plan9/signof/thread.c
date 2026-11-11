#include <u.h>
#include <libc.h>
#include <thread.h>

void
main(void)
{
	print("Alt %.8lux\n", signof(Alt));
	print("Channel %.8lux\n", signof(Channel));
	print("Ref %.8lux\n", signof(Ref));
	print("ChanOp %.8lux\n", signof(ChanOp));
	print("struct Channel %.8lux\n", signof(struct Channel));
	print("struct Alt %.8lux\n", signof(struct Alt));
	print("struct Ref %.8lux\n", signof(struct Ref));
	print("alt %.8lux\n", signof alt);
	print("chanclose %.8lux\n", signof chanclose);
	print("chanclosing %.8lux\n", signof chanclosing);
	print("chancreate %.8lux\n", signof chancreate);
	print("chanfree %.8lux\n", signof chanfree);
	print("chanprint %.8lux\n", signof chanprint);
	print("decref %.8lux\n", signof decref);
	print("incref %.8lux\n", signof incref);
	print("nbrecv %.8lux\n", signof nbrecv);
	print("nbrecvp %.8lux\n", signof nbrecvp);
	print("nbrecvul %.8lux\n", signof nbrecvul);
	print("nbsend %.8lux\n", signof nbsend);
	print("nbsendp %.8lux\n", signof nbsendp);
	print("nbsendul %.8lux\n", signof nbsendul);
	print("needstack %.8lux\n", signof needstack);
	print("proccreate %.8lux\n", signof proccreate);
	print("procrfork %.8lux\n", signof procrfork);
	print("procdata %.8lux\n", signof procdata);
	print("procexec %.8lux\n", signof procexec);
	print("procexecl %.8lux\n", signof procexecl);
	print("recv %.8lux\n", signof recv);
	print("recvp %.8lux\n", signof recvp);
	print("recvul %.8lux\n", signof recvul);
	print("send %.8lux\n", signof send);
	print("sendp %.8lux\n", signof sendp);
	print("sendul %.8lux\n", signof sendul);
	print("threadcreate %.8lux\n", signof threadcreate);
	print("threaddata %.8lux\n", signof threaddata);
	print("threadexits %.8lux\n", signof threadexits);
	print("threadexitsall %.8lux\n", signof threadexitsall);
	print("threadgetgrp %.8lux\n", signof threadgetgrp);
	print("threadgetname %.8lux\n", signof threadgetname);
	print("threadint %.8lux\n", signof threadint);
	print("threadintgrp %.8lux\n", signof threadintgrp);
	print("threadkill %.8lux\n", signof threadkill);
	print("threadkillgrp %.8lux\n", signof threadkillgrp);
	print("threadmain %.8lux\n", signof threadmain);
	print("threadnotify %.8lux\n", signof threadnotify);
	print("threadid %.8lux\n", signof threadid);
	print("threadpid %.8lux\n", signof threadpid);
	print("threadsetgrp %.8lux\n", signof threadsetgrp);
	print("threadsetname %.8lux\n", signof threadsetname);
	print("threadwaitchan %.8lux\n", signof threadwaitchan);
	print("yield %.8lux\n", signof yield);
	print("mainstacksize %.8lux\n", signof mainstacksize);
	print("ioproc %.8lux\n", signof ioproc);
	print("closeioproc %.8lux\n", signof closeioproc);
	print("iointerrupt %.8lux\n", signof iointerrupt);
	print("ioclose %.8lux\n", signof ioclose);
	print("iodial %.8lux\n", signof iodial);
	print("ioopen %.8lux\n", signof ioopen);
	print("ioread %.8lux\n", signof ioread);
	print("ioreadn %.8lux\n", signof ioreadn);
	print("iowrite %.8lux\n", signof iowrite);
	print("iosleep %.8lux\n", signof iosleep);
	print("ioflush %.8lux\n", signof ioflush);
	print("iocall %.8lux\n", signof iocall);
	exits(nil);
}
