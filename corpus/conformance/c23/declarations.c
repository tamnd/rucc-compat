// C23 declarations: labels before a declaration and at the end of a block, unnamed parameters
// in a definition, a variadic function with no named parameter, a function declared with () now
// taking no arguments, an enumeration with a fixed underlying type, enumerators wider than int,
// and a structure tag redeclared with the same members being the same type.
#include <stdio.h>
#include <stdarg.h>

enum small : unsigned char { A = 1, B = 200 };
enum big { HUGE_ONE = 0x100000000 };

static int ignore_second(int a, int) { return a; }

static int sum(...)
{
    va_list ap;
    va_start(ap);
    int n = va_arg(ap, int);
    int total = 0;
    for (int i = 0; i < n; i++)
        total += va_arg(ap, int);
    va_end(ap);
    return total;
}

static int nothing() { return 9; }

struct tagged { int a; };
struct tagged { int a; };

static int use(struct tagged t) { return t.a; }

int main(void)
{
    int n = 0;
again:
    int x = n * 2;
    if (++n < 3)
        goto again;
    printf("%d %d\n", x, ignore_second(4, 5));
    printf("%d %d\n", sum(3, 1, 2, 3), nothing());
    printf("%zu %d %zu\n", sizeof(enum small), B, sizeof(enum big));
    printf("%d\n", use((struct tagged){ 5 }));
    {
        goto done;
    done:
    }
    return 0;
}
