#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { uint f0; short f1; ushort f2; uchar f3; char f4[2]; uchar f5; };
typedef struct S1 S1;
struct S1 { long f0; float f1; uint f2; char f3; short f4; ushort f5; };
typedef struct S2 S2;
struct S2 { int f0; char f1; int f2; ulong f3; ushort f4; char f5[8]; char f6[3]; uint f7; char f8; uchar f9; uchar f10; int f11; short f12; char f13; };
typedef struct S3 S3;
struct S3 { char f0; short f1; long f2; short f3; char f4; long f5; uchar f6; };

long f0(uint a0, S0 a1, uvlong a2);
vlong f1(double a0, S0 a1, long a2, short a3, ushort a4, S3 a5, vlong a6, ulong a7);
vlong f2(S2 a0, ulong a1, uvlong a2, double a3, short a4, ulong a5);
uint f3(ulong a0, S3 a1);
uint f4(uvlong a0);
short f5(float a0, short a1, vlong a2);
S2 f6(long a0, uvlong a1, ulong a2, long a3, uchar a4, S1 a5);
long f7(float a0);
char f8(S3 a0, ushort a1);
uchar f9(ushort a0, ulong a1, S1 a2);
void vf(int n, ...);
S1 cb(S1 (*fn)(S1, double, vlong), S1 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %ud %d %ud %ud %d %d %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4[0], s.f4[1], s.f5);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %ld %g %ud %d %d %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d %d %d %lud %ud %d %d %d %d %d %d %d %d %d %d %d %ud %d %ud %ud %d %d %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5[0], s.f5[1], s.f5[2], s.f5[3], s.f5[4], s.f5[5], s.f5[6], s.f5[7], s.f6[0], s.f6[1], s.f6[2], s.f7, s.f8, s.f9, s.f10, s.f11, s.f12, s.f13);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %d %d %ld %d %d %ld %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6);
}

long
f0(uint a0, S0 a1, uvlong a2)
{
	print("in f0\n");
	print("a0 uint %ud\n", a0);
	pS0("a1", a1);
	print("a2 uvlong %llud\n", a2);
	return 396366360L;
}

vlong
f1(double a0, S0 a1, long a2, short a3, ushort a4, S3 a5, vlong a6, ulong a7)
{
	print("in f1\n");
	print("a0 double %g\n", a0);
	pS0("a1", a1);
	print("a2 long %ld\n", a2);
	print("a3 short %d\n", a3);
	print("a4 ushort %ud\n", a4);
	pS3("a5", a5);
	print("a6 vlong %lld\n", a6);
	print("a7 ulong %lud\n", a7);
	return 241770680309872LL;
}

vlong
f2(S2 a0, ulong a1, uvlong a2, double a3, short a4, ulong a5)
{
	print("in f2\n");
	pS2("a0", a0);
	print("a1 ulong %lud\n", a1);
	print("a2 uvlong %llud\n", a2);
	print("a3 double %g\n", a3);
	print("a4 short %d\n", a4);
	print("a5 ulong %lud\n", a5);
	return -1516606022LL;
}

uint
f3(ulong a0, S3 a1)
{
	print("in f3\n");
	print("a0 ulong %lud\n", a0);
	pS3("a1", a1);
	return 735382308U;
}

uint
f4(uvlong a0)
{
	print("in f4\n");
	print("a0 uvlong %llud\n", a0);
	return 73833790U;
}

short
f5(float a0, short a1, vlong a2)
{
	print("in f5\n");
	print("a0 float %g\n", a0);
	print("a1 short %d\n", a1);
	print("a2 vlong %lld\n", a2);
	return 11652;
}

S2
f6(long a0, uvlong a1, ulong a2, long a3, uchar a4, S1 a5)
{
	S2 r;

	print("in f6\n");
	print("a0 long %ld\n", a0);
	print("a1 uvlong %llud\n", a1);
	print("a2 ulong %lud\n", a2);
	print("a3 long %ld\n", a3);
	print("a4 uchar %ud\n", a4);
	pS1("a5", a5);
	r.f0 = 1805789192;
	r.f1 = -57;
	r.f2 = 672209770;
	r.f3 = 1179161883UL;
	r.f4 = 3788;
	r.f5[0] = 125;
	r.f5[1] = 46;
	r.f5[2] = -95;
	r.f5[3] = 16;
	r.f5[4] = 65;
	r.f5[5] = -114;
	r.f5[6] = 35;
	r.f5[7] = 84;
	r.f6[0] = -5;
	r.f6[1] = 54;
	r.f6[2] = 103;
	r.f7 = 1327088408U;
	r.f8 = 73;
	r.f9 = 122;
	r.f10 = 43;
	r.f11 = 1207413212;
	r.f12 = 9101;
	r.f13 = -62;
	return r;
}

long
f7(float a0)
{
	print("in f7\n");
	print("a0 float %g\n", a0);
	return 180169226L;
}

char
f8(S3 a0, ushort a1)
{
	print("in f8\n");
	pS3("a0", a0);
	print("a1 ushort %ud\n", a1);
	return 80;
}

