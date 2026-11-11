#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { ushort f0; char f1; };
typedef struct S1 S1;
struct S1 { float f0; vlong f1; uchar f2; ulong f3; double f4; short f5; float f6; char f7[2]; double f8; char f9[7]; };
typedef struct S2 S2;
struct S2 { double f0; uvlong f1; uvlong f2; uchar f3; uchar f4[6]; int f5; long f6; float f7; short f8; ushort f9; char f10; };
typedef struct S3 S3;
struct S3 { char f0; uchar f1[5]; };

float f0(S0 a0, ushort a1, uchar a2, int a3, ulong a4, long a5);
float f1(char a0);
ushort f2(long a0, short a1, int a2, double a3);
long f3(ushort a0, uint a1, float a2, uvlong a3);
int f4(uchar a0, double a1);
int f5(ulong a0, int a1, int a2, ulong a3, char a4, uchar a5, uchar a6, double a7);
S3 f6(uvlong a0, float a1, S2 a2, uvlong a3, S2 a4, uint a5);
uvlong f7(S2 a0, S1 a1);
char f8(long a0);
vlong f9(double a0, S1 a1, long a2, long a3, double a4, S2 a5, short a6, char a7);
void vf(int n, ...);
S3 cb(S3 (*fn)(S3, double, vlong), S3 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %ud %d\n", w, s.f0, s.f1);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %g %lld %ud %lud %g %d %g %d %d %g %d %d %d %d %d %d %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7[0], s.f7[1], s.f8, s.f9[0], s.f9[1], s.f9[2], s.f9[3], s.f9[4], s.f9[5], s.f9[6]);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %g %llud %llud %ud %ud %ud %ud %ud %ud %ud %d %ld %g %d %ud %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4[0], s.f4[1], s.f4[2], s.f4[3], s.f4[4], s.f4[5], s.f5, s.f6, s.f7, s.f8, s.f9, s.f10);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %d %ud %ud %ud %ud %ud\n", w, s.f0, s.f1[0], s.f1[1], s.f1[2], s.f1[3], s.f1[4]);
}

float
f0(S0 a0, ushort a1, uchar a2, int a3, ulong a4, long a5)
{
	print("in f0\n");
	pS0("a0", a0);
	print("a1 ushort %ud\n", a1);
	print("a2 uchar %ud\n", a2);
	print("a3 int %d\n", a3);
	print("a4 ulong %lud\n", a4);
	print("a5 long %ld\n", a5);
	return -25.000;
}

float
f1(char a0)
{
	print("in f1\n");
	print("a0 char %d\n", a0);
	return 37.250;
}

ushort
f2(long a0, short a1, int a2, double a3)
{
	print("in f2\n");
	print("a0 long %ld\n", a0);
	print("a1 short %d\n", a1);
	print("a2 int %d\n", a2);
	print("a3 double %g\n", a3);
	return 6852;
}

long
f3(ushort a0, uint a1, float a2, uvlong a3)
{
	print("in f3\n");
	print("a0 ushort %ud\n", a0);
	print("a1 uint %ud\n", a1);
	print("a2 float %g\n", a2);
	print("a3 uvlong %llud\n", a3);
	return 1927583773L;
}

int
f4(uchar a0, double a1)
{
	print("in f4\n");
	print("a0 uchar %ud\n", a0);
	print("a1 double %g\n", a1);
	return 1237783926;
}

int
f5(ulong a0, int a1, int a2, ulong a3, char a4, uchar a5, uchar a6, double a7)
{
	print("in f5\n");
	print("a0 ulong %lud\n", a0);
	print("a1 int %d\n", a1);
	print("a2 int %d\n", a2);
	print("a3 ulong %lud\n", a3);
	print("a4 char %d\n", a4);
	print("a5 uchar %ud\n", a5);
	print("a6 uchar %ud\n", a6);
	print("a7 double %g\n", a7);
	return 1681563501;
}

