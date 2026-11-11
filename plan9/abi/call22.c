#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { long f0; long f1; char f2; short f3; float f4; uchar f5; };
typedef struct S1 S1;
struct S1 { long f0; char f1; uchar f2; };
typedef struct S2 S2;
struct S2 { char f0[6]; int f1; vlong f2; char f3; ulong f4; uint f5; short f6; long f7; uint f8; double f9; long f10; int f11; vlong f12; char f13; char f14; };
typedef struct S3 S3;
struct S3 { long f0; };

S2 f0(uint a0);
uint f1(vlong a0, uint a1, uchar a2);
float f2(long a0, char a1);
short f3(uchar a0, vlong a1, float a2, float a3);
uchar f4(ulong a0);
uint f5(uint a0, S0 a1, vlong a2, uchar a3, short a4, short a5);
long f6(S3 a0);
S2 f7(vlong a0, S0 a1);
S1 f8(S3 a0, double a1);
ulong f9(long a0);
void vf(int n, ...);
S2 cb(S2 (*fn)(S2, double, vlong), S2 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %ld %ld %d %d %g %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %ld %d %ud\n", w, s.f0, s.f1, s.f2);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d %d %d %d %d %d %d %lld %d %lud %ud %d %ld %ud %g %ld %d %lld %d %d\n", w, s.f0[0], s.f0[1], s.f0[2], s.f0[3], s.f0[4], s.f0[5], s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11, s.f12, s.f13, s.f14);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %ld\n", w, s.f0);
}

S2
f0(uint a0)
{
	S2 r;

	print("in f0\n");
	print("a0 uint %ud\n", a0);
	r.f0[0] = -36;
	r.f0[1] = 85;
	r.f0[2] = 6;
	r.f0[3] = -55;
	r.f0[4] = 104;
	r.f0[5] = 25;
	r.f1 = -2031117002;
	r.f2 = 390586638756408LL;
	r.f3 = 44;
	r.f4 = 1404489693UL;
	r.f5 = 1911441806U;
	r.f6 = 17215;
	r.f7 = -777862384L;
	r.f8 = 1284814497U;
	r.f9 = -30.750;
	r.f10 = -151235075L;
	r.f11 = 658187188;
	r.f12 = 1165142796417910LL;
	r.f13 = -22;
	r.f14 = 71;
	return r;
}

uint
f1(vlong a0, uint a1, uchar a2)
{
	print("in f1\n");
	print("a0 vlong %lld\n", a0);
	print("a1 uint %ud\n", a1);
	print("a2 uchar %ud\n", a2);
	return 229319182U;
}

float
f2(long a0, char a1)
{
	print("in f2\n");
	print("a0 long %ld\n", a0);
	print("a1 char %d\n", a1);
	return 37.250;
}

short
f3(uchar a0, vlong a1, float a2, float a3)
{
	print("in f3\n");
	print("a0 uchar %ud\n", a0);
	print("a1 vlong %lld\n", a1);
	print("a2 float %g\n", a2);
	print("a3 float %g\n", a3);
	return 12205;
}

uchar
f4(ulong a0)
{
	print("in f4\n");
	print("a0 ulong %lud\n", a0);
	return 6;
}

uint
f5(uint a0, S0 a1, vlong a2, uchar a3, short a4, short a5)
{
	print("in f5\n");
	print("a0 uint %ud\n", a0);
	pS0("a1", a1);
	print("a2 vlong %lld\n", a2);
	print("a3 uchar %ud\n", a3);
	print("a4 short %d\n", a4);
	print("a5 short %d\n", a5);
	return 870858060U;
}

long
f6(S3 a0)
{
	print("in f6\n");
	pS3("a0", a0);
	return 89634346L;
}

S2
f7(vlong a0, S0 a1)
{
	S2 r;

	print("in f7\n");
	print("a0 vlong %lld\n", a0);
	pS0("a1", a1);
	r.f0[0] = -111;
	r.f0[1] = 32;
	r.f0[2] = 81;
	r.f0[3] = -2;
	r.f0[4] = 51;
	r.f0[5] = 100;
	r.f1 = -659758997;
	r.f2 = 1166711110LL;
	r.f3 = 119;
	r.f4 = 33131688UL;
	r.f5 = 540083801U;
	r.f6 = 10;
	r.f7 = -1553988027L;
	r.f8 = 2060940140U;
	r.f9 = -6.375;
	r.f10 = -927360718L;
	r.f11 = 1434312831;
	r.f12 = 1941264944LL;
	r.f13 = -97;
	r.f14 = 18;
	return r;
}

S1
f8(S3 a0, double a1)
{
	S1 r;

	print("in f8\n");
	pS3("a0", a0);
	print("a1 double %g\n", a1);
	r.f0 = 1251465097L;
	r.f1 = 58;
	r.f2 = 235;
	return r;
}

