/* Vectors of eight and sixteen bytes, the __m64 and __m128 shapes. An eight byte vector is one SSE
 * eightbyte whatever its lanes are and a sixteen byte one is SSE and SSEUP, so both take one xmm
 * register, and both come back in xmm0. A narrower vector is INTEGER, a wider one is MEMORY when
 * there is no AVX to put it in, and a vector inside a struct is classified eightbyte by eightbyte
 * with the rest of it. */
#include "abi.h"
#include <stdarg.h>

typedef float v4f __attribute__((vector_size(16)));
typedef int v4i __attribute__((vector_size(16)));
typedef double v2d __attribute__((vector_size(16)));
typedef short v4s __attribute__((vector_size(8)));
typedef float v2f __attribute__((vector_size(8)));
typedef long v1l __attribute__((vector_size(8)));
typedef char v4c __attribute__((vector_size(4)));
typedef float v8f __attribute__((vector_size(32)));

struct v2f_i { v2f a; int b; };
struct one { v4i a; };
struct two { v2f a, b; };
struct i_v { long a; v2f b; };

void vecs(v4f a, int b, v2d c, v4i d, v4s e, v2f f, double g);
void vec_spilled(v2d a, v2d b, v2d c, v2d d, v2d e, v2d f, v2d g, v2d h, v4i i, double j);
v4f give_v4f(v4f a, v4f b);
v4s give_v4s(v4s a);
v2d back(v4i a, v2f b);
void callee_side(void);
v1l odd(v1l a, v4c b, v8f c, int d);
v8f give_v8f(v8f a);
v4c give_v4c(v4c a);
void inside(struct v2f_i a, struct one b, struct two c, struct i_v d);
struct v2f_i give_v2f_i(void);
struct one give_one(void);
struct two give_two(void);
struct i_v give_i_v(void);
void dots(int n, ...);

#ifdef CALLEE
void vecs(v4f a, int b, v2d c, v4i d, v4s e, v2f f, double g)
{
    printf("vecs %a %a %a %a %d %a %a\n", a[0], a[1], a[2], a[3], b, c[0], c[1]);
    printf("vecs %d %d %d %d %d %d %d %d %a %a %a\n", d[0], d[1], d[2], d[3], e[0], e[1], e[2],
           e[3], f[0], f[1], g);
}

void vec_spilled(v2d a, v2d b, v2d c, v2d d, v2d e, v2d f, v2d g, v2d h, v4i i, double j)
{
    printf("vec_spilled %a %a %a %a %a %a %a %a\n", a[0], b[1], c[0], d[1], e[0], f[1], g[0], h[1]);
    printf("vec_spilled %d %d %d %d %a\n", i[0], i[1], i[2], i[3], j);
}

v4f give_v4f(v4f a, v4f b) { return a * b; }
v4s give_v4s(v4s a) { return a + a; }

v1l odd(v1l a, v4c b, v8f c, int d)
{
    printf("odd %ld %d %d %d %d %a %a %a %d\n", a[0], b[0], b[1], b[2], b[3], c[0], c[4], c[7], d);
    v1l r = { a[0] * 3 + d };
    return r;
}

v8f give_v8f(v8f a) { return a + a; }
v4c give_v4c(v4c a) { return a - 1; }

void inside(struct v2f_i a, struct one b, struct two c, struct i_v d)
{
    printf("inside %a %a %d %d %d %a %a %a %a %ld %a %a\n", a.a[0], a.a[1], a.b, b.a[0], b.a[3],
           c.a[0], c.a[1], c.b[0], c.b[1], d.a, d.b[0], d.b[1]);
}

struct v2f_i give_v2f_i(void) { return (struct v2f_i){ { 1.5f, 2.5f }, -3 }; }
struct one give_one(void) { return (struct one){ { 4, 5, 6, 7 } }; }
struct two give_two(void) { return (struct two){ { 8, 9 }, { 10, 11 } }; }
struct i_v give_i_v(void) { return (struct i_v){ 12, { 13, 14 } }; }

void dots(int n, ...)
{
    va_list ap;
    va_start(ap, n);
    for (int i = 0; i < n; i++) {
        v4f a = va_arg(ap, v4f);
        v2f b = va_arg(ap, v2f);
        printf("dots %a %a %a %a\n", a[0], a[3], b[0], b[1]);
    }
    va_end(ap);
}

void callee_side(void)
{
    v4i a = { 1, -2, 3, -4 };
    v2f b = { 0.5f, -0.25f };
    v2d r = back(a, b);
    printf("got %a %a\n", r[0], r[1]);
}
#else
v2d back(v4i a, v2f b)
{
    printf("back %d %d %d %d %a %a\n", a[0], a[1], a[2], a[3], b[0], b[1]);
    v2d r = { a[0] + b[0], a[3] * b[1] };
    return r;
}

int main(void)
{
    v4f a = { 1.5f, -2, 1e30f, 0.125f };
    v2d c = { 1.0 / 3, -1e300 };
    v4i d = { -1, 2147483647, 0, 42 };
    v4s e = { -300, 1, 300, -2 };
    v2f f = { 3.5f, -0.0f };
    vecs(a, 9, c, d, e, f, 6.5);
    vec_spilled(c, c, c, c, c, c, c, c, d, 7.25);
    v4f p = give_v4f(a, a);
    v4s q = give_v4s(e);
    printf("v4f %a %a %a %a\n", p[0], p[1], p[2], p[3]);
    printf("v4s %d %d %d %d\n", q[0], q[1], q[2], q[3]);
    v1l l = { -5 };
    v4c k = { 1, -2, 3, -4 };
    v8f w = { 1, 2, 3, 4, 5, 6, 7, 8.5f };
    v1l lr = odd(l, k, w, 9);
    v8f wr = give_v8f(w);
    v4c kr = give_v4c(k);
    printf("odd %ld v8f %a %a v4c %d %d\n", lr[0], wr[0], wr[7], kr[0], kr[3]);
    struct v2f_i s1 = { { 0.5f, -0.5f }, 7 };
    struct one s2 = { { -1, -2, -3, -4 } };
    struct two s3 = { { 1, 2 }, { 3, 4 } };
    struct i_v s4 = { -9, { 5, 6 } };
    inside(s1, s2, s3, s4);
    s1 = give_v2f_i();
    s2 = give_one();
    s3 = give_two();
    s4 = give_i_v();
    printf("given %a %d %d %a %a %ld %a\n", s1.a[1], s1.b, s2.a[2], s3.a[1], s3.b[0], s4.a, s4.b[1]);
    /* Ten of each, so the later ones come off the stack rather than the register save area. */
    dots(10, a, f, a, f, a, f, a, f, a, f, a, f, a, f, a, f, a, f, a, f);
    callee_side();
    return 0;
}
#endif
