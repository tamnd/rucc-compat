#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { uchar f0; };
typedef struct S1 S1;
struct S1 { short f0; ushort f1; uint f2; uint f3; short f4; uint f5; char f6[6]; };
typedef struct S2 S2;
struct S2 { float f0; char f1; };
typedef struct S3 S3;
struct S3 { long f0; uvlong f1; uint f2; uint f3; short f4; char f5; double f6; float f7; ushort f8; double f9; short f10; uchar f11; };

long f0(vlong a0, long a1, char a2, vlong a3, double a4, short a5);
ushort f1(int a0, uchar a1);
void f2(long a0, long a1, int a2, uint a3, vlong a4, ulong a5, uint a6, float a7);
short f3(double a0, S1 a1, uint a2, short a3, uvlong a4, S3 a5, ushort a6, int a7);
double f4(vlong a0, uchar a1);
uint f5(ushort a0, vlong a1, int a2, long a3, ulong a4, uint a5, S1 a6, double a7);
int f6(S2 a0, float a1, short a2, char a3, S3 a4, S2 a5);
S2 f7(uint a0);
float f8(double a0);
char f9(S2 a0, S0 a1);
void vf(int n, ...);
S3 cb(S3 (*fn)(S3, double, vlong), S3 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %ud\n", w, s.f0);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %d %ud %ud %ud %d %ud %d %d %d %d %d %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6[0], s.f6[1], s.f6[2], s.f6[3], s.f6[4], s.f6[5]);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %g %d\n", w, s.f0, s.f1);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %ld %llud %ud %ud %d %d %g %g %ud %g %d %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11);
}

long
f0(vlong a0, long a1, char a2, vlong a3, double a4, short a5)
{
	print("in f0\n");
	print("a0 vlong %lld\n", a0);
	print("a1 long %ld\n", a1);
	print("a2 char %d\n", a2);
	print("a3 vlong %lld\n", a3);
	print("a4 double %g\n", a4);
	print("a5 short %d\n", a5);
	return 1752212440L;
}

ushort
f1(int a0, uchar a1)
{
	print("in f1\n");
	print("a0 int %d\n", a0);
	print("a1 uchar %ud\n", a1);
	return 5267;
}

void
f2(long a0, long a1, int a2, uint a3, vlong a4, ulong a5, uint a6, float a7)
{
	print("in f2\n");
	print("a0 long %ld\n", a0);
	print("a1 long %ld\n", a1);
	print("a2 int %d\n", a2);
	print("a3 uint %ud\n", a3);
	print("a4 vlong %lld\n", a4);
	print("a5 ulong %lud\n", a5);
	print("a6 uint %ud\n", a6);
	print("a7 float %g\n", a7);
}

short
f3(double a0, S1 a1, uint a2, short a3, uvlong a4, S3 a5, ushort a6, int a7)
{
	print("in f3\n");
	print("a0 double %g\n", a0);
	pS1("a1", a1);
	print("a2 uint %ud\n", a2);
	print("a3 short %d\n", a3);
	print("a4 uvlong %llud\n", a4);
	pS3("a5", a5);
	print("a6 ushort %ud\n", a6);
	print("a7 int %d\n", a7);
	return -679;
}

double
f4(vlong a0, uchar a1)
{
	print("in f4\n");
	print("a0 vlong %lld\n", a0);
	print("a1 uchar %ud\n", a1);
	return -16.750;
}

uint
f5(ushort a0, vlong a1, int a2, long a3, ulong a4, uint a5, S1 a6, double a7)
{
	print("in f5\n");
	print("a0 ushort %ud\n", a0);
	print("a1 vlong %lld\n", a1);
	print("a2 int %d\n", a2);
	print("a3 long %ld\n", a3);
	print("a4 ulong %lud\n", a4);
	print("a5 uint %ud\n", a5);
	pS1("a6", a6);
	print("a7 double %g\n", a7);
	return 1281753345U;
}

int
f6(S2 a0, float a1, short a2, char a3, S3 a4, S2 a5)
{
	print("in f6\n");
	pS2("a0", a0);
	print("a1 float %g\n", a1);
	print("a2 short %d\n", a2);
	print("a3 char %d\n", a3);
	pS3("a4", a4);
	pS2("a5", a5);
	return -1514433857;
}

S2
f7(uint a0)
{
	S2 r;

	print("in f7\n");
	print("a0 uint %ud\n", a0);
	r.f0 = -10.875;
	r.f1 = 114;
	return r;
}

float
f8(double a0)
{
	print("in f8\n");
	print("a0 double %g\n", a0);
	return 31.625;
}

char
f9(S2 a0, S0 a1)
{
	print("in f9\n");
	pS2("a0", a0);
	pS0("a1", a1);
	return 113;
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %ud\n", va_arg(ap, uint));
	print("v1 %g\n", va_arg(ap, double));
	print("v2 %g\n", va_arg(ap, double));
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
	print("%s S0 %ud\n", w, s.f0);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %d %ud %ud %ud %d %ud %d %d %d %d %d %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6[0], s.f6[1], s.f6[2], s.f6[3], s.f6[4], s.f6[5]);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %g %d\n", w, s.f0, s.f1);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %ld %llud %ud %ud %d %d %g %g %ud %g %d %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11);
}

