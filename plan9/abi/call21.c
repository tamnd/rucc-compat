#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { uvlong f0; };
typedef struct S1 S1;
struct S1 { short f0; float f1; uchar f2[2]; char f3; };
typedef struct S2 S2;
struct S2 { int f0; uvlong f1; ushort f2; uchar f3; ulong f4; char f5; vlong f6; float f7; uvlong f8; uvlong f9; uvlong f10; uint f11; char f12[4]; };
typedef struct S3 S3;
struct S3 { ushort f0; ulong f1; double f2; ushort f3; uchar f4; };

void f0(double a0, vlong a1, S1 a2, S0 a3);
double f1(S1 a0, S2 a1, uvlong a2, S2 a3);
ushort f2(vlong a0, ushort a1, float a2);
uchar f3(long a0, char a1, short a2, char a3);
S3 f4(uchar a0);
double f5(S3 a0);
double f6(ushort a0, uint a1, uint a2, S2 a3);
float f7(S1 a0, vlong a1, uvlong a2, uvlong a3);
float f8(ulong a0, S2 a1);
void f9(uint a0, long a1);
void vf(int n, ...);
S3 cb(S3 (*fn)(S3, double, vlong), S3 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %llud\n", w, s.f0);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %d %g %ud %ud %d\n", w, s.f0, s.f1, s.f2[0], s.f2[1], s.f3);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d %llud %ud %ud %lud %d %lld %g %llud %llud %llud %ud %d %d %d %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11, s.f12[0], s.f12[1], s.f12[2], s.f12[3]);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %ud %lud %g %ud %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4);
}

void
f0(double a0, vlong a1, S1 a2, S0 a3)
{
	print("in f0\n");
	print("a0 double %g\n", a0);
	print("a1 vlong %lld\n", a1);
	pS1("a2", a2);
	pS0("a3", a3);
}

double
f1(S1 a0, S2 a1, uvlong a2, S2 a3)
{
	print("in f1\n");
	pS1("a0", a0);
	pS2("a1", a1);
	print("a2 uvlong %llud\n", a2);
	pS2("a3", a3);
	return 8.125;
}

ushort
f2(vlong a0, ushort a1, float a2)
{
	print("in f2\n");
	print("a0 vlong %lld\n", a0);
	print("a1 ushort %ud\n", a1);
	print("a2 float %g\n", a2);
	return 55745;
}

uchar
f3(long a0, char a1, short a2, char a3)
{
	print("in f3\n");
	print("a0 long %ld\n", a0);
	print("a1 char %d\n", a1);
	print("a2 short %d\n", a2);
	print("a3 char %d\n", a3);
	return 105;
}

S3
f4(uchar a0)
{
	S3 r;

	print("in f4\n");
	print("a0 uchar %ud\n", a0);
	r.f0 = 53662;
	r.f1 = 1295010639UL;
	r.f2 = -8.000;
	r.f3 = 16049;
	r.f4 = 98;
	return r;
}

double
f5(S3 a0)
{
	print("in f5\n");
	pS3("a0", a0);
	return 31.000;
}

double
f6(ushort a0, uint a1, uint a2, S2 a3)
{
	print("in f6\n");
	print("a0 ushort %ud\n", a0);
	print("a1 uint %ud\n", a1);
	print("a2 uint %ud\n", a2);
	pS2("a3", a3);
	return -9.875;
}

float
f7(S1 a0, vlong a1, uvlong a2, uvlong a3)
{
	print("in f7\n");
	pS1("a0", a0);
	print("a1 vlong %lld\n", a1);
	print("a2 uvlong %llud\n", a2);
	print("a3 uvlong %llud\n", a3);
	return 51.375;
}

float
f8(ulong a0, S2 a1)
{
	print("in f8\n");
	print("a0 ulong %lud\n", a0);
	pS2("a1", a1);
	return 14.875;
}

void
f9(uint a0, long a1)
{
	print("in f9\n");
	print("a0 uint %ud\n", a0);
	print("a1 long %ld\n", a1);
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %g\n", va_arg(ap, double));
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
	print("%s S0 %llud\n", w, s.f0);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %d %g %ud %ud %d\n", w, s.f0, s.f1, s.f2[0], s.f2[1], s.f3);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d %llud %ud %ud %lud %d %lld %g %llud %llud %llud %ud %d %d %d %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11, s.f12[0], s.f12[1], s.f12[2], s.f12[3]);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %ud %lud %g %ud %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4);
}

static S3
back(S3 x, double d, vlong v)
{
	pS3("back x", x);
	print("back %g %lld\n", d, v);
	x.f0 = x.f0 + 3;
	x.f1 = x.f1 + 3;
	x.f2 = x.f2 * 2;
	x.f3 = x.f3 + 3;
	x.f4 = x.f4 + 3;
	return x;
}

