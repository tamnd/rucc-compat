#include <u.h>
#include <libc.h>
#include <authsrv.h>

void
main(void)
{
	print("struct Ticketreq %d\n", sizeof(struct Ticketreq));
	print("struct Ticketreq.type %lud\n", offsetof(struct Ticketreq, type));
	print("struct Ticketreq.authid %lud\n", offsetof(struct Ticketreq, authid));
	print("struct Ticketreq.authdom %lud\n", offsetof(struct Ticketreq, authdom));
	print("struct Ticketreq.chal %lud\n", offsetof(struct Ticketreq, chal));
	print("struct Ticketreq.hostid %lud\n", offsetof(struct Ticketreq, hostid));
	print("struct Ticketreq.uid %lud\n", offsetof(struct Ticketreq, uid));
	print("struct Ticket %d\n", sizeof(struct Ticket));
	print("struct Ticket.num %lud\n", offsetof(struct Ticket, num));
	print("struct Ticket.chal %lud\n", offsetof(struct Ticket, chal));
	print("struct Ticket.cuid %lud\n", offsetof(struct Ticket, cuid));
	print("struct Ticket.suid %lud\n", offsetof(struct Ticket, suid));
	print("struct Ticket.key %lud\n", offsetof(struct Ticket, key));
	print("struct Ticket.form %lud\n", offsetof(struct Ticket, form));
	print("struct Authenticator %d\n", sizeof(struct Authenticator));
	print("struct Authenticator.num %lud\n", offsetof(struct Authenticator, num));
	print("struct Authenticator.chal %lud\n", offsetof(struct Authenticator, chal));
	print("struct Authenticator.rand %lud\n", offsetof(struct Authenticator, rand));
	print("struct Passwordreq %d\n", sizeof(struct Passwordreq));
	print("struct Passwordreq.num %lud\n", offsetof(struct Passwordreq, num));
	print("struct Passwordreq.old %lud\n", offsetof(struct Passwordreq, old));
	print("struct Passwordreq.new %lud\n", offsetof(struct Passwordreq, new));
	print("struct Passwordreq.changesecret %lud\n", offsetof(struct Passwordreq, changesecret));
	print("struct Passwordreq.secret %lud\n", offsetof(struct Passwordreq, secret));
	print("struct OChapreply %d\n", sizeof(struct OChapreply));
	print("struct OChapreply.id %lud\n", offsetof(struct OChapreply, id));
	print("struct OChapreply.uid %lud\n", offsetof(struct OChapreply, uid));
	print("struct OChapreply.resp %lud\n", offsetof(struct OChapreply, resp));
	print("struct OMSchapreply %d\n", sizeof(struct OMSchapreply));
	print("struct OMSchapreply.uid %lud\n", offsetof(struct OMSchapreply, uid));
	print("struct OMSchapreply.LMresp %lud\n", offsetof(struct OMSchapreply, LMresp));
	print("struct OMSchapreply.NTresp %lud\n", offsetof(struct OMSchapreply, NTresp));
	print("struct NTLMreply %d\n", sizeof(struct NTLMreply));
	print("struct NTLMreply.len %lud\n", offsetof(struct NTLMreply, len));
	print("struct NTLMreply.uid %lud\n", offsetof(struct NTLMreply, uid));
	print("struct NTLMreply.dom %lud\n", offsetof(struct NTLMreply, dom));
	print("struct NTLMreply.LMresp %lud\n", offsetof(struct NTLMreply, LMresp));
	print("struct NTLMreply.NTresp %lud\n", offsetof(struct NTLMreply, NTresp));
	print("struct Authkey %d\n", sizeof(struct Authkey));
	print("struct Authkey.des %lud\n", offsetof(struct Authkey, des));
	print("struct Authkey.aes %lud\n", offsetof(struct Authkey, aes));
	print("struct Authkey.pakkey %lud\n", offsetof(struct Authkey, pakkey));
	print("struct Authkey.pakhash %lud\n", offsetof(struct Authkey, pakhash));
	print("struct Nvrsafe %d\n", sizeof(struct Nvrsafe));
	print("struct Nvrsafe.machkey %lud\n", offsetof(struct Nvrsafe, machkey));
	print("struct Nvrsafe.machsum %lud\n", offsetof(struct Nvrsafe, machsum));
	print("struct Nvrsafe.authkey %lud\n", offsetof(struct Nvrsafe, authkey));
	print("struct Nvrsafe.authsum %lud\n", offsetof(struct Nvrsafe, authsum));
	print("struct Nvrsafe.config %lud\n", offsetof(struct Nvrsafe, config));
	print("struct Nvrsafe.configsum %lud\n", offsetof(struct Nvrsafe, configsum));
	print("struct Nvrsafe.authid %lud\n", offsetof(struct Nvrsafe, authid));
	print("struct Nvrsafe.authidsum %lud\n", offsetof(struct Nvrsafe, authidsum));
	print("struct Nvrsafe.authdom %lud\n", offsetof(struct Nvrsafe, authdom));
	print("struct Nvrsafe.authdomsum %lud\n", offsetof(struct Nvrsafe, authdomsum));
	print("struct Nvrsafe.aesmachkey %lud\n", offsetof(struct Nvrsafe, aesmachkey));
	print("struct Nvrsafe.aesmachsum %lud\n", offsetof(struct Nvrsafe, aesmachsum));
	print("struct PAKpriv %d\n", sizeof(struct PAKpriv));
	print("struct PAKpriv.isclient %lud\n", offsetof(struct PAKpriv, isclient));
	print("struct PAKpriv.x %lud\n", offsetof(struct PAKpriv, x));
	print("struct PAKpriv.y %lud\n", offsetof(struct PAKpriv, y));
	exits(nil);
}
