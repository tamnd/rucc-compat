#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { int f0; uchar f1; };
typedef struct S1 S1;
struct S1 { int f0; float f1; double f2; ulong f3; float f4; };
typedef struct S2 S2;
struct S2 { uint f0; ushort f1; };
typedef struct S3 S3;
struct S3 { char f0; ulong f1; char f2; char f3; };

char f0(long a0, S2 a1, double a2, uchar a3);
int f1(double a0, uvlong a1, double a2, S3 a3, S0 a4, uint a5, float a6, S2 a7);
long f2(uchar a0, int a1, S0 a2, long a3, float a4, ulong a5);
long f3(uchar a0, long a1);
uint f4(double a0, S2 a1, long a2);
uint f5(int a0);
double f6(vlong a0);
uvlong f7(uint a0);
vlong f8(float a0, uint a1);
S2 f9(S1 a0, short a1, uchar a2, S3 a3);
void vf(int n, ...);
S0 cb(S0 (*fn)(S0, double, vlong), S0 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %d %ud\n", w, s.f0, s.f1);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %d %g %g %lud %g\n", w, s.f0, s.f1, s.f2, s.f3, s.f4);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %ud %ud\n", w, s.f0, s.f1);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %d %lud %d %d\n", w, s.f0, s.f1, s.f2, s.f3);
}

char
f0(long a0, S2 a1, double a2, uchar a3)
{
	print("in f0\n");
	print("a0 long %ld\n", a0);
	pS2("a1", a1);
	print("a2 double %g\n", a2);
	print("a3 uchar %ud\n", a3);
	return 96;
}

int
f1(double a0, uvlong a1, double a2, S3 a3, S0 a4, uint a5, float a6, S2 a7)
{
	print("in f1\n");
	print("a0 double %g\n", a0);
	print("a1 uvlong %llud\n", a1);
	print("a2 double %g\n", a2);
	pS3("a3", a3);
	pS0("a4", a4);
	print("a5 uint %ud\n", a5);
	print("a6 float %g\n", a6);
	pS2("a7", a7);
	return 310805852;
}

long
f2(uchar a0, int a1, S0 a2, long a3, float a4, ulong a5)
{
	print("in f2\n");
	print("a0 uchar %ud\n", a0);
	print("a1 int %d\n", a1);
	pS0("a2", a2);
	print("a3 long %ld\n", a3);
	print("a4 float %g\n", a4);
	print("a5 ulong %lud\n", a5);
	return 480313826L;
}

long
f3(uchar a0, long a1)
{
	print("in f3\n");
	print("a0 uchar %ud\n", a0);
	print("a1 long %ld\n", a1);
	return 1846573760L;
}

uint
f4(double a0, S2 a1, long a2)
{
	print("in f4\n");
	print("a0 double %g\n", a0);
	pS2("a1", a1);
	print("a2 long %ld\n", a2);
	return 142869687U;
}

uint
f5(int a0)
{
	print("in f5\n");
	print("a0 int %d\n", a0);
	return 2135756930U;
}

double
f6(vlong a0)
{
	print("in f6\n");
	print("a0 vlong %lld\n", a0);
	return 3.000;
}

uvlong
f7(uint a0)
{
	print("in f7\n");
	print("a0 uint %ud\n", a0);
	return 2009411854ULL;
}

vlong
f8(float a0, uint a1)
{
	print("in f8\n");
	print("a0 float %g\n", a0);
	print("a1 uint %ud\n", a1);
	return -1946239316LL;
}

S2
f9(S1 a0, short a1, uchar a2, S3 a3)
{
	S2 r;

	print("in f9\n");
	pS1("a0", a0);
	print("a1 short %d\n", a1);
	print("a2 uchar %ud\n", a2);
	pS3("a3", a3);
	r.f0 = 1086931495U;
	r.f1 = 48088;
	return r;
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %ud\n", va_arg(ap, uint));
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
	print("%s S0 %d %ud\n", w, s.f0, s.f1);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %d %g %g %lud %g\n", w, s.f0, s.f1, s.f2, s.f3, s.f4);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %ud %ud\n", w, s.f0, s.f1);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %d %lud %d %d\n", w, s.f0, s.f1, s.f2, s.f3);
}

static S0
back(S0 x, double d, vlong v)
{
	pS0("back x", x);
	print("back %g %lld\n", d, v);
	x.f0 = x.f0 + 3;
	x.f1 = x.f1 + 3;
	return x;
}

void
main(void)
{
	{
	S2 v1;
	char r;
	v1.f0 = 729860360U;
	v1.f1 = 17081;
	r = f0((long)131484380L, v1, (double)34.375, (uchar)62);
	print("ret f0 char %d\n", r);
	}
	{
	S3 v3;
	S0 v4;
	S2 v7;
	int r;
	v3.f0 = 4;
	v3.f1 = 1589168181UL;
	v3.f2 = 102;
	v3.f3 = 23;
	v4.f0 = 483840088;
	v4.f1 = 9;
	v7.f0 = 2032947756U;
	v7.f1 = 52189;
	r = f1((double)36.000, (uvlong)1941529713571674ULL, (double)38.750, v3, v4, (uint)807944467U, (float)40.500, v7);
	print("ret f1 int %d\n", r);
	}
	{
	S0 v2;
	long r;
	v2.f0 = 1251724042;
	v2.f1 = 187;
	r = f2((uchar)222, (int)1160300175, v2, (long)-1667252288L, (float)4.875, (ulong)533672866UL);
	print("ret f2 long %ld\n", r);
	}
	{
	long r;
	r = f3((uchar)232, (long)977452441L);
	print("ret f3 long %ld\n", r);
	}
	{
	S2 v1;
	uint r;
	v1.f0 = 914279903U;
	v1.f1 = 18320;
	r = f4((double)5.625, v1, (long)822856036L);
	print("ret f4 uint %ud\n", r);
	}
	{
	uint r;
	r = f5((int)-759683498);
	print("ret f5 uint %ud\n", r);
	}
	{
	double r;
	r = f6((vlong)696510960LL);
	print("ret f6 double %g\n", r);
	}
	{
	uvlong r;
	r = f7((uint)633338422U);
	print("ret f7 uvlong %llud\n", r);
	}
	{
	vlong r;
	r = f8((float)-36.500, (uint)1077117997U);
	print("ret f8 vlong %lld\n", r);
	}
	{
	S1 v0;
	S3 v3;
	S2 r;
	v0.f0 = -1013945459;
	v0.f1 = 4.500;
	v0.f2 = 5.375;
	v0.f3 = 387318150UL;
	v0.f4 = 7.125;
	v3.f0 = 71;
	v3.f1 = 922521592UL;
	v3.f2 = 41;
	v3.f3 = 90;
	r = f9(v0, (short)6171, (uchar)204, v3);
	pS2("ret f9", r);
	}
	vf(1, (uint)260973074U);
	{
	S0 x, r;

	x.f0 = 1251341398;
	x.f1 = 7;
	r = cb(back, x);
	pS0("ret cb", r);
	}
	exits(nil);
}
#endif
