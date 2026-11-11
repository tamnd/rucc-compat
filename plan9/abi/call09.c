#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { char f0[3]; long f1; char f2; int f3; ushort f4; vlong f5; ulong f6; ushort f7; short f8; uint f9; uint f10; short f11; };
typedef struct S1 S1;
struct S1 { char f0[4]; uchar f1; char f2; char f3; char f4; };
typedef struct S2 S2;
struct S2 { int f0; ushort f1; float f2; float f3; char f4; ushort f5; };
typedef struct S3 S3;
struct S3 { double f0; };

S2 f0(ulong a0, float a1, S3 a2, vlong a3, ushort a4, char a5, long a6, S0 a7);
S3 f1(S1 a0, S0 a1, S1 a2, S3 a3, long a4, S2 a5, long a6, S1 a7);
S1 f2(uchar a0);
S1 f3(short a0, int a1, S0 a2, ushort a3);
float f4(ushort a0, short a1);
short f5(S0 a0);
S2 f6(double a0, long a1, uvlong a2, S2 a3, S0 a4, uint a5);
S2 f7(S0 a0);
vlong f8(long a0, vlong a1, ushort a2);
S2 f9(S2 a0, S0 a1, S3 a2, vlong a3, uchar a4, S3 a5, S3 a6, uchar a7);
void vf(int n, ...);
S0 cb(S0 (*fn)(S0, double, vlong), S0 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %d %d %d %ld %d %d %ud %lld %lud %ud %d %ud %ud %d\n", w, s.f0[0], s.f0[1], s.f0[2], s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %d %d %d %d %ud %d %d %d\n", w, s.f0[0], s.f0[1], s.f0[2], s.f0[3], s.f1, s.f2, s.f3, s.f4);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d %ud %g %g %d %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %g\n", w, s.f0);
}

S2
f0(ulong a0, float a1, S3 a2, vlong a3, ushort a4, char a5, long a6, S0 a7)
{
	S2 r;

	print("in f0\n");
	print("a0 ulong %lud\n", a0);
	print("a1 float %g\n", a1);
	pS3("a2", a2);
	print("a3 vlong %lld\n", a3);
	print("a4 ushort %ud\n", a4);
	print("a5 char %d\n", a5);
	print("a6 long %ld\n", a6);
	pS0("a7", a7);
	r.f0 = 1386734684;
	r.f1 = 24077;
	r.f2 = 53.250;
	r.f3 = 54.125;
	r.f4 = -32;
	r.f5 = 17617;
	return r;
}

S3
f1(S1 a0, S0 a1, S1 a2, S3 a3, long a4, S2 a5, long a6, S1 a7)
{
	S3 r;

	print("in f1\n");
	pS1("a0", a0);
	pS0("a1", a1);
	pS1("a2", a2);
	pS3("a3", a3);
	print("a4 long %ld\n", a4);
	pS2("a5", a5);
	print("a6 long %ld\n", a6);
	pS1("a7", a7);
	r = a3;
	r.f0 = r.f0 * 2;
	return r;
}

S1
f2(uchar a0)
{
	S1 r;

	print("in f2\n");
	print("a0 uchar %ud\n", a0);
	r.f0[0] = 46;
	r.f0[1] = 95;
	r.f0[2] = -16;
	r.f0[3] = 65;
	r.f1 = 114;
	r.f2 = -35;
	r.f3 = 84;
	r.f4 = 5;
	return r;
}

S1
f3(short a0, int a1, S0 a2, ushort a3)
{
	S1 r;

	print("in f3\n");
	print("a0 short %d\n", a0);
	print("a1 int %d\n", a1);
	pS0("a2", a2);
	print("a3 ushort %ud\n", a3);
	r.f0[0] = -116;
	r.f0[1] = 37;
	r.f0[2] = 86;
	r.f0[3] = -7;
	r.f1 = 184;
	r.f2 = 105;
	r.f3 = -26;
	r.f4 = 75;
	return r;
}

float
f4(ushort a0, short a1)
{
	print("in f4\n");
	print("a0 ushort %ud\n", a0);
	print("a1 short %d\n", a1);
	return 6.500;
}

short
f5(S0 a0)
{
	print("in f5\n");
	pS0("a0", a0);
	return 5771;
}

S2
f6(double a0, long a1, uvlong a2, S2 a3, S0 a4, uint a5)
{
	S2 r;

	print("in f6\n");
	print("a0 double %g\n", a0);
	print("a1 long %ld\n", a1);
	print("a2 uvlong %llud\n", a2);
	pS2("a3", a3);
	pS0("a4", a4);
	print("a5 uint %ud\n", a5);
	r = a3;
	r.f0 = r.f0 + 3;
	r.f1 = r.f1 + 3;
	r.f2 = r.f2 * 2;
	r.f3 = r.f3 * 2;
	r.f4 = r.f4 + 3;
	r.f5 = r.f5 + 3;
	return r;
}

S2
f7(S0 a0)
{
	S2 r;

	print("in f7\n");
	pS0("a0", a0);
	r.f0 = -1487972049;
	r.f1 = 8322;
	r.f2 = -12.625;
	r.f3 = -11.500;
	r.f4 = 21;
	r.f5 = 1862;
	return r;
}

