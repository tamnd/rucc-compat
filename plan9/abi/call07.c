#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { char f0[2]; short f1; char f2; };
typedef struct S1 S1;
struct S1 { char f0[9]; vlong f1; double f2; short f3; float f4; uchar f5; };
typedef struct S2 S2;
struct S2 { int f0; ushort f1; short f2; float f3; uint f4; float f5; char f6; uchar f7[8]; double f8; char f9; char f10; char f11; };
typedef struct S3 S3;
struct S3 { double f0; char f1; };

short f0(uint a0, S2 a1, uvlong a2);
uchar f1(short a0, S2 a1, S3 a2, S2 a3, short a4, long a5, S1 a6, float a7);
ulong f2(int a0, ulong a1, S3 a2, int a3, int a4, char a5, S1 a6, S1 a7);
S1 f3(S2 a0, char a1, long a2, S0 a3, int a4, ushort a5, uchar a6, S0 a7);
short f4(S0 a0, ulong a1, S2 a2, char a3);
long f5(float a0, float a1);
double f6(float a0, double a1, ushort a2, short a3, double a4, int a5, float a6, S1 a7);
uvlong f7(short a0, char a1, float a2, uchar a3, double a4, S3 a5);
S3 f8(uchar a0, long a1, float a2);
void f9(S1 a0, char a1, S2 a2, ulong a3, S2 a4, int a5, int a6, S3 a7);
void vf(int n, ...);
S1 cb(S1 (*fn)(S1, double, vlong), S1 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %d %d %d %d\n", w, s.f0[0], s.f0[1], s.f1, s.f2);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %d %d %d %d %d %d %d %d %d %lld %g %d %g %ud\n", w, s.f0[0], s.f0[1], s.f0[2], s.f0[3], s.f0[4], s.f0[5], s.f0[6], s.f0[7], s.f0[8], s.f1, s.f2, s.f3, s.f4, s.f5);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d %ud %d %g %ud %g %d %ud %ud %ud %ud %ud %ud %ud %ud %g %d %d %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7[0], s.f7[1], s.f7[2], s.f7[3], s.f7[4], s.f7[5], s.f7[6], s.f7[7], s.f8, s.f9, s.f10, s.f11);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %g %d\n", w, s.f0, s.f1);
}

short
f0(uint a0, S2 a1, uvlong a2)
{
	print("in f0\n");
	print("a0 uint %ud\n", a0);
	pS2("a1", a1);
	print("a2 uvlong %llud\n", a2);
	return 14000;
}

uchar
f1(short a0, S2 a1, S3 a2, S2 a3, short a4, long a5, S1 a6, float a7)
{
	print("in f1\n");
	print("a0 short %d\n", a0);
	pS2("a1", a1);
	pS3("a2", a2);
	pS2("a3", a3);
	print("a4 short %d\n", a4);
	print("a5 long %ld\n", a5);
	pS1("a6", a6);
	print("a7 float %g\n", a7);
	return 123;
}

ulong
f2(int a0, ulong a1, S3 a2, int a3, int a4, char a5, S1 a6, S1 a7)
{
	print("in f2\n");
	print("a0 int %d\n", a0);
	print("a1 ulong %lud\n", a1);
	pS3("a2", a2);
	print("a3 int %d\n", a3);
	print("a4 int %d\n", a4);
	print("a5 char %d\n", a5);
	pS1("a6", a6);
	pS1("a7", a7);
	return 1307461412UL;
}

S1
f3(S2 a0, char a1, long a2, S0 a3, int a4, ushort a5, uchar a6, S0 a7)
{
	S1 r;

	print("in f3\n");
	pS2("a0", a0);
	print("a1 char %d\n", a1);
	print("a2 long %ld\n", a2);
	pS0("a3", a3);
	print("a4 int %d\n", a4);
	print("a5 ushort %ud\n", a5);
	print("a6 uchar %ud\n", a6);
	pS0("a7", a7);
	r.f0[0] = -6;
	r.f0[1] = 55;
	r.f0[2] = 104;
	r.f0[3] = -25;
	r.f0[4] = 74;
	r.f0[5] = 123;
	r.f0[6] = -44;
	r.f0[7] = 93;
	r.f0[8] = 14;
	r.f1 = -4611244533391936778LL;
	r.f2 = -8.000;
	r.f3 = 29985;
	r.f4 = -6.750;
	r.f5 = 131;
	return r;
}

short
f4(S0 a0, ulong a1, S2 a2, char a3)
{
	print("in f4\n");
	pS0("a0", a0);
	print("a1 ulong %lud\n", a1);
	pS2("a2", a2);
	print("a3 char %d\n", a3);
	return 16432;
}

