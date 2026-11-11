#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { char f0[7]; };
typedef struct S1 S1;
struct S1 { ushort f0; short f1; uvlong f2; char f3[3]; };
typedef struct S2 S2;
struct S2 { int f0; char f1; uint f2; uchar f3; long f4; ushort f5; ushort f6; long f7; ushort f8; uint f9; float f10; uchar f11; ulong f12; uint f13; long f14; uint f15; vlong f16; float f17; short f18; };
typedef struct S3 S3;
struct S3 { double f0; long f1; vlong f2; double f3; uchar f4; short f5; };

float f0(char a0, uvlong a1, uchar a2);
uchar f1(S3 a0, S1 a1, vlong a2);
float f2(long a0, ulong a1, S0 a2, int a3, S2 a4, char a5);
ushort f3(S0 a0, uvlong a1, short a2, S1 a3, uvlong a4, ushort a5, float a6, float a7);
ulong f4(ushort a0, float a1);
uvlong f5(ushort a0, S2 a1, uchar a2, long a3);
float f6(double a0, vlong a1, vlong a2, vlong a3);
short f7(S2 a0, uint a1, float a2, uchar a3, S1 a4, S2 a5, double a6, uchar a7);
S3 f8(ulong a0, S0 a1, long a2, short a3);
S1 f9(ushort a0, uint a1, S3 a2, long a3);
void vf(int n, ...);
S2 cb(S2 (*fn)(S2, double, vlong), S2 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %d %d %d %d %d %d %d\n", w, s.f0[0], s.f0[1], s.f0[2], s.f0[3], s.f0[4], s.f0[5], s.f0[6]);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %ud %d %llud %d %d %d\n", w, s.f0, s.f1, s.f2, s.f3[0], s.f3[1], s.f3[2]);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d %d %ud %ud %ld %ud %ud %ld %ud %ud %g %ud %lud %ud %ld %ud %lld %g %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11, s.f12, s.f13, s.f14, s.f15, s.f16, s.f17, s.f18);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %g %ld %lld %g %ud %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5);
}

float
f0(char a0, uvlong a1, uchar a2)
{
	print("in f0\n");
	print("a0 char %d\n", a0);
	print("a1 uvlong %llud\n", a1);
	print("a2 uchar %ud\n", a2);
	return 17.000;
}

uchar
f1(S3 a0, S1 a1, vlong a2)
{
	print("in f1\n");
	pS3("a0", a0);
	pS1("a1", a1);
	print("a2 vlong %lld\n", a2);
	return 248;
}

float
f2(long a0, ulong a1, S0 a2, int a3, S2 a4, char a5)
{
	print("in f2\n");
	print("a0 long %ld\n", a0);
	print("a1 ulong %lud\n", a1);
	pS0("a2", a2);
	print("a3 int %d\n", a3);
	pS2("a4", a4);
	print("a5 char %d\n", a5);
	return 38.250;
}

ushort
f3(S0 a0, uvlong a1, short a2, S1 a3, uvlong a4, ushort a5, float a6, float a7)
{
	print("in f3\n");
	pS0("a0", a0);
	print("a1 uvlong %llud\n", a1);
	print("a2 short %d\n", a2);
	pS1("a3", a3);
	print("a4 uvlong %llud\n", a4);
	print("a5 ushort %ud\n", a5);
	print("a6 float %g\n", a6);
	print("a7 float %g\n", a7);
	return 48359;
}

ulong
f4(ushort a0, float a1)
{
	print("in f4\n");
	print("a0 ushort %ud\n", a0);
	print("a1 float %g\n", a1);
	return 2060857674UL;
}

uvlong
f5(ushort a0, S2 a1, uchar a2, long a3)
{
	print("in f5\n");
	print("a0 ushort %ud\n", a0);
	pS2("a1", a1);
	print("a2 uchar %ud\n", a2);
	print("a3 long %ld\n", a3);
	return 357154672460810ULL;
}

float
f6(double a0, vlong a1, vlong a2, vlong a3)
{
	print("in f6\n");
	print("a0 double %g\n", a0);
	print("a1 vlong %lld\n", a1);
	print("a2 vlong %lld\n", a2);
	print("a3 vlong %lld\n", a3);
	return 10.375;
}

short
f7(S2 a0, uint a1, float a2, uchar a3, S1 a4, S2 a5, double a6, uchar a7)
{
	print("in f7\n");
	pS2("a0", a0);
	print("a1 uint %ud\n", a1);
	print("a2 float %g\n", a2);
	print("a3 uchar %ud\n", a3);
	pS1("a4", a4);
	pS2("a5", a5);
	print("a6 double %g\n", a6);
	print("a7 uchar %ud\n", a7);
	return 15894;
}