uchar
f9(ushort a0, ulong a1, S1 a2)
{
	print("in f9\n");
	print("a0 ushort %ud\n", a0);
	print("a1 ulong %lud\n", a1);
	pS1("a2", a2);
	return 106;
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
	print("%s S0 %ud %d %ud %ud %d %d %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4[0], s.f4[1], s.f5);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %ld %g %ud %d %d %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d %d %d %lud %ud %d %d %d %d %d %d %d %d %d %d %d %ud %d %ud %ud %d %d %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5[0], s.f5[1], s.f5[2], s.f5[3], s.f5[4], s.f5[5], s.f5[6], s.f5[7], s.f6[0], s.f6[1], s.f6[2], s.f7, s.f8, s.f9, s.f10, s.f11, s.f12, s.f13);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %d %d %ld %d %d %ld %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6);
}

static S1
back(S1 x, double d, vlong v)
{
	pS1("back x", x);
	print("back %g %lld\n", d, v);
	x.f0 = x.f0 + 3;
	x.f1 = x.f1 * 2;
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
	S0 v1;
	long r;
	v1.f0 = 1167776576U;
	v1.f1 = -21745;
	v1.f2 = 52898;
	v1.f3 = 83;
	v1.f4[0] = -4;
	v1.f4[1] = 53;
	v1.f5 = 102;
	r = f0((uint)569400596U, v1, (uvlong)1076355938058134ULL);
	print("ret f0 long %ld\n", r);
	}
	{
	S0 v1;
	S3 v5;
	vlong r;
	v1.f0 = 1013180171U;
	v1.f1 = 24764;
	v1.f2 = 55917;
	v1.f3 = 30;
	v1.f4[0] = 79;
	v1.f4[1] = 0;
	v1.f5 = 49;
	v5.f0 = -95;
	v5.f1 = 25232;
	v5.f2 = 1428708417L;
	v5.f3 = -22002;
	v5.f4 = 35;
	v5.f5 = 802081108L;
	v5.f6 = 5;
	r = f1((double)8.625, v1, (long)-323380324L, (short)24085, (ushort)22470, v5, (vlong)-4609841776231677922LL, (ulong)203705128UL);
	print("ret f1 vlong %lld\n", r);
	}
	{
	S2 v0;
	vlong r;
	v0.f0 = -140532590;
	v0.f1 = 31;
	v0.f2 = 1154436816;
	v0.f3 = 1661388929UL;
	v0.f4 = 16946;
	v0.f5[0] = 99;
	v0.f5[1] = -20;
	v0.f5[2] = 69;
	v0.f5[3] = 118;
	v0.f5[4] = -39;
	v0.f5[5] = 88;
	v0.f5[6] = 9;
	v0.f5[7] = -58;
	v0.f6[0] = 107;
	v0.f6[1] = 28;
	v0.f6[2] = -77;
	v0.f7 = 1809315454U;
	v0.f8 = 47;
	v0.f9 = 224;
	v0.f10 = 145;
	v0.f11 = 1689640258;
	v0.f12 = -22259;
	v0.f13 = 36;
	r = f2(v0, (ulong)1689640258UL, (uvlong)49108870326176ULL, (double)-24.500, (short)19029, (ulong)1569965062UL);
	print("ret f2 vlong %lld\n", r);
	}
	{
	S3 v1;
	uint r;
	v1.f0 = 76;
	v1.f1 = -19965;
	v1.f2 = 373213102L;
	v1.f3 = 16735;
	v1.f4 = -16;
	v1.f5 = 1894069441L;
	v1.f6 = 114;
	r = f3((ulong)908416544UL, v1);
	print("ret f3 uint %ud\n", r);
	}
	{
	uint r;
	r = f4((uvlong)845244006ULL);
	print("ret f4 uint %ud\n", r);
	}
	{
	short r;
	r = f5((float)15.500, (short)-28765, (vlong)1795975694LL);
	print("ret f5 short %d\n", r);
	}
	{
	S1 v5;
	S2 r;
	v5.f0 = -1732803156L;
	v5.f1 = 56.375;
	v5.f2 = 599223734U;
	v5.f3 = -103;
	v5.f4 = 24856;
	v5.f5 = 56009;
	r = f6((long)1134427176L, (uvlong)1641384213137874ULL, (ulong)847754UL, (long)507799867L, (uchar)236, v5);
	pS2("ret f6", r);
	}
	{
	long r;
	r = f7((float)20.750);
	print("ret f7 long %ld\n", r);
	}
	{
	S3 v0;
	char r;
	v0.f0 = 120;
	v0.f1 = 32041;
	v0.f2 = -1902311130L;
	v0.f3 = 28811;
	v0.f4 = 60;
	v0.f5 = -1275683821L;
	v0.f6 = 158;
	r = f8(v0, (ushort)34124);
	print("ret f8 char %d\n", r);
	}
	{
	S1 v2;
	uchar r;
	v2.f0 = 226858386L;
	v2.f1 = 20.625;
	v2.f2 = 1240762612U;
	v2.f3 = 37;
	v2.f4 = -31830;
	v2.f5 = 62983;
	r = f9((ushort)5990, (ulong)135434519UL, v2);
	print("ret f9 uchar %ud\n", r);
	}
	vf(1, (vlong)72262197785950LL);
	{
	S1 x, r;

	x.f0 = 1062630305L;
	x.f1 = 9.750;
	x.f2 = 2076534531U;
	x.f3 = 52;
	x.f4 = 23141;
	x.f5 = 54294;
	r = cb(back, x);
	pS1("ret cb", r);
	}
	exits(nil);
}
#endif
