/* __builtin_add_overflow, __builtin_sub_overflow and __builtin_mul_overflow: the operation is
 * done in infinite precision, the result is converted to the type the third argument points at,
 * and the builtin answers whether that conversion lost anything. The operands may have different
 * types and different signedness, which is how Postgres uses them in its int8 and numeric code. */
#include <limits.h>
#include <stdint.h>
#include "../check.h"

#if __has_builtin(__builtin_add_overflow)
#define HAS_0 1
#else
#define HAS_0 0
#endif
#if __has_builtin(__builtin_sub_overflow)
#define HAS_1 1
#else
#define HAS_1 0
#endif
#if __has_builtin(__builtin_mul_overflow)
#define HAS_2 1
#else
#define HAS_2 0
#endif

int main(void) {
    CLAIM("__has_builtin(__builtin_add_overflow)", HAS_0);
    CLAIM("__has_builtin(__builtin_sub_overflow)", HAS_1);
    CLAIM("__has_builtin(__builtin_mul_overflow)", HAS_2);
    int i;
    unsigned u;
    long long ll;
    unsigned long long ull;
    int64_t i64;
    short s;
    unsigned char uc;

    CHECK(__builtin_add_overflow(INT_MAX, 1, &i) && i == INT_MIN);
    CHECK(!__builtin_add_overflow(INT_MAX - 1, 1, &i) && i == INT_MAX);
    CHECK(!__builtin_add_overflow(UINT_MAX, -1, &u) && u == UINT_MAX - 1);
    CHECK(__builtin_add_overflow(-1, 0u, &u) && u == UINT_MAX);
    CHECK(!__builtin_add_overflow(UINT_MAX, 1, &ll) && ll == 4294967296LL);
    CHECK(__builtin_add_overflow(200, 100, &uc) && uc == 44);
    CHECK(__builtin_add_overflow(ULLONG_MAX, 1, &ull) && ull == 0);
    CHECK(!__builtin_add_overflow(ULLONG_MAX, -1LL, &ull) && ull == ULLONG_MAX - 1);

    CHECK(!__builtin_sub_overflow(0u, 1, &i) && i == -1);
    CHECK(__builtin_sub_overflow(0, 1, &u) && u == UINT_MAX);
    CHECK(__builtin_sub_overflow(INT_MIN, 1, &i) && i == INT_MAX);
    CHECK(!__builtin_sub_overflow(5u, 7u, &s) && s == -2);
    CHECK(__builtin_sub_overflow(INT64_MIN, (int64_t)1, &i64) && i64 == INT64_MAX);
    CHECK(!__builtin_sub_overflow(0, INT_MIN, &ll) && ll == 2147483648LL);

    CHECK(!__builtin_mul_overflow(-1, UINT_MAX, &ll) && ll == -4294967295LL);
    CHECK(__builtin_mul_overflow(-1, UINT_MAX, &i) && i == 1);
    CHECK(__builtin_mul_overflow(INT64_MIN, (int64_t)-1, &i64) && i64 == INT64_MIN);
    CHECK(!__builtin_mul_overflow(65535u, 65537u, &u) && u == UINT_MAX);
    CHECK(__builtin_mul_overflow(65536u, 65536u, &u) && u == 0);
    CHECK(!__builtin_mul_overflow(-3, 7u, &i) && i == -21);
    CHECK(__builtin_mul_overflow(-3, 7u, &u) && u == (unsigned)-21);
    CHECK(__builtin_mul_overflow((int64_t)1 << 40, (int64_t)1 << 30, &i64));
    CHECK(!__builtin_mul_overflow(INT_MIN, -1, &ll) && ll == 2147483648LL);

    /* The operands are read once, and a variable works where a constant did. */
    volatile int big = INT_MAX, one = 1;
    CHECK(__builtin_add_overflow(big, one, &i) && i == INT_MIN);
    volatile unsigned ubig = UINT_MAX;
    volatile int minus = -2;
    CHECK(!__builtin_mul_overflow(ubig, minus, &ll) && ll == -8589934590LL);
    DONE();
}
