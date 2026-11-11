#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { uint f0; ushort f1; double f2; char f3; long f4; long f5; uchar f6; };
typedef struct S1 S1;
struct S1 { ulong f0; float f1; uchar f2[9]; double f3; int f4; uchar f5; char f6; };
typedef struct S2 S2;
struct S2 { uvlong f0; float f1; int f2; char f3; };
typedef struct S3 S3;
struct S3 { uchar f0[8]; uchar f1[4]; ushort f2; short f3; uchar f4; };

S3 f0(S3 a0, ushort a1);
uchar f1(S2 a0, long a1, uchar a2, vlong a3);
S1 f2(S3 a0, ushort a1, ushort a2, ulong a3, int a4, long a5);
void f3(double a0, uint a1, char a2);
char f4(ulong a0, uvlong a1, S0 a2, char a3, float a4, ulong a5, uchar a6, short a7);
char f5(S1 a0, long a1, char a2);
S2 f6(S1 a0, long a1);
int f7(S1 a0, S2 a1, ushort a2, short a3, S3 a4, S0 a5);
S3 f8(vlong a0, ulong a1);
void f9(uint a0);
void vf(int n, ...);
S2 cb(S2 (*fn)(S2, double, vlong), S2 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %ud %ud %g %d %ld %ld %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %lud %g %ud %ud %ud %ud %ud %ud %ud %ud %ud %g %d %ud %d\n", w, s.f0, s.f1, s.f2[0], s.f2[1], s.f2[2], s.f2[3], s.f2[4], s.f2[5], s.f2[6], s.f2[7], s.f2[8], s.f3, s.f4, s.f5, s.f6);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %llud %g %d %d\n", w, s.f0, s.f1, s.f2, s.f3);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %ud %ud %ud %ud %ud %ud %ud %ud %ud %ud %ud %ud %ud %d %ud\n", w, s.f0[0], s.f0[1], s.f0[2], s.f0[3], s.f0[4], s.f0[5], s.f0[6], s.f0[7], s.f1[0], s.f1[1], s.f1[2], s.f1[3], s.f2, s.f3, s.f4);
}

S3
f0(S3 a0, ushort a1)
{
	S3 r;

	print("in f0\n");
	pS3("a0", a0);
	print("a1 ushort %ud\n", a1);
	r = a0;
	r.f0[0] = r.f0[0] + 3;
	r.f0[1] = r.f0[1] + 3;
	r.f0[2] = r.f0[2] + 3;
	r.f0[3] = r.f0[3] + 3;
	r.f0[4] = r.f0[4] + 3;
	r.f0[5] = r.f0[5] + 3;
	r.f0[6] = r.f0[6] + 3;
	r.f0[7] = r.f0[7] + 3;
	r.f1[0] = r.f1[0] + 3;
	r.f1[1] = r.f1[1] + 3;
	r.f1[2] = r.f1[2] + 3;
	r.f1[3] = r.f1[3] + 3;
	r.f2 = r.f2 + 3;
	r.f3 = r.f3 + 3;
	r.f4 = r.f4 + 3;
	return r;
}

uchar
f1(S2 a0, long a1, uchar a2, vlong a3)
{
	print("in f1\n");
	pS2("a0", a0);
	print("a1 long %ld\n", a1);
	print("a2 uchar %ud\n", a2);
	print("a3 vlong %lld\n", a3);
	return 162;
}

S1
f2(S3 a0, ushort a1, ushort a2, ulong a3, int a4, long a5)
{
	S1 r;

	print("in f2\n");
	pS3("a0", a0);
	print("a1 ushort %ud\n", a1);
	print("a2 ushort %ud\n", a2);
	print("a3 ulong %lud\n", a3);
	print("a4 int %d\n", a4);
	print("a5 long %ld\n", a5);
	r.f0 = 1807402234UL;
	r.f1 = 29.625;
	r.f2[0] = 92;
	r.f2[1] = 13;
	r.f2[2] = 190;
	r.f2[3] = 111;
	r.f2[4] = 32;
	r.f2[5] = 209;
	r.f2[6] = 130;
	r.f2[7] = 51;
	r.f2[8] = 228;
	r.f3 = 39.375;
	r.f4 = 1448376646;
	r.f5 = 247;
	r.f6 = 40;
	return r;
}

void
f3(double a0, uint a1, char a2)
{
	print("in f3\n");
	print("a0 double %g\n", a0);
	print("a1 uint %ud\n", a1);
	print("a2 char %d\n", a2);
}

