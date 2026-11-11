#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { uint f0; long f1; char f2; };
typedef struct S1 S1;
struct S1 { uchar f0; ulong f1; char f2[3]; char f3; };
typedef struct S2 S2;
struct S2 { uchar f0; uchar f1; };
typedef struct S3 S3;
struct S3 { long f0; ushort f1; };

uint f0(uvlong a0, S0 a1, S1 a2, long a3, float a4, uchar a5, S3 a6, int a7);
S1 f1(S2 a0, short a1, long a2);
float f2(char a0, vlong a1, ushort a2, double a3, S0 a4, float a5, ulong a6, S2 a7);
void f3(S2 a0);
char f4(S2 a0, short a1, S3 a2, uchar a3, vlong a4, ulong a5, uint a6, ushort a7);
S0 f5(ushort a0, S1 a1, float a2, uvlong a3, long a4, float a5);
short f6(double a0, float a1, short a2);
ushort f7(long a0);
uchar f8(S1 a0);
uvlong f9(uint a0, S1 a1, float a2);
void vf(int n, ...);
S0 cb(S0 (*fn)(S0, double, vlong), S0 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %ud %ld %d\n", w, s.f0, s.f1, s.f2);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %ud %lud %d %d %d %d\n", w, s.f0, s.f1, s.f2[0], s.f2[1], s.f2[2], s.f3);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %ud %ud\n", w, s.f0, s.f1);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %ld %ud\n", w, s.f0, s.f1);
}

uint
f0(uvlong a0, S0 a1, S1 a2, long a3, float a4, uchar a5, S3 a6, int a7)
{
	print("in f0\n");
	print("a0 uvlong %llud\n", a0);
	pS0("a1", a1);
	pS1("a2", a2);
	print("a3 long %ld\n", a3);
	print("a4 float %g\n", a4);
	print("a5 uchar %ud\n", a5);
	pS3("a6", a6);
	print("a7 int %d\n", a7);
	return 1898184512U;
}

S1
f1(S2 a0, short a1, long a2)
{
	S1 r;

	print("in f1\n");
	pS2("a0", a0);
	print("a1 short %d\n", a1);
	print("a2 long %ld\n", a2);
	r.f0 = 162;
	r.f1 = 1271557203UL;
	r.f2[0] = 4;
	r.f2[1] = 53;
	r.f2[2] = -102;
	r.f3 = 23;
	return r;
}

float
f2(char a0, vlong a1, ushort a2, double a3, S0 a4, float a5, ulong a6, S2 a7)
{
	print("in f2\n");
	print("a0 char %d\n", a0);
	print("a1 vlong %lld\n", a1);
	print("a2 ushort %ud\n", a2);
	print("a3 double %g\n", a3);
	pS0("a4", a4);
	print("a5 float %g\n", a5);
	print("a6 ulong %lud\n", a6);
	pS2("a7", a7);
	return -35.875;
}

void
f3(S2 a0)
{
	print("in f3\n");
	pS2("a0", a0);
}

char
f4(S2 a0, short a1, S3 a2, uchar a3, vlong a4, ulong a5, uint a6, ushort a7)
{
	print("in f4\n");
	pS2("a0", a0);
	print("a1 short %d\n", a1);
	pS3("a2", a2);
	print("a3 uchar %ud\n", a3);
	print("a4 vlong %lld\n", a4);
	print("a5 ulong %lud\n", a5);
	print("a6 uint %ud\n", a6);
	print("a7 ushort %ud\n", a7);
	return 93;
}

S0
f5(ushort a0, S1 a1, float a2, uvlong a3, long a4, float a5)
{
	S0 r;

	print("in f5\n");
	print("a0 ushort %ud\n", a0);
	pS1("a1", a1);
	print("a2 float %g\n", a2);
	print("a3 uvlong %llud\n", a3);
	print("a4 long %ld\n", a4);
	print("a5 float %g\n", a5);
	r.f0 = 1991180188U;
	r.f1 = -350648653L;
	r.f2 = 126;
	return r;
}

short
f6(double a0, float a1, short a2)
{
	print("in f6\n");
	print("a0 double %g\n", a0);
	print("a1 float %g\n", a1);
	print("a2 short %d\n", a2);
	return 414;
}

ushort
f7(long a0)
{
	print("in f7\n");
	print("a0 long %ld\n", a0);
	return 1350;
}

uchar
f8(S1 a0)
{
	print("in f8\n");
	pS1("a0", a0);
	return 140;
}

