#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { uint f0; };
typedef struct S1 S1;
struct S1 { short f0; uchar f1; };
typedef struct S2 S2;
struct S2 { ulong f0; ushort f1; float f2; uchar f3; float f4; ulong f5; uchar f6; int f7; char f8; double f9; int f10; double f11; long f12; ulong f13; uchar f14; double f15; short f16; };
typedef struct S3 S3;
struct S3 { double f0; uint f1; double f2; float f3; uvlong f4; long f5; double f6; short f7; ushort f8; ulong f9; uint f10; uchar f11; char f12; float f13; short f14; };

void f0(uchar a0, ulong a1, long a2, int a3, S2 a4, vlong a5);
void f1(S0 a0, double a1, S1 a2);
ushort f2(short a0);
uint f3(uchar a0);
uchar f4(S2 a0, uchar a1, uint a2, uint a3, float a4, short a5);
uchar f5(ulong a0, short a1, double a2, float a3);
float f6(ushort a0, ushort a1, S1 a2, short a3, uchar a4, double a5);
int f7(int a0, long a1, char a2, ushort a3);
S0 f8(S0 a0, S3 a1, S2 a2, double a3, int a4, char a5, S3 a6, S1 a7);
float f9(ulong a0, uvlong a1, int a2, char a3, short a4, double a5);
void vf(int n, ...);
S0 cb(S0 (*fn)(S0, double, vlong), S0 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %ud\n", w, s.f0);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %d %ud\n", w, s.f0, s.f1);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %lud %ud %g %ud %g %lud %ud %d %d %g %d %g %ld %lud %ud %g %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11, s.f12, s.f13, s.f14, s.f15, s.f16);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %g %ud %g %g %llud %ld %g %d %ud %lud %ud %ud %d %g %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11, s.f12, s.f13, s.f14);
}

void
f0(uchar a0, ulong a1, long a2, int a3, S2 a4, vlong a5)
{
	print("in f0\n");
	print("a0 uchar %ud\n", a0);
	print("a1 ulong %lud\n", a1);
	print("a2 long %ld\n", a2);
	print("a3 int %d\n", a3);
	pS2("a4", a4);
	print("a5 vlong %lld\n", a5);
}

void
f1(S0 a0, double a1, S1 a2)
{
	print("in f1\n");
	pS0("a0", a0);
	print("a1 double %g\n", a1);
	pS1("a2", a2);
}

ushort
f2(short a0)
{
	print("in f2\n");
	print("a0 short %d\n", a0);
	return 7868;
}

uint
f3(uchar a0)
{
	print("in f3\n");
	print("a0 uchar %ud\n", a0);
	return 1461333762U;
}

uchar
f4(S2 a0, uchar a1, uint a2, uint a3, float a4, short a5)
{
	print("in f4\n");
	pS2("a0", a0);
	print("a1 uchar %ud\n", a1);
	print("a2 uint %ud\n", a2);
	print("a3 uint %ud\n", a3);
	print("a4 float %g\n", a4);
	print("a5 short %d\n", a5);
	return 72;
}

uchar
f5(ulong a0, short a1, double a2, float a3)
{
	print("in f5\n");
	print("a0 ulong %lud\n", a0);
	print("a1 short %d\n", a1);
	print("a2 double %g\n", a2);
	print("a3 float %g\n", a3);
	return 38;
}

float
f6(ushort a0, ushort a1, S1 a2, short a3, uchar a4, double a5)
{
	print("in f6\n");
	print("a0 ushort %ud\n", a0);
	print("a1 ushort %ud\n", a1);
	pS1("a2", a2);
	print("a3 short %d\n", a3);
	print("a4 uchar %ud\n", a4);
	print("a5 double %g\n", a5);
	return -29.125;
}

int
f7(int a0, long a1, char a2, ushort a3)
{
	print("in f7\n");
	print("a0 int %d\n", a0);
	print("a1 long %ld\n", a1);
	print("a2 char %d\n", a2);
	print("a3 ushort %ud\n", a3);
	return -1293397597;
}

S0
f8(S0 a0, S3 a1, S2 a2, double a3, int a4, char a5, S3 a6, S1 a7)
{
	S0 r;

	print("in f8\n");
	pS0("a0", a0);
	pS3("a1", a1);
	pS2("a2", a2);
	print("a3 double %g\n", a3);
	print("a4 int %d\n", a4);
	print("a5 char %d\n", a5);
	pS3("a6", a6);
	pS1("a7", a7);
	r = a0;
	r.f0 = r.f0 + 3;
	return r;
}

float
f9(ulong a0, uvlong a1, int a2, char a3, short a4, double a5)
{
	print("in f9\n");
	print("a0 ulong %lud\n", a0);
	print("a1 uvlong %llud\n", a1);
	print("a2 int %d\n", a2);
	print("a3 char %d\n", a3);
	print("a4 short %d\n", a4);
	print("a5 double %g\n", a5);
	return 20.750;
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %d\n", va_arg(ap, int));
	print("v1 %lud\n", va_arg(ap, ulong));
	print("v2 %lld\n", va_arg(ap, vlong));
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
	print("%s S0 %ud\n", w, s.f0);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %d %ud\n", w, s.f0, s.f1);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %lud %ud %g %ud %g %lud %ud %d %d %g %d %g %ld %lud %ud %g %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11, s.f12, s.f13, s.f14, s.f15, s.f16);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %g %ud %g %g %llud %ld %g %d %ud %lud %ud %ud %d %g %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11, s.f12, s.f13, s.f14);
}

