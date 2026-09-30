/* C89 floating constants: the forms with and without a fraction or an exponent, the suffixes f
 * and l, and the type each one gets. */
#include <stdio.h>

int main(void)
{
    printf("%g %g %g %g\n", 1.5, .5, 3., 1e3);
    printf("%g %g %g\n", 2.5E-3, 1.25e+2, 0.0);
    printf("%lu %lu %lu\n", (unsigned long)sizeof(1.0f), (unsigned long)sizeof(1.0), (unsigned long)sizeof(1.0L));
    printf("%.10f\n", 0.1f + 0.2f);
    printf("%.17g\n", 0.1 + 0.2);
    printf("%.6Lf\n", 1.0L / 3.0L);
    printf("%d\n", 1.0f == 1.0);
    return 0;
}
