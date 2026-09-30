/* C89 type specifiers: every spelling of the basic types, in any order the grammar allows, and the
 * range of the character and integer types through <limits.h> and <float.h>. */
#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void)
{
    signed char sc = SCHAR_MIN;
    unsigned char uc = UCHAR_MAX;
    short int si = SHRT_MAX;
    int short is = SHRT_MIN;
    unsigned short int usi = USHRT_MAX;
    signed s = INT_MIN;
    unsigned u = UINT_MAX;
    long int li = LONG_MAX;
    unsigned long int uli = ULONG_MAX;
    long unsigned lu = 1;
    float f = FLT_MAX;
    double d = DBL_EPSILON;
    long double ld = 2.5L;
    char c = CHAR_MIN;
    printf("%d %d %d %d %u\n", sc, uc, si, is, usi);
    printf("%d %u %ld %lu %lu\n", s, u, li, uli, lu);
    printf("%g %g %Lg\n", f, d, ld);
    printf("%d %d %d\n", c, CHAR_BIT, CHAR_MAX);
    printf("%lu %lu %lu\n", (unsigned long)sizeof(float), (unsigned long)sizeof(double), (unsigned long)sizeof(long double));
    printf("%d %d %d\n", FLT_DIG, DBL_DIG, DBL_MANT_DIG);
    return 0;
}
