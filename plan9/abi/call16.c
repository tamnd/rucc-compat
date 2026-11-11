#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { float f0; uint f1; ushort f2; uint f3; ushort f4; uchar f5; };
typedef struct S1 S1;
struct S1 { ushort f0; int f1; char f2[9]; uchar f3; char f4; };
typedef struct S2 S2;
struct S2 { double f0; ulong f1; ushort f2; char f3; };
typedef struct S3 S3;
struct S3 { int f0; long f1; uchar f2; char f3; ushort f4; uchar f5[2]; uchar f6; };

float f0(ulong a0, double a1, S0 a2);
float f1(vlong a0);
S2 f2(float a0, float a1, short a2, vlong a3, double a4, uvlong a5, long a6, int a7);
double f3(uchar a0, vlong a1, double a2);
uint f4(S0 a0, S0 a1, char a2, ushort a3, uint a4, ushort a5);
uint f5(uchar a0, uvlong a1, uvlong a2, float a3, int a4, uchar a5, char a6, uchar a7);
S0 f6(short a0, uvlong a1);
ushort f7(uint a0);
float f8(float a0, uchar a1, uvlong a2, uchar a3);
uchar f9(vlong a0);
void vf(int n, ...);
S0 cb(S0 (*fn)(S0, double, vlong), S0 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %g %ud %ud %ud %ud %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %ud %d %d %d %d %d %d %d %d %d %d %ud %d\n", w, s.f0, s.f1, s.f2[0], s.f2[1], s.f2[2], s.f2[3], s.f2[4], s.f2[5], s.f2[6], s.f2[7], s.f2[8], s.f3, s.f4);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %g %lud %ud %d\n", w, s.f0, s.f1, s.f2, s.f3);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %d %ld %ud %d %ud %ud %ud %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5[0], s.f5[1], s.f6);
}

float
f0(ulong a0, double a1, S0 a2)
{
	print("in f0\n");
	print("a0 ulong %lud\n", a0);
	print("a1 double %g\n", a1);
	pS0("a2", a2);
	return -27.000;
}

float
f1(vlong a0)
{
	print("in f1\n");
	print("a0 vlong %lld\n", a0);
	return 32.625;
}

S2
f2(float a0, float a1, short a2, vlong a3, double a4, uvlong a5, long a6, int a7)
{
	S2 r;

	print("in f2\n");
	print("a0 float %g\n", a0);
	print("a1 float %g\n", a1);
	print("a2 short %d\n", a2);
	print("a3 vlong %lld\n", a3);
	print("a4 double %g\n", a4);
	print("a5 uvlong %llud\n", a5);
	print("a6 long %ld\n", a6);
	print("a7 int %d\n", a7);
	r.f0 = -30.375;
	r.f1 = 550238710UL;
	r.f2 = 29607;
	r.f3 = 88;
	return r;
}

double
f3(uchar a0, vlong a1, double a2)
{
	print("in f3\n");
	print("a0 uchar %ud\n", a0);
	print("a1 vlong %lld\n", a1);
	print("a2 double %g\n", a2);
	return 18.250;
}

uint
f4(S0 a0, S0 a1, char a2, ushort a3, uint a4, ushort a5)
{
	print("in f4\n");
	pS0("a0", a0);
	pS0("a1", a1);
	print("a2 char %d\n", a2);
	print("a3 ushort %ud\n", a3);
	print("a4 uint %ud\n", a4);
	print("a5 ushort %ud\n", a5);
	return 1487630638U;
}

uint
f5(uchar a0, uvlong a1, uvlong a2, float a3, int a4, uchar a5, char a6, uchar a7)
{
	print("in f5\n");
	print("a0 uchar %ud\n", a0);
	print("a1 uvlong %llud\n", a1);
	print("a2 uvlong %llud\n", a2);
	print("a3 float %g\n", a3);
	print("a4 int %d\n", a4);
	print("a5 uchar %ud\n", a5);
	print("a6 char %d\n", a6);
	print("a7 uchar %ud\n", a7);
	return 1748562479U;
}

S0
f6(short a0, uvlong a1)
{
	S0 r;

	print("in f6\n");
	print("a0 short %d\n", a0);
	print("a1 uvlong %llud\n", a1);
	r.f0 = -13.000;
	r.f1 = 142952153U;
	r.f2 = 49290;
	r.f3 = 1156856379U;
	r.f4 = 46060;
	r.f5 = 157;
	return r;
}