void
main(void)
{
	{
	S1 v2;
	S0 v3;
	v2.f0 = -32648;
	v2.f1 = 9.875;
	v2.f2[0] = 234;
	v2.f2[1] = 155;
	v2.f3 = 76;
	v3.f0 = 319553884ULL;
	f0((double)48.000, (vlong)228130701390058LL, v2, v3);
	}
	{
	S1 v0;
	S2 v1;
	S2 v3;
	double r;
	v0.f0 = 3367;
	v0.f1 = -9.000;
	v0.f2[0] = 137;
	v0.f2[1] = 58;
	v0.f3 = 107;
	v1.f0 = -1714065147;
	v1.f1 = 73533612ULL;
	v1.f2 = 33373;
	v1.f3 = 14;
	v1.f4 = 1594389951UL;
	v1.f5 = 112;
	v1.f6 = -4611225206515956324LL;
	v1.f7 = 17.750;
	v1.f8 = 1474719179144272ULL;
	v1.f9 = 1981666868ULL;
	v1.f10 = 341136356406006ULL;
	v1.f11 = 848087446U;
	v1.f12[0] = -71;
	v1.f12[1] = 120;
	v1.f12[2] = 41;
	v1.f12[3] = -90;
	v3.f0 = 1115689167;
	v3.f1 = 1622641280ULL;
	v3.f2 = 1073;
	v3.f3 = 226;
	v3.f4 = 996013971UL;
	v3.f5 = 68;
	v3.f6 = 2009924226754598LL;
	v3.f7 = 37.250;
	v3.f8 = 876341404016332ULL;
	v3.f9 = 1383290888ULL;
	v3.f10 = 1890248671729010ULL;
	v3.f11 = 249711466U;
	v3.f12[0] = 27;
	v3.f12[1] = -76;
	v3.f12[2] = 125;
	v3.f12[3] = 46;
	r = f1(v0, v1, (uvlong)517314738939568ULL, v3);
	print("ret f1 double %g\n", r);
	}
	{
	ushort r;
	r = f2((vlong)-4611231876415965964LL, (ushort)7322, (float)-7.625);
	print("ret f2 ushort %ud\n", r);
	}
	{
	uchar r;
	r = f3((long)1404872337L, (char)66, (short)-6643, (char)36);
	print("ret f3 uchar %ud\n", r);
	}
	{
	S3 r;
	r = f4((uchar)234);
	pS3("ret f4", r);
	}
	{
	S3 v0;
	double r;
	v0.f0 = 13360;
	v0.f1 = 1158852065UL;
	v0.f2 = 15.750;
	v0.f3 = 41283;
	v0.f4 = 244;
	r = f5(v0);
	print("ret f5 double %g\n", r);
	}
	{
	S2 v3;
	double r;
	v3.f0 = 1630882969;
	v3.f1 = 2137835082ULL;
	v3.f2 = 16379;
	v3.f3 = 172;
	v3.f4 = 1511207773UL;
	v3.f5 = 14;
	v3.f6 = 377629483885060LL;
	v3.f7 = -20.000;
	v3.f8 = 1391536751597738ULL;
	v3.f9 = 1898484690ULL;
	v3.f10 = 257953928859472ULL;
	v3.f11 = 764905268U;
	v3.f12[0] = 101;
	v3.f12[1] = -22;
	v3.f12[2] = 71;
	v3.f12[3] = 120;
	r = f6((ushort)52845, (uint)1539459102U, (uint)2046411215U, v3);
	print("ret f6 double %g\n", r);
	}
	{
	S1 v0;
	float r;
	v0.f0 = 21013;
	v0.f1 = 34.250;
	v0.f2[0] = 119;
	v0.f2[1] = 40;
	v0.f3 = -89;
	r = f7(v0, (vlong)1384866851588098LL, (uvlong)1891814810ULL, (uvlong)251284028849832ULL);
	print("ret f7 float %g\n", r);
	}
	{
	S2 v1;
	float r;
	v1.f0 = 188110737;
	v1.f1 = 695062850ULL;
	v1.f2 = 19187;
	v1.f3 = 164;
	v1.f4 = 68435541UL;
	v1.f5 = 6;
	v1.f6 = 1082343014019308LL;
	v1.f7 = 3.000;
	v1.f8 = 2096250281731986ULL;
	v1.f9 = 455712458ULL;
	v1.f10 = 962667458993720ULL;
	v1.f11 = 1469616684U;
	v1.f12[0] = 93;
	v1.f12[1] = -14;
	v1.f12[2] = 63;
	v1.f12[3] = 112;
	r = f8((ulong)1737218405UL, v1);
	print("ret f8 float %g\n", r);
	}
	{
	f9((uint)1674045867U, (long)33514332L);
	}
	vf(1, (double)-4.750);
	{
	S3 x, r;

	x.f0 = 17894;
	x.f1 = 1467662231UL;
	x.f2 = 25.000;
	x.f3 = 45817;
	x.f4 = 170;
	r = cb(back, x);
	pS3("ret cb", r);
	}
	exits(nil);
}
#endif
