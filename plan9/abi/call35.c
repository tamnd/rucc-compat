#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { vlong f0; uvlong f1; uchar f2[9]; double f3; float f4; uchar f5; uint f6; long f7; float f8; int f9; uvlong f10; char f11; };
typedef struct S1 S1;
struct S1 { uint f0; char f1; char f2; };
typedef struct S2 S2;
struct S2 { vlong f0; uint f1; };
typedef struct S3 S3;
struct S3 { char f0; uchar f1; };

void f0(int a0, S1 a1);
S3 f1(S3 a0, S1 a1, S1 a2);
long f2(double a0, int a1, short a2, ulong a3);
double f3(char a0, S2 a1, S0 a2, ulong a3, int a4, vlong a5, ushort a6, uvlong a7);
S1 f4(uvlong a0);
double f5(short a0, int a1, uchar a2);
long f6(double a0, double a1, int a2, float a3);
short f7(uchar a0, short a1, ushort a2);
long f8(uvlong a0);
double f9(short a0, float a1, short a2, uvlong a3, ushort a4, S2 a5, uint a6, uchar a7);
void vf(int n, ...);
S2 cb(S2 (*fn)(S2, double, vlong), S2 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %lld %llud %ud %ud %ud %ud %ud %ud %ud %ud %ud %g %g %ud %ud %ld %g %d %llud %d\n", w, s.f0, s.f1, s.f2[0], s.f2[1], s.f2[2], s.f2[3], s.f2[4], s.f2[5], s.f2[6], s.f2[7], s.f2[8], s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %ud %d %d\n", w, s.f0, s.f1, s.f2);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %lld %ud\n", w, s.f0, s.f1);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %d %ud\n", w, s.f0, s.f1);
}

void
f0(int a0, S1 a1)
{
	print("in f0\n");
	print("a0 int %d\n", a0);
	pS1("a1", a1);
}

S3
f1(S3 a0, S1 a1, S1 a2)
{
	S3 r;

	print("in f1\n");
	pS3("a0", a0);
	pS1("a1", a1);
	pS1("a2", a2);
	r = a0;
	r.f0 = r.f0 + 3;
	r.f1 = r.f1 + 3;
	return r;
}

long
f2(double a0, int a1, short a2, ulong a3)
{
	print("in f2\n");
	print("a0 double %g\n", a0);
	print("a1 int %d\n", a1);
	print("a2 short %d\n", a2);
	print("a3 ulong %lud\n", a3);
	return 1310811195L;
}

double
f3(char a0, S2 a1, S0 a2, ulong a3, int a4, vlong a5, ushort a6, uvlong a7)
{
	print("in f3\n");
	print("a0 char %d\n", a0);
	pS2("a1", a1);
	pS0("a2", a2);
	print("a3 ulong %lud\n", a3);
	print("a4 int %d\n", a4);
	print("a5 vlong %lld\n", a5);
	print("a6 ushort %ud\n", a6);
	print("a7 uvlong %llud\n", a7);
	return -37.500;
}

S1
f4(uvlong a0)
{
	S1 r;

	print("in f4\n");
	print("a0 uvlong %llud\n", a0);
	r.f0 = 592760019U;
	r.f1 = 4;
	r.f2 = -53;
	return r;
}

double
f5(short a0, int a1, uchar a2)
{
	print("in f5\n");
	print("a0 short %d\n", a0);
	print("a1 int %d\n", a1);
	print("a2 uchar %ud\n", a2);
	return -13.375;
}

long
f6(double a0, double a1, int a2, float a3)
{
	print("in f6\n");
	print("a0 double %g\n", a0);
	print("a1 double %g\n", a1);
	print("a2 int %d\n", a2);
	print("a3 float %g\n", a3);
	return 635922917L;
}

short
f7(uchar a0, short a1, ushort a2)
{
	print("in f7\n");
	print("a0 uchar %ud\n", a0);
	print("a1 short %d\n", a1);
	print("a2 ushort %ud\n", a2);
	return 26430;
}

long
f8(uvlong a0)
{
	print("in f8\n");
	print("a0 uvlong %llud\n", a0);
	return 896854758L;
}

