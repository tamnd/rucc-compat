#include <u.h>
#include <libc.h>
#include <ip.h>

void
main(void)
{
	print("Ipifc %.8lux\n", signof(Ipifc));
	print("Iplifc %.8lux\n", signof(Iplifc));
	print("Ipv6rp %.8lux\n", signof(Ipv6rp));
	print("Ip6hdr %.8lux\n", signof(Ip6hdr));
	print("Icmp6hdr %.8lux\n", signof(Icmp6hdr));
	print("Udphdr %.8lux\n", signof(Udphdr));
	print("struct Iplifc %.8lux\n", signof(struct Iplifc));
	print("struct Ipv6rp %.8lux\n", signof(struct Ipv6rp));
	print("struct Ipifc %.8lux\n", signof(struct Ipifc));
	print("struct Ip6hdr %.8lux\n", signof(struct Ip6hdr));
	print("struct Icmp6hdr %.8lux\n", signof(struct Icmp6hdr));
	print("struct Udphdr %.8lux\n", signof(struct Udphdr));
	print("defmask %.8lux\n", signof defmask);
	print("maskip %.8lux\n", signof maskip);
	print("eipfmt %.8lux\n", signof eipfmt);
	print("isv4 %.8lux\n", signof isv4);
	print("parseip %.8lux\n", signof parseip);
	print("parseipmask %.8lux\n", signof parseipmask);
	print("parseipandmask %.8lux\n", signof parseipandmask);
	print("v4parseip %.8lux\n", signof v4parseip);
	print("parseether %.8lux\n", signof parseether);
	print("myipaddr %.8lux\n", signof myipaddr);
	print("myetheraddr %.8lux\n", signof myetheraddr);
	print("equivip4 %.8lux\n", signof equivip4);
	print("equivip6 %.8lux\n", signof equivip6);
	print("readipifc %.8lux\n", signof readipifc);
	print("iplocalonifc %.8lux\n", signof iplocalonifc);
	print("ipremoteonifc %.8lux\n", signof ipremoteonifc);
	print("hnputv %.8lux\n", signof hnputv);
	print("hnputl %.8lux\n", signof hnputl);
	print("hnputs %.8lux\n", signof hnputs);
	print("nhgetv %.8lux\n", signof nhgetv);
	print("nhgetl %.8lux\n", signof nhgetl);
	print("nhgets %.8lux\n", signof nhgets);
	print("ptclbsum %.8lux\n", signof ptclbsum);
	print("v6tov4 %.8lux\n", signof v6tov4);
	print("v4tov6 %.8lux\n", signof v4tov6);
	print("IPv4bcast %.8lux\n", signof IPv4bcast);
	print("IPv4bcastobs %.8lux\n", signof IPv4bcastobs);
	print("IPv4allsys %.8lux\n", signof IPv4allsys);
	print("IPv4allrouter %.8lux\n", signof IPv4allrouter);
	print("IPnoaddr %.8lux\n", signof IPnoaddr);
	print("v4prefix %.8lux\n", signof v4prefix);
	print("IPallbits %.8lux\n", signof IPallbits);
	exits(nil);
}
