#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { short f0; short f1; float f2; char f3[9]; uvlong f4; uchar f5[6]; };
typedef struct S1 S1;
struct S1 { double f0; char f1; short f2; double f3; ulong f4; double f5; long f6; short f7; short f8; ushort f9; char f10[3]; double f11; long f12; double f13; };
typedef struct S2 S2;
struct S2 { uchar f0; ushort f1; float f2; ushort f3; long f4; char f5; uchar f6; uchar f7; };
typedef struct S3 S3;
struct S3 { int f0; uint f1; char f2; };

S1 f0(S0 a0, uvlong a1);
uvlong f1(double a0, char a1, S0 a2, ushort a3);
char f2(S3 a0, S0 a1, S3 a2, short a3, short a4, long a5, S0 a6, S2 a7);
vlong f3(S0 a0, S2 a1, double a2, short a3, uvlong a4, S2 a5);
uchar f4(S2 a0, char a1);
S3 f5(S1 a0, S1 a1, int a2, char a3, int a4, S1 a5);
ulong f6(vlong a0, ushort a1, uchar a2, S1 a3, ulong a4, S2 a5, ulong a6, S3 a7);
vlong f7(short a0, vlong a1, short a2, S0 a3);
float f8(long a0, S0 a1, uvlong a2, S3 a3, short a4, ushort a5);
uint f9(long a0, S2 a1, uint a2);
void vf(int n, ...);
S3 cb(S3 (*fn)(S3, double, vlong), S3 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %d %d %g %d %d %d %d %d %d %d %d %d %llud %ud %ud %ud %ud %ud %ud\n", w, s.f0, s.f1, s.f2, s.f3[0], s.f3[1], s.f3[2], s.f3[3], s.f3[4], s.f3[5], s.f3[6], s.f3[7], s.f3[8], s.f4, s.f5[0], s.f5[1], s.f5[2], s.f5[3], s.f5[4], s.f5[5]);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %g %d %d %g %lud %g %ld %d %d %ud %d %d %d %g %ld %g\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10[0], s.f10[1], s.f10[2], s.f11, s.f12, s.f13);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %ud %ud %g %ud %ld %d %ud %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %d %ud %d\n", w, s.f0, s.f1, s.f2);
}

S1
f0(S0 a0, uvlong a1)
{
	S1 r;

	print("in f0\n");
	pS0("a0", a0);
	print("a1 uvlong %llud\n", a1);
	r.f0 = -25.500;
	r.f1 = -101;
	r.f2 = 8470;
	r.f3 = -22.125;
	r.f4 = 2100794488UL;
	r.f5 = -20.875;
	r.f6 = 967215066L;
	r.f7 = -395;
	r.f8 = 31548;
	r.f9 = 62701;
	r.f10[0] = -30;
	r.f10[1] = 79;
	r.f10[2] = 0;
	r.f11 = -12.875;
	r.f12 = 727864674L;
	r.f13 = -10.625;
	return r;
}

uvlong
f1(double a0, char a1, S0 a2, ushort a3)
{
	print("in f1\n");
	print("a0 double %g\n", a0);
	print("a1 char %d\n", a1);
	pS0("a2", a2);
	print("a3 ushort %ud\n", a3);
	return 714524914ULL;
}

char
f2(S3 a0, S0 a1, S3 a2, short a3, short a4, long a5, S0 a6, S2 a7)
{
	print("in f2\n");
	pS3("a0", a0);
	pS0("a1", a1);
	pS3("a2", a2);
	print("a3 short %d\n", a3);
	print("a4 short %d\n", a4);
	print("a5 long %ld\n", a5);
	pS0("a6", a6);
	pS2("a7", a7);
	return 110;
}

vlong
f3(S0 a0, S2 a1, double a2, short a3, uvlong a4, S2 a5)
{
	print("in f3\n");
	pS0("a0", a0);
	pS2("a1", a1);
	print("a2 double %g\n", a2);
	print("a3 short %d\n", a3);
	print("a4 uvlong %llud\n", a4);
	pS2("a5", a5);
	return -1173216058LL;
}

uchar
f4(S2 a0, char a1)
{
	print("in f4\n");
	pS2("a0", a0);
	print("a1 char %d\n", a1);
	return 94;
}

S3
f5(S1 a0, S1 a1, int a2, char a3, int a4, S1 a5)
{
	S3 r;

	print("in f5\n");
	pS1("a0", a0);
	pS1("a1", a1);
	print("a2 int %d\n", a2);
	print("a3 char %d\n", a3);
	print("a4 int %d\n", a4);
	pS1("a5", a5);
	r.f0 = 511667540;
	r.f1 = 1018619653U;
	r.f2 = -54;
	return r;
}