double
f9(short a0, float a1, short a2, uvlong a3, ushort a4, S2 a5, uint a6, uchar a7)
{
	print("in f9\n");
	print("a0 short %d\n", a0);
	print("a1 float %g\n", a1);
	print("a2 short %d\n", a2);
	print("a3 uvlong %llud\n", a3);
	print("a4 ushort %ud\n", a4);
	pS2("a5", a5);
	print("a6 uint %ud\n", a6);
	print("a7 uchar %ud\n", a7);
	return 49.500;
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %llud\n", va_arg(ap, uvlong));
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
	print("%s S0 %lld %llud %ud %ud %ud %ud %ud %ud %ud %ud %ud %g %g %ud %ud %ld %g %d %llud %d\n", w, s.f0, s.f1, s.f2[0], s.f2[1], s.f2[2], s.f2[3], s.f2[4], s.f2[5], s.f2[6], s.f2[7], s.f2[8], s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %ud %d %d\n", w, s.f0, s.f1, s.f2);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %lld %ud\n", w, s.f0, s.f1);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %d %ud\n", w, s.f0, s.f1);
}

static S2
back(S2 x, double d, vlong v)
{
	pS2("back x", x);
	print("back %g %lld\n", d, v);
	x.f0 = x.f0 + 3;
	x.f1 = x.f1 + 3;
	return x;
}

void
main(void)
{
	{
	S1 v1;
	v1.f0 = 814055224U;
	v1.f1 = -105;
	v1.f2 = 26;
	f0((int)215679244, v1);
	}
	{
	S3 v0;
	S1 v1;
	S1 v2;
	S3 r;
	v0.f0 = -82;
	v0.f1 = 3;
	v1.f0 = 1701614374U;
	v1.f1 = -87;
	v1.f2 = 8;
	v2.f0 = 1103238394U;
	v2.f1 = 43;
	v2.f2 = -92;
	r = f1(v0, v1, v2);
	pS3("ret f1", r);
	}
	{
	long r;
	r = f2((double)1.625, (int)441689876, (short)-8389, (ulong)1455594102UL);
	print("ret f2 long %ld\n", r);
	}
	{
	S2 v1;
	S0 v2;
	double r;
	v1.f0 = -1392421564LL;
	v1.f1 = 1899373677U;
	v2.f0 = 794045584LL;
	v2.f1 = 1301001599993098ULL;
	v2.f2[0] = 242;
	v2.f2[1] = 163;
	v2.f2[2] = 84;
	v2.f2[3] = 5;
	v2.f2[4] = 182;
	v2.f2[5] = 103;
	v2.f2[6] = 24;
	v2.f2[7] = 201;
	v2.f2[8] = 122;
	v2.f3 = -24.625;
	v2.f4 = -23.500;
	v2.f5 = 141;
	v2.f6 = 1448924222U;
	v2.f7 = 1955876335L;
	v2.f8 = -19.000;
	v2.f9 = 822296913;
	v2.f10 = 1329249026ULL;
	v2.f11 = -51;
	r = f3((char)100, v1, v2, (ulong)702621717UL, (int)-1209573830, (vlong)1716531092577836LL, (ushort)38184, (uvlong)582948269839570ULL);
	print("ret f3 double %g\n", r);
	}
	{
	S1 r;
	r = f4((uvlong)519775542321956ULL);
	pS1("ret f4", r);
	}
	{
	double r;
	r = f5((short)12133, (int)963553558, (uchar)199);
	print("ret f5 double %g\n", r);
	}
	{
	long r;
	r = f6((double)9.375, (double)10.250, (int)273753711, (float)12.000);
	print("ret f6 long %ld\n", r);
	}
	{
	short r;
	r = f7((uchar)102, (short)10775, (ushort)41928);
	print("ret f7 short %d\n", r);
	}
	{
	long r;
	r = f8((uvlong)1668264974ULL);
	print("ret f8 long %ld\n", r);
	}
	{
	S2 v5;
	double r;
	v5.f0 = 1605092436LL;
	v5.f1 = 2112044549U;
	r = f9((short)-17960, (float)52.875, (short)14730, (uvlong)380090287267448ULL, (ushort)11500, v5, (uint)1393993373U, (uchar)78);
	print("ret f9 double %g\n", r);
	}
	vf(1, (uvlong)1837772948ULL);
	{
	S2 x, r;

	x.f0 = 680657624LL;
	x.f1 = 1187609737U;
	r = cb(back, x);
	pS2("ret cb", r);
	}
	exits(nil);
}
#endif
