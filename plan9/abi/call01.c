#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { double f0; ushort f1; uvlong f2; double f3; uchar f4; ushort f5; uchar f6; long f7; vlong f8; uint f9; short f10; };
typedef struct S1 S1;
struct S1 { short f0; float f1; int f2; short f3; double f4; int f5; };
typedef struct S2 S2;
struct S2 { char f0[4]; int f1; short f2; uchar f3; char f4[9]; ushort f5; long f6; int f7; char f8; uchar f9; };
typedef struct S3 S3;
struct S3 { int f0; short f1; ulong f2; float f3; short f4; };

S3 f0(S2 a0, uint a1);
float f1(uvlong a0);
int f2(vlong a0, uchar a1);
uchar f3(double a0, ulong a1, S3 a2, S1 a3, int a4, char a5);
vlong f4(S2 a0, uchar a1, ushort a2, S0 a3, short a4, uchar a5, double a6, float a7);
double f5(uchar a0);
uint f6(int a0, S2 a1, S0 a2, uvlong a3, uint a4, S2 a5);
char f7(ushort a0);
double f8(S3 a0);
ulong f9(S1 a0, double a1, S1 a2, S0 a3);
void vf(int n, ...);
S3 cb(S3 (*fn)(S3, double, vlong), S3 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %g %ud %llud %g %ud %ud %ud %ld %lld %ud %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %d %g %d %d %g %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d %d %d %d %d %d %ud %d %d %d %d %d %d %d %d %d %ud %ld %d %d %ud\n", w, s.f0[0], s.f0[1], s.f0[2], s.f0[3], s.f1, s.f2, s.f3, s.f4[0], s.f4[1], s.f4[2], s.f4[3], s.f4[4], s.f4[5], s.f4[6], s.f4[7], s.f4[8], s.f5, s.f6, s.f7, s.f8, s.f9);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %d %d %lud %g %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4);
}

S3
f0(S2 a0, uint a1)
{
	S3 r;

	print("in f0\n");
	pS2("a0", a0);
	print("a1 uint %ud\n", a1);
	r.f0 = -218958108;
	r.f1 = 717;
	r.f2 = 1232862334UL;
	r.f3 = 8.125;
	r.f4 = 28640;
	return r;
}

float
f1(uvlong a0)
{
	print("in f1\n");
	print("a0 uvlong %llud\n", a0);
	return -31.750;
}

int
f2(vlong a0, uchar a1)
{
	print("in f2\n");
	print("a0 vlong %lld\n", a0);
	print("a1 uchar %ud\n", a1);
	return 797324448;
}

uchar
f3(double a0, ulong a1, S3 a2, S1 a3, int a4, char a5)
{
	print("in f3\n");
	print("a0 double %g\n", a0);
	print("a1 ulong %lud\n", a1);
	pS3("a2", a2);
	pS1("a3", a3);
	print("a4 int %d\n", a4);
	print("a5 char %d\n", a5);
	return 151;
}

vlong
f4(S2 a0, uchar a1, ushort a2, S0 a3, short a4, uchar a5, double a6, float a7)
{
	print("in f4\n");
	pS2("a0", a0);
	print("a1 uchar %ud\n", a1);
	print("a2 ushort %ud\n", a2);
	pS0("a3", a3);
	print("a4 short %d\n", a4);
	print("a5 uchar %ud\n", a5);
	print("a6 double %g\n", a6);
	print("a7 float %g\n", a7);
	return 1502035864LL;
}

double
f5(uchar a0)
{
	print("in f5\n");
	print("a0 uchar %ud\n", a0);
	return 16.625;
}

uint
f6(int a0, S2 a1, S0 a2, uvlong a3, uint a4, S2 a5)
{
	print("in f6\n");
	print("a0 int %d\n", a0);
	pS2("a1", a1);
	pS0("a2", a2);
	print("a3 uvlong %llud\n", a3);
	print("a4 uint %ud\n", a4);
	pS2("a5", a5);
	return 566215745U;
}

char
f7(ushort a0)
{
	print("in f7\n");
	print("a0 ushort %ud\n", a0);
	return -101;
}

