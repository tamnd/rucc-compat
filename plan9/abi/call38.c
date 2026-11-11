#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { long f0; float f1; ushort f2; short f3; short f4; long f5; double f6; int f7; ushort f8; };
typedef struct S1 S1;
struct S1 { ushort f0; char f1; char f2[9]; uchar f3; char f4; uchar f5; };
typedef struct S2 S2;
struct S2 { uchar f0[5]; long f1; ushort f2; ushort f3; ushort f4; ushort f5; };
typedef struct S3 S3;
struct S3 { char f0[4]; short f1; char f2; };

ulong f0(ushort a0, ulong a1, char a2);
S0 f1(uchar a0, uvlong a1, int a2, uchar a3, uvlong a4, double a5, float a6, ulong a7);
uchar f2(S1 a0, vlong a1, uint a2);
short f3(short a0, ushort a1, char a2, S2 a3, float a4, char a5);
int f4(long a0, S3 a1, S2 a2, S3 a3, ushort a4, long a5);
double f5(double a0, char a1, uchar a2, char a3, ulong a4, ushort a5, int a6, S3 a7);
float f6(ushort a0, short a1, ushort a2, S1 a3);
S3 f7(uvlong a0);
uint f8(ushort a0, S0 a1, S3 a2);
S0 f9(long a0, float a1, vlong a2, ushort a3);
void vf(int n, ...);
S2 cb(S2 (*fn)(S2, double, vlong), S2 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %ld %g %ud %d %d %ld %g %d %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %ud %d %d %d %d %d %d %d %d %d %d %ud %d %ud\n", w, s.f0, s.f1, s.f2[0], s.f2[1], s.f2[2], s.f2[3], s.f2[4], s.f2[5], s.f2[6], s.f2[7], s.f2[8], s.f3, s.f4, s.f5);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %ud %ud %ud %ud %ud %ld %ud %ud %ud %ud\n", w, s.f0[0], s.f0[1], s.f0[2], s.f0[3], s.f0[4], s.f1, s.f2, s.f3, s.f4, s.f5);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %d %d %d %d %d %d\n", w, s.f0[0], s.f0[1], s.f0[2], s.f0[3], s.f1, s.f2);
}

ulong
f0(ushort a0, ulong a1, char a2)
{
	print("in f0\n");
	print("a0 ushort %ud\n", a0);
	print("a1 ulong %lud\n", a1);
	print("a2 char %d\n", a2);
	return 480561224UL;
}

S0
f1(uchar a0, uvlong a1, int a2, uchar a3, uvlong a4, double a5, float a6, ulong a7)
{
	S0 r;

	print("in f1\n");
	print("a0 uchar %ud\n", a0);
	print("a1 uvlong %llud\n", a1);
	print("a2 int %d\n", a2);
	print("a3 uchar %ud\n", a3);
	print("a4 uvlong %llud\n", a4);
	print("a5 double %g\n", a5);
	print("a6 float %g\n", a6);
	print("a7 ulong %lud\n", a7);
	r.f0 = 128205516L;
	r.f1 = -8.375;
	r.f2 = 13870;
	r.f3 = 12255;
	r.f4 = -10640;
	r.f5 = 515482433L;
	r.f6 = -3.750;
	r.f7 = -1529386659;
	r.f8 = 4180;
	return r;
}

uchar
f2(S1 a0, vlong a1, uint a2)
{
	print("in f2\n");
	pS1("a0", a0);
	print("a1 vlong %lld\n", a1);
	print("a2 uint %ud\n", a2);
	return 13;
}

short
f3(short a0, ushort a1, char a2, S2 a3, float a4, char a5)
{
	print("in f3\n");
	print("a0 short %d\n", a0);
	print("a1 ushort %ud\n", a1);
	print("a2 char %d\n", a2);
	pS2("a3", a3);
	print("a4 float %g\n", a4);
	print("a5 char %d\n", a5);
	return 15320;
}

