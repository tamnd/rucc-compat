#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { uchar f0[9]; };
typedef struct S1 S1;
struct S1 { char f0; };
typedef struct S2 S2;
struct S2 { uint f0; int f1; ushort f2; ushort f3; long f4; uchar f5; vlong f6; vlong f7; float f8; vlong f9; uchar f10; ushort f11; };
typedef struct S3 S3;
struct S3 { double f0; char f1; uvlong f2; char f3; vlong f4; uint f5; uchar f6; };

long f0(S2 a0, S2 a1, uvlong a2, char a3, S1 a4, uvlong a5, uint a6, S3 a7);
void f1(uvlong a0, S0 a1, short a2, ushort a3, vlong a4, uvlong a5, S2 a6, vlong a7);
ushort f2(int a0, S2 a1, ushort a2, vlong a3);
S2 f3(uint a0, uvlong a1, S3 a2);
S3 f4(short a0, uint a1, uvlong a2, vlong a3, vlong a4, S1 a5, uchar a6, ushort a7);
double f5(vlong a0, float a1, float a2);
void f6(S1 a0, S1 a1, vlong a2, uchar a3, char a4, uint a5);
ushort f7(S2 a0, S1 a1, uvlong a2, S0 a3, uvlong a4, double a5);
uint f8(S3 a0, S1 a1, int a2, uint a3, ushort a4, S1 a5, char a6, S0 a7);
uvlong f9(vlong a0);
void vf(int n, ...);
S0 cb(S0 (*fn)(S0, double, vlong), S0 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %ud %ud %ud %ud %ud %ud %ud %ud %ud\n", w, s.f0[0], s.f0[1], s.f0[2], s.f0[3], s.f0[4], s.f0[5], s.f0[6], s.f0[7], s.f0[8]);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %d\n", w, s.f0);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %ud %d %ud %ud %ld %ud %lld %lld %g %lld %ud %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %g %d %llud %d %lld %ud %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6);
}

long
f0(S2 a0, S2 a1, uvlong a2, char a3, S1 a4, uvlong a5, uint a6, S3 a7)
{
	print("in f0\n");
	pS2("a0", a0);
	pS2("a1", a1);
	print("a2 uvlong %llud\n", a2);
	print("a3 char %d\n", a3);
	pS1("a4", a4);
	print("a5 uvlong %llud\n", a5);
	print("a6 uint %ud\n", a6);
	pS3("a7", a7);
	return -980254648L;
}

void
f1(uvlong a0, S0 a1, short a2, ushort a3, vlong a4, uvlong a5, S2 a6, vlong a7)
{
	print("in f1\n");
	print("a0 uvlong %llud\n", a0);
	pS0("a1", a1);
	print("a2 short %d\n", a2);
	print("a3 ushort %ud\n", a3);
	print("a4 vlong %lld\n", a4);
	print("a5 uvlong %llud\n", a5);
	pS2("a6", a6);
	print("a7 vlong %lld\n", a7);
}

ushort
f2(int a0, S2 a1, ushort a2, vlong a3)
{
	print("in f2\n");
	print("a0 int %d\n", a0);
	pS2("a1", a1);
	print("a2 ushort %ud\n", a2);
	print("a3 vlong %lld\n", a3);
	return 30916;
}

S2
f3(uint a0, uvlong a1, S3 a2)
{
	S2 r;

	print("in f3\n");
	print("a0 uint %ud\n", a0);
	print("a1 uvlong %llud\n", a1);
	pS3("a2", a2);
	r.f0 = 368538908U;
	r.f1 = -875491021;
	r.f2 = 26750;
	r.f3 = 57903;
	r.f4 = -248863712L;
	r.f5 = 145;
	r.f6 = 1262767938LL;
	r.f7 = -4609916293067227758LL;
	r.f8 = 25.500;
	r.f9 = 636142537421894LL;
	r.f10 = 6;
	r.f11 = 44983;
	return r;
}

S3
f4(short a0, uint a1, uvlong a2, vlong a3, vlong a4, S1 a5, uchar a6, ushort a7)
{
	S3 r;

	print("in f4\n");
	print("a0 short %d\n", a0);
	print("a1 uint %ud\n", a1);
	print("a2 uvlong %llud\n", a2);
	print("a3 vlong %lld\n", a3);
	print("a4 vlong %lld\n", a4);
	pS1("a5", a5);
	print("a6 uchar %ud\n", a6);
	print("a7 ushort %ud\n", a7);
	r.f0 = -21.125;
	r.f1 = 24;
	r.f2 = 1227850412540194ULL;
	r.f3 = 122;
	r.f4 = 94267589801928LL;
	r.f5 = 601219420U;
	r.f6 = 13;
	return r;
}

double
f5(vlong a0, float a1, float a2)
{
	print("in f5\n");
	print("a0 vlong %lld\n", a0);
	print("a1 float %g\n", a1);
	print("a2 float %g\n", a2);
	return 46.625;
}

