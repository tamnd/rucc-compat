#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { uint f0; ushort f1; uchar f2; };
typedef struct S1 S1;
struct S1 { double f0; uint f1; double f2; uchar f3[3]; uint f4; float f5; uint f6; short f7; short f8; char f9; };
typedef struct S2 S2;
struct S2 { ulong f0; short f1; ulong f2; ulong f3; short f4; };
typedef struct S3 S3;
struct S3 { uvlong f0; ushort f1; uchar f2; char f3; };

S3 f0(double a0, S0 a1, uchar a2);
short f1(S0 a0, uvlong a1, S2 a2, ushort a3);
S0 f2(S3 a0, S2 a1, short a2, float a3, uvlong a4, S1 a5);
double f3(uint a0, long a1, char a2, S2 a3, S1 a4, S2 a5);
float f4(double a0, uvlong a1, ulong a2, double a3, ulong a4, uint a5, char a6, double a7);
S1 f5(char a0, uvlong a1);
char f6(uchar a0);
ushort f7(float a0);
void f8(char a0, int a1);
uchar f9(uvlong a0);
void vf(int n, ...);
S0 cb(S0 (*fn)(S0, double, vlong), S0 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %ud %ud %ud\n", w, s.f0, s.f1, s.f2);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %g %ud %g %ud %ud %ud %ud %g %ud %d %d %d\n", w, s.f0, s.f1, s.f2, s.f3[0], s.f3[1], s.f3[2], s.f4, s.f5, s.f6, s.f7, s.f8, s.f9);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %lud %d %lud %lud %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %llud %ud %ud %d\n", w, s.f0, s.f1, s.f2, s.f3);
}

S3
f0(double a0, S0 a1, uchar a2)
{
	S3 r;

	print("in f0\n");
	print("a0 double %g\n", a0);
	pS0("a1", a1);
	print("a2 uchar %ud\n", a2);
	r.f0 = 1532706756ULL;
	r.f1 = 47477;
	r.f2 = 38;
	r.f3 = -87;
	return r;
}

short
f1(S0 a0, uvlong a1, S2 a2, ushort a3)
{
	print("in f1\n");
	pS0("a0", a0);
	print("a1 uvlong %llud\n", a1);
	pS2("a2", a2);
	print("a3 ushort %ud\n", a3);
	return -21683;
}

S0
f2(S3 a0, S2 a1, short a2, float a3, uvlong a4, S1 a5)
{
	S0 r;

	print("in f2\n");
	pS3("a0", a0);
	pS2("a1", a1);
	print("a2 short %d\n", a2);
	print("a3 float %g\n", a3);
	print("a4 uvlong %llud\n", a4);
	pS1("a5", a5);
	r.f0 = 625137966U;
	r.f1 = 21215;
	r.f2 = 144;
	return r;
}

double
f3(uint a0, long a1, char a2, S2 a3, S1 a4, S2 a5)
{
	print("in f3\n");
	print("a0 uint %ud\n", a0);
	print("a1 long %ld\n", a1);
	print("a2 char %d\n", a2);
	pS2("a3", a3);
	pS1("a4", a4);
	pS2("a5", a5);
	return 31.250;
}

float
f4(double a0, uvlong a1, ulong a2, double a3, ulong a4, uint a5, char a6, double a7)
{
	print("in f4\n");
	print("a0 double %g\n", a0);
	print("a1 uvlong %llud\n", a1);
	print("a2 ulong %lud\n", a2);
	print("a3 double %g\n", a3);
	print("a4 ulong %lud\n", a4);
	print("a5 uint %ud\n", a5);
	print("a6 char %d\n", a6);
	print("a7 double %g\n", a7);
	return 34.750;
}

S1
f5(char a0, uvlong a1)
{
	S1 r;

	print("in f5\n");
	print("a0 char %d\n", a0);
	print("a1 uvlong %llud\n", a1);
	r.f0 = -21.625;
	r.f1 = 781306180U;
	r.f2 = -19.375;
	r.f3[0] = 166;
	r.f3[1] = 87;
	r.f3[2] = 8;
	r.f4 = 1168583097U;
	r.f5 = -14.750;
	r.f6 = 35003675U;
	r.f7 = 5836;
	r.f8 = -4221;
	r.f9 = 46;
	return r;
}

char
f6(uchar a0)
{
	print("in f6\n");
	print("a0 uchar %ud\n", a0);
	return -46;
}

ushort
f7(float a0)
{
	print("in f7\n");
	print("a0 float %g\n", a0);
	return 29428;
}

void
f8(char a0, int a1)
{
	print("in f8\n");
	print("a0 char %d\n", a0);
	print("a1 int %d\n", a1);
}

