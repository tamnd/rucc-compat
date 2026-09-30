/* C89 operators: unary, multiplicative, additive, shifts, relational, equality, bitwise, logical,
 * conditional, assignment and comma, their precedence and associativity, and the order the
 * logical operators and the comma guarantee. */
#include <stdio.h>

static int calls;
static int note(int v) { calls = calls * 10 + v; return v; }

int main(void)
{
    int a = 7, b = -3, x;
    unsigned u = 0xF0F0;
    printf("%d %d %d %d\n", -a, +b, ~a, !a);
    printf("%d %d %d %d\n", a / 2, a % 3, b / 2, b % 2);
    printf("%d %d\n", a * b + 1, a - b - 1);
    printf("%d %d %u\n", 1 << 4, -16 >> 2, u >> 4);
    printf("%d %d %d %d\n", a < b, a >= 7, a == 7, a != 7);
    printf("%d %d %d\n", a & 3, a | 8, a ^ 5);
    printf("%d %d %d\n", 1 + 2 * 3, (1 + 2) * 3, 10 - 4 - 3);
    printf("%d %d\n", 1 < 2 == 1, 6 & 3 == 3);
    calls = 0;
    x = note(0) && note(1);
    printf("%d %d\n", x, calls);
    calls = 0;
    x = note(2) || note(3);
    printf("%d %d\n", x, calls);
    calls = 0;
    x = (note(4), note(5));
    printf("%d %d\n", x, calls);
    printf("%d %d\n", a > b ? a : b, a < 0 ? -1 : a > 0 ? 1 : 0);
    x = a;
    x += 3; printf("%d ", x);
    x -= 1; printf("%d ", x);
    x *= 2; printf("%d ", x);
    x /= 3; printf("%d ", x);
    x %= 4; printf("%d ", x);
    x <<= 3; printf("%d ", x);
    x >>= 1; printf("%d ", x);
    x &= 6; printf("%d ", x);
    x |= 9; printf("%d ", x);
    x ^= 3; printf("%d\n", x);
    a = b = 4;
    printf("%d %d\n", a, b);
    return 0;
}
