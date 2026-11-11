#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { uchar f0; ulong f1; vlong f2; int f3; int f4; short f5; uchar f6; };
typedef struct S1 S1;
struct S1 { vlong f0; char f1; double f2; char f3; ulong f4; int f5; uchar f6[2]; ushort f7; ushort f8; };
typedef struct S2 S2;
struct S2 { uchar f0[4]; uchar f1; char f2; };
typedef struct S3 S3;
struct S3 { short f0; float f1; float f2; long f3; int f4; uint f5; float f6; uint f7; uint f8; vlong f9; short f10; vlong f11; float f12; char f13[3]; uchar f14[2]; short f15; uchar f16; };

uvlong f0(ulong a0, S2 a1, S3 a2);
ulong f1(uvlong a0, uchar a1, S1 a2, ushort a3, char a4, uvlong a5, ulong a6, short a7);
uvlong f2(uvlong a0, S1 a1, uchar a2, long a3, int a4, float a5, uint a6, uint a7);
int f3(uvlong a0, S3 a1, S1 a2, ulong a3, ushort a4, uvlong a5);
uvlong f4(float a0, ulong a1, S2 a2);
S0 f5(uchar a0, S2 a1, S3 a2, long a3, uvlong a4, double a5);
int f6(uvlong a0, S2 a1, vlong a2);
S0 f7(double a0, uchar a1);
void f8(uint a0, S0 a1);
short f9(S0 a0);
void vf(int n, ...);
S2 cb(S2 (*fn)(S2, double, vlong), S2 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %ud %lud %lld %d %d %d %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %lld %d %g %d %lud %d %ud %ud %ud %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6[0], s.f6[1], s.f7, s.f8);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %ud %ud %ud %ud %ud %d\n", w, s.f0[0], s.f0[1], s.f0[2], s.f0[3], s.f1, s.f2);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %d %g %g %ld %d %ud %g %ud %ud %lld %d %lld %g %d %d %d %ud %ud %d %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11, s.f12, s.f13[0], s.f13[1], s.f13[2], s.f14[0], s.f14[1], s.f15, s.f16);
}

uvlong
f0(ulong a0, S2 a1, S3 a2)
{
	print("in f0\n");
	print("a0 ulong %lud\n", a0);
	pS2("a1", a1);
	pS3("a2", a2);
	return 1959961720ULL;
}

ulong
f1(uvlong a0, uchar a1, S1 a2, ushort a3, char a4, uvlong a5, ulong a6, short a7)
{
	print("in f1\n");
	print("a0 uvlong %llud\n", a0);
	print("a1 uchar %ud\n", a1);
	pS1("a2", a2);
	print("a3 ushort %ud\n", a3);
	print("a4 char %d\n", a4);
	print("a5 uvlong %llud\n", a5);
	print("a6 ulong %lud\n", a6);
	print("a7 short %d\n", a7);
	return 700037222UL;
}

uvlong
f2(uvlong a0, S1 a1, uchar a2, long a3, int a4, float a5, uint a6, uint a7)
{
	print("in f2\n");
	print("a0 uvlong %llud\n", a0);
	pS1("a1", a1);
	print("a2 uchar %ud\n", a2);
	print("a3 long %ld\n", a3);
	print("a4 int %d\n", a4);
	print("a5 float %g\n", a5);
	print("a6 uint %ud\n", a6);
	print("a7 uint %ud\n", a7);
	return 932717734ULL;
}

int
f3(uvlong a0, S3 a1, S1 a2, ulong a3, ushort a4, uvlong a5)
{
	print("in f3\n");
	print("a0 uvlong %llud\n", a0);
	pS3("a1", a1);
	pS1("a2", a2);
	print("a3 ulong %lud\n", a3);
	print("a4 ushort %ud\n", a4);
	print("a5 uvlong %llud\n", a5);
	return -1165398246;
}

uvlong
f4(float a0, ulong a1, S2 a2)
{
	print("in f4\n");
	print("a0 float %g\n", a0);
	print("a1 ulong %lud\n", a1);
	pS2("a2", a2);
	return 1426334365990268ULL;
}

S0
f5(uchar a0, S2 a1, S3 a2, long a3, uvlong a4, double a5)
{
	S0 r;

	print("in f5\n");
	print("a0 uchar %ud\n", a0);
	pS2("a1", a1);
	pS3("a2", a2);
	print("a3 long %ld\n", a3);
	print("a4 uvlong %llud\n", a4);
	print("a5 double %g\n", a5);
	r.f0 = 142;
	r.f1 = 475598399UL;
	r.f2 = -982550512LL;
	r.f3 = 1489502625;
	r.f4 = 1996454738;
	r.f5 = -29955;
	r.f6 = 180;
	return r;
}

