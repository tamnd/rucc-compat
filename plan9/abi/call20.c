#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { ulong f0; ushort f1; char f2; char f3; };
typedef struct S1 S1;
struct S1 { double f0; uchar f1; };
typedef struct S2 S2;
struct S2 { int f0; char f1[8]; short f2; short f3; char f4[4]; int f5; double f6; short f7; char f8[8]; float f9; ushort f10; short f11; ulong f12; ulong f13; int f14; short f15; };
typedef struct S3 S3;
struct S3 { short f0; int f1; short f2; };

char f0(uvlong a0, float a1, uint a2, vlong a3, S2 a4, ulong a5);
long f1(long a0);
uvlong f2(S2 a0, S1 a1, ulong a2, uchar a3);
S2 f3(vlong a0, uvlong a1, ulong a2, short a3, S3 a4, vlong a5, ushort a6, S3 a7);
void f4(short a0, uchar a1, S2 a2, S3 a3, S2 a4, uvlong a5, vlong a6, ushort a7);
S3 f5(S2 a0, int a1, int a2);
char f6(S1 a0);
int f7(uint a0, float a1, ushort a2, S1 a3);
double f8(S2 a0, int a1, vlong a2);
float f9(int a0, uvlong a1, vlong a2, long a3, short a4, float a5, S3 a6, uchar a7);
void vf(int n, ...);
S2 cb(S2 (*fn)(S2, double, vlong), S2 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %lud %ud %d %d\n", w, s.f0, s.f1, s.f2, s.f3);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %g %ud\n", w, s.f0, s.f1);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %g %d %d %d %d %d %d %d %d %d %g %ud %d %lud %lud %d %d\n", w, s.f0, s.f1[0], s.f1[1], s.f1[2], s.f1[3], s.f1[4], s.f1[5], s.f1[6], s.f1[7], s.f2, s.f3, s.f4[0], s.f4[1], s.f4[2], s.f4[3], s.f5, s.f6, s.f7, s.f8[0], s.f8[1], s.f8[2], s.f8[3], s.f8[4], s.f8[5], s.f8[6], s.f8[7], s.f9, s.f10, s.f11, s.f12, s.f13, s.f14, s.f15);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %d %d %d\n", w, s.f0, s.f1, s.f2);
}

char
f0(uvlong a0, float a1, uint a2, vlong a3, S2 a4, ulong a5)
{
	print("in f0\n");
	print("a0 uvlong %llud\n", a0);
	print("a1 float %g\n", a1);
	print("a2 uint %ud\n", a2);
	print("a3 vlong %lld\n", a3);
	pS2("a4", a4);
	print("a5 ulong %lud\n", a5);
	return 120;
}

long
f1(long a0)
{
	print("in f1\n");
	print("a0 long %ld\n", a0);
	return 1366807510L;
}

uvlong
f2(S2 a0, S1 a1, ulong a2, uchar a3)
{
	print("in f2\n");
	pS2("a0", a0);
	pS1("a1", a1);
	print("a2 ulong %lud\n", a2);
	print("a3 uchar %ud\n", a3);
	return 1303634972ULL;
}

S2
f3(vlong a0, uvlong a1, ulong a2, short a3, S3 a4, vlong a5, ushort a6, S3 a7)
{
	S2 r;

	print("in f3\n");
	print("a0 vlong %lld\n", a0);
	print("a1 uvlong %llud\n", a1);
	print("a2 ulong %lud\n", a2);
	print("a3 short %d\n", a3);
	pS3("a4", a4);
	print("a5 vlong %lld\n", a5);
	print("a6 ushort %ud\n", a6);
	pS3("a7", a7);
	r.f0 = -1395058839;
	r.f1[0] = 72;
	r.f1[1] = 121;
	r.f1[2] = -42;
	r.f1[3] = 91;
	r.f1[4] = 12;
	r.f1[5] = -61;
	r.f1[6] = 110;
	r.f1[7] = 31;
	r.f2 = -12240;
	r.f3 = 10625;
	r.f4[0] = 50;
	r.f4[1] = -99;
	r.f4[2] = 20;
	r.f4[3] = 69;
	r.f5 = -409405942;
	r.f6 = -6.125;
	r.f7 = 32088;
	r.f8[0] = -9;
	r.f8[1] = 58;
	r.f8[2] = 107;
	r.f8[3] = -28;
	r.f8[4] = 77;
	r.f8[5] = 126;
	r.f8[6] = -47;
	r.f8[7] = 96;
	r.f9 = 4.875;
	r.f10 = 48706;
	r.f11 = 14323;
	r.f12 = 1064284580UL;
	r.f13 = 1571236693UL;
	r.f14 = 2078188806;
	r.f15 = 7863;
	return r;
}

