#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { uchar f0; long f1; ushort f2; char f3; };
typedef struct S1 S1;
struct S1 { char f0; char f1; };
typedef struct S2 S2;
struct S2 { char f0; short f1; uchar f2[7]; uvlong f3; ulong f4; vlong f5; vlong f6; ulong f7; char f8; uchar f9[7]; char f10; ulong f11; uvlong f12; char f13; };
typedef struct S3 S3;
struct S3 { long f0; ulong f1; short f2; uchar f3; float f4; ushort f5; ulong f6; short f7; ushort f8; ushort f9; uchar f10[3]; uchar f11; uchar f12[2]; ulong f13; float f14; vlong f15; ushort f16; uint f17; float f18; uchar f19[4]; char f20; };

int f0(float a0);
long f1(S0 a0, S3 a1, uvlong a2, S1 a3, int a4, double a5);
uchar f2(ushort a0, S1 a1, int a2, char a3, uint a4, S1 a5);
S3 f3(vlong a0, S0 a1, uint a2);
float f4(long a0);
double f5(uvlong a0, long a1);
uint f6(ulong a0, vlong a1, uvlong a2, short a3, S2 a4, int a5);
uchar f7(float a0, float a1, float a2, vlong a3);
S2 f8(vlong a0, S1 a1, long a2);
short f9(long a0, S0 a1);
void vf(int n, ...);
S2 cb(S2 (*fn)(S2, double, vlong), S2 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %ud %ld %ud %d\n", w, s.f0, s.f1, s.f2, s.f3);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %d %d\n", w, s.f0, s.f1);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d %d %ud %ud %ud %ud %ud %ud %ud %llud %lud %lld %lld %lud %d %ud %ud %ud %ud %ud %ud %ud %d %lud %llud %d\n", w, s.f0, s.f1, s.f2[0], s.f2[1], s.f2[2], s.f2[3], s.f2[4], s.f2[5], s.f2[6], s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9[0], s.f9[1], s.f9[2], s.f9[3], s.f9[4], s.f9[5], s.f9[6], s.f10, s.f11, s.f12, s.f13);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %ld %lud %d %ud %g %ud %lud %d %ud %ud %ud %ud %ud %ud %ud %ud %lud %g %lld %ud %ud %g %ud %ud %ud %ud %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10[0], s.f10[1], s.f10[2], s.f11, s.f12[0], s.f12[1], s.f13, s.f14, s.f15, s.f16, s.f17, s.f18, s.f19[0], s.f19[1], s.f19[2], s.f19[3], s.f20);
}

int
f0(float a0)
{
	print("in f0\n");
	print("a0 float %g\n", a0);
	return 1668017576;
}

long
f1(S0 a0, S3 a1, uvlong a2, S1 a3, int a4, double a5)
{
	print("in f1\n");
	pS0("a0", a0);
	pS3("a1", a1);
	print("a2 uvlong %llud\n", a2);
	pS1("a3", a3);
	print("a4 int %d\n", a4);
	print("a5 double %g\n", a5);
	return 1604845038L;
}

uchar
f2(ushort a0, S1 a1, int a2, char a3, uint a4, S1 a5)
{
	print("in f2\n");
	print("a0 ushort %ud\n", a0);
	pS1("a1", a1);
	print("a2 int %d\n", a2);
	print("a3 char %d\n", a3);
	print("a4 uint %ud\n", a4);
	pS1("a5", a5);
	return 18;
}

S3
f3(vlong a0, S0 a1, uint a2)
{
	S3 r;

	print("in f3\n");
	print("a0 vlong %lld\n", a0);
	pS0("a1", a1);
	print("a2 uint %ud\n", a2);
	r.f0 = 1865776879L;
	r.f1 = 225245344UL;
	r.f2 = -29265;
	r.f3 = 2;
	r.f4 = -33.625;
	r.f5 = 57188;
	r.f6 = 612522261UL;
	r.f7 = 21190;
	r.f8 = 19575;
	r.f9 = 50728;
	r.f10[0] = 217;
	r.f10[1] = 138;
	r.f10[2] = 59;
	r.f11 = 236;
	r.f12[0] = 157;
	r.f12[1] = 78;
	r.f13 = 1387076095UL;
	r.f14 = -20.000;
	r.f15 = 253497433490026LL;
	r.f16 = 34578;
	r.f17 = 1267400899U;
	r.f18 = -16.500;
	r.f19[0] = 37;
	r.f19[1] = 214;
	r.f19[2] = 135;
	r.f19[3] = 56;
	r.f20 = -105;
	return r;
}

float
f4(long a0)
{
	print("in f4\n");
	print("a0 long %ld\n", a0);
	return 25.250;
}

double
f5(uvlong a0, long a1)
{
	print("in f5\n");
	print("a0 uvlong %llud\n", a0);
	print("a1 long %ld\n", a1);
	return -34.500;
}