uchar
f9(uvlong a0)
{
	print("in f9\n");
	print("a0 uvlong %llud\n", a0);
	return 49;
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %llud\n", va_arg(ap, uvlong));
	print("v1 %llud\n", va_arg(ap, uvlong));
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
	print("%s S0 %ud %ud %ud\n", w, s.f0, s.f1, s.f2);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %g %ud %g %ud %ud %ud %ud %g %ud %d %d %d\n", w, s.f0, s.f1, s.f2, s.f3[0], s.f3[1], s.f3[2], s.f4, s.f5, s.f6, s.f7, s.f8, s.f9);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %lud %d %lud %lud %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %llud %ud %ud %d\n", w, s.f0, s.f1, s.f2, s.f3);
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
	S3 r;
	v1.f0 = 1459720720U;
	v1.f1 = 3009;
	v1.f2 = 114;
	r = f0((double)-11.500, v1, (uchar)149);
	pS3("ret f0", r);
	}
	{
	S0 v0;
	S2 v2;
	short r;
	v0.f0 = 1305124315U;
	v0.f1 = 6028;
	v0.f2 = 61;
	v2.f0 = 706748335UL;
	v2.f1 = -6496;
	v2.f2 = 1720652561UL;
	v2.f3 = 80121026UL;
	v2.f4 = -1651;
	r = f1(v0, (uvlong)108372680117072ULL, v2, (ushort)6964);
	print("ret f1 short %d\n", r);
	}
	{
	S3 v0;
	S2 v1;
	S1 v5;
	S0 r;
	v0.f0 = 552151930ULL;
	v0.f1 = 42283;
	v0.f2 = 220;
	v0.f3 = 13;
	v1.f0 = 2101259598UL;
	v1.f1 = 9983;
	v1.f2 = 967680176UL;
	v1.f3 = 1474632289UL;
	v1.f4 = 5138;
	v5.f0 = 50.750;
	v5.f1 = 2009835731U;
	v5.f2 = 52.500;
	v5.f3[0] = 53;
	v5.f3[1] = 230;
	v5.f3[2] = 151;
	v5.f4 = 249629000U;
	v5.f5 = -40.875;
	v5.f6 = 1263533226U;
	v5.f7 = 30299;
	v5.f8 = -28684;
	v5.f9 = 61;
	r = f2(v0, v1, (short)12534, (float)-26.125, (uvlong)1918411864ULL, v5);
	pS0("ret f2", r);
	}
	{
	S2 v3;
	S1 v4;
	S2 v5;
	double r;
	v3.f0 = 1855239326UL;
	v3.f1 = -11855;
	v3.f2 = 721659904UL;
	v3.f3 = 1228612017UL;
	v3.f4 = -7010;
	v4.f0 = 33.750;
	v4.f1 = 1763815459U;
	v4.f2 = 35.500;
	v4.f3[0] = 133;
	v4.f3[1] = 54;
	v4.f3[2] = 231;
	v4.f4 = 3608728U;
	v4.f5 = 40.875;
	v4.f6 = 1017512954U;
	v4.f7 = 32171;
	v4.f8 = 30556;
	v4.f9 = -13;
	v5.f0 = 658487366UL;
	v5.f1 = 12791;
	v5.f2 = 1672391592UL;
	v5.f3 = 31860057UL;
	v5.f4 = 7946;
	r = f3((uint)60111386U, (long)-567063499L, (char)124, v3, v4, v5);
	print("ret f3 double %g\n", r);
	}
	{
	float r;
	r = f4((double)16.750, (uvlong)1517799740385568ULL, (ulong)2024747300UL, (double)19.375, (ulong)891167878UL, (uint)1398119991U, (char)-104, (double)23.875);
	print("ret f4 float %g\n", r);
	}
	{
	S1 r;
	r = f5((char)-95, (uvlong)708320144ULL);
	pS1("ret f5", r);
	}
	{
	char r;
	r = f6((uchar)214);
	print("ret f6 char %d\n", r);
	}
	{
	ushort r;
	r = f7((float)41.500);
	print("ret f7 ushort %ud\n", r);
	}
	{
	f8((char)98, (int)1025754643);
	}
	{
	uchar r;
	r = f9((uvlong)962584992746322ULL);
	print("ret f9 uchar %ud\n", r);
	}
	vf(2, (uvlong)899412265228708ULL, (uvlong)1406361680ULL);
	{
	S0 x, r;

	x.f0 = 1889777891U;
	x.f1 = 12948;
	x.f2 = 69;
	r = cb(back, x);
	pS0("ret cb", r);
	}
	exits(nil);
}
#endif