double
f8(S3 a0)
{
	print("in f8\n");
	pS3("a0", a0);
	return -2.625;
}

ulong
f9(S1 a0, double a1, S1 a2, S0 a3)
{
	print("in f9\n");
	pS1("a0", a0);
	print("a1 double %g\n", a1);
	pS1("a2", a2);
	pS0("a3", a3);
	return 637629972UL;
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
	print("%s S0 %g %ud %llud %g %ud %ud %ud %ld %lld %ud %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %d %g %d %d %g %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d %d %d %d %d %d %ud %d %d %d %d %d %d %d %d %d %ud %ld %d %d %ud\n", w, s.f0[0], s.f0[1], s.f0[2], s.f0[3], s.f1, s.f2, s.f3, s.f4[0], s.f4[1], s.f4[2], s.f4[3], s.f4[4], s.f4[5], s.f4[6], s.f4[7], s.f4[8], s.f5, s.f6, s.f7, s.f8, s.f9);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %d %d %lud %g %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4);
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
	return x;
}

void
main(void)
{
	{
	S2 v0;
	S3 r;
	v0.f0[0] = 104;
	v0.f0[1] = 25;
	v0.f0[2] = -74;
	v0.f0[3] = 123;
	v0.f1 = 26296876;
	v0.f2 = -15325;
	v0.f3 = 142;
	v0.f4[0] = 63;
	v0.f4[1] = -112;
	v0.f4[2] = 33;
	v0.f4[3] = 82;
	v0.f4[4] = -3;
	v0.f4[5] = 52;
	v0.f4[6] = 101;
	v0.f4[7] = -22;
	v0.f4[8] = 71;
	v0.f5 = 63096;
	v0.f6 = -174223401L;
	v0.f7 = 681175514;
	v0.f8 = 11;
	v0.f9 = 60;
	r = f0(v0, (uint)1695079740U);
	pS3("ret f0", r);
	}
	{
	float r;
	r = f1((uvlong)1631907202ULL);
	print("ret f1 float %g\n", r);
	}
	{
	int r;
	r = f2((vlong)1568734664LL, (uchar)121);
	print("ret f2 int %d\n", r);
	}
	{
	S3 v2;
	S1 v3;
	uchar r;
	v2.f0 = 2012514239;
	v2.f1 = 368;
	v2.f2 = 878934817UL;
	v2.f3 = 31.750;
	v2.f4 = 28291;
	v3.f0 = -2451;
	v3.f1 = 49.500;
	v3.f2 = 280558837;
	v3.f3 = -30374;
	v3.f4 = 52.125;
	v3.f5 = 1801415176;
	r = f3((double)-29.125, (ulong)1322714392UL, v2, v3, (int)1829666505, (char)122);
	print("ret f3 uchar %ud\n", r);
	}
	{
	S2 v0;
	S0 v3;
	vlong r;
	v0.f0[0] = 64;
	v0.f0[1] = 113;
	v0.f0[2] = -34;
	v0.f0[3] = 83;
	v0.f1 = 6287236;
	v0.f2 = -26933;
	v0.f3 = 230;
	v0.f4[0] = 23;
	v0.f4[1] = -72;
	v0.f4[2] = 121;
	v0.f4[3] = 42;
	v0.f4[4] = -91;
	v0.f4[5] = 12;
	v0.f4[6] = 61;
	v0.f4[7] = -110;
	v0.f4[8] = 31;
	v0.f5 = 41936;
	v0.f6 = -154213761L;
	v0.f7 = 661165874;
	v0.f8 = 99;
	v0.f9 = 148;
	v3.f0 = 32.500;
	v3.f1 = 1093;
	v3.f2 = 541490678ULL;
	v3.f3 = 35.125;
	v3.f4 = 88;
	v3.f5 = 60169;
	v3.f6 = 186;
	v3.f7 = 928767595L;
	v3.f8 = 1435719708LL;
	v3.f9 = 1942671821U;
	v3.f10 = 19326;
	r = f4(v0, (uchar)104, (ushort)34329, v3, (short)32714, (uchar)123, (double)56.500, (float)-40.375);
	print("ret f4 vlong %lld\n", r);
	}
	{
	double r;
	r = f5((uchar)35);
	print("ret f5 double %g\n", r);
	}
	{
	S2 v1;
	S0 v2;
	S2 v5;
	uint r;
	v1.f0[0] = 105;
	v1.f0[1] = -26;
	v1.f0[2] = 75;
	v1.f0[3] = 124;
	v1.f1 = -1217950765;
	v1.f2 = 28126;
	v1.f3 = 143;
	v1.f4[0] = -64;
	v1.f4[1] = 113;
	v1.f4[2] = 34;
	v1.f4[3] = -83;
	v1.f4[4] = 4;
	v1.f4[5] = 53;
	v1.f4[6] = -102;
	v1.f4[7] = 23;
	v1.f4[8] = 72;
	v1.f5 = 10361;
	v1.f6 = 1365877290L;
	v1.f7 = 1872829403;
	v1.f8 = -12;
	v1.f9 = 61;
	v2.f0 = 56.375;
	v2.f1 = 35054;
	v2.f2 = 1753159466462628ULL;
	v2.f3 = -38.000;
	v2.f4 = 1;
	v2.f5 = 28594;
	v2.f6 = 99;
	v2.f7 = 2140431124L;
	v2.f8 = -4611186117338689144LL;
	v2.f9 = 1006851702U;
	v2.f10 = 20519;
	v5.f0[0] = -17;
	v5.f0[1] = 66;
	v5.f0[2] = 115;
	v5.f0[3] = -36;
	v5.f1 = 21198805;
	v5.f2 = 29062;
	v5.f3 = 55;
	v5.f4[0] = 104;
	v5.f4[1] = 25;
	v5.f4[2] = -74;
	v5.f4[3] = 123;
	v5.f4[4] = 44;
	v5.f4[5] = -93;
	v5.f4[6] = 14;
	v5.f4[7] = 63;
	v5.f4[8] = -112;
	v5.f5 = 11297;
	v5.f6 = 169125330L;
	v5.f7 = -676077443;
	v5.f8 = 52;
	v5.f9 = 229;
	r = f6((int)1689981669, v1, v2, (uvlong)49450134ULL, (uint)556402247U, v5);
	print("ret f6 uint %ud\n", r);
	}
	{
	char r;
	r = f7((ushort)5773);
	print("ret f7 char %d\n", r);
	}
	{
	S3 v0;
	double r;
	v0.f0 = 430057171;
	v0.f1 = -8324;
	v0.f2 = 1443961397UL;
	v0.f3 = -17.250;
	v0.f4 = -3479;
	r = f8(v0);
	print("ret f8 double %g\n", r);
	}
	{
	S1 v0;
	S1 v2;
	S0 v3;
	ulong r;
	v0.f0 = 16188;
	v0.f1 = 38.375;
	v0.f2 = 275460766;
	v0.f3 = 11343;
	v0.f4 = 41.000;
	v0.f5 = 1796317105;
	v2.f0 = 16656;
	v2.f1 = -39.875;
	v2.f2 = -1824568434;
	v2.f3 = 11811;
	v2.f4 = -36.500;
	v2.f5 = -1197941125;
	v3.f0 = -20.500;
	v3.f1 = 48277;
	v3.f2 = 1226192454ULL;
	v3.f3 = -17.125;
	v3.f4 = 168;
	v3.f5 = 41817;
	v3.f6 = 10;
	v3.f7 = 1613469371L;
	v3.f8 = 2120421484LL;
	v3.f9 = 479889949U;
	v3.f10 = 974;
	r = f9(v0, (double)0.000, v2, v3);
	print("ret f9 ulong %lud\n", r);
	}
	vf(1, (ulong)1698223358UL);
	{
	S3 x, r;

	x.f0 = 541108034;
	x.f1 = 8435;
	x.f2 = 1555012260UL;
	x.f3 = -29.375;
	x.f4 = 3590;
	r = cb(back, x);
	pS3("ret cb", r);
	}
	exits(nil);
}
#endif
