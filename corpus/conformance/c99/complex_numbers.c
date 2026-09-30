// C99 complex types: _Complex float, double and long double, the imaginary unit I from
// <complex.h>, arithmetic including multiplication and division, creal, cimag and conj, and the
// conversion from a real value.
#include <stdio.h>
#include <complex.h>

int main(void)
{
    double complex z = 1.0 + 2.0 * I;
    double complex w = 3.0 - 1.0 * I;
    double complex p = z * w;
    double complex q = z / w;
    float complex f = 2.0f;
    long double complex l = 1.5L * I;
    printf("%g %g\n", creal(p), cimag(p));
    printf("%.6f %.6f\n", creal(q), cimag(q));
    printf("%g %g\n", creal(conj(z)), cimag(conj(z)));
    printf("%g %g\n", crealf(f), cimagf(f));
    printf("%Lg %Lg\n", creall(l), cimagl(l));
    printf("%zu %zu %zu\n", sizeof(float complex), sizeof(double complex), sizeof(long double complex));
    printf("%d\n", z == 1.0 + 2.0 * I);
    return 0;
}
