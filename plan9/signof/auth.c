#include <u.h>
#include <libc.h>
#include <auth.h>

void
main(void)
{
	print("AuthInfo %.8lux\n", signof(AuthInfo));
	print("Chalstate %.8lux\n", signof(Chalstate));
	print("Chapreply %.8lux\n", signof(Chapreply));
	print("MSchapreply %.8lux\n", signof(MSchapreply));
	print("UserPasswd %.8lux\n", signof(UserPasswd));
	print("AuthRpc %.8lux\n", signof(AuthRpc));
	print("Attr %.8lux\n", signof(Attr));
	print("struct AuthRpc %.8lux\n", signof(struct AuthRpc));
	print("struct AuthInfo %.8lux\n", signof(struct AuthInfo));
	print("struct Chalstate %.8lux\n", signof(struct Chalstate));
	print("struct Chapreply %.8lux\n", signof(struct Chapreply));
	print("struct MSchapreply %.8lux\n", signof(struct MSchapreply));
	print("struct UserPasswd %.8lux\n", signof(struct UserPasswd));
	print("struct Attr %.8lux\n", signof(struct Attr));
	print("newns %.8lux\n", signof newns);
	print("addns %.8lux\n", signof addns);
	print("noworld %.8lux\n", signof noworld);
	print("amount %.8lux\n", signof amount);
	print("login %.8lux\n", signof login);
	print("procsetuser %.8lux\n", signof procsetuser);
	print("_attrfmt %.8lux\n", signof _attrfmt);
	print("_copyattr %.8lux\n", signof _copyattr);
	print("_delattr %.8lux\n", signof _delattr);
	print("_findattr %.8lux\n", signof _findattr);
	print("_freeattr %.8lux\n", signof _freeattr);
	print("_mkattr %.8lux\n", signof _mkattr);
	print("_parseattr %.8lux\n", signof _parseattr);
	print("_strfindattr %.8lux\n", signof _strfindattr);
	print("fauth_proxy %.8lux\n", signof fauth_proxy);
	print("auth_proxy %.8lux\n", signof auth_proxy);
	print("auth_getkey %.8lux\n", signof auth_getkey);
	print("amount_getkey %.8lux\n", signof amount_getkey);
	print("auth_freeAI %.8lux\n", signof auth_freeAI);
	print("auth_chuid %.8lux\n", signof auth_chuid);
	print("auth_challenge %.8lux\n", signof auth_challenge);
	print("auth_response %.8lux\n", signof auth_response);
	print("auth_respond %.8lux\n", signof auth_respond);
	print("auth_respondAI %.8lux\n", signof auth_respondAI);
	print("auth_freechal %.8lux\n", signof auth_freechal);
	print("auth_userpasswd %.8lux\n", signof auth_userpasswd);
	print("auth_getuserpasswd %.8lux\n", signof auth_getuserpasswd);
	print("auth_getinfo %.8lux\n", signof auth_getinfo);
	print("auth_allocrpc %.8lux\n", signof auth_allocrpc);
	print("auth_attr %.8lux\n", signof auth_attr);
	print("auth_freerpc %.8lux\n", signof auth_freerpc);
	print("auth_rpc %.8lux\n", signof auth_rpc);
	exits(nil);
}
