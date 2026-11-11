#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { int f0; uint f1; ulong f2; char f3[5]; float f4; ushort f5; vlong f6; uchar f7; };
typedef struct S1 S1;
struct S1 { ulong f0; int f1; ulong f2; char f3; int f4; };
typedef struct S2 S2;
struct S2 { char f0; char f1; };
typedef struct S3 S3;
struct S3 { float f0; ulong f1; uvlong f2; };

short f0(long a0, ulong a1);
float f1(S0 a0, S2 a1, S1 a2);
void f2(vlong a0);
double f3(S3 a0, double a1, char a2, ushort a3);
short f4(uvlong a0, char a1, ushort a2);
int f5(char a0, S3 a1, double a2, S2 a3, int a4, float a5);
float f6(vlong a0, int a1, S3 a2, uint a3, vlong a4, uchar a5, S0 a6, S2 a7);
double f7(S3 a0, uvlong a1, uint a2, vlong a3, float a4, S3 a5);
long f8(float a0, S1 a1, S1 a2, vlong a3);
S0 f9(uchar a0);
void vf(int n, ...);
S1 cb(S1 (*fn)(S1, double, vlong), S1 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %d %ud %lud %d %d %d %d %d %g %ud %lld %ud\n", w, s.f0, s.f1, s.f2, s.f3[0], s.f3[1], s.f3[2], s.f3[3], s.f3[4], s.f4, s.f5, s.f6, s.f7);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %lud %d %lud %d %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d %d\n", w, s.f0, s.f1);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %g %lud %llud\n", w, s.f0, s.f1, s.f2);
}

short
f0(long a0, ulong a1)
{
	print("in f0\n");
	print("a0 long %ld\n", a0);
	print("a1 ulong %lud\n", a1);
	return 32656;
}

float
f1(S0 a0, S2 a1, S1 a2)
{
	print("in f1\n");
	pS0("a0", a0);
	pS2("a1", a1);
	pS1("a2", a2);
	return 5.125;
}

void
f2(vlong a0)
{
	print("in f2\n");
	print("a0 vlong %lld\n", a0);
}

double
f3(S3 a0, double a1, char a2, ushort a3)
{
	print("in f3\n");
	pS3("a0", a0);
	print("a1 double %g\n", a1);
	print("a2 char %d\n", a2);
	print("a3 ushort %ud\n", a3);
	return 43.250;
}

short
f4(uvlong a0, char a1, ushort a2)
{
	print("in f4\n");
	print("a0 uvlong %llud\n", a0);
	print("a1 char %d\n", a1);
	print("a2 ushort %ud\n", a2);
	return 15194;
}

int
f5(char a0, S3 a1, double a2, S2 a3, int a4, float a5)
{
	print("in f5\n");
	print("a0 char %d\n", a0);
	pS3("a1", a1);
	print("a2 double %g\n", a2);
	pS2("a3", a3);
	print("a4 int %d\n", a4);
	print("a5 float %g\n", a5);
	return 1320500994;
}

float
f6(vlong a0, int a1, S3 a2, uint a3, vlong a4, uchar a5, S0 a6, S2 a7)
{
	print("in f6\n");
	print("a0 vlong %lld\n", a0);
	print("a1 int %d\n", a1);
	pS3("a2", a2);
	print("a3 uint %ud\n", a3);
	print("a4 vlong %lld\n", a4);
	print("a5 uchar %ud\n", a5);
	pS0("a6", a6);
	pS2("a7", a7);
	return 30.625;
}

double
f7(S3 a0, uvlong a1, uint a2, vlong a3, float a4, S3 a5)
{
	print("in f7\n");
	pS3("a0", a0);
	print("a1 uvlong %llud\n", a1);
	print("a2 uint %ud\n", a2);
	print("a3 vlong %lld\n", a3);
	print("a4 float %g\n", a4);
	pS3("a5", a5);
	return 35.875;
}

long
f8(float a0, S1 a1, S1 a2, vlong a3)
{
	print("in f8\n");
	print("a0 float %g\n", a0);
	pS1("a1", a1);
	pS1("a2", a2);
	print("a3 vlong %lld\n", a3);
	return 2011872650L;
}

S0
f9(uchar a0)
{
	S0 r;

	print("in f9\n");
	print("a0 uchar %ud\n", a0);
	r.f0 = 2103296517;
	r.f1 = 462764982U;
	r.f2 = 969717095UL;
	r.f3[0] = 24;
	r.f3[1] = -73;
	r.f3[2] = 122;
	r.f3[3] = 43;
	r.f3[4] = -92;
	r.f4 = 6.375;
	r.f5 = 2366;
	r.f6 = -4610955649533287802LL;
	r.f7 = 160;
	return r;
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %g\n", va_arg(ap, double));
	print("v1 %llud\n", va_arg(ap, uvlong));
	print("v2 %llud\n", va_arg(ap, uvlong));
	print("v3 %ud\n", va_arg(ap, uint));
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
	print("%s S0 %d %ud %lud %d %d %d %d %d %g %ud %lld %ud\n", w, s.f0, s.f1, s.f2, s.f3[0], s.f3[1], s.f3[2], s.f3[3], s.f3[4], s.f4, s.f5, s.f6, s.f7);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %lud %d %lud %d %d\n", w, s.f0, s.f1, s.f2, s.f3, s.f4);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %d %d\n", w, s.f0, s.f1);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %g %lud %llud\n", w, s.f0, s.f1, s.f2);
}

