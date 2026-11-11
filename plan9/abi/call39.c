#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { short f0; };
typedef struct S1 S1;
struct S1 { vlong f0; short f1; double f2; long f3; uint f4; uint f5; uchar f6; uchar f7; };
typedef struct S2 S2;
struct S2 { short f0; ushort f1; char f2; };
typedef struct S3 S3;
struct S3 { long f0; char f1[4]; uchar f2; };

void f0(uchar a0, vlong a1, ushort a2);
S2 f1(S3 a0, S3 a1);
S2 f2(short a0, uint a1);
long f3(long a0, S2 a1);
S2 f4(float a0, S0 a1, uvlong a2);
long f5(uchar a0, ulong a1);
uvlong f6(float a0, S0 a1);
vlong f7(uint a0, uchar a1, float a2, char a3, ushort a4, S1 a5);
double f8(S1 a0, S2 a1, char a2, float a3);
S3 f9(S3 a0, S3 a1, long a2, S1 a3, float a4, ulong a5, float a6, long a7);
void vf(int n, ...);
S1 cb(S1 (*fn)(S1, double, vlong), S1 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %d\n", w, s.f0);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %lld %d %g %ld %ud %ud %ud %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d %ud %d\n", w, s.f0, s.f1, s.f2);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %ld %d %d %d %d %ud\n", w, s.f0, s.f1[0], s.f1[1], s.f1[2], s.f1[3], s.f2);
}

void
f0(uchar a0, vlong a1, ushort a2)
{
	print("in f0\n");
	print("a0 uchar %ud\n", a0);
	print("a1 vlong %lld\n", a1);
	print("a2 ushort %ud\n", a2);
}

S2
f1(S3 a0, S3 a1)
{
	S2 r;

	print("in f1\n");
	pS3("a0", a0);
	pS3("a1", a1);
	r.f0 = -7732;
	r.f1 = 6117;
	r.f2 = 22;
	return r;
}

S2
f2(short a0, uint a1)
{
	S2 r;

	print("in f2\n");
	print("a0 short %d\n", a0);
	print("a1 uint %ud\n", a1);
	r.f0 = 14449;
	r.f1 = 45602;
	r.f2 = 83;
	return r;
}

long
f3(long a0, S2 a1)
{
	print("in f3\n");
	print("a0 long %ld\n", a0);
	pS2("a1", a1);
	return -254167948L;
}

S2
f4(float a0, S0 a1, uvlong a2)
{
	S2 r;

	print("in f4\n");
	print("a0 float %g\n", a0);
	pS0("a1", a1);
	print("a2 uvlong %llud\n", a2);
	r.f0 = -21634;
	r.f1 = 52787;
	r.f2 = 100;
	return r;
}

long
f5(uchar a0, ulong a1)
{
	print("in f5\n");
	print("a0 uchar %ud\n", a0);
	print("a1 ulong %lud\n", a1);
	return -1585506673L;
}

uvlong
f6(float a0, S0 a1)
{
	print("in f6\n");
	print("a0 float %g\n", a0);
	pS0("a1", a1);
	return 2029286248ULL;
}

vlong
f7(uint a0, uchar a1, float a2, char a3, ushort a4, S1 a5)
{
	print("in f7\n");
	print("a0 uint %ud\n", a0);
	print("a1 uchar %ud\n", a1);
	print("a2 float %g\n", a2);
	print("a3 char %d\n", a3);
	print("a4 ushort %ud\n", a4);
	pS1("a5", a5);
	return 1367737730LL;
}

double
f8(S1 a0, S2 a1, char a2, float a3)
{
	print("in f8\n");
	pS1("a0", a0);
	pS2("a1", a1);
	print("a2 char %d\n", a2);
	print("a3 float %g\n", a3);
	return 28.000;
}

S3
f9(S3 a0, S3 a1, long a2, S1 a3, float a4, ulong a5, float a6, long a7)
{
	S3 r;

	print("in f9\n");
	pS3("a0", a0);
	pS3("a1", a1);
	print("a2 long %ld\n", a2);
	pS1("a3", a3);
	print("a4 float %g\n", a4);
	print("a5 ulong %lud\n", a5);
	print("a6 float %g\n", a6);
	print("a7 long %ld\n", a7);
	r = a0;
	r.f0 = r.f0 + 3;
	r.f1[0] = r.f1[0] + 3;
	r.f1[1] = r.f1[1] + 3;
	r.f1[2] = r.f1[2] + 3;
	r.f1[3] = r.f1[3] + 3;
	r.f2 = r.f2 + 3;
	return r;
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %lud\n", va_arg(ap, ulong));
	print("v1 %llud\n", va_arg(ap, uvlong));
	va_end(ap);
}

S1
cb(S1 (*fn)(S1, double, vlong), S1 x)
{
	S1 r;

	r = fn(x, 2.5, -7LL);
	pS1("cb got", r);
	return fn(r, -1.25, 1LL<<40);
}