char
f4(ulong a0, uvlong a1, S0 a2, char a3, float a4, ulong a5, uchar a6, short a7)
{
	print("in f4\n");
	print("a0 ulong %lud\n", a0);
	print("a1 uvlong %llud\n", a1);
	pS0("a2", a2);
	print("a3 char %d\n", a3);
	print("a4 float %g\n", a4);
	print("a5 ulong %lud\n", a5);
	print("a6 uchar %ud\n", a6);
	print("a7 short %d\n", a7);
	return -36;
}

char
f5(S1 a0, long a1, char a2)
{
	print("in f5\n");
	pS1("a0", a0);
	print("a1 long %ld\n", a1);
	print("a2 char %d\n", a2);
	return 100;
}

S2
f6(S1 a0, long a1)
{
	S2 r;

	print("in f6\n");
	pS1("a0", a0);
	print("a1 long %ld\n", a1);
	r.f0 = 2055000479982952ULL;
	r.f1 = -37.500;
	r.f2 = 921414893;
	r.f3 = 30;
	return r;
}

int
f7(S1 a0, S2 a1, ushort a2, short a3, S3 a4, S0 a5)
{
	print("in f7\n");
	pS1("a0", a0);
	pS2("a1", a1);
	print("a2 ushort %ud\n", a2);
	print("a3 short %d\n", a3);
	pS3("a4", a4);
	pS0("a5", a5);
	return 549049545;
}

S3
f8(vlong a0, ulong a1)
{
	S3 r;

	print("in f8\n");
	print("a0 vlong %lld\n", a0);
	print("a1 ulong %lud\n", a1);
	r.f0[0] = 236;
	r.f0[1] = 157;
	r.f0[2] = 78;
	r.f0[3] = 255;
	r.f0[4] = 176;
	r.f0[5] = 97;
	r.f0[6] = 18;
	r.f0[7] = 195;
	r.f1[0] = 116;
	r.f1[1] = 37;
	r.f1[2] = 214;
	r.f1[3] = 135;
	r.f2 = 37176;
	r.f3 = -2793;
	r.f4 = 154;
	return r;
}

void
f9(uint a0)
{
	print("in f9\n");
	print("a0 uint %ud\n", a0);
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %lud\n", va_arg(ap, ulong));
	print("v1 %g\n", va_arg(ap, double));
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
	print("%s S0 %ud %ud %g %d %ld %ld %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %lud %g %ud %ud %ud %ud %ud %ud %ud %ud %ud %g %d %ud %d\n", w, s.f0, s.f1, s.f2[0], s.f2[1], s.f2[2], s.f2[3], s.f2[4], s.f2[5], s.f2[6], s.f2[7], s.f2[8], s.f3, s.f4, s.f5, s.f6);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %llud %g %d %d\n", w, s.f0, s.f1, s.f2, s.f3);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %ud %ud %ud %ud %ud %ud %ud %ud %ud %ud %ud %ud %ud %d %ud\n", w, s.f0[0], s.f0[1], s.f0[2], s.f0[3], s.f0[4], s.f0[5], s.f0[6], s.f0[7], s.f1[0], s.f1[1], s.f1[2], s.f1[3], s.f2, s.f3, s.f4);
}

static S2
back(S2 x, double d, vlong v)
{
	pS2("back x", x);
	print("back %g %lld\n", d, v);
	x.f0 = x.f0 + 3;
	x.f1 = x.f1 * 2;
	x.f2 = x.f2 + 3;
	x.f3 = x.f3 + 3;
	return x;
}

