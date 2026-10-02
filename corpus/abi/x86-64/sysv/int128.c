/* __int128 is two INTEGER eightbytes and takes a register pair, or the stack aligned to sixteen
 * when only one register is left, in which case the register it did not take goes to the next
 * argument that fits. It comes back in rax and rdx. */
#include "abi.h"

typedef __int128 i128;
typedef unsigned __int128 u128;

static void wide(const char *what, u128 v)
{
    printf("%s %016llx%016llx\n", what, (unsigned long long)(v >> 64), (unsigned long long)v);
}

void pair(i128 a, u128 b);
void fifth(long a, long b, long c, long d, long e, i128 f, long g);
void spilled(long a, long b, long c, long d, long e, long f, i128 g, long h, i128 i);
i128 sum(i128 a, i128 b);
u128 across(int a, u128 b, int c);
i128 back(long a, i128 b);
void callee_side(void);

#ifdef CALLEE
void pair(i128 a, u128 b) { wide("pair a", a); wide("pair b", b); }

void fifth(long a, long b, long c, long d, long e, i128 f, long g)
{
    printf("fifth %ld %ld %ld %ld %ld %ld\n", a, b, c, d, e, g);
    wide("fifth f", f);
}

void spilled(long a, long b, long c, long d, long e, long f, i128 g, long h, i128 i)
{
    printf("spilled %ld %ld %ld %ld %ld %ld %ld\n", a, b, c, d, e, f, h);
    wide("spilled g", g);
    wide("spilled i", i);
}

i128 sum(i128 a, i128 b) { return a + b; }
u128 across(int a, u128 b, int c) { return b * 3 + (u128)a + (u128)c; }

void callee_side(void)
{
    i128 v = back(-1, ((i128)1 << 100) - 12345);
    wide("got", v);
}
#else
i128 back(long a, i128 b)
{
    printf("back %ld\n", a);
    wide("back b", b);
    return b * a;
}

int main(void)
{
    i128 big = ((i128)0x0123456789abcdefLL << 64) | 0xfedcba9876543210ULL;
    pair(big, ~(u128)0 - 5);
    fifth(1, 2, 3, 4, 5, -big, 7);
    spilled(1, 2, 3, 4, 5, 6, big, 8, (i128)-1);
    wide("sum", sum(big, big));
    wide("across", across(-1, ((u128)1 << 127) | 9, 100));
    callee_side();
    return 0;
}
#endif