ulong
f6(vlong a0, ushort a1, uchar a2, S1 a3, ulong a4, S2 a5, ulong a6, S3 a7)
{
	print("in f6\n");
	print("a0 vlong %lld\n", a0);
	print("a1 ushort %ud\n", a1);
	print("a2 uchar %ud\n", a2);
	pS1("a3", a3);
	print("a4 ulong %lud\n", a4);
	pS2("a5", a5);
	print("a6 ulong %lud\n", a6);
	pS3("a7", a7);
	return 970358684UL;
}

vlong
f7(short a0, vlong a1, short a2, S0 a3)
{
	print("in f7\n");
	print("a0 short %d\n", a0);
	print("a1 vlong %lld\n", a1);
	print("a2 short %d\n", a2);
	pS0("a3", a3);
	return -1139866658LL;
}

float
f8(long a0, S0 a1, uvlong a2, S3 a3, short a4, ushort a5)
{
	print("in f8\n");
	print("a0 long %ld\n", a0);
	pS0("a1", a1);
	print("a2 uvlong %llud\n", a2);
	pS3("a3", a3);
	print("a4 short %d\n", a4);
	print("a5 ushort %ud\n", a5);
	return -23.250;
}

uint
f9(long a0, S2 a1, uint a2)
{
	print("in f9\n");
	print("a0 long %ld\n", a0);
	pS2("a1", a1);
	print("a2 uint %ud\n", a2);
	return 1753154207U;
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
	print("%s S0 %d %d %g %d %d %d %d %d %d %d %d %d %llud %ud %ud %ud %ud %ud %ud\n", w, s.f0, s.f1, s.f2, s.f3[0], s.f3[1], s.f3[2], s.f3[3], s.f3[4], s.f3[5], s.f3[6], s.f3[7], s.f3[8], s.f4, s.f5[0], s.f5[1], s.f5[2], s.f5[3], s.f5[4], s.f5[5]);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %g %d %d %g %lud %g %ld %d %d %ud %d %d %d %g %ld %g\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10[0], s.f10[1], s.f10[2], s.f11, s.f12, s.f13);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %ud %ud %g %ud %ld %d %ud %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %d %ud %d\n", w, s.f0, s.f1, s.f2);
}