void
f6(S1 a0, S1 a1, vlong a2, uchar a3, char a4, uint a5)
{
	print("in f6\n");
	pS1("a0", a0);
	pS1("a1", a1);
	print("a2 vlong %lld\n", a2);
	print("a3 uchar %ud\n", a3);
	print("a4 char %d\n", a4);
	print("a5 uint %ud\n", a5);
}

ushort
f7(S2 a0, S1 a1, uvlong a2, S0 a3, uvlong a4, double a5)
{
	print("in f7\n");
	pS2("a0", a0);
	pS1("a1", a1);
	print("a2 uvlong %llud\n", a2);
	pS0("a3", a3);
	print("a4 uvlong %llud\n", a4);
	print("a5 double %g\n", a5);
	return 64244;
}

uint
f8(S3 a0, S1 a1, int a2, uint a3, ushort a4, S1 a5, char a6, S0 a7)
{
	print("in f8\n");
	pS3("a0", a0);
	pS1("a1", a1);
	print("a2 int %d\n", a2);
	print("a3 uint %ud\n", a3);
	print("a4 ushort %ud\n", a4);
	pS1("a5", a5);
	print("a6 char %d\n", a6);
	pS0("a7", a7);
	return 2116977688U;
}

uvlong
f9(vlong a0)
{
	print("in f9\n");
	print("a0 vlong %lld\n", a0);
	return 1181161112472714ULL;
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

S0
cb(S0 (*fn)(S0, double, vlong), S0 x)
{
	S0 r;

	r = fn(x, 2.5, -7LL);
	pS0("cb got", r);
	return fn(r, -1.25, 1LL<<40);
}

#else
static void
pS0(char *w, S0 s)
{
	print("%s S0 %ud %ud %ud %ud %ud %ud %ud %ud %ud\n", w, s.f0[0], s.f0[1], s.f0[2], s.f0[3], s.f0[4], s.f0[5], s.f0[6], s.f0[7], s.f0[8]);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %d\n", w, s.f0);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %ud %d %ud %ud %ld %ud %lld %lld %g %lld %ud %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %g %d %llud %d %lld %ud %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6);
}

static S0
back(S0 x, double d, vlong v)
{
	pS0("back x", x);
	print("back %g %lld\n", d, v);
	x.f0[0] = x.f0[0] + 3;
	x.f0[1] = x.f0[1] + 3;
	x.f0[2] = x.f0[2] + 3;
	x.f0[3] = x.f0[3] + 3;
	x.f0[4] = x.f0[4] + 3;
	x.f0[5] = x.f0[5] + 3;
	x.f0[6] = x.f0[6] + 3;
	x.f0[7] = x.f0[7] + 3;
	x.f0[8] = x.f0[8] + 3;
	return x;
}

void
main(void)
{
	{
	S2 v0;
	S2 v1;
	S1 v4;
	S3 v7;
	long r;
	v0.f0 = 1751664864U;
	v0.f1 = 111133329;
	v0.f2 = 15426;
	v0.f3 = 46579;
	v0.f4 = 1631989668L;
	v0.f5 = 85;
	v0.f6 = -498410246LL;
	v0.f7 = 1005365375087084LL;
	v0.f8 = 37.000;
	v0.f9 = -4609666745784588156LL;
	v0.f10 = 202;
	v0.f11 = 33659;
	v1.f0 = 1153288884U;
	v1.f1 = -1660240997;
	v1.f2 = 48662;
	v1.f3 = 14279;
	v1.f4 = -1033613688L;
	v1.f5 = 41;
	v1.f6 = 2047517914LL;
	v1.f7 = -4611279030827428774LL;
	v1.f8 = -40.500;
	v1.f9 = 1420894867671822LL;
	v1.f10 = 158;
	v1.f11 = 1359;
	v4.f0 = 8;
	v7.f0 = -8.500;
	v7.f1 = 13;
	v7.f2 = 970441150ULL;
	v7.f3 = -111;
	v7.f4 = 1984345376LL;
	v7.f5 = 343813841U;
	v7.f6 = 130;
	r = f0(v0, v1, (uvlong)1505644592ULL, (char)-97, v4, (uvlong)372065170ULL, (uint)879017283U, v7);
	print("ret f0 long %ld\n", r);
	}
	{
	S0 v1;
	S2 v6;
	v1.f0[0] = 137;
	v1.f0[1] = 58;
	v1.f0[2] = 235;
	v1.f0[3] = 156;
	v1.f0[4] = 77;
	v1.f0[5] = 254;
	v1.f0[6] = 175;
	v1.f0[7] = 96;
	v1.f0[8] = 17;
	v6.f0 = 217468765U;
	v6.f1 = 724420878;
	v6.f2 = 17087;
	v6.f3 = 48240;
	v6.f4 = 97793569L;
	v6.f5 = 210;
	v6.f6 = -4610574317297294526LL;
	v6.f7 = 1618649908LL;
	v6.f8 = -16.375;
	v6.f9 = -485070486LL;
	v6.f10 = 71;
	v6.f11 = 35320;
	f1((uvlong)1766581732729306ULL, v1, (short)-19170, (ushort)50323, (vlong)1139949124LL, (uvlong)1646906177703718ULL, v6, (vlong)6369702LL);
	}
	{
	S2 v1;
	ushort r;
	v1.f0 = 2090680812U;
	v1.f1 = 450149277;
	v1.f2 = 13646;
	v1.f3 = 44799;
	v1.f4 = 1971005616L;
	v1.f5 = 97;
	v1.f6 = -837426194LL;
	v1.f7 = 1344382340134928LL;
	v1.f8 = 47.500;
	v1.f9 = -4611475218909991256LL;
	v1.f10 = 214;
	v1.f11 = 31879;
	r = f2((int)1492304832, v1, (ushort)15729, (vlong)358725410LL);
	print("ret f2 ushort %ud\n", r);
	}
	{
	S3 v2;
	S2 r;
	v2.f0 = 2.000;
	v2.f1 = 25;
	v2.f2 = 1309457098ULL;
	v2.f3 = -123;
	v2.f4 = 175877676LL;
	v2.f5 = 682829789U;
	v2.f6 = 142;
	r = f3((uint)1844660540U, (uvlong)204129617387022ULL, v2);
	pS2("ret f3", r);
	}
	{
	S1 v5;
	S3 r;
	v5.f0 = 51;
	r = f4((short)21767, (uint)49532600U, (uvlong)556486382454146ULL, (vlong)1063436826LL, (vlong)1570393650166824LL, v5, (uchar)124, (ushort)12077);
	pS3("ret f4", r);
	}
	{
	double r;
	r = f5((vlong)-4611312380327476974LL, (float)29.500, (float)30.375);
	print("ret f5 double %g\n", r);
	}
	{
	S1 v0;
	S1 v1;
	v0.f0 = 27;
	v1.f0 = -111;
	f6(v0, v1, (vlong)127617089850128LL, (uchar)116, (char)37, (uint)1648473046U);
	}
	{
	S2 v0;
	S1 v1;
	S0 v3;
	ushort r;
	v0.f0 = 1585300508U;
	v0.f1 = 2092252621;
	v0.f2 = 46974;
	v0.f3 = 12591;
	v0.f4 = 1465625312L;
	v0.f5 = 145;
	v0.f6 = 332045890LL;
	v0.f7 = 839000519994016LL;
	v0.f8 = -37.500;
	v0.f9 = 1852907787706694LL;
	v0.f10 = 6;
	v0.f11 = 65207;
	v1.f0 = -112;
	v3.f0[0] = 196;
	v3.f0[1] = 117;
	v3.f0[2] = 38;
	v3.f0[3] = 215;
	v3.f0[4] = 136;
	v3.f0[5] = 57;
	v3.f0[6] = 234;
	v3.f0[7] = 155;
	v3.f0[8] = 76;
	r = f7(v0, v1, (uvlong)1937656216ULL, v3, (uvlong)297125572374050ULL, (double)17.750);
	print("ret f7 ushort %ud\n", r);
	}
	{
	S3 v0;
	S1 v1;
	S1 v5;
	S0 v7;
	uint r;
	v0.f0 = 55.000;
	v0.f1 = -113;
	v0.f2 = 1754808482ULL;
	v0.f3 = 83;
	v0.f4 = -621229060LL;
	v0.f5 = 1128181173U;
	v0.f6 = 102;
	v1.f0 = 20;
	v5.f0 = -104;
	v7.f0[0] = 188;
	v7.f0[1] = 109;
	v7.f0[2] = 30;
	v7.f0[3] = 207;
	v7.f0[4] = 128;
	v7.f0[5] = 49;
	v7.f0[6] = 226;
	v7.f0[7] = 147;
	v7.f0[8] = 68;
	r = f8(v0, v1, (int)494883984, (uint)1001836097U, (ushort)18418, v5, (char)35, v7);
	print("ret f8 uint %ud\n", r);
	}
	{
	uvlong r;
	r = f9((vlong)-4609733444784684556LL);
	print("ret f9 uvlong %llud\n", r);
	}
	vf(2, (vlong)1889400915185748LL, (int)-248863712);
	{
	S0 x, r;

	x.f0[0] = 115;
	x.f0[1] = 36;
	x.f0[2] = 213;
	x.f0[3] = 134;
	x.f0[4] = 55;
	x.f0[5] = 232;
	x.f0[6] = 153;
	x.f0[7] = 74;
	x.f0[8] = 251;
	r = cb(back, x);
	pS0("ret cb", r);
	}
	exits(nil);
}
#endif
