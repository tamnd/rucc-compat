// C99 preprocessing: variadic macros and __VA_ARGS__, empty macro arguments, the _Pragma
// operator, __STDC_VERSION__ and __STDC_HOSTED__, and #if arithmetic done in the widest type.
#include <stdio.h>

#define SHOW(fmt, ...) printf(fmt "\n", __VA_ARGS__)
#define COUNT(...) (sizeof((int[]){ __VA_ARGS__ }) / sizeof(int))
#define FIRST(a, ...) a
#define EMPTY_OK(a, b) [a|b]
#define STR(x) #x
#define XSTR(x) STR(x)
#define QUIET _Pragma("GCC diagnostic ignored \"-Wunused-variable\"")

#if 0xFFFFFFFFFFFFFFFF > 0 && -1 < 0
#define WIDE "wide"
#else
#define WIDE "narrow"
#endif

QUIET

int main(void)
{
    SHOW("%d %s", 3, "three");
    printf("%zu\n", COUNT(1, 2, 3, 4));
    printf("%d\n", FIRST(7, 8, 9));
    printf("%s\n", XSTR(EMPTY_OK(, x)));
    printf("%s\n", XSTR(EMPTY_OK(,)));
    printf("%ld %d\n", __STDC_VERSION__, __STDC_HOSTED__);
    printf("%s\n", WIDE);
    return 0;
}
