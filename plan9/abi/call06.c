#include <u.h>
#include <libc.h>

typedef struct S0 S0;
struct S0 { double f0; short f1; short f2; uchar f3[3]; uchar f4; short f5; int f6; float f7; uint f8; short f9; };
typedef struct S1 S1;
struct S1 { ushort f0; ushort f1; double f2; };
typedef struct S2 S2;
struct S2 { uchar f0; uchar f1; };
typedef struct S3 S3;
struct S3 { uvlong f0; vlong f1; ushort f2; long f3; double f4; uchar f5; };

int f0(ushort a0, vlong a1, S2 a2, int a3);
vlong f1(uchar a0, S0 a1);
S3 f2(float a0, double a1);
long f3(S3 a0, vlong a1, vlong a2, long a3, char a4, ushort a5);
S3 f4(ulong a0, S2 a1);
ulong f5(S0 a0);
int f6(float a0, ulong a1, ushort a2, float a3, S0 a4, float a5);
vlong f7(long a0, uchar a1, ulong a2, S2 a3, uint a4, short a5, int a6, uchar a7);
ushort f8(S0 a0);
uvlong f9(char a0, S0 a1, uchar a2, S2 a3, vlong a4, char a5);
void vf(int n, ...);
S1 cb(S1 (*fn)(S1, double, vlong), S1 x);

#ifdef CALLEE
static void
pS0(char *w, S0 s)
{
	print("%s S0 %g %d %d %ud %ud %ud %ud %d %d %g %ud %d\n", w, s.f0, s.f1, s.f2, s.f3[0], s.f3[1], s.f3[2], s.f4, s.f5, s.f6, s.f7, s.f8, s.f9);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %ud %ud %g\n", w, s.f0, s.f1, s.f2);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %ud %ud\n", w, s.f0, s.f1);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %llud %lld %ud %ld %g %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5);
}

int
f0(ushort a0, vlong a1, S2 a2, int a3)
{
	print("in f0\n");
	print("a0 ushort %ud\n", a0);
	print("a1 vlong %lld\n", a1);
	pS2("a2", a2);
	print("a3 int %d\n", a3);
	return -104422216;
}

vlong
f1(uchar a0, S0 a1)
{
	print("in f1\n");
	print("a0 uchar %ud\n", a0);
	pS0("a1", a1);
	return -456777924LL;
}

S3
f2(float a0, double a1)
{
	S3 r;

	print("in f2\n");
	print("a0 float %g\n", a0);
	print("a1 double %g\n", a1);
	r.f0 = 639625658ULL;
	r.f1 = 1146581210733320LL;
	r.f2 = 56604;
	r.f3 = -12998349L;
	r.f4 = -14.250;
	r.f5 = 47;
	return r;
}

long
f3(S3 a0, vlong a1, vlong a2, long a3, char a4, ushort a5)
{
	print("in f3\n");
	pS3("a0", a0);
	print("a1 vlong %lld\n", a1);
	print("a2 vlong %lld\n", a2);
	print("a3 long %ld\n", a3);
	print("a4 char %d\n", a4);
	print("a5 ushort %ud\n", a5);
	return 239008981L;
}

S3
f4(ulong a0, S2 a1)
{
	S3 r;

	print("in f4\n");
	print("a0 ulong %lud\n", a0);
	pS2("a1", a1);
	r.f0 = 302182425544564ULL;
	r.f1 = -809133632LL;
	r.f2 = 57329;
	r.f3 = 1823037858L;
	r.f4 = -10.625;
	r.f5 = 4;
	return r;
}

ulong
f5(S0 a0)
{
	print("in f5\n");
	pS0("a0", a0);
	return 943720397UL;
}

int
f6(float a0, ulong a1, ushort a2, float a3, S0 a4, float a5)
{
	print("in f6\n");
	print("a0 float %g\n", a0);
	print("a1 ulong %lud\n", a1);
	print("a2 ushort %ud\n", a2);
	print("a3 float %g\n", a3);
	pS0("a4", a4);
	print("a5 float %g\n", a5);
	return 1922703414;
}

vlong
f7(long a0, uchar a1, ulong a2, S2 a3, uint a4, short a5, int a6, uchar a7)
{
	print("in f7\n");
	print("a0 long %ld\n", a0);
	print("a1 uchar %ud\n", a1);
	print("a2 ulong %lud\n", a2);
	pS2("a3", a3);
	print("a4 uint %ud\n", a4);
	print("a5 short %d\n", a5);
	print("a6 int %d\n", a6);
	print("a7 uchar %ud\n", a7);
	return -1141479700LL;
}

ushort
f8(S0 a0)
{
	print("in f8\n");
	pS0("a0", a0);
	return 1364;
}

uvlong
f9(char a0, S0 a1, uchar a2, S2 a3, vlong a4, char a5)
{
	print("in f9\n");
	print("a0 char %d\n", a0);
	pS0("a1", a1);
	print("a2 uchar %ud\n", a2);
	pS2("a3", a3);
	print("a4 vlong %lld\n", a4);
	print("a5 char %d\n", a5);
	return 205660197978750ULL;
}

void
vf(int n, ...)
{
	va_list ap;

	va_start(ap, n);
	print("in vf %d\n", n);
	print("v0 %d\n", va_arg(ap, int));
	print("v1 %g\n", va_arg(ap, double));
	print("v2 %llud\n", va_arg(ap, uvlong));
	print("v3 %d\n", va_arg(ap, int));
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
	print("%s S0 %g %d %d %ud %ud %ud %ud %d %d %g %ud %d\n", w, s.f0, s.f1, s.f2, s.f3[0], s.f3[1], s.f3[2], s.f4, s.f5, s.f6, s.f7, s.f8, s.f9);
}

