/* Aggregates whose class is MEMORY. Anything over sixteen bytes, anything with a member that is
 * not at its natural alignment, and anything holding a long double. As an argument the whole
 * object is copied to the stack, and as a result the caller passes the address to write it to in
 * rdi and gets the same address back in rax, which shifts every other argument over by one. */
#include "abi.h"

struct big { long a, b, c; };
struct bigd { double a, b, c, d; };
struct mixed24 { int a; double b; char c; };
struct __attribute__((packed)) packed { char a; int b; };
struct __attribute__((packed)) packed16 { char a; long b; char c[7]; };
struct withld { long double a; };
struct ld_i { int a; long double b; };
struct huge { char a[100]; };

void args(struct big a, int b, struct bigd c, double d, struct mixed24 e, struct packed f,
          struct packed16 g, struct withld h, struct ld_i i, struct huge j, long k);
struct big give_big(long a, long b, long c);
struct bigd give_bigd(double a);
struct mixed24 give_mixed24(int a, double b, char c);
struct packed give_packed(void);
struct packed16 give_packed16(void);
struct withld give_withld(void);
struct huge give_huge(char c);
struct big back(struct bigd a, int b, struct packed c);
void callee_side(void);

#ifdef CALLEE
void args(struct big a, int b, struct bigd c, double d, struct mixed24 e, struct packed f,
          struct packed16 g, struct withld h, struct ld_i i, struct huge j, long k)
{
    printf("args %ld %ld %ld %d %a %a %a %a %a\n", a.a, a.b, a.c, b, c.a, c.b, c.c, c.d, d);
    printf("args %d %a %d %d %d %d %ld %d\n", e.a, e.b, e.c, f.a, f.b, g.a, g.b, g.c[6]);
    printf("args %La %d %La %d %d %ld\n", h.a, i.a, i.b, j.a[0], j.a[99], k);
}

struct big give_big(long a, long b, long c) { return (struct big){ c, b, a }; }
struct bigd give_bigd(double a) { return (struct bigd){ a, a * 2, a * 3, a * 4 }; }
struct mixed24 give_mixed24(int a, double b, char c) { return (struct mixed24){ a, b, c }; }
struct packed give_packed(void) { return (struct packed){ 'p', -123456789 }; }
struct packed16 give_packed16(void)
{
    return (struct packed16){ 'q', -1L << 50, { 1, 2, 3, 4, 5, 6, 7 } };
}
struct withld give_withld(void) { return (struct withld){ 1.0L / 3 }; }
struct huge give_huge(char c)
{
    struct huge h;
    for (int i = 0; i < 100; i++)
        h.a[i] = (char)(c + i);
    return h;
}

void callee_side(void)
{
    struct big r = back((struct bigd){ 1, 2, 3, 4 }, 5, (struct packed){ 6, 7 });
    printf("got %ld %ld %ld\n", r.a, r.b, r.c);
}
#else
struct big back(struct bigd a, int b, struct packed c)
{
    printf("back %a %a %a %a %d %d %d\n", a.a, a.b, a.c, a.d, b, c.a, c.b);
    return (struct big){ (long)a.a + b, (long)a.d * c.b, c.a };
}

int main(void)
{
    struct huge j;
    for (int i = 0; i < 100; i++)
        j.a[i] = (char)(i * 3);
    args((struct big){ 1, -2, 3 }, 4, (struct bigd){ 0.5, 1.5, 2.5, 3.5 }, 4.5,
         (struct mixed24){ -5, 5.5, 'm' }, (struct packed){ 'c', 0x12345678 },
         (struct packed16){ 'd', 1L << 40, { 0, 0, 0, 0, 0, 0, -6 } }, (struct withld){ 1e-4000L },
         (struct ld_i){ 6, -6.25L }, j, 7);
    struct big a = give_big(1, 2, 3);
    struct bigd b = give_bigd(0.1);
    struct mixed24 c = give_mixed24(8, 8.5, 'z');
    struct packed d = give_packed();
    struct packed16 e = give_packed16();
    struct withld f = give_withld();
    struct huge g = give_huge(-10);
    printf("big %ld %ld %ld bigd %a %a %a %a\n", a.a, a.b, a.c, b.a, b.b, b.c, b.d);
    printf("mixed24 %d %a %c packed %c %d\n", c.a, c.b, c.c, d.a, d.b);
    printf("packed16 %c %ld %d withld %La huge %d %d\n", e.a, e.b, e.c[6], f.a, g.a[0], g.a[99]);
    /* Passed straight on, so the hidden pointer of one call is an argument of the next. */
    struct big h = give_big(give_bigd(2).b, give_mixed24(1, 2, 3).a, give_huge(5).a[50]);
    printf("chained %ld %ld %ld\n", h.a, h.b, h.c);
    callee_side();
    return 0;
}
#endif