int
f4(long a0, S3 a1, S2 a2, S3 a3, ushort a4, long a5)
{
	print("in f4\n");
	print("a0 long %ld\n", a0);
	pS3("a1", a1);
	pS2("a2", a2);
	pS3("a3", a3);
	print("a4 ushort %ud\n", a4);
	print("a5 long %ld\n", a5);
	return 1833481398;
}

double
f5(double a0, char a1, uchar a2, char a3, ulong a4, ushort a5, int a6, S3 a7)
{
	print("in f5\n");
	print("a0 double %g\n", a0);
	print("a1 char %d\n", a1);
	print("a2 uchar %ud\n", a2);
	print("a3 char %d\n", a3);
	print("a4 ulong %lud\n", a4);
	print("a5 ushort %ud\n", a5);
	print("a6 int %d\n", a6);
	pS3("a7", a7);
	return -31.750;
}

float
f6(ushort a0, short a1, ushort a2, S1 a3)
{
	print("in f6\n");
	print("a0 ushort %ud\n", a0);
	print("a1 short %d\n", a1);
	print("a2 ushort %ud\n", a2);
	pS1("a3", a3);
	return 33.750;
}

S3
f7(uvlong a0)
{
	S3 r;

	print("in f7\n");
	print("a0 uvlong %llud\n", a0);
	r.f0[0] = 114;
	r.f0[1] = -35;
	r.f0[2] = 84;
	r.f0[3] = 5;
	r.f1 = -3382;
	r.f2 = 103;
	return r;
}

uint
f8(ushort a0, S0 a1, S3 a2)
{
	print("in f8\n");
	print("a0 ushort %ud\n", a0);
	pS0("a1", a1);
	pS3("a2", a2);
	return 1510948828U;
}