long
f5(float a0, float a1)
{
	print("in f5\n");
	print("a0 float %g\n", a0);
	print("a1 float %g\n", a1);
	return 893504975L;
}

double
f6(float a0, double a1, ushort a2, short a3, double a4, int a5, float a6, S1 a7)
{
	print("in f6\n");
	print("a0 float %g\n", a0);
	print("a1 double %g\n", a1);
	print("a2 ushort %ud\n", a2);
	print("a3 short %d\n", a3);
	print("a4 double %g\n", a4);
	print("a5 int %d\n", a5);
	print("a6 float %g\n", a6);
	pS1("a7", a7);
	return 11.250;
}

uvlong
f7(short a0, char a1, float a2, uchar a3, double a4, S3 a5)
{
	print("in f7\n");
	print("a0 short %d\n", a0);
	print("a1 char %d\n", a1);
	print("a2 float %g\n", a2);
	print("a3 uchar %ud\n", a3);
	print("a4 double %g\n", a4);
	pS3("a5", a5);
	return 1569965062ULL;
}

S3
f8(uchar a0, long a1, float a2)
{
	S3 r;

	print("in f8\n");
	print("a0 uchar %ud\n", a0);
	print("a1 long %ld\n", a1);
	print("a2 float %g\n", a2);
	r.f0 = 37.000;
	r.f1 = 113;
	return r;
}

void
f9(S1 a0, char a1, S2 a2, ulong a3, S2 a4, int a5, int a6, S3 a7)
{
	print("in f9\n");
	pS1("a0", a0);
	print("a1 char %d\n", a1);
	pS2("a2", a2);
	print("a3 ulong %lud\n", a3);
	pS2("a4", a4);
	print("a5 int %d\n", a5);
	print("a6 int %d\n", a6);
	pS3("a7", a7);
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %llud\n", va_arg(ap, uvlong));
	print("v1 %lld\n", va_arg(ap, vlong));
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
	print("%s S0 %d %d %d %d\n", w, s.f0[0], s.f0[1], s.f1, s.f2);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %d %d %d %d %d %d %d %d %d %lld %g %d %g %ud\n", w, s.f0[0], s.f0[1], s.f0[2], s.f0[3], s.f0[4], s.f0[5], s.f0[6], s.f0[7], s.f0[8], s.f1, s.f2, s.f3, s.f4, s.f5);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d %ud %d %g %ud %g %d %ud %ud %ud %ud %ud %ud %ud %ud %g %d %d %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7[0], s.f7[1], s.f7[2], s.f7[3], s.f7[4], s.f7[5], s.f7[6], s.f7[7], s.f8, s.f9, s.f10, s.f11);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %g %d\n", w, s.f0, s.f1);
}

static S1
back(S1 x, double d, vlong v)
{
	pS1("back x", x);
	print("back %g %lld\n", d, v);
	x.f0[0] = x.f0[0] + 3;
	x.f0[1] = x.f0[1] + 3;
	x.f0[2] = x.f0[2] + 3;
	x.f0[3] = x.f0[3] + 3;
	x.f0[4] = x.f0[4] + 3;
	x.f0[5] = x.f0[5] + 3;
	x.f0[6] = x.f0[6] + 3;
	x.f0[7] = x.f0[7] + 3;
	x.f0[8] = x.f0[8] + 3;
	x.f1 = x.f1 + 3;
	x.f2 = x.f2 * 2;
	x.f3 = x.f3 + 3;
	x.f4 = x.f4 * 2;
	x.f5 = x.f5 + 3;
	return x;
}

