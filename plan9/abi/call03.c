#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { ushort f0; double f1; vlong f2; uint f3; uchar f4[8]; uchar f5; };
typedef struct S1 S1;
struct S1 { ushort f0; double f1; uint f2; vlong f3; vlong f4; uchar f5; char f6[5]; uchar f7[7]; char f8[7]; short f9; double f10; uchar f11; ushort f12; uchar f13; };
typedef struct S2 S2;
struct S2 { long f0; uvlong f1; vlong f2; short f3; vlong f4; double f5; uint f6; uint f7; int f8; ushort f9; uint f10; long f11; short f12; uchar f13; char f14; };
typedef struct S3 S3;
struct S3 { char f0[2]; int f1; ulong f2; float f3; ushort f4; char f5; };

double f0(uint a0, char a1, float a2);
S0 f1(ushort a0, uchar a1, long a2, char a3, ulong a4, S1 a5, int a6, ulong a7);
char f2(uchar a0, S3 a1, float a2, char a3, long a4, short a5);
S1 f3(short a0, short a1, uvlong a2, S0 a3);
short f4(ulong a0, double a1, ulong a2, S1 a3, ulong a4, vlong a5, float a6, uvlong a7);
double f5(S3 a0, uchar a1, S2 a2, ulong a3, int a4, ushort a5);
S1 f6(uchar a0, S0 a1, long a2, ushort a3, uchar a4, S0 a5);
S2 f7(short a0, long a1, uint a2, char a3, long a4, uint a5, vlong a6, S1 a7);
long f8(ushort a0, float a1, float a2, S1 a3);
void f9(char a0, short a1);
void vf(int n, ...);
S2 cb(S2 (*fn)(S2, double, vlong), S2 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %ud %g %lld %ud %ud %ud %ud %ud %ud %ud %ud %ud %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4[0], s.f4[1], s.f4[2], s.f4[3], s.f4[4], s.f4[5], s.f4[6], s.f4[7], s.f5);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %ud %g %ud %lld %lld %ud %d %d %d %d %d %ud %ud %ud %ud %ud %ud %ud %d %d %d %d %d %d %d %d %g %ud %ud %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6[0], s.f6[1], s.f6[2], s.f6[3], s.f6[4], s.f7[0], s.f7[1], s.f7[2], s.f7[3], s.f7[4], s.f7[5], s.f7[6], s.f8[0], s.f8[1], s.f8[2], s.f8[3], s.f8[4], s.f8[5], s.f8[6], s.f9, s.f10, s.f11, s.f12, s.f13);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %ld %llud %lld %d %lld %g %ud %ud %d %ud %ud %ld %d %ud %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11, s.f12, s.f13, s.f14);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %d %d %d %lud %g %ud %d\n", w, s.f0[0], s.f0[1], s.f1, s.f2, s.f3, s.f4, s.f5);
}

double
f0(uint a0, char a1, float a2)
{
	print("in f0\n");
	print("a0 uint %ud\n", a0);
	print("a1 char %d\n", a1);
	print("a2 float %g\n", a2);
	return -29.000;
}

S0
f1(ushort a0, uchar a1, long a2, char a3, ulong a4, S1 a5, int a6, ulong a7)
{
	S0 r;

	print("in f1\n");
	print("a0 ushort %ud\n", a0);
	print("a1 uchar %ud\n", a1);
	print("a2 long %ld\n", a2);
	print("a3 char %d\n", a3);
	print("a4 ulong %lud\n", a4);
	pS1("a5", a5);
	print("a6 int %d\n", a6);
	print("a7 ulong %lud\n", a7);
	r.f0 = 50068;
	r.f1 = 9.375;
	r.f2 = 328054518LL;
	r.f3 = 835006631U;
	r.f4[0] = 88;
	r.f4[1] = 9;
	r.f4[2] = 186;
	r.f4[3] = 107;
	r.f4[4] = 28;
	r.f4[5] = 205;
	r.f4[6] = 126;
	r.f4[7] = 47;
	r.f5 = 224;
	return r;
}

