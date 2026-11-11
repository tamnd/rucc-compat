#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { short f0; long f1; char f2; char f3[6]; short f4; ushort f5; double f6; uvlong f7; ushort f8; uvlong f9; long f10; uchar f11[2]; ulong f12; float f13; int f14; uchar f15; char f16; };
typedef struct S1 S1;
struct S1 { ushort f0; };
typedef struct S2 S2;
struct S2 { int f0; char f1; uchar f2; };
typedef struct S3 S3;
struct S3 { long f0; int f1; char f2[2]; uchar f3; uchar f4[4]; };

long f0(uint a0, uvlong a1, vlong a2, S0 a3, short a4, float a5, S2 a6, float a7);
long f1(uvlong a0);
uvlong f2(uint a0, vlong a1, long a2);
int f3(vlong a0);
S3 f4(S1 a0, uvlong a1);
double f5(S1 a0);
uchar f6(S0 a0, uint a1);
S3 f7(ushort a0, float a1);
short f8(short a0, uint a1, ulong a2, uvlong a3);
uchar f9(ushort a0, int a1, double a2);
void vf(int n, ...);
S2 cb(S2 (*fn)(S2, double, vlong), S2 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %d %ld %d %d %d %d %d %d %d %d %ud %g %llud %ud %llud %ld %ud %ud %lud %g %d %ud %d\n", w, s.f0, s.f1, s.f2, s.f3[0], s.f3[1], s.f3[2], s.f3[3], s.f3[4], s.f3[5], s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11[0], s.f11[1], s.f12, s.f13, s.f14, s.f15, s.f16);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %ud\n", w, s.f0);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d %d %ud\n", w, s.f0, s.f1, s.f2);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %ld %d %d %d %ud %ud %ud %ud %ud\n", w, s.f0, s.f1, s.f2[0], s.f2[1], s.f3, s.f4[0], s.f4[1], s.f4[2], s.f4[3]);
}

long
f0(uint a0, uvlong a1, vlong a2, S0 a3, short a4, float a5, S2 a6, float a7)
{
	print("in f0\n");
	print("a0 uint %ud\n", a0);
	print("a1 uvlong %llud\n", a1);
	print("a2 vlong %lld\n", a2);
	pS0("a3", a3);
	print("a4 short %d\n", a4);
	print("a5 float %g\n", a5);
	pS2("a6", a6);
	print("a7 float %g\n", a7);
	return 1168324152L;
}

long
f1(uvlong a0)
{
	print("in f1\n");
	print("a0 uvlong %llud\n", a0);
	return -295676571L;
}

uvlong
f2(uint a0, vlong a1, long a2)
{
	print("in f2\n");
	print("a0 uint %ud\n", a0);
	print("a1 vlong %lld\n", a1);
	print("a2 long %ld\n", a2);
	return 232504730512106ULL;
}

int
f3(vlong a0)
{
	print("in f3\n");
	print("a0 vlong %lld\n", a0);
	return -1183235721;
}

S3
f4(S1 a0, uvlong a1)
{
	S3 r;

	print("in f4\n");
	pS1("a0", a0);
	print("a1 uvlong %llud\n", a1);
	r.f0 = 1964459435L;
	r.f1 = 323927900;
	r.f2[0] = -13;
	r.f2[1] = 62;
	r.f3 = 111;
	r.f4[0] = 32;
	r.f4[1] = 209;
	r.f4[2] = 130;
	r.f4[3] = 51;
	return r;
}

double
f5(S1 a0)
{
	print("in f5\n");
	pS1("a0", a0);
	return 8.875;
}

uchar
f6(S0 a0, uint a1)
{
	print("in f6\n");
	pS0("a0", a0);
	print("a1 uint %ud\n", a1);
	return 82;
}

S3
f7(ushort a0, float a1)
{
	S3 r;

	print("in f7\n");
	print("a0 ushort %ud\n", a0);
	print("a1 float %g\n", a1);
	r.f0 = -1620345416L;
	r.f1 = 2127297529;
	r.f2[0] = 42;
	r.f2[1] = -91;
	r.f3 = 12;
	r.f4[0] = 189;
	r.f4[1] = 110;
	r.f4[2] = 31;
	r.f4[3] = 208;
	return r;
}

short
f8(short a0, uint a1, ulong a2, uvlong a3)
{
	print("in f8\n");
	print("a0 short %d\n", a0);
	print("a1 uint %ud\n", a1);
	print("a2 ulong %lud\n", a2);
	print("a3 uvlong %llud\n", a3);
	return 5475;
}