S3
f8(ulong a0, S0 a1, long a2, short a3)
{
	S3 r;

	print("in f8\n");
	print("a0 ulong %lud\n", a0);
	pS0("a1", a1);
	print("a2 long %ld\n", a2);
	print("a3 short %d\n", a3);
	r.f0 = 53.000;
	r.f1 = 1540565801L;
	r.f2 = 2047517914LL;
	r.f3 = 56.625;
	r.f4 = 60;
	r.f5 = 4589;
	return r;
}

S1
f9(ushort a0, uint a1, S3 a2, long a3)
{
	S1 r;

	print("in f9\n");
	print("a0 ushort %ud\n", a0);
	print("a1 uint %ud\n", a1);
	pS3("a2", a2);
	print("a3 long %ld\n", a3);
	r.f0 = 14068;
	r.f1 = 12453;
	r.f2 = 252389974ULL;
	r.f3[0] = -7;
	r.f3[1] = 56;
	r.f3[2] = 105;
	return r;
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %lld\n", va_arg(ap, vlong));
	print("v1 %llud\n", va_arg(ap, uvlong));
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
	print("%s S0 %d %d %d %d %d %d %d\n", w, s.f0[0], s.f0[1], s.f0[2], s.f0[3], s.f0[4], s.f0[5], s.f0[6]);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %ud %d %llud %d %d %d\n", w, s.f0, s.f1, s.f2, s.f3[0], s.f3[1], s.f3[2]);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d %d %ud %ud %ld %ud %ud %ld %ud %ud %g %ud %lud %ud %ld %ud %lld %g %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11, s.f12, s.f13, s.f14, s.f15, s.f16, s.f17, s.f18);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %g %ld %lld %g %ud %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5);
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
	x.f5 = x.f5 + 3;
	x.f6 = x.f6 + 3;
	x.f7 = x.f7 + 3;
	x.f8 = x.f8 + 3;
	x.f9 = x.f9 + 3;
	x.f10 = x.f10 * 2;
	x.f11 = x.f11 + 3;
	x.f12 = x.f12 + 3;
	x.f13 = x.f13 + 3;
	x.f14 = x.f14 + 3;
	x.f15 = x.f15 + 3;
	x.f16 = x.f16 + 3;
	x.f17 = x.f17 * 2;
	x.f18 = x.f18 + 3;
	return x;
}