char
f2(uchar a0, S3 a1, float a2, char a3, long a4, short a5)
{
	print("in f2\n");
	print("a0 uchar %ud\n", a0);
	pS3("a1", a1);
	print("a2 float %g\n", a2);
	print("a3 char %d\n", a3);
	print("a4 long %ld\n", a4);
	print("a5 short %d\n", a5);
	return 120;
}

S1
f3(short a0, short a1, uvlong a2, S0 a3)
{
	S1 r;

	print("in f3\n");
	print("a0 short %d\n", a0);
	print("a1 short %d\n", a1);
	print("a2 uvlong %llud\n", a2);
	pS0("a3", a3);
	r.f0 = 43186;
	r.f1 = 38.625;
	r.f2 = 1926994964U;
	r.f3 = -4611399554138997624LL;
	r.f4 = 793415542LL;
	r.f5 = 39;
	r.f6[0] = -88;
	r.f6[1] = 9;
	r.f6[2] = 58;
	r.f6[3] = -107;
	r.f6[4] = 28;
	r.f7[0] = 77;
	r.f7[1] = 254;
	r.f7[2] = 175;
	r.f7[3] = 96;
	r.f7[4] = 17;
	r.f7[5] = 194;
	r.f7[6] = 115;
	r.f8[0] = -36;
	r.f8[1] = 85;
	r.f8[2] = 6;
	r.f8[3] = -55;
	r.f8[4] = 104;
	r.f8[5] = 25;
	r.f8[6] = -74;
	r.f9 = 2811;
	r.f10 = -34.500;
	r.f11 = 93;
	r.f12 = 63502;
	r.f13 = 191;
	return r;
}

short
f4(ulong a0, double a1, ulong a2, S1 a3, ulong a4, vlong a5, float a6, uvlong a7)
{
	print("in f4\n");
	print("a0 ulong %lud\n", a0);
	print("a1 double %g\n", a1);
	print("a2 ulong %lud\n", a2);
	pS1("a3", a3);
	print("a4 ulong %lud\n", a4);
	print("a5 vlong %lld\n", a5);
	print("a6 float %g\n", a6);
	print("a7 uvlong %llud\n", a7);
	return 14162;
}

double
f5(S3 a0, uchar a1, S2 a2, ulong a3, int a4, ushort a5)
{
	print("in f5\n");
	pS3("a0", a0);
	print("a1 uchar %ud\n", a1);
	pS2("a2", a2);
	print("a3 ulong %lud\n", a3);
	print("a4 int %d\n", a4);
	print("a5 ushort %ud\n", a5);
	return -30.750;
}

S1
f6(uchar a0, S0 a1, long a2, ushort a3, uchar a4, S0 a5)
{
	S1 r;

	print("in f6\n");
	print("a0 uchar %ud\n", a0);
	pS0("a1", a1);
	print("a2 long %ld\n", a2);
	print("a3 ushort %ud\n", a3);
	print("a4 uchar %ud\n", a4);
	pS0("a5", a5);
	r.f0 = 7023;
	r.f1 = 49.000;
	r.f2 = 625479377U;
	r.f3 = 1132431490LL;
	r.f4 = 1639388521150816LL;
	r.f5 = 228;
	r.f6[0] = 21;
	r.f6[1] = 70;
	r.f6[2] = -119;
	r.f6[3] = 40;
	r.f6[4] = 89;
	r.f7[0] = 10;
	r.f7[1] = 187;
	r.f7[2] = 108;
	r.f7[3] = 29;
	r.f7[4] = 206;
	r.f7[5] = 127;
	r.f7[6] = 48;
	r.f8[0] = 97;
	r.f8[1] = 18;
	r.f8[2] = -67;
	r.f8[3] = 116;
	r.f8[4] = 37;
	r.f8[5] = -86;
	r.f8[6] = 7;
	r.f9 = 32184;
	r.f10 = -23.875;
	r.f11 = 26;
	r.f12 = 27339;
	r.f13 = 124;
	return r;
}