static S0
back(S0 x, double d, vlong v)
{
	pS0("back x", x);
	print("back %g %lld\n", d, v);
	x.f0 = x.f0 + 3;
	return x;
}

void
main(void)
{
	{
	S2 v4;
	v4.f0 = 42097432UL;
	v4.f1 = 54473;
	v4.f2 = 24.750;
	v4.f3 = 43;
	v4.f4 = 26.500;
	v4.f5 = 429374349UL;
	v4.f6 = 62;
	v4.f7 = 1443278575;
	v4.f8 = 32;
	v4.f9 = 31.875;
	v4.f10 = 816651266;
	v4.f11 = 33.625;
	v4.f12 = -1830555492L;
	v4.f13 = 190023957UL;
	v4.f14 = 198;
	v4.f15 = 37.125;
	v4.f16 = 30248;
	f0((uchar)236, (ulong)2098157213UL, (long)457625678L, (int)964577791, v4, (vlong)-1471529904LL);
	}
	{
	S0 v0;
	S1 v2;
	v0.f0 = 1408357366U;
	v2.f0 = 21962;
	v2.f1 = 123;
	f1(v0, (double)27.250, v2);
	}
	{
	ushort r;
	r = f2((short)26596);
	print("ret f2 ushort %ud\n", r);
	}
	{
	uint r;
	r = f3((uchar)42);
	print("ret f3 uint %ud\n", r);
	}
	{
	S2 v0;
	uchar r;
	v0.f0 = 22087792UL;
	v0.f1 = 33313;
	v0.f2 = 46.750;
	v0.f3 = 131;
	v0.f4 = 48.500;
	v0.f5 = 409364709UL;
	v0.f6 = 150;
	v0.f7 = 1423268935;
	v0.f8 = 120;
	v0.f9 = 53.875;
	v0.f10 = 796641626;
	v0.f11 = 55.625;
	v0.f12 = -1810545852L;
	v0.f13 = 170014317UL;
	v0.f14 = 30;
	v0.f15 = -38.125;
	v0.f16 = 9088;
	r = f4(v0, (uchar)68, (uint)2078147573U, (uint)437616038U, (float)-30.125, (short)-28936);
	print("ret f4 uchar %ud\n", r);
	}
	{
	uchar r;
	r = f5((ulong)1388347726UL, (short)-31487, (double)11.000, (float)12.875);
	print("ret f5 uchar %ud\n", r);
	}
	{
	S1 v2;
	float r;
	v2.f0 = 32423;
	v2.f1 = 88;
	r = f6((ushort)32891, (ushort)64044, v2, (short)29661, (uchar)142, (double)-23.125);
	print("ret f6 float %g\n", r);
	}
	{
	int r;
	r = f7((int)-2064807813, (long)424276278L, (char)103, (ushort)58520);
	print("ret f7 int %d\n", r);
	}
	{
	S0 v0;
	S3 v1;
	S2 v2;
	S3 v6;
	S1 v7;
	S0 r;
	v0.f0 = 1375007966U;
	v1.f0 = -21.750;
	v1.f1 = 1283584099U;
	v1.f2 = -19.500;
	v1.f3 = -18.375;
	v1.f4 = 656956790ULL;
	v1.f5 = -1163908903L;
	v1.f6 = -15.000;
	v1.f7 = 19081;
	v1.f8 = 17466;
	v1.f9 = 1044233707UL;
	v1.f10 = 1551185820U;
	v1.f11 = 77;
	v1.f12 = 126;
	v1.f13 = -8.125;
	v1.f14 = -7776;
	v2.f0 = 178256006UL;
	v2.f1 = 29239;
	v2.f2 = 1.000;
	v2.f3 = 153;
	v2.f4 = 3.750;
	v2.f5 = 565532923UL;
	v2.f6 = 172;
	v2.f7 = 1579437149;
	v2.f8 = 14;
	v2.f9 = 8.125;
	v2.f10 = 952809840;
	v2.f11 = 10.875;
	v2.f12 = -1966714066L;
	v2.f13 = 326182531UL;
	v2.f14 = 52;
	v2.f15 = 14.375;
	v2.f16 = 5014;
	v6.f0 = 19.750;
	v6.f1 = 86832139U;
	v6.f2 = 21.500;
	v6.f3 = 22.375;
	v6.f4 = 1607688478ULL;
	v6.f5 = 2114640591L;
	v6.f6 = 25.000;
	v6.f7 = -20017;
	v6.f8 = 18402;
	v6.f9 = 1994965395UL;
	v6.f10 = 354433860U;
	v6.f11 = 245;
	v6.f12 = 38;
	v6.f13 = 32.125;
	v6.f14 = 8712;
	v7.f0 = 31790;
	v7.f1 = 223;
	r = f8(v0, v1, v2, (double)-38.750, (int)1037563827, (char)100, v6, v7);
	pS0("ret f8", r);
	}
	{
	float r;
	r = f9((ulong)1481343402UL, (uvlong)1988301479886552ULL, (int)-347763980, (char)61, (short)26734, (double)7.125);
	print("ret f9 float %g\n", r);
	}
	vf(3, (int)1805447781, (ulong)164916246UL, (vlong)671870374605084LL);
	{
	S0 x, r;

	x.f0 = 648332457U;
	r = cb(back, x);
	pS0("ret cb", r);
	}
	exits(nil);
}
#endif