void
main(void)
{
	{
	S2 v1;
	short r;
	v1.f0 = 1021804504;
	v1.f1 = 63881;
	v1.f2 = -29498;
	v1.f3 = -21.625;
	v1.f4 = 902129308U;
	v1.f5 = -19.375;
	v1.f6 = 126;
	v1.f7[0] = 175;
	v1.f7[1] = 96;
	v1.f7[2] = 17;
	v1.f7[3] = 194;
	v1.f7[4] = 115;
	v1.f7[5] = 36;
	v1.f7[6] = 213;
	v1.f7[7] = 134;
	v1.f8 = -9.125;
	v1.f9 = 104;
	v1.f10 = -25;
	v1.f11 = 74;
	r = f0((uint)423428524U, v1, (uvlong)930383428141918ULL);
	print("ret f0 short %d\n", r);
	}
	{
	S2 v1;
	S3 v2;
	S2 v3;
	S1 v6;
	uchar r;
	v1.f0 = -867208099;
	v1.f1 = 1364;
	v1.f2 = 32517;
	v1.f3 = 38.250;
	v1.f4 = 747532903U;
	v1.f5 = 40.000;
	v1.f6 = -73;
	v1.f7[0] = 122;
	v1.f7[1] = 43;
	v1.f7[2] = 220;
	v1.f7[3] = 141;
	v1.f7[4] = 62;
	v1.f7[5] = 239;
	v1.f7[6] = 160;
	v1.f7[7] = 81;
	v1.f8 = 50.750;
	v1.f9 = 51;
	v1.f10 = 100;
	v1.f11 = -21;
	v2.f0 = 55.125;
	v2.f1 = -40;
	v3.f0 = 1817939787;
	v3.f1 = 2300;
	v3.f2 = -685;
	v3.f3 = -19.250;
	v3.f4 = 1698264591U;
	v3.f5 = -17.000;
	v3.f6 = 113;
	v3.f7[0] = 34;
	v3.f7[1] = 211;
	v3.f7[2] = 132;
	v3.f7[3] = 53;
	v3.f7[4] = 230;
	v3.f7[5] = 151;
	v3.f7[6] = 72;
	v3.f7[7] = 249;
	v3.f8 = -7.750;
	v3.f9 = 91;
	v3.f10 = -12;
	v3.f11 = 61;
	v6.f0[0] = -31;
	v6.f0[1] = 80;
	v6.f0[2] = 1;
	v6.f0[3] = -50;
	v6.f0[4] = 99;
	v6.f0[5] = 20;
	v6.f0[6] = -69;
	v6.f0[7] = 118;
	v6.f0[8] = 39;
	v6.f1 = -1487165528LL;
	v6.f2 = 8.875;
	v6.f3 = 19386;
	v6.f4 = 10.625;
	v6.f5 = 28;
	r = f1((short)4851, v1, v2, v3, (short)-3236, (long)1635092053L, v6, (float)21.250);
	print("ret f1 uchar %ud\n", r);
	}
	{
	S3 v2;
	S1 v6;
	S1 v7;
	ulong r;
	v2.f0 = -38.500;
	v2.f1 = 125;
	v6.f0[0] = -32;
	v6.f0[1] = 81;
	v6.f0[2] = 2;
	v6.f0[3] = -51;
	v6.f0[4] = 100;
	v6.f0[5] = 21;
	v6.f0[6] = -70;
	v6.f0[7] = 119;
	v6.f0[8] = 40;
	v6.f1 = -4609937915814095804LL;
	v6.f2 = -8.750;
	v6.f3 = 19643;
	v6.f4 = -6.500;
	v6.f5 = 29;
	v7.f0[0] = 116;
	v7.f0[1] = -37;
	v7.f0[2] = 86;
	v7.f0[3] = 7;
	v7.f0[4] = -56;
	v7.f0[5] = 105;
	v7.f0[6] = 26;
	v7.f0[7] = -75;
	v7.f0[8] = 124;
	v7.f1 = 1149724838164174LL;
	v7.f2 = 12.250;
	v7.f3 = 20111;
	v7.f4 = 14.000;
	v7.f5 = 241;
	r = f2((int)283743688, (ulong)790695801UL, v2, (int)-1297647914, (int)1804600027, (char)12, v6, v7);
	print("ret f2 ulong %lud\n", r);
	}
	{
	S2 v0;
	S0 v3;
	S0 v7;
	S1 r;
	v0.f0 = 100895954;
	v0.f1 = 1667;
	v0.f2 = -52;
	v0.f3 = -30.375;
	v0.f4 = 2128704406U;
	v0.f5 = -28.125;
	v0.f6 = 120;
	v0.f7[0] = 169;
	v0.f7[1] = 90;
	v0.f7[2] = 11;
	v0.f7[3] = 188;
	v0.f7[4] = 109;
	v0.f7[5] = 30;
	v0.f7[6] = 207;
	v0.f7[7] = 128;
	v0.f8 = -18.875;
	v0.f9 = 98;
	v0.f10 = -19;
	v0.f11 = 68;
	v3.f0[0] = -38;
	v3.f0[1] = 87;
	v3.f1 = 520;
	v3.f2 = -57;
	v7.f0[0] = 122;
	v7.f0[1] = -43;
	v7.f1 = 988;
	v7.f2 = 13;
	r = f3(v0, (char)78, (long)960203775L, v3, (int)-1467155888, (ushort)32609, (uchar)18, v7);
	pS1("ret f3", r);
	}
	{
	S0 v0;
	S2 v2;
	short r;
	v0.f0[0] = 88;
	v0.f0[1] = 9;
	v0.f1 = -31930;
	v0.f2 = 107;
	v2.f0 = -1819511596;
	v2.f1 = 1245;
	v2.f2 = 32398;
	v2.f3 = -5.125;
	v2.f4 = 1699836400U;
	v2.f5 = -3.875;
	v2.f6 = -82;
	v2.f7[0] = 3;
	v2.f7[1] = 180;
	v2.f7[2] = 101;
	v2.f7[3] = 22;
	v2.f7[4] = 199;
	v2.f7[5] = 120;
	v2.f7[6] = 41;
	v2.f7[7] = 218;
	v2.f8 = 7.625;
	v2.f9 = 60;
	v2.f10 = 109;
	v2.f11 = -30;
	r = f4(v0, (ulong)1221135616UL, v2, (char)-49);
	print("ret f4 short %d\n", r);
	}
	{
	long r;
	r = f5((float)51.125, (float)52.000);
	print("ret f5 long %ld\n", r);
	}
	{
	S1 v7;
	double r;
	v7.f0[0] = 110;
	v7.f0[1] = -31;
	v7.f0[2] = 80;
	v7.f0[3] = 1;
	v7.f0[4] = -50;
	v7.f0[5] = 99;
	v7.f0[6] = 20;
	v7.f0[7] = -69;
	v7.f0[8] = 118;
	v7.f1 = 228813525438524LL;
	v7.f2 = 3.000;
	v7.f3 = 23433;
	v7.f4 = 5.750;
	v7.f5 = 235;
	r = f6((float)13.750, (double)14.625, (ushort)38436, (short)4053, (double)17.250, (int)-1897595703, (float)19.000, v7);
	print("ret f6 double %g\n", r);
	}
	{
	S3 v5;
	uvlong r;
	v5.f0 = -40.250;
	v5.f1 = 95;
	r = f7((short)3842, (char)-51, (float)-18.500, (uchar)21, (double)-16.250, v5);
	print("ret f7 uvlong %llud\n", r);
	}
	{
	S3 r;
	r = f8((uchar)12, (long)-2067103677L, (float)24.250);
	pS3("ret f8", r);
	}
	{
	S1 v0;
	S2 v2;
	S2 v4;
	S3 v7;
	v0.f0[0] = -52;
	v0.f0[1] = 101;
	v0.f0[2] = 22;
	v0.f0[3] = -71;
	v0.f0[4] = 120;
	v0.f0[5] = 41;
	v0.f0[6] = -90;
	v0.f0[7] = 11;
	v0.f0[8] = 60;
	v0.f1 = -4611055015209383936LL;
	v0.f2 = -25.250;
	v0.f3 = 17487;
	v0.f4 = -23.000;
	v0.f5 = 177;
	v2.f0 = 1912507272;
	v2.f1 = 1337;
	v2.f2 = 32490;
	v2.f3 = -12.625;
	v2.f4 = 1792832076U;
	v2.f5 = -10.375;
	v2.f6 = 46;
	v2.f7[0] = 95;
	v2.f7[1] = 16;
	v2.f7[2] = 193;
	v2.f7[3] = 114;
	v2.f7[4] = 35;
	v2.f7[5] = 212;
	v2.f7[6] = 133;
	v2.f7[7] = 54;
	v2.f8 = 0.125;
	v2.f9 = -24;
	v2.f10 = 73;
	v2.f11 = 122;
	v4.f0 = 1314131292;
	v4.f1 = 34573;
	v4.f2 = -190;
	v4.f3 = 8.125;
	v4.f4 = 1194456096U;
	v4.f5 = 10.875;
	v4.f6 = 2;
	v4.f7[0] = 51;
	v4.f7[1] = 228;
	v4.f7[2] = 149;
	v4.f7[3] = 70;
	v4.f7[4] = 247;
	v4.f7[5] = 168;
	v4.f7[6] = 89;
	v4.f7[7] = 10;
	v4.f8 = 20.625;
	v4.f9 = 108;
	v4.f10 = -29;
	v4.f11 = 78;
	v7.f0 = 25.000;
	v7.f1 = 97;
	f9(v0, (char)4, v2, (ulong)624331445UL, v4, (int)1131283558, (int)1638235671, v7);
	}
	vf(2, (uvlong)1575067858189406ULL, (vlong)2082015246LL);
	{
	S1 x, r;

	x.f0[0] = 33;
	x.f0[1] = 82;
	x.f0[2] = -3;
	x.f0[3] = 52;
	x.f0[4] = 101;
	x.f0[5] = -22;
	x.f0[6] = 71;
	x.f0[7] = 120;
	x.f0[8] = -41;
	x.f1 = 685549530LL;
	x.f2 = 26.625;
	x.f3 = -6972;
	x.f4 = 28.375;
	x.f5 = 158;
	r = cb(back, x);
	pS1("ret cb", r);
	}
	exits(nil);
}
#endif
