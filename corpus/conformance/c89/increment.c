/* C89 increment and decrement: prefix and postfix forms on integers, on pointers and on members,
 * and the value each expression has. */
#include <stdio.h>

struct counter { int n; };

int main(void)
{
    int i = 5, j;
    int a[3];
    int *p = a;
    struct counter c;
    struct counter *cp = &c;
    double d = 1.5;
    a[0] = 10; a[1] = 20; a[2] = 30;
    j = i++; printf("%d %d\n", i, j);
    j = ++i; printf("%d %d\n", i, j);
    j = i--; printf("%d %d\n", i, j);
    j = --i; printf("%d %d\n", i, j);
    printf("%d ", *p++);
    printf("%d ", *++p);
    printf("%d\n", (*p)--);
    printf("%d %d\n", a[2], a[1]);
    c.n = 0;
    c.n++;
    ++cp->n;
    cp->n++;
    printf("%d\n", c.n);
    d++;
    printf("%g\n", d);
    return 0;
}
