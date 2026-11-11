#include <u.h>
#include <libc.h>
#include <auth.h>

void
main(void)
{
	print("struct AuthRpc %d\n", sizeof(struct AuthRpc));
	print("struct AuthRpc.afd %lud\n", offsetof(struct AuthRpc, afd));
	print("struct AuthRpc.ibuf %lud\n", offsetof(struct AuthRpc, ibuf));
	print("struct AuthRpc.obuf %lud\n", offsetof(struct AuthRpc, obuf));
	print("struct AuthRpc.arg %lud\n", offsetof(struct AuthRpc, arg));
	print("struct AuthRpc.narg %lud\n", offsetof(struct AuthRpc, narg));
	print("struct AuthInfo %d\n", sizeof(struct AuthInfo));
	print("struct AuthInfo.cuid %lud\n", offsetof(struct AuthInfo, cuid));
	print("struct AuthInfo.suid %lud\n", offsetof(struct AuthInfo, suid));
	print("struct AuthInfo.cap %lud\n", offsetof(struct AuthInfo, cap));
	print("struct AuthInfo.nsecret %lud\n", offsetof(struct AuthInfo, nsecret));
	print("struct AuthInfo.secret %lud\n", offsetof(struct AuthInfo, secret));
	print("struct Chalstate %d\n", sizeof(struct Chalstate));
	print("struct Chalstate.user %lud\n", offsetof(struct Chalstate, user));
	print("struct Chalstate.dom %lud\n", offsetof(struct Chalstate, dom));
	print("struct Chalstate.chal %lud\n", offsetof(struct Chalstate, chal));
	print("struct Chalstate.nchal %lud\n", offsetof(struct Chalstate, nchal));
	print("struct Chalstate.resp %lud\n", offsetof(struct Chalstate, resp));
	print("struct Chalstate.nresp %lud\n", offsetof(struct Chalstate, nresp));
	print("struct Chalstate.afd %lud\n", offsetof(struct Chalstate, afd));
	print("struct Chalstate.rpc %lud\n", offsetof(struct Chalstate, rpc));
	print("struct Chalstate.userbuf %lud\n", offsetof(struct Chalstate, userbuf));
	print("struct Chalstate.userinchal %lud\n", offsetof(struct Chalstate, userinchal));
	print("struct Chapreply %d\n", sizeof(struct Chapreply));
	print("struct Chapreply.id %lud\n", offsetof(struct Chapreply, id));
	print("struct Chapreply.resp %lud\n", offsetof(struct Chapreply, resp));
	print("struct MSchapreply %d\n", sizeof(struct MSchapreply));
	print("struct MSchapreply.LMresp %lud\n", offsetof(struct MSchapreply, LMresp));
	print("struct MSchapreply.NTresp %lud\n", offsetof(struct MSchapreply, NTresp));
	print("struct UserPasswd %d\n", sizeof(struct UserPasswd));
	print("struct UserPasswd.user %lud\n", offsetof(struct UserPasswd, user));
	print("struct UserPasswd.passwd %lud\n", offsetof(struct UserPasswd, passwd));
	print("struct Attr %d\n", sizeof(struct Attr));
	print("struct Attr.type %lud\n", offsetof(struct Attr, type));
	print("struct Attr.next %lud\n", offsetof(struct Attr, next));
	print("struct Attr.name %lud\n", offsetof(struct Attr, name));
	print("struct Attr.val %lud\n", offsetof(struct Attr, val));
	exits(nil);
}
