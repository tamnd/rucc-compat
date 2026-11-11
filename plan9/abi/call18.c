#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { ushort f0; short f1; uint f2; uvlong f3; double f4; uint f5; int f6; short f7; short f8; uint f9; };
typedef struct S1 S1;
struct S1 { uint f0; char f1; ulong f2; long f3; char f4[3]; vlong f5; };
typedef struct S2 S2;
struct S2 { uint f0; int f1; };
typedef struct S3 S3;
struct S3 { double f0; double f1; ulong f2; long f3; char f4[6]; short f5; };

int f0(long a0, uint a1, uvlong a2, vlong a3, double a4, float a5);
char f1(ulong a0, ushort a1, double a2, ulong a3, S1 a4, float a5, ushort a6, S1 a7);
double f2(S2 a0, S1 a1, uchar a2, uvlong a3, int a4, ulong a5);
short f3(vlong a0, long a1, double a2);
ushort f4(float a0, vlong a1, float a2, uvlong a3, S2 a4, S3 a5);
S1 f5(S3 a0, S1 a1, long a2, long a3, uint a4, S3 a5, S1 a6, uint a7);
S3 f6(float a0, ulong a1, ulong a2);
ushort f7(ushort a0, S2 a1, int a2, uint a3, uchar a4, S0 a5, S1 a6, S1 a7);
ushort f8(S0 a0, S3 a1, uint a2);
S0 f9(ulong a0, uchar a1, ulong a2, uchar a3, short a4, int a5, vlong a6, S2 a7);
void vf(int n, ...);
S3 cb(S3 (*fn)(S3, double, vlong), S3 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %ud %d %ud %llud %g %ud %d %d %d %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %ud %d %lud %ld %d %d %d %lld\n", w, s.f0, s.f1, s.f2, s.f3, s.f4[0], s.f4[1], s.f4[2], s.f5);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %ud %d\n", w, s.f0, s.f1);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %g %g %lud %ld %d %d %d %d %d %d %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4[0], s.f4[1], s.f4[2], s.f4[3], s.f4[4], s.f4[5], s.f5);
}

int
f0(long a0, uint a1, uvlong a2, vlong a3, double a4, float a5)
{
	print("in f0\n");
	print("a0 long %ld\n", a0);
	print("a1 uint %ud\n", a1);
	print("a2 uvlong %llud\n", a2);
	print("a3 vlong %lld\n", a3);
	print("a4 double %g\n", a4);
	print("a5 float %g\n", a5);
	return -1856087080;
}

char
f1(ulong a0, ushort a1, double a2, ulong a3, S1 a4, float a5, ushort a6, S1 a7)
{
	print("in f1\n");
	print("a0 ulong %lud\n", a0);
	print("a1 ushort %ud\n", a1);
	print("a2 double %g\n", a2);
	print("a3 ulong %lud\n", a3);
	pS1("a4", a4);
	print("a5 float %g\n", a5);
	print("a6 ushort %ud\n", a6);
	pS1("a7", a7);
	return 99;
}

double
f2(S2 a0, S1 a1, uchar a2, uvlong a3, int a4, ulong a5)
{
	print("in f2\n");
	pS2("a0", a0);
	pS1("a1", a1);
	print("a2 uchar %ud\n", a2);
	print("a3 uvlong %llud\n", a3);
	print("a4 int %d\n", a4);
	print("a5 ulong %lud\n", a5);
	return -35.250;
}

short
f3(vlong a0, long a1, double a2)
{
	print("in f3\n");
	print("a0 vlong %lld\n", a0);
	print("a1 long %ld\n", a1);
	print("a2 double %g\n", a2);
	return -2631;
}

ushort
f4(float a0, vlong a1, float a2, uvlong a3, S2 a4, S3 a5)
{
	print("in f4\n");
	print("a0 float %g\n", a0);
	print("a1 vlong %lld\n", a1);
	print("a2 float %g\n", a2);
	print("a3 uvlong %llud\n", a3);
	pS2("a4", a4);
	pS3("a5", a5);
	return 3567;
}

