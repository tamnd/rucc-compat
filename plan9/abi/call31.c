#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { float f0; char f1; };
typedef struct S1 S1;
struct S1 { short f0; char f1; char f2; };
typedef struct S2 S2;
struct S2 { ushort f0; uint f1; uchar f2; ushort f3; ulong f4; uvlong f5; long f6; short f7; char f8[2]; short f9; uchar f10; };
typedef struct S3 S3;
struct S3 { ushort f0; };

long f0(S1 a0, int a1);
uchar f1(short a0);
void f2(ulong a0, ushort a1, char a2);
void f3(vlong a0);
int f4(S0 a0, S0 a1, S3 a2, int a3);
S1 f5(S3 a0, uchar a1, uint a2, short a3, S1 a4, char a5);
void f6(float a0, uchar a1, double a2, uchar a3);
short f7(uvlong a0);
short f8(S3 a0, char a1, long a2, short a3, long a4, float a5);
S1 f9(S2 a0, int a1);
void vf(int n, ...);
S0 cb(S0 (*fn)(S0, double, vlong), S0 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %g %d\n", w, s.f0, s.f1);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %d %d %d\n", w, s.f0, s.f1, s.f2);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %ud %ud %ud %ud %lud %llud %ld %d %d %d %d %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8[0], s.f8[1], s.f9, s.f10);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %ud\n", w, s.f0);
}

long
f0(S1 a0, int a1)
{
	print("in f0\n");
	pS1("a0", a0);
	print("a1 int %d\n", a1);
	return 1606240368L;
}

uchar
f1(short a0)
{
	print("in f1\n");
	print("a0 short %d\n", a0);
	return 138;
}

void
f2(ulong a0, ushort a1, char a2)
{
	print("in f2\n");
	print("a0 ulong %lud\n", a0);
	print("a1 ushort %ud\n", a1);
	print("a2 char %d\n", a2);
}

void
f3(vlong a0)
{
	print("in f3\n");
	print("a0 vlong %lld\n", a0);
}

int
f4(S0 a0, S0 a1, S3 a2, int a3)
{
	print("in f4\n");
	pS0("a0", a0);
	pS0("a1", a1);
	pS3("a2", a2);
	print("a3 int %d\n", a3);
	return 1769078462;
}

S1
f5(S3 a0, uchar a1, uint a2, short a3, S1 a4, char a5)
{
	S1 r;

	print("in f5\n");
	pS3("a0", a0);
	print("a1 uchar %ud\n", a1);
	print("a2 uint %ud\n", a2);
	print("a3 short %d\n", a3);
	pS1("a4", a4);
	print("a5 char %d\n", a5);
	r = a4;
	r.f0 = r.f0 + 3;
	r.f1 = r.f1 + 3;
	r.f2 = r.f2 + 3;
	return r;
}

void
f6(float a0, uchar a1, double a2, uchar a3)
{
	print("in f6\n");
	print("a0 float %g\n", a0);
	print("a1 uchar %ud\n", a1);
	print("a2 double %g\n", a2);
	print("a3 uchar %ud\n", a3);
}

short
f7(uvlong a0)
{
	print("in f7\n");
	print("a0 uvlong %llud\n", a0);
	return 4826;
}

short
f8(S3 a0, char a1, long a2, short a3, long a4, float a5)
{
	print("in f8\n");
	pS3("a0", a0);
	print("a1 char %d\n", a1);
	print("a2 long %ld\n", a2);
	print("a3 short %d\n", a3);
	print("a4 long %ld\n", a4);
	print("a5 float %g\n", a5);
	return 8992;
}

S1
f9(S2 a0, int a1)
{
	S1 r;

	print("in f9\n");
	pS2("a0", a0);
	print("a1 int %d\n", a1);
	r.f0 = 4826;
	r.f1 = -11;
	r.f2 = 60;
	return r;
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %llud\n", va_arg(ap, uvlong));
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
	print("%s S0 %g %d\n", w, s.f0, s.f1);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %d %d %d\n", w, s.f0, s.f1, s.f2);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %ud %ud %ud %ud %lud %llud %ld %d %d %d %d %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8[0], s.f8[1], s.f9, s.f10);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %ud\n", w, s.f0);
}

static S0
back(S0 x, double d, vlong v)
{
	pS0("back x", x);
	print("back %g %lld\n", d, v);
	x.f0 = x.f0 * 2;
	x.f1 = x.f1 + 3;
	return x;
}

void
main(void)
{
	{
	S1 v0;
	long r;
	v0.f0 = 4504;
	v0.f1 = 73;
	v0.f2 = -122;
	r = f0(v0, (int)-1779274604);
	print("ret f0 long %ld\n", r);
	}
	{
	uchar r;
	r = f1((short)9138);
	print("ret f1 uchar %ud\n", r);
	}
	{
	f2((ulong)1652929528UL, (ushort)11689, (char)-90);
	}
	{
	f3((vlong)456177568LL);
	}
	{
	S0 v0;
	S0 v1;
	S3 v2;
	int r;
	v0.f0 = -3.250;
	v0.f1 = 23;
	v1.f0 = 17.750;
	v1.f1 = 107;
	v2.f0 = 52110;
	r = f4(v0, v1, v2, (int)745360738);
	print("ret f4 int %d\n", r);
	}
	{
	S3 v0;
	S1 v4;
	S1 r;
	v0.f0 = 23976;
	v4.f0 = 24444;
	v4.f1 = -45;
	v4.f2 = 94;
	r = f5(v0, (uchar)80, (uint)2139872001U, (short)-21682, v4, (char)99);
	pS1("ret f5", r);
	}
	{
	f6((float)-18.875, (uchar)90, (double)-16.625, (uchar)188);
	}
	{
	short r;
	r = f7((uvlong)253320194ULL);
	print("ret f7 short %d\n", r);
	}
	{
	S3 v0;
	short r;
	v0.f0 = 27720;
	r = f8(v0, (char)-28, (long)98723789L, (short)24958, (long)-1112628015L, (float)-12.000);
	print("ret f8 short %d\n", r);
	}
	{
	S2 v0;
	S1 r;
	v0.f0 = 58662;
	v0.f1 = 2063359703U;
	v0.f2 = 136;
	v0.f3 = 21049;
	v0.f4 = 1436732394UL;
	v0.f5 = 1943690338053528ULL;
	v0.f6 = -303152972L;
	v0.f7 = 14589;
	v0.f8[0] = 46;
	v0.f8[1] = -95;
	v0.f9 = 9744;
	v0.f10 = 193;
	r = f9(v0, (int)958031610);
	pS1("ret f9", r);
	}
	vf(1, (uvlong)894859072ULL);
	{
	S0 x, r;

	x.f0 = 14.500;
	x.f1 = 53;
	r = cb(back, x);
	pS0("ret cb", r);
	}
	exits(nil);
}
#endif