static void
pS1(char *w, S1 s)
{
	print("%s S1 %ud %ud %g\n", w, s.f0, s.f1, s.f2);
}

static void
pS2(char *w, S2 s)
{
	print("%s S2 %ud %ud\n", w, s.f0, s.f1);
}

static void
pS3(char *w, S3 s)
{
	print("%s S3 %llud %lld %ud %ld %g %ud\n", w, s.f0, s.f1, s.f2, s.f3, s.f4, s.f5);
}

static S1
back(S1 x, double d, vlong v)
{
	pS1("back x", x);
	print("back %g %lld\n", d, v);
	x.f0 = x.f0 + 3;
	x.f1 = x.f1 + 3;
	x.f2 = x.f2 * 2;
	return x;
}

void
main(void)
{
	{
	S2 v2;
	int r;
	v2.f0 = 112;
	v2.f1 = 33;
	r = f0((ushort)42564, (vlong)-4610901607509162216LL, v2, (int)1291360678);
	print("ret f0 int %d\n", r);
	}
	{
	S0 v1;
	vlong r;
	v1.f0 = 6.500;
	v1.f1 = 9117;
	v1.f2 = 7502;
	v1.f3[0] = 255;
	v1.f3[1] = 176;
	v1.f3[2] = 97;
	v1.f4 = 18;
	v1.f5 = 32195;
	v1.f6 = 988837748;
	v1.f7 = 15.375;
	v1.f8 = 2002741974U;
	v1.f9 = 25735;
	r = f1((uchar)192, v1);
	print("ret f1 vlong %lld\n", r);
	}
	{
	S3 r;
	r = f2((float)-33.250, (double)-32.125);
	pS3("ret f2", r);
	}
	{
	S3 v0;
	long r;
	v0.f0 = 1010422228257598ULL;
	v0.f1 = 1517371310LL;
	v0.f2 = 47455;
	v0.f3 = 383791888L;
	v0.f4 = 10.875;
	v0.f5 = 114;
	r = f3(v0, (vlong)-4611273973974258260LL, (vlong)918995330LL, (long)1425947443L, (char)-100, (ushort)11925);
	print("ret f3 long %ld\n", r);
	}
	{
	S2 v1;
	S3 r;
	v1.f0 = 219;
	v1.f1 = 140;
	r = f4((ulong)1778303151UL, v1);
	pS3("ret f4", r);
	}
	{
	S0 v0;
	ulong r;
	v0.f0 = 29.375;
	v0.f1 = 19110;
	v0.f2 = -17495;
	v0.f3[0] = 8;
	v0.f3[1] = 185;
	v0.f3[2] = 106;
	v0.f4 = 27;
	v0.f5 = 9420;
	v0.f6 = -1475780221;
	v0.f7 = 38.250;
	v0.f8 = 342200799U;
	v0.f9 = -2960;
	r = f5(v0);
	print("ret f5 ulong %lud\n", r);
	}
	{
	S0 v4;
	int r;
	v4.f0 = -11.250;
	v4.f1 = 25359;
	v4.f2 = -23744;
	v4.f3[0] = 113;
	v4.f3[1] = 34;
	v4.f3[2] = 211;
	v4.f4 = 132;
	v4.f5 = 15669;
	v4.f6 = -307279590;
	v4.f7 = -2.125;
	v4.f8 = 1321183816U;
	v4.f9 = -9209;
	r = f6((float)9.750, (ulong)455206115UL, (ushort)24212, (float)12.375, v4, (float)13.250);
	print("ret f6 int %d\n", r);
	}
	{
	S2 v3;
	vlong r;
	v3.f0 = 60;
	v3.f1 = 237;
	r = f7((long)1314513936L, (uchar)193, (ulong)180934514UL, v3, (uint)687886627U, (short)-19156, (int)1701790853, (uchar)54);
	print("ret f7 vlong %lld\n", r);
	}
	{
	S0 v0;
	ushort r;
	v0.f0 = 18.500;
	v0.f1 = 18477;
	v0.f2 = -16862;
	v0.f3[0] = 143;
	v0.f3[1] = 64;
	v0.f3[2] = 241;
	v0.f4 = 162;
	v0.f5 = 8787;
	v0.f6 = -1906220036;
	v0.f7 = 27.375;
	v0.f8 = 772640614U;
	v0.f9 = -2327;
	r = f8(v0);
	print("ret f8 ushort %ud\n", r);
	}
	{
	S0 v1;
	S2 v3;
	uvlong r;
	v1.f0 = -22.375;
	v1.f1 = 24726;
	v1.f2 = -23111;
	v1.f3[0] = 248;
	v1.f3[1] = 169;
	v1.f3[2] = 90;
	v1.f4 = 11;
	v1.f5 = 15036;
	v1.f6 = -737719405;
	v1.f7 = -13.250;
	v1.f8 = 1751623631U;
	v1.f9 = -8576;
	v3.f0 = 185;
	v3.f1 = 106;
	r = f9((char)13, v1, (uchar)62, v3, (vlong)794224445666196LL, (char)32);
	print("ret f9 uvlong %llud\n", r);
	}
	vf(4, (int)1238001638, (double)-37.125, (uvlong)104422216ULL, (int)611374329);
	{
	S1 x, r;

	x.f0 = 14890;
	x.f1 = 46043;
	x.f2 = -9.500;
	r = cb(back, x);
	pS1("ret cb", r);
	}
	exits(nil);
}
#endif