S3
f6(uvlong a0, float a1, S2 a2, uvlong a3, S2 a4, uint a5)
{
	S3 r;

	print("in f6\n");
	print("a0 uvlong %llud\n", a0);
	print("a1 float %g\n", a1);
	pS2("a2", a2);
	print("a3 uvlong %llud\n", a3);
	pS2("a4", a4);
	print("a5 uint %ud\n", a5);
	r.f0 = -102;
	r.f1[0] = 23;
	r.f1[1] = 200;
	r.f1[2] = 121;
	r.f1[3] = 42;
	r.f1[4] = 219;
	return r;
}

uvlong
f7(S2 a0, S1 a1)
{
	print("in f7\n");
	pS2("a0", a0);
	pS1("a1", a1);
	return 1133023698060904ULL;
}

char
f8(long a0)
{
	print("in f8\n");
	print("a0 long %ld\n", a0);
	return -72;
}

vlong
f9(double a0, S1 a1, long a2, long a3, double a4, S2 a5, short a6, char a7)
{
	print("in f9\n");
	print("a0 double %g\n", a0);
	pS1("a1", a1);
	print("a2 long %ld\n", a2);
	print("a3 long %ld\n", a3);
	print("a4 double %g\n", a4);
	pS2("a5", a5);
	print("a6 short %d\n", a6);
	print("a7 char %d\n", a7);
	return 1450454798LL;
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %llud\n", va_arg(ap, uvlong));
	print("v1 %ud\n", va_arg(ap, uint));
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
	print("%s S0 %ud %d\n", w, s.f0, s.f1);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %g %lld %ud %lud %g %d %g %d %d %g %d %d %d %d %d %d %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7[0], s.f7[1], s.f8, s.f9[0], s.f9[1], s.f9[2], s.f9[3], s.f9[4], s.f9[5], s.f9[6]);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %g %llud %llud %ud %ud %ud %ud %ud %ud %ud %d %ld %g %d %ud %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4[0], s.f4[1], s.f4[2], s.f4[3], s.f4[4], s.f4[5], s.f5, s.f6, s.f7, s.f8, s.f9, s.f10);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %d %ud %ud %ud %ud %ud\n", w, s.f0, s.f1[0], s.f1[1], s.f1[2], s.f1[3], s.f1[4]);
}

static S3
back(S3 x, double d, vlong v)
{
	pS3("back x", x);
	print("back %g %lld\n", d, v);
	x.f0 = x.f0 + 3;
	x.f1[0] = x.f1[0] + 3;
	x.f1[1] = x.f1[1] + 3;
	x.f1[2] = x.f1[2] + 3;
	x.f1[3] = x.f1[3] + 3;
	x.f1[4] = x.f1[4] + 3;
	return x;
}