S2
f7(short a0, long a1, uint a2, char a3, long a4, uint a5, vlong a6, S1 a7)
{
	S2 r;

	print("in f7\n");
	print("a0 short %d\n", a0);
	print("a1 long %ld\n", a1);
	print("a2 uint %ud\n", a2);
	print("a3 char %d\n", a3);
	print("a4 long %ld\n", a4);
	print("a5 uint %ud\n", a5);
	print("a6 vlong %lld\n", a6);
	pS1("a7", a7);
	r.f0 = 2019990640L;
	r.f1 = 379460243377322ULL;
	r.f2 = -886411218LL;
	r.f3 = 2435;
	r.f4 = 1900315444LL;
	r.f5 = 37.375;
	r.f6 = 766736022U;
	r.f7 = 1273688135U;
	r.f8 = -1780640248;
	r.f9 = 58281;
	r.f10 = 647060826U;
	r.f11 = -1154012939L;
	r.f12 = 20668;
	r.f13 = 109;
	r.f14 = -30;
	return r;
}

long
f8(ushort a0, float a1, float a2, S1 a3)
{
	print("in f8\n");
	print("a0 ushort %ud\n", a0);
	print("a1 float %g\n", a1);
	print("a2 float %g\n", a2);
	pS1("a3", a3);
	return -1408274900L;
}

void
f9(char a0, short a1)
{
	print("in f9\n");
	print("a0 char %d\n", a0);
	print("a1 short %d\n", a1);
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %lld\n", va_arg(ap, vlong));
	print("v1 %lld\n", va_arg(ap, vlong));
	print("v2 %lld\n", va_arg(ap, vlong));
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
	print("%s S0 %ud %g %lld %ud %ud %ud %ud %ud %ud %ud %ud %ud %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4[0], s.f4[1], s.f4[2], s.f4[3], s.f4[4], s.f4[5], s.f4[6], s.f4[7], s.f5);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %ud %g %ud %lld %lld %ud %d %d %d %d %d %ud %ud %ud %ud %ud %ud %ud %d %d %d %d %d %d %d %d %g %ud %ud %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6[0], s.f6[1], s.f6[2], s.f6[3], s.f6[4], s.f7[0], s.f7[1], s.f7[2], s.f7[3], s.f7[4], s.f7[5], s.f7[6], s.f8[0], s.f8[1], s.f8[2], s.f8[3], s.f8[4], s.f8[5], s.f8[6], s.f9, s.f10, s.f11, s.f12, s.f13);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %ld %llud %lld %d %lld %g %ud %ud %d %ud %ud %ld %d %ud %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11, s.f12, s.f13, s.f14);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %d %d %d %lud %g %ud %d\n", w, s.f0[0], s.f0[1], s.f1, s.f2, s.f3, s.f4, s.f5);
}

static S2
back(S2 x, double d, vlong v)
{
	pS2("back x", x);
	print("back %g %lld\n", d, v);
	x.f0 = x.f0 + 3;
	x.f1 = x.f1 + 3;
	x.f2 = x.f2 + 3;
	x.f3 = x.f3 + 3;
	x.f4 = x.f4 + 3;
	x.f5 = x.f5 * 2;
	x.f6 = x.f6 + 3;
	x.f7 = x.f7 + 3;
	x.f8 = x.f8 + 3;
	x.f9 = x.f9 + 3;
	x.f10 = x.f10 + 3;
	x.f11 = x.f11 + 3;
	x.f12 = x.f12 + 3;
	x.f13 = x.f13 + 3;
	x.f14 = x.f14 + 3;
	return x;
}

