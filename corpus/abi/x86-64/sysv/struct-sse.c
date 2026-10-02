/* Aggregates whose eightbytes are all SSE. Two floats share one eightbyte and one register, a
 * third float starts a second eightbyte, and two doubles take two registers. As results they come
 * back in xmm0 and xmm1. */
#include "abi.h"

struct f1 { float a; };
struct f2 { float a, b; };
struct f3 { float a, b, c; };
struct f4 { float a, b, c, d; };
struct d1 { double a; };
struct d2 { double a, b; };
struct fd { float a, b; double c; };
struct df { double a; float b; };
struct fa { float a[3]; };

void args(struct f1 a, struct f2 b, struct f3 c, struct f4 d, struct d1 e, struct d2 f);
void more(struct fd a, struct df b, struct fa c, double d);
struct f1 give_f1(void);
struct f2 give_f2(float x);
struct f3 give_f3(void);
struct f4 give_f4(void);
struct d2 give_d2(double a, double b);
struct fd give_fd(void);
struct df give_df(void);
struct f3 back(struct f3 a, struct d2 b);
void callee_side(void);

#ifdef CALLEE
void args(struct f1 a, struct f2 b, struct f3 c, struct f4 d, struct d1 e, struct d2 f)
{
    printf("args %a %a %a %a %a %a\n", a.a, b.a, b.b, c.a, c.b, c.c);
    printf("args %a %a %a %a %a %a %a\n", d.a, d.b, d.c, d.d, e.a, f.a, f.b);
}

void more(struct fd a, struct df b, struct fa c, double d)
{
    printf("more %a %a %a %a %a %a %a %a %a\n", a.a, a.b, a.c, b.a, b.b, c.a[0], c.a[1], c.a[2], d);
}

struct f1 give_f1(void) { return (struct f1){ -1.5f }; }
struct f2 give_f2(float x) { return (struct f2){ x, -x }; }
struct f3 give_f3(void) { return (struct f3){ 1, 2, 3 }; }
struct f4 give_f4(void) { return (struct f4){ 0.5f, 0.25f, 0.125f, -8 }; }
struct d2 give_d2(double a, double b) { return (struct d2){ b, a }; }
struct fd give_fd(void) { return (struct fd){ 1.25f, 2.5f, 1e-300 }; }
struct df give_df(void) { return (struct df){ -1e300, 3.75f }; }

void callee_side(void)
{
    struct f3 r = back((struct f3){ 1, -1, 0.5f }, (struct d2){ 1.0 / 3, 2.0 / 3 });
    printf("got %a %a %a\n", r.a, r.b, r.c);
}
#else
struct f3 back(struct f3 a, struct d2 b)
{
    printf("back %a %a %a %a %a\n", a.a, a.b, a.c, b.a, b.b);
    return (struct f3){ a.c, (float)b.b, a.a };
}

int main(void)
{
    args((struct f1){ 0.1f }, (struct f2){ 1, -2 }, (struct f3){ 3, 4, 5 },
         (struct f4){ 6, 7, 8, 9 }, (struct d1){ 1.0 / 3 }, (struct d2){ -1e100, 1e-100 });
    more((struct fd){ 1, 2, 3 }, (struct df){ 4, 5 }, (struct fa){ { 6, 7, 8 } }, 9);
    struct f2 r2 = give_f2(7.5f);
    struct f3 r3 = give_f3();
    struct f4 r4 = give_f4();
    struct d2 rd = give_d2(1, 2);
    struct fd rfd = give_fd();
    struct df rdf = give_df();
    printf("f1 %a f2 %a %a\n", give_f1().a, r2.a, r2.b);
    printf("f3 %a %a %a f4 %a %a %a %a\n", r3.a, r3.b, r3.c, r4.a, r4.b, r4.c, r4.d);
    printf("d2 %a %a fd %a %a %a df %a %a\n", rd.a, rd.b, rfd.a, rfd.b, rfd.c, rdf.a, rdf.b);
    callee_side();
    return 0;
}
#endif