void
main(void)
{
	{
	float r;
	r = f0((char)120, (uvlong)2112651242934722ULL, (uchar)218);
	print("ret f0 float %g\n", r);
	}
	{
	S3 v0;
	S1 v1;
	uchar r;
	v0.f0 = 39.000;
	v0.f1 = 915892945L;
	v0.f2 = 1422845058LL;
	v0.f3 = 42.625;
	v0.f4 = 228;
	v0.f5 = 20885;
	v1.f0 = 29428;
	v1.f1 = -27813;
	v1.f2 = 824469078ULL;
	v1.f3[0] = 7;
	v1.f3[1] = -56;
	v1.f3[2] = 105;
	r = f1(v0, v1, (vlong)1359672520LL);
	print("ret f1 uchar %ud\n", r);
	}
	{
	S0 v2;
	S2 v4;
	float r;
	v2.f0[0] = -14;
	v2.f0[1] = 63;
	v2.f0[2] = 112;
	v2.f0[3] = -33;
	v2.f0[4] = 82;
	v2.f0[5] = 3;
	v2.f0[6] = -52;
	v4.f0 = 698124002;
	v4.f1 = -19;
	v4.f2 = 1712028228U;
	v4.f3 = 245;
	v4.f4 = -578448806L;
	v4.f5 = 59223;
	v4.f6 = 24840;
	v4.f7 = -2099305145L;
	v4.f8 = 21610;
	v4.f9 = 965725723U;
	v4.f10 = 50.500;
	v4.f11 = 125;
	v4.f12 = 339098414UL;
	v4.f13 = 846050527U;
	v4.f14 = 1353002640L;
	v4.f15 = 1859954753U;
	v4.f16 = -219423218LL;
	v4.f17 = -40.625;
	v4.f18 = 5460;
	r = f2((long)99748022L, (ulong)606700135UL, v2, (int)-1113652248, v4, (char)73);
	print("ret f2 float %g\n", r);
	}
	{
	S0 v0;
	S1 v3;
	ushort r;
	v0.f0[0] = -15;
	v0.f0[1] = 64;
	v0.f0[2] = 113;
	v0.f0[3] = -34;
	v0.f0[4] = 83;
	v0.f0[5] = 4;
	v0.f0[6] = -53;
	v3.f0 = 2019;
	v3.f1 = -404;
	v3.f2 = 1972965987880214ULL;
	v3.f3[0] = 118;
	v3.f3[1] = -39;
	v3.f3[2] = 88;
	r = f3(v0, (uvlong)360680945039596ULL, (short)872, v3, (uvlong)1374588212752274ULL, (ushort)63178, (float)48.625, (float)49.500);
	print("ret f3 ushort %ud\n", r);
	}
	{
	ulong r;
	r = f4((ushort)64114, (float)-9.625);
	print("ret f4 ulong %lud\n", r);
	}
	{
	S2 v1;
	uvlong r;
	v1.f0 = 1128563817;
	v1.f1 = -26;
	v1.f2 = 2142468043U;
	v1.f3 = 124;
	v1.f4 = -1008888621L;
	v1.f5 = 58590;
	v1.f6 = 24207;
	v1.f7 = -382261312L;
	v1.f8 = 20977;
	v1.f9 = 1396165538U;
	v1.f10 = 39.625;
	v1.f11 = 4;
	v1.f12 = 769538229UL;
	v1.f13 = 1276490342U;
	v1.f14 = 1783442455L;
	v1.f15 = 142910920U;
	v1.f16 = -4611036153444798812LL;
	v1.f17 = 46.750;
	v1.f18 = 4827;
	r = f5((ushort)1597, v1, (uchar)238, (long)-1544092063L);
	print("ret f5 uvlong %llud\n", r);
	}
	{
	float r;
	r = f6((double)-8.375, (vlong)-1987871638LL, (vlong)347341145020316LL, (vlong)854292216LL);
	print("ret f6 float %g\n", r);
	}
	{
	S2 v0;
	S1 v4;
	S2 v5;
	short r;
	v0.f0 = 791119678;
	v0.f1 = 111;
	v0.f2 = 1805023904U;
	v0.f3 = 81;
	v0.f4 = 671444482L;
	v0.f5 = 59315;
	v0.f6 = 24932;
	v0.f7 = 44817173L;
	v0.f8 = 21702;
	v0.f9 = 1058721399U;
	v0.f10 = 43.000;
	v0.f11 = 217;
	v0.f12 = 432094090UL;
	v0.f13 = 939046203U;
	v0.f14 = -1445998316L;
	v0.f15 = 1952950429U;
	v0.f16 = 312418894LL;
	v0.f17 = 50.125;
	v0.f18 = 5552;
	v4.f0 = 2322;
	v4.f1 = 707;
	v4.f2 = 1206647924ULL;
	v4.f3[0] = -37;
	v4.f3[1] = 86;
	v4.f3[2] = 7;
	v5.f0 = 1741851366;
	v5.f1 = -23;
	v5.f2 = 608271944U;
	v5.f3 = 249;
	v5.f4 = -1622176170L;
	v5.f5 = 60251;
	v5.f6 = 25868;
	v5.f7 = -995548861L;
	v5.f8 = 22638;
	v5.f9 = 2009453087U;
	v5.f10 = -14.000;
	v5.f11 = 129;
	v5.f12 = 1382825778UL;
	v5.f13 = 1889777891U;
	v5.f14 = 249246356L;
	v5.f15 = 756198469U;
	v5.f16 = -1263150582LL;
	v5.f17 = -7.125;
	v5.f18 = 6488;
	r = f7(v0, (uint)1143475386U, (float)-3.625, (uchar)28, v4, v5, (double)-1.375, (uchar)126);
	print("ret f7 short %d\n", r);
	}
	{
	S0 v1;
	S3 r;
	v1.f0[0] = 68;
	v1.f0[1] = 117;
	v1.f0[2] = -38;
	v1.f0[3] = 87;
	v1.f0[4] = 8;
	v1.f0[5] = -57;
	v1.f0[6] = 106;
	r = f8((ulong)362251672UL, v1, (long)869203785L, (short)30970);
	pS3("ret f8", r);
	}
	{
	S3 v2;
	S1 r;
	v2.f0 = 1.000;
	v2.f1 = 1819935473L;
	v2.f2 = -179403938LL;
	v2.f3 = 4.625;
	v2.f4 = 4;
	v2.f5 = -27061;
	r = f9((ushort)2836, (uint)1221559493U, v2, (long)1728511606L);
	pS1("ret f9", r);
	}
	vf(2, (vlong)1665339068LL, (uvlong)24807607422606ULL);
	{
	S2 x, r;

	x.f0 = 508223744;
	x.f1 = 49;
	x.f2 = 1522127970U;
	x.f3 = 19;
	x.f4 = 388548548L;
	x.f5 = 16757;
	x.f6 = 47910;
	x.f7 = 1909404887L;
	x.f8 = 44680;
	x.f9 = 775825465U;
	x.f10 = 1.750;
	x.f11 = 155;
	x.f12 = 149198156UL;
	x.f13 = 656150269U;
	x.f14 = -1163102382L;
	x.f15 = 1670054495U;
	x.f16 = 29522960LL;
	x.f17 = 8.875;
	x.f18 = 28530;
	r = cb(back, x);
	pS2("ret cb", r);
	}
	exits(nil);
}
#endif
