#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { uchar f0[5]; short f1; uvlong f2; uint f3; double f4; uchar f5[9]; uvlong f6; char f7; short f8; uchar f9; };
typedef struct S1 S1;
struct S1 { vlong f0; long f1; short f2; vlong f3; ushort f4; ulong f5; char f6; char f7; char f8; };
typedef struct S2 S2;
struct S2 { double f0; uchar f1[4]; ushort f2; char f3; vlong f4; uchar f5; };
typedef struct S3 S3;
struct S3 { char f0[2]; int f1; uchar f2; };

int f0(S0 a0, ulong a1, uvlong a2, short a3);
long f1(uchar a0, S2 a1, S3 a2, ushort a3, float a4, S1 a5);
uvlong f2(short a0, S3 a1, S3 a2, char a3);
int f3(uvlong a0, float a1, long a2, ulong a3, vlong a4, ushort a5);
ushort f4(int a0, ulong a1);
uvlong f5(int a0, S2 a1, ulong a2, int a3);
char f6(uvlong a0, long a1, int a2);
S3 f7(uvlong a0, vlong a1, S1 a2, S3 a3, S1 a4, uint a5, S3 a6, ushort a7);
int f8(S0 a0, int a1, S3 a2, double a3);
S2 f9(S3 a0, vlong a1, uvlong a2);
void vf(int n, ...);
S1 cb(S1 (*fn)(S1, double, vlong), S1 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %ud %ud %ud %ud %ud %d %llud %ud %g %ud %ud %ud %ud %ud %ud %ud %ud %ud %llud %d %d %ud\n", w, s.f0[0], s.f0[1], s.f0[2], s.f0[3], s.f0[4], s.f1, s.f2, s.f3, s.f4, s.f5[0], s.f5[1], s.f5[2], s.f5[3], s.f5[4], s.f5[5], s.f5[6], s.f5[7], s.f5[8], s.f6, s.f7, s.f8, s.f9);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %lld %ld %d %lld %ud %lud %d %d %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %g %ud %ud %ud %ud %ud %d %lld %ud\n", w, s.f0, s.f1[0], s.f1[1], s.f1[2], s.f1[3], s.f2, s.f3, s.f4, s.f5);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %d %d %d %ud\n", w, s.f0[0], s.f0[1], s.f1, s.f2);
}

int
f0(S0 a0, ulong a1, uvlong a2, short a3)
{
	print("in f0\n");
	pS0("a0", a0);
	print("a1 ulong %lud\n", a1);
	print("a2 uvlong %llud\n", a2);
	print("a3 short %d\n", a3);
	return 2044156584;
}

long
f1(uchar a0, S2 a1, S3 a2, ushort a3, float a4, S1 a5)
{
	print("in f1\n");
	print("a0 uchar %ud\n", a0);
	pS2("a1", a1);
	pS3("a2", a2);
	print("a3 ushort %ud\n", a3);
	print("a4 float %g\n", a4);
	pS1("a5", a5);
	return 249028644L;
}

uvlong
f2(short a0, S3 a1, S3 a2, char a3)
{
	print("in f2\n");
	print("a0 short %d\n", a0);
	pS3("a1", a1);
	pS3("a2", a2);
	print("a3 char %d\n", a3);
	return 1552116040ULL;
}

int
f3(uvlong a0, float a1, long a2, ulong a3, vlong a4, ushort a5)
{
	print("in f3\n");
	print("a0 uvlong %llud\n", a0);
	print("a1 float %g\n", a1);
	print("a2 long %ld\n", a2);
	print("a3 ulong %lud\n", a3);
	print("a4 vlong %lld\n", a4);
	print("a5 ushort %ud\n", a5);
	return -799143655;
}

ushort
f4(int a0, ulong a1)
{
	print("in f4\n");
	print("a0 int %d\n", a0);
	print("a1 ulong %lud\n", a1);
	return 26530;
}

uvlong
f5(int a0, S2 a1, ulong a2, int a3)
{
	print("in f5\n");
	print("a0 int %d\n", a0);
	pS2("a1", a1);
	print("a2 ulong %lud\n", a2);
	print("a3 int %d\n", a3);
	return 1567032310082834ULL;
}

char
f6(uvlong a0, long a1, int a2)
{
	print("in f6\n");
	print("a0 uvlong %llud\n", a0);
	print("a1 long %ld\n", a1);
	print("a2 int %d\n", a2);
	return 21;
}

