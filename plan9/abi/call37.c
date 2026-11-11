#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { uvlong f0; short f1; uvlong f2; uint f3; ushort f4; char f5[3]; vlong f6; ushort f7; uchar f8[9]; vlong f9; uint f10; long f11; char f12; uchar f13; };
typedef struct S1 S1;
struct S1 { ulong f0; short f1; char f2; };
typedef struct S2 S2;
struct S2 { uint f0; uchar f1; };
typedef struct S3 S3;
struct S3 { uchar f0; ulong f1; uchar f2; float f3; int f4; short f5; char f6; };

S2 f0(ulong a0, double a1, S0 a2, int a3, S2 a4, S1 a5);
uint f1(ushort a0, S1 a1);
S1 f2(uchar a0);
void f3(int a0, ulong a1, float a2, short a3, S0 a4, uint a5, uvlong a6, float a7);
char f4(S3 a0, int a1, uchar a2, long a3, S0 a4, S0 a5, short a6, uvlong a7);
uchar f5(float a0, ushort a1);
S0 f6(S2 a0, uchar a1);
ulong f7(int a0, int a1, uvlong a2, uint a3, S1 a4, S2 a5);
short f8(S0 a0, uint a1);
int f9(int a0, float a1, S2 a2, uvlong a3);
void vf(int n, ...);
S3 cb(S3 (*fn)(S3, double, vlong), S3 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %llud %d %llud %ud %ud %d %d %d %lld %ud %ud %ud %ud %ud %ud %ud %ud %ud %ud %lld %ud %ld %d %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5[0], s.f5[1], s.f5[2], s.f6, s.f7, s.f8[0], s.f8[1], s.f8[2], s.f8[3], s.f8[4], s.f8[5], s.f8[6], s.f8[7], s.f8[8], s.f9, s.f10, s.f11, s.f12, s.f13);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %lud %d %d\n", w, s.f0, s.f1, s.f2);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %ud %ud\n", w, s.f0, s.f1);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %ud %lud %ud %g %d %d %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6);
}

S2
f0(ulong a0, double a1, S0 a2, int a3, S2 a4, S1 a5)
{
	S2 r;

	print("in f0\n");
	print("a0 ulong %lud\n", a0);
	print("a1 double %g\n", a1);
	pS0("a2", a2);
	print("a3 int %d\n", a3);
	pS2("a4", a4);
	pS1("a5", a5);
	r = a4;
	r.f0 = r.f0 + 3;
	r.f1 = r.f1 + 3;
	return r;
}

uint
f1(ushort a0, S1 a1)
{
	print("in f1\n");
	print("a0 ushort %ud\n", a0);
	pS1("a1", a1);
	return 1637676548U;
}

S1
f2(uchar a0)
{
	S1 r;

	print("in f2\n");
	print("a0 uchar %ud\n", a0);
	r.f0 = 1820524282UL;
	r.f1 = -30891;
	r.f2 = 92;
	return r;
}

void
f3(int a0, ulong a1, float a2, short a3, S0 a4, uint a5, uvlong a6, float a7)
{
	print("in f3\n");
	print("a0 int %d\n", a0);
	print("a1 ulong %lud\n", a1);
	print("a2 float %g\n", a2);
	print("a3 short %d\n", a3);
	pS0("a4", a4);
	print("a5 uint %ud\n", a5);
	print("a6 uvlong %llud\n", a6);
	print("a7 float %g\n", a7);
}

char
f4(S3 a0, int a1, uchar a2, long a3, S0 a4, S0 a5, short a6, uvlong a7)
{
	print("in f4\n");
	pS3("a0", a0);
	print("a1 int %d\n", a1);
	print("a2 uchar %ud\n", a2);
	print("a3 long %ld\n", a3);
	pS0("a4", a4);
	pS0("a5", a5);
	print("a6 short %d\n", a6);
	print("a7 uvlong %llud\n", a7);
	return -36;
}

uchar
f5(float a0, ushort a1)
{
	print("in f5\n");
	print("a0 float %g\n", a0);
	print("a1 ushort %ud\n", a1);
	return 42;
}

S0
f6(S2 a0, uchar a1)
{
	S0 r;

	print("in f6\n");
	pS2("a0", a0);
	print("a1 uchar %ud\n", a1);
	r.f0 = 455837524508478ULL;
	r.f1 = -31662;
	r.f2 = 1469744792221156ULL;
	r.f3 = 1976692496U;
	r.f4 = 26817;
	r.f5[0] = 114;
	r.f5[1] = 35;
	r.f5[2] = -84;
	r.f6 = 216486414457302LL;
	r.f7 = 51510;
	r.f8[0] = 231;
	r.f8[1] = 152;
	r.f8[2] = 73;
	r.f8[3] = 250;
	r.f8[4] = 171;
	r.f8[5] = 92;
	r.f8[6] = 13;
	r.f8[7] = 190;
	r.f8[8] = 111;
	r.f9 = -1497991712LL;
	r.f10 = 2004943825U;
	r.f11 = 364412290L;
	r.f12 = -51;
	r.f13 = 228;
	return r;
}

