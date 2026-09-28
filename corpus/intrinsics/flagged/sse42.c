/* The CRC32C steps and the population counts in a unit built with -msse4.2 and -mpopcnt, and no
 * target attribute anywhere, which is how Postgres builds pg_crc32c_sse42.c when configure finds
 * the compiler needs the flag. The macros the flags define are printed first, since configure and
 * Postgres's own headers read them to decide which path to build. The run is guarded by cpuid like
 * the others, because a unit built for SSE4.2 is still allowed to be run somewhere without it. */
#include <cpuid.h>
#include <nmmintrin.h>

#include "../check.h"
#include "../crc.h"

static uint32_t pg_comp_crc32c_sse42(uint32_t crc, const void *data, size_t len)
{
    PG_COMP_CRC32C_BODY(crc, data, len);
    return crc;
}

static int bits(uint64_t v)
{
    int n = 0;
    for (; v; v >>= 1)
        n += (int)(v & 1);
    return n;
}

int main(void)
{
#ifdef __SSE4_2__
    printf("__SSE4_2__ 1\n");
#else
    printf("__SSE4_2__ 0\n");
#endif
#ifdef __SSE4_1__
    printf("__SSE4_1__ 1\n");
#else
    printf("__SSE4_1__ 0\n");
#endif
#ifdef __POPCNT__
    printf("__POPCNT__ 1\n");
#else
    printf("__POPCNT__ 0\n");
#endif
#ifdef __CRC32__
    printf("__CRC32__ 1\n");
#else
    printf("__CRC32__ 0\n");
#endif
    unsigned a, b, c, d;
    if (!__get_cpuid(1, &a, &b, &c, &d) || !(c & bit_SSE4_2) || !(c & bit_POPCNT)) {
        printf("no sse4.2 or popcnt, nothing to run\n");
        return 0;
    }
    int bad = 0;
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        uint8_t in[8];
        uint32_t crc;
        uint16_t h;
        uint32_t w;
        uint64_t q;
        fill(in, 8, r);
        fill(&crc, 4, r + 1);
        memcpy(&h, in, 2);
        memcpy(&w, in, 4);
        memcpy(&q, in, 8);
        uint64_t got[6] = {_mm_crc32_u8(crc, in[0]), _mm_crc32_u16(crc, h), _mm_crc32_u32(crc, w),
                           _mm_crc32_u64(crc, q), (uint64_t)_mm_popcnt_u32(w), (uint64_t)_mm_popcnt_u64(q)};
        uint64_t want[6] = {crc32c_bits(crc, in, 1), crc32c_bits(crc, in, 2), crc32c_bits(crc, in, 4),
                            crc32c_bits(crc, in, 8), (uint64_t)bits(w), (uint64_t)bits(q)};
        judge(&bad, &sum, in, NULL, 8, got, want, sizeof got);
    }
    report("crc32_and_popcnt_with_flags", bad, sum);

    bad = 0;
    sum = 0;
    uint8_t buf[64 + 8];
    fill(buf, sizeof buf, 70);
    for (size_t off = 0; off < 8; off++) {
        for (size_t len = 0; len <= 64; len++) {
            uint32_t got = pg_comp_crc32c_sse42(0xffffffffu, buf + off, len);
            uint32_t want = crc32c_bits(0xffffffffu, buf + off, len);
            judge(&bad, &sum, &len, NULL, sizeof len, &got, &want, 4);
        }
    }
    report("pg_comp_crc32c_sse42_with_flags", bad, sum);
    printf("check value %08x\n", pg_comp_crc32c_sse42(0xffffffffu, "123456789", 9) ^ 0xffffffffu);
    DONE();
}
