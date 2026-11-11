#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { uvlong f0; char f1[6]; uchar f2; ulong f3; double f4; long f5; double f6; vlong f7; short f8; ulong f9; uvlong f10; char f11; uchar f12; char f13; };
typedef struct S1 S1;
struct S1 { float f0; uvlong f1; int f2; ushort f3; long f4; double f5; ushort f6; };
typedef struct S2 S2;
struct S2 { int f0; char f1; };
typedef struct S3 S3;
struct S3 { ulong f0; vlong f1; char f2[3]; char f3; };

uchar f0(double a0, double a1, ushort a2);
S3 f1(double a0, char a1, uchar a2, ulong a3, uchar a4, ulong a5, vlong a6, uvlong a7);
ushort f2(double a0, uint a1, ulong a2, char a3, S2 a4, int a5, double a6, float a7);
uchar f3(short a0, int a1, S2 a2, S0 a3, S3 a4, float a5, vlong a6, int a7);
short f4(ushort a0);
S3 f5(S1 a0, uchar a1, S3 a2);
int f6(short a0);
char f7(uint a0, S2 a1, S0 a2, short a3, S3 a4, int a5, S1 a6, float a7);
uchar f8(float a0, long a1, uchar a2);
S3 f9(int a0, S3 a1);
void vf(int n, ...);
S2 cb(S2 (*fn)(S2, double, vlong), S2 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %llud %d %d %d %d %d %d %ud %lud %g %ld %g %lld %d %lud %llud %d %ud %d\n", w, s.f0, s.f1[0], s.f1[1], s.f1[2], s.f1[3], s.f1[4], s.f1[5], s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11, s.f12, s.f13);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %g %llud %d %ud %ld %g %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d %d\n", w, s.f0, s.f1);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %lud %lld %d %d %d %d\n", w, s.f0, s.f1, s.f2[0], s.f2[1], s.f2[2], s.f3);
}

uchar
f0(double a0, double a1, ushort a2)
{
	print("in f0\n");
	print("a0 double %g\n", a0);
	print("a1 double %g\n", a1);
	print("a2 ushort %ud\n", a2);
	return 48;
}

S3
f1(double a0, char a1, uchar a2, ulong a3, uchar a4, ulong a5, vlong a6, uvlong a7)
{
	S3 r;

	print("in f1\n");
	print("a0 double %g\n", a0);
	print("a1 char %d\n", a1);
	print("a2 uchar %ud\n", a2);
	print("a3 ulong %lud\n", a3);
	print("a4 uchar %ud\n", a4);
	print("a5 ulong %lud\n", a5);
	print("a6 vlong %lld\n", a6);
	print("a7 uvlong %llud\n", a7);
	r.f0 = 86108084UL;
	r.f1 = -4611092956451207320LL;
	r.f2[0] = 22;
	r.f2[1] = 71;
	r.f2[2] = -120;
	r.f3 = 41;
	return r;
}

ushort
f2(double a0, uint a1, ulong a2, char a3, S2 a4, int a5, double a6, float a7)
{
	print("in f2\n");
	print("a0 double %g\n", a0);
	print("a1 uint %ud\n", a1);
	print("a2 ulong %lud\n", a2);
	print("a3 char %d\n", a3);
	pS2("a4", a4);
	print("a5 int %d\n", a5);
	print("a6 double %g\n", a6);
	print("a7 float %g\n", a7);
	return 54517;
}

uchar
f3(short a0, int a1, S2 a2, S0 a3, S3 a4, float a5, vlong a6, int a7)
{
	print("in f3\n");
	print("a0 short %d\n", a0);
	print("a1 int %d\n", a1);
	pS2("a2", a2);
	pS0("a3", a3);
	pS3("a4", a4);
	print("a5 float %g\n", a5);
	print("a6 vlong %lld\n", a6);
	print("a7 int %d\n", a7);
	return 53;
}

short
f4(ushort a0)
{
	print("in f4\n");
	print("a0 ushort %ud\n", a0);
	return 15803;
}

