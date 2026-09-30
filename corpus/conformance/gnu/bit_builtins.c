/* The builtins that count bits, swap bytes, take absolute values and check arithmetic for
   overflow, over the int, long and long long widths each comes in. */
#include <inttypes.h>
#include <limits.h>
#include <stdio.h>

int main(void)
{
    unsigned u = 0x00f0u;
    unsigned long ul = 0x0f00ul;
    unsigned long long ull = 0x1000000000ull;
    printf("clz %d %d %d\n", __builtin_clz(u), __builtin_clzl(ul), __builtin_clzll(ull));
    printf("ctz %d %d %d\n", __builtin_ctz(u), __builtin_ctzl(ul), __builtin_ctzll(ull));
    printf("popcount %d %d %d\n", __builtin_popcount(u), __builtin_popcountl(ul | 1), __builtin_popcountll(ull - 1));
    printf("parity %d %d %d\n", __builtin_parity(u | 1), __builtin_parityl(ul), __builtin_parityll(ull | 3));
    printf("ffs %d %d %d %d\n", __builtin_ffs(0), __builtin_ffs(8), __builtin_ffsl(1L << 20), __builtin_ffsll(1LL << 40));
    printf("clrsb %d %d %d\n", __builtin_clrsb(-1), __builtin_clrsbl(1L), __builtin_clrsbll(-256LL));
    printf("bswap %04x %08x %016llx\n", __builtin_bswap16(0x1234), __builtin_bswap32(0x12345678u), (unsigned long long)__builtin_bswap64(0x0102030405060708ull));
    printf("uabs %u %lu %llu %ju\n", __builtin_uabs(INT_MIN), __builtin_ulabs(-5L), __builtin_ullabs(LLONG_MIN), (uintmax_t)__builtin_umaxabs((intmax_t)-9));
    int r;
    long long wide;
    unsigned char small;
    int a = __builtin_add_overflow(INT_MAX, 1, &r);
    int s = __builtin_sub_overflow(5, 7, &small);
    int m = __builtin_mul_overflow(1LL << 40, 1 << 10, &wide);
    printf("overflow %d %d %d %d %lld\n", a, s, small, m, wide);
    printf("overflow_p %d %d %d\n", __builtin_add_overflow_p(INT_MAX, 1, (int)0), __builtin_sub_overflow_p(0u, 1u, (unsigned)0), __builtin_mul_overflow_p(1 << 16, 1 << 16, (long long)0));
    _Static_assert(__builtin_add_overflow_p(INT_MAX, 1, (int)0), "a constant expression");
    return 0;
}