S3
f7(uvlong a0, vlong a1, S1 a2, S3 a3, S1 a4, uint a5, S3 a6, ushort a7)
{
	S3 r;

	print("in f7\n");
	print("a0 uvlong %llud\n", a0);
	print("a1 vlong %lld\n", a1);
	pS1("a2", a2);
	pS3("a3", a3);
	pS1("a4", a4);
	print("a5 uint %ud\n", a5);
	pS3("a6", a6);
	print("a7 ushort %ud\n", a7);
	r = a3;
	r.f0[0] = r.f0[0] + 3;
	r.f0[1] = r.f0[1] + 3;
	r.f1 = r.f1 + 3;
	r.f2 = r.f2 + 3;
	return r;
}

int
f8(S0 a0, int a1, S3 a2, double a3)
{
	print("in f8\n");
	pS0("a0", a0);
	print("a1 int %d\n", a1);
	pS3("a2", a2);
	print("a3 double %g\n", a3);
	return -1934294886;
}

S2
f9(S3 a0, vlong a1, uvlong a2)
{
	S2 r;

	print("in f9\n");
	pS3("a0", a0);
	print("a1 vlong %lld\n", a1);
	print("a2 uvlong %llud\n", a2);
	r.f0 = -33.875;
	r.f1[0] = 146;
	r.f1[1] = 67;
	r.f1[2] = 244;
	r.f1[3] = 165;
	r.f2 = 25686;
	r.f3 = -7;
	r.f4 = 1279416248LL;
	r.f5 = 105;
	return r;
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %lld\n", va_arg(ap, vlong));
	print("v1 %g\n", va_arg(ap, double));
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
	print("%s S0 %ud %ud %ud %ud %ud %d %llud %ud %g %ud %ud %ud %ud %ud %ud %ud %ud %ud %llud %d %d %ud\n", w, s.f0[0], s.f0[1], s.f0[2], s.f0[3], s.f0[4], s.f1, s.f2, s.f3, s.f4, s.f5[0], s.f5[1], s.f5[2], s.f5[3], s.f5[4], s.f5[5], s.f5[6], s.f5[7], s.f5[8], s.f6, s.f7, s.f8, s.f9);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %lld %ld %d %lld %ud %lud %d %d %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %g %ud %ud %ud %ud %ud %d %lld %ud\n", w, s.f0, s.f1[0], s.f1[1], s.f1[2], s.f1[3], s.f2, s.f3, s.f4, s.f5);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %d %d %d %ud\n", w, s.f0[0], s.f0[1], s.f1, s.f2);
}

static S1
back(S1 x, double d, vlong v)
{
	pS1("back x", x);
	print("back %g %lld\n", d, v);
	x.f0 = x.f0 + 3;
	x.f1 = x.f1 + 3;
	x.f2 = x.f2 + 3;
	x.f3 = x.f3 + 3;
	x.f4 = x.f4 + 3;
	x.f5 = x.f5 + 3;
	x.f6 = x.f6 + 3;
	x.f7 = x.f7 + 3;
	x.f8 = x.f8 + 3;
	return x;
}

