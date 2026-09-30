// C23 _BitInt: signed and unsigned bit-precise integers of widths other than the standard ones,
// their arithmetic wrapping or promoting as the standard says, their sizes, and BITINT_MAXWIDTH.
#include <stdio.h>
#include <limits.h>

int main(void)
{
    _BitInt(7) a = 63;
    unsigned _BitInt(7) b = 127;
    b += 1;
    _BitInt(65) c = (_BitInt(65))1 << 63;
    c = -c * 2;
    unsigned _BitInt(128) d = ((unsigned _BitInt(128))1 << 100) + 5;
    printf("%d %d\n", (int)a, (int)b);
    printf("%d %lld\n", c < 0, (long long)(c / 4));
    printf("%llu %llu\n", (unsigned long long)(d >> 64), (unsigned long long)d);
    printf("%zu %zu %zu\n", sizeof(_BitInt(7)), sizeof(_BitInt(65)), sizeof(unsigned _BitInt(128)));
    printf("%d\n", BITINT_MAXWIDTH >= 128);
    printf("%d\n", _Generic(a + a, _BitInt(7): 1, int: 2, default: 3));
    return 0;
}
