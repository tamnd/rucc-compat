/* Aggregates of sixteen bytes or less whose eightbytes are all INTEGER. Every size from one byte
 * to sixteen, since a struct of three or five or seven bytes is the one that finds a half that
 * moves a whole register where it should move part of one. One eightbyte takes one register and
 * two take two, and the same goes for the result, in rax and then rdx. */
#include "abi.h"

struct s1 { char a; };
struct s2 { short a; };
struct s3 { char a, b, c; };
struct s4 { int a; };
struct s5 { char a[5]; };
struct s6 { short a, b, c; };
struct s7 { char a[7]; };
struct s8 { long a; };
struct s9 { char a[9]; };
struct s12 { int a, b, c; };
struct s15 { char a[15]; };
struct s16 { long a, b; };
struct sp { char *p; int i; };
/* A flexible array member adds nothing to the size, so this is one INTEGER eightbyte. */
struct flex { long n; int data[]; };

void small(struct s1 a, struct s2 b, struct s3 c, struct s4 d, struct s5 e, struct s6 f);
void larger(struct s7 a, struct s8 b, struct s9 c, struct s12 d);
void sixteen(struct s15 a, struct s16 b, struct sp c, struct flex d);
struct s1 give1(void);
struct s3 give3(char x);
struct s5 give5(void);
struct s7 give7(void);
struct s9 give9(void);
struct s12 give12(int x);
struct s15 give15(void);
struct s16 give16(long a, long b);
struct s7 back(struct s3 a, struct s9 b, struct s15 c);
void callee_side(void);

static void show(const char *what, const char *p, int n)
{
    printf("%s", what);
    for (int i = 0; i < n; i++)
        printf(" %d", p[i]);
    printf("\n");
}

#ifdef CALLEE
void small(struct s1 a, struct s2 b, struct s3 c, struct s4 d, struct s5 e, struct s6 f)
{
    printf("small %d %d %d %d %d %d\n", a.a, b.a, c.a, c.b, c.c, d.a);
    show("small e", e.a, 5);
    printf("small f %d %d %d\n", f.a, f.b, f.c);
}

void larger(struct s7 a, struct s8 b, struct s9 c, struct s12 d)
{
    show("larger a", a.a, 7);
    printf("larger b %ld\n", b.a);
    show("larger c", c.a, 9);
    printf("larger d %d %d %d\n", d.a, d.b, d.c);
}

void sixteen(struct s15 a, struct s16 b, struct sp c, struct flex d)
{
    show("sixteen a", a.a, 15);
    printf("sixteen %ld %ld %s %d %ld\n", b.a, b.b, c.p, c.i, d.n);
}

struct s1 give1(void) { return (struct s1){ -9 }; }
struct s3 give3(char x) { return (struct s3){ x, -x, 2 * x }; }
struct s5 give5(void) { return (struct s5){ { 1, -2, 3, -4, 5 } }; }
struct s7 give7(void) { return (struct s7){ { 7, 6, 5, 4, 3, 2, -1 } }; }
struct s9 give9(void) { return (struct s9){ { 9, 8, 7, 6, 5, 4, 3, 2, -1 } }; }
struct s12 give12(int x) { return (struct s12){ x, x + 1, -x }; }
struct s15 give15(void)
{
    struct s15 r;
    for (int i = 0; i < 15; i++)
        r.a[i] = 100 - i * 13;
    return r;
}
struct s16 give16(long a, long b) { return (struct s16){ b, a }; }

void callee_side(void)
{
    struct s3 a = { 1, 2, 3 };
    struct s9 b = { { -1, -2, -3, -4, -5, -6, -7, -8, -9 } };
    struct s15 c = give15();
    show("got", back(a, b, c).a, 7);
}
#else
struct s7 back(struct s3 a, struct s9 b, struct s15 c)
{
    printf("back %d %d %d\n", a.a, a.b, a.c);
    show("back b", b.a, 9);
    show("back c", c.a, 15);
    struct s7 r = { { a.a, a.b, a.c, b.a[0], b.a[8], c.a[0], c.a[14] } };
    return r;
}

int main(void)
{
    struct s5 e = { { -1, 2, -3, 4, -5 } };
    small((struct s1){ -128 }, (struct s2){ -32768 }, (struct s3){ 1, -1, 127 },
          (struct s4){ -123456 }, e, (struct s6){ -1, 0, 32767 });
    struct s7 a7 = { { 1, 2, 3, 4, 5, 6, 7 } };
    struct s9 a9 = { { -9, -8, -7, -6, -5, -4, -3, -2, -1 } };
    larger(a7, (struct s8){ -5000000000L }, a9, (struct s12){ 1, -2, 3 });
    struct s15 a15;
    for (int i = 0; i < 15; i++)
        a15.a[i] = i * 7 - 50;
    sixteen(a15, (struct s16){ 1L << 50, -3 }, (struct sp){ "pointer", -11 }, (struct flex){ 77 });
    printf("give1 %d\n", give1().a);
    struct s3 r3 = give3(-20);
    printf("give3 %d %d %d\n", r3.a, r3.b, r3.c);
    show("give5", give5().a, 5);
    show("give7", give7().a, 7);
    show("give9", give9().a, 9);
    struct s12 r12 = give12(-40);
    printf("give12 %d %d %d\n", r12.a, r12.b, r12.c);
    show("give15", give15().a, 15);
    struct s16 r16 = give16(11, -22);
    printf("give16 %ld %ld\n", r16.a, r16.b);
    callee_side();
    return 0;
}
#endif
