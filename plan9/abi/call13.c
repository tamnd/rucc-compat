#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { vlong f0; short f1; short f2; };
typedef struct S1 S1;
struct S1 { uchar f0; char f1; };
typedef struct S2 S2;
struct S2 { ulong f0; };
typedef struct S3 S3;
struct S3 { int f0; ushort f1; short f2; double f3; uchar f4; float f5; ulong f6; ulong f7; vlong f8; double f9; ushort f10; char f11; };

double f0(char a0);
ulong f1(long a0, short a1, S2 a2);
S2 f2(float a0, S3 a1, ushort a2, S3 a3);
S3 f3(vlong a0, int a1, uchar a2, float a3);
S1 f4(char a0, double a1);
void f5(S2 a0, long a1, float a2, int a3, double a4, vlong a5);
int f6(vlong a0, ushort a1);
S3 f7(uchar a0, ushort a1, double a2, uint a3, S0 a4, short a5);
S0 f8(ushort a0, ulong a1, double a2);
long f9(char a0, float a1);
void vf(int n, ...);
S3 cb(S3 (*fn)(S3, double, vlong), S3 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %lld %d %d\n", w, s.f0, s.f1, s.f2);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %ud %d\n", w, s.f0, s.f1);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %lud\n", w, s.f0);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %d %ud %d %g %ud %g %lud %lud %lld %g %ud %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11);
}

double
f0(char a0)
{
	print("in f0\n");
	print("a0 char %d\n", a0);
	return -20.000;
}

ulong
f1(long a0, short a1, S2 a2)
{
	print("in f1\n");
	print("a0 long %ld\n", a0);
	print("a1 short %d\n", a1);
	pS2("a2", a2);
	return 1063054182UL;
}

S2
f2(float a0, S3 a1, ushort a2, S3 a3)
{
	S2 r;

	print("in f2\n");
	print("a0 float %g\n", a0);
	pS3("a1", a1);
	print("a2 ushort %ud\n", a2);
	pS3("a3", a3);
	r.f0 = 1752854029UL;
	return r;
}

S3
f3(vlong a0, int a1, uchar a2, float a3)
{
	S3 r;

	print("in f3\n");
	print("a0 vlong %lld\n", a0);
	print("a1 int %d\n", a1);
	print("a2 uchar %ud\n", a2);
	print("a3 float %g\n", a3);
	r.f0 = 999881644;
	r.f1 = 30045;
	r.f2 = 28430;
	r.f3 = -38.125;
	r.f4 = 112;
	r.f5 = -36.875;
	r.f6 = 1894110674UL;
	r.f7 = 253579139UL;
	r.f8 = 760531252LL;
	r.f9 = -32.375;
	r.f10 = 48278;
	r.f11 = 71;
	return r;
}

S1
f4(char a0, double a1)
{
	S1 r;

	print("in f4\n");
	print("a0 char %d\n", a0);
	print("a1 double %g\n", a1);
	r.f0 = 5;
	r.f1 = 54;
	return r;
}

void
f5(S2 a0, long a1, float a2, int a3, double a4, vlong a5)
{
	print("in f5\n");
	pS2("a0", a0);
	print("a1 long %ld\n", a1);
	print("a2 float %g\n", a2);
	print("a3 int %d\n", a3);
	print("a4 double %g\n", a4);
	print("a5 vlong %lld\n", a5);
}

int
f6(vlong a0, ushort a1)
{
	print("in f6\n");
	print("a0 vlong %lld\n", a0);
	print("a1 ushort %ud\n", a1);
	return 1275725054;
}

S3
f7(uchar a0, ushort a1, double a2, uint a3, S0 a4, short a5)
{
	S3 r;

	print("in f7\n");
	print("a0 uchar %ud\n", a0);
	print("a1 ushort %ud\n", a1);
	print("a2 double %g\n", a2);
	print("a3 uint %ud\n", a3);
	pS0("a4", a4);
	print("a5 short %d\n", a5);
	r.f0 = -416417233;
	r.f1 = 32642;
	r.f2 = 31027;
	r.f3 = 46.500;
	r.f4 = 149;
	r.f5 = 48.250;
	r.f6 = 1310646263UL;
	r.f7 = 1817598376UL;
	r.f8 = 177067372200530LL;
	r.f9 = 52.750;
	r.f10 = 50875;
	r.f11 = 108;
	return r;
}

S0
f8(ushort a0, ulong a1, double a2)
{
	S0 r;

	print("in f8\n");
	print("a0 ushort %ud\n", a0);
	print("a1 ulong %lud\n", a1);
	print("a2 double %g\n", a2);
	r.f0 = 1782682515031508LL;
	r.f1 = -30816;
	r.f2 = 29201;
	return r;
}