S3
f5(S1 a0, uchar a1, S3 a2)
{
	S3 r;

	print("in f5\n");
	pS1("a0", a0);
	print("a1 uchar %ud\n", a1);
	pS3("a2", a2);
	r = a2;
	r.f0 = r.f0 + 3;
	r.f1 = r.f1 + 3;
	r.f2[0] = r.f2[0] + 3;
	r.f2[1] = r.f2[1] + 3;
	r.f2[2] = r.f2[2] + 3;
	r.f3 = r.f3 + 3;
	return r;
}

int
f6(short a0)
{
	print("in f6\n");
	print("a0 short %d\n", a0);
	return -1806295535;
}

char
f7(uint a0, S2 a1, S0 a2, short a3, S3 a4, int a5, S1 a6, float a7)
{
	print("in f7\n");
	print("a0 uint %ud\n", a0);
	pS2("a1", a1);
	pS0("a2", a2);
	print("a3 short %d\n", a3);
	pS3("a4", a4);
	print("a5 int %d\n", a5);
	pS1("a6", a6);
	print("a7 float %g\n", a7);
	return 53;
}

uchar
f8(float a0, long a1, uchar a2)
{
	print("in f8\n");
	print("a0 float %g\n", a0);
	print("a1 long %ld\n", a1);
	print("a2 uchar %ud\n", a2);
	return 222;
}

S3
f9(int a0, S3 a1)
{
	S3 r;

	print("in f9\n");
	print("a0 int %d\n", a0);
	pS3("a1", a1);
	r = a1;
	r.f0 = r.f0 + 3;
	r.f1 = r.f1 + 3;
	r.f2[0] = r.f2[0] + 3;
	r.f2[1] = r.f2[1] + 3;
	r.f2[2] = r.f2[2] + 3;
	r.f3 = r.f3 + 3;
	return r;
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %lld\n", va_arg(ap, vlong));
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
	print("%s S0 %llud %d %d %d %d %d %d %ud %lud %g %ld %g %lld %d %lud %llud %d %ud %d\n", w, s.f0, s.f1[0], s.f1[1], s.f1[2], s.f1[3], s.f1[4], s.f1[5], s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11, s.f12, s.f13);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %g %llud %d %ud %ld %g %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d %d\n", w, s.f0, s.f1);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %lud %lld %d %d %d %d\n", w, s.f0, s.f1, s.f2[0], s.f2[1], s.f2[2], s.f3);
}

static S2
back(S2 x, double d, vlong v)
{
	pS2("back x", x);
	print("back %g %lld\n", d, v);
	x.f0 = x.f0 + 3;
	x.f1 = x.f1 + 3;
	return x;
}

