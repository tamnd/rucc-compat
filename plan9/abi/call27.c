#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { long f0; ulong f1; long f2; long f3; uint f4; short f5; char f6[5]; double f7; short f8; float f9; long f10; uchar f11[7]; uchar f12; short f13; float f14; ulong f15; };
typedef struct S1 S1;
struct S1 { float f0; long f1; vlong f2; ulong f3; double f4; float f5; uchar f6[4]; ulong f7; };
typedef struct S2 S2;
struct S2 { float f0; uvlong f1; char f2; float f3; uint f4; short f5; int f6; uint f7; };
typedef struct S3 S3;
struct S3 { ulong f0; uint f1; short f2; uvlong f3; uchar f4[3]; uint f5; short f6; char f7[3]; ushort f8; };

uint f0(uint a0);
S3 f1(short a0, ushort a1, float a2, uvlong a3, uchar a4, S0 a5);
S3 f2(ulong a0, S3 a1, ushort a2, ulong a3, float a4, S1 a5);
ulong f3(short a0, vlong a1);
long f4(ulong a0, ulong a1, uchar a2, short a3);
vlong f5(vlong a0, vlong a1, int a2, short a3);
S0 f6(float a0, uint a1, uint a2);
void f7(float a0, char a1, uvlong a2, S3 a3);
ushort f8(uchar a0, S1 a1);
float f9(ushort a0, short a1, int a2);
void vf(int n, ...);
S0 cb(S0 (*fn)(S0, double, vlong), S0 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %ld %lud %ld %ld %ud %d %d %d %d %d %d %g %d %g %ld %ud %ud %ud %ud %ud %ud %ud %ud %d %g %lud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6[0], s.f6[1], s.f6[2], s.f6[3], s.f6[4], s.f7, s.f8, s.f9, s.f10, s.f11[0], s.f11[1], s.f11[2], s.f11[3], s.f11[4], s.f11[5], s.f11[6], s.f12, s.f13, s.f14, s.f15);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %g %ld %lld %lud %g %g %ud %ud %ud %ud %lud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6[0], s.f6[1], s.f6[2], s.f6[3], s.f7);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %g %llud %d %g %ud %d %d %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %lud %ud %d %llud %ud %ud %ud %ud %d %d %d %d %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4[0], s.f4[1], s.f4[2], s.f5, s.f6, s.f7[0], s.f7[1], s.f7[2], s.f8);
}

uint
f0(uint a0)
{
	print("in f0\n");
	print("a0 uint %ud\n", a0);
	return 1022352080U;
}

S3
f1(short a0, ushort a1, float a2, uvlong a3, uchar a4, S0 a5)
{
	S3 r;

	print("in f1\n");
	print("a0 short %d\n", a0);
	print("a1 ushort %ud\n", a1);
	print("a2 float %g\n", a2);
	print("a3 uvlong %llud\n", a3);
	print("a4 uchar %ud\n", a4);
	pS0("a5", a5);
	r.f0 = 1803575794UL;
	r.f1 = 163044259U;
	r.f2 = -21844;
	r.f3 = 1176952015845462ULL;
	r.f4[0] = 182;
	r.f4[1] = 103;
	r.f4[2] = 24;
	r.f5 = 1057273289U;
	r.f6 = -12154;
	r.f7[0] = 43;
	r.f7[1] = 92;
	r.f7[2] = -13;
	r.f8 = 5694;
	return r;
}

S3
f2(ulong a0, S3 a1, ushort a2, ulong a3, float a4, S1 a5)
{
	S3 r;

	print("in f2\n");
	print("a0 ulong %lud\n", a0);
	pS3("a1", a1);
	print("a2 ushort %ud\n", a2);
	print("a3 ulong %lud\n", a3);
	print("a4 float %g\n", a4);
	pS1("a5", a5);
	r = a1;
	r.f0 = r.f0 + 3;
	r.f1 = r.f1 + 3;
	r.f2 = r.f2 + 3;
	r.f3 = r.f3 + 3;
	r.f4[0] = r.f4[0] + 3;
	r.f4[1] = r.f4[1] + 3;
	r.f4[2] = r.f4[2] + 3;
	r.f5 = r.f5 + 3;
	r.f6 = r.f6 + 3;
	r.f7[0] = r.f7[0] + 3;
	r.f7[1] = r.f7[1] + 3;
	r.f7[2] = r.f7[2] + 3;
	r.f8 = r.f8 + 3;
	return r;
}

ulong
f3(short a0, vlong a1)
{
	print("in f3\n");
	print("a0 short %d\n", a0);
	print("a1 vlong %lld\n", a1);
	return 438887669UL;
}

long
f4(ulong a0, ulong a1, uchar a2, short a3)
{
	print("in f4\n");
	print("a0 ulong %lud\n", a0);
	print("a1 ulong %lud\n", a1);
	print("a2 uchar %ud\n", a2);
	print("a3 short %d\n", a3);
	return 882667244L;
}

