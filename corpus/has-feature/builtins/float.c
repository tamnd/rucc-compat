/* The floating point builtins Postgres's float.h and the C library's math.h are written over:
 * the constants, the classification and the rounding family. */
#include <float.h>
#include <math.h>
#include "../check.h"

#if __has_builtin(__builtin_fabs)
#define HAS_0 1
#else
#define HAS_0 0
#endif
#if __has_builtin(__builtin_copysign)
#define HAS_1 1
#else
#define HAS_1 0
#endif
#if __has_builtin(__builtin_inf)
#define HAS_2 1
#else
#define HAS_2 0
#endif
#if __has_builtin(__builtin_huge_val)
#define HAS_3 1
#else
#define HAS_3 0
#endif
#if __has_builtin(__builtin_nan)
#define HAS_4 1
#else
#define HAS_4 0
#endif
#if __has_builtin(__builtin_isnan)
#define HAS_5 1
#else
#define HAS_5 0
#endif
#if __has_builtin(__builtin_isinf)
#define HAS_6 1
#else
#define HAS_6 0
#endif
#if __has_builtin(__builtin_isinf_sign)
#define HAS_7 1
#else
#define HAS_7 0
#endif
#if __has_builtin(__builtin_isfinite)
#define HAS_8 1
#else
#define HAS_8 0
#endif
#if __has_builtin(__builtin_isnormal)
#define HAS_9 1
#else
#define HAS_9 0
#endif
#if __has_builtin(__builtin_fpclassify)
#define HAS_10 1
#else
#define HAS_10 0
#endif
#if __has_builtin(__builtin_signbit)
#define HAS_11 1
#else
#define HAS_11 0
#endif
#if __has_builtin(__builtin_isgreater)
#define HAS_12 1
#else
#define HAS_12 0
#endif
#if __has_builtin(__builtin_isunordered)
#define HAS_13 1
#else
#define HAS_13 0
#endif
#if __has_builtin(__builtin_floor)
#define HAS_14 1
#else
#define HAS_14 0
#endif
#if __has_builtin(__builtin_ceil)
#define HAS_15 1
#else
#define HAS_15 0
#endif
#if __has_builtin(__builtin_trunc)
#define HAS_16 1
#else
#define HAS_16 0
#endif
#if __has_builtin(__builtin_round)
#define HAS_17 1
#else
#define HAS_17 0
#endif
#if __has_builtin(__builtin_rint)
#define HAS_18 1
#else
#define HAS_18 0
#endif
#if __has_builtin(__builtin_nearbyint)
#define HAS_19 1
#else
#define HAS_19 0
#endif
#if __has_builtin(__builtin_fmax)
#define HAS_20 1
#else
#define HAS_20 0
#endif
#if __has_builtin(__builtin_fmin)
#define HAS_21 1
#else
#define HAS_21 0
#endif

int main(void) {
    CLAIM("__has_builtin(__builtin_fabs)", HAS_0);
    CLAIM("__has_builtin(__builtin_copysign)", HAS_1);
    CLAIM("__has_builtin(__builtin_inf)", HAS_2);
    CLAIM("__has_builtin(__builtin_huge_val)", HAS_3);
    CLAIM("__has_builtin(__builtin_nan)", HAS_4);
    CLAIM("__has_builtin(__builtin_isnan)", HAS_5);
    CLAIM("__has_builtin(__builtin_isinf)", HAS_6);
    CLAIM("__has_builtin(__builtin_isinf_sign)", HAS_7);
    CLAIM("__has_builtin(__builtin_isfinite)", HAS_8);
    CLAIM("__has_builtin(__builtin_isnormal)", HAS_9);
    CLAIM("__has_builtin(__builtin_fpclassify)", HAS_10);
    CLAIM("__has_builtin(__builtin_signbit)", HAS_11);
    CLAIM("__has_builtin(__builtin_isgreater)", HAS_12);
    CLAIM("__has_builtin(__builtin_isunordered)", HAS_13);
    CLAIM("__has_builtin(__builtin_floor)", HAS_14);
    CLAIM("__has_builtin(__builtin_ceil)", HAS_15);
    CLAIM("__has_builtin(__builtin_trunc)", HAS_16);
    CLAIM("__has_builtin(__builtin_round)", HAS_17);
    CLAIM("__has_builtin(__builtin_rint)", HAS_18);
    CLAIM("__has_builtin(__builtin_nearbyint)", HAS_19);
    CLAIM("__has_builtin(__builtin_fmax)", HAS_20);
    CLAIM("__has_builtin(__builtin_fmin)", HAS_21);
    volatile double x = -2.5, y = 3.0, zero = 0.0;
    double inf = __builtin_inf(), nan = __builtin_nan("");
    CHECK(__builtin_fabs(x) == 2.5);
    CHECK(__builtin_fabsf(-1.5f) == 1.5f);
    CHECK(__builtin_copysign(y, x) == -3.0);
    CHECK(__builtin_copysign(1.0, -zero) == -1.0);
    CHECK(inf > DBL_MAX && __builtin_huge_val() == inf && __builtin_inff() > FLT_MAX);
    CHECK(nan != nan);
    CHECK(__builtin_isnan(nan) && !__builtin_isnan(inf));
    CHECK(__builtin_isinf(inf) && !__builtin_isinf(y));
    CHECK(__builtin_isinf_sign(-inf) == -1 && __builtin_isinf_sign(inf) == 1 && __builtin_isinf_sign(y) == 0);
    CHECK(__builtin_isfinite(y) && !__builtin_isfinite(inf) && !__builtin_isfinite(nan));
    CHECK(__builtin_isnormal(y) && !__builtin_isnormal(zero) && !__builtin_isnormal(DBL_MIN / 2));
    CHECK(__builtin_fpclassify(0, 1, 2, 3, 4, nan) == 0);
    CHECK(__builtin_fpclassify(0, 1, 2, 3, 4, inf) == 1);
    CHECK(__builtin_fpclassify(0, 1, 2, 3, 4, y) == 2);
    CHECK(__builtin_fpclassify(0, 1, 2, 3, 4, DBL_MIN / 4) == 3);
    CHECK(__builtin_fpclassify(0, 1, 2, 3, 4, zero) == 4);
    CHECK(__builtin_signbit(-zero) != 0 && __builtin_signbit(zero) == 0 && __builtin_signbit(x) != 0);
    CHECK(__builtin_isgreater(y, x) && !__builtin_isgreater(nan, x));
    CHECK(__builtin_isunordered(nan, y) && !__builtin_isunordered(x, y));
    CHECK(__builtin_floor(x) == -3.0 && __builtin_ceil(x) == -2.0);
    CHECK(__builtin_trunc(x) == -2.0 && __builtin_round(x) == -3.0);
    CHECK(__builtin_rint(x) == -2.0 && __builtin_nearbyint(2.5) == 2.0);
    CHECK(__builtin_floorf(1.75f) == 1.0f && __builtin_roundl(0.5L) == 1.0L);
    CHECK(__builtin_fmax(x, y) == 3.0 && __builtin_fmin(x, y) == -2.5);
    CHECK(__builtin_fmax(nan, y) == 3.0);
    printf("%.3f %.3f %.3f\n", __builtin_floor(-0.5), __builtin_round(-0.5), __builtin_trunc(7.9));
    DONE();
}
