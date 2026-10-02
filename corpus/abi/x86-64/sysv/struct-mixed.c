/* Aggregates whose two eightbytes have different classes, and eightbytes that hold an integer and
 * a float together. An eightbyte with any INTEGER in it is INTEGER, so { int, float } is one
 * general register, while { double, int } is an xmm register and then a general one, and
 * { int, double } is the other way round. As results the INTEGER eightbyte comes back in rax and
 * the SSE one in xmm0, whichever of the two is first. */
#include "abi.h"

struct i_f { int a; float b; };
struct f_i { float a; int b; };
struct d_i { double a; int b; };
struct i_d { int a; double b; };
struct l_d { long a; double b; };
struct d_l { double a; long b; };
struct ff_i { float a, b; int c; };
struct i_ff { int a; float b, c; };
struct c_d { char a; double b; };
struct p_f { void *a; float b; };

void args(struct i_f a, struct f_i b, struct d_i c, struct i_d d, struct l_d e, struct d_l f);
void more(struct ff_i a, struct i_ff b, struct c_d c, struct p_f d, double e, long g);
struct i_f give_i_f(void);
struct d_i give_d_i(void);
struct i_d give_i_d(void);
struct l_d give_l_d(long a, double b);
struct d_l give_d_l(void);
struct ff_i give_ff_i(void);
struct i_ff give_i_ff(void);
struct c_d give_c_d(void);
struct d_i back(struct i_d a, struct d_l b, struct ff_i c);
void callee_side(void);

#ifdef CALLEE
void args(struct i_f a, struct f_i b, struct d_i c, struct i_d d, struct l_d e, struct d_l f)
{
    printf("args %d %a %a %d %a %d %d %a %ld %a %a %ld\n", a.a, a.b, b.a, b.b, c.a, c.b, d.a, d.b,
           e.a, e.b, f.a, f.b);
}

void more(struct ff_i a, struct i_ff b, struct c_d c, struct p_f d, double e, long g)
{
    printf("more %a %a %d %d %a %a %d %a %s %a %a %ld\n", a.a, a.b, a.c, b.a, b.b, b.c, c.a, c.b,
           (char *)d.a, d.b, e, g);
}

struct i_f give_i_f(void) { return (struct i_f){ -7, 7.5f }; }
struct d_i give_d_i(void) { return (struct d_i){ 1e-10, -10 }; }
struct i_d give_i_d(void) { return (struct i_d){ 11, -1e11 }; }
struct l_d give_l_d(long a, double b) { return (struct l_d){ a * 2, b * 2 }; }
struct d_l give_d_l(void) { return (struct d_l){ 0.75, 1L << 62 }; }
struct ff_i give_ff_i(void) { return (struct ff_i){ 1.5f, -2.5f, 99 }; }
struct i_ff give_i_ff(void) { return (struct i_ff){ -99, 3.5f, -4.5f }; }
struct c_d give_c_d(void) { return (struct c_d){ 'x', 1.0 / 9 }; }

void callee_side(void)
{
    struct d_i r = back((struct i_d){ 5, 0.5 }, (struct d_l){ -0.5, -5 },
                        (struct ff_i){ 0.1f, 0.2f, 3 });
    printf("got %a %d\n", r.a, r.b);
}
#else
struct d_i back(struct i_d a, struct d_l b, struct ff_i c)
{
    printf("back %d %a %a %ld %a %a %d\n", a.a, a.b, b.a, b.b, c.a, c.b, c.c);
    return (struct d_i){ a.b + b.a + c.a, a.a + (int)b.b + c.c };
}

int main(void)
{
    args((struct i_f){ 1, 2 }, (struct f_i){ 3, 4 }, (struct d_i){ 5, 6 }, (struct i_d){ 7, 8 },
         (struct l_d){ 9, 10 }, (struct d_l){ 11, 12 });
    more((struct ff_i){ 1, 2, 3 }, (struct i_ff){ 4, 5, 6 }, (struct c_d){ 7, 8 },
         (struct p_f){ "nine", 10 }, 11, 12);
    struct i_f a = give_i_f();
    struct d_i b = give_d_i();
    struct i_d c = give_i_d();
    struct l_d d = give_l_d(-3, 0.125);
    struct d_l e = give_d_l();
    struct ff_i f = give_ff_i();
    struct i_ff g = give_i_ff();
    struct c_d h = give_c_d();
    printf("i_f %d %a d_i %a %d i_d %d %a\n", a.a, a.b, b.a, b.b, c.a, c.b);
    printf("l_d %ld %a d_l %a %ld\n", d.a, d.b, e.a, e.b);
    printf("ff_i %a %a %d i_ff %d %a %a c_d %d %a\n", f.a, f.b, f.c, g.a, g.b, g.c, h.a, h.b);
    callee_side();
    return 0;
}
#endif
