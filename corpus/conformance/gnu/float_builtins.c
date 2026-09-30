/* The floating builtins: the constants, the classification and comparison macros' builtins,
   the complex parts, the rounding library functions under their builtin names, and the decimal
   floating ones. Every answer is printed as something exact so the two compilers can be
   compared byte for byte. */
#include <complex.h>
#include <stdio.h>

int main(void)
{
    double inf = __builtin_inf(), nan = __builtin_nan("");
    float inff = __builtin_inff(), nanf = __builtin_nanf("0x1");
    long double infl = __builtin_infl(), nanl = __builtin_nanl("");
    printf("inf %d %d %d\n", inf > 1e308, inff > 3e38f, infl > 1e308L);
    printf("huge %d %d %d\n", __builtin_huge_val() == inf, __builtin_huge_valf() == inff, __builtin_huge_vall() == infl);
    printf("nan %d %d %d\n", nan != nan, nanf != nanf, nanl != nanl);
    printf("nans %d %d %d\n", __builtin_isnan(__builtin_nans("")), __builtin_isnan(__builtin_nansf("")), __builtin_isnan(__builtin_nansl("")));
    printf("fabs %g %g %Lg\n", __builtin_fabs(-2.5), (double)__builtin_fabsf(-1.5f), __builtin_fabsl(-0.5L));
    printf("copysign %g %g %Lg\n", __builtin_copysign(3.0, -0.0), (double)__builtin_copysignf(2.0f, 1.0f), __builtin_copysignl(1.0L, -1.0L));
    double one = 1.0, two = 2.0;
    printf("compare %d %d %d %d %d %d %d\n", __builtin_isgreater(two, one), __builtin_isgreaterequal(one, one), __builtin_isless(one, two), __builtin_islessequal(two, one), __builtin_islessgreater(one, two), __builtin_isunordered(one, nan), __builtin_isless(nan, one));
    printf("isnan %d %d %d\n", __builtin_isnan(nan), __builtin_isnanf(nanf), __builtin_isnanl(nanl));
    printf("isinf %d %d %d %d %d\n", __builtin_isinf(inf), __builtin_isinff(inff), __builtin_isinfl(-infl) != 0, __builtin_isinf_sign(-inf), __builtin_isinf_sign(one));
    printf("finite %d %d %d %d %d\n", __builtin_isfinite(one), __builtin_finite(inf), __builtin_finitef(1.0f), __builtin_finitel(nanl), __builtin_isnormal(1e-320));
    printf("fpclassify %d %d %d %d %d\n", __builtin_fpclassify(0, 1, 2, 3, 4, nan), __builtin_fpclassify(0, 1, 2, 3, 4, inf), __builtin_fpclassify(0, 1, 2, 3, 4, one), __builtin_fpclassify(0, 1, 2, 3, 4, 1e-320), __builtin_fpclassify(0, 1, 2, 3, 4, 0.0));
    printf("signbit %d %d %d\n", __builtin_signbit(-0.0) != 0, __builtin_signbitf(1.0f) != 0, __builtin_signbitl(-1.0L) != 0);
    _Complex double z = 3.0 + 4.0 * I;
    _Complex float zf = 1.0f - 2.0f * I;
    _Complex long double zl = 5.0L + 6.0L * I;
    printf("complex %g %g %g %g %Lg %Lg\n", __builtin_creal(z), __builtin_cimag(__builtin_conj(z)), (double)__builtin_crealf(__builtin_conjf(zf)), (double)__builtin_cimagf(zf), __builtin_creall(zl), __builtin_cimagl(__builtin_conjl(zl)));
    volatile double x = 2.5, y = -2.5;
    volatile float xf = 2.5f;
    volatile long double xl = 2.5L;
    printf("ceil %g %g %Lg\n", __builtin_ceil(x), (double)__builtin_ceilf(xf), __builtin_ceill(xl));
    printf("floor %g %g %Lg\n", __builtin_floor(y), (double)__builtin_floorf(xf), __builtin_floorl(xl));
    printf("trunc %g %g %Lg\n", __builtin_trunc(y), (double)__builtin_truncf(xf), __builtin_truncl(xl));
    printf("round %g %g %Lg\n", __builtin_round(y), (double)__builtin_roundf(xf), __builtin_roundl(xl));
    printf("rint %g %g %Lg\n", __builtin_rint(x), (double)__builtin_rintf(xf), __builtin_rintl(xl));
    printf("nearbyint %g %g %Lg\n", __builtin_nearbyint(y), (double)__builtin_nearbyintf(xf), __builtin_nearbyintl(xl));
    printf("fmax %g %g %Lg\n", __builtin_fmax(x, nan), (double)__builtin_fmaxf(xf, 1.0f), __builtin_fmaxl(xl, 3.0L));
    printf("fmin %g %g %Lg\n", __builtin_fmin(y, x), (double)__builtin_fminf(xf, 1.0f), __builtin_fminl(xl, 3.0L));
    return 0;
}