void
main(void)
{
	{
	uchar r;
	r = f0((double)-29.000, (double)-28.875, (ushort)10682);
	print("ret f0 uchar %ud\n", r);
	}
	{
	S3 r;
	r = f1((double)11.000, (char)49, (uchar)98, (ulong)1533978387UL, (uchar)196, (ulong)400398965UL, (vlong)-907351078LL, (uvlong)1414307433909580ULL);
	pS3("ret f1", r);
	}
	{
	S2 v4;
	ushort r;
	v4.f0 = -1351130653;
	v4.f1 = 78;
	r = f2((double)-21.875, (uint)1259706786U, (ulong)1766658899UL, (char)4, v4, (int)-633079477, (double)-16.250, (float)-15.125);
	print("ret f2 ushort %ud\n", r);
	}
	{
	S2 v2;
	S0 v3;
	S3 v4;
	uchar r;
	v2.f0 = 1583811165;
	v2.f1 = 14;
	v3.f0 = 985438141305562ULL;
	v3.f1[0] = 98;
	v3.f1[1] = 19;
	v3.f1[2] = -68;
	v3.f1[3] = 117;
	v3.f1[4] = 38;
	v3.f1[5] = -87;
	v3.f2 = 8;
	v3.f3 = 746084793UL;
	v3.f4 = 52.750;
	v3.f5 = 1759989019L;
	v3.f6 = 54.500;
	v3.f7 = -4611059606951159120LL;
	v3.f8 = 14894;
	v3.f9 = 1640313823UL;
	v3.f10 = 2147265936ULL;
	v3.f11 = 65;
	v3.f12 = 242;
	v3.f13 = -35;
	v4.f0 = 387059205UL;
	v4.f1 = -894011318LL;
	v4.f2[0] = 103;
	v4.f2[1] = 24;
	v4.f2[2] = -73;
	v4.f3 = 122;
	r = f3((short)4057, (int)295635338, v2, v3, v4, (float)-12.625, (vlong)1309539564LL, (int)1816491677);
	print("ret f3 uchar %ud\n", r);
	}
	{
	short r;
	r = f4((ushort)34531);
	print("ret f4 short %d\n", r);
	}
	{
	S1 v0;
	S3 v2;
	S3 r;
	v0.f0 = -31.875;
	v0.f1 = 49615066ULL;
	v0.f2 = 556567179;
	v0.f3 = 1084;
	v0.f4 = 1570471405L;
	v0.f5 = -26.250;
	v0.f6 = 29007;
	v2.f0 = 1091770621UL;
	v2.f1 = -1598722734LL;
	v2.f2[0] = 95;
	v2.f2[1] = 16;
	v2.f2[2] = -65;
	v2.f3 = 114;
	r = f5(v0, (uchar)209, v2);
	pS3("ret f5", r);
	}
	{
	int r;
	r = f6((short)-11031);
	print("ret f6 int %d\n", r);
	}
	{
	S2 v1;
	S0 v2;
	S3 v4;
	S1 v6;
	char r;
	v1.f0 = 367049565;
	v1.f1 = -14;
	v2.f0 = 1916162981471706ULL;
	v2.f1[0] = 98;
	v2.f1[1] = -19;
	v2.f1[2] = 68;
	v2.f1[3] = 117;
	v2.f1[4] = -38;
	v2.f1[5] = 87;
	v2.f2 = 8;
	v2.f3 = 1676806841UL;
	v2.f4 = 17.750;
	v2.f5 = 543227419L;
	v2.f6 = 19.500;
	v2.f7 = 1557136316394942LL;
	v2.f8 = 27438;
	v2.f9 = 423552223UL;
	v2.f10 = 930504336ULL;
	v2.f11 = 65;
	v2.f12 = 242;
	v2.f13 = 35;
	v4.f0 = 1317781253UL;
	v4.f1 = 1824733366LL;
	v4.f2[0] = 103;
	v4.f2[1] = -24;
	v4.f2[2] = 73;
	v4.f3 = 122;
	v6.f0 = 48.875;
	v6.f1 = 1226357386ULL;
	v6.f2 = 1733309499;
	v6.f3 = 44524;
	v6.f4 = -599730077L;
	v6.f5 = 53.250;
	v6.f6 = 6911;
	r = f7((uint)121029293U, v1, v2, (short)15454, v4, (int)-1134933519, v6, (float)-26.000);
	print("ret f7 char %d\n", r);
	}
	{
	uchar r;
	r = f8((float)12.250, (long)2085665207L, (uchar)104);
	print("ret f8 uchar %ud\n", r);
	}
	{
	S3 v1;
	S3 r;
	v1.f0 = 381961134UL;
	v1.f1 = 888915913739748LL;
	v1.f2[0] = -16;
	v1.f2[1] = 65;
	v1.f2[2] = 114;
	v1.f3 = -35;
	r = f9((int)-1931068802, v1);
	pS3("ret f9", r);
	}
	vf(1, (vlong)1867896264LL);
	{
	S2 x, r;

	x.f0 = 710780940;
	x.f1 = -61;
	r = cb(back, x);
	pS2("ret cb", r);
	}
	exits(nil);
}
#endif