ulong
f7(int a0, int a1, uvlong a2, uint a3, S1 a4, S2 a5)
{
	print("in f7\n");
	print("a0 int %d\n", a0);
	print("a1 int %d\n", a1);
	print("a2 uvlong %llud\n", a2);
	print("a3 uint %ud\n", a3);
	pS1("a4", a4);
	pS2("a5", a5);
	return 1097375035UL;
}

short
f8(S0 a0, uint a1)
{
	print("in f8\n");
	pS0("a0", a0);
	print("a1 uint %ud\n", a1);
	return 7740;
}

int
f9(int a0, float a1, S2 a2, uvlong a3)
{
	print("in f9\n");
	print("a0 int %d\n", a0);
	print("a1 float %g\n", a1);
	pS2("a2", a2);
	print("a3 uvlong %llud\n", a3);
	return 696758358;
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %llud\n", va_arg(ap, uvlong));
	print("v1 %ld\n", va_arg(ap, long));
	va_end(ap);
}

S3
cb(S3 (*fn)(S3, double, vlong), S3 x)
{
	S3 r;

	r = fn(x, 2.5, -7LL);
	pS3("cb got", r);
	return fn(r, -1.25, 1LL<<40);
}

#else
static void
pS0(char *w, S0 s)
{
	print("%s S0 %llud %d %llud %ud %ud %d %d %d %lld %ud %ud %ud %ud %ud %ud %ud %ud %ud %ud %lld %ud %ld %d %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5[0], s.f5[1], s.f5[2], s.f6, s.f7, s.f8[0], s.f8[1], s.f8[2], s.f8[3], s.f8[4], s.f8[5], s.f8[6], s.f8[7], s.f8[8], s.f9, s.f10, s.f11, s.f12, s.f13);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %lud %d %d\n", w, s.f0, s.f1, s.f2);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %ud %ud\n", w, s.f0, s.f1);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %ud %lud %ud %g %d %d %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6);
}

static S3
back(S3 x, double d, vlong v)
{
	pS3("back x", x);
	print("back %g %lld\n", d, v);
	x.f0 = x.f0 + 3;
	x.f1 = x.f1 + 3;
	x.f2 = x.f2 + 3;
	x.f3 = x.f3 * 2;
	x.f4 = x.f4 + 3;
	x.f5 = x.f5 + 3;
	x.f6 = x.f6 + 3;
	return x;
}

