#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { uvlong f0; uint f1; float f2; long f3; ushort f4; char f5[4]; short f6; long f7; };
typedef struct S1 S1;
struct S1 { double f0; ushort f1; short f2; uchar f3; short f4; };
typedef struct S2 S2;
struct S2 { uint f0; ushort f1; };
typedef struct S3 S3;
struct S3 { short f0; float f1; char f2; uint f3; float f4; uvlong f5; ushort f6; uint f7; double f8; int f9; float f10; char f11; uvlong f12; long f13; char f14[2]; int f15; };

float f0(long a0, S3 a1, S1 a2, float a3, float a4, S1 a5, S1 a6, uvlong a7);
void f1(S1 a0, double a1, int a2, char a3, vlong a4, int a5, long a6, uint a7);
S2 f2(int a0, int a1);
float f3(uint a0, uchar a1, float a2);
double f4(uint a0, uvlong a1, S2 a2, int a3, uvlong a4, ulong a5);
float f5(S3 a0, uint a1);
float f6(vlong a0, short a1, float a2, double a3, S2 a4, S1 a5);
S1 f7(char a0, double a1);
double f8(uint a0, S1 a1, vlong a2, int a3, int a4, int a5, S1 a6, S3 a7);
uint f9(ushort a0, long a1, S0 a2, char a3);
void vf(int n, ...);
S3 cb(S3 (*fn)(S3, double, vlong), S3 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %llud %ud %g %ld %ud %d %d %d %d %d %ld\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5[0], s.f5[1], s.f5[2], s.f5[3], s.f6, s.f7);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %g %ud %d %ud %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %ud %ud\n", w, s.f0, s.f1);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %d %g %d %ud %g %llud %ud %ud %g %d %g %d %llud %ld %d %d %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11, s.f12, s.f13, s.f14[0], s.f14[1], s.f15);
}

float
f0(long a0, S3 a1, S1 a2, float a3, float a4, S1 a5, S1 a6, uvlong a7)
{
	print("in f0\n");
	print("a0 long %ld\n", a0);
	pS3("a1", a1);
	pS1("a2", a2);
	print("a3 float %g\n", a3);
	print("a4 float %g\n", a4);
	pS1("a5", a5);
	pS1("a6", a6);
	print("a7 uvlong %llud\n", a7);
	return 5.000;
}

void
f1(S1 a0, double a1, int a2, char a3, vlong a4, int a5, long a6, uint a7)
{
	print("in f1\n");
	pS1("a0", a0);
	print("a1 double %g\n", a1);
	print("a2 int %d\n", a2);
	print("a3 char %d\n", a3);
	print("a4 vlong %lld\n", a4);
	print("a5 int %d\n", a5);
	print("a6 long %ld\n", a6);
	print("a7 uint %ud\n", a7);
}

S2
f2(int a0, int a1)
{
	S2 r;

	print("in f2\n");
	print("a0 int %d\n", a0);
	print("a1 int %d\n", a1);
	r.f0 = 1601524941U;
	r.f1 = 52862;
	return r;
}

float
f3(uint a0, uchar a1, float a2)
{
	print("in f3\n");
	print("a0 uint %ud\n", a0);
	print("a1 uchar %ud\n", a1);
	print("a2 float %g\n", a2);
	return 35.000;
}

double
f4(uint a0, uvlong a1, S2 a2, int a3, uvlong a4, ulong a5)
{
	print("in f4\n");
	print("a0 uint %ud\n", a0);
	print("a1 uvlong %llud\n", a1);
	pS2("a2", a2);
	print("a3 int %d\n", a3);
	print("a4 uvlong %llud\n", a4);
	print("a5 ulong %lud\n", a5);
	return -22.000;
}

float
f5(S3 a0, uint a1)
{
	print("in f5\n");
	pS3("a0", a0);
	print("a1 uint %ud\n", a1);
	return 40.250;
}

float
f6(vlong a0, short a1, float a2, double a3, S2 a4, S1 a5)
{
	print("in f6\n");
	print("a0 vlong %lld\n", a0);
	print("a1 short %d\n", a1);
	print("a2 float %g\n", a2);
	print("a3 double %g\n", a3);
	pS2("a4", a4);
	pS1("a5", a5);
	return 1.000;
}

