/* __builtin_expect and __builtin_expect_with_probability answer their first argument and only
 * change how the code is laid out. __builtin_unreachable promises a point is never reached, and a
 * program that keeps the promise runs the same. Postgres spells them likely, unlikely and
 * pg_unreachable. */
#include "../check.h"

static int classify(int x) {
    switch (x & 3) {
    case 0:
        return 10;
    case 1:
        return 11;
    case 2:
        return 12;
    case 3:
        return 13;
    }
    __builtin_unreachable();
}

#if __has_builtin(__builtin_expect)
#define HAS_0 1
#else
#define HAS_0 0
#endif
#if __has_builtin(__builtin_expect_with_probability)
#define HAS_1 1
#else
#define HAS_1 0
#endif
#if __has_builtin(__builtin_unreachable)
#define HAS_2 1
#else
#define HAS_2 0
#endif

int main(void) {
    CLAIM("__has_builtin(__builtin_expect)", HAS_0);
    CLAIM("__has_builtin(__builtin_expect_with_probability)", HAS_1);
    CLAIM("__has_builtin(__builtin_unreachable)", HAS_2);
    volatile int x = 5;
    CHECK(__builtin_expect(x, 0) == 5);
    CHECK(__builtin_expect(x == 5, 1));
    CHECK(__builtin_expect_with_probability(x, 5, 0.9) == 5);
    long l = __builtin_expect(1L << 40, 0);
    CHECK(l == 1L << 40);
    int sum = 0;
    for (int i = 0; i < 8; i++) {
        if (__builtin_expect(i == 7, 0))
            sum += 100;
        else
            sum += classify(i);
    }
    CHECK(sum == 10 + 11 + 12 + 13 + 10 + 11 + 12 + 100);
    DONE();
}