S1
f5(S3 a0, S1 a1, long a2, long a3, uint a4, S3 a5, S1 a6, uint a7)
{
	S1 r;

	print("in f5\n");
	pS3("a0", a0);
	pS1("a1", a1);
	print("a2 long %ld\n", a2);
	print("a3 long %ld\n", a3);
	print("a4 uint %ud\n", a4);
	pS3("a5", a5);
	pS1("a6", a6);
	print("a7 uint %ud\n", a7);
	r = a1;
	r.f0 = r.f0 + 3;
	r.f1 = r.f1 + 3;
	r.f2 = r.f2 + 3;
	r.f3 = r.f3 + 3;
	r.f4[0] = r.f4[0] + 3;
	r.f4[1] = r.f4[1] + 3;
	r.f4[2] = r.f4[2] + 3;
	r.f5 = r.f5 + 3;
	return r;
}

S3
f6(float a0, ulong a1, ulong a2)
{
	S3 r;

	print("in f6\n");
	print("a0 float %g\n", a0);
	print("a1 ulong %lud\n", a1);
	print("a2 ulong %lud\n", a2);
	r.f0 = -6.375;
	r.f1 = -5.250;
	r.f2 = 1555135959UL;
	r.f3 = 2062088072L;
	r.f4[0] = 57;
	r.f4[1] = -106;
	r.f4[2] = 27;
	r.f4[3] = 76;
	r.f4[4] = -125;
	r.f4[5] = 46;
	r.f5 = 19295;
	return r;
}

ushort
f7(ushort a0, S2 a1, int a2, uint a3, uchar a4, S0 a5, S1 a6, S1 a7)
{
	print("in f7\n");
	print("a0 ushort %ud\n", a0);
	pS2("a1", a1);
	print("a2 int %d\n", a2);
	print("a3 uint %ud\n", a3);
	print("a4 uchar %ud\n", a4);
	pS0("a5", a5);
	pS1("a6", a6);
	pS1("a7", a7);
	return 5953;
}

ushort
f8(S0 a0, S3 a1, uint a2)
{
	print("in f8\n");
	pS0("a0", a0);
	pS3("a1", a1);
	print("a2 uint %ud\n", a2);
	return 39914;
}

S0
f9(ulong a0, uchar a1, ulong a2, uchar a3, short a4, int a5, vlong a6, S2 a7)
{
	S0 r;

	print("in f9\n");
	print("a0 ulong %lud\n", a0);
	print("a1 uchar %ud\n", a1);
	print("a2 ulong %lud\n", a2);
	print("a3 uchar %ud\n", a3);
	print("a4 short %d\n", a4);
	print("a5 int %d\n", a5);
	print("a6 vlong %lld\n", a6);
	pS2("a7", a7);
	r.f0 = 9908;
	r.f1 = 8293;
	r.f2 = 310123030U;
	r.f3 = 817077594225436ULL;
	r.f4 = 43.000;
	r.f5 = 1830979369U;
	r.f6 = -190447834;
	r.f7 = 31371;
	r.f8 = 29756;
	r.f9 = 1711304173U;
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
	print("%s S0 %ud %d %ud %llud %g %ud %d %d %d %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %ud %d %lud %ld %d %d %d %lld\n", w, s.f0, s.f1, s.f2, s.f3, s.f4[0], s.f4[1], s.f4[2], s.f5);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %ud %d\n", w, s.f0, s.f1);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %g %g %lud %ld %d %d %d %d %d %d %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4[0], s.f4[1], s.f4[2], s.f4[3], s.f4[4], s.f4[5], s.f5);
}

static S3
back(S3 x, double d, vlong v)
{
	pS3("back x", x);
	print("back %g %lld\n", d, v);
	x.f0 = x.f0 * 2;
	x.f1 = x.f1 * 2;
	x.f2 = x.f2 + 3;
	x.f3 = x.f3 + 3;
	x.f4[0] = x.f4[0] + 3;
	x.f4[1] = x.f4[1] + 3;
	x.f4[2] = x.f4[2] + 3;
	x.f4[3] = x.f4[3] + 3;
	x.f4[4] = x.f4[4] + 3;
	x.f4[5] = x.f4[5] + 3;
	x.f5 = x.f5 + 3;
	return x;
}

