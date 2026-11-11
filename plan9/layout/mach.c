#include <u.h>
#include <libc.h>
#include <bio.h>
#include <mach.h>

void
main(void)
{
	print("struct Map %d\n", sizeof(struct Map));
	print("struct Map.nsegs %lud\n", offsetof(struct Map, nsegs));
	print("struct Map.seg %lud\n", offsetof(struct Map, seg));
	print("struct segment %d\n", sizeof(struct segment));
	print("struct segment.name %lud\n", offsetof(struct segment, name));
	print("struct segment.fd %lud\n", offsetof(struct segment, fd));
	print("struct segment.read %lud\n", offsetof(struct segment, read));
	print("struct segment.inuse %lud\n", offsetof(struct segment, inuse));
	print("struct segment.cache %lud\n", offsetof(struct segment, cache));
	print("struct segment.b %lud\n", offsetof(struct segment, b));
	print("struct segment.e %lud\n", offsetof(struct segment, e));
	print("struct segment.f %lud\n", offsetof(struct segment, f));
	print("struct Symbol %d\n", sizeof(struct Symbol));
	print("struct Symbol.handle %lud\n", offsetof(struct Symbol, handle));
	print("struct Symbol.name %lud\n", offsetof(struct Symbol, name));
	print("struct Symbol.value %lud\n", offsetof(struct Symbol, value));
	print("struct Symbol.type %lud\n", offsetof(struct Symbol, type));
	print("struct Symbol.class %lud\n", offsetof(struct Symbol, class));
	print("struct Symbol.index %lud\n", offsetof(struct Symbol, index));
	print("struct Reglist %d\n", sizeof(struct Reglist));
	print("struct Reglist.rname %lud\n", offsetof(struct Reglist, rname));
	print("struct Reglist.roffs %lud\n", offsetof(struct Reglist, roffs));
	print("struct Reglist.rflags %lud\n", offsetof(struct Reglist, rflags));
	print("struct Reglist.rformat %lud\n", offsetof(struct Reglist, rformat));
	print("struct Mach %d\n", sizeof(struct Mach));
	print("struct Mach.name %lud\n", offsetof(struct Mach, name));
	print("struct Mach.mtype %lud\n", offsetof(struct Mach, mtype));
	print("struct Mach.reglist %lud\n", offsetof(struct Mach, reglist));
	print("struct Mach.regsize %lud\n", offsetof(struct Mach, regsize));
	print("struct Mach.fpregsize %lud\n", offsetof(struct Mach, fpregsize));
	print("struct Mach.pc %lud\n", offsetof(struct Mach, pc));
	print("struct Mach.sp %lud\n", offsetof(struct Mach, sp));
	print("struct Mach.link %lud\n", offsetof(struct Mach, link));
	print("struct Mach.sbreg %lud\n", offsetof(struct Mach, sbreg));
	print("struct Mach.sb %lud\n", offsetof(struct Mach, sb));
	print("struct Mach.pgsize %lud\n", offsetof(struct Mach, pgsize));
	print("struct Mach.kbase %lud\n", offsetof(struct Mach, kbase));
	print("struct Mach.ktmask %lud\n", offsetof(struct Mach, ktmask));
	print("struct Mach.utop %lud\n", offsetof(struct Mach, utop));
	print("struct Mach.pcquant %lud\n", offsetof(struct Mach, pcquant));
	print("struct Mach.szaddr %lud\n", offsetof(struct Mach, szaddr));
	print("struct Mach.szreg %lud\n", offsetof(struct Mach, szreg));
	print("struct Mach.szfloat %lud\n", offsetof(struct Mach, szfloat));
	print("struct Mach.szdouble %lud\n", offsetof(struct Mach, szdouble));
	print("struct Machdata %d\n", sizeof(struct Machdata));
	print("struct Machdata.bpinst %lud\n", offsetof(struct Machdata, bpinst));
	print("struct Machdata.bpsize %lud\n", offsetof(struct Machdata, bpsize));
	print("struct Machdata.swab %lud\n", offsetof(struct Machdata, swab));
	print("struct Machdata.swal %lud\n", offsetof(struct Machdata, swal));
	print("struct Machdata.swav %lud\n", offsetof(struct Machdata, swav));
	print("struct Machdata.ctrace %lud\n", offsetof(struct Machdata, ctrace));
	print("struct Machdata.findframe %lud\n", offsetof(struct Machdata, findframe));
	print("struct Machdata.excep %lud\n", offsetof(struct Machdata, excep));
	print("struct Machdata.bpfix %lud\n", offsetof(struct Machdata, bpfix));
	print("struct Machdata.sftos %lud\n", offsetof(struct Machdata, sftos));
	print("struct Machdata.dftos %lud\n", offsetof(struct Machdata, dftos));
	print("struct Machdata.foll %lud\n", offsetof(struct Machdata, foll));
	print("struct Machdata.das %lud\n", offsetof(struct Machdata, das));
	print("struct Machdata.hexinst %lud\n", offsetof(struct Machdata, hexinst));
	print("struct Machdata.instsize %lud\n", offsetof(struct Machdata, instsize));
	print("struct Fhdr %d\n", sizeof(struct Fhdr));
	print("struct Fhdr.name %lud\n", offsetof(struct Fhdr, name));
	print("struct Fhdr.type %lud\n", offsetof(struct Fhdr, type));
	print("struct Fhdr.hdrsz %lud\n", offsetof(struct Fhdr, hdrsz));
	print("struct Fhdr._magic %lud\n", offsetof(struct Fhdr, _magic));
	print("struct Fhdr.spare %lud\n", offsetof(struct Fhdr, spare));
	print("struct Fhdr.magic %lud\n", offsetof(struct Fhdr, magic));
	print("struct Fhdr.txtaddr %lud\n", offsetof(struct Fhdr, txtaddr));
	print("struct Fhdr.txtoff %lud\n", offsetof(struct Fhdr, txtoff));
	print("struct Fhdr.dataddr %lud\n", offsetof(struct Fhdr, dataddr));
	print("struct Fhdr.datoff %lud\n", offsetof(struct Fhdr, datoff));
	print("struct Fhdr.symoff %lud\n", offsetof(struct Fhdr, symoff));
	print("struct Fhdr.entry %lud\n", offsetof(struct Fhdr, entry));
	print("struct Fhdr.sppcoff %lud\n", offsetof(struct Fhdr, sppcoff));
	print("struct Fhdr.lnpcoff %lud\n", offsetof(struct Fhdr, lnpcoff));
	print("struct Fhdr.txtsz %lud\n", offsetof(struct Fhdr, txtsz));
	print("struct Fhdr.datsz %lud\n", offsetof(struct Fhdr, datsz));
	print("struct Fhdr.bsssz %lud\n", offsetof(struct Fhdr, bsssz));
	print("struct Fhdr.symsz %lud\n", offsetof(struct Fhdr, symsz));
	print("struct Fhdr.sppcsz %lud\n", offsetof(struct Fhdr, sppcsz));
	print("struct Fhdr.lnpcsz %lud\n", offsetof(struct Fhdr, lnpcsz));
	exits(nil);
}
