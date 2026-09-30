// C99 integer types: <stdint.h> exact, least and fast width types and their limits, intmax_t and
// uintptr_t, the <inttypes.h> format macros, long long arithmetic and its conversions, and
// integer division truncating toward zero, which C99 made required.
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int main(void)
{
    int8_t a = INT8_MIN;
    uint16_t b = UINT16_MAX;
    int32_t c = INT32_MAX;
    uint64_t d = UINT64_MAX;
    int_least16_t e = -300;
    uint_fast8_t f = 250;
    intmax_t g = INTMAX_MIN;
    uintptr_t h = (uintptr_t)&a;
    printf("%" PRId8 " %" PRIu16 " %" PRId32 " %" PRIu64 "\n", a, b, c, d);
    printf("%" PRIdLEAST16 " %" PRIuFAST8 " %" PRIdMAX "\n", e, f, g);
    printf("%d\n", (int8_t *)h == &a);
    printf("%d %d %d %d\n", -7 / 2, -7 % 2, 7 / -2, 7 % -2);
    long long x = 1LL << 40;
    printf("%lld %lld %lld\n", x, x / 3, -x % 1000);
    unsigned long long y = (unsigned long long)-1 / 3;
    printf("%llu %llx\n", y, y);
    printf("%lld\n", (long long)(double)(1LL << 53));
    printf("%zu %d\n", sizeof(intmax_t), sizeof(int_fast16_t) >= 2);
    return 0;
}