void
main(void)
{
	{
	int r;
	r = f0((long)-480013648L, (uint)986965761U, (uvlong)1493917874ULL, (vlong)-4609685142437777950LL, (double)19.500, (float)20.375);
	print("ret f0 int %d\n", r);
	}
	{
	S1 v4;
	S1 v7;
	char r;
	v4.f0 = 804118027U;
	v4.f1 = 60;
	v4.f2 = 1818022253UL;
	v4.f3 = 177490718L;
	v4.f4[0] = 79;
	v4.f4[1] = 0;
	v4.f4[2] = 49;
	v4.f5 = 57815522LL;
	v7.f0 = 205742047U;
	v7.f1 = 16;
	v7.f2 = 1219646273UL;
	v7.f3 = -1726598386L;
	v7.f4[0] = 35;
	v7.f4[1] = 84;
	v7.f4[2] = -5;
	v7.f5 = 1606923190LL;
	r = f1((ulong)1754849715UL, (ushort)23396, (double)3.375, (ulong)1128222406UL, v4, (float)5.125, (ushort)16936, v7);
	print("ret f1 char %d\n", r);
	}
	{
	S2 v0;
	S1 v1;
	double r;
	v0.f0 = 2078954094U;
	v0.f1 = 438422559;
	v1.f0 = 1480578114U;
	v1.f1 = -115;
	v1.f2 = 346998692UL;
	v1.f3 = 853950805L;
	v1.f4[0] = -6;
	v1.f4[1] = 55;
	v1.f4[2] = 104;
	v1.f5 = -4610951740615561084LL;
	r = f2(v0, v1, (uchar)22, (uvlong)1389158414462748ULL, (int)-1896106360, (ulong)255574825UL);
	print("ret f2 double %g\n", r);
	}
	{
	short r;
	r = f3((vlong)-4611493615563181050LL, (long)699354400L, (double)30.875);
	print("ret f3 short %d\n", r);
	}
	{
	S2 v4;
	S3 v5;
	ushort r;
	v4.f0 = 1143133975U;
	v4.f1 = 1650086088;
	v5.f0 = -9.625;
	v5.f1 = -8.500;
	v5.f2 = 1558662221UL;
	v5.f3 = -2065614334L;
	v5.f4[0] = 47;
	v5.f4[1] = 96;
	v5.f4[2] = -17;
	v5.f4[3] = 66;
	v5.f4[4] = 115;
	v5.f4[5] = -36;
	v5.f5 = 6613;
	r = f4((float)11.125, (vlong)-453334128LL, (float)13.875, (uvlong)1467238354ULL, v4, v5);
	print("ret f4 ushort %ud\n", r);
	}
	{
	S3 v0;
	S1 v1;
	S3 v5;
	S1 v6;
	S1 r;
	v0.f0 = 52.000;
	v0.f1 = 53.875;
	v0.f2 = 270486394UL;
	v0.f3 = 777438507L;
	v0.f4[0] = 92;
	v0.f4[1] = -13;
	v0.f4[2] = 62;
	v0.f4[3] = 111;
	v0.f4[4] = -32;
	v0.f4[5] = 81;
	v0.f5 = 6402;
	v1.f0 = 805689836U;
	v1.f1 = 29;
	v1.f2 = 1819594062UL;
	v1.f3 = -179062527L;
	v1.f4[0] = 48;
	v1.f4[1] = 97;
	v1.f4[2] = -18;
	v1.f5 = 59387509162000LL;
	v5.f0 = -5.000;
	v5.f1 = -4.875;
	v5.f2 = 1221218082UL;
	v5.f3 = 1728170195L;
	v5.f4[0] = -4;
	v5.f4[1] = 53;
	v5.f4[2] = 102;
	v5.f4[3] = -23;
	v5.f4[4] = 72;
	v5.f4[5] = 121;
	v5.f5 = -7338;
	v6.f0 = 1756421524U;
	v6.f1 = 69;
	v6.f2 = 622842102UL;
	v6.f3 = 1129794215L;
	v6.f4[0] = 88;
	v6.f4[1] = -9;
	v6.f4[2] = 58;
	v6.f5 = 1010122049357064LL;
	r = f5(v0, v1, (long)-1158045544L, (long)1664997657L, (uint)24466122U, v5, v6, (uint)531418235U);
	pS1("ret f5", r);
	}
	{
	S3 r;
	r = f6((float)-21.875, (ulong)975197810UL, (ulong)1482149923UL);
	pS3("ret f6", r);
	}
	{
	S2 v1;
	S0 v5;
	S1 v6;
	S1 v7;
	ushort r;
	v1.f0 = 1418977385U;
	v1.f1 = 1925929498;
	v5.f0 = 25149;
	v5.f1 = -23534;
	v5.f2 = 1834505631U;
	v5.f3 = 193974096ULL;
	v5.f4 = 43.875;
	v5.f5 = 1207878322U;
	v5.f6 = 1714830435;
	v5.f7 = -13844;
	v5.f8 = 12229;
	v5.f9 = 1088203126U;
	v6.f0 = 222225425U;
	v6.f1 = 66;
	v6.f2 = 1236129651UL;
	v6.f3 = 1743081764L;
	v6.f4[0] = 85;
	v6.f4[1] = -6;
	v6.f4[2] = 55;
	v6.f5 = 1623406568LL;
	v7.f0 = 1771333093U;
	v7.f1 = 22;
	v7.f2 = 637753671UL;
	v7.f3 = -1144705784L;
	v7.f4[0] = 41;
	v7.f4[1] = 90;
	v7.f4[2] = -11;
	v7.f5 = 1025030588LL;
	r = f7((ushort)59321, v1, (int)-1679909226, (uint)39377691U, (uchar)204, v5, v6, v7);
	print("ret f7 ushort %ud\n", r);
	}
	{
	S0 v0;
	S3 v1;
	ushort r;
	v0.f0 = 25874;
	v0.f1 = 24259;
	v0.f2 = 1497061492U;
	v0.f3 = 2004019617040822ULL;
	v0.f4 = 47.250;
	v0.f5 = 870434183U;
	v0.f6 = 1377386296;
	v0.f7 = 14569;
	v0.f8 = -12954;
	v0.f9 = 750758987U;
	v1.f0 = -34.250;
	v1.f1 = -33.125;
	v1.f2 = 898685512UL;
	v1.f3 = -1405637625L;
	v1.f4[0] = 42;
	v1.f4[1] = 91;
	v1.f4[2] = -12;
	v1.f4[3] = 61;
	v1.f4[4] = 110;
	v1.f4[5] = -31;
	v1.f5 = 10192;
	r = f8(v0, v1, (uint)1433888954U);
	print("ret f8 ushort %ud\n", r);
	}
	{
	S2 v7;
	S0 r;
	v7.f0 = 1370716416U;
	v7.f1 = 1877668529;
	r = f9((ulong)772340436UL, (uchar)133, (ulong)1786244662UL, (uchar)231, (short)24984, (int)1159617353, (vlong)-1666569466LL, v7);
	pS0("ret f9", r);
	}
	vf(1, (vlong)1603396928LL);
	{
	S3 x, r;

	x.f0 = 18.500;
	x.f1 = 19.375;
	x.f2 = 1460185830UL;
	x.f3 = 1967137943L;
	x.f4[0] = -72;
	x.f4[1] = 121;
	x.f4[2] = 42;
	x.f4[3] = -91;
	x.f4[4] = 12;
	x.f4[5] = 61;
	x.f5 = -30830;
	r = cb(back, x);
	pS3("ret cb", r);
	}
	exits(nil);
}
#endif