ulong
f9(long a0)
{
	print("in f9\n");
	print("a0 long %ld\n", a0);
	return 1893003975UL;
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %ud\n", va_arg(ap, uint));
	print("v1 %d\n", va_arg(ap, int));
	print("v2 %ld\n", va_arg(ap, long));
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
	print("%s S0 %ld %ld %d %d %g %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %ld %d %ud\n", w, s.f0, s.f1, s.f2);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d %d %d %d %d %d %d %lld %d %lud %ud %d %ld %ud %g %ld %d %lld %d %d\n", w, s.f0[0], s.f0[1], s.f0[2], s.f0[3], s.f0[4], s.f0[5], s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11, s.f12, s.f13, s.f14);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %ld\n", w, s.f0);
}

static S2
back(S2 x, double d, vlong v)
{
	pS2("back x", x);
	print("back %g %lld\n", d, v);
	x.f0[0] = x.f0[0] + 3;
	x.f0[1] = x.f0[1] + 3;
	x.f0[2] = x.f0[2] + 3;
	x.f0[3] = x.f0[3] + 3;
	x.f0[4] = x.f0[4] + 3;
	x.f0[5] = x.f0[5] + 3;
	x.f1 = x.f1 + 3;
	x.f2 = x.f2 + 3;
	x.f3 = x.f3 + 3;
	x.f4 = x.f4 + 3;
	x.f5 = x.f5 + 3;
	x.f6 = x.f6 + 3;
	x.f7 = x.f7 + 3;
	x.f8 = x.f8 + 3;
	x.f9 = x.f9 * 2;
	x.f10 = x.f10 + 3;
	x.f11 = x.f11 + 3;
	x.f12 = x.f12 + 3;
	x.f13 = x.f13 + 3;
	x.f14 = x.f14 + 3;
	return x;
}

void
main(void)
{
	{
	S2 r;
	r = f0((uint)1063901936U);
	pS2("ret f0", r);
	}
	{
	uint r;
	r = f1((vlong)-1000729398LL, (uint)1507681511U, (uchar)152);
	print("ret f1 uint %ud\n", r);
	}
	{
	float r;
	r = f2((long)1951461086L, (char)15);
	print("ret f2 float %g\n", r);
	}
	{
	short r;
	r = f3((uchar)213, (vlong)754709126LL, (float)-37.125, (float)-36.000);
	print("ret f3 short %d\n", r);
	}
	{
	uchar r;
	r = f4((ulong)1705440814UL);
	print("ret f4 uchar %ud\n", r);
	}
	{
	S0 v1;
	uint r;
	v1.f0 = 1642268276L;
	v1.f1 = -1736741L;
	v1.f2 = 86;
	v1.f3 = 29575;
	v1.f4 = 44.000;
	v1.f5 = 233;
	r = f5((uint)1043892296U, v1, (vlong)1550849061533234LL, (uchar)170, (short)30043, (short)28428);
	print("ret f5 uint %ud\n", r);
	}
	{
	S3 v0;
	long r;
	v0.f0 = 861044562L;
	r = f6(v0);
	print("ret f6 long %ld\n", r);
	}
	{
	S0 v1;
	S2 r;
	v1.f0 = 1840027579L;
	v1.f1 = 199496044L;
	v1.f2 = -29;
	v1.f3 = 1230;
	v1.f4 = -31.125;
	v1.f5 = 48;
	r = f7((vlong)-4610444363103433114LL, v1);
	pS2("ret f7", r);
	}
	{
	S3 v0;
	S1 r;
	v0.f0 = 1178479061L;
	r = f8(v0, (double)43.875);
	pS1("ret f8", r);
	}
	{
	ulong r;
	r = f9((long)-516930543L);
	print("ret f9 ulong %lud\n", r);
	}
	vf(3, (uint)453758005U, (int)-960710118, (long)1467662231L);
	{
	S2 x, r;

	x.f0[0] = 121;
	x.f0[1] = -42;
	x.f0[2] = 91;
	x.f0[3] = 12;
	x.f0[4] = -61;
	x.f0[5] = 110;
	x.f1 = 190871711;
	x.f2 = -697823824LL;
	x.f3 = 1;
	x.f4 = 1711728050UL;
	x.f5 = 71196515U;
	x.f6 = 22804;
	x.f7 = 1085100741L;
	x.f8 = 1592052854U;
	x.f9 = -34.125;
	x.f10 = 458473432L;
	x.f11 = -965425545;
	x.f12 = 1472377658LL;
	x.f13 = 107;
	x.f14 = -28;
	r = cb(back, x);
	pS2("ret cb", r);
	}
	exits(nil);
}
#endif