uint
f6(ulong a0, vlong a1, uvlong a2, short a3, S2 a4, int a5)
{
	print("in f6\n");
	print("a0 ulong %lud\n", a0);
	print("a1 vlong %lld\n", a1);
	print("a2 uvlong %llud\n", a2);
	print("a3 short %d\n", a3);
	pS2("a4", a4);
	print("a5 int %d\n", a5);
	return 1247391259U;
}

uchar
f7(float a0, float a1, float a2, vlong a3)
{
	print("in f7\n");
	print("a0 float %g\n", a0);
	print("a1 float %g\n", a1);
	print("a2 float %g\n", a2);
	print("a3 vlong %lld\n", a3);
	return 249;
}

S2
f8(vlong a0, S1 a1, long a2)
{
	S2 r;

	print("in f8\n");
	print("a0 vlong %lld\n", a0);
	pS1("a1", a1);
	print("a2 long %ld\n", a2);
	r.f0 = -46;
	r.f1 = 5343;
	r.f2[0] = 144;
	r.f2[1] = 65;
	r.f2[2] = 242;
	r.f2[3] = 163;
	r.f2[4] = 84;
	r.f2[5] = 5;
	r.f2[6] = 182;
	r.f3 = 888368336097020ULL;
	r.f4 = 1395317784UL;
	r.f5 = 1902275603809698LL;
	r.f6 = -261738362LL;
	r.f7 = 768690475UL;
	r.f8 = 92;
	r.f9[0] = 141;
	r.f9[1] = 62;
	r.f9[2] = 239;
	r.f9[3] = 160;
	r.f9[4] = 81;
	r.f9[5] = 2;
	r.f9[6] = 179;
	r.f10 = 100;
	r.f11 = 1543244309UL;
	r.f12 = 2050196422ULL;
	r.f13 = 119;
	return r;
}

short
f9(long a0, S0 a1)
{
	print("in f9\n");
	print("a0 long %ld\n", a0);
	pS0("a1", a1);
	return -12317;
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %lud\n", va_arg(ap, ulong));
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
	print("%s S0 %ud %ld %ud %d\n", w, s.f0, s.f1, s.f2, s.f3);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %d %d\n", w, s.f0, s.f1);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d %d %ud %ud %ud %ud %ud %ud %ud %llud %lud %lld %lld %lud %d %ud %ud %ud %ud %ud %ud %ud %d %lud %llud %d\n", w, s.f0, s.f1, s.f2[0], s.f2[1], s.f2[2], s.f2[3], s.f2[4], s.f2[5], s.f2[6], s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9[0], s.f9[1], s.f9[2], s.f9[3], s.f9[4], s.f9[5], s.f9[6], s.f10, s.f11, s.f12, s.f13);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %ld %lud %d %ud %g %ud %lud %d %ud %ud %ud %ud %ud %ud %ud %ud %lud %g %lld %ud %ud %g %ud %ud %ud %ud %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10[0], s.f10[1], s.f10[2], s.f11, s.f12[0], s.f12[1], s.f13, s.f14, s.f15, s.f16, s.f17, s.f18, s.f19[0], s.f19[1], s.f19[2], s.f19[3], s.f20);
}

static S2
back(S2 x, double d, vlong v)
{
	pS2("back x", x);
	print("back %g %lld\n", d, v);
	x.f0 = x.f0 + 3;
	x.f1 = x.f1 + 3;
	x.f2[0] = x.f2[0] + 3;
	x.f2[1] = x.f2[1] + 3;
	x.f2[2] = x.f2[2] + 3;
	x.f2[3] = x.f2[3] + 3;
	x.f2[4] = x.f2[4] + 3;
	x.f2[5] = x.f2[5] + 3;
	x.f2[6] = x.f2[6] + 3;
	x.f3 = x.f3 + 3;
	x.f4 = x.f4 + 3;
	x.f5 = x.f5 + 3;
	x.f6 = x.f6 + 3;
	x.f7 = x.f7 + 3;
	x.f8 = x.f8 + 3;
	x.f9[0] = x.f9[0] + 3;
	x.f9[1] = x.f9[1] + 3;
	x.f9[2] = x.f9[2] + 3;
	x.f9[3] = x.f9[3] + 3;
	x.f9[4] = x.f9[4] + 3;
	x.f9[5] = x.f9[5] + 3;
	x.f9[6] = x.f9[6] + 3;
	x.f10 = x.f10 + 3;
	x.f11 = x.f11 + 3;
	x.f12 = x.f12 + 3;
	x.f13 = x.f13 + 3;
	return x;
}