static S3
back(S3 x, double d, vlong v)
{
	pS3("back x", x);
	print("back %g %lld\n", d, v);
	x.f0 = x.f0 + 3;
	x.f1 = x.f1 + 3;
	x.f2 = x.f2 + 3;
	x.f3 = x.f3 + 3;
	x.f4 = x.f4 + 3;
	x.f5 = x.f5 + 3;
	x.f6 = x.f6 * 2;
	x.f7 = x.f7 * 2;
	x.f8 = x.f8 + 3;
	x.f9 = x.f9 * 2;
	x.f10 = x.f10 + 3;
	x.f11 = x.f11 + 3;
	return x;
}

void
main(void)
{
	{
	long r;
	r = f0((vlong)376139008LL, (long)-883091121L, (char)98, (vlong)1897001037986048LL, (double)51.500, (short)19829);
	print("ret f0 long %ld\n", r);
	}
	{
	ushort r;
	r = f1((int)-700243387, (uchar)108);
	print("ret f1 ushort %ud\n", r);
	}
	{
	f2((long)-1144022962L, (long)1650975075L, (int)10443540, (uint)517395653U, (vlong)1024347766LL, (ulong)1531299879UL, (uint)2038251992U, (float)39.875);
	}
	{
	S1 v1;
	S3 v5;
	short r;
	v1.f0 = -19407;
	v1.f1 = 17792;
	v1.f2 = 1348452145U;
	v1.f3 = 1855404258U;
	v1.f4 = 12947;
	v1.f5 = 721824836U;
	v1.f6[0] = -117;
	v1.f6[1] = 38;
	v1.f6[2] = 87;
	v1.f6[3] = -8;
	v1.f6[4] = 57;
	v1.f6[5] = 106;
	v5.f0 = 1883655587L;
	v5.f1 = 243124052ULL;
	v5.f2 = 750076165U;
	v5.f3 = 1257028278U;
	v5.f4 = -13415;
	v5.f5 = 24;
	v5.f6 = 6.875;
	v5.f7 = 7.750;
	v5.f8 = 6955;
	v5.f9 = 9.500;
	v5.f10 = -3725;
	v5.f11 = 62;
	r = f3((double)20.125, v1, (uint)1792231720U, (short)-17113, (uvlong)658652298ULL, v5, (ushort)46651, (int)-1672556524);
	print("ret f3 short %d\n", r);
	}
	{
	double r;
	r = f4((vlong)1609383986LL, (uchar)227);
	print("ret f4 double %g\n", r);
	}
	{
	S1 v6;
	uint r;
	v6.f0 = 18985;
	v6.f1 = 17370;
	v6.f2 = 919584139U;
	v6.f3 = 1426536252U;
	v6.f4 = -12525;
	v6.f5 = 292956830U;
	v6.f6[0] = 79;
	v6.f6[1] = 0;
	v6.f6[2] = 49;
	v6.f6[3] = 98;
	v6.f6[4] = -19;
	v6.f6[5] = 68;
	r = f5((ushort)19453, (vlong)1961739694LL, (int)-321208159, (long)828160272L, (ulong)1335112385UL, (uint)1842064498U, v6, (double)31.625);
	print("ret f5 uint %ud\n", r);
	}
	{
	S2 v0;
	S3 v4;
	S2 v5;
	int r;
	v0.f0 = -28.875;
	v0.f1 = 26;
	v4.f0 = 1687468093L;
	v4.f1 = 46936558ULL;
	v4.f2 = 553888671U;
	v4.f3 = 1060840784U;
	v4.f4 = -7937;
	v4.f5 = 50;
	v4.f6 = -2.625;
	v4.f7 = -1.500;
	v4.f8 = 34245;
	v4.f9 = 1.250;
	v4.f10 = -31015;
	v4.f11 = 216;
	v5.f0 = 12.875;
	v5.f1 = 66;
	r = f6(v0, (float)32.375, (short)13718, (char)71, v4, v5);
	print("ret f6 int %d\n", r);
	}
	{
	S2 r;
	r = f7((uint)1441447821U);
	pS2("ret f7", r);
	}
	{
	float r;
	r = f8((double)13.625);
	print("ret f8 float %g\n", r);
	}
	{
	S2 v0;
	S0 v1;
	char r;
	v0.f0 = 51.875;
	v0.f1 = -74;
	v1.f0 = 237;
	r = f9(v0, v1);
	print("ret f9 char %d\n", r);
	}
	vf(3, (uint)1695709782U, (double)32.125, (double)33.000);
	{
	S3 x, r;

	x.f0 = 538594458L;
	x.f1 = 1045549707639720ULL;
	x.f2 = 1552498684U;
	x.f3 = 2059450797U;
	x.f4 = 13150;
	x.f5 = -15;
	x.f6 = -33.000;
	x.f7 = -32.875;
	x.f8 = 6690;
	x.f9 = -30.625;
	x.f10 = 3460;
	x.f11 = 53;
	r = cb(back, x);
	pS3("ret cb", r);
	}
	exits(nil);
}
#endif
