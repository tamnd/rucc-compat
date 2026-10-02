/* What happens when the registers run out part way. An aggregate takes all of its registers or
 * none: when it needs two general registers and one is left, the whole of it goes on the stack,
 * and the register it did not take is still free for the next argument that fits in one. The
 * same holds for the xmm registers, and for a struct that needs one of each when only one kind is
 * left. */
#include "abi.h"

struct ll { long a, b; };
struct dd { double a, b; };
struct ld { long a; double b; };
struct l { long a; };

void ints(long a, long b, long c, long d, long e, struct ll f, long g, struct l h, long i);
void sses(double a, double b, double c, double d, double e, double f, double g, struct dd h,
          double i, struct dd j);
void mixed_out_of_int(long a, long b, long c, long d, long e, long f, struct ld g, double h,
                      long i);
void mixed_out_of_sse(double a, double b, double c, double d, double e, double f, double g,
                      double h, struct ld i, long j, double k);
void split(long a, long b, long c, long d, struct ld e, struct ld f, double g);
struct ll back(long a, long b, long c, long d, long e, struct ll f, long g);
void callee_side(void);

#ifdef CALLEE
void ints(long a, long b, long c, long d, long e, struct ll f, long g, struct l h, long i)
{
    printf("ints %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld\n", a, b, c, d, e, f.a, f.b, g, h.a, i);
}

void sses(double a, double b, double c, double d, double e, double f, double g, struct dd h,
          double i, struct dd j)
{
    printf("sses %a %a %a %a %a %a %a %a %a %a %a %a\n", a, b, c, d, e, f, g, h.a, h.b, i, j.a,
           j.b);
}

void mixed_out_of_int(long a, long b, long c, long d, long e, long f, struct ld g, double h,
                      long i)
{
    printf("mixed_out_of_int %ld %ld %ld %ld %ld %ld %ld %a %a %ld\n", a, b, c, d, e, f, g.a, g.b,
           h, i);
}

void mixed_out_of_sse(double a, double b, double c, double d, double e, double f, double g,
                      double h, struct ld i, long j, double k)
{
    printf("mixed_out_of_sse %a %a %a %a %a %a %a %a %ld %a %ld %a\n", a, b, c, d, e, f, g, h,
           i.a, i.b, j, k);
}

void split(long a, long b, long c, long d, struct ld e, struct ld f, double g)
{
    printf("split %ld %ld %ld %ld %ld %a %ld %a %a\n", a, b, c, d, e.a, e.b, f.a, f.b, g);
}

void callee_side(void)
{
    struct ll r = back(1, 2, 3, 4, 5, (struct ll){ 6, 7 }, 8);
    printf("got %ld %ld\n", r.a, r.b);
}
#else
struct ll back(long a, long b, long c, long d, long e, struct ll f, long g)
{
    printf("back %ld %ld %ld %ld %ld %ld %ld %ld\n", a, b, c, d, e, f.a, f.b, g);
    return (struct ll){ a + g, f.a * f.b };
}

int main(void)
{
    ints(1, 2, 3, 4, 5, (struct ll){ 6, 7 }, 8, (struct l){ 9 }, 10);
    sses(1, 2, 3, 4, 5, 6, 7, (struct dd){ 8, 9 }, 10, (struct dd){ 11, 12 });
    mixed_out_of_int(1, 2, 3, 4, 5, 6, (struct ld){ 7, 8 }, 9, 10);
    mixed_out_of_sse(1, 2, 3, 4, 5, 6, 7, 8, (struct ld){ 9, 10 }, 11, 12);
    split(1, 2, 3, 4, (struct ld){ 5, 6 }, (struct ld){ 7, 8 }, 9);
    callee_side();
    return 0;
}
#endif
