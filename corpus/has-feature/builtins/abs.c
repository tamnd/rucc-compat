/* The absolute value builtins. The u forms are GCC 15's, and answer the magnitude as an unsigned
 * type, so the most negative value has an answer. */
#include <limits.h>
#include <stdint.h>
#include "../check.h"

#if __has_builtin(__builtin_abs)
#define HAS_0 1
#else
#define HAS_0 0
#endif
#if __has_builtin(__builtin_labs)
#define HAS_1 1
#else
#define HAS_1 0
#endif
#if __has_builtin(__builtin_llabs)
#define HAS_2 1
#else
#define HAS_2 0
#endif
#if __has_builtin(__builtin_imaxabs)
#define HAS_3 1
#else
#define HAS_3 0
#endif
#if __has_builtin(__builtin_uabs)
#define HAS_4 1
#else
#define HAS_4 0
#endif
#if __has_builtin(__builtin_ulabs)
#define HAS_5 1
#else
#define HAS_5 0
#endif
#if __has_builtin(__builtin_ullabs)
#define HAS_6 1
#else
#define HAS_6 0
#endif
#if __has_builtin(__builtin_umaxabs)
#define HAS_7 1
#else
#define HAS_7 0
#endif

int main(void) {
    CLAIM("__has_builtin(__builtin_abs)", HAS_0);
    CLAIM("__has_builtin(__builtin_labs)", HAS_1);
    CLAIM("__has_builtin(__builtin_llabs)", HAS_2);
    CLAIM("__has_builtin(__builtin_imaxabs)", HAS_3);
    CLAIM("__has_builtin(__builtin_uabs)", HAS_4);
    CLAIM("__has_builtin(__builtin_ulabs)", HAS_5);
    CLAIM("__has_builtin(__builtin_ullabs)", HAS_6);
    CLAIM("__has_builtin(__builtin_umaxabs)", HAS_7);
    volatile int i = -5;
    volatile long l = -6;
    volatile long long ll = -7;
    CHECK(__builtin_abs(i) == 5);
    CHECK(__builtin_labs(l) == 6);
    CHECK(__builtin_llabs(ll) == 7);
    CHECK(__builtin_imaxabs((intmax_t)ll) == 7);
    volatile int least = INT_MIN;
    CHECK(__builtin_uabs(least) == 2147483648u);
    CHECK(__builtin_ulabs(LONG_MIN) == 9223372036854775808ul);
    CHECK(__builtin_ullabs(ll) == 7);
    CHECK(__builtin_umaxabs(INTMAX_MIN) == (uintmax_t)INTMAX_MAX + 1);
    DONE();
}