vlong
f5(vlong a0, vlong a1, int a2, short a3)
{
	print("in f5\n");
	print("a0 vlong %lld\n", a0);
	print("a1 vlong %lld\n", a1);
	print("a2 int %d\n", a2);
	print("a3 short %d\n", a3);
	return -4611493150451785720LL;
}

S0
f6(float a0, uint a1, uint a2)
{
	S0 r;

	print("in f6\n");
	print("a0 float %g\n", a0);
	print("a1 uint %ud\n", a1);
	print("a2 uint %ud\n", a2);
	r.f0 = 347463802L;
	r.f1 = 854415915UL;
	r.f2 = -1361368028L;
	r.f3 = 1868320141L;
	r.f4 = 227788606U;
	r.f5 = -16623;
	r.f6[0] = 32;
	r.f6[1] = 81;
	r.f6[2] = -2;
	r.f6[3] = 51;
	r.f6[4] = 100;
	r.f7 = 31.375;
	r.f8 = 5318;
	r.f9 = 33.125;
	r.f10 = -1002342440L;
	r.f11[0] = 217;
	r.f11[1] = 138;
	r.f11[2] = 59;
	r.f11[3] = 236;
	r.f11[4] = 157;
	r.f11[5] = 78;
	r.f11[6] = 255;
	r.f12 = 176;
	r.f13 = -20321;
	r.f14 = 44.750;
	r.f15 = 136364739UL;
	return r;
}

void
f7(float a0, char a1, uvlong a2, S3 a3)
{
	print("in f7\n");
	print("a0 float %g\n", a0);
	print("a1 char %d\n", a1);
	print("a2 uvlong %llud\n", a2);
	pS3("a3", a3);
}

ushort
f8(uchar a0, S1 a1)
{
	print("in f8\n");
	print("a0 uchar %ud\n", a0);
	pS1("a1", a1);
	return 62146;
}

