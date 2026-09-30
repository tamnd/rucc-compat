// C99 compound literals and designated initializers: array, structure and scalar compound
// literals, their being lvalues, designators for members and elements in any order, nested
// designators, and a designator overriding an earlier initializer.
#include <stdio.h>

struct point { int x, y; };
struct shape { const char *name; struct point at; int sides[4]; };

static int sum(const int *v, int n)
{
    int total = 0;
    for (int i = 0; i < n; i++)
        total += v[i];
    return total;
}

int main(void)
{
    struct point p = { .y = 2, .x = 1 };
    int days[12] = { [1] = 28, [0] = 31, [11] = 31 };
    struct shape s = { .at.y = 7, .name = "sq", .sides = { [3] = 4, [0] = 1 } };
    int over[4] = { 1, 2, 3, 4, [1] = 9 };
    int after[5] = { [2] = 5, 6, 7 };
    printf("%d %d\n", p.x, p.y);
    printf("%d %d %d %d\n", days[0], days[1], days[2], days[11]);
    printf("%s %d %d %d %d\n", s.name, s.at.x, s.at.y, s.sides[0], s.sides[3]);
    printf("%d %d %d\n", over[1], after[3], after[4]);
    printf("%d\n", sum((int[]){ 4, 5, 6 }, 3));
    struct point *q = &(struct point){ 3, 4 };
    q->x += 10;
    printf("%d %d\n", q->x, q->y);
    p = (struct point){ .x = -1 };
    printf("%d %d\n", p.x, p.y);
    int *r = (int[2]){ 0 };
    r[1] = 8;
    printf("%d %d\n", r[0], r[1]);
    printf("%d\n", (int){ 5 } * 2);
    return 0;
}
