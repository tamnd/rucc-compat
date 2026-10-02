/* long double is X87 and X87UP. As an argument that class is MEMORY, so it goes on the stack in a
 * sixteen byte slot aligned to sixteen whatever registers are free, and as a result it comes back
 * in st0. */
#include "abi.h"

void first(long double a, int b, long double c, double d);
void late(double a, double b, double c, double d, double e, double f, double g, double h,
          double i, long double j, int k, long double l);
long double give(long double a, double b);
double take_back(long double a);
long double back(int a, long double b, long double c);
void callee_side(void);

#ifdef CALLEE
void first(long double a, int b, long double c, double d)
{
    printf("first %La %d %La %a\n", a, b, c, d);
}

void late(double a, double b, double c, double d, double e, double f, double g, double h,
          double i, long double j, int k, long double l)
{
    printf("late %a %a %a %a %a %a %a %a %a %La %d %La\n", a, b, c, d, e, f, g, h, i, j, k, l);
}

long double give(long double a, double b) { return a * b + 1; }
double take_back(long double a) { return (double)(a / 3); }

void callee_side(void)
{
    printf("got %La\n", back(4, 1.0L / 3, -1e4000L));
}
#else
long double back(int a, long double b, long double c)
{
    printf("back %d %La %La\n", a, b, c);
    return b * a + c;
}

int main(void)
{
    first(1.0L / 7, 3, -0x1.123456789abcdefp+1000L, 2.5);
    late(1, 2, 3, 4, 5, 6, 7, 8, 9, 10.25L, 11, 1e-4000L);
    printf("give %La\n", give(1.0L / 3, 3.0));
    printf("take %a\n", take_back(10.0L));
    /* A result in st0 that nobody reads still has to be popped, so call one and drop it, and
     * then make enough calls that a stack the callee forgot to pop would overflow. */
    give(1, 2);
    long double total = 0;
    for (int i = 0; i < 20; i++)
        total += give(i, 0.5);
    printf("total %La\n", total);
    callee_side();
    return 0;
}
#endif
