/* C89 conversions: integer promotion, conversion between signed and unsigned types, between real
 * floating and integer types, and the usual arithmetic conversions of mixed operands. */
#include <stdio.h>

int main(void)
{
    unsigned char uc = 200;
    signed char sc = -56;
    unsigned short us = 65535;
    short s = -1;
    unsigned int u = 1;
    long l = -3;
    double d;
    float f;
    printf("%d %d\n", uc + uc, sc * 3);
    printf("%lu %lu\n", (unsigned long)sizeof(uc + 0), (unsigned long)sizeof(+s));
    printf("%d %u\n", us + 1, (unsigned)(us + 1));
    printf("%d\n", s < u);
    printf("%d\n", -1 < (int)u);
    printf("%u\n", (unsigned int)-1);
    printf("%d\n", (signed char)200);
    printf("%d %d\n", (unsigned char)-1, (unsigned char)511);
    printf("%d %d %d\n", (int)3.99, (int)-3.99, (int)0.5);
    d = 7;
    f = (float)1 / 3;
    printf("%g %.7g\n", d / 2, f);
    printf("%ld %g\n", l * 2, l / 2.0);
    printf("%lu\n", (unsigned long)sizeof(1 + 1.0f));
    printf("%lu\n", (unsigned long)sizeof('a' + 1L));
    printf("%u\n", 2U - 3);
    return 0;
}
