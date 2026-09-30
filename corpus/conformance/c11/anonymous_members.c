// C11 anonymous structures and unions: members reached as if they were the containing record's,
// nested anonymous members, initialization of them, and their effect on size and layout.
#include <stdio.h>
#include <stddef.h>

struct value {
    int kind;
    union {
        long integer;
        double real;
        struct {
            short lo, hi;
        };
    };
};

struct vec {
    union {
        struct { float x, y, z; };
        float v[3];
    };
};

int main(void)
{
    struct value a = { .kind = 1, .integer = 42 };
    struct value b = { 2, { .real = 1.5 } };
    struct value c;
    c.kind = 3;
    c.lo = 7;
    c.hi = 9;
    printf("%d %ld\n", a.kind, a.integer);
    printf("%d %g\n", b.kind, b.real);
    printf("%d %d %d\n", c.kind, c.lo, c.hi);
    printf("%zu %zu\n", offsetof(struct value, real), offsetof(struct value, hi));
    struct vec v = { .x = 1, .y = 2, .z = 3 };
    printf("%g %g %g %zu\n", v.v[0], v.v[1], v.v[2], sizeof v);
    return 0;
}
