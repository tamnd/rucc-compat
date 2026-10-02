/* Arguments on the stack keep their own alignment, so a sixteen byte aligned one starts at a
 * sixteen byte boundary and leaves a gap after an eightbyte one before it. The stack is sixteen
 * byte aligned at every call, which a callee that keeps an aligned object on its own frame finds
 * out about. */
#include "abi.h"

struct aligned16 { _Alignas(16) long a; long b; long c; };
struct over { _Alignas(32) char a; };
struct q { __int128 a; };

void gaps(long a, long b, long c, long d, long e, long f, long g, __int128 h, long i,
          long double j, long k, struct q l, long m);
void aligned(int a, struct aligned16 b, int c, struct aligned16 d);
void over(int a, struct over b, int c);
void framed(int a);
void back(long a, long b, long c, long d, long e, long f, long g, __int128 h);
void callee_side(void);

#ifdef CALLEE
void gaps(long a, long b, long c, long d, long e, long f, long g, __int128 h, long i,
          long double j, long k, struct q l, long m)
{
    printf("gaps %ld %ld %ld %ld %ld %ld %ld %llx %ld %La %ld %llx %ld\n", a, b, c, d, e, f, g,
           (unsigned long long)h, i, j, k, (unsigned long long)(l.a >> 64), m);
}

void aligned(int a, struct aligned16 b, int c, struct aligned16 d)
{
    printf("aligned %d %ld %ld %ld %d %ld %ld %ld\n", a, b.a, b.b, b.c, c, d.a, d.b, d.c);
}

void over(int a, struct over b, int c)
{
    printf("over %d %d %d\n", a, b.a, c);
}

void framed(int a)
{
    _Alignas(64) char local[64];
    local[0] = (char)a;
    printf("framed %d %d %d\n", a, local[0], (int)((unsigned long)local % 64));
    if (a > 0)
        framed(a - 1);
}

void callee_side(void)
{
    back(1, 2, 3, 4, 5, 6, 7, (__int128)-8);
}
#else
void back(long a, long b, long c, long d, long e, long f, long g, __int128 h)
{
    _Alignas(32) double here[4] = { 1, 2, 3, 4 };
    printf("back %ld %ld %ld %ld %ld %ld %ld %lld %d\n", a, b, c, d, e, f, g, (long long)h,
           (int)((unsigned long)here % 32));
}

int main(void)
{
    gaps(1, 2, 3, 4, 5, 6, 7, (__int128)8 << 64 | 8, 9, 10.5L, 11, (struct q){ (__int128)12 << 64 },
         13);
    aligned(1, (struct aligned16){ 2, 3, 4 }, 5, (struct aligned16){ 6, 7, 8 });
    over(1, (struct over){ 2 }, 3);
    framed(3);
    callee_side();
    return 0;
}
#endif