int
f6(uvlong a0, S2 a1, vlong a2)
{
	print("in f6\n");
	print("a0 uvlong %llud\n", a0);
	pS2("a1", a1);
	print("a2 vlong %lld\n", a2);
	return 1532665523;
}

S0
f7(double a0, uchar a1)
{
	S0 r;

	print("in f7\n");
	print("a0 double %g\n", a0);
	print("a1 uchar %ud\n", a1);
	r.f0 = 90;
	r.f1 = 581933835UL;
	r.f2 = 1088885948LL;
	r.f3 = -1595838061;
	r.f4 = 2102790174;
	r.f5 = 463;
	r.f6 = 128;
	return r;
}

void
f8(uint a0, S0 a1)
{
	print("in f8\n");
	print("a0 uint %ud\n", a0);
	pS0("a1", a1);
}

short
f9(S0 a0)
{
	print("in f9\n");
	pS0("a0", a0);
	return 18063;
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %lld\n", va_arg(ap, vlong));
	print("v1 %d\n", va_arg(ap, int));
	va_end(ap);
}

S2
cb(S2 (*fn)(S2, double, vlong), S2 x)
{
	S2 r;

	r = fn(x, 2.5, -7LL);
	pS2("cb got", r);
	return fn(r, -1.25, 1LL<<40);
}

#else
static void
pS0(char *w, S0 s)
{
	print("%s S0 %ud %lud %lld %d %d %d %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %lld %d %g %d %lud %d %ud %ud %ud %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6[0], s.f6[1], s.f7, s.f8);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %ud %ud %ud %ud %ud %d\n", w, s.f0[0], s.f0[1], s.f0[2], s.f0[3], s.f1, s.f2);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %d %g %g %ld %d %ud %g %ud %ud %lld %d %lld %g %d %d %d %ud %ud %d %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11, s.f12, s.f13[0], s.f13[1], s.f13[2], s.f14[0], s.f14[1], s.f15, s.f16);
}

static S2
back(S2 x, double d, vlong v)
{
	pS2("back x", x);
	print("back %g %lld\n", d, v);
	x.f0[0] = x.f0[0] + 3;
	x.f0[1] = x.f0[1] + 3;
	x.f0[2] = x.f0[2] + 3;
	x.f0[3] = x.f0[3] + 3;
	x.f1 = x.f1 + 3;
	x.f2 = x.f2 + 3;
	return x;
}

