/* _BitInt(N) is INTEGER in one eightbyte up to sixty four bits and in two up to a hundred and
 * twenty eight, so it takes one register or a pair, and the stack when the pair is not there.
 * The narrow ones are given values with the top bit of their width set, so a
 * half that reads more bits than the type has gets a different answer. */
#include "abi.h"
#include <stdarg.h>

typedef _BitInt(7) b7;
typedef unsigned _BitInt(37) u37;
typedef _BitInt(64) b64;
typedef _BitInt(65) b65;
typedef unsigned _BitInt(128) u128;
typedef _BitInt(128) b128;


void args(b7 a, u37 b, b64 c, b65 d, u128 e, b128 f, b7 g);
void spilled(long a, long b, long c, long d, long e, b65 f, b7 g);
b7 give_b7(int x);
u37 give_u37(void);
b65 give_b65(b65 a);
u128 give_u128(void);
b128 give_b128(b128 a, int b);
b65 back(b7 a, b128 b, u37 c);
void spilled128(long a, long b, long c, long d, long e, int pad, long s, b128 f, b7 g);
void listed(int n, ...);
void callee_side(void);

#ifdef CALLEE
void args(b7 a, u37 b, b64 c, b65 d, u128 e, b128 f, b7 g)
{
    printf("args %d %llu %lld %d\n", (int)a, (unsigned long long)b, (long long)c, (int)g);
    printf("args d %lld %d\n", (long long)(d >> 1), (int)(d & 1));
    printf("args e %llx %llx\n", (unsigned long long)(e >> 64), (unsigned long long)e);
    printf("args f %lld %lld\n", (long long)(f >> 100), (long long)(f & 0xffffffff));
}

void spilled(long a, long b, long c, long d, long e, b65 f, b7 g)
{
    printf("spilled %ld %ld %ld %ld %ld %lld %d %d\n", a, b, c, d, e, (long long)(f >> 2), (int)(f & 3), (int)g);
}

/* An `__int128` here would sit at the next sixteen byte boundary, and a `_BitInt(128)` is aligned
 * to eight, so a half that used the wrong one reads the eight bytes after it. */
void spilled128(long a, long b, long c, long d, long e, int pad, long s, b128 f, b7 g)
{
    printf("spilled128 %ld %ld %d %ld %lld %lld %d\n", a, e, pad, s, (long long)(f >> 64), (long long)f, (int)g);
}

void listed(int n, ...)
{
    va_list ap;
    va_start(ap, n);
    for (int i = 0; i < n; i++) {
        b65 v = va_arg(ap, b65);
        b7 w = va_arg(ap, b7);
        printf("listed %d %lld %d %d\n", i, (long long)(v >> 1), (int)(v & 1), (int)w);
    }
    va_end(ap);
}

b7 give_b7(int x) { return (b7)x; }
u37 give_u37(void) { return (u37)1 << 36 | 5; }
b65 give_b65(b65 a) { return -a; }
u128 give_u128(void) { return ~(u128)0 / 3; }
b128 give_b128(b128 a, int b) { return a * b; }

void callee_side(void)
{
    b65 r = back(-64, (b128)1 << 120, 99);
    printf("got %lld %d\n", (long long)(r >> 1), (int)(r & 1));
}
#else
b65 back(b7 a, b128 b, u37 c)
{
    printf("back %d %lld %llu\n", (int)a, (long long)(b >> 110), (unsigned long long)c);
    return (b65)a * (b65)c - ((b65)1 << 63);
}

int main(void)
{
    args(-64, (u37)1 << 36, -1, -((b65)1 << 63) * 2, ((u128)1 << 127) | 3, -((b128)7 << 120), 63);
    spilled(1, 2, 3, 4, 5, -((b65)1 << 63) - 5, -1);
    spilled128(1, 2, 3, 4, 5, 6, 7, -((b128)3 << 64) + 9, -2);
    listed(3, (b65)-5, (b7)1, -((b65)1 << 64), (b7)-64, ((b65)1 << 63) + 1, (b7)63);
    printf("b7 %d %d\n", (int)give_b7(-64), (int)give_b7(63));
    printf("u37 %llu\n", (unsigned long long)give_u37());
    b65 a = give_b65((b65)1 << 63);
    printf("b65 %lld %d\n", (long long)(a >> 1), (int)(a & 1));
    u128 b = give_u128();
    printf("u128 %llx %llx\n", (unsigned long long)(b >> 64), (unsigned long long)b);
    b128 c = give_b128(((b128)1 << 120) + 11, -3);
    printf("b128 %lld %lld\n", (long long)(c >> 120), (long long)(c & 0xffff));
    callee_side();
    return 0;
}
#endif
