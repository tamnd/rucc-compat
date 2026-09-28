/* The _p forms of the overflow builtins: the same question, with the type of the third argument
 * standing for the result type and its value ignored. They are constant expressions when their
 * operands are. */
#include <limits.h>
#include "../check.h"

#if __has_builtin(__builtin_add_overflow_p)
#define HAS_0 1
#else
#define HAS_0 0
#endif
#if __has_builtin(__builtin_sub_overflow_p)
#define HAS_1 1
#else
#define HAS_1 0
#endif
#if __has_builtin(__builtin_mul_overflow_p)
#define HAS_2 1
#else
#define HAS_2 0
#endif

int main(void) {
    CLAIM("__has_builtin(__builtin_add_overflow_p)", HAS_0);
    CLAIM("__has_builtin(__builtin_sub_overflow_p)", HAS_1);
    CLAIM("__has_builtin(__builtin_mul_overflow_p)", HAS_2);
    CHECK(__builtin_add_overflow_p(INT_MAX, 1, (int)0));
    CHECK(!__builtin_add_overflow_p(INT_MAX, 1, (long long)0));
    CHECK(__builtin_sub_overflow_p(0, 1, (unsigned)0));
    CHECK(!__builtin_sub_overflow_p(0u, 1, (int)0));
    CHECK(__builtin_mul_overflow_p(1 << 20, 1 << 12, (int)0));
    CHECK(!__builtin_mul_overflow_p(-1, UINT_MAX, (long long)0));
    static const int folded = __builtin_add_overflow_p(250, 10, (unsigned char)0);
    CHECK(folded == 1);
    DONE();
}
