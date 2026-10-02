/* The complex types. _Complex float is two floats in one eightbyte, so one SSE register.
 * _Complex double is two SSE eightbytes, so two registers, or the stack when fewer than two are
 * left. _Complex long double is COMPLEX_X87, which is MEMORY as an argument and comes back in st0
 * and st1. */
#include "abi.h"

typedef _Complex float cf;
typedef _Complex double cd;
typedef _Complex long double cld;

void args(cf a, cd b, cld c, cf d);
void crowded(double a, double b, double c, double d, double e, double f, double g, cd h, cf i,
             cd j);
cf give_cf(cf a);
cd give_cd(cd a, cd b);
cld give_cld(cld a);
cd back(cf a, cd b, cld c);
void callee_side(void);

#ifdef CALLEE
void args(cf a, cd b, cld c, cf d)
{
    printf("args %a %a %a %a %La %La %a %a\n", __real__ a, __imag__ a, __real__ b, __imag__ b,
           __real__ c, __imag__ c, __real__ d, __imag__ d);
}

void crowded(double a, double b, double c, double d, double e, double f, double g, cd h, cf i,
             cd j)
{
    printf("crowded %a %a %a %a %a %a %a\n", a, b, c, d, e, f, g);
    printf("crowded %a %a %a %a %a %a\n", __real__ h, __imag__ h, __real__ i, __imag__ i,
           __real__ j, __imag__ j);
}

cf give_cf(cf a) { return a * 2; }
cd give_cd(cd a, cd b) { return a + b; }
cld give_cld(cld a) { cld r; __real__ r = __imag__ a; __imag__ r = -__real__ a; return r; }

void callee_side(void)
{
    cf a; __real__ a = 1.5f; __imag__ a = -2.5f;
    cd b; __real__ b = 1e10; __imag__ b = 1e-10;
    cld c; __real__ c = 1.0L / 3; __imag__ c = 3;
    cd r = back(a, b, c);
    printf("got %a %a\n", __real__ r, __imag__ r);
}
#else
cd back(cf a, cd b, cld c)
{
    printf("back %a %a %a %a %La %La\n", __real__ a, __imag__ a, __real__ b, __imag__ b,
           __real__ c, __imag__ c);
    cd r; __real__ r = __real__ b + __imag__ a; __imag__ r = (double)__imag__ c;
    return r;
}

int main(void)
{
    cf a; __real__ a = 0.25f; __imag__ a = -8;
    cd b; __real__ b = 1.0 / 3; __imag__ b = -1e200;
    cld c; __real__ c = 1.0L / 7; __imag__ c = 2e3000L;
    cf d; __real__ d = 3; __imag__ d = 4;
    args(a, b, c, d);
    crowded(1, 2, 3, 4, 5, 6, 7, b, a, b);
    cf r1 = give_cf(a);
    cd r2 = give_cd(b, b);
    cld r3 = give_cld(c);
    printf("cf %a %a\n", __real__ r1, __imag__ r1);
    printf("cd %a %a\n", __real__ r2, __imag__ r2);
    printf("cld %La %La\n", __real__ r3, __imag__ r3);
    callee_side();
    return 0;
}
#endif