uvlong
f9(uint a0, S1 a1, float a2)
{
	print("in f9\n");
	print("a0 uint %ud\n", a0);
	pS1("a1", a1);
	print("a2 float %g\n", a2);
	return 84618994856230ULL;
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %d\n", va_arg(ap, int));
	print("v1 %d\n", va_arg(ap, int));
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
	print("%s S0 %ud %ld %d\n", w, s.f0, s.f1, s.f2);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %ud %lud %d %d %d %d\n", w, s.f0, s.f1, s.f2[0], s.f2[1], s.f2[2], s.f3);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %ud %ud\n", w, s.f0, s.f1);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %ld %ud\n", w, s.f0, s.f1);
}

static S0
back(S0 x, double d, vlong v)
{
	pS0("back x", x);
	print("back %g %lld\n", d, v);
	x.f0 = x.f0 + 3;
	x.f1 = x.f1 + 3;
	x.f2 = x.f2 + 3;
	return x;
}

void
main(void)
{
	{
	S0 v1;
	S1 v2;
	S3 v6;
	uint r;
	v1.f0 = 522111080U;
	v1.f1 = 1029063193L;
	v1.f2 = 74;
	v2.f0 = 60;
	v2.f1 = 430687213UL;
	v2.f2[0] = 30;
	v2.f2[1] = 79;
	v2.f2[2] = 0;
	v2.f3 = 49;
	v6.f0 = 1472842768L;
	v6.f1 = 17857;
	r = f0((uvlong)874466788ULL, v1, v2, (long)1381418901L, (float)42.250, (uchar)247, v6, (int)754791592);
	print("ret f0 uint %ud\n", r);
	}
	{
	S2 v0;
	S1 r;
	v0.f0 = 238;
	v0.f1 = 159;
	r = f1(v0, (short)18114, (long)-600195187L);
	pS1("ret f1", r);
	}
	{
	S0 v4;
	S2 v7;
	float r;
	v4.f0 = 537022649U;
	v4.f1 = -1043974762L;
	v4.f2 = 27;
	v7.f0 = 141;
	v7.f1 = 62;
	r = f2((char)-97, (vlong)1994706450LL, (ushort)18371, (double)-10.500, v4, (float)-9.375, (ulong)1875031254UL, v7);
	print("ret f2 float %g\n", r);
	}
	{
	S2 v0;
	v0.f0 = 28;
	v0.f1 = 205;
	f3(v0);
	}
	{
	S2 v0;
	S3 v2;
	char r;
	v0.f0 = 133;
	v0.f1 = 54;
	v2.f0 = -44982105L;
	v2.f1 = 55562;
	r = f4(v0, (short)24877, v2, (uchar)222, (vlong)460511732531060LL, (ulong)967462464UL, (uint)1474414577U, (ushort)16802);
	print("ret f4 char %d\n", r);
	}
	{
	S1 v1;
	S0 r;
	v1.f0 = 232;
	v1.f1 = 277662617UL;
	v1.f2[0] = 74;
	v1.f2[1] = -123;
	v1.f2[2] = 44;
	v1.f3 = 93;
	r = f5((ushort)54204, v1, (float)-3.375, (uvlong)186238750ULL, (long)693190863L, (float)0.000);
	pS0("ret f5", r);
	}
	{
	short r;
	r = f6((double)38.250, (float)39.125, (short)15912);
	print("ret f6 short %d\n", r);
	}
	{
	ushort r;
	r = f7((long)-2087702126L);
	print("ret f7 ushort %ud\n", r);
	}
	{
	S1 v0;
	uchar r;
	v0.f0 = 180;
	v0.f1 = 383998053UL;
	v0.f2[0] = 22;
	v0.f2[1] = 71;
	v0.f2[2] = -120;
	v0.f3 = 41;
	r = f8(v0);
	print("ret f8 uchar %ud\n", r);
	}
	{
	S1 v1;
	uvlong r;
	v1.f0 = 29;
	v1.f1 = 1362981070UL;
	v1.f2[0] = 127;
	v1.f2[1] = 48;
	v1.f2[2] = -97;
	v1.f3 = 18;
	r = f9((uint)257652977U, v1, (float)0.750);
	print("ret f9 uvlong %llud\n", r);
	}
	vf(2, (int)701432552, (int)1208384665);
	{
	S0 x, r;

	x.f0 = 1691800876U;
	x.f1 = 51269341L;
	x.f2 = -14;
	r = cb(back, x);
	pS0("ret cb", r);
	}
	exits(nil);
}
#endif
