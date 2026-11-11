#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { short f0; };
typedef struct S1 S1;
struct S1 { char f0; char f1; char f2; };
typedef struct S2 S2;
struct S2 { char f0; };
typedef struct S3 S3;
struct S3 { uvlong f0; int f1; float f2; short f3; uint f4; vlong f5; uvlong f6; vlong f7; short f8; short f9; short f10; ulong f11; ushort f12; ushort f13; short f14; uchar f15; uchar f16; };

uvlong f0(long a0);
S1 f1(uint a0, double a1, char a2, char a3);
int f2(ulong a0, uint a1, char a2, double a3);
int f3(uchar a0, S1 a1, int a2);
ushort f4(vlong a0, int a1);
short f5(double a0, S1 a1);
char f6(S0 a0);
S0 f7(uvlong a0, float a1, int a2, uvlong a3, ulong a4, uvlong a5);
void f8(ulong a0, ulong a1, char a2);
S1 f9(short a0, char a1, double a2);
void vf(int n, ...);
S3 cb(S3 (*fn)(S3, double, vlong), S3 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %d\n", w, s.f0);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %d %d %d\n", w, s.f0, s.f1, s.f2);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d\n", w, s.f0);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %llud %d %g %d %ud %lld %llud %lld %d %d %d %lud %ud %ud %d %ud %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11, s.f12, s.f13, s.f14, s.f15, s.f16);
}

uvlong
f0(long a0)
{
	print("in f0\n");
	print("a0 long %ld\n", a0);
	return 188617080ULL;
}

S1
f1(uint a0, double a1, char a2, char a3)
{
	S1 r;

	print("in f1\n");
	print("a0 uint %ud\n", a0);
	print("a1 double %g\n", a1);
	print("a2 char %d\n", a2);
	print("a3 char %d\n", a3);
	r.f0 = 26;
	r.f1 = 75;
	r.f2 = -124;
	return r;
}

int
f2(ulong a0, uint a1, char a2, double a3)
{
	print("in f2\n");
	print("a0 ulong %lud\n", a0);
	print("a1 uint %ud\n", a1);
	print("a2 char %d\n", a2);
	print("a3 double %g\n", a3);
	return 1583128343;
}

int
f3(uchar a0, S1 a1, int a2)
{
	print("in f3\n");
	print("a0 uchar %ud\n", a0);
	pS1("a1", a1);
	print("a2 int %d\n", a2);
	return -893328496;
}

ushort
f4(vlong a0, int a1)
{
	print("in f4\n");
	print("a0 vlong %lld\n", a0);
	print("a1 int %d\n", a1);
	return 10299;
}

short
f5(double a0, S1 a1)
{
	print("in f5\n");
	print("a0 double %g\n", a0);
	pS1("a1", a1);
	return 12850;
}

char
f6(S0 a0)
{
	print("in f6\n");
	pS0("a0", a0);
	return -76;
}

S0
f7(uvlong a0, float a1, int a2, uvlong a3, ulong a4, uvlong a5)
{
	S0 r;

	print("in f7\n");
	print("a0 uvlong %llud\n", a0);
	print("a1 float %g\n", a1);
	print("a2 int %d\n", a2);
	print("a3 uvlong %llud\n", a3);
	print("a4 ulong %lud\n", a4);
	print("a5 uvlong %llud\n", a5);
	r.f0 = 21393;
	return r;
}

void
f8(ulong a0, ulong a1, char a2)
{
	print("in f8\n");
	print("a0 ulong %lud\n", a0);
	print("a1 ulong %lud\n", a1);
	print("a2 char %d\n", a2);
}

S1
f9(short a0, char a1, double a2)
{
	S1 r;

	print("in f9\n");
	print("a0 short %d\n", a0);
	print("a1 char %d\n", a1);
	print("a2 double %g\n", a2);
	r.f0 = 116;
	r.f1 = 37;
	r.f2 = -86;
	return r;
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %g\n", va_arg(ap, double));
	print("v1 %lud\n", va_arg(ap, ulong));
	print("v2 %g\n", va_arg(ap, double));
	print("v3 %g\n", va_arg(ap, double));
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
	print("%s S0 %d\n", w, s.f0);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %d %d %d\n", w, s.f0, s.f1, s.f2);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d\n", w, s.f0);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %llud %d %g %d %ud %lld %llud %lld %d %d %d %lud %ud %ud %d %ud %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11, s.f12, s.f13, s.f14, s.f15, s.f16);
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
	x.f5 = x.f5 + 3;
	x.f6 = x.f6 + 3;
	x.f7 = x.f7 + 3;
	x.f8 = x.f8 + 3;
	x.f9 = x.f9 + 3;
	x.f10 = x.f10 + 3;
	x.f11 = x.f11 + 3;
	x.f12 = x.f12 + 3;
	x.f13 = x.f13 + 3;
	x.f14 = x.f14 + 3;
	x.f15 = x.f15 + 3;
	x.f16 = x.f16 + 3;
	return x;
}

void
main(void)
{
	{
	uvlong r;
	r = f0((long)-960027296L);
	print("ret f0 uvlong %llud\n", r);
	}
	{
	S1 r;
	r = f1((uint)896854758U, (double)12.125, (char)72, (char)121);
	pS1("ret f1", r);
	}
	{
	int r;
	r = f2((ulong)207054911UL, (uint)714007024U, (char)-33, (double)55.750);
	print("ret f2 int %d\n", r);
	}
	{
	S1 v1;
	int r;
	v1.f0 = -24;
	v1.f1 = 73;
	v1.f2 = 122;
	r = f3((uchar)108, v1, (int)-1573314845);
	print("ret f3 int %d\n", r);
	}
	{
	ushort r;
	r = f4((vlong)1510146837426928LL, (int)-2017094420);
	print("ret f4 ushort %ud\n", r);
	}
	{
	S1 v1;
	short r;
	v1.f0 = 90;
	v1.f1 = -11;
	v1.f2 = 60;
	r = f5((double)17.250, v1);
	print("ret f5 short %d\n", r);
	}
	{
	S0 v0;
	char r;
	v0.f0 = -3444;
	r = f6(v0);
	print("ret f6 char %d\n", r);
	}
	{
	S0 r;
	r = f7((uvlong)123873104618206ULL, (float)16.250, (int)1137776959, (uvlong)1644729072ULL, (ulong)4197537UL, (uvlong)511149650ULL);
	pS0("ret f7", r);
	}
	{
	f8((ulong)447977112UL, (ulong)954929225UL, (char)-122);
	}
	{
	S1 r;
	r = f9((short)6720, (char)-113, (double)3.750);
	pS1("ret f9", r);
	}
	vf(4, (double)41.000, (ulong)708908953UL, (double)43.750, (double)44.625);
	{
	S3 x, r;

	x.f0 = 1192325164ULL;
	x.f1 = 1699277277;
	x.f2 = -27.250;
	x.f3 = -23871;
	x.f4 = 1072649968U;
	x.f5 = 1579606819806250LL;
	x.f6 = 2086554194ULL;
	x.f7 = 446023997067984LL;
	x.f8 = 15796;
	x.f9 = -14181;
	x.f10 = 12566;
	x.f11 = 326347463UL;
	x.f12 = 9336;
	x.f13 = 40489;
	x.f14 = 6106;
	x.f15 = 139;
	x.f16 = 60;
	r = cb(back, x);
	pS3("ret cb", r);
	}
	exits(nil);
}
#endif
