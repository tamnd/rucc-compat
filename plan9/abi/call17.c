#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { short f0; ushort f1; int f2; double f3; };
typedef struct S1 S1;
struct S1 { uchar f0; long f1; short f2; uvlong f3; };
typedef struct S2 S2;
struct S2 { float f0; };
typedef struct S3 S3;
struct S3 { ushort f0; ushort f1; char f2; int f3; short f4; char f5; };

S1 f0(S2 a0, uvlong a1, vlong a2, vlong a3, vlong a4, uint a5, float a6, ushort a7);
ulong f1(char a0, char a1, char a2);
float f2(char a0, ushort a1, double a2, ulong a3);
ulong f3(double a0, ulong a1, uchar a2, long a3, ulong a4, ulong a5);
float f4(S0 a0, short a1, double a2, float a3, S0 a4, uvlong a5);
float f5(long a0, S2 a1, S1 a2, short a3, S1 a4, int a5, S1 a6, uchar a7);
void f6(S2 a0, uvlong a1, long a2, S1 a3, uvlong a4, double a5, S0 a6, uchar a7);
vlong f7(long a0, S0 a1);
double f8(int a0, double a1, float a2, uvlong a3, S1 a4, uchar a5, S1 a6, ushort a7);
short f9(short a0, short a1, uint a2);
void vf(int n, ...);
S2 cb(S2 (*fn)(S2, double, vlong), S2 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %d %ud %d %g\n", w, s.f0, s.f1, s.f2, s.f3);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %ud %ld %d %llud\n", w, s.f0, s.f1, s.f2, s.f3);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %g\n", w, s.f0);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %ud %ud %d %d %d %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5);
}

S1
f0(S2 a0, uvlong a1, vlong a2, vlong a3, vlong a4, uint a5, float a6, ushort a7)
{
	S1 r;

	print("in f0\n");
	pS2("a0", a0);
	print("a1 uvlong %llud\n", a1);
	print("a2 vlong %lld\n", a2);
	print("a3 vlong %lld\n", a3);
	print("a4 vlong %lld\n", a4);
	print("a5 uint %ud\n", a5);
	print("a6 float %g\n", a6);
	print("a7 ushort %ud\n", a7);
	r.f0 = 156;
	r.f1 = 913979725L;
	r.f2 = -13054;
	r.f3 = 1927889734651860ULL;
	return r;
}

ulong
f1(char a0, char a1, char a2)
{
	print("in f1\n");
	print("a0 char %d\n", a0);
	print("a1 char %d\n", a1);
	print("a2 char %d\n", a2);
	return 1942795520UL;
}

float
f2(char a0, ushort a1, double a2, ulong a3)
{
	print("in f2\n");
	print("a0 char %d\n", a0);
	print("a1 ushort %ud\n", a1);
	print("a2 double %g\n", a2);
	print("a3 ulong %lud\n", a3);
	return 10.000;
}

ulong
f3(double a0, ulong a1, uchar a2, long a3, ulong a4, ulong a5)
{
	print("in f3\n");
	print("a0 double %g\n", a0);
	print("a1 ulong %lud\n", a1);
	print("a2 uchar %ud\n", a2);
	print("a3 long %ld\n", a3);
	print("a4 ulong %lud\n", a4);
	print("a5 ulong %lud\n", a5);
	return 56243713UL;
}

float
f4(S0 a0, short a1, double a2, float a3, S0 a4, uvlong a5)
{
	print("in f4\n");
	pS0("a0", a0);
	print("a1 short %d\n", a1);
	print("a2 double %g\n", a2);
	print("a3 float %g\n", a3);
	pS0("a4", a4);
	print("a5 uvlong %llud\n", a5);
	return -3.500;
}

float
f5(long a0, S2 a1, S1 a2, short a3, S1 a4, int a5, S1 a6, uchar a7)
{
	print("in f5\n");
	print("a0 long %ld\n", a0);
	pS2("a1", a1);
	pS1("a2", a2);
	print("a3 short %d\n", a3);
	pS1("a4", a4);
	print("a5 int %d\n", a5);
	pS1("a6", a6);
	print("a7 uchar %ud\n", a7);
	return -19.375;
}

void
f6(S2 a0, uvlong a1, long a2, S1 a3, uvlong a4, double a5, S0 a6, uchar a7)
{
	print("in f6\n");
	pS2("a0", a0);
	print("a1 uvlong %llud\n", a1);
	print("a2 long %ld\n", a2);
	pS1("a3", a3);
	print("a4 uvlong %llud\n", a4);
	print("a5 double %g\n", a5);
	pS0("a6", a6);
	print("a7 uchar %ud\n", a7);
}

vlong
f7(long a0, S0 a1)
{
	print("in f7\n");
	print("a0 long %ld\n", a0);
	pS0("a1", a1);
	return 2022451436LL;
}