void
main(void)
{
	{
	S3 v0;
	S3 r;
	v0.f0[0] = 176;
	v0.f0[1] = 97;
	v0.f0[2] = 18;
	v0.f0[3] = 195;
	v0.f0[4] = 116;
	v0.f0[5] = 37;
	v0.f0[6] = 214;
	v0.f0[7] = 135;
	v0.f1[0] = 56;
	v0.f1[1] = 233;
	v0.f1[2] = 154;
	v0.f1[3] = 75;
	v0.f2 = 46076;
	v0.f3 = -11693;
	v0.f4 = 94;
	r = f0(v0, (ushort)33156);
	pS3("ret f0", r);
	}
	{
	S2 v0;
	uchar r;
	v0.f0 = 1382060490ULL;
	v0.f1 = 51.625;
	v0.f2 = 248481068;
	v0.f3 = -93;
	r = f1(v0, (long)783684510L, (uchar)79, (vlong)1797588736LL);
	print("ret f1 uchar %ud\n", r);
	}
	{
	S3 v0;
	S1 r;
	v0.f0[0] = 70;
	v0.f0[1] = 247;
	v0.f0[2] = 168;
	v0.f0[3] = 89;
	v0.f0[4] = 10;
	v0.f0[5] = 187;
	v0.f0[6] = 108;
	v0.f0[7] = 29;
	v0.f1[0] = 206;
	v0.f1[1] = 127;
	v0.f1[2] = 48;
	v0.f1[3] = 225;
	v0.f2 = 52114;
	v0.f3 = 17731;
	v0.f4 = 244;
	r = f2(v0, (ushort)39194, (ushort)4811, (ulong)2460796UL, (int)509412909, (long)-1016365022L);
	pS1("ret f2", r);
	}
	{
	f3((double)-22.500, (uint)1460144597U, (char)6);
	}
	{
	S0 v2;
	char r;
	v2.f0 = 1903924172U;
	v2.f1 = 3453;
	v2.f2 = 20.250;
	v2.f3 = -95;
	v2.f4 = 1784248976L;
	v2.f5 = 143717441L;
	v2.f6 = 242;
	r = f4((ulong)1305548192UL, (uvlong)1812505742500922ULL, v2, (char)2, (float)41.625, (ulong)1185872996UL, (uchar)21, (short)28614);
	print("ret f4 char %d\n", r);
	}
	{
	S1 v0;
	char r;
	v0.f0 = 2136604684UL;
	v0.f1 = -14.375;
	v0.f2[0] = 110;
	v0.f2[1] = 31;
	v0.f2[2] = 208;
	v0.f2[3] = 129;
	v0.f2[4] = 50;
	v0.f2[5] = 227;
	v0.f2[6] = 148;
	v0.f2[7] = 69;
	v0.f2[8] = 246;
	v0.f3 = -4.125;
	v0.f4 = 1777579096;
	v0.f5 = 9;
	v0.f6 = -58;
	r = f5(v0, (long)-1538228704L, (char)17);
	print("ret f5 char %d\n", r);
	}
	{
	S1 v0;
	S2 r;
	v0.f0 = 1982008279UL;
	v0.f1 = 45.000;
	v0.f2[0] = 57;
	v0.f2[1] = 234;
	v0.f2[2] = 155;
	v0.f2[3] = 76;
	v0.f2[4] = 253;
	v0.f2[5] = 174;
	v0.f2[6] = 95;
	v0.f2[7] = 16;
	v0.f2[8] = 193;
	v0.f3 = 55.750;
	v0.f4 = -1622982691;
	v0.f5 = 212;
	v0.f6 = 5;
	r = f6(v0, (long)1383632299L);
	pS2("ret f6", r);
	}
	{
	S1 v0;
	S2 v1;
	S3 v4;
	S0 v5;
	int r;
	v0.f0 = 1320459761UL;
	v0.f1 = 6.750;
	v0.f2[0] = 83;
	v0.f2[1] = 4;
	v0.f2[2] = 181;
	v0.f2[3] = 102;
	v0.f2[4] = 23;
	v0.f2[5] = 200;
	v0.f2[6] = 121;
	v0.f2[7] = 42;
	v0.f2[8] = 219;
	v0.f3 = 16.500;
	v0.f4 = 961434173;
	v0.f5 = 238;
	v0.f6 = -31;
	v1.f0 = 722085947251350ULL;
	v1.f1 = 26.250;
	v1.f2 = 1735988007;
	v1.f3 = -88;
	v4.f0[0] = 153;
	v4.f0[1] = 74;
	v4.f0[2] = 251;
	v4.f0[3] = 172;
	v4.f0[4] = 93;
	v4.f0[5] = 14;
	v4.f0[6] = 191;
	v4.f0[7] = 112;
	v4.f1[0] = 33;
	v4.f1[1] = 210;
	v4.f1[2] = 131;
	v4.f1[3] = 52;
	v4.f2 = 21989;
	v4.f3 = -20374;
	v4.f4 = 71;
	v5.f0 = 1672815469U;
	v5.f1 = 40222;
	v5.f2 = -30.125;
	v5.f3 = 0;
	v5.f4 = 1553140273L;
	v5.f5 = -2060092386L;
	v5.f6 = 147;
	r = f7(v0, v1, (ushort)42305, (short)7922, v4, v5);
	print("ret f7 int %d\n", r);
	}
	{
	S3 r;
	r = f8((vlong)-1518219064LL, (ulong)2025171177UL);
	pS3("ret f8", r);
	}
	{
	f9((uint)1961998639U);
	}
	vf(2, (ulong)1898826101UL, (double)8.250);
	{
	S2 x, r;

	x.f0 = 741713002132338ULL;
	x.f1 = 35.750;
	x.f2 = 1755615003;
	x.f3 = 76;
	r = cb(back, x);
	pS2("ret cb", r);
	}
	exits(nil);
}
#endif
