// C99 hexadecimal floating constants and the %a conversion, together with the floating
// constants and the precision the standard's hexadecimal form makes exact.
#include <stdio.h>
#include <float.h>

int main(void)
{
    double a = 0x1p-1;
    double b = 0x1.8p1;
    float c = 0x.8p0f;
    long double d = 0x1.0p-2L;
    printf("%g %g %g %Lg\n", a, b, c, d);
    printf("%a %a\n", 1.0, 0x1.fffffffffffffp1023);
    printf("%d %d\n", 0x1p0 == 1.0, 0xA.8p0 == 10.5);
    printf("%.17g\n", 0x1.999999999999ap-4);
    printf("%d\n", DBL_MAX == 0x1.fffffffffffffp1023);
    return 0;
}
