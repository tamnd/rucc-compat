/* The SSE class for the scalars that have it, float and double. The first eight go in xmm0 to
 * xmm7, whatever INTEGER arguments sit between them, and the rest go on the stack in the order
 * they were written, interleaved with the INTEGER arguments that overflowed. Each comes back in
 * xmm0. */
#include "abi.h"

void eight(double a, float b, double c, float d, double e, float f, double g, float h);
void twelve(int i0, double a, long i1, float b, double c, int i2, double d, double e, int i3,
            float f, double g, int i4, double h, double i, int i5, float j, int i6, double k,
            int i7, double l);
float give_float(float a, float b);
double give_double(double a, int b, double c);
double back(float a, double b, int c, double d, float e, double f, double g, double h, double i,
            float j);
void callee_side(void);

#ifdef CALLEE
void eight(double a, float b, double c, float d, double e, float f, double g, float h)
{
    printf("eight %a %a %a %a %a %a %a %a\n", a, b, c, d, e, f, g, h);
}

void twelve(int i0, double a, long i1, float b, double c, int i2, double d, double e, int i3,
            float f, double g, int i4, double h, double i, int i5, float j, int i6, double k,
            int i7, double l)
{
    printf("twelve %a %a %a %a %a %a %a %a %a %a %a %a\n", a, b, c, d, e, f, g, h, i, j, k, l);
    printf("twelve ints %d %ld %d %d %d %d %d %d\n", i0, i1, i2, i3, i4, i5, i6, i7);
}

float give_float(float a, float b) { return a * b - 0.5f; }
double give_double(double a, int b, double c) { return a / c + b; }

void callee_side(void)
{
    printf("got %a\n", back(1.5f, -2.25, 3, 1e300, -0.0f, 1e-300, 7, 8, 9, 10.75f));
}
#else
double back(float a, double b, int c, double d, float e, double f, double g, double h, double i,
            float j)
{
    printf("back %a %a %d %a %a %a %a %a %a %a\n", a, b, c, d, e, f, g, h, i, j);
    return a + b + c + g + h + i + j;
}

int main(void)
{
    eight(1.0 / 3, 2.5f, -1e100, 1e-30f, 0.1, -3.75f, 6.0, 7.125f);
    twelve(-1, 1.5, 2, 2.5f, 3.5, -3, 4.5, 5.5, 4, 6.5f, 7.5, 5, 8.5, 9.5, 6, 10.5f, 7, 11.5, 8,
           12.5);
    printf("float %a\n", give_float(1.25f, -3.5f));
    printf("double %a\n", give_double(1.0, 7, 3.0));
    callee_side();
    return 0;
}
#endif
