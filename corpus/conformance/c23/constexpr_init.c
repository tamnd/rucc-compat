// C23 constexpr objects and the empty initializer: a constexpr scalar used as a constant
// expression, a constexpr structure, and = {} zeroing a scalar, an array, a structure and a
// variable length array.
#include <stdio.h>

struct pt { int x, y; };

constexpr int size = 4;
constexpr struct pt origin = { 1, 2 };
static int table[size * 2];

int main(void)
{
    constexpr double half = 0.5;
    int a = {};
    int b[3] = {};
    struct pt c = {};
    int n = 3;
    int v[n] = {};
    printf("%zu %d %d %g\n", sizeof table / sizeof table[0], origin.x, origin.y, half);
    printf("%d %d %d %d %d %d\n", a, b[0], b[2], c.x, c.y, v[0] + v[1] + v[2]);
    _Static_assert(size == 4, "constexpr is a constant");
    return 0;
}