void
f4(short a0, uchar a1, S2 a2, S3 a3, S2 a4, uvlong a5, vlong a6, ushort a7)
{
	print("in f4\n");
	print("a0 short %d\n", a0);
	print("a1 uchar %ud\n", a1);
	pS2("a2", a2);
	pS3("a3", a3);
	pS2("a4", a4);
	print("a5 uvlong %llud\n", a5);
	print("a6 vlong %lld\n", a6);
	print("a7 ushort %ud\n", a7);
}

S3
f5(S2 a0, int a1, int a2)
{
	S3 r;

	print("in f5\n");
	pS2("a0", a0);
	print("a1 int %d\n", a1);
	print("a2 int %d\n", a2);
	r.f0 = 22912;
	r.f1 = -1198871345;
	r.f2 = 19682;
	return r;
}

char
f6(S1 a0)
{
	print("in f6\n");
	pS1("a0", a0);
	return 111;
}

int
f7(uint a0, float a1, ushort a2, S1 a3)
{
	print("in f7\n");
	print("a0 uint %ud\n", a0);
	print("a1 float %g\n", a1);
	print("a2 ushort %ud\n", a2);
	pS1("a3", a3);
	return 671909592;
}

double
f8(S2 a0, int a1, vlong a2)
{
	print("in f8\n");
	pS2("a0", a0);
	print("a1 int %d\n", a1);
	print("a2 vlong %lld\n", a2);
	return 51.500;
}

float
f9(int a0, uvlong a1, vlong a2, long a3, short a4, float a5, S3 a6, uchar a7)
{
	print("in f9\n");
	print("a0 int %d\n", a0);
	print("a1 uvlong %llud\n", a1);
	print("a2 vlong %lld\n", a2);
	print("a3 long %ld\n", a3);
	print("a4 short %d\n", a4);
	print("a5 float %g\n", a5);
	pS3("a6", a6);
	print("a7 uchar %ud\n", a7);
	return 13.125;
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %lud\n", va_arg(ap, ulong));
	print("v1 %ud\n", va_arg(ap, uint));
	print("v2 %d\n", va_arg(ap, int));
	print("v3 %ld\n", va_arg(ap, long));
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
	print("%s S0 %lud %ud %d %d\n", w, s.f0, s.f1, s.f2, s.f3);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %g %ud\n", w, s.f0, s.f1);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %g %d %d %d %d %d %d %d %d %d %g %ud %d %lud %lud %d %d\n", w, s.f0, s.f1[0], s.f1[1], s.f1[2], s.f1[3], s.f1[4], s.f1[5], s.f1[6], s.f1[7], s.f2, s.f3, s.f4[0], s.f4[1], s.f4[2], s.f4[3], s.f5, s.f6, s.f7, s.f8[0], s.f8[1], s.f8[2], s.f8[3], s.f8[4], s.f8[5], s.f8[6], s.f8[7], s.f9, s.f10, s.f11, s.f12, s.f13, s.f14, s.f15);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %d %d %d\n", w, s.f0, s.f1, s.f2);
}

