#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { ushort f0; ulong f1; vlong f2; ulong f3; vlong f4; short f5; uchar f6; uint f7; ushort f8; uchar f9; int f10; vlong f11; int f12; uvlong f13; short f14; uchar f15; char f16; };
typedef struct S1 S1;
struct S1 { short f0; char f1[8]; uvlong f2; uint f3; short f4; long f5; char f6; float f7; float f8; short f9; char f10; };
typedef struct S2 S2;
struct S2 { int f0; long f1; char f2; float f3; double f4; uchar f5; int f6; vlong f7; short f8; int f9; char f10[7]; char f11; };
typedef struct S3 S3;
struct S3 { uint f0; double f1; ushort f2; ulong f3; uchar f4; uchar f5; uchar f6[3]; short f7; uvlong f8; long f9; short f10; vlong f11; int f12; uvlong f13; ulong f14; };

float f0(int a0, ushort a1);
S0 f1(vlong a0, S3 a1);
double f2(S2 a0, S0 a1, uint a2, S1 a3, ulong a4, float a5, short a6, S0 a7);
uint f3(S1 a0, char a1, S3 a2, double a3, uint a4, uchar a5);
int f4(uvlong a0, vlong a1, uvlong a2, int a3);
long f5(ulong a0, ulong a1, S1 a2, int a3, S0 a4, uchar a5);
uchar f6(uint a0, S0 a1, uint a2, int a3, long a4, uchar a5);
long f7(char a0, uchar a1, uint a2, S3 a3);
S0 f8(float a0, uint a1, long a2);
float f9(S0 a0, S3 a1, uchar a2, S1 a3, int a4, int a5);
void vf(int n, ...);
S2 cb(S2 (*fn)(S2, double, vlong), S2 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %ud %lud %lld %lud %lld %d %ud %ud %ud %ud %d %lld %d %llud %d %ud %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11, s.f12, s.f13, s.f14, s.f15, s.f16);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %d %d %d %d %d %d %d %d %d %llud %ud %d %ld %d %g %g %d %d\n", w, s.f0, s.f1[0], s.f1[1], s.f1[2], s.f1[3], s.f1[4], s.f1[5], s.f1[6], s.f1[7], s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d %ld %d %g %g %ud %d %lld %d %d %d %d %d %d %d %d %d %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10[0], s.f10[1], s.f10[2], s.f10[3], s.f10[4], s.f10[5], s.f10[6], s.f11);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %ud %g %ud %lud %ud %ud %ud %ud %ud %d %llud %ld %d %lld %d %llud %lud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6[0], s.f6[1], s.f6[2], s.f7, s.f8, s.f9, s.f10, s.f11, s.f12, s.f13, s.f14);
}

float
f0(int a0, ushort a1)
{
	print("in f0\n");
	print("a0 int %d\n", a0);
	print("a1 ushort %ud\n", a1);
	return 19.000;
}

S0
f1(vlong a0, S3 a1)
{
	S0 r;

	print("in f1\n");
	print("a0 vlong %lld\n", a0);
	pS3("a1", a1);
	r.f0 = 51563;
	r.f1 = 232080156UL;
	r.f2 = 739034486096814LL;
	r.f3 = 1245984382UL;
	r.f4 = -4609933076673578426LL;
	r.f5 = 10720;
	r.f6 = 145;
	r.f7 = 1126309186U;
	r.f8 = 38643;
	r.f9 = 164;
	r.f10 = -499681877;
	r.f11 = 1006633990LL;
	r.f12 = 1513586103;
	r.f13 = 2020538216ULL;
	r.f14 = 28953;
	r.f15 = 202;
	r.f16 = -123;
	return r;
}

double
f2(S2 a0, S0 a1, uint a2, S1 a3, ulong a4, float a5, short a6, S0 a7)
{
	print("in f2\n");
	pS2("a0", a0);
	pS0("a1", a1);
	print("a2 uint %ud\n", a2);
	pS1("a3", a3);
	print("a4 ulong %lud\n", a4);
	print("a5 float %g\n", a5);
	print("a6 short %d\n", a6);
	pS0("a7", a7);
	return 19.875;
}