double
f8(int a0, double a1, float a2, uvlong a3, S1 a4, uchar a5, S1 a6, ushort a7)
{
	print("in f8\n");
	print("a0 int %d\n", a0);
	print("a1 double %g\n", a1);
	print("a2 float %g\n", a2);
	print("a3 uvlong %llud\n", a3);
	pS1("a4", a4);
	print("a5 uchar %ud\n", a5);
	pS1("a6", a6);
	print("a7 ushort %ud\n", a7);
	return -29.250;
}

short
f9(short a0, short a1, uint a2)
{
	print("in f9\n");
	print("a0 short %d\n", a0);
	print("a1 short %d\n", a1);
	print("a2 uint %ud\n", a2);
	return 12137;
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
	print("%s S0 %d %ud %d %g\n", w, s.f0, s.f1, s.f2, s.f3);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %ud %ld %d %llud\n", w, s.f0, s.f1, s.f2, s.f3);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %g\n", w, s.f0);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %ud %ud %d %d %d %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5);
}

static S2
back(S2 x, double d, vlong v)
{
	pS2("back x", x);
	print("back %g %lld\n", d, v);
	x.f0 = x.f0 * 2;
	return x;
}

void
main(void)
{
	{
	S2 v0;
	S1 r;
	v0.f0 = -15.000;
	r = f0(v0, (uvlong)1883149244ULL, (vlong)242618436853134LL, (vlong)-749569822LL, (vlong)1256525704565812LL, (uint)1763474048U, (float)10.875, (ushort)28130);
	pS1("ret f0", r);
	}
	{
	ulong r;
	r = f1((char)-40, (char)89, (char)10);
	print("ret f1 ulong %lud\n", r);
	}
	{
	float r;
	r = f2((char)80, (ushort)64385, (double)-6.750, (ulong)890826467UL);
	print("ret f2 float %g\n", r);
	}
	{
	ulong r;
	r = f3((double)33.875, (ulong)1334606042UL, (uchar)139, (long)-201026620L, (ulong)707978733UL, (ulong)1214930846UL);
	print("ret f3 ulong %lud\n", r);
	}
	{
	S0 v0;
	S0 v4;
	float r;
	v0.f0 = 28644;
	v0.f1 = 59797;
	v0.f2 = -18178886;
	v0.f3 = -18.125;
	v4.f0 = -29112;
	v4.f1 = 27497;
	v4.f2 = 1567286554;
	v4.f3 = 2.625;
	r = f4(v0, (short)29580, (double)20.375, (float)21.250, v4, (uvlong)1475867114588068ULL);
	print("ret f4 float %g\n", r);
	}
	{
	S2 v1;
	S1 v2;
	S1 v4;
	S1 v6;
	float r;
	v1.f0 = -37.375;
	v2.f0 = 185;
	v2.f1 = 1321266282L;
	v2.f2 = 26139;
	v2.f3 = 187686860ULL;
	v4.f0 = 141;
	v4.f1 = -722890302L;
	v4.f2 = 26607;
	v4.f3 = 1736794528ULL;
	v6.f0 = 97;
	v6.f1 = 124514322L;
	v6.f2 = -27075;
	v6.f3 = 1138418548ULL;
	r = f5((long)-1166669877L, v1, v2, (short)29158, v4, (int)33090455, v6, (uchar)72);
	print("ret f5 float %g\n", r);
	}
	{
	S2 v0;
	S1 v3;
	S0 v6;
	v0.f0 = -13.250;
	v3.f0 = 98;
	v3.f1 = 385446163L;
	v3.f2 = -27332;
	v3.f3 = 1399354587051174ULL;
	v6.f0 = -31030;
	v6.f1 = 62183;
	v6.f2 = 294022296;
	v6.f3 = 30.875;
	f6(v0, (uvlong)829225738ULL, (long)-1336177851L, v3, (uvlong)1843129964ULL, (double)50.375, v6, (uchar)206);
	}
	{
	S0 v1;
	vlong r;
	v1.f0 = 29204;
	v1.f1 = 27589;
	v1.f2 = 1660282230;
	v1.f3 = -5.125;
	r = f7((long)48002024L, v1);
	print("ret f7 vlong %lld\n", r);
	}
	{
	S1 v4;
	S1 v6;
	double r;
	v4.f0 = 46;
	v4.f1 = 491781599L;
	v4.f2 = 30608;
	v4.f3 = 1505690342057482ULL;
	v6.f0 = 2;
	v6.f1 = -2040889267L;
	v6.f2 = 31076;
	v6.f3 = 907312566929542ULL;
	r = f8((int)935561174, (double)-6.125, (float)-5.000, (uvlong)308934791801602ULL, v4, (uchar)154, v6, (ushort)59467);
	print("ret f8 double %g\n", r);
	}
	{
	short r;
	r = f9((short)30865, (short)-29250, (uint)126086131U);
	print("ret f9 short %d\n", r);
	}
	vf(1, (ulong)62913593UL);
	{
	S2 x, r;

	x.f0 = 6.375;
	r = cb(back, x);
	pS2("ret cb", r);
	}
	exits(nil);
}
#endif
