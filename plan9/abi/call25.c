#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { uchar f0; };
typedef struct S1 S1;
struct S1 { ushort f0; uchar f1[2]; double f2; };
typedef struct S2 S2;
struct S2 { char f0; float f1; uvlong f2; short f3; };
typedef struct S3 S3;
struct S3 { double f0; double f1; vlong f2; uint f3; float f4; vlong f5; vlong f6; float f7; char f8; int f9; uint f10; char f11; short f12; };

S1 f0(uint a0, long a1, uvlong a2, int a3, ulong a4, char a5, S3 a6, S0 a7);
short f1(float a0);
ushort f2(S3 a0, char a1, S1 a2, S3 a3);
long f3(uvlong a0, S3 a1);
uchar f4(long a0, S0 a1, char a2, uint a3, int a4, S0 a5, float a6, uchar a7);
int f5(char a0, int a1, int a2, S2 a3);
float f6(short a0, vlong a1, int a2, char a3, float a4, char a5, uchar a6, ulong a7);
char f7(uint a0);
S2 f8(float a0, S3 a1, ushort a2);
short f9(ulong a0, vlong a1);
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
	print("%s S1 %ud %ud %ud %g\n", w, s.f0, s.f1[0], s.f1[1], s.f2);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d %g %llud %d\n", w, s.f0, s.f1, s.f2, s.f3);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %g %g %lld %ud %g %lld %lld %g %d %d %ud %d %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11, s.f12);
}

S1
f0(uint a0, long a1, uvlong a2, int a3, ulong a4, char a5, S3 a6, S0 a7)
{
	S1 r;

	print("in f0\n");
	print("a0 uint %ud\n", a0);
	print("a1 long %ld\n", a1);
	print("a2 uvlong %llud\n", a2);
	print("a3 int %d\n", a3);
	print("a4 ulong %lud\n", a4);
	print("a5 char %d\n", a5);
	pS3("a6", a6);
	pS0("a7", a7);
	r.f0 = 39644;
	r.f1[0] = 141;
	r.f1[1] = 62;
	r.f2 = 49.125;
	return r;
}

short
f1(float a0)
{
	print("in f1\n");
	print("a0 float %g\n", a0);
	return -6243;
}

ushort
f2(S3 a0, char a1, S1 a2, S3 a3)
{
	print("in f2\n");
	pS3("a0", a0);
	print("a1 char %d\n", a1);
	pS1("a2", a2);
	pS3("a3", a3);
	return 43177;
}

long
f3(uvlong a0, S3 a1)
{
	print("in f3\n");
	print("a0 uvlong %llud\n", a0);
	pS3("a1", a1);
	return 83770987L;
}

uchar
f4(long a0, S0 a1, char a2, uint a3, int a4, S0 a5, float a6, uchar a7)
{
	print("in f4\n");
	print("a0 long %ld\n", a0);
	pS0("a1", a1);
	print("a2 char %d\n", a2);
	print("a3 uint %ud\n", a3);
	print("a4 int %d\n", a4);
	pS0("a5", a5);
	print("a6 float %g\n", a6);
	print("a7 uchar %ud\n", a7);
	return 133;
}

int
f5(char a0, int a1, int a2, S2 a3)
{
	print("in f5\n");
	print("a0 char %d\n", a0);
	print("a1 int %d\n", a1);
	print("a2 int %d\n", a2);
	pS2("a3", a3);
	return 697058536;
}

float
f6(short a0, vlong a1, int a2, char a3, float a4, char a5, uchar a6, ulong a7)
{
	print("in f6\n");
	print("a0 short %d\n", a0);
	print("a1 vlong %lld\n", a1);
	print("a2 int %d\n", a2);
	print("a3 char %d\n", a3);
	print("a4 float %g\n", a4);
	print("a5 char %d\n", a5);
	print("a6 uchar %ud\n", a6);
	print("a7 ulong %lud\n", a7);
	return -16.500;
}

char
f7(uint a0)
{
	print("in f7\n");
	print("a0 uint %ud\n", a0);
	return 1;
}

S2
f8(float a0, S3 a1, ushort a2)
{
	S2 r;

	print("in f8\n");
	print("a0 float %g\n", a0);
	pS3("a1", a1);
	print("a2 ushort %ud\n", a2);
	r.f0 = 35;
	r.f1 = -32.500;
	r.f2 = 2035073246201430ULL;
	r.f3 = 8886;
	return r;
}

short
f9(ulong a0, vlong a1)
{
	print("in f9\n");
	print("a0 ulong %lud\n", a0);
	print("a1 vlong %lld\n", a1);
	return 19090;
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
	print("%s S0 %ud\n", w, s.f0);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %ud %ud %ud %g\n", w, s.f0, s.f1[0], s.f1[1], s.f2);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d %g %llud %d\n", w, s.f0, s.f1, s.f2, s.f3);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %g %g %lld %ud %g %lld %lld %g %d %d %ud %d %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5, s.f6, s.f7, s.f8, s.f9, s.f10, s.f11, s.f12);
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
	x.f4 = x.f4 * 2;
	x.f5 = x.f5 + 3;
	x.f6 = x.f6 + 3;
	x.f7 = x.f7 * 2;
	x.f8 = x.f8 + 3;
	x.f9 = x.f9 + 3;
	x.f10 = x.f10 + 3;
	x.f11 = x.f11 + 3;
	x.f12 = x.f12 + 3;
	return x;
}