S1
f7(char a0, double a1)
{
	S1 r;

	print("in f7\n");
	print("a0 char %d\n", a0);
	print("a1 double %g\n", a1);
	r.f0 = -18.375;
	r.f1 = 59414;
	r.f2 = 25031;
	r.f3 = 120;
	r.f4 = -21801;
	return r;
}

double
f8(uint a0, S1 a1, vlong a2, int a3, int a4, int a5, S1 a6, S3 a7)
{
	print("in f8\n");
	print("a0 uint %ud\n", a0);
	pS1("a1", a1);
	print("a2 vlong %lld\n", a2);
	print("a3 int %d\n", a3);
	print("a4 int %d\n", a4);
	print("a5 int %d\n", a5);
	pS1("a6", a6);
	pS3("a7", a7);
	return 24.000;
}

uint
f9(ushort a0, long a1, S0 a2, char a3)
{
	print("in f9\n");
	print("a0 ushort %ud\n", a0);
	print("a1 long %ld\n", a1);
	pS0("a2", a2);
	print("a3 char %d\n", a3);
	return 1583087110U;
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %ld\n", va_arg(ap, long));
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
	print("%s S0 %llud %ud %g %ld %ud %d %d %d %d %d %ld\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5[0], s.f5[1], s.f5[2], s.f5[3], s.f6, s.f7);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %g %ud %d %ud %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %ud %ud\n", w, s.f0, s.f1);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %d %g %d %ud %g %llud %ud %ud %g %d %g %d %llud %ld %d %d %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11, s.f12, s.f13, s.f14[0], s.f14[1], s.f15);
}

static S3
back(S3 x, double d, vlong v)
{
	pS3("back x", x);
	print("back %g %lld\n", d, v);
	x.f0 = x.f0 + 3;
	x.f1 = x.f1 * 2;
	x.f2 = x.f2 + 3;
	x.f3 = x.f3 + 3;
	x.f4 = x.f4 * 2;
	x.f5 = x.f5 + 3;
	x.f6 = x.f6 + 3;
	x.f7 = x.f7 + 3;
	x.f8 = x.f8 * 2;
	x.f9 = x.f9 + 3;
	x.f10 = x.f10 * 2;
	x.f11 = x.f11 + 3;
	x.f12 = x.f12 + 3;
	x.f13 = x.f13 + 3;
	x.f14[0] = x.f14[0] + 3;
	x.f14[1] = x.f14[1] + 3;
	x.f15 = x.f15 + 3;
	return x;
}