static S2
back(S2 x, double d, vlong v)
{
	pS2("back x", x);
	print("back %g %lld\n", d, v);
	x.f0 = x.f0 + 3;
	x.f1[0] = x.f1[0] + 3;
	x.f1[1] = x.f1[1] + 3;
	x.f1[2] = x.f1[2] + 3;
	x.f1[3] = x.f1[3] + 3;
	x.f1[4] = x.f1[4] + 3;
	x.f1[5] = x.f1[5] + 3;
	x.f1[6] = x.f1[6] + 3;
	x.f1[7] = x.f1[7] + 3;
	x.f2 = x.f2 + 3;
	x.f3 = x.f3 + 3;
	x.f4[0] = x.f4[0] + 3;
	x.f4[1] = x.f4[1] + 3;
	x.f4[2] = x.f4[2] + 3;
	x.f4[3] = x.f4[3] + 3;
	x.f5 = x.f5 + 3;
	x.f6 = x.f6 * 2;
	x.f7 = x.f7 + 3;
	x.f8[0] = x.f8[0] + 3;
	x.f8[1] = x.f8[1] + 3;
	x.f8[2] = x.f8[2] + 3;
	x.f8[3] = x.f8[3] + 3;
	x.f8[4] = x.f8[4] + 3;
	x.f8[5] = x.f8[5] + 3;
	x.f8[6] = x.f8[6] + 3;
	x.f8[7] = x.f8[7] + 3;
	x.f9 = x.f9 * 2;
	x.f10 = x.f10 + 3;
	x.f11 = x.f11 + 3;
	x.f12 = x.f12 + 3;
	x.f13 = x.f13 + 3;
	x.f14 = x.f14 + 3;
	x.f15 = x.f15 + 3;
	return x;
}

