/* The bit counting builtins, which Postgres uses in pg_bitutils.h for its leftmost and rightmost
 * one and its popcount. clz and ctz are undefined for zero and nothing here asks them about it. */
#include "../check.h"

#if __has_builtin(__builtin_clz)
#define HAS_0 1
#else
#define HAS_0 0
#endif
#if __has_builtin(__builtin_ctz)
#define HAS_1 1
#else
#define HAS_1 0
#endif
#if __has_builtin(__builtin_popcount)
#define HAS_2 1
#else
#define HAS_2 0
#endif
#if __has_builtin(__builtin_parity)
#define HAS_3 1
#else
#define HAS_3 0
#endif
#if __has_builtin(__builtin_ffs)
#define HAS_4 1
#else
#define HAS_4 0
#endif
#if __has_builtin(__builtin_clrsb)
#define HAS_5 1
#else
#define HAS_5 0
#endif
#if __has_builtin(__builtin_clzl)
#define HAS_6 1
#else
#define HAS_6 0
#endif
#if __has_builtin(__builtin_clzll)
#define HAS_7 1
#else
#define HAS_7 0
#endif
#if __has_builtin(__builtin_ctzl)
#define HAS_8 1
#else
#define HAS_8 0
#endif
#if __has_builtin(__builtin_ctzll)
#define HAS_9 1
#else
#define HAS_9 0
#endif
#if __has_builtin(__builtin_popcountl)
#define HAS_10 1
#else
#define HAS_10 0
#endif
#if __has_builtin(__builtin_popcountll)
#define HAS_11 1
#else
#define HAS_11 0
#endif
#if __has_builtin(__builtin_parityl)
#define HAS_12 1
#else
#define HAS_12 0
#endif
#if __has_builtin(__builtin_parityll)
#define HAS_13 1
#else
#define HAS_13 0
#endif
#if __has_builtin(__builtin_ffsl)
#define HAS_14 1
#else
#define HAS_14 0
#endif
#if __has_builtin(__builtin_ffsll)
#define HAS_15 1
#else
#define HAS_15 0
#endif
#if __has_builtin(__builtin_clrsbl)
#define HAS_16 1
#else
#define HAS_16 0
#endif
#if __has_builtin(__builtin_clrsbll)
#define HAS_17 1
#else
#define HAS_17 0
#endif

int main(void) {
    CLAIM("__has_builtin(__builtin_clz)", HAS_0);
    CLAIM("__has_builtin(__builtin_ctz)", HAS_1);
    CLAIM("__has_builtin(__builtin_popcount)", HAS_2);
    CLAIM("__has_builtin(__builtin_parity)", HAS_3);
    CLAIM("__has_builtin(__builtin_ffs)", HAS_4);
    CLAIM("__has_builtin(__builtin_clrsb)", HAS_5);
    CLAIM("__has_builtin(__builtin_clzl)", HAS_6);
    CLAIM("__has_builtin(__builtin_clzll)", HAS_7);
    CLAIM("__has_builtin(__builtin_ctzl)", HAS_8);
    CLAIM("__has_builtin(__builtin_ctzll)", HAS_9);
    CLAIM("__has_builtin(__builtin_popcountl)", HAS_10);
    CLAIM("__has_builtin(__builtin_popcountll)", HAS_11);
    CLAIM("__has_builtin(__builtin_parityl)", HAS_12);
    CLAIM("__has_builtin(__builtin_parityll)", HAS_13);
    CLAIM("__has_builtin(__builtin_ffsl)", HAS_14);
    CLAIM("__has_builtin(__builtin_ffsll)", HAS_15);
    CLAIM("__has_builtin(__builtin_clrsbl)", HAS_16);
    CLAIM("__has_builtin(__builtin_clrsbll)", HAS_17);
    volatile unsigned v = 0x00f00000u;
    volatile unsigned long lv = 1UL << 40;
    volatile unsigned long long llv = 0x8000000000000001ULL;
    CHECK(__builtin_clz(1u) == 31);
    CHECK(__builtin_clz(v) == 8);
    CHECK(__builtin_clz(0x80000000u) == 0);
    CHECK(__builtin_ctz(v) == 20);
    CHECK(__builtin_ctz(0x80000000u) == 31);
    CHECK(__builtin_popcount(v) == 4);
    CHECK(__builtin_popcount(0u) == 0);
    CHECK(__builtin_popcount(0xffffffffu) == 32);
    CHECK(__builtin_parity(7u) == 1 && __builtin_parity(v) == 0);
    CHECK(__builtin_ffs(0) == 0 && __builtin_ffs(8) == 4 && __builtin_ffs(-1) == 1);
    CHECK(__builtin_clrsb(0) == 31 && __builtin_clrsb(-1) == 31 && __builtin_clrsb(1) == 30);
    CHECK(__builtin_clzl(lv) == 23);
    CHECK(__builtin_ctzl(lv) == 40);
    CHECK(__builtin_popcountl(~0UL) == 64);
    CHECK(__builtin_parityl(lv | 1) == 0);
    CHECK(__builtin_ffsl((long)lv) == 41);
    CHECK(__builtin_clrsbl(-2L) == 62);
    CHECK(__builtin_clzll(llv) == 0);
    CHECK(__builtin_ctzll(llv) == 0);
    CHECK(__builtin_ctzll(llv - 1) == 63);
    CHECK(__builtin_popcountll(llv) == 2);
    CHECK(__builtin_parityll(llv) == 0);
    CHECK(__builtin_ffsll(0LL) == 0 && __builtin_ffsll(1LL << 62) == 63);
    CHECK(__builtin_clrsbll(1LL << 40) == 22);
    int total = 0;
    for (unsigned i = 1; i < 300; i += 7)
        total += __builtin_clz(i) + __builtin_ctz(i) + __builtin_popcount(i);
    printf("total %d\n", total);
    DONE();
}
