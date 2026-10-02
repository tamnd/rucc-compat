/* Bit-fields are classified by the eightbytes they lie in like any other member, so a struct of
 * bit-fields is one or two INTEGER eightbytes, and a bit-field next to a float makes that
 * eightbyte INTEGER. */
#include "abi.h"

struct small { unsigned a : 3, b : 5, c : 7; };
struct wide { long a : 40; int b : 20; unsigned c : 4; };
struct straddle { unsigned long a : 60, b : 60; };
struct with_float { float f; int a : 4, b : 12; };
struct signed_bits { signed char a : 3; short b : 9; int c : 17; };

void args(struct small a, struct wide b, struct straddle c, struct with_float d,
          struct signed_bits e);
struct small give_small(void);
struct wide give_wide(void);
struct straddle give_straddle(void);
struct with_float give_with_float(void);
struct signed_bits give_signed_bits(int x);
struct wide back(struct small a, struct with_float b);
void callee_side(void);

#ifdef CALLEE
void args(struct small a, struct wide b, struct straddle c, struct with_float d,
          struct signed_bits e)
{
    printf("args %u %u %u %ld %d %u %lx %lx\n", a.a, a.b, a.c, (long)b.a, b.b, b.c,
           (unsigned long)c.a, (unsigned long)c.b);
    printf("args %a %d %d %d %d %d\n", d.f, d.a, d.b, e.a, e.b, e.c);
}

struct small give_small(void) { return (struct small){ 5, 17, 100 }; }
struct wide give_wide(void) { return (struct wide){ -123456789012L, -300000, 9 }; }
struct straddle give_straddle(void)
{
    return (struct straddle){ 0xfedcba987654321UL, 0x123456789abcdefUL };
}
struct with_float give_with_float(void) { return (struct with_float){ -0.75f, -8, 2047 }; }
struct signed_bits give_signed_bits(int x) { return (struct signed_bits){ x, -x * 10, x * 1000 }; }

void callee_side(void)
{
    struct wide r = back((struct small){ 1, 2, 3 }, (struct with_float){ 4.5f, 5, 6 });
    printf("got %ld %d %u\n", (long)r.a, r.b, r.c);
}
#else
struct wide back(struct small a, struct with_float b)
{
    printf("back %u %u %u %a %d %d\n", a.a, a.b, a.c, b.f, b.a, b.b);
    return (struct wide){ (long)a.c << 32, b.b * -100, a.a };
}

int main(void)
{
    args((struct small){ 7, 31, 127 }, (struct wide){ -1, 524287, 15 },
         (struct straddle){ 0xaaaaaaaaaaaaaaaUL, 0x555555555555555UL },
         (struct with_float){ 1e10f, -1, -2048 }, (struct signed_bits){ -4, 255, -65536 });
    struct small a = give_small();
    struct wide b = give_wide();
    struct straddle c = give_straddle();
    struct with_float d = give_with_float();
    struct signed_bits e = give_signed_bits(-3);
    printf("small %u %u %u wide %ld %d %u\n", a.a, a.b, a.c, (long)b.a, b.b, b.c);
    printf("straddle %lx %lx with_float %a %d %d signed %d %d %d\n", (unsigned long)c.a,
           (unsigned long)c.b, d.f, d.a, d.b, e.a, e.b, e.c);
    callee_side();
    return 0;
}
#endif
