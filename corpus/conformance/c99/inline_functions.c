// C99 inline functions and func: a static inline function, an inline definition with an extern
// declaration giving the external one, and the predefined identifier __func__.
#include <stdio.h>
#include <string.h>

static inline int square(int x) { return x * x; }

inline int cube(int x) { return x * x * x; }
extern int cube(int x);

static const char *name(void) { return __func__; }

int main(void)
{
    int (*f)(int) = cube;
    printf("%d %d %d\n", square(7), cube(3), f(2));
    printf("%s %s %zu\n", name(), __func__, strlen(__func__));
    return 0;
}