#else
static void
pS0(char *w, S0 s)
{
	print("%s S0 %d\n", w, s.f0);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %lld %d %g %ld %ud %ud %ud %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d %ud %d\n", w, s.f0, s.f1, s.f2);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %ld %d %d %d %d %ud\n", w, s.f0, s.f1[0], s.f1[1], s.f1[2], s.f1[3], s.f2);
}

static S1
back(S1 x, double d, vlong v)
{
	pS1("back x", x);
	print("back %g %lld\n", d, v);
	x.f0 = x.f0 + 3;
	x.f1 = x.f1 + 3;
	x.f2 = x.f2 * 2;
	x.f3 = x.f3 + 3;
	x.f4 = x.f4 + 3;
	x.f5 = x.f5 + 3;
	x.f6 = x.f6 + 3;
	x.f7 = x.f7 + 3;
	return x;
}

void
main(void)
{
	{
	f0((uchar)216, (vlong)1904901339686882LL, (ushort)57402);
	}
	{
	S3 v0;
	S3 v1;
	S2 r;
	v0.f0 = 201191552L;
	v0.f1[0] = 49;
	v0.f1[1] = -98;
	v0.f1[2] = 19;
	v0.f1[3] = 68;
	v0.f2 = 245;
	v1.f0 = -1750299220L;
	v1.f1[0] = 5;
	v1.f1[1] = 54;
	v1.f1[2] = -103;
	v1.f1[3] = 24;
	v1.f2 = 201;
	r = f1(v0, v1);
	pS2("ret f1", r);
	}
	{
	S2 r;
	r = f2((short)-2749, (uint)1088750702U);
	pS2("ret f2", r);
	}
	{
	S2 v1;
	long r;
	v1.f0 = -5300;
	v1.f1 = 36453;
	v1.f2 = 22;
	r = f3((long)427202184L, v1);
	print("ret f3 long %ld\n", r);
	}
	{
	S0 v1;
	S2 r;
	v1.f0 = 9934;
	r = f4((float)6.750, v1, (uvlong)272606596817344ULL);
	pS2("ret f4", r);
	}
	{
	long r;
	r = f5((uchar)153, (ulong)716385354UL);
	print("ret f5 long %ld\n", r);
	}
	{
	S0 v1;
	uvlong r;
	v1.f0 = -15504;
	r = f6((float)7.500, v1);
	print("ret f6 uvlong %llud\n", r);
	}
	{
	S1 v5;
	vlong r;
	v5.f0 = 2139147946LL;
	v5.f1 = 18523;
	v5.f2 = 47.500;
	v5.f3 = 1512520637L;
	v5.f4 = 2019472750U;
	v5.f5 = 378941215U;
	v5.f6 = 208;
	v5.f7 = 129;
	r = f7((uint)1540771966U, (uchar)47, (float)-30.000, (char)-17, (ushort)14146, v5);
	print("ret f7 vlong %lld\n", r);
	}
	{
	S1 v0;
	S2 v1;
	double r;
	v0.f0 = -1357924232LL;
	v0.f1 = 16697;
	v0.f2 = 12.750;
	v0.f3 = -731296923L;
	v0.f4 = 1238249036U;
	v0.f5 = 1745201149U;
	v0.f6 = 174;
	v0.f7 = 95;
	v1.f0 = 18780;
	v1.f1 = 17165;
	v1.f2 = 62;
	r = f8(v0, v1, (char)48, (float)51.875);
	print("ret f8 double %g\n", r);
	}
	{
	S3 v0;
	S3 v1;
	S1 v3;
	S3 r;
	v0.f0 = 604951847L;
	v0.f1[0] = 88;
	v0.f1[1] = -9;
	v0.f1[2] = 58;
	v0.f1[3] = 107;
	v0.f2 = 156;
	v1.f0 = -6575867L;
	v1.f1[0] = 44;
	v1.f1[1] = 93;
	v1.f1[2] = -14;
	v1.f1[3] = 63;
	v1.f2 = 112;
	v3.f0 = 1555688202050612LL;
	v3.f1 = -21120;
	v3.f2 = 34.875;
	v3.f3 = 929056226L;
	v3.f4 = 1436008339U;
	v3.f5 = 1942960452U;
	v3.f6 = 245;
	v3.f7 = 166;
	r = f9(v0, v1, (long)957307555L, v3, (float)53.500, (ulong)1971211781UL, (float)55.250, (long)837632359L);
	pS3("ret f9", r);
	}
	vf(2, (ulong)774459821UL, (uvlong)1281411934ULL);
	{
	S1 x, r;

	x.f0 = 1764833439484442LL;
	x.f1 = 7586;
	x.f2 = 26.625;
	x.f3 = 1138200836L;
	x.f4 = 1645152949U;
	x.f5 = 4621414U;
	x.f6 = 23;
	x.f7 = 200;
	r = cb(back, x);
	pS1("ret cb", r);
	}
	exits(nil);
}
#endif
