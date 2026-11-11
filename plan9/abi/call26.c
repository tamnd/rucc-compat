#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { char f0; short f1; ushort f2; };
typedef struct S1 S1;
struct S1 { ushort f0; uchar f1[4]; ushort f2; double f3; vlong f4; short f5; uint f6; short f7; uint f8; vlong f9; char f10[3]; char f11; };
typedef struct S2 S2;
struct S2 { char f0; };
typedef struct S3 S3;
struct S3 { float f0; char f1[2]; double f2; ushort f3; };

double f0(ushort a0, uint a1, S0 a2);
S1 f1(S1 a0, uint a1);
int f2(S2 a0, double a1, uvlong a2, vlong a3);
S3 f3(S2 a0);
S0 f4(uchar a0);
char f5(short a0, ushort a1);
int f6(S1 a0, S3 a1, double a2);
void f7(vlong a0);
S2 f8(int a0, float a1);
vlong f9(ulong a0);
void vf(int n, ...);
S3 cb(S3 (*fn)(S3, double, vlong), S3 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %d %d %ud\n", w, s.f0, s.f1, s.f2);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %ud %ud %ud %ud %ud %ud %g %lld %d %ud %d %ud %lld %d %d %d %d\n", w, s.f0, s.f1[0], s.f1[1], s.f1[2], s.f1[3], s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10[0], s.f10[1], s.f10[2], s.f11);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d\n", w, s.f0);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %g %d %d %g %ud\n", w, s.f0, s.f1[0], s.f1[1], s.f2, s.f3);
}

double
f0(ushort a0, uint a1, S0 a2)
{
	print("in f0\n");
	print("a0 ushort %ud\n", a0);
	print("a1 uint %ud\n", a1);
	pS0("a2", a2);
	return -18.000;
}

S1
f1(S1 a0, uint a1)
{
	S1 r;

	print("in f1\n");
	pS1("a0", a0);
	print("a1 uint %ud\n", a1);
	r = a0;
	r.f0 = r.f0 + 3;
	r.f1[0] = r.f1[0] + 3;
	r.f1[1] = r.f1[1] + 3;
	r.f1[2] = r.f1[2] + 3;
	r.f1[3] = r.f1[3] + 3;
	r.f2 = r.f2 + 3;
	r.f3 = r.f3 * 2;
	r.f4 = r.f4 + 3;
	r.f5 = r.f5 + 3;
	r.f6 = r.f6 + 3;
	r.f7 = r.f7 + 3;
	r.f8 = r.f8 + 3;
	r.f9 = r.f9 + 3;
	r.f10[0] = r.f10[0] + 3;
	r.f10[1] = r.f10[1] + 3;
	r.f10[2] = r.f10[2] + 3;
	r.f11 = r.f11 + 3;
	return r;
}

int
f2(S2 a0, double a1, uvlong a2, vlong a3)
{
	print("in f2\n");
	pS2("a0", a0);
	print("a1 double %g\n", a1);
	print("a2 uvlong %llud\n", a2);
	print("a3 vlong %lld\n", a3);
	return 60235085;
}

S3
f3(S2 a0)
{
	S3 r;

	print("in f3\n");
	pS2("a0", a0);
	r.f0 = -38.375;
	r.f1[0] = 86;
	r.f1[1] = -7;
	r.f2 = -35.000;
	r.f3 = 105;
	return r;
}

S0
f4(uchar a0)
{
	S0 r;

	print("in f4\n");
	print("a0 uchar %ud\n", a0);
	r.f0 = 14;
	r.f1 = 11199;
	r.f2 = 9584;
	return r;
}

char
f5(short a0, ushort a1)
{
	print("in f5\n");
	print("a0 short %d\n", a0);
	print("a1 ushort %ud\n", a1);
	return 120;
}

int
f6(S1 a0, S3 a1, double a2)
{
	print("in f6\n");
	pS1("a0", a0);
	pS3("a1", a1);
	print("a2 double %g\n", a2);
	return 1772180847;
}

void
f7(vlong a0)
{
	print("in f7\n");
	print("a0 vlong %lld\n", a0);
}

S2
f8(int a0, float a1)
{
	S2 r;

	print("in f8\n");
	print("a0 int %d\n", a0);
	print("a1 float %g\n", a1);
	r.f0 = 127;
	return r;
}