long
f9(char a0, float a1)
{
	print("in f9\n");
	print("a0 char %d\n", a0);
	print("a1 float %g\n", a1);
	return 1889012603L;
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %g\n", va_arg(ap, double));
	print("v1 %ud\n", va_arg(ap, uint));
	print("v2 %d\n", va_arg(ap, int));
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
	print("%s S0 %lld %d %d\n", w, s.f0, s.f1, s.f2);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %ud %d\n", w, s.f0, s.f1);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %lud\n", w, s.f0);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %d %ud %d %g %ud %g %lud %lud %lld %g %ud %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11);
}

static S3
back(S3 x, double d, vlong v)
{
	pS3("back x", x);
	print("back %g %lld\n", d, v);
	x.f0 = x.f0 + 3;
	x.f1 = x.f1 + 3;
	x.f2 = x.f2 + 3;
	x.f3 = x.f3 * 2;
	x.f4 = x.f4 + 3;
	x.f5 = x.f5 * 2;
	x.f6 = x.f6 + 3;
	x.f7 = x.f7 + 3;
	x.f8 = x.f8 + 3;
	x.f9 = x.f9 * 2;
	x.f10 = x.f10 + 3;
	x.f11 = x.f11 + 3;
	return x;
}

void
main(void)
{
	{
	double r;
	r = f0((char)72);
	print("ret f0 double %g\n", r);
	}
	{
	S2 v2;
	ulong r;
	v2.f0 = 1834464398UL;
	r = f1((long)1236088418L, (short)-12307, v2);
	print("ret f1 ulong %lud\n", r);
	}
	{
	S3 v1;
	S3 v3;
	S2 r;
	v1.f0 = 1679867993;
	v1.f1 = 14858;
	v1.f2 = 13243;
	v1.f3 = -35.500;
	v1.f4 = 29;
	v1.f5 = -33.250;
	v1.f6 = 426613375UL;
	v1.f7 = 933565488UL;
	v1.f8 = 1440521922552810LL;
	v1.f9 = -29.750;
	v1.f10 = 33091;
	v1.f11 = 116;
	v3.f0 = 1081492013;
	v3.f1 = 48094;
	v3.f2 = -13711;
	v3.f3 = -15.000;
	v3.f4 = 241;
	v3.f5 = -13.750;
	v3.f6 = 1975721043UL;
	v3.f7 = 335189508UL;
	v3.f8 = -4610843874279963048LL;
	v3.f9 = -9.250;
	v3.f10 = 791;
	v3.f11 = -72;
	r = f2((float)2.875, v1, (ushort)15794, v3);
	pS2("ret f2", r);
	}
	{
	S3 r;
	r = f3((vlong)-926895608LL, (int)1433847721, (uchar)90, (float)44.625);
	pS3("ret f3", r);
	}
	{
	S1 r;
	r = f4((char)81, (double)-14.750);
	pS1("ret f4", r);
	}
	{
	S2 v0;
	v0.f0 = 680875336UL;
	f5(v0, (long)82499356L, (float)45.375, (int)-1096403582, (double)47.125, (vlong)2110307808LL);
	}
	{
	int r;
	r = f6((vlong)2047135270LL, (ushort)18391);
	print("ret f6 int %d\n", r);
	}
	{
	S0 v4;
	S3 r;
	v4.f0 = 343432227293598LL;
	v4.f1 = 20942;
	v4.f2 = -19327;
	r = f7((uchar)241, (ushort)21410, (double)50.625, (uint)1265911556U, v4, (short)16565);
	pS3("ret f7", r);
	}
	{
	S0 r;
	r = f8((ushort)53499, (ulong)69159596UL, (double)-5.375);
	pS0("ret f8", r);
	}
	{
	long r;
	r = f9((char)35, (float)34.500);
	print("ret f9 long %ld\n", r);
	}
	vf(3, (double)-25.750, (uint)1463670859U, (int)-1970622972);
	{
	S3 x, r;

	x.f0 = 1947087070;
	x.f1 = 43663;
	x.f2 = -9280;
	x.f3 = 5.875;
	x.f4 = 162;
	x.f5 = 7.625;
	x.f6 = 693832452UL;
	x.f7 = 1200784565UL;
	x.f8 = -1707736678LL;
	x.f9 = 11.125;
	x.f10 = 61896;
	x.f11 = -121;
	r = cb(back, x);
	pS3("ret cb", r);
	}
	exits(nil);
}
#endif
