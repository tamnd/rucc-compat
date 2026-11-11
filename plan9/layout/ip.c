#include <u.h>
#include <libc.h>
#include <ip.h>

void
main(void)
{
	print("struct Iplifc %d\n", sizeof(struct Iplifc));
	print("struct Iplifc.next %lud\n", offsetof(struct Iplifc, next));
	print("struct Iplifc.ip %lud\n", offsetof(struct Iplifc, ip));
	print("struct Iplifc.mask %lud\n", offsetof(struct Iplifc, mask));
	print("struct Iplifc.net %lud\n", offsetof(struct Iplifc, net));
	print("struct Iplifc.preflt %lud\n", offsetof(struct Iplifc, preflt));
	print("struct Iplifc.validlt %lud\n", offsetof(struct Iplifc, validlt));
	print("struct Ipv6rp %d\n", sizeof(struct Ipv6rp));
	print("struct Ipv6rp.mflag %lud\n", offsetof(struct Ipv6rp, mflag));
	print("struct Ipv6rp.oflag %lud\n", offsetof(struct Ipv6rp, oflag));
	print("struct Ipv6rp.maxraint %lud\n", offsetof(struct Ipv6rp, maxraint));
	print("struct Ipv6rp.minraint %lud\n", offsetof(struct Ipv6rp, minraint));
	print("struct Ipv6rp.linkmtu %lud\n", offsetof(struct Ipv6rp, linkmtu));
	print("struct Ipv6rp.reachtime %lud\n", offsetof(struct Ipv6rp, reachtime));
	print("struct Ipv6rp.rxmitra %lud\n", offsetof(struct Ipv6rp, rxmitra));
	print("struct Ipv6rp.ttl %lud\n", offsetof(struct Ipv6rp, ttl));
	print("struct Ipv6rp.routerlt %lud\n", offsetof(struct Ipv6rp, routerlt));
	print("struct Ipifc %d\n", sizeof(struct Ipifc));
	print("struct Ipifc.next %lud\n", offsetof(struct Ipifc, next));
	print("struct Ipifc.lifc %lud\n", offsetof(struct Ipifc, lifc));
	print("struct Ipifc.index %lud\n", offsetof(struct Ipifc, index));
	print("struct Ipifc.dev %lud\n", offsetof(struct Ipifc, dev));
	print("struct Ipifc.sendra6 %lud\n", offsetof(struct Ipifc, sendra6));
	print("struct Ipifc.recvra6 %lud\n", offsetof(struct Ipifc, recvra6));
	print("struct Ipifc.mtu %lud\n", offsetof(struct Ipifc, mtu));
	print("struct Ipifc.pktin %lud\n", offsetof(struct Ipifc, pktin));
	print("struct Ipifc.pktout %lud\n", offsetof(struct Ipifc, pktout));
	print("struct Ipifc.errin %lud\n", offsetof(struct Ipifc, errin));
	print("struct Ipifc.errout %lud\n", offsetof(struct Ipifc, errout));
	print("struct Ipifc.rp %lud\n", offsetof(struct Ipifc, rp));
	print("struct Ip6hdr %d\n", sizeof(struct Ip6hdr));
	print("struct Ip6hdr.vcf %lud\n", offsetof(struct Ip6hdr, vcf));
	print("struct Ip6hdr.ploadlen %lud\n", offsetof(struct Ip6hdr, ploadlen));
	print("struct Ip6hdr.proto %lud\n", offsetof(struct Ip6hdr, proto));
	print("struct Ip6hdr.ttl %lud\n", offsetof(struct Ip6hdr, ttl));
	print("struct Ip6hdr.src %lud\n", offsetof(struct Ip6hdr, src));
	print("struct Ip6hdr.dst %lud\n", offsetof(struct Ip6hdr, dst));
	print("struct Ip6hdr.payload %lud\n", offsetof(struct Ip6hdr, payload));
	print("struct Icmp6hdr %d\n", sizeof(struct Icmp6hdr));
	print("struct Icmp6hdr._0_ %lud\n", offsetof(struct Icmp6hdr, _0_));
	print("struct Icmp6hdr.laddr %lud\n", offsetof(struct Icmp6hdr, laddr));
	print("struct Icmp6hdr.raddr %lud\n", offsetof(struct Icmp6hdr, raddr));
	print("struct Udphdr %d\n", sizeof(struct Udphdr));
	print("struct Udphdr.raddr %lud\n", offsetof(struct Udphdr, raddr));
	print("struct Udphdr.laddr %lud\n", offsetof(struct Udphdr, laddr));
	print("struct Udphdr.ifcaddr %lud\n", offsetof(struct Udphdr, ifcaddr));
	print("struct Udphdr.rport %lud\n", offsetof(struct Udphdr, rport));
	print("struct Udphdr.lport %lud\n", offsetof(struct Udphdr, lport));
	exits(nil);
}