vlong
f8(long a0, vlong a1, ushort a2)
{
	print("in f8\n");
	print("a0 long %ld\n", a0);
	print("a1 vlong %lld\n", a1);
	print("a2 ushort %ud\n", a2);
	return 1622558814LL;
}

S2
f9(S2 a0, S0 a1, S3 a2, vlong a3, uchar a4, S3 a5, S3 a6, uchar a7)
{
	S2 r;

	print("in f9\n");
	pS2("a0", a0);
	pS0("a1", a1);
	pS3("a2", a2);
	print("a3 vlong %lld\n", a3);
	print("a4 uchar %ud\n", a4);
	pS3("a5", a5);
	pS3("a6", a6);
	print("a7 uchar %ud\n", a7);
	r = a0;
	r.f0 = r.f0 + 3;
	r.f1 = r.f1 + 3;
	r.f2 = r.f2 * 2;
	r.f3 = r.f3 * 2;
	r.f4 = r.f4 + 3;
	r.f5 = r.f5 + 3;
	return r;
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %ld\n", va_arg(ap, long));
	print("v1 %g\n", va_arg(ap, double));
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
	print("%s S0 %d %d %d %ld %d %d %ud %lld %lud %ud %d %ud %ud %d\n", w, s.f0[0], s.f0[1], s.f0[2], s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %d %d %d %d %ud %d %d %d\n", w, s.f0[0], s.f0[1], s.f0[2], s.f0[3], s.f1, s.f2, s.f3, s.f4);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d %ud %g %g %d %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %g\n", w, s.f0);
}

static S0
back(S0 x, double d, vlong v)
{
	pS0("back x", x);
	print("back %g %lld\n", d, v);
	x.f0[0] = x.f0[0] + 3;
	x.f0[1] = x.f0[1] + 3;
	x.f0[2] = x.f0[2] + 3;
	x.f1 = x.f1 + 3;
	x.f2 = x.f2 + 3;
	x.f3 = x.f3 + 3;
	x.f4 = x.f4 + 3;
	x.f5 = x.f5 + 3;
	x.f6 = x.f6 + 3;
	x.f7 = x.f7 + 3;
	x.f8 = x.f8 + 3;
	x.f9 = x.f9 + 3;
	x.f10 = x.f10 + 3;
	x.f11 = x.f11 + 3;
	return x;
}