static S1
back(S1 x, double d, vlong v)
{
	pS1("back x", x);
	print("back %g %lld\n", d, v);
	x.f0 = x.f0 + 3;
	x.f1 = x.f1 + 3;
	x.f2 = x.f2 + 3;
	x.f3 = x.f3 + 3;
	x.f4 = x.f4 + 3;
	return x;
}

void
main(void)
{
	{
	short r;
	r = f0((long)625985720L, (ulong)1132937833UL);
	print("ret f0 short %d\n", r);
	}
	{
	S0 v0;
	S2 v1;
	S1 v2;
	float r;
	v0.f0 = 1069765295;
	v0.f1 = 1576717408U;
	v0.f2 = 2083669521UL;
	v0.f3[0] = 66;
	v0.f3[1] = 115;
	v0.f3[2] = -36;
	v0.f3[3] = 85;
	v0.f3[4] = 6;
	v0.f4 = -5.125;
	v0.f5 = 39400;
	v0.f6 = 1844324661957394LL;
	v0.f7 = 74;
	v1.f0 = -3;
	v1.f1 = 52;
	v2.f0 = 2020496983UL;
	v2.f1 = -379965448;
	v2.f2 = 886917561UL;
	v2.f3 = 106;
	v2.f4 = -1900821787;
	r = f1(v0, v1, v2);
	print("ret f1 float %g\n", r);
	}
	{
	f2((vlong)851996352LL);
	}
	{
	S3 v0;
	double r;
	v0.f0 = 25.250;
	v0.f1 = 1295775927UL;
	v0.f2 = 1802728040ULL;
	r = f3(v0, (double)45.750, (char)11, (ushort)62524);
	print("ret f3 double %g\n", r);
	}
	{
	short r;
	r = f4((uvlong)1141179522ULL, (char)51, (ushort)63460);
	print("ret f4 short %d\n", r);
	}
	{
	S3 v1;
	S2 v3;
	int r;
	v1.f0 = 28.750;
	v1.f1 = 451379675UL;
	v1.f2 = 958331788ULL;
	v3.f0 = 126;
	v3.f1 = 47;
	r = f5((char)-82, v1, (double)-28.625, v3, (int)1909063476, (float)-26.375);
	print("ret f5 int %d\n", r);
	}
	{
	S3 v2;
	S0 v6;
	S2 v7;
	float r;
	v2.f0 = 12.625;
	v2.f1 = 712311516UL;
	v2.f2 = 1219267286790894ULL;
	v6.f0 = 1754467071;
	v6.f1 = 113935536U;
	v6.f2 = 620887649UL;
	v6.f3[0] = 18;
	v6.f3[1] = 67;
	v6.f3[2] = -116;
	v6.f3[3] = 37;
	v6.f3[4] = 86;
	v6.f4 = 40.125;
	v6.f5 = 21048;
	v6.f6 = 381538401611778LL;
	v6.f7 = 154;
	v7.f0 = -83;
	v7.f1 = 4;
	r = f6((vlong)557716784145340LL, (int)-1064667224, v2, (uint)1571619337U, (vlong)2078571450LL, (uchar)107, v6, v7);
	print("ret f6 float %g\n", r);
	}
	{
	S3 v0;
	S3 v5;
	double r;
	v0.f0 = 17.875;
	v0.f1 = 881819490UL;
	v0.f2 = 1388775769314816ULL;
	v5.f0 = 37.375;
	v5.f1 = 283443510UL;
	v5.f2 = 790397994186876ULL;
	r = f7(v0, (uvlong)1325603041797202ULL, (uint)1832551178U, (vlong)192020219058936LL, (float)-37.500, v5);
	print("ret f7 double %g\n", r);
	}
	{
	S1 v1;
	S1 v2;
	long r;
	v1.f0 = 635799218UL;
	v1.f1 = -1142751331;
	v1.f2 = 1649703444UL;
	v1.f3 = 69;
	v1.f4 = -516124022;
	v2.f0 = 37423238UL;
	v2.f1 = 544375351;
	v2.f2 = 1051327464UL;
	v2.f3 = 25;
	v2.f4 = 2065231690;
	r = f8((float)41.750, v1, v2, (vlong)2093489299449064LL);
	print("ret f8 long %ld\n", r);
	}
	{
	S0 r;
	r = f9((uchar)81);
	pS0("ret f9", r);
	}
	vf(4, (double)21.125, (uvlong)326606408ULL, (uvlong)833561021675570ULL, (uint)1340510634U);
	{
	S1 x, r;

	x.f0 = 810022619UL;
	x.f1 = -1316974732;
	x.f2 = 1823926845UL;
	x.f3 = 110;
	x.f4 = -690347423;
	r = cb(back, x);
	pS1("ret cb", r);
	}
	exits(nil);
}
#endif