static S3
back(S3 x, double d, vlong v)
{
	pS3("back x", x);
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
	S0 v0;
	S1 r;
	v0.f0 = 0;
	v0.f1 = 31153;
	v0.f2 = -38.750;
	v0.f3[0] = -19;
	v0.f3[1] = 68;
	v0.f3[2] = 117;
	v0.f3[3] = -38;
	v0.f3[4] = 87;
	v0.f3[5] = 8;
	v0.f3[6] = -57;
	v0.f3[7] = 106;
	v0.f3[8] = 27;
	v0.f4 = 1788458060ULL;
	v0.f5[0] = 253;
	v0.f5[1] = 174;
	v0.f5[2] = 95;
	v0.f5[3] = 16;
	v0.f5[4] = 193;
	v0.f5[5] = 114;
	r = f0(v0, (uvlong)1549107668ULL);
	pS1("ret f0", r);
	}
	{
	S0 v2;
	uvlong r;
	v2.f0 = 4634;
	v2.f1 = 3019;
	v2.f2 = 20.500;
	v2.f3[0] = 45;
	v2.f3[1] = 94;
	v2.f3[2] = -15;
	v2.f3[3] = 64;
	v2.f3[4] = 113;
	v2.f3[5] = -34;
	v2.f3[6] = 83;
	v2.f3[7] = 4;
	v2.f3[8] = -53;
	v2.f4 = 1126909542ULL;
	v2.f5[0] = 23;
	v2.f5[1] = 200;
	v2.f5[2] = 121;
	v2.f5[3] = 42;
	v2.f5[4] = 219;
	v2.f5[5] = 140;
	r = f1((double)38.250, (char)31, v2, (ushort)1872);
	print("ret f1 uvlong %llud\n", r);
	}
	{
	S3 v0;
	S0 v1;
	S3 v2;
	S0 v6;
	S2 v7;
	char r;
	v0.f0 = 1838290838;
	v0.f1 = 197759303U;
	v0.f2 = -120;
	v1.f0 = -6506;
	v1.f1 = 4891;
	v1.f2 = 3.500;
	v1.f3[0] = -125;
	v1.f3[1] = 46;
	v1.f3[2] = 95;
	v1.f3[3] = -16;
	v1.f3[4] = 65;
	v1.f3[5] = 114;
	v1.f3[6] = -35;
	v1.f3[7] = 84;
	v1.f3[8] = 5;
	v1.f4 = 880889270ULL;
	v1.f5[0] = 103;
	v1.f5[1] = 24;
	v1.f5[2] = 201;
	v1.f5[3] = 122;
	v1.f5[4] = 43;
	v1.f5[5] = 220;
	v2.f0 = 641538878;
	v2.f1 = 1148490991U;
	v2.f2 = 32;
	v6.f0 = 7442;
	v6.f1 = 5827;
	v6.f2 = 43.500;
	v6.f3[0] = 37;
	v6.f3[1] = 86;
	v6.f3[2] = -7;
	v6.f3[3] = 56;
	v6.f3[4] = 105;
	v6.f3[5] = -26;
	v6.f3[6] = 75;
	v6.f3[7] = 124;
	v6.f3[8] = -45;
	v6.f4 = 1831620958ULL;
	v6.f5[0] = 15;
	v6.f5[1] = 192;
	v6.f5[2] = 113;
	v6.f5[3] = 34;
	v6.f5[4] = 211;
	v6.f5[5] = 132;
	v7.f0 = 230;
	v7.f1 = 39063;
	v7.f2 = -34.000;
	v7.f3 = 35833;
	v7.f4 = 1472595370L;
	v7.f5 = 91;
	v7.f6 = 12;
	v7.f7 = 189;
	r = f2(v0, v1, v2, (short)8378, (short)-6763, (long)2007798812L, v6, v7);
	print("ret f2 char %d\n", r);
	}
	{
	S0 v0;
	S2 v1;
	S2 v5;
	vlong r;
	v0.f0 = -9314;
	v0.f1 = 7699;
	v0.f2 = 26.500;
	v0.f3[0] = -117;
	v0.f3[1] = 38;
	v0.f3[2] = 87;
	v0.f3[3] = -8;
	v0.f3[4] = 57;
	v0.f3[5] = 106;
	v0.f3[6] = -27;
	v0.f3[7] = 76;
	v0.f3[8] = 125;
	v0.f4 = 1585600686ULL;
	v0.f5[0] = 95;
	v0.f5[1] = 16;
	v0.f5[2] = 193;
	v0.f5[3] = 114;
	v0.f5[4] = 35;
	v0.f5[5] = 212;
	v1.f0 = 54;
	v1.f1 = 40935;
	v1.f2 = 46.000;
	v1.f3 = 37705;
	v1.f4 = -1226575098L;
	v1.f5 = 43;
	v1.f6 = 92;
	v1.f7 = 13;
	v5.f0 = 10;
	v5.f1 = 8635;
	v5.f2 = -31.500;
	v5.f3 = 5405;
	v5.f4 = 628199118L;
	v5.f5 = -127;
	v5.f6 = 48;
	v5.f7 = 225;
	r = f3(v0, v1, (double)-13.250, (short)9103, (uvlong)1163402560ULL, v5);
	print("ret f3 vlong %lld\n", r);
	}
	{
	S2 v0;
	uchar r;
	v0.f0 = 134;
	v0.f1 = 42807;
	v0.f2 = 29.000;
	v0.f3 = 39577;
	v0.f4 = 980554826L;
	v0.f5 = -123;
	v0.f6 = 172;
	v0.f7 = 93;
	r = f4(v0, (char)-90);
	print("ret f4 uchar %ud\n", r);
	}
	{
	S1 v0;
	S1 v1;
	S1 v5;
	S3 r;
	v0.f0 = -12.000;
	v0.f1 = -81;
	v0.f2 = 13058;
	v0.f3 = -9.625;
	v0.f4 = 319006308UL;
	v0.f5 = -7.375;
	v0.f6 = 1332910534L;
	v0.f7 = -4983;
	v0.f8 = 3368;
	v0.f9 = 1753;
	v0.f10[0] = -10;
	v0.f10[1] = 59;
	v0.f10[2] = 108;
	v0.f11 = 1.375;
	v0.f12 = 1093560142L;
	v0.f13 = 3.125;
	v1.f0 = 8.500;
	v1.f1 = 37;
	v1.f2 = -13526;
	v1.f3 = 11.125;
	v1.f4 = 1868113976UL;
	v1.f5 = 13.875;
	v1.f6 = 734534554L;
	v1.f7 = 5451;
	v1.f8 = -3836;
	v1.f9 = 34989;
	v1.f10[0] = 94;
	v1.f10[1] = -15;
	v1.f10[2] = 64;
	v1.f11 = 21.875;
	v1.f12 = -495184162L;
	v1.f13 = 23.625;
	v5.f0 = 28.000;
	v5.f1 = 121;
	v5.f2 = 13994;
	v5.f3 = 31.625;
	v5.f4 = 1269737996UL;
	v5.f5 = 33.375;
	v5.f6 = -136158574L;
	v5.f7 = 5919;
	v5.f8 = 4304;
	v5.f9 = 2689;
	v5.f10[0] = 50;
	v5.f10[1] = 99;
	v5.f10[2] = -20;
	v5.f11 = 41.375;
	v5.f12 = 2044291830L;
	v5.f13 = 43.125;
	r = f5(v0, v1, (int)791037212, (char)-77, (int)1804941438, v5);
	pS3("ret f5", r);
	}
	{
	S1 v3;
	S2 v5;
	S3 v7;
	ulong r;
	v3.f0 = -9.500;
	v3.f1 = 117;
	v3.f2 = 15398;
	v3.f3 = -6.125;
	v3.f4 = 1622093704UL;
	v3.f5 = -4.875;
	v3.f6 = -488514282L;
	v3.f7 = 7323;
	v3.f8 = 5708;
	v3.f9 = 36861;
	v3.f10[0] = 46;
	v3.f10[1] = 95;
	v3.f10[2] = -16;
	v3.f11 = 4.875;
	v3.f12 = 249163890L;
	v3.f13 = 6.625;
	v5.f0 = 152;
	v5.f1 = 17481;
	v5.f2 = 13.750;
	v5.f3 = 14251;
	v5.f4 = -1023717724L;
	v5.f5 = 13;
	v5.f6 = 190;
	v5.f7 = 111;
	v7.f0 = 545016940;
	v7.f1 = 1051969053U;
	v7.f2 = -78;
	r = f6((vlong)-2094124608LL, (ushort)18417, (uchar)162, v3, (ulong)1467497299UL, v5, (ulong)1974449412UL, v7);
	print("ret f6 ulong %lud\n", r);
	}
	{
	S0 v3;
	vlong r;
	v3.f0 = -17738;
	v3.f1 = 16123;
	v3.f2 = -2.500;
	v3.f3[0] = -93;
	v3.f3[1] = 14;
	v3.f3[2] = 63;
	v3.f3[3] = -112;
	v3.f3[4] = 33;
	v3.f3[5] = 82;
	v3.f3[6] = -3;
	v3.f3[7] = 52;
	v3.f3[8] = 101;
	v3.f4 = 1552251286ULL;
	v3.f5[0] = 71;
	v3.f5[1] = 248;
	v3.f5[2] = 169;
	v3.f5[3] = 90;
	v3.f5[4] = 11;
	v3.f5[5] = 188;
	r = f7((short)18206, (vlong)-4609866159960828890LL, (short)14976, v3);
	print("ret f7 vlong %lld\n", r);
	}
	{
	S0 v1;
	S3 v3;
	float r;
	v1.f0 = -19142;
	v1.f1 = 17527;
	v1.f2 = -39.000;
	v1.f3[0] = -89;
	v1.f3[1] = 10;
	v1.f3[2] = 59;
	v1.f3[3] = -108;
	v1.f3[4] = 29;
	v1.f3[5] = 78;
	v1.f3[6] = -127;
	v1.f3[7] = 48;
	v1.f3[8] = 97;
	v1.f4 = 1904606994ULL;
	v1.f5[0] = 195;
	v1.f5[1] = 116;
	v1.f5[2] = 37;
	v1.f5[3] = 214;
	v1.f5[4] = 135;
	v1.f5[5] = 56;
	v3.f0 = 1665256602;
	v3.f1 = 24725067U;
	v3.f2 = 124;
	r = f8((long)1066880622L, v1, (uvlong)1573837456498212ULL, v3, (short)-16848, (ushort)48001);
	print("ret f8 float %g\n", r);
	}
	{
	S2 v1;
	uint r;
	v1.f0 = 199;
	v1.f1 = 17784;
	v1.f2 = 42.875;
	v1.f3 = 14554;
	v1.f4 = 257405579L;
	v1.f5 = 60;
	v1.f6 = 237;
	v1.f7 = 158;
	r = f9((long)1926188443L, v1, (uint)285656908U);
	print("ret f9 uint %ud\n", r);
	}
	vf(1, (vlong)222484370LL);
	{
	S3 x, r;

	x.f0 = 1212852694;
	x.f1 = 1719804807U;
	x.f2 = 56;
	r = cb(back, x);
	pS3("ret cb", r);
	}
	exits(nil);
}
#endif