void
main(void)
{
	{
	int r;
	r = f0((float)20.000);
	print("ret f0 int %d\n", r);
	}
	{
	S0 v0;
	S3 v1;
	S1 v3;
	long r;
	v0.f0 = 22;
	v0.f1 = 735723719L;
	v0.f2 = 47736;
	v0.f3 = 41;
	v1.f0 = -1777879274L;
	v1.f1 = 137347739UL;
	v1.f2 = 15436;
	v1.f3 = 253;
	v1.f4 = -15.250;
	v1.f5 = 43359;
	v1.f6 = 524624656UL;
	v1.f7 = 7361;
	v1.f8 = 5746;
	v1.f9 = 36899;
	v1.f10[0] = 212;
	v1.f10[1] = 133;
	v1.f10[2] = 54;
	v1.f11 = 231;
	v1.f12[0] = 152;
	v1.f12[1] = 73;
	v1.f13 = 1299178490UL;
	v1.f14 = -2.625;
	v1.f15 = -165599068LL;
	v1.f16 = 20749;
	v1.f17 = 1179503294U;
	v1.f18 = 2.125;
	v1.f19[0] = 32;
	v1.f19[1] = 209;
	v1.f19[2] = 130;
	v1.f19[3] = 51;
	v1.f20 = 100;
	v3.f0 = 62;
	v3.f1 = -111;
	r = f1(v0, v1, (uvlong)581127314ULL, v3, (int)1088079427, (double)23.500);
	print("ret f1 long %ld\n", r);
	}
	{
	S1 v1;
	S1 v5;
	uchar r;
	v1.f0 = 58;
	v1.f1 = -107;
	v5.f0 = 14;
	v5.f1 = 63;
	r = f2((ushort)21474, v1, (int)842059155, (char)68, (uint)1855963381U, v5);
	print("ret f2 uchar %ud\n", r);
	}
	{
	S0 v1;
	S3 r;
	v1.f0 = 59;
	v1.f1 = -152259308L;
	v1.f2 = 50333;
	v1.f3 = 78;
	r = f3((vlong)1194418446244596LL, v1, (uint)1701366976U);
	pS3("ret f3", r);
	}
	{
	float r;
	r = f4((long)1638194438L);
	print("ret f4 float %g\n", r);
	}
	{
	double r;
	r = f5((uvlong)1575021900ULL, (long)2081974013L);
	print("ret f5 double %g\n", r);
	}
	{
	S2 v4;
	uint r;
	v4.f0 = -67;
	v4.f1 = 28916;
	v4.f2[0] = 165;
	v4.f2[1] = 86;
	v4.f2[2] = 7;
	v4.f2[3] = 184;
	v4.f2[4] = 105;
	v4.f2[5] = 26;
	v4.f2[6] = 203;
	v4.f3 = 138919548ULL;
	v4.f4 = 645871661UL;
	v4.f5 = 1152823774LL;
	v4.f6 = -4610026237561060250LL;
	v4.f7 = 19244352UL;
	v4.f8 = 113;
	v4.f9[0] = 162;
	v4.f9[1] = 83;
	v4.f9[2] = 4;
	v4.f9[3] = 181;
	v4.f9[4] = 102;
	v4.f9[5] = 23;
	v4.f9[6] = 200;
	v4.f10 = 121;
	v4.f11 = 793798186UL;
	v4.f12 = 1300754201250904ULL;
	v4.f13 = 12;
	r = f6((ulong)1420425495UL, (vlong)-1927377608LL, (uvlong)286846933538226ULL, (short)26154, v4, (int)-1300750299);
	print("ret f6 uint %ud\n", r);
	}
	{
	uchar r;
	r = f7((float)49.875, (float)50.750, (float)51.625, (vlong)610950452LL);
	print("ret f7 uchar %ud\n", r);
	}
	{
	S1 v1;
	S2 r;
	v1.f0 = 122;
	v1.f1 = 43;
	r = f8((vlong)-2096885582LL, v1, (long)456354047L);
	pS2("ret f8", r);
	}
	{
	S0 v1;
	short r;
	v1.f0 = 69;
	v1.f1 = 900133622L;
	v1.f2 = 27815;
	v1.f3 = -88;
	r = f9((long)1942289177L, v1);
	print("ret f9 short %d\n", r);
	}
	vf(1, (ulong)1879116639UL);
	{
	S2 x, r;

	x.f0 = 35;
	x.f1 = 22356;
	x.f2[0] = 5;
	x.f2[1] = 182;
	x.f2[2] = 103;
	x.f2[3] = 24;
	x.f2[4] = 201;
	x.f2[5] = 122;
	x.f2[6] = 43;
	x.f3 = 989603036ULL;
	x.f4 = 1496555149UL;
	x.f5 = -2003507262LL;
	x.f6 = 362976815927188LL;
	x.f7 = 869927840UL;
	x.f8 = -81;
	x.f9[0] = 2;
	x.f9[1] = 179;
	x.f9[2] = 100;
	x.f9[3] = 21;
	x.f9[4] = 198;
	x.f9[5] = 119;
	x.f9[6] = 40;
	x.f10 = 89;
	x.f11 = 1644481674UL;
	x.f12 = 3950150850424ULL;
	x.f13 = 108;
	r = cb(back, x);
	pS2("ret cb", r);
	}
	exits(nil);
}
#endif