void
main(void)
{
	{
	S3 v1;
	S1 v2;
	S1 v5;
	S1 v6;
	float r;
	v1.f0 = -13872;
	v1.f1 = -12.875;
	v1.f2 = 18;
	v1.f3 = 1605051203U;
	v1.f4 = -9.500;
	v1.f5 = 471473195415350ULL;
	v1.f6 = 36950;
	v1.f7 = 1485376007U;
	v1.f8 = -5.000;
	v1.f9 = -351796585;
	v1.f10 = -3.750;
	v1.f11 = 75;
	v1.f12 = 1872652924ULL;
	v1.f13 = 232121389L;
	v1.f14[0] = 94;
	v1.f14[1] = -15;
	v1.f15 = 1752977728;
	v2.f0 = 7.500;
	v2.f1 = 45493;
	v2.f2 = 11110;
	v2.f3 = 23;
	v2.f4 = -7880;
	v5.f0 = 27.000;
	v5.f1 = 13193;
	v5.f2 = -11578;
	v5.f3 = 235;
	v5.f4 = 8348;
	v6.f0 = 47.500;
	v6.f1 = 46429;
	v6.f2 = 12046;
	v6.f3 = 191;
	v6.f4 = 8816;
	r = f0((long)1985658240L, v1, v2, (float)-29.875, (float)-28.750, v5, v6, (uvlong)1359035008092800ULL);
	print("ret f0 float %g\n", r);
	}
	{
	S1 v0;
	v0.f0 = 11.875;
	v0.f1 = 46218;
	v0.f2 = -11835;
	v0.f3 = 236;
	v0.f4 = 8605;
	f1(v0, (double)31.375, (int)1204434526, (char)15, (vlong)-70855104LL, (int)577807217, (long)1084759330L, (uint)1591711443U);
	}
	{
	S2 r;
	r = f2((int)1528538905, (int)-2035491018);
	pS2("ret f2", r);
	}
	{
	float r;
	r = f3((uint)1972318480U, (uchar)193, (float)19.750);
	print("ret f3 float %g\n", r);
	}
	{
	S2 v2;
	double r;
	v2.f0 = 775566520U;
	v2.f1 = 44649;
	r = f4((uint)177190540U, (uvlong)684144705427966ULL, v2, (int)1191094766, (uvlong)1698051973140644ULL, (ulong)57515344UL);
	print("ret f4 double %g\n", r);
	}
	{
	S3 v0;
	float r;
	v0.f0 = 11670;
	v0.f1 = 23.125;
	v0.f2 = 120;
	v0.f3 = 1515199145U;
	v0.f4 = 26.750;
	v0.f5 = 381620867859176ULL;
	v0.f6 = 34748;
	v0.f7 = 1395523949U;
	v0.f8 = 30.250;
	v0.f9 = 261944527;
	v0.f10 = 32.000;
	v0.f11 = 49;
	v0.f12 = 1782800866ULL;
	v0.f13 = -142269331L;
	v0.f14[0] = 68;
	v0.f14[1] = 117;
	v0.f15 = -1663125670;
	r = f5(v0, (uint)1543450474U);
	print("ret f5 float %g\n", r);
	}
	{
	S2 v4;
	S1 v5;
	float r;
	v4.f0 = 1480277936U;
	v4.f1 = 47457;
	v5.f0 = 3.500;
	v5.f1 = 15157;
	v5.f2 = 13542;
	v5.f3 = 151;
	v5.f4 = -10312;
	r = f6((vlong)283525976LL, (short)15625, (float)25.750, (double)26.625, v4, v5);
	print("ret f6 float %g\n", r);
	}
	{
	S1 r;
	r = f7((char)-49, (double)-32.750);
	pS1("ret f7", r);
	}
	{
	S1 v1;
	S1 v6;
	S3 v7;
	double r;
	v1.f0 = 6.000;
	v1.f1 = 50265;
	v1.f2 = 15882;
	v1.f3 = 187;
	v1.f4 = 12652;
	v6.f0 = 26.500;
	v6.f1 = 17965;
	v6.f2 = 16350;
	v6.f3 = 143;
	v6.f4 = -13120;
	v7.f0 = 20048;
	v7.f1 = 47.875;
	v7.f2 = -50;
	v7.f3 = 361610083U;
	v7.f4 = 50.500;
	v7.f5 = 1375518435542934ULL;
	v7.f6 = 10358;
	v7.f7 = 241934887U;
	v7.f8 = 54.000;
	v7.f9 = 1255839113;
	v7.f10 = 56.750;
	v7.f11 = -107;
	v7.f12 = 629211804ULL;
	v7.f13 = 1136163917L;
	v7.f14[0] = -126;
	v7.f14[1] = 47;
	v7.f15 = 509536608;
	r = f8((uint)389861412U, v1, (vlong)896816215440582LL, (int)1403765638, (int)-1910717751, (int)270186216, v6, v7);
	print("ret f8 double %g\n", r);
	}
	{
	S0 v2;
	uint r;
	v2.f0 = 207013678ULL;
	v2.f1 = 713965791U;
	v2.f2 = 13.000;
	v2.f3 = -1727870017L;
	v2.f4 = 44530;
	v2.f5[0] = 35;
	v2.f5[1] = -84;
	v2.f5[2] = 5;
	v2.f5[3] = 54;
	v2.f6 = -3687;
	v2.f7 = 981567512L;
	r = f9((ushort)18690, (long)-115589811L, v2, (char)100);
	print("ret f9 uint %ud\n", r);
	}
	vf(1, (long)-559369386L);
	{
	S3 x, r;

	x.f0 = -7918;
	x.f1 = 2.125;
	x.f2 = 80;
	x.f3 = 923110401U;
	x.f4 = 5.750;
	x.f5 = 1937020438043888ULL;
	x.f6 = 63764;
	x.f7 = 803435205U;
	x.f8 = 9.250;
	x.f9 = -1817339431;
	x.f10 = 11.000;
	x.f11 = 9;
	x.f12 = 1190712122ULL;
	x.f13 = 1697664235L;
	x.f14[0] = 28;
	x.f14[1] = -77;
	x.f15 = 1071036926;
	r = cb(back, x);
	pS3("ret cb", r);
	}
	exits(nil);
}
#endif
