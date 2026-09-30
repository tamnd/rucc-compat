/* C89 pointers: address and indirection, arrays turning into pointers to their first element, a
 * function name turning into a pointer to the function, arithmetic and differences, comparison,
 * the null pointer constant and conversions through void *. */
#include <stdio.h>
#include <stddef.h>

static int twice(int x) { return 2 * x; }

int main(void)
{
    int a[5];
    int *p = a, *q;
    int **pp = &p;
    void *v;
    int (*fn)(int) = twice;
    int (*row)[5] = &a;
    char c = 'x';
    ptrdiff_t diff;
    int i;
    for (i = 0; i < 5; i++)
        a[i] = i * i;
    q = &a[4];
    diff = q - p;
    printf("%d %d %d\n", *p, *(p + 2), p[3]);
    printf("%d %d\n", 3[a], *(a + 1));
    printf("%ld %d %d\n", (long)diff, q > p, p + 4 == q);
    printf("%d %d\n", **pp, (*row)[2]);
    printf("%d %d %d\n", fn(21), (*fn)(4), (**fn)(5));
    v = &c;
    printf("%c\n", *(char *)v);
    p = 0;
    printf("%d %d\n", p == NULL, !p);
    v = a;
    q = v;
    printf("%d\n", q[4]);
    printf("%lu\n", (unsigned long)(sizeof a / sizeof a[0]));
    printf("%d\n", (char *)&a[1] - (char *)&a[0] == (int)sizeof(int));
    return 0;
}