ushort
f7(uint a0)
{
	print("in f7\n");
	print("a0 uint %ud\n", a0);
	return 57411;
}

float
f8(float a0, uchar a1, uvlong a2, uchar a3)
{
	print("in f8\n");
	print("a0 float %g\n", a0);
	print("a1 uchar %ud\n", a1);
	print("a2 uvlong %llud\n", a2);
	print("a3 uchar %ud\n", a3);
	return -30.875;
}

uchar
f9(vlong a0)
{
	print("in f9\n");
	print("a0 vlong %lld\n", a0);
	return 226;
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %ld\n", va_arg(ap, long));
	print("v1 %ld\n", va_arg(ap, long));
	print("v2 %g\n", va_arg(ap, double));
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
	print("%s S0 %g %ud %ud %ud %ud %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %ud %d %d %d %d %d %d %d %d %d %d %ud %d\n", w, s.f0, s.f1, s.f2[0], s.f2[1], s.f2[2], s.f2[3], s.f2[4], s.f2[5], s.f2[6], s.f2[7], s.f2[8], s.f3, s.f4);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %g %lud %ud %d\n", w, s.f0, s.f1, s.f2, s.f3);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %d %ld %ud %d %ud %ud %ud %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5[0], s.f5[1], s.f6);
}

static S0
back(S0 x, double d, vlong v)
{
	pS0("back x", x);
	print("back %g %lld\n", d, v);
	x.f0 = x.f0 * 2;
	x.f1 = x.f1 + 3;
	x.f2 = x.f2 + 3;
	x.f3 = x.f3 + 3;
	x.f4 = x.f4 + 3;
	x.f5 = x.f5 + 3;
	return x;
}

void
main(void)
{
	{
	S0 v2;
	float r;
	v2.f0 = 52.000;
	v2.f1 = 695021617U;
	v2.f2 = 43490;
	v2.f3 = 1708925843U;
	v2.f4 = 40260;
	v2.f5 = 245;
	r = f0((ulong)1737177172UL, (double)-24.375, v2);
	print("ret f0 float %g\n", r);
	}
	{
	float r;
	r = f1((vlong)-4611652545227968614LL);
	print("ret f1 float %g\n", r);
	}
	{
	S2 r;
	r = f2((float)52.875, (float)53.750, (short)17907, (vlong)1491156900LL, (double)56.375, (uvlong)357577478ULL, (long)864529591L, (int)-1371481704);
	pS2("ret f2", r);
	}
	{
	double r;
	r = f3((uchar)174, (vlong)-4609870751702604074LL, (double)2.000);
	print("ret f3 double %g\n", r);
	}
	{
	S0 v0;
	S0 v1;
	uint r;
	v0.f0 = 40.250;
	v0.f1 = 618509319U;
	v0.f2 = 11704;
	v0.f3 = 1632413545U;
	v0.f4 = 8474;
	v0.f5 = 203;
	v1.f0 = -37.750;
	v1.f1 = 20133339U;
	v1.f2 = 44940;
	v1.f3 = 1034037565U;
	v1.f4 = 41710;
	v1.f5 = 159;
	r = f4(v0, v1, (char)126, (ushort)47023, (uint)2076193120U, (ushort)43793);
	print("ret f4 uint %ud\n", r);
	}
	{
	uint r;
	r = f5((uchar)87, (uvlong)879441160ULL, (uvlong)1386397432179826ULL, (float)27.750, (int)252813851, (uchar)204, (char)-125, (uchar)46);
	print("ret f5 uint %ud\n", r);
	}
	{
	S0 r;
	r = f6((short)-8052, (uvlong)69966326898358ULL);
	pS0("ret f6", r);
	}
	{
	ushort r;
	r = f7((uint)6793579U);
	print("ret f7 ushort %ud\n", r);
	}
	{
	float r;
	r = f8((float)49.875, (uchar)98, (uvlong)957528139575808ULL, (uchar)196);
	print("ret f8 float %g\n", r);
	}
	{
	uchar r;
	r = f9((vlong)1401304842LL);
	print("ret f9 uchar %ud\n", r);
	}
	vf(3, (long)-1338132304L, (long)1845084417L, (double)33.750);
	{
	S0 x, r;

	x.f0 = -39.500;
	x.f1 = 687969093U;
	x.f2 = 3318;
	x.f3 = 1701873319U;
	x.f4 = 88;
	x.f5 = 9;
	r = cb(back, x);
	pS0("ret cb", r);
	}
	exits(nil);
}
#endif