S0
f9(long a0, float a1, vlong a2, ushort a3)
{
	S0 r;

	print("in f9\n");
	print("a0 long %ld\n", a0);
	print("a1 float %g\n", a1);
	print("a2 vlong %lld\n", a2);
	print("a3 ushort %ud\n", a3);
	r.f0 = 1095420582L;
	r.f1 = 13.125;
	r.f2 = 48648;
	r.f3 = 14265;
	r.f4 = 12650;
	r.f5 = -1482697499L;
	r.f6 = 18.500;
	r.f7 = 349118077;
	r.f8 = 38958;
	return r;
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %g\n", va_arg(ap, double));
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
	print("%s S0 %ld %g %ud %d %d %ld %g %d %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %ud %d %d %d %d %d %d %d %d %d %d %ud %d %ud\n", w, s.f0, s.f1, s.f2[0], s.f2[1], s.f2[2], s.f2[3], s.f2[4], s.f2[5], s.f2[6], s.f2[7], s.f2[8], s.f3, s.f4, s.f5);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %ud %ud %ud %ud %ud %ld %ud %ud %ud %ud\n", w, s.f0[0], s.f0[1], s.f0[2], s.f0[3], s.f0[4], s.f1, s.f2, s.f3, s.f4, s.f5);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %d %d %d %d %d %d\n", w, s.f0[0], s.f0[1], s.f0[2], s.f0[3], s.f1, s.f2);
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
	ulong r;
	r = f0((ushort)37232, (ulong)1758923553UL, (char)82);
	print("ret f0 ulong %lud\n", r);
	}
	{
	S0 r;
	r = f1((uchar)24, (uvlong)562173279514786ULL, (int)1069123706, (uchar)43, (uvlong)2083027932ULL, (double)-19.375, (float)-18.250, (ulong)1456400623UL);
	pS0("ret f1", r);
	}
	{
	S1 v0;
	uchar r;
	v0.f0 = 63797;
	v0.f1 = 102;
	v0.f2[0] = 23;
	v0.f2[1] = -72;
	v0.f2[2] = 121;
	v0.f2[3] = 42;
	v0.f2[4] = -91;
	v0.f2[5] = 12;
	v0.f2[6] = 61;
	v0.f2[7] = -110;
	v0.f2[8] = 31;
	v0.f3 = 208;
	v0.f4 = -1;
	v0.f5 = 50;
	r = f2(v0, (vlong)794854489556322LL, (uint)1301804218U);
	print("ret f2 uchar %ud\n", r);
	}
	{
	S2 v3;
	short r;
	v3.f0[0] = 0;
	v3.f0[1] = 177;
	v3.f0[2] = 98;
	v3.f0[3] = 19;
	v3.f0[4] = 196;
	v3.f1 = 1625908597L;
	v3.f2 = 57126;
	v3.f3 = 22743;
	v3.f4 = 53896;
	v3.f5 = 19513;
	r = f3((short)1748, (ushort)133, (char)-54, v3, (float)6.125, (char)24);
	print("ret f3 short %d\n", r);
	}
	{
	S3 v1;
	S2 v2;
	S3 v3;
	int r;
	v1.f0[0] = 94;
	v1.f0[1] = 15;
	v1.f0[2] = -64;
	v1.f0[3] = 113;
	v1.f1 = 25762;
	v1.f2 = -83;
	v2.f0[0] = 178;
	v2.f0[1] = 99;
	v2.f0[2] = 20;
	v2.f0[3] = 197;
	v2.f0[4] = 118;
	v2.f1 = 246308903L;
	v2.f2 = 55768;
	v2.f3 = 21385;
	v2.f4 = 52538;
	v2.f5 = 18155;
	v3.f0[0] = 6;
	v3.f0[1] = -55;
	v3.f0[2] = 104;
	v3.f0[3] = 25;
	v3.f1 = -26698;
	v3.f2 = 123;
	r = f4((long)809763674L, v1, v2, v3, (ushort)32011, (long)-1823667900L);
	print("ret f4 int %d\n", r);
	}
	{
	S3 v7;
	double r;
	v7.f0[0] = 2;
	v7.f0[1] = -51;
	v7.f0[2] = 100;
	v7.f0[3] = 21;
	v7.f1 = -28102;
	v7.f2 = 119;
	r = f5((double)-29.250, (char)7, (uchar)56, (char)105, (ulong)1042444186UL, (ushort)59723, (int)2056348412, v7);
	print("ret f5 double %g\n", r);
	}
	{
	S1 v3;
	float r;
	v3.f0 = 29506;
	v3.f1 = 115;
	v3.f2[0] = 36;
	v3.f2[1] = -85;
	v3.f2[2] = 6;
	v3.f2[3] = 55;
	v3.f2[4] = -104;
	v3.f2[5] = 25;
	v3.f2[6] = 74;
	v3.f2[7] = -123;
	v3.f2[8] = 44;
	v3.f3 = 221;
	v3.f4 = -14;
	v3.f5 = 63;
	r = f6((ushort)62742, (short)-28359, (ushort)59512, v3);
	print("ret f6 float %g\n", r);
	}
	{
	S3 r;
	r = f7((uvlong)198047934ULL);
	pS3("ret f7", r);
	}
	{
	S0 v1;
	S3 v2;
	uint r;
	v1.f0 = 134875396L;
	v1.f1 = 17.375;
	v1.f2 = 64614;
	v1.f3 = 30231;
	v1.f4 = -28616;
	v1.f5 = 522152313L;
	v1.f6 = 22.750;
	v1.f7 = -1536056539;
	v1.f8 = 54924;
	v2.f0[0] = 88;
	v2.f0[1] = 9;
	v2.f0[2] = -58;
	v2.f0[3] = 107;
	v2.f1 = 29084;
	v2.f2 = -77;
	r = f8((ushort)3244, v1, v2);
	print("ret f8 uint %ud\n", r);
	}
	{
	S0 r;
	r = f9((long)1022434546L, (float)-2.625, (vlong)2036338772LL, (ushort)35333);
	pS0("ret f9", r);
	}
	vf(1, (double)38.625);
	{
	S2 x, r;

	x.f0[0] = 143;
	x.f0[1] = 64;
	x.f0[2] = 241;
	x.f0[3] = 162;
	x.f0[4] = 83;
	x.f1 = -1710279940L;
	x.f2 = 18101;
	x.f3 = 49254;
	x.f4 = 14871;
	x.f5 = 46024;
	r = cb(back, x);
	pS2("ret cb", r);
	}
	exits(nil);
}
#endif