void
main(void)
{
	{
	S0 v0;
	int r;
	v0.f0[0] = 208;
	v0.f0[1] = 129;
	v0.f0[2] = 50;
	v0.f0[3] = 227;
	v0.f0[4] = 148;
	v0.f1 = -1093;
	v0.f2 = 1562312182ULL;
	v0.f3 = 2069264295U;
	v0.f4 = 18.000;
	v0.f5[0] = 9;
	v0.f5[1] = 186;
	v0.f5[2] = 107;
	v0.f5[3] = 28;
	v0.f5[4] = 205;
	v0.f5[5] = 126;
	v0.f5[6] = 47;
	v0.f5[7] = 224;
	v0.f5[8] = 145;
	v0.f6 = 1203286594ULL;
	v0.f7 = 115;
	v0.f8 = -9636;
	v0.f9 = 85;
	r = f0(v0, (ulong)69707172UL, (uvlong)576661014977862ULL, (short)6406);
	print("ret f0 int %d\n", r);
	}
	{
	S2 v1;
	S3 v2;
	S1 v5;
	long r;
	v1.f0 = -27.500;
	v1.f1[0] = 253;
	v1.f1[1] = 174;
	v1.f1[2] = 95;
	v1.f1[3] = 16;
	v1.f2 = 2497;
	v1.f3 = 114;
	v1.f4 = 274137177409072LL;
	v1.f5 = 212;
	v2.f0[0] = -32;
	v2.f0[1] = 81;
	v2.f1 = 1435967106;
	v2.f2 = 51;
	v5.f0 = 1971170548LL;
	v5.f1 = -330639013L;
	v5.f2 = 8278;
	v5.f3 = 1344547272629724LL;
	v5.f4 = 37816;
	v5.f5 = 210963817UL;
	v5.f6 = 26;
	v5.f7 = -75;
	v5.f8 = 124;
	r = f1((uchar)200, v1, v2, (ushort)43129, (float)35.750, v5);
	print("ret f1 long %ld\n", r);
	}
	{
	S3 v1;
	S3 v2;
	uvlong r;
	v1.f0[0] = 112;
	v1.f0[1] = -33;
	v1.f1 = 1189946834;
	v1.f2 = 131;
	v2.f0[0] = 68;
	v2.f0[1] = 117;
	v2.f1 = -591570854;
	v2.f2 = 87;
	r = f2((short)-13848, v1, v2, (char)73);
	print("ret f2 uvlong %llud\n", r);
	}
	{
	int r;
	r = f3((uvlong)1570558582661620ULL, (float)56.000, (long)436974449L, (ulong)943926562UL, (vlong)1450883027636032LL, (ushort)8324);
	print("ret f3 int %d\n", r);
	}
	{
	ushort r;
	r = f4((int)1894658250, (ulong)254126715UL);
	print("ret f4 ushort %ud\n", r);
	}
	{
	S2 v1;
	uvlong r;
	v1.f0 = 40.875;
	v1.f1[0] = 114;
	v1.f1[1] = 35;
	v1.f1[2] = 212;
	v1.f1[3] = 133;
	v1.f2 = 6966;
	v1.f3 = 103;
	v1.f4 = 1592135320LL;
	v1.f5 = 73;
	r = f5((int)-1740061845, v1, (ulong)99530310UL, (int)606482423);
	print("ret f5 uvlong %llud\n", r);
	}
	{
	char r;
	r = f6((uvlong)543311514929662ULL, (long)1050261998L, (int)-1557214111);
	print("ret f6 char %d\n", r);
	}
	{
	S1 v2;
	S3 v3;
	S1 v4;
	S3 v6;
	S3 r;
	v2.f0 = 1494046055124726LL;
	v2.f1 = -2000993686L;
	v2.f2 = 14151;
	v2.f3 = 867414264LL;
	v2.f4 = 10921;
	v2.f5 = 1881318490UL;
	v2.f6 = 11;
	v2.f7 = -60;
	v2.f8 = 109;
	v3.f0[0] = 57;
	v3.f0[1] = 106;
	v3.f1 = -1909569819;
	v3.f2 = 204;
	v4.f0 = -4611388727922519072LL;
	v4.f1 = 804241726L;
	v4.f2 = 15087;
	v4.f3 = -1818145952LL;
	v4.f4 = 11857;
	v4.f5 = 684566530UL;
	v4.f6 = -51;
	v4.f7 = 100;
	v4.f8 = 21;
	v6.f0[0] = 97;
	v6.f0[1] = -18;
	v6.f1 = 712817859;
	v6.f2 = 116;
	r = f7((uvlong)1248025045063910ULL, (vlong)1754973414LL, v2, v3, v4, (uint)114441879U, v6, (ushort)47176);
	pS3("ret f7", r);
	}
	{
	S0 v0;
	S3 v2;
	int r;
	v0.f0[0] = 142;
	v0.f0[1] = 63;
	v0.f0[2] = 240;
	v0.f0[3] = 161;
	v0.f0[4] = 82;
	v0.f1 = 10499;
	v0.f2 = 1452450484ULL;
	v0.f3 = 1959402597U;
	v0.f4 = -22.250;
	v0.f5[0] = 199;
	v0.f5[1] = 120;
	v0.f5[2] = 41;
	v0.f5[3] = 218;
	v0.f5[4] = 139;
	v0.f5[5] = 60;
	v0.f5[6] = 237;
	v0.f5[7] = 158;
	v0.f5[8] = 79;
	v0.f6 = 1093424896ULL;
	v0.f7 = 49;
	v0.f8 = 19042;
	v0.f9 = 19;
	v2.f0[0] = 98;
	v2.f0[1] = -19;
	v2.f1 = 973749700;
	v2.f2 = 117;
	r = f8(v0, (int)1508953142, v2, (double)11.125);
	print("ret f8 int %d\n", r);
	}
	{
	S3 v0;
	S2 r;
	v0.f0[0] = 45;
	v0.f0[1] = 94;
	v0.f1 = -819153295;
	v0.f2 = 64;
	r = f9(v0, (vlong)-4610331657627317700LL, (uvlong)1861308850ULL);
	pS2("ret f9", r);
	}
	vf(2, (vlong)-1798136312LL, (double)12.875);
	{
	S1 x, r;

	x.f0 = -641020988LL;
	x.f1 = 1147973101L;
	x.f2 = 10142;
	x.f3 = -4611671624705206874LL;
	x.f4 = 6912;
	x.f5 = 1028297905UL;
	x.f6 = -98;
	x.f7 = 19;
	x.f8 = 68;
	r = cb(back, x);
	pS1("ret cb", r);
	}
	exits(nil);
}
#endif
