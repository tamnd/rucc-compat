/* The floating types beyond float and double. _Float16 is SSE, passed in the low two bytes of an
 * xmm register. _Float128 is SSE and SSEUP, one sixteen byte register as an argument, the stack
 * aligned to sixteen when none is left, and xmm0 as a result. */
#include "abi.h"

void halves(_Float16 a, double b, _Float16 c, float d);
_Float16 give_half(_Float16 a, _Float16 b);
void quads(_Float128 a, double b, _Float128 c);
void quad_spilled(double a, double b, double c, double d, double e, double f, double g, double h,
                  _Float128 i, double j);
_Float128 give_quad(_Float128 a, _Float128 b);
_Float128 back(_Float16 a, _Float128 b, double c);
void callee_side(void);

#ifdef CALLEE
void halves(_Float16 a, double b, _Float16 c, float d)
{
    printf("halves %a %a %a %a\n", (double)a, b, (double)c, d);
}

_Float16 give_half(_Float16 a, _Float16 b) { return a * b; }

void quads(_Float128 a, double b, _Float128 c)
{
    bytes("quads a", &a, sizeof a);
    printf("quads b %a\n", b);
    bytes("quads c", &c, sizeof c);
}

void quad_spilled(double a, double b, double c, double d, double e, double f, double g, double h,
                  _Float128 i, double j)
{
    printf("quad_spilled %a %a %a %a %a %a %a %a %a\n", a, b, c, d, e, f, g, h, j);
    bytes("quad_spilled i", &i, sizeof i);
}

_Float128 give_quad(_Float128 a, _Float128 b) { return a / b; }

void callee_side(void)
{
    _Float128 r = back(1.5f16, 1 / (_Float128)3, -4.0);
    bytes("got", &r, sizeof r);
}
#else
_Float128 back(_Float16 a, _Float128 b, double c)
{
    printf("back %a %a\n", (double)a, c);
    bytes("back b", &b, sizeof b);
    return b * c + a;
}

int main(void)
{
    halves(0.5f16, 1e-5, -65504.0f16, 3.25f);
    printf("half %a\n", (double)give_half(1.5f16, -2.25f16));
    _Float128 third = 1 / (_Float128)3;
    quads(third, 2.5, -third * 1000);
    quad_spilled(1, 2, 3, 4, 5, 6, 7, 8, third, 10);
    _Float128 q = give_quad(1, 7);
    bytes("quad", &q, sizeof q);
    callee_side();
    return 0;
}
#endif