void
main(void)
{
	{
	S2 v1;
	S3 v2;
	uvlong r;
	v1.f0[0] = 160;
	v1.f0[1] = 81;
	v1.f0[2] = 2;
	v1.f0[3] = 179;
	v1.f1 = 100;
	v1.f2 = -21;
	v2.f0 = -28532;
	v2.f1 = 4.375;
	v2.f2 = 5.250;
	v2.f3 = -1506368647L;
	v2.f4 = 2013320760;
	v2.f5 = 372789225U;
	v2.f6 = 9.750;
	v2.f7 = 1386693451U;
	v2.f8 = 1893645564U;
	v2.f9 = -4611432903639045824LL;
	v2.f10 = 12382;
	v2.f11 = 1267022056054772LL;
	v2.f12 = 15.000;
	v2.f13[0] = 113;
	v2.f13[1] = 34;
	v2.f13[2] = -83;
	v2.f14[0] = 132;
	v2.f14[1] = 53;
	v2.f15 = -32230;
	v2.f16 = 151;
	r = f0((ulong)1534619976UL, v1, v2);
	print("ret f0 uvlong %llud\n", r);
	}
	{
	S1 v2;
	ulong r;
	v2.f0 = 1471447438LL;
	v2.f1 = 63;
	v2.f2 = -34.000;
	v2.f3 = 33;
	v2.f4 = 1351772242UL;
	v2.f5 = -1858724355;
	v2.f6[0] = 180;
	v2.f6[1] = 101;
	v2.f7 = 20246;
	v2.f8 = 51399;
	r = f1((uvlong)873071458ULL, (uchar)19, v2, (ushort)63172, (char)-117, (uvlong)753396262ULL, (ulong)1260348375UL, (short)-23944);
	print("ret f1 ulong %lud\n", r);
	}
	{
	S1 v1;
	uvlong r;
	v1.f0 = 1704127950LL;
	v1.f1 = -127;
	v1.f2 = 30.000;
	v1.f3 = 97;
	v1.f4 = 1584452754UL;
	v1.f5 = 2091404867;
	v1.f6[0] = 244;
	v1.f6[1] = 165;
	v1.f7 = 47958;
	v1.f8 = 13575;
	r = f2((uvlong)1105751970ULL, v1, (uchar)83, (long)-2119656196L, (int)479124661, (float)52.250, (uint)1493028887U, (uint)1999981000U);
	print("ret f2 uvlong %llud\n", r);
	}
	{
	S3 v1;
	S1 v2;
	int r;
	v1.f0 = -23054;
	v1.f1 = -4.125;
	v1.f2 = -3.000;
	v1.f3 = -1310181153L;
	v1.f4 = 1817133266;
	v1.f5 = 176601731U;
	v1.f6 = 1.500;
	v1.f7 = 1190505957U;
	v1.f8 = 1697458070U;
	v1.f9 = -4611629091721608306LL;
	v1.f10 = 6904;
	v1.f11 = 1070833973492290LL;
	v1.f12 = 7.750;
	v1.f13[0] = 11;
	v1.f13[1] = 60;
	v1.f13[2] = -109;
	v1.f14[0] = 30;
	v1.f14[1] = 207;
	v1.f15 = -26752;
	v1.f16 = 49;
	v2.f0 = 1338432482LL;
	v2.f1 = -19;
	v2.f2 = 17.500;
	v2.f3 = 117;
	v2.f4 = 1218757286UL;
	v2.f5 = 1725709399;
	v2.f6[0] = 8;
	v2.f6[1] = 185;
	v2.f7 = 43370;
	v2.f8 = 8987;
	r = f3((uvlong)740056502ULL, v1, v2, (ulong)1247008615UL, (ushort)20760, (uvlong)113429533287586ULL);
	print("ret f3 int %d\n", r);
	}
	{
	S2 v2;
	uvlong r;
	v2.f0[0] = 15;
	v2.f0[1] = 192;
	v2.f0[2] = 113;
	v2.f0[3] = 34;
	v2.f1 = 211;
	v2.f2 = 4;
	r = f4((float)-1.625, (ulong)2106316436UL, v2);
	print("ret f4 uvlong %llud\n", r);
	}
	{
	S2 v1;
	S3 v2;
	S0 r;
	v1.f0[0] = 218;
	v1.f0[1] = 139;
	v1.f0[2] = 60;
	v1.f0[3] = 237;
	v1.f1 = 158;
	v1.f2 = 79;
	v2.f0 = 26798;
	v2.f1 = -38.125;
	v2.f2 = -37.000;
	v2.f3 = 818140609L;
	v2.f4 = 1325092722;
	v2.f5 = 1832044835U;
	v2.f6 = -33.500;
	v2.f7 = 698465413U;
	v2.f8 = 1205417526U;
	v2.f9 = 1712374776108924LL;
	v2.f10 = 10648;
	v2.f11 = -4611107226474017260LL;
	v2.f12 = -27.750;
	v2.f13[0] = 43;
	v2.f13[1] = -92;
	v2.f13[2] = 13;
	v2.f14[0] = 190;
	v2.f14[1] = 111;
	v2.f15 = 30496;
	v2.f16 = 209;
	r = f5((uchar)130, v1, v2, (long)1353344051L, (uvlong)1860296164ULL, (double)-16.375);
	pS0("ret f5", r);
	}
	{
	S2 v1;
	int r;
	v1.f0[0] = 219;
	v1.f0[1] = 140;
	v1.f0[2] = 61;
	v1.f0[3] = 238;
	v1.f1 = 159;
	v1.f2 = 80;
	r = f6((uvlong)1705704876099284ULL, v1, (vlong)65168224LL);
	print("ret f6 int %d\n", r);
	}
	{
	S0 r;
	r = f7((double)-16.250, (uchar)87);
	pS0("ret f7", r);
	}
	{
	S0 v1;
	v1.f0 = 157;
	v1.f1 = 952727374UL;
	v1.f2 = -4610226334561349450LL;
	v1.f3 = 1966631600;
	v1.f4 = 326100065;
	v1.f5 = -24082;
	v1.f6 = 195;
	f8((uint)1994882929U, v1);
	}
	{
	S0 v0;
	short r;
	v0.f0 = 183;
	v0.f1 = 291178856UL;
	v0.f2 = 798133363392914LL;
	v0.f3 = 1305083082;
	v0.f4 = -1812035195;
	v0.f5 = 28716;
	v0.f6 = 221;
	r = f9(v0);
	print("ret f9 short %d\n", r);
	}
	vf(2, (vlong)763209760LL, (int)-1270161873);
	{
	S2 x, r;

	x.f0[0] = 100;
	x.f0[1] = 21;
	x.f0[2] = 198;
	x.f0[3] = 119;
	x.f1 = 40;
	x.f2 = 89;
	r = cb(back, x);
	pS2("ret cb", r);
	}
	exits(nil);
}
#endif