void
main(void)
{
	{
	double r;
	r = f0((uint)437916216U, (char)105, (float)52.750);
	print("ret f0 double %g\n", r);
	}
	{
	S1 v5;
	S0 r;
	v5.f0 = 5600;
	v5.f1 = -6.875;
	v5.f2 = 255068482U;
	v5.f3 = 762022881061792LL;
	v5.f4 = 1268972708LL;
	v5.f5 = 85;
	v5.f6[0] = 6;
	v5.f6[1] = 55;
	v5.f6[2] = -104;
	v5.f6[3] = 25;
	v5.f6[4] = 74;
	v5.f7[0] = 123;
	v5.f7[1] = 44;
	v5.f7[2] = 221;
	v5.f7[3] = 142;
	v5.f7[4] = 63;
	v5.f7[5] = 240;
	v5.f7[6] = 161;
	v5.f8[0] = 82;
	v5.f8[1] = 3;
	v5.f8[2] = -52;
	v5.f8[3] = 101;
	v5.f8[4] = 22;
	v5.f8[5] = -71;
	v5.f8[6] = 120;
	v5.f9 = 30761;
	v5.f10 = 19.750;
	v5.f11 = 139;
	v5.f12 = 25916;
	v5.f13 = 237;
	r = f1((ushort)38836, (uchar)101, (long)1804176150L, (char)-71, (ulong)670596728UL, v5, (int)1177548841, (ulong)1684500954UL);
	pS0("ret f1", r);
	}
	{
	S3 v1;
	char r;
	v1.f0[0] = 32;
	v1.f0[1] = -81;
	v1.f1 = 487748994;
	v1.f2 = 994701107UL;
	v1.f3 = -36.500;
	v1.f4 = 58005;
	v1.f5 = 70;
	r = f2((uchar)244, v1, (float)-19.375, (char)-86, (long)396325127L, (short)27320);
	print("ret f2 char %d\n", r);
	}
	{
	S0 v3;
	S1 r;
	v3.f0 = 64254;
	v3.f1 = 23.125;
	v3.f2 = -1854008928LL;
	v3.f3 = 213477393U;
	v3.f4[0] = 194;
	v3.f4[1] = 115;
	v3.f4[2] = 36;
	v3.f4[3] = 213;
	v3.f4[4] = 134;
	v3.f4[5] = 55;
	v3.f4[6] = 232;
	v3.f4[7] = 153;
	v3.f5 = 74;
	r = f3((short)-31954, (short)30339, (uvlong)1255632948ULL, v3);
	pS1("ret f3", r);
	}
	{
	S1 v3;
	short r;
	v3.f0 = 32890;
	v3.f1 = -14.625;
	v3.f2 = 58880988U;
	v3.f3 = 565834798499310LL;
	v3.f4 = 1072785214LL;
	v3.f5 = 239;
	v3.f6[0] = 32;
	v3.f6[1] = 81;
	v3.f6[2] = -2;
	v3.f6[3] = 51;
	v3.f6[4] = 100;
	v3.f7[0] = 21;
	v3.f7[1] = 198;
	v3.f7[2] = 119;
	v3.f7[3] = 40;
	v3.f7[4] = 217;
	v3.f7[5] = 138;
	v3.f7[6] = 59;
	v3.f8[0] = 108;
	v3.f8[1] = 29;
	v3.f8[2] = -78;
	v3.f8[3] = 127;
	v3.f8[4] = 48;
	v3.f8[5] = -97;
	v3.f8[6] = 18;
	v3.f9 = 25283;
	v3.f10 = 11.500;
	v3.f11 = 37;
	v3.f12 = 53206;
	v3.f13 = 135;
	r = f4((ulong)594084430UL, (double)6.125, (ulong)1607988656UL, v3, (ulong)2114940769UL, (vlong)474409234LL, (float)10.625, (uvlong)1488313460ULL);
	print("ret f4 short %d\n", r);
	}
	{
	S3 v0;
	S2 v2;
	double r;
	v0.f0[0] = 58;
	v0.f0[1] = -107;
	v0.f1 = 291561500;
	v0.f2 = 798513613UL;
	v0.f3 = 53.250;
	v0.f4 = 19759;
	v0.f5 = 96;
	v2.f0 = 826764942L;
	v2.f1 = 1333721056151172ULL;
	v2.f2 = -1840669168LL;
	v2.f3 = 23457;
	v2.f4 = 707089746LL;
	v2.f5 = -23.625;
	v2.f6 = 1720993972U;
	v2.f7 = 80462437U;
	v2.f8 = -587414550;
	v2.f9 = 46535;
	v2.f10 = 1601318776U;
	v2.f11 = -2108270889L;
	v2.f12 = 8922;
	v2.f13 = 139;
	v2.f14 = -60;
	r = f5(v0, (uchar)98, v2, (ulong)735341075UL, (int)1242293188, (ushort)23925);
	print("ret f5 double %g\n", r);
	}
	{
	S0 v1;
	S0 v5;
	S1 r;
	v1.f0 = 28091;
	v1.f1 = 34.500;
	v1.f2 = 552494998480030LL;
	v1.f3 = 1059445454U;
	v1.f4[0] = 127;
	v1.f4[1] = 48;
	v1.f4[2] = 225;
	v1.f4[3] = 146;
	v1.f4[4] = 67;
	v1.f4[5] = 244;
	v1.f4[6] = 165;
	v1.f4[7] = 86;
	v1.f5 = 7;
	v5.f0 = 61327;
	v5.f1 = 54.000;
	v5.f2 = -4609584411113584884LL;
	v5.f3 = 461069474U;
	v5.f4[0] = 83;
	v5.f4[1] = 4;
	v5.f4[2] = 181;
	v5.f4[3] = 102;
	v5.f4[4] = 23;
	v5.f4[5] = 200;
	v5.f4[6] = 121;
	v5.f4[7] = 42;
	v5.f5 = 219;
	r = f6((uchar)99, v1, (long)996272916L, (ushort)25797, (uchar)118, v5);
	pS1("ret f6", r);
	}
	{
	S1 v7;
	S2 r;
	v7.f0 = 61116;
	v7.f1 = 18.375;
	v7.f2 = 813425182U;
	v7.f3 = 1320381256131892LL;
	v7.f4 = -1827329408LL;
	v7.f5 = 49;
	v7.f6[0] = 98;
	v7.f6[1] = -19;
	v7.f6[2] = 68;
	v7.f6[3] = 117;
	v7.f6[4] = -38;
	v7.f7[0] = 87;
	v7.f7[1] = 8;
	v7.f7[2] = 185;
	v7.f7[3] = 106;
	v7.f7[4] = 27;
	v7.f7[5] = 204;
	v7.f7[6] = 125;
	v7.f8[0] = 46;
	v7.f8[1] = -95;
	v7.f8[2] = 16;
	v7.f8[3] = 65;
	v7.f8[4] = -114;
	v7.f8[5] = 35;
	v7.f8[6] = 84;
	v7.f9 = -20741;
	v7.f10 = 43.250;
	v7.f11 = 103;
	v7.f12 = 15896;
	v7.f13 = 201;
	r = f7((short)28816, (long)1855580737L, (uint)215049202U, (char)35, (long)1228953428L, (uint)1735905541U, (vlong)95374006LL, v7);
	pS2("ret f7", r);
	}
	{
	S1 v3;
	long r;
	v3.f0 = 23292;
	v3.f1 = -15.375;
	v3.f2 = 1046105694U;
	v3.f3 = -4610132955961214490LL;
	v3.f4 = 2060009920LL;
	v3.f5 = 113;
	v3.f6[0] = -34;
	v3.f6[1] = 83;
	v3.f6[2] = 4;
	v3.f6[3] = -53;
	v3.f6[4] = 102;
	v3.f7[0] = 151;
	v3.f7[1] = 72;
	v3.f7[2] = 249;
	v3.f7[3] = 170;
	v3.f7[4] = 91;
	v3.f7[5] = 12;
	v3.f7[6] = 189;
	v3.f8[0] = -110;
	v3.f8[1] = 31;
	v3.f8[2] = 80;
	v3.f8[3] = -1;
	v3.f8[4] = 50;
	v3.f8[5] = 99;
	v3.f8[6] = -20;
	v3.f9 = 15685;
	v3.f10 = 10.250;
	v3.f11 = 167;
	v3.f12 = 43608;
	v3.f13 = 9;
	r = f8((ushort)56528, (float)5.875, (float)6.750, v3);
	print("ret f8 long %ld\n", r);
	}
	{
	f9((char)-120, (short)23081);
	}
	vf(3, (vlong)-4610857679191377658LL, (vlong)1335288864LL, (vlong)1842246503722938LL);
	{
	S2 x, r;

	x.f0 = -1818705075L;
	x.f1 = 178173540ULL;
	x.f2 = 685127708376966LL;
	x.f3 = -10694;
	x.f4 = 1699034976089644LL;
	x.f5 = 18.000;
	x.f6 = 565450457U;
	x.f7 = 1072402570U;
	x.f8 = 1579354683;
	x.f9 = 33772;
	x.f10 = 445775261U;
	x.f11 = 952727374L;
	x.f12 = -28927;
	x.f13 = 176;
	x.f14 = 97;
	r = cb(back, x);
	pS2("ret cb", r);
	}
	exits(nil);
}
#endif