uint
f3(S1 a0, char a1, S3 a2, double a3, uint a4, uchar a5)
{
	print("in f3\n");
	pS1("a0", a0);
	print("a1 char %d\n", a1);
	pS3("a2", a2);
	print("a3 double %g\n", a3);
	print("a4 uint %ud\n", a4);
	print("a5 uchar %ud\n", a5);
	return 1578330450U;
}

int
f4(uvlong a0, vlong a1, uvlong a2, int a3)
{
	print("in f4\n");
	print("a0 uvlong %llud\n", a0);
	print("a1 vlong %lld\n", a1);
	print("a2 uvlong %llud\n", a2);
	print("a3 int %d\n", a3);
	return 1839262291;
}

long
f5(ulong a0, ulong a1, S1 a2, int a3, S0 a4, uchar a5)
{
	print("in f5\n");
	print("a0 ulong %lud\n", a0);
	print("a1 ulong %lud\n", a1);
	pS1("a2", a2);
	print("a3 int %d\n", a3);
	pS0("a4", a4);
	print("a5 uchar %ud\n", a5);
	return 1149462444L;
}

uchar
f6(uint a0, S0 a1, uint a2, int a3, long a4, uchar a5)
{
	print("in f6\n");
	print("a0 uint %ud\n", a0);
	pS0("a1", a1);
	print("a2 uint %ud\n", a2);
	print("a3 int %d\n", a3);
	print("a4 long %ld\n", a4);
	print("a5 uchar %ud\n", a5);
	return 173;
}

long
f7(char a0, uchar a1, uint a2, S3 a3)
{
	print("in f7\n");
	print("a0 char %d\n", a0);
	print("a1 uchar %ud\n", a1);
	print("a2 uint %ud\n", a2);
	pS3("a3", a3);
	return -629170571L;
}

S0
f8(float a0, uint a1, long a2)
{
	S0 r;

	print("in f8\n");
	print("a0 float %g\n", a0);
	print("a1 uint %ud\n", a1);
	print("a2 long %ld\n", a2);
	r.f0 = 24035;
	r.f1 = 185390996UL;
	r.f2 = 692345186029334LL;
	r.f3 = 1199295222UL;
	r.f4 = -4609979765973645906LL;
	r.f5 = 15960;
	r.f6 = 9;
	r.f7 = 1079620026U;
	r.f8 = 11115;
	r.f9 = 28;
	r.f10 = -452992717;
	r.f11 = 959944830LL;
	r.f12 = 1466896943;
	r.f13 = 1973849056ULL;
	r.f14 = 1425;
	r.f15 = 66;
	r.f16 = -115;
	return r;
}

float
f9(S0 a0, S3 a1, uchar a2, S1 a3, int a4, int a5)
{
	print("in f9\n");
	pS0("a0", a0);
	pS3("a1", a1);
	print("a2 uchar %ud\n", a2);
	pS1("a3", a3);
	print("a4 int %d\n", a4);
	print("a5 int %d\n", a5);
	return 20.125;
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %ud\n", va_arg(ap, uint));
	print("v1 %ud\n", va_arg(ap, uint));
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
	print("%s S0 %ud %lud %lld %lud %lld %d %ud %ud %ud %ud %d %lld %d %llud %d %ud %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11, s.f12, s.f13, s.f14, s.f15, s.f16);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %d %d %d %d %d %d %d %d %d %llud %ud %d %ld %d %g %g %d %d\n", w, s.f0, s.f1[0], s.f1[1], s.f1[2], s.f1[3], s.f1[4], s.f1[5], s.f1[6], s.f1[7], s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d %ld %d %g %g %ud %d %lld %d %d %d %d %d %d %d %d %d %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10[0], s.f10[1], s.f10[2], s.f10[3], s.f10[4], s.f10[5], s.f10[6], s.f11);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %ud %g %ud %lud %ud %ud %ud %ud %ud %d %llud %ld %d %lld %d %llud %lud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6[0], s.f6[1], s.f6[2], s.f7, s.f8, s.f9, s.f10, s.f11, s.f12, s.f13, s.f14);
}