vlong
f9(ulong a0)
{
	print("in f9\n");
	print("a0 ulong %lud\n", a0);
	return -892863386LL;
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %ud\n", va_arg(ap, uint));
	print("v1 %lud\n", va_arg(ap, ulong));
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
	print("%s S0 %d %d %ud\n", w, s.f0, s.f1, s.f2);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %ud %ud %ud %ud %ud %ud %g %lld %d %ud %d %ud %lld %d %d %d %d\n", w, s.f0, s.f1[0], s.f1[1], s.f1[2], s.f1[3], s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10[0], s.f10[1], s.f10[2], s.f11);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d\n", w, s.f0);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %g %d %d %g %ud\n", w, s.f0, s.f1[0], s.f1[1], s.f2, s.f3);
}

static S3
back(S3 x, double d, vlong v)
{
	pS3("back x", x);
	print("back %g %lld\n", d, v);
	x.f0 = x.f0 * 2;
	x.f1[0] = x.f1[0] + 3;
	x.f1[1] = x.f1[1] + 3;
	x.f2 = x.f2 * 2;
	x.f3 = x.f3 + 3;
	return x;
}

void
main(void)
{
	{
	S0 v2;
	double r;
	v2.f0 = 16;
	v2.f1 = -16961;
	v2.f2 = 15346;
	r = f0((ushort)51812, (uint)1556366357U, v2);
	print("ret f0 double %g\n", r);
	}
	{
	S1 v0;
	S1 r;
	v0.f0 = 21595;
	v0.f1[0] = 12;
	v0.f1[1] = 189;
	v0.f1[2] = 110;
	v0.f1[3] = 31;
	v0.f2 = 46288;
	v0.f3 = 29.875;
	v0.f4 = 746891314LL;
	v0.f5 = -8675;
	v0.f6 = 1760795540U;
	v0.f7 = 5445;
	v0.f8 = 627216118U;
	v0.f9 = 1134171633504700LL;
	v0.f10[0] = 88;
	v0.f10[1] = -9;
	v0.f10[2] = 58;
	v0.f11 = 107;
	r = f1(v0, (uint)894817839U);
	pS1("ret f1", r);
	}
	{
	S2 v0;
	int r;
	v0.f0 = 117;
	r = f2(v0, (double)4.875, (uvlong)740221434ULL, (vlong)-4610438841138867270LL);
	print("ret f2 int %d\n", r);
	}
	{
	S2 v0;
	S3 r;
	v0.f0 = 113;
	r = f3(v0);
	pS3("ret f3", r);
	}
	{
	S0 r;
	r = f4((uchar)90);
	pS0("ret f4", r);
	}
	{
	char r;
	r = f5((short)5280, (ushort)3665);
	print("ret f5 char %d\n", r);
	}
	{
	S1 v0;
	S3 v1;
	int r;
	v0.f0 = 7831;
	v0.f1[0] = 72;
	v0.f1[1] = 249;
	v0.f1[2] = 170;
	v0.f1[3] = 91;
	v0.f2 = 32524;
	v0.f3 = -10.375;
	v0.f4 = 1797288558LL;
	v0.f5 = -27679;
	v0.f6 = 663709136U;
	v0.f7 = 24449;
	v0.f8 = 1677613362U;
	v0.f9 = 37081938245488LL;
	v0.f10[0] = 20;
	v0.f10[1] = -69;
	v0.f10[2] = 118;
	v0.f11 = 39;
	v1.f0 = 4.625;
	v1.f1[0] = 28;
	v1.f1[1] = 77;
	v1.f2 = 7.250;
	v1.f3 = 34607;
	r = f6(v0, v1, (double)24.125);
	print("ret f6 int %d\n", r);
	}
	{
	f7((vlong)1283670415999702LL);
	}
	{
	S2 r;
	r = f8((int)-1220494027, (float)4.500);
	pS2("ret f8", r);
	}
	{
	vlong r;
	r = f9((ulong)1664273602UL);
	print("ret f9 vlong %lld\n", r);
	}
	vf(2, (uint)1601101064U, (ulong)2108053177UL);
	{
	S3 x, r;

	x.f0 = 10.500;
	x.f1[0] = -125;
	x.f1[1] = 46;
	x.f2 = 13.125;
	x.f3 = 38416;
	r = cb(back, x);
	pS3("ret cb", r);
	}
	exits(nil);
}
#endif
