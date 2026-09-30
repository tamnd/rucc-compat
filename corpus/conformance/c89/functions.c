/* C89 functions: prototypes, a definition written the old way with its parameters declared after
 * the list, a call with no prototype in scope and the default argument promotions it gets, a
 * variadic function reading its arguments through <stdarg.h>, recursion, and a function returning
 * a pointer to a function. */
#include <stdio.h>
#include <stdarg.h>

static int add(int, int);
double half();

static int add(int a, int b) { return a + b; }

double half(x)
    double x;
{
    return x / 2;
}

int widen(c, s, f)
    char c;
    short s;
    float f;
{
    return c + s + (int)f;
}

static int sum(int count, ...)
{
    va_list ap;
    int total = 0;
    va_start(ap, count);
    while (count-- > 0)
        total += va_arg(ap, int);
    va_end(ap);
    return total;
}

static double mean(const char *fmt, ...)
{
    va_list ap;
    double total = 0;
    int n = 0;
    va_start(ap, fmt);
    for (; *fmt; fmt++, n++)
        total += *fmt == 'd' ? va_arg(ap, double) : (double)va_arg(ap, int);
    va_end(ap);
    return total / n;
}

static long factorial(int n) { return n <= 1 ? 1 : n * factorial(n - 1); }

static int (*pick(int which))(int, int)
{
    (void)which;
    return add;
}

int main(void)
{
    printf("%d %g\n", add(2, 3), half(9.0));
    printf("%d\n", widen('a', 1000, 2.75f));
    printf("%d %d\n", sum(4, 1, 2, 3, 4), sum(0));
    printf("%g\n", mean("did", 1.5, 2, 4.5));
    printf("%ld\n", factorial(12));
    printf("%d\n", pick(0)(20, 22));
    return 7;
}
