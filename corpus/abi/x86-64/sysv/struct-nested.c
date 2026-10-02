/* Classification looks through nested aggregates and arrays to the scalars, eightbyte by
 * eightbyte, so a struct inside a struct is classified as if its members were written out. A
 * union merges the classes of its members in each eightbyte, INTEGER winning over SSE. A GNU
 * empty struct has size zero and takes no register at all, so the arguments around it are where
 * they would be without it. */
#include "abi.h"

struct pt { float x, y; };
struct seg { struct pt a; double len; };
struct box { struct pt a, b; };
struct arr { float f[2]; int i; };
struct inner { char c; short s; };
struct outer { struct inner in; int i; struct inner in2; };
union u_if { int i; float f; };
union u_fd { float f; double d; };
union u_dl { double d; long l; };
union u_f2d { float f[2]; double d; };
struct with_union { union u_if a; float b; double c; };
struct empty { };
struct e_i { struct empty e; int i; };

void args(struct seg a, struct box b, struct arr c, struct outer d, union u_if e, union u_fd f,
          union u_dl g, union u_f2d h, struct with_union i);
void empties(int a, struct empty b, double c, struct empty d, int e, struct e_i f);
struct seg give_seg(void);
struct box give_box(float s);
struct outer give_outer(void);
union u_dl give_u_dl(long l);
union u_f2d give_u_f2d(void);
struct with_union give_with_union(void);
struct empty give_empty(int a);
struct box back(struct seg a, union u_fd b, struct empty c, struct arr d);
void callee_side(void);

#ifdef CALLEE
void args(struct seg a, struct box b, struct arr c, struct outer d, union u_if e, union u_fd f,
          union u_dl g, union u_f2d h, struct with_union i)
{
    printf("args %a %a %a %a %a %a %a\n", a.a.x, a.a.y, a.len, b.a.x, b.a.y, b.b.x, b.b.y);
    printf("args %a %a %d %d %d %d %d %d\n", c.f[0], c.f[1], c.i, d.in.c, d.in.s, d.i, d.in2.c,
           d.in2.s);
    printf("args %d %a %ld %a %a %d %a %a\n", e.i, f.d, g.l, h.f[0], h.f[1], i.a.i, i.b, i.c);
}

void empties(int a, struct empty b, double c, struct empty d, int e, struct e_i f)
{
    (void)b;
    (void)d;
    printf("empties %d %a %d %d\n", a, c, e, f.i);
}

struct seg give_seg(void) { return (struct seg){ { 1, 2 }, 3 }; }
struct box give_box(float s) { return (struct box){ { s, -s }, { 2 * s, -2 * s } }; }
struct outer give_outer(void) { return (struct outer){ { 1, -2 }, 3, { -4, 5 } }; }
union u_dl give_u_dl(long l) { union u_dl u; u.l = l; return u; }
union u_f2d give_u_f2d(void) { union u_f2d u; u.f[0] = 0.5f; u.f[1] = -0.5f; return u; }
struct with_union give_with_union(void)
{
    struct with_union w;
    w.a.i = -77;
    w.b = 7.75f;
    w.c = 1e77;
    return w;
}
struct empty give_empty(int a)
{
    printf("give_empty %d\n", a);
    return (struct empty){ };
}

void callee_side(void)
{
    union u_fd u;
    u.d = -2.5;
    struct box r = back((struct seg){ { 0.5f, 1.5f }, 2.5 }, u, (struct empty){ },
                        (struct arr){ { 3, 4 }, 5 });
    printf("got %a %a %a %a\n", r.a.x, r.a.y, r.b.x, r.b.y);
}
#else
struct box back(struct seg a, union u_fd b, struct empty c, struct arr d)
{
    (void)c;
    printf("back %a %a %a %a %a %a %d\n", a.a.x, a.a.y, a.len, b.d, d.f[0], d.f[1], d.i);
    return (struct box){ a.a, { d.f[0], (float)d.i } };
}

int main(void)
{
    union u_if e;
    e.i = 0x40490fdb;
    union u_fd f;
    f.d = 1.0 / 3;
    union u_dl g;
    g.l = -1;
    union u_f2d h;
    h.f[0] = 1.25f;
    h.f[1] = 2.5f;
    struct with_union i;
    i.a.f = 3.0f;
    i.b = 4;
    i.c = 5;
    args((struct seg){ { 1, 2 }, 3 }, (struct box){ { 4, 5 }, { 6, 7 } },
         (struct arr){ { 8, 9 }, 10 }, (struct outer){ { 11, 12 }, 13, { 14, 15 } }, e, f, g, h,
         i);
    empties(1, (struct empty){ }, 2.5, (struct empty){ }, 3, (struct e_i){ { }, 4 });
    struct seg a = give_seg();
    struct box b = give_box(1.5f);
    struct outer c = give_outer();
    union u_dl d = give_u_dl(1L << 60);
    union u_f2d k = give_u_f2d();
    struct with_union w = give_with_union();
    give_empty(9);
    printf("seg %a %a %a box %a %a %a %a\n", a.a.x, a.a.y, a.len, b.a.x, b.a.y, b.b.x, b.b.y);
    printf("outer %d %d %d %d %d u_dl %ld u_f2d %a %a\n", c.in.c, c.in.s, c.i, c.in2.c, c.in2.s,
           d.l, k.f[0], k.f[1]);
    printf("with_union %d %a %a\n", w.a.i, w.b, w.c);
    callee_side();
    return 0;
}
#endif