float
f9(ushort a0, short a1, int a2)
{
	print("in f9\n");
	print("a0 ushort %ud\n", a0);
	print("a1 short %d\n", a1);
	print("a2 int %d\n", a2);
	return -13.500;
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %lud\n", va_arg(ap, ulong));
	print("v1 %ud\n", va_arg(ap, uint));
	print("v2 %lld\n", va_arg(ap, vlong));
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
	print("%s S0 %ld %lud %ld %ld %ud %d %d %d %d %d %d %g %d %g %ld %ud %ud %ud %ud %ud %ud %ud %ud %d %g %lud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6[0], s.f6[1], s.f6[2], s.f6[3], s.f6[4], s.f7, s.f8, s.f9, s.f10, s.f11[0], s.f11[1], s.f11[2], s.f11[3], s.f11[4], s.f11[5], s.f11[6], s.f12, s.f13, s.f14, s.f15);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %g %ld %lld %lud %g %g %ud %ud %ud %ud %lud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6[0], s.f6[1], s.f6[2], s.f6[3], s.f7);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %g %llud %d %g %ud %d %d %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %lud %ud %d %llud %ud %ud %ud %ud %d %d %d %d %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4[0], s.f4[1], s.f4[2], s.f5, s.f6, s.f7[0], s.f7[1], s.f7[2], s.f8);
}

static S0
back(S0 x, double d, vlong v)
{
	pS0("back x", x);
	print("back %g %lld\n", d, v);
	x.f0 = x.f0 + 3;
	x.f1 = x.f1 + 3;
	x.f2 = x.f2 + 3;
	x.f3 = x.f3 + 3;
	x.f4 = x.f4 + 3;
	x.f5 = x.f5 + 3;
	x.f6[0] = x.f6[0] + 3;
	x.f6[1] = x.f6[1] + 3;
	x.f6[2] = x.f6[2] + 3;
	x.f6[3] = x.f6[3] + 3;
	x.f6[4] = x.f6[4] + 3;
	x.f7 = x.f7 * 2;
	x.f8 = x.f8 + 3;
	x.f9 = x.f9 * 2;
	x.f10 = x.f10 + 3;
	x.f11[0] = x.f11[0] + 3;
	x.f11[1] = x.f11[1] + 3;
	x.f11[2] = x.f11[2] + 3;
	x.f11[3] = x.f11[3] + 3;
	x.f11[4] = x.f11[4] + 3;
	x.f11[5] = x.f11[5] + 3;
	x.f11[6] = x.f11[6] + 3;
	x.f12 = x.f12 + 3;
	x.f13 = x.f13 + 3;
	x.f14 = x.f14 * 2;
	x.f15 = x.f15 + 3;
	return x;
}

void
main(void)
{
	{
	uint r;
	r = f0((uint)1793762296U);
	print("ret f0 uint %ud\n", r);
	}
	{
	S0 v5;
	S3 r;
	v5.f0 = 1730589758L;
	v5.f1 = 90058223UL;
	v5.f2 = 597010336L;
	v5.f3 = 1103962449L;
	v5.f4 = 1610914562U;
	v5.f5 = 5299;
	v5.f6[0] = 100;
	v5.f6[1] = -21;
	v5.f6[2] = 70;
	v5.f6[3] = 119;
	v5.f6[4] = -40;
	v5.f7 = 43.875;
	v5.f8 = 26762;
	v5.f9 = 45.625;
	v5.f10 = 237984748L;
	v5.f11[0] = 157;
	v5.f11[1] = 78;
	v5.f11[2] = 255;
	v5.f11[3] = 176;
	v5.f11[4] = 97;
	v5.f11[5] = 18;
	v5.f11[6] = 195;
	v5.f12 = 116;
	v5.f13 = 8997;
	v5.f14 = 56.250;
	v5.f15 = 1519490695UL;
	r = f1((short)13842, (ushort)44995, (float)54.500, (uvlong)505587985759414ULL, (uchar)214, v5);
	pS3("ret f1", r);
	}
	{
	S3 v1;
	S1 v5;
	S3 r;
	v1.f0 = 949366044UL;
	v1.f1 = 1456318157U;
	v1.f2 = -8318;
	v1.f3 = 322739703216212ULL;
	v1.f4[0] = 224;
	v1.f4[1] = 145;
	v1.f4[2] = 66;
	v1.f5 = 203063539U;
	v1.f6 = -31396;
	v1.f7[0] = 85;
	v1.f7[1] = 6;
	v1.f7[2] = -55;
	v1.f8 = 57704;
	v5.f0 = 17.000;
	v5.f1 = 857942177L;
	v5.f2 = 1364894290LL;
	v5.f3 = 1871846403UL;
	v5.f4 = 21.500;
	v5.f5 = 22.375;
	v5.f6[0] = 22;
	v5.f6[1] = 199;
	v5.f6[2] = 120;
	v5.f6[3] = 41;
	v5.f7 = 1125543898UL;
	r = f2((ulong)1900097732UL, v1, (ushort)43637, (ulong)766518310UL, (float)40.125, v5);
	pS3("ret f2", r);
	}
	{
	ulong r;
	r = f3((short)11805, (vlong)1717249998LL);
	print("ret f3 ulong %lud\n", r);
	}
	{
	long r;
	r = f4((ulong)1654077460UL, (ulong)13545925UL, (uchar)118, (short)9511);
	print("ret f4 long %ld\n", r);
	}
	{
	vlong r;
	r = f5((vlong)-4610721737921555072LL, (vlong)1471229726LL, (int)1978181839, (short)-8832);
	print("ret f5 vlong %lld\n", r);
	}
	{
	S0 r;
	r = f6((float)5.250, (uint)781429879U, (uint)1288381992U);
	pS0("ret f6", r);
	}
	{
	S3 v3;
	v3.f0 = 1225209454UL;
	v3.f1 = 1732161567U;
	v3.f2 = 10704;
	v3.f3 = 598583940746442ULL;
	v3.f4[0] = 50;
	v3.f4[1] = 227;
	v3.f4[2] = 148;
	v3.f5 = 478906949U;
	v3.f6 = 1014;
	v3.f7[0] = -39;
	v3.f7[1] = 88;
	v3.f7[2] = 9;
	v3.f8 = 60090;
	f7((float)-32.750, (char)-115, (uvlong)1640737700ULL, v3);
	}
	{
	S1 v1;
	ushort r;
	v1.f0 = 8.750;
	v1.f1 = 2084517275L;
	v1.f2 = 443985740LL;
	v1.f3 = 950937853UL;
	v1.f4 = 12.250;
	v1.f5 = 13.125;
	v1.f6[0] = 16;
	v1.f6[1] = 193;
	v1.f6[2] = 114;
	v1.f6[3] = 35;
	v1.f7 = 204635348UL;
	r = f8((uchar)190, v1);
	print("ret f8 ushort %ud\n", r);
	}
	{
	float r;
	r = f9((ushort)19972, (short)18357, (int)-1929920870);
	print("ret f9 float %g\n", r);
	}
	vf(3, (ulong)1866748332UL, (uint)226216797U, (vlong)733168910LL);
	{
	S0 x, r;

	x.f0 = 709633008L;
	x.f1 = 1216585121UL;
	x.f2 = 1723537234L;
	x.f3 = 83005699L;
	x.f4 = 589957812U;
	x.f5 = 1125;
	x.f6[0] = 22;
	x.f6[1] = -71;
	x.f6[2] = 120;
	x.f6[3] = 41;
	x.f6[4] = -90;
	x.f7 = 47.625;
	x.f8 = 22588;
	x.f9 = 49.375;
	x.f10 = 1364511646L;
	x.f11[0] = 79;
	x.f11[1] = 0;
	x.f11[2] = 177;
	x.f11[3] = 98;
	x.f11[4] = 19;
	x.f11[5] = 196;
	x.f11[6] = 117;
	x.f12 = 38;
	x.f13 = 4823;
	x.f14 = -37.000;
	x.f15 = 498533945UL;
	r = cb(back, x);
	pS0("ret cb", r);
	}
	exits(nil);
}
#endif
