/* The byte swap builtins, which Postgres uses in pg_bswap.h for network byte order. */
#include <stdint.h>
#include "../check.h"

#if __has_builtin(__builtin_bswap16)
#define HAS_0 1
#else
#define HAS_0 0
#endif
#if __has_builtin(__builtin_bswap32)
#define HAS_1 1
#else
#define HAS_1 0
#endif
#if __has_builtin(__builtin_bswap64)
#define HAS_2 1
#else
#define HAS_2 0
#endif

int main(void) {
    CLAIM("__has_builtin(__builtin_bswap16)", HAS_0);
    CLAIM("__has_builtin(__builtin_bswap32)", HAS_1);
    CLAIM("__has_builtin(__builtin_bswap64)", HAS_2);
    volatile uint16_t h = 0x1234;
    volatile uint32_t w = 0x12345678u;
    volatile uint64_t d = 0x0102030405060708ULL;
    CHECK(__builtin_bswap16(h) == 0x3412);
    CHECK(__builtin_bswap32(w) == 0x78563412u);
    CHECK(__builtin_bswap64(d) == 0x0807060504030201ULL);
    CHECK(__builtin_bswap16(0xff00) == 0x00ff);
    CHECK(__builtin_bswap32(__builtin_bswap32(w)) == w);
    static const uint32_t folded = __builtin_bswap32(0xaabbccddu);
    CHECK(folded == 0xddccbbaau);
    CHECK(sizeof(__builtin_bswap16(h)) == 2 && sizeof(__builtin_bswap64(d)) == 8);
    DONE();
}
