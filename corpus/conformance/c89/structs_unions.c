/* C89 structures and unions: members and their order, nesting, assignment and passing by value,
 * a union's members sharing storage, offsetof, and a pointer to a structure through ->. */
#include <stdio.h>
#include <stddef.h>

struct point { int x, y; };
struct rect { struct point lo, hi; char name[8]; };
union word { unsigned int u; unsigned char b[sizeof(unsigned int)]; };

static struct point shift(struct point p, int by)
{
    p.x += by;
    p.y += by;
    return p;
}

static int area(const struct rect *r)
{
    return (r->hi.x - r->lo.x) * (r->hi.y - r->lo.y);
}

int main(void)
{
    struct rect r;
    struct point a, b;
    union word w;
    struct { int tag; union { int i; double d; } v; } tagged;
    r.lo.x = 1; r.lo.y = 2; r.hi.x = 4; r.hi.y = 6;
    sprintf(r.name, "box");
    printf("%d %s\n", area(&r), r.name);
    a = r.lo;
    b = shift(a, 10);
    printf("%d %d %d %d\n", a.x, a.y, b.x, b.y);
    r.hi = b;
    printf("%d\n", area(&r));
    w.u = 0;
    w.b[0] = 1;
    printf("%d %lu\n", w.u == 1 || w.u == 1u << (8 * (sizeof w.u - 1)), (unsigned long)sizeof w);
    tagged.tag = 1;
    tagged.v.d = 2.5;
    printf("%d %g %lu\n", tagged.tag, tagged.v.d, (unsigned long)sizeof tagged.v);
    printf("%lu %lu %lu\n", (unsigned long)offsetof(struct rect, lo), (unsigned long)offsetof(struct rect, hi), (unsigned long)offsetof(struct rect, name));
    printf("%d\n", &r.lo.x == (int *)&r);
    return 0;
}
