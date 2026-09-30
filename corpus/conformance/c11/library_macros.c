// C11 odds and ends: __STDC_VERSION__, the optional feature macros, CMPLX, the float
// characteristics C11 added, quick_exit and at_quick_exit, and timespec_get.
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <complex.h>
#include <time.h>

static void last(void) { printf("quick exit handler\n"); fflush(stdout); }

int main(void)
{
    printf("%ld\n", __STDC_VERSION__);
#ifdef __STDC_NO_VLA__
    printf("no vla\n");
#else
    printf("vla\n");
#endif
#ifdef __STDC_NO_COMPLEX__
    printf("no complex\n");
#else
    double complex z = CMPLX(1.0, 2.0);
    printf("%g %g\n", creal(z), cimag(z));
#endif
    printf("%d %d %d\n", FLT_DECIMAL_DIG, DBL_DECIMAL_DIG, FLT_HAS_SUBNORM);
    printf("%g\n", DBL_TRUE_MIN);
    struct timespec ts;
    printf("%d\n", timespec_get(&ts, TIME_UTC) == TIME_UTC);
    at_quick_exit(last);
    quick_exit(4);
}
