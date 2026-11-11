#include <u.h>
#include <libc.h>
#include <authsrv.h>

void
main(void)
{
	print("Ticket %.8lux\n", signof(Ticket));
	print("Ticketreq %.8lux\n", signof(Ticketreq));
	print("Authenticator %.8lux\n", signof(Authenticator));
	print("Nvrsafe %.8lux\n", signof(Nvrsafe));
	print("Passwordreq %.8lux\n", signof(Passwordreq));
	print("OChapreply %.8lux\n", signof(OChapreply));
	print("OMSchapreply %.8lux\n", signof(OMSchapreply));
	print("NTLMreply %.8lux\n", signof(NTLMreply));
	print("Authkey %.8lux\n", signof(Authkey));
	print("PAKpriv %.8lux\n", signof(PAKpriv));
	print("struct Ticketreq %.8lux\n", signof(struct Ticketreq));
	print("struct Ticket %.8lux\n", signof(struct Ticket));
	print("struct Authenticator %.8lux\n", signof(struct Authenticator));
	print("struct Passwordreq %.8lux\n", signof(struct Passwordreq));
	print("struct OChapreply %.8lux\n", signof(struct OChapreply));
	print("struct OMSchapreply %.8lux\n", signof(struct OMSchapreply));
	print("struct NTLMreply %.8lux\n", signof(struct NTLMreply));
	print("struct Authkey %.8lux\n", signof(struct Authkey));
	print("struct Nvrsafe %.8lux\n", signof(struct Nvrsafe));
	print("struct PAKpriv %.8lux\n", signof(struct PAKpriv));
	print("convT2M %.8lux\n", signof convT2M);
	print("convM2T %.8lux\n", signof convM2T);
	print("convA2M %.8lux\n", signof convA2M);
	print("convM2A %.8lux\n", signof convM2A);
	print("convTR2M %.8lux\n", signof convTR2M);
	print("convM2TR %.8lux\n", signof convM2TR);
	print("convPR2M %.8lux\n", signof convPR2M);
	print("convM2PR %.8lux\n", signof convM2PR);
	print("passtokey %.8lux\n", signof passtokey);
	print("passtodeskey %.8lux\n", signof passtodeskey);
	print("passtoaeskey %.8lux\n", signof passtoaeskey);
	print("nvcsum %.8lux\n", signof nvcsum);
	print("readnvram %.8lux\n", signof readnvram);
	print("readcons %.8lux\n", signof readcons);
	print("authdial %.8lux\n", signof authdial);
	print("_asgetpakkey %.8lux\n", signof _asgetpakkey);
	print("_asgetticket %.8lux\n", signof _asgetticket);
	print("_asrequest %.8lux\n", signof _asrequest);
	print("_asgetresp %.8lux\n", signof _asgetresp);
	print("_asrdresp %.8lux\n", signof _asrdresp);
	print("authpak_hash %.8lux\n", signof authpak_hash);
	print("authpak_new %.8lux\n", signof authpak_new);
	print("authpak_finish %.8lux\n", signof authpak_finish);
	exits(nil);
}