static S2
back(S2 x, double d, vlong v)
{
	pS2("back x", x);
	print("back %g %lld\n", d, v);
	x.f0 = x.f0 + 3;
	x.f1 = x.f1 + 3;
	x.f2 = x.f2 + 3;
	x.f3 = x.f3 * 2;
	x.f4 = x.f4 * 2;
	x.f5 = x.f5 + 3;
	x.f6 = x.f6 + 3;
	x.f7 = x.f7 + 3;
	x.f8 = x.f8 + 3;
	x.f9 = x.f9 + 3;
	x.f10[0] = x.f10[0] + 3;
	x.f10[1] = x.f10[1] + 3;
	x.f10[2] = x.f10[2] + 3;
	x.f10[3] = x.f10[3] + 3;
	x.f10[4] = x.f10[4] + 3;
	x.f10[5] = x.f10[5] + 3;
	x.f10[6] = x.f10[6] + 3;
	x.f11 = x.f11 + 3;
	return x;
}

void
main(void)
{
	{
	float r;
	r = f0((int)-1355846080, (ushort)2929);
	print("ret f0 float %g\n", r);
	}
	{
	S3 v1;
	S0 r;
	v1.f0 = 1799625655U;
	v1.f1 = 41.000;
	v1.f2 = 3865;
	v1.f3 = 1172998346UL;
	v1.f4 = 123;
	v1.f5 = 44;
	v1.f6[0] = 221;
	v1.f6[1] = 142;
	v1.f6[2] = 63;
	v1.f7 = -25328;
	v1.f8 = 426697121087530ULL;
	v1.f9 = 933647954L;
	v1.f10 = -20483;
	v1.f11 = 1947552180LL;
	v1.f12 = 307020645;
	v1.f13 = 813972758ULL;
	v1.f14 = 1320924871UL;
	r = f1((vlong)1201253278749032LL, v1);
	pS0("ret f1", r);
	}
	{
	S2 v0;
	S0 v1;
	S1 v3;
	S0 v7;
	double r;
	v0.f0 = 1138077137;
	v0.f1 = 1645029250L;
	v0.f2 = -51;
	v0.f3 = 4.500;
	v0.f4 = 5.375;
	v0.f5 = 70;
	v0.f6 = 2032306167;
	v0.f7 = 391774632LL;
	v0.f8 = -31577;
	v0.f9 = 1405678858;
	v0.f10[0] = 59;
	v0.f10[1] = -108;
	v0.f10[2] = 29;
	v0.f10[3] = 78;
	v0.f10[4] = -127;
	v0.f10[5] = 48;
	v0.f10[6] = 97;
	v0.f11 = -18;
	v1.f0 = 12197;
	v1.f1 = 1046653270UL;
	v1.f2 = 1553610043816156LL;
	v1.f3 = 2060557496UL;
	v1.f4 = 420027221077890LL;
	v1.f5 = 4122;
	v1.f6 = 203;
	v1.f7 = 1940882300U;
	v1.f8 = 64813;
	v1.f9 = 222;
	v1.f10 = 1314254991;
	v1.f11 = 1821207104LL;
	v1.f12 = -180675569;
	v1.f13 = 687627682ULL;
	v1.f14 = 22355;
	v1.f15 = 4;
	v1.f16 = 53;
	v3.f0 = 12665;
	v3.f1[0] = -42;
	v3.f1[1] = 91;
	v3.f1[2] = 12;
	v3.f1[3] = -61;
	v3.f1[4] = 110;
	v3.f1[5] = 31;
	v3.f1[6] = -80;
	v3.f1[7] = 1;
	v3.f2 = 208926898ULL;
	v3.f3 = 715879011U;
	v3.f4 = 27668;
	v3.f5 = 1729783237L;
	v3.f6 = -118;
	v3.f7 = 55.125;
	v3.f8 = 56.000;
	v3.f9 = -19593;
	v3.f10 = 58;
	v7.f0 = 13133;
	v7.f1 = 1997384958UL;
	v7.f2 = -4611329163933827642LL;
	v7.f3 = 863805536UL;
	v7.f4 = 1370761761272954LL;
	v7.f5 = -5058;
	v7.f6 = 115;
	v7.f7 = 744130340U;
	v7.f8 = 213;
	v7.f9 = 134;
	v7.f10 = 117503031;
	v7.f11 = -624455144LL;
	v7.f12 = 1131407257;
	v7.f13 = 1638359370ULL;
	v7.f14 = -23291;
	v7.f15 = 172;
	v7.f16 = 93;
	r = f2(v0, v1, (uint)892056865U, v3, (ulong)1399008978UL, (float)-14.625, (short)-8756, v7);
	print("ret f2 double %g\n", r);
	}
	{
	S1 v0;
	S3 v2;
	uint r;
	v0.f0 = 12922;
	v0.f1[0] = -43;
	v0.f1[1] = 92;
	v0.f1[2] = 13;
	v0.f1[3] = -62;
	v0.f1[4] = 111;
	v0.f1[5] = 32;
	v0.f1[6] = -81;
	v0.f1[7] = 2;
	v0.f2 = 469860148576224ULL;
	v0.f3 = 976810852U;
	v0.f4 = 27925;
	v0.f5 = 1990715078L;
	v0.f6 = -119;
	v0.f7 = 39.000;
	v0.f8 = 40.875;
	v0.f9 = -19850;
	v0.f10 = 59;
	v2.f0 = 1751364686U;
	v2.f1 = 46.125;
	v2.f2 = 42928;
	v2.f3 = 1124737377UL;
	v2.f4 = 18;
	v2.f5 = 195;
	v2.f6[0] = 116;
	v2.f6[1] = 37;
	v2.f6[2] = 214;
	v2.f7 = 31623;
	v2.f8 = 378434872ULL;
	v2.f9 = -885386985L;
	v2.f10 = 26778;
	v2.f11 = 1899296908873640LL;
	v2.f12 = -258759676;
	v2.f13 = 765714086135374ULL;
	v2.f14 = 1272663902UL;
	r = f3(v0, (char)-34, v2, (double)-31.625, (uint)19409284U, (uchar)53);
	print("ret f3 uint %ud\n", r);
	}
	{
	int r;
	r = f4((uvlong)463190248566584ULL, (vlong)-970140972LL, (uvlong)1477097516279262ULL, (int)1984045198);
	print("ret f4 int %d\n", r);
	}
	{
	S1 v2;
	S0 v4;
	long r;
	v2.f0 = 12500;
	v2.f1[0] = 5;
	v2.f1[1] = -54;
	v2.f1[2] = 103;
	v2.f1[3] = 24;
	v2.f1[4] = -73;
	v2.f1[5] = 122;
	v2.f1[6] = 43;
	v2.f1[7] = -92;
	v2.f2 = 40990855972206ULL;
	v2.f3 = 547942846U;
	v2.f4 = -27503;
	v2.f5 = 1561847072L;
	v2.f6 = 81;
	v2.f7 = -33.750;
	v2.f8 = -32.625;
	v2.f9 = 19428;
	v2.f10 = -21;
	v4.f0 = 45736;
	v4.f1 = 1829448793UL;
	v4.f2 = 188917258LL;
	v4.f3 = 695869371UL;
	v4.f4 = 1202821484LL;
	v4.f5 = 4893;
	v4.f6 = 206;
	v4.f7 = 576194175U;
	v4.f8 = 32816;
	v4.f9 = 225;
	v4.f10 = 2097050514;
	v4.f11 = 456520348556944LL;
	v4.f12 = -963471092;
	v4.f13 = 1470427616269622ULL;
	v4.f14 = 23126;
	v4.f15 = 7;
	v4.f16 = 56;
	r = f5((ulong)724120700UL, (ulong)1231072813UL, v2, (int)1738024926, v4, (uchar)143);
	print("ret f5 long %ld\n", r);
	}
	{
	S0 v1;
	uchar r;
	v1.f0 = 45525;
	v1.f1 = 541272966UL;
	v1.f2 = -4610637790203712674LL;
	v1.f3 = 1555177192UL;
	v1.f4 = 2062135491387922LL;
	v1.f5 = -4682;
	v1.f6 = 251;
	v1.f7 = 1435501996U;
	v1.f8 = 32605;
	v1.f9 = 14;
	v1.f10 = 808874687;
	v1.f11 = -1315826800LL;
	v1.f12 = 1822778913;
	v1.f13 = 182247378ULL;
	v1.f14 = -22915;
	v1.f15 = 52;
	v1.f16 = 101;
	r = f6((uint)1583428521U, v1, (uint)2090380634U, (int)449849099, (long)-956801212L, (uchar)109);
	print("ret f6 uchar %ud\n", r);
	}
	{
	S3 v3;
	long r;
	v3.f0 = 1400580787U;
	v3.f1 = 0.500;
	v3.f2 = 7701;
	v3.f3 = 773953478UL;
	v3.f4 = 119;
	v3.f5 = 40;
	v3.f6[0] = 217;
	v3.f6[1] = 138;
	v3.f6[2] = 59;
	v3.f7 = -29164;
	v3.f8 = 27651055952926ULL;
	v3.f9 = 534603086L;
	v3.f10 = -24319;
	v3.f11 = 1548507312LL;
	v3.f12 = 2055459425;
	v3.f13 = 414927890ULL;
	v3.f14 = 921880003UL;
	r = f7((char)7, (uchar)56, (uint)1816109033U, v3);
	print("ret f7 long %ld\n", r);
	}
	{
	S0 r;
	r = f8((float)-38.125, (uint)112404960U, (long)619357073L);
	pS0("ret f8", r);
	}
	{
	S0 v0;
	S3 v1;
	S1 v3;
	float r;
	v0.f0 = 46039;
	v0.f1 = 1063136648UL;
	v0.f2 = -4610115924956121628LL;
	v0.f3 = 2077040874UL;
	v0.f4 = 436510648528024LL;
	v0.f5 = -5196;
	v0.f6 = 253;
	v0.f7 = 1957365678U;
	v0.f8 = 33119;
	v0.f9 = 16;
	v0.f10 = 1330738369;
	v0.f11 = -1837690482LL;
	v0.f12 = 197158947;
	v0.f13 = 704111060ULL;
	v0.f14 = -23429;
	v0.f15 = 54;
	v0.f16 = 103;
	v1.f0 = 2105292203U;
	v1.f1 = 23.500;
	v1.f2 = 10509;
	v1.f3 = 1478664894UL;
	v1.f4 = 111;
	v1.f5 = 32;
	v1.f6[0] = 209;
	v1.f6[1] = 130;
	v1.f6[2] = 51;
	v1.f7 = -31972;
	v1.f8 = 732364586087174ULL;
	v1.f9 = 1239314502L;
	v1.f10 = -27127;
	v1.f11 = 105735080LL;
	v1.f12 = 612687193;
	v1.f13 = 1119639306ULL;
	v1.f14 = 1626591419UL;
	v3.f0 = 14207;
	v3.f1[0] = -48;
	v3.f1[1] = 97;
	v3.f1[2] = 18;
	v3.f1[3] = -67;
	v3.f1[4] = 116;
	v3.f1[5] = 37;
	v3.f1[6] = -86;
	v3.f1[7] = 7;
	v3.f2 = 1774517944ULL;
	v3.f3 = 133986409U;
	v3.f4 = 29210;
	v3.f5 = 1147890635L;
	v3.f6 = -124;
	v3.f7 = 56.375;
	v3.f8 = -40.250;
	v3.f9 = -21135;
	v3.f10 = 64;
	r = f9(v0, v1, (uchar)83, v3, (int)1415492356, (int)-1922444469);
	print("ret f9 float %g\n", r);
	}
	vf(3, (uint)1859271931U, (uint)218740396U, (vlong)725694686077534LL);
	{
	S2 x, r;

	x.f0 = 702156607;
	x.f1 = -1209108720L;
	x.f2 = 33;
	x.f3 = 35.750;
	x.f4 = 36.625;
	x.f5 = 180;
	x.f6 = 1596385637;
	x.f7 = -2103337750LL;
	x.f8 = 23751;
	x.f9 = 969758328;
	x.f10[0] = -41;
	x.f10[1] = 90;
	x.f10[2] = 11;
	x.f10[3] = -60;
	x.f10[4] = 109;
	x.f10[5] = 30;
	x.f10[6] = -79;
	x.f11 = 0;
	r = cb(back, x);
	pS2("ret cb", r);
	}
	exits(nil);
}
#endif