void
main(void)
{
	{
	S0 v0;
	float r;
	v0.f0 = 23240;
	v0.f1 = -121;
	r = f0(v0, (ushort)56476, (uchar)77, (int)-353751038, (ulong)860703151UL, (long)1367655264L);
	print("ret f0 float %g\n", r);
	}
	{
	float r;
	r = f1((char)38);
	print("ret f1 float %g\n", r);
	}
	{
	ushort r;
	r = f2((long)-1241310188L, (short)23965, (int)107730766, (double)-37.125);
	print("ret f2 ushort %ud\n", r);
	}
	{
	long r;
	r = f3((ushort)24901, (uint)1058462454U, (float)3.125, (uvlong)2072366680ULL);
	print("ret f3 long %ld\n", r);
	}
	{
	int r;
	r = f4((uchar)158, (double)43.125);
	print("ret f4 int %d\n", r);
	}
	{
	int r;
	r = f5((ulong)305490069UL, (int)812442182, (int)-1319394295, (ulong)1826346408UL, (char)89, (uchar)10, (uchar)187, (double)-9.500);
	print("ret f5 int %d\n", r);
	}
	{
	S2 v2;
	S2 v4;
	S3 r;
	v2.f0 = 29.750;
	v2.f1 = 2967147901424ULL;
	v2.f2 = 509919252ULL;
	v2.f3 = 197;
	v2.f4[0] = 118;
	v2.f4[1] = 39;
	v2.f4[2] = 216;
	v2.f4[3] = 137;
	v2.f4[4] = 58;
	v2.f4[5] = 235;
	v2.f5 = 270568860;
	v2.f6 = -777520973L;
	v2.f7 = 41.250;
	v2.f8 = 31407;
	v2.f9 = 29792;
	v2.f10 = 17;
	v4.f0 = 49.250;
	v4.f1 = 1552079463224428ULL;
	v4.f2 = 2059026920ULL;
	v4.f3 = 153;
	v4.f4[0] = 74;
	v4.f4[1] = 251;
	v4.f4[2] = 172;
	v4.f4[3] = 93;
	v4.f4[4] = 14;
	v4.f4[5] = 191;
	v4.f5 = 1819676528;
	v4.f6 = 179144993L;
	v4.f7 = -36.750;
	v4.f8 = 31875;
	v4.f9 = 63028;
	v4.f10 = -101;
	r = f6((uvlong)446746714ULL, (float)-27.625, v2, (uvlong)1460650940ULL, v4, (uint)1967603053U);
	pS3("ret f6", r);
	}
	{
	S2 v0;
	S1 v1;
	uvlong r;
	v0.f0 = 13.625;
	v0.f1 = 263898980ULL;
	v0.f2 = 770853405553286ULL;
	v0.f3 = 198;
	v0.f4[0] = 119;
	v0.f4[1] = 40;
	v0.f4[2] = 217;
	v0.f4[3] = 138;
	v0.f4[4] = 59;
	v0.f4[5] = 236;
	v0.f5 = 531500701;
	v0.f6 = -1038452814L;
	v0.f7 = 25.125;
	v0.f8 = 31664;
	v0.f9 = 62817;
	v0.f10 = 18;
	v1.f0 = 33.125;
	v1.f1 = 1813006648LL;
	v1.f2 = 233;
	v1.f3 = 679427226UL;
	v1.f4 = 37.625;
	v1.f5 = 12284;
	v1.f6 = 39.375;
	v1.f7[0] = 94;
	v1.f7[1] = 15;
	v1.f8 = 42.000;
	v1.f9[0] = 113;
	v1.f9[1] = 34;
	v1.f9[2] = -83;
	v1.f9[3] = 4;
	v1.f9[4] = 53;
	v1.f9[5] = -102;
	v1.f9[6] = 23;
	r = f7(v0, v1);
	print("ret f7 uvlong %llud\n", r);
	}
	{
	char r;
	r = f8((long)-137553904L);
	print("ret f8 char %d\n", r);
	}
	{
	S1 v1;
	S2 v5;
	vlong r;
	v1.f0 = 31.250;
	v1.f1 = -4611104683204387474LL;
	v1.f2 = 152;
	v1.f3 = 1595237705UL;
	v1.f4 = 35.750;
	v1.f5 = 22699;
	v1.f6 = 37.500;
	v1.f7[0] = -13;
	v1.f7[1] = 62;
	v1.f8 = 40.125;
	v1.f9[0] = -32;
	v1.f9[1] = 81;
	v1.f9[2] = 2;
	v1.f9[3] = -51;
	v1.f9[4] = 100;
	v1.f9[5] = 21;
	v1.f9[6] = -70;
	v5.f0 = 51.750;
	v5.f1 = 2130447538323448ULL;
	v5.f2 = 489909612ULL;
	v5.f3 = 29;
	v5.f4[0] = 206;
	v5.f4[1] = 127;
	v5.f4[2] = 48;
	v5.f4[3] = 225;
	v5.f4[4] = 146;
	v5.f4[5] = 67;
	v5.f5 = 250559220;
	v5.f6 = -757511333L;
	v5.f7 = -34.250;
	v5.f8 = 10247;
	v5.f9 = 8632;
	v5.f10 = 105;
	r = f9((double)-26.250, v1, (long)1532065167L, (long)2039017280L, (double)-23.875, v5, (short)25250, (char)83);
	print("ret f9 vlong %lld\n", r);
	}
	vf(2, (uvlong)1349221480652306ULL, (uint)1856169546U);
	{
	S3 x, r;

	x.f0 = 93;
	x.f1[0] = 142;
	x.f1[1] = 63;
	x.f1[2] = 240;
	x.f1[3] = 161;
	x.f1[4] = 82;
	r = cb(back, x);
	pS3("ret cb", r);
	}
	exits(nil);
}
#endif