void
main(void)
{
	{
	S3 v2;
	S0 v7;
	S2 r;
	v2.f0 = 36.000;
	v7.f0[0] = 124;
	v7.f0[1] = -45;
	v7.f0[2] = 94;
	v7.f1 = 88745359L;
	v7.f2 = -64;
	v7.f3 = 1102649585;
	v7.f4 = 37538;
	v7.f5 = -4609569458266726478LL;
	v7.f6 = 476022276UL;
	v7.f7 = 65461;
	v7.f8 = -31078;
	v7.f9 = 1996878615U;
	v7.f10 = 356347080U;
	v7.f11 = -26233;
	r = f0((ulong)116996688UL, (float)-20.875, v2, (vlong)-1130900914LL, (ushort)42851, (char)20, (long)-504273605L, v7);
	pS2("ret f0", r);
	}
	{
	S1 v0;
	S0 v1;
	S1 v2;
	S3 v3;
	S2 v5;
	S1 v7;
	S3 r;
	v0.f0[0] = 11;
	v0.f0[1] = -60;
	v0.f0[2] = 109;
	v0.f0[3] = 30;
	v0.f1 = 207;
	v0.f2 = 0;
	v0.f3 = 49;
	v0.f4 = -98;
	v1.f0[0] = 95;
	v1.f0[1] = 16;
	v1.f0[2] = -65;
	v1.f1 = 1363581426L;
	v1.f2 = 35;
	v1.f3 = -230002004;
	v1.f4 = 1797;
	v1.f5 = 1243906230LL;
	v1.f6 = 1750858343UL;
	v1.f7 = 29720;
	v1.f8 = 28105;
	v1.f9 = 1124231034U;
	v1.f10 = 1631183147U;
	v1.f11 = 23260;
	v2.f0[0] = -51;
	v2.f0[1] = 100;
	v2.f0[2] = 21;
	v2.f0[3] = -70;
	v2.f1 = 119;
	v2.f2 = 40;
	v2.f3 = -89;
	v2.f4 = 10;
	v3.f0 = -15.125;
	v5.f0 = 195080795;
	v5.f1 = 11276;
	v5.f2 = 7.375;
	v5.f3 = 8.250;
	v5.f4 = 31;
	v5.f5 = 4816;
	v7.f0[0] = -47;
	v7.f0[1] = 96;
	v7.f0[2] = 17;
	v7.f0[3] = -66;
	v7.f1 = 243;
	v7.f2 = 36;
	v7.f3 = -85;
	v7.f4 = 6;
	r = f1(v0, v1, v2, v3, (long)1145812483L, v5, (long)-1652764596L, v7);
	pS3("ret f1", r);
	}
	{
	S1 r;
	r = f2((uchar)250);
	pS1("ret f2", r);
	}
	{
	S0 v2;
	S1 r;
	v2.f0[0] = 64;
	v2.f0[1] = 113;
	v2.f0[2] = -34;
	v2.f1 = 899792211L;
	v2.f2 = 4;
	v2.f3 = -1913696437;
	v2.f4 = 10854;
	v2.f5 = 780119355351052LL;
	v2.f6 = 1287069128UL;
	v2.f7 = 38777;
	v2.f8 = 4394;
	v2.f9 = 660441819U;
	v2.f10 = 1167393932U;
	v2.f11 = 32317;
	r = f3((short)-21012, (int)1434995653, v2, (ushort)50550);
	pS1("ret f3", r);
	}
	{
	float r;
	r = f4((ushort)54716, (short)20333);
	print("ret f4 float %g\n", r);
	}
	{
	S0 v0;
	short r;
	v0.f0[0] = 51;
	v0.f0[1] = 100;
	v0.f0[2] = -21;
	v0.f1 = 1695927494L;
	v0.f2 = 119;
	v0.f3 = -562348072;
	v0.f4 = 14809;
	v0.f5 = 1576252298LL;
	v0.f6 = 2083204411UL;
	v0.f7 = 42732;
	v0.f8 = 8349;
	v0.f9 = 1456577102U;
	v0.f10 = 1963529215U;
	v0.f11 = 3504;
	r = f5(v0);
	print("ret f5 short %d\n", r);
	}
	{
	S2 v3;
	S0 v4;
	S2 r;
	v3.f0 = 1154054172;
	v3.f1 = 61901;
	v3.f2 = -11.250;
	v3.f3 = -10.125;
	v3.f4 = 96;
	v3.f5 = 55441;
	v4.f0[0] = -112;
	v4.f0[1] = 33;
	v4.f0[2] = 82;
	v4.f1 = -2076534531L;
	v4.f2 = 52;
	v4.f3 = 942955109;
	v4.f4 = 54294;
	v4.f5 = 1956865205578012LL;
	v4.f6 = 316327800UL;
	v4.f7 = 16681;
	v4.f8 = 15066;
	v4.f9 = 1837184139U;
	v4.f10 = 196652604U;
	v4.f11 = 10221;
	r = f6((double)27.500, (long)-464254325L, (uvlong)971206438ULL, v3, v4, (uint)1478158551U);
	pS2("ret f6", r);
	}
	{
	S0 v0;
	S2 r;
	v0.f0[0] = 29;
	v0.f0[1] = 78;
	v0.f0[2] = -127;
	v0.f1 = 788358704L;
	v0.f2 = 97;
	v0.f3 = -1802262930;
	v0.f4 = 54083;
	v0.f5 = 668683508LL;
	v0.f6 = 1175635621UL;
	v0.f7 = 16470;
	v0.f8 = 14855;
	v0.f9 = 549008312U;
	v0.f10 = 1055960425U;
	v0.f11 = 10010;
	r = f7(v0);
	pS2("ret f7", r);
	}
	{
	vlong r;
	r = f8((long)246485382L, (vlong)753439755312492LL, (ushort)1256);
	print("ret f8 vlong %lld\n", r);
	}
	{
	S2 v0;
	S0 v1;
	S3 v2;
	S3 v5;
	S3 v6;
	S2 r;
	v0.f0 = 1197217070;
	v0.f1 = 36575;
	v0.f2 = -27.000;
	v0.f3 = -26.875;
	v0.f4 = -114;
	v0.f5 = 30115;
	v1.f0[0] = 2;
	v1.f0[1] = 51;
	v1.f0[2] = -100;
	v1.f1 = 2119697429L;
	v1.f2 = 70;
	v1.f3 = -986118007;
	v1.f4 = 28968;
	v1.f5 = 2000028233066706LL;
	v1.f6 = 359490698UL;
	v1.f7 = 56891;
	v1.f8 = 22508;
	v1.f9 = 1880347037U;
	v1.f10 = 239815502U;
	v1.f11 = 17663;
	v2.f0 = 11.250;
	v5.f0 = 31.750;
	v6.f0 = 51.250;
	r = f9(v0, v1, v2, (vlong)-352820818LL, (uchar)3, v5, v6, (uchar)180);
	pS2("ret f9", r);
	}
	vf(2, (long)1303552506L, (double)15.625);
	{
	S0 x, r;

	x.f0[0] = 62;
	x.f0[1] = 111;
	x.f0[2] = -32;
	x.f1 = 1667293521L;
	x.f2 = 2;
	x.f3 = -533714099;
	x.f4 = 20068;
	x.f5 = 1547622967854982LL;
	x.f6 = 2054570438UL;
	x.f7 = 47991;
	x.f8 = 13608;
	x.f9 = 1427943129U;
	x.f10 = 1934895242U;
	x.f11 = 8763;
	r = cb(back, x);
	pS0("ret cb", r);
	}
	exits(nil);
}
#endif