uchar
f9(ushort a0, int a1, double a2)
{
	print("in f9\n");
	print("a0 ushort %ud\n", a0);
	print("a1 int %d\n", a1);
	print("a2 double %g\n", a2);
	return 188;
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %d\n", va_arg(ap, int));
	print("v1 %lld\n", va_arg(ap, vlong));
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
	print("%s S0 %d %ld %d %d %d %d %d %d %d %d %ud %g %llud %ud %llud %ld %ud %ud %lud %g %d %ud %d\n", w, s.f0, s.f1, s.f2, s.f3[0], s.f3[1], s.f3[2], s.f3[3], s.f3[4], s.f3[5], s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11[0], s.f11[1], s.f12, s.f13, s.f14, s.f15, s.f16);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %ud\n", w, s.f0);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d %d %ud\n", w, s.f0, s.f1, s.f2);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %ld %d %d %d %ud %ud %ud %ud %ud\n", w, s.f0, s.f1, s.f2[0], s.f2[1], s.f3, s.f4[0], s.f4[1], s.f4[2], s.f4[3]);
}

static S2
back(S2 x, double d, vlong v)
{
	pS2("back x", x);
	print("back %g %lld\n", d, v);
	x.f0 = x.f0 + 3;
	x.f1 = x.f1 + 3;
	x.f2 = x.f2 + 3;
	return x;
}

void
main(void)
{
	{
	S0 v3;
	S2 v6;
	long r;
	v3.f0 = 32608;
	v3.f1 = 299202833L;
	v3.f2 = -66;
	v3.f3[0] = 115;
	v3.f3[1] = 36;
	v3.f3[2] = -85;
	v3.f3[3] = 6;
	v3.f3[4] = 55;
	v3.f3[5] = -104;
	v3.f4 = 18073;
	v3.f5 = 49226;
	v3.f6 = 35.625;
	v3.f7 = 1580708780ULL;
	v3.f8 = 11613;
	v3.f9 = 447129358ULL;
	v3.f10 = 954081471L;
	v3.f11[0] = 112;
	v3.f11[1] = 33;
	v3.f12 = 327454162UL;
	v3.f13 = 43.625;
	v3.f14 = -1341358388;
	v3.f15 = 229;
	v3.f16 = 22;
	v6.f0 = -1341358388;
	v6.f1 = 101;
	v6.f2 = 150;
	r = f0((uint)742982408U, (uvlong)1249938270803570ULL, (vlong)1756886634LL, v3, (short)28699, (float)-29.500, v6, (float)-28.375);
	print("ret f0 long %ld\n", r);
	}
	{
	long r;
	r = f1((uvlong)1067089988260368ULL);
	print("ret f1 long %ld\n", r);
	}
	{
	uvlong r;
	r = f2((uint)1003914249U, (vlong)-1510866362LL, (long)2017818475L);
	print("ret f2 uvlong %llud\n", r);
	}
	{
	int r;
	r = f3((vlong)-4609731366626450100LL);
	print("ret f3 int %d\n", r);
	}
	{
	S1 v0;
	S3 r;
	v0.f0 = 38903;
	r = f4(v0, (uvlong)1293101298292264ULL);
	pS3("ret f4", r);
	}
	{
	S1 v0;
	double r;
	v0.f0 = 10769;
	r = f5(v0);
	print("ret f5 double %g\n", r);
	}
	{
	S0 v0;
	uchar r;
	v0.f0 = -17018;
	v0.f1 = 568376363L;
	v0.f2 = 92;
	v0.f3[0] = -13;
	v0.f3[1] = 62;
	v0.f3[2] = 111;
	v0.f3[3] = -32;
	v0.f3[4] = 81;
	v0.f3[5] = 2;
	v0.f4 = -2483;
	v0.f5 = 868;
	v0.f6 = -39.375;
	v0.f7 = 1849882310ULL;
	v0.f8 = 28791;
	v0.f9 = 716302888ULL;
	v0.f10 = -1223255001L;
	v0.f11[0] = 138;
	v0.f11[1] = 59;
	v0.f12 = 596627692UL;
	v0.f13 = -31.375;
	v0.f14 = 1610531918;
	v0.f15 = 255;
	v0.f16 = 48;
	r = f6(v0, (uint)1610531918U);
	print("ret f6 uchar %ud\n", r);
	}
	{
	S3 r;
	r = f7((ushort)54420, (float)9.375);
	pS3("ret f7", r);
	}
	{
	short r;
	r = f8((short)24203, (uint)350607420U, (ulong)857559533UL, (uvlong)1364511646ULL);
	print("ret f8 short %d\n", r);
	}
	{
	uchar r;
	r = f9((ushort)56292, (int)1808291221, (double)-7.250);
	print("ret f9 uchar %ud\n", r);
	}
	vf(2, (int)104587148, (vlong)611541095617790LL);
	{
	S2 x, r;

	x.f0 = 1094955472;
	x.f1 = 1;
	x.f2 = 50;
	r = cb(back, x);
	pS2("ret cb", r);
	}
	exits(nil);
}
#endif
