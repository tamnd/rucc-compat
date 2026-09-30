// C23 constants: binary integer constants, digit separators in every base, u8 character
// constants and the char8_t type, and the wb suffix giving a _BitInt constant.
#include <stdio.h>
#include <uchar.h>

int main(void)
{
    int a = 0b1011;
    unsigned b = 0B1111'0000u;
    long c = 1'000'000L;
    int d = 0x7f'ff;
    double e = 1'234.5'6;
    char8_t f = u8'A';
    printf("%d %u %ld %d %g\n", a, b, c, d, e);
    printf("%d %zu\n", f, sizeof(char8_t));
    printf("%d %d\n", (int)sizeof(3wb), (int)(7uwb + 1wb));
    printf("%d\n", 0'17);
    return 0;
}