void
main(void)
{
	{
	S0 v2;
	S2 v4;
	S1 v5;
	S2 r;
	v2.f0 = 1105999368ULL;
	v2.f1 = 12217;
	v2.f2 = 2119903594ULL;
	v2.f3 = 479372059U;
	v2.f4 = 7372;
	v2.f5[0] = -125;
	v2.f5[1] = 46;
	v2.f5[2] = 95;
	v2.f6 = -866648976LL;
	v2.f7 = 32065;
	v2.f8[0] = 242;
	v2.f8[1] = 163;
	v2.f8[2] = 84;
	v2.f8[3] = 5;
	v2.f8[4] = 182;
	v2.f8[5] = 103;
	v2.f8[6] = 24;
	v2.f8[7] = 201;
	v2.f8[8] = 122;
	v2.f9 = 671277013832LL;
	v2.f10 = 507623388U;
	v2.f11 = 1014575501L;
	v2.f12 = 62;
	v2.f13 = 239;
	v4.f0 = 507623388U;
	v4.f1 = 141;
	v5.f0 = 2056731056UL;
	v5.f1 = -13153;
	v5.f2 = 18;
	r = f0((ulong)1458355076UL, (double)-33.375, v2, (int)-324775654, v4, v5);
	pS2("ret f0", r);
	}
	{
	S1 v1;
	uint r;
	v1.f0 = 261603116UL;
	v1.f1 = -14557;
	v1.f2 = 14;
	r = f1((ushort)16640, v1);
	print("ret f1 uint %ud\n", r);
	}
	{
	S1 r;
	r = f2((uchar)70);
	pS1("ret f2", r);
	}
	{
	S0 v4;
	v4.f0 = 1684365708ULL;
	v4.f1 = -23357;
	v4.f2 = 550786286ULL;
	v4.f3 = 1057738399U;
	v4.f4 = 18512;
	v4.f5[0] = 1;
	v4.f5[1] = 50;
	v4.f5[2] = -99;
	v4.f6 = 1445015316LL;
	v4.f7 = 43205;
	v4.f8[0] = 118;
	v4.f8[1] = 39;
	v4.f8[2] = 216;
	v4.f8[3] = 137;
	v4.f8[4] = 58;
	v4.f8[5] = 235;
	v4.f8[6] = 156;
	v4.f8[7] = 77;
	v4.f8[8] = 254;
	v4.f9 = -4611106979075275066LL;
	v4.f10 = 1085989728U;
	v4.f11 = 1592941841L;
	v4.f12 = -66;
	v4.f13 = 115;
	f3((int)1085989728, (ulong)1592941841UL, (float)27.750, (short)20595, v4, (uint)966314532U, (uvlong)1473271064799942ULL, (float)31.250);
	}
	{
	S3 v0;
	S0 v4;
	S0 v5;
	char r;
	v0.f0 = 204;
	v0.f1 = 276514685UL;
	v0.f2 = 46;
	v0.f3 = -25.125;
	v0.f4 = 1797371024;
	v0.f5 = 11841;
	v0.f6 = -114;
	v4.f0 = 1318670240ULL;
	v4.f1 = -18769;
	v4.f2 = 185090818ULL;
	v4.f3 = 692042931U;
	v4.f4 = 13924;
	v4.f5[0] = 21;
	v4.f5[1] = 70;
	v4.f5[2] = -119;
	v4.f6 = 1079319848LL;
	v4.f7 = 38617;
	v4.f8[0] = 138;
	v4.f8[1] = 59;
	v4.f8[2] = 236;
	v4.f8[3] = 157;
	v4.f8[4] = 78;
	v4.f8[5] = 255;
	v4.f8[6] = 176;
	v4.f8[7] = 97;
	v4.f8[8] = 18;
	v4.f9 = -4611472675640361470LL;
	v4.f10 = 720294260U;
	v4.f11 = 1227246373L;
	v4.f12 = -86;
	v4.f13 = 135;
	v5.f0 = 720294260ULL;
	v5.f1 = 19237;
	v5.f2 = 1734198486ULL;
	v5.f3 = 93666951U;
	v5.f4 = 47160;
	v5.f5[0] = -105;
	v5.f5[1] = 26;
	v5.f5[2] = 75;
	v5.f6 = -480943868LL;
	v5.f7 = 6317;
	v5.f8[0] = 94;
	v5.f8[1] = 15;
	v5.f8[2] = 192;
	v5.f8[3] = 113;
	v5.f8[4] = 34;
	v5.f8[5] = 211;
	v5.f8[6] = 132;
	v5.f8[7] = 53;
	v5.f8[8] = 230;
	v5.f9 = 1762455102349452LL;
	v5.f10 = 121918280U;
	v5.f11 = 628870393L;
	v5.f12 = 42;
	v5.f13 = 91;
	r = f4(v0, (int)-121918280, (uchar)249, (long)1135822506L, v4, v5, (short)-16475, (uvlong)2243084ULL);
	print("ret f4 char %d\n", r);
	}
	{
	uchar r;
	r = f5((float)-23.750, (ushort)50179);
	print("ret f5 uchar %ud\n", r);
	}
	{
	S2 v0;
	S0 r;
	v0.f0 = 382850121U;
	v0.f1 = 250;
	r = f6(v0, (uchar)29);
	pS0("ret f6", r);
	}
	{
	S1 v4;
	S2 v5;
	ulong r;
	v4.f0 = 1868785251UL;
	v4.f1 = 24596;
	v4.f2 = -69;
	v5.f0 = 1270409271U;
	v5.f1 = 232;
	r = f7((int)672033291, (int)-1178985404, (uvlong)1685942574812558ULL, (uint)45405982U, v4, v5);
	print("ret f7 ulong %lud\n", r);
	}
	{
	S0 v0;
	short r;
	v0.f0 = 2129717092ULL;
	v0.f1 = 24853;
	v0.f2 = 996137670ULL;
	v0.f3 = 1503089783U;
	v0.f4 = 52776;
	v0.f5[0] = -89;
	v0.f5[1] = 10;
	v0.f5[2] = 59;
	v0.f6 = -1890366700LL;
	v0.f7 = 11933;
	v0.f8[0] = 78;
	v0.f8[1] = 255;
	v0.f8[2] = 176;
	v0.f8[3] = 97;
	v0.f8[4] = 18;
	v0.f8[5] = 195;
	v0.f8[6] = 116;
	v0.f8[7] = 37;
	v0.f8[8] = 214;
	v0.f9 = 1024392072167004LL;
	v0.f10 = 1531341112U;
	v0.f11 = 2038293225L;
	v0.f12 = 26;
	v0.f13 = 75;
	r = f8(v0, (uint)1531341112U);
	print("ret f8 short %d\n", r);
	}
	{
	S2 v2;
	int r;
	v2.f0 = 1468168574U;
	v2.f1 = 47;
	r = f9((int)869792594, (float)40.625, v2, (uvlong)1883696820ULL);
	print("ret f9 int %d\n", r);
	}
	vf(2, (uvlong)1820524282ULL, (long)-179992747L);
	{
	S3 x, r;

	x.f0 = 62;
	x.f1 = 1170361071UL;
	x.f2 = 160;
	x.f3 = 12.875;
	x.f4 = -543733762;
	x.f5 = 12723;
	x.f6 = 100;
	r = cb(back, x);
	pS3("ret cb", r);
	}
	exits(nil);
}
#endif
