/* C89 qualifiers and storage classes: const and volatile objects and pointers, a static local that
 * keeps its value between calls, a file scope static, extern, register and auto, and typedef. */
#include <stdio.h>

typedef unsigned long ulong;
typedef int pair[2];
typedef int (*binop)(int, int);

static int hidden = 40;
int shared;
extern int shared;

static int counter(void)
{
    static int n = 0;
    auto int step = 1;
    n += step;
    return n;
}

static int add(int a, int b) { return a + b; }

int main(void)
{
    const int k = 7;
    const int *pc = &k;
    int x = 1;
    int *const cp = &x;
    volatile int v = 3;
    register int r = 5;
    ulong big = 3000000000UL;
    pair p;
    binop op = add;
    counter();
    counter();
    printf("%d\n", counter());
    *cp = 9;
    printf("%d %d %d\n", *pc, x, v + r);
    v = v * 2;
    printf("%d\n", v);
    shared = hidden + 2;
    printf("%d %lu\n", shared, big);
    p[0] = 1; p[1] = 2;
    printf("%d %lu\n", op(p[0], p[1]), (unsigned long)sizeof(pair));
    return 0;
}