void
main(void)
{
	{
	S3 v6;
	S0 v7;
	S1 r;
	v6.f0 = 31.000;
	v6.f1 = 32.875;
	v6.f2 = -368238730LL;
	v6.f3 = 875190843U;
	v6.f4 = 35.500;
	v6.f5 = -4609796917691102704LL;
	v6.f6 = 248563534LL;
	v6.f7 = 38.125;
	v6.f8 = -48;
	v6.f9 = 1769419873;
	v6.f10 = 128888338U;
	v6.f11 = -67;
	v6.f12 = 8564;
	v7.f0 = 252;
	r = f0((uint)305066192U, (long)-812018305L, (uvlong)1318970418ULL, (int)1825922531, (ulong)185390996UL, (char)69, v6, v7);
	pS1("ret f0", r);
	}
	{
	short r;
	r = f1((float)17.625);
	print("ret f1 short %d\n", r);
	}
	{
	S3 v0;
	S1 v2;
	S3 v3;
	ushort r;
	v0.f0 = 55.875;
	v0.f1 = 56.750;
	v0.f2 = 1579906998706784LL;
	v0.f3 = 2086854372U;
	v0.f4 = -38.375;
	v0.f5 = 953274950LL;
	v0.f6 = 1460231443681196LL;
	v0.f7 = -35.000;
	v0.f8 = 89;
	v0.f9 = 833599754;
	v0.f10 = 1340551867U;
	v0.f11 = 108;
	v0.f12 = 9757;
	v2.f0 = 62373;
	v2.f1[0] = 86;
	v2.f1[1] = 7;
	v2.f2 = -19.000;
	v3.f0 = -2.875;
	v3.f1 = -1.750;
	v3.f2 = 383151448450904LL;
	v3.f3 = 890102412U;
	v3.f4 = 2.375;
	v3.f5 = 1904006638LL;
	v3.f6 = -4611422542533962602LL;
	v3.f7 = 5.000;
	v3.f8 = 1;
	v3.f9 = -1784331442;
	v3.f10 = 143799907U;
	v3.f11 = 20;
	v3.f12 = -10693;
	r = f2(v0, (char)77, v2, v3);
	print("ret f2 ushort %ud\n", r);
	}
	{
	S3 v1;
	long r;
	v1.f0 = 56.625;
	v1.f1 = -40.500;
	v1.f2 = -4609816927391131624LL;
	v1.f3 = 228553894U;
	v1.f4 = -37.125;
	v1.f5 = -1242458120LL;
	v1.f6 = 1749415481230706LL;
	v1.f7 = -34.750;
	v1.f8 = -27;
	v1.f9 = 1122782924;
	v1.f10 = 1629735037U;
	v1.f11 = -46;
	v1.f12 = 15327;
	r = f3((uvlong)256805993415676ULL, v1);
	print("ret f3 long %ld\n", r);
	}
	{
	S0 v1;
	S0 v5;
	uchar r;
	v1.f0 = 173;
	v5.f0 = 129;
	r = f4((long)-1144364373L, v1, (char)6, (uint)10784951U, (int)-517737064, v5, (float)-36.875, (uchar)202);
	print("ret f4 uchar %ud\n", r);
	}
	{
	S2 v3;
	int r;
	v3.f0 = 16;
	v3.f1 = 4.875;
	v3.f2 = 334889330ULL;
	v3.f3 = 31523;
	r = f5((char)-100, (int)1377044885, (int)1883996998, v3);
	print("ret f5 int %d\n", r);
	}
	{
	float r;
	r = f6((short)5004, (vlong)180293465878782LL, (int)-687245038, (char)31, (float)-30.000, (char)-1, (uchar)178, (ulong)1074521955UL);
	print("ret f6 float %g\n", r);
	}
	{
	char r;
	r = f7((uint)1011349417U);
	print("ret f7 char %d\n", r);
	}
	{
	S3 v1;
	S2 r;
	v1.f0 = 49.125;
	v1.f1 = 50.000;
	v1.f2 = 1962086991243322LL;
	v1.f3 = 321549570U;
	v1.f4 = 53.625;
	v1.f5 = 1335453796LL;
	v1.f6 = -4609843606991170184LL;
	v1.f7 = 56.250;
	v1.f8 = 119;
	v1.f9 = -1215778600;
	v1.f10 = 1722730713U;
	v1.f11 = 10;
	v1.f12 = -15419;
	r = f8((float)-28.625, v1, (ushort)884);
	pS2("ret f8", r);
	}
	{
	short r;
	r = f9((ulong)793580474UL, (vlong)-4610385481938790150LL);
	print("ret f9 short %d\n", r);
	}
	vf(1, (vlong)1237363761080154LL);
	{
	S3 x, r;

	x.f0 = -20.375;
	x.f1 = -19.250;
	x.f2 = 1094152233446860LL;
	x.f3 = 1601101064U;
	x.f4 = -16.875;
	x.f5 = 467521642LL;
	x.f6 = 974476678421272LL;
	x.f7 = -13.500;
	x.f8 = 125;
	x.f9 = 347846446;
	x.f10 = 854798559U;
	x.f11 = 16;
	x.f12 = 9281;
	r = cb(back, x);
	pS3("ret cb", r);
	}
	exits(nil);
}
#endif
