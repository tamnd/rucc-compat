/* A variadic call passes its arguments by the same classification and also says in al how many
 * xmm registers it used, and va_arg in the callee has to find each one again in the register save
 * area or the overflow area, which for an aggregate means reading it back from both kinds of
 * register or from the stack. */
#include "abi.h"
#include <stdarg.h>

struct ll { long a, b; };
struct dd { double a, b; };
struct ld { long a; double b; };
struct f2 { float a, b; };
struct big { long a, b, c; };
struct s3 { char a, b, c; };

void many(const char *kinds, ...);
double sum(int n, ...);
long back(int n, ...);
void callee_side(void);

#ifdef CALLEE
void many(const char *kinds, ...)
{
    va_list ap;
    va_start(ap, kinds);
    for (const char *k = kinds; *k; k++) {
        switch (*k) {
        case 'i': printf(" i %d", va_arg(ap, int)); break;
        case 'l': printf(" l %ld", va_arg(ap, long)); break;
        case 'd': printf(" d %a", va_arg(ap, double)); break;
        case 'L': printf(" L %La", va_arg(ap, long double)); break;
        case 'q': {
            __int128 v = va_arg(ap, __int128);
            printf(" q %llx %llx", (unsigned long long)(v >> 64), (unsigned long long)v);
            break;
        }
        case 'a': { struct ll v = va_arg(ap, struct ll); printf(" ll %ld %ld", v.a, v.b); break; }
        case 'b': { struct dd v = va_arg(ap, struct dd); printf(" dd %a %a", v.a, v.b); break; }
        case 'c': { struct ld v = va_arg(ap, struct ld); printf(" ld %ld %a", v.a, v.b); break; }
        case 'e': { struct f2 v = va_arg(ap, struct f2); printf(" f2 %a %a", v.a, v.b); break; }
        case 'g': {
            struct big v = va_arg(ap, struct big);
            printf(" big %ld %ld %ld", v.a, v.b, v.c);
            break;
        }
        case 'h': {
            struct s3 v = va_arg(ap, struct s3);
            printf(" s3 %d %d %d", v.a, v.b, v.c);
            break;
        }
        case 'p': printf(" p %s", va_arg(ap, char *)); break;
        }
    }
    va_end(ap);
    printf("\n");
}

double sum(int n, ...)
{
    va_list ap, again;
    va_start(ap, n);
    va_copy(again, ap);
    double total = 0;
    for (int i = 0; i < n; i++)
        total += va_arg(ap, double);
    for (int i = 0; i < n; i++)
        total -= va_arg(again, double) / 2;
    va_end(again);
    va_end(ap);
    return total;
}

void callee_side(void)
{
    printf("got %ld\n", back(3, 1.5, (struct ld){ 2, 2.5 }, (struct ll){ 3, 4 }));
    printf("got %ld\n", back(0));
}
#else
long back(int n, ...)
{
    va_list ap;
    va_start(ap, n);
    long r = n;
    if (n) {
        double a = va_arg(ap, double);
        struct ld b = va_arg(ap, struct ld);
        struct ll c = va_arg(ap, struct ll);
        printf("back %a %ld %a %ld %ld\n", a, b.a, b.b, c.a, c.b);
        r += (long)(a * 2) + b.a + c.b;
    }
    va_end(ap);
    return r;
}

int main(void)
{
    struct ll a = { -1, 1 };
    struct dd b = { 0.5, -0.5 };
    struct ld c = { 3, 3.5 };
    struct f2 e = { 1.25f, -1.25f };
    struct big g = { 7, 8, 9 };
    struct s3 h = { 1, -2, 3 };
    __int128 q = ((__int128)0x1122334455667788LL << 64) | 0x99aabbccddeeff00ULL;
    many("ildLq", 1, 2L, 3.0, 4.0L, q);
    many("abcegh", a, b, c, e, g, h);
    /* Enough of each kind that some land in registers and the rest in the overflow area, and
     * aggregates that straddle the point where the registers run out. */
    many("ddddddddddd", 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0);
    many("llllaclbbdd", 1L, 2L, 3L, 4L, a, c, 5L, b, b, 6.0, 7.0);
    many("pbbbbcLqaa", "text", b, b, b, b, c, 8.0L, q, a, a);
    printf("sum %a\n", sum(10, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.5));
    callee_side();
    return 0;
}
#endif