void
main(void)
{
	{
	S2 v4;
	char r;
	v4.f0 = 771957792;
	v4.f1[0] = -81;
	v4.f1[1] = 2;
	v4.f1[2] = 51;
	v4.f1[3] = -100;
	v4.f1[4] = 21;
	v4.f1[5] = 70;
	v4.f1[6] = -119;
	v4.f1[7] = 40;
	v4.f2 = 27481;
	v4.f3 = -25866;
	v4.f4[0] = 59;
	v4.f4[1] = 108;
	v4.f4[2] = -29;
	v4.f4[3] = 78;
	v4.f5 = 1933788543;
	v4.f6 = -6.000;
	v4.f7 = 14561;
	v4.f8[0] = 18;
	v4.f8[1] = -67;
	v4.f8[2] = 116;
	v4.f8[3] = 37;
	v4.f8[4] = -86;
	v4.f8[5] = 7;
	v4.f8[6] = 56;
	v4.f8[7] = -105;
	v4.f9 = 4.750;
	v4.f10 = 63947;
	v4.f11 = -29564;
	v4.f12 = 441183533UL;
	v4.f13 = 948135646UL;
	v4.f14 = -1455087759;
	v4.f15 = 23104;
	r = f0((uvlong)173581812ULL, (float)-1.375, (uint)1187486038U, (vlong)1694443234314460LL, v4, (ulong)53906616UL);
	print("ret f0 char %d\n", r);
	}
	{
	long r;
	r = f1((long)2138217726L);
	print("ret f1 long %ld\n", r);
	}
	{
	S2 v0;
	S1 v1;
	uvlong r;
	v0.f0 = -2075045188;
	v0.f1[0] = 117;
	v0.f1[1] = 38;
	v0.f1[2] = -87;
	v0.f1[3] = 8;
	v0.f1[4] = 57;
	v0.f1[5] = -106;
	v0.f1[6] = 27;
	v0.f1[7] = 76;
	v0.f2 = -29821;
	v0.f3 = 28206;
	v0.f4[0] = 95;
	v0.f4[1] = -16;
	v0.f4[2] = 65;
	v0.f4[3] = 114;
	v0.f5 = -1089392291;
	v0.f6 = -3.500;
	v0.f7 = 16901;
	v0.f8[0] = -54;
	v0.f8[1] = 103;
	v0.f8[2] = 24;
	v0.f8[3] = -73;
	v0.f8[4] = 122;
	v0.f8[5] = 43;
	v0.f8[6] = -92;
	v0.f8[7] = 13;
	v0.f9 = 7.250;
	v0.f10 = 33519;
	v0.f11 = 31904;
	v0.f12 = 1744270929UL;
	v0.f13 = 103739394UL;
	v0.f14 = 610691507;
	v0.f15 = 25444;
	v1.f0 = 1.000;
	v1.f1 = 201;
	r = f2(v0, v1, (ulong)878293228UL, (uchar)157);
	print("ret f2 uvlong %llud\n", r);
	}
	{
	S3 v4;
	S3 v7;
	S2 r;
	v4.f0 = 15075;
	v4.f1 = 1829024916;
	v4.f2 = -11845;
	v7.f0 = -15543;
	v7.f1 = 1230648936;
	v7.f2 = 12313;
	r = f3((vlong)125321218962536LL, (uvlong)632272956ULL, (ulong)1139225069UL, (short)11166, v4, (vlong)-4611680372763450970LL, (ushort)40704, v7);
	pS2("ret f3", r);
	}
	{
	S2 v2;
	S3 v3;
	S2 v4;
	v2.f0 = -449425222;
	v2.f1[0] = 119;
	v2.f1[1] = 40;
	v2.f1[2] = -89;
	v2.f1[3] = 10;
	v2.f1[4] = 59;
	v2.f1[5] = -108;
	v2.f1[6] = 29;
	v2.f1[7] = 78;
	v2.f2 = -30335;
	v2.f3 = 28720;
	v2.f4[0] = 97;
	v2.f4[1] = -18;
	v2.f4[2] = 67;
	v2.f4[3] = 116;
	v2.f5 = -1611255973;
	v2.f6 = -35.250;
	v2.f7 = 17415;
	v2.f8[0] = -56;
	v2.f8[1] = 105;
	v2.f8[2] = 26;
	v2.f8[3] = -75;
	v2.f8[4] = 124;
	v2.f8[5] = 45;
	v2.f8[6] = -94;
	v2.f8[7] = 15;
	v2.f9 = -25.000;
	v2.f10 = 34033;
	v2.f11 = 32418;
	v2.f12 = 118650963UL;
	v2.f13 = 625603076UL;
	v2.f14 = 1132555189;
	v2.f15 = 25958;
	v3.f0 = 12570;
	v3.f1 = -358001355;
	v3.f2 = 9340;
	v4.f0 = 1400156910;
	v4.f1[0] = 31;
	v4.f1[1] = -80;
	v4.f1[2] = 1;
	v4.f1[3] = 50;
	v4.f1[4] = -99;
	v4.f1[5] = 20;
	v4.f1[6] = 69;
	v4.f1[7] = -118;
	v4.f2 = 31271;
	v4.f3 = 29656;
	v4.f4[0] = -9;
	v4.f4[1] = 58;
	v4.f4[2] = 107;
	v4.f4[3] = -28;
	v4.f5 = 414504013;
	v4.f6 = 5.250;
	v4.f7 = -18351;
	v4.f8[0] = 96;
	v4.f8[1] = 17;
	v4.f8[2] = -66;
	v4.f8[3] = 115;
	v4.f8[4] = 36;
	v4.f8[5] = -85;
	v4.f8[6] = 6;
	v4.f8[7] = 55;
	v4.f9 = 15.000;
	v4.f10 = 34969;
	v4.f11 = 586;
	v4.f12 = 1069382651UL;
	v4.f13 = 1576334764UL;
	v4.f14 = 2083286877;
	v4.f15 = -26894;
	f4((short)-13506, (uchar)115, v2, v3, v4, (uvlong)1815685156ULL, (vlong)-4611510864280927048LL, (ushort)7046);
	}
	{
	S2 v0;
	S3 r;
	v0.f0 = -618933196;
	v0.f1[0] = 125;
	v0.f1[1] = 46;
	v0.f1[2] = -95;
	v0.f1[3] = 16;
	v0.f1[4] = 65;
	v0.f1[5] = -114;
	v0.f1[6] = 35;
	v0.f1[7] = 84;
	v0.f2 = -29445;
	v0.f3 = 27830;
	v0.f4[0] = 103;
	v0.f4[1] = -24;
	v0.f4[2] = 73;
	v0.f4[3] = 122;
	v0.f5 = -1780763947;
	v0.f6 = -30.500;
	v0.f7 = 16525;
	v0.f8[0] = -62;
	v0.f8[1] = 111;
	v0.f8[2] = 32;
	v0.f8[3] = -81;
	v0.f8[4] = 2;
	v0.f8[5] = 51;
	v0.f8[6] = -100;
	v0.f8[7] = 21;
	v0.f9 = -20.250;
	v0.f10 = 375;
	v0.f11 = 31528;
	v0.f12 = 288158937UL;
	v0.f13 = 795111050UL;
	v0.f14 = 1302063163;
	v0.f15 = 25068;
	r = f5(v0, (int)20557216, (int)-527509329);
	pS3("ret f5", r);
	}
	{
	S1 v0;
	char r;
	v0.f0 = 13.125;
	v0.f1 = 72;
	r = f6(v0);
	print("ret f6 char %d\n", r);
	}
	{
	S1 v3;
	int r;
	v3.f0 = -27.000;
	v3.f1 = 177;
	r = f7((uint)844943828U, (float)-6.375, (ushort)50486, v3);
	print("ret f7 int %d\n", r);
	}
	{
	S2 v0;
	double r;
	v0.f0 = 1795675516;
	v0.f1[0] = -45;
	v0.f1[1] = 94;
	v0.f1[2] = 15;
	v0.f1[3] = -64;
	v0.f1[4] = 113;
	v0.f1[5] = 34;
	v0.f1[6] = -83;
	v0.f1[7] = 4;
	v0.f2 = 7349;
	v0.f3 = -5734;
	v0.f4[0] = 23;
	v0.f4[1] = 72;
	v0.f4[2] = -121;
	v0.f4[3] = 42;
	v0.f5 = 810022619;
	v0.f6 = 49.500;
	v0.f7 = 27197;
	v0.f8[0] = 110;
	v0.f8[1] = -31;
	v0.f8[2] = 80;
	v0.f8[3] = 1;
	v0.f8[4] = -50;
	v0.f8[5] = 99;
	v0.f8[6] = 20;
	v0.f8[7] = -69;
	v0.f9 = -38.250;
	v0.f10 = 43815;
	v0.f11 = -9432;
	v0.f12 = 1464901257UL;
	v0.f13 = 1971853370UL;
	v0.f14 = -331321835;
	v0.f15 = 2972;
	r = f8(v0, (int)1197299536, (vlong)1704256761754954LL);
	print("ret f8 double %g\n", r);
	}
	{
	S3 v6;
	float r;
	v6.f0 = 24903;
	v6.f1 = 547576;
	v6.f2 = -21673;
	r = f9((int)-1042703131, (uvlong)1549655244ULL, (vlong)2056613526822078LL, (long)-416075822L, (short)18911, (float)20.000, v6, (uchar)65);
	print("ret f9 float %g\n", r);
	}
	vf(4, (ulong)1873759623UL, (uint)233228088U, (int)740180201, (long)1247132314L);
	{
	S2 x, r;

	x.f0 = 716644299;
	x.f1[0] = -124;
	x.f1[1] = 45;
	x.f1[2] = 94;
	x.f1[3] = -15;
	x.f1[4] = 64;
	x.f1[5] = 113;
	x.f1[6] = -34;
	x.f1[7] = 83;
	x.f2 = 26372;
	x.f3 = -24757;
	x.f4[0] = 102;
	x.f4[1] = 23;
	x.f4[2] = -72;
	x.f4[3] = 121;
	x.f5 = 1878475050;
	x.f6 = 5.625;
	x.f7 = 13452;
	x.f8[0] = 61;
	x.f8[1] = -110;
	x.f8[2] = 31;
	x.f8[3] = 80;
	x.f8[4] = -1;
	x.f8[5] = 50;
	x.f8[6] = 99;
	x.f8[7] = -20;
	x.f9 = 15.375;
	x.f10 = 62838;
	x.f11 = -28455;
	x.f12 = 385870040UL;
	x.f13 = 892822153UL;
	x.f14 = -1399774266;
	x.f15 = 21995;
	r = cb(back, x);
	pS2("ret cb", r);
	}
	exits(nil);
}
#endif
