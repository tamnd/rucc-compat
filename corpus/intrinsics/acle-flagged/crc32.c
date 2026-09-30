/* The eight CRC32 intrinsics of arm_acle.h in a unit built with -march=armv8-a+crc+simd and no
 * target attribute anywhere, which is the flag Postgres's configure tries when the baseline refuses
 * them, and how it builds src/port/pg_crc32c_armv8.c. The macros the flag defines are printed
 * first, since configure and Postgres's own headers read them to decide which path to build. The
 * run is guarded like the other, because a unit built for the extension is still allowed to be run
 * somewhere without it. */
#include <arm_acle.h>

#include "../arm.h"
#include "../check.h"
#include "../crc.h"

static uint32_t pg_comp_crc32c_armv8(uint32_t crc, const void *data, size_t len)
{
    PG_COMP_CRC32C_ARMV8_BODY(crc, data, len);
    return crc;
}

int main(void)
{
#ifdef __ARM_FEATURE_CRC32
    printf("__ARM_FEATURE_CRC32 1\n");
#else
    printf("__ARM_FEATURE_CRC32 0\n");
#endif
#ifdef __ARM_NEON
    printf("__ARM_NEON 1\n");
#else
    printf("__ARM_NEON 0\n");
#endif
    if (!have_crc32()) {
        printf("no crc32, nothing to check\n");
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
        uint32_t got[8] = {__crc32b(crc, in[0]),  __crc32h(crc, h),  __crc32w(crc, w),  __crc32d(crc, q),
                           __crc32cb(crc, in[0]), __crc32ch(crc, h), __crc32cw(crc, w), __crc32cd(crc, q)};
        uint32_t want[8] = {crc32_bits(crc, in, 1),  crc32_bits(crc, in, 2),  crc32_bits(crc, in, 4),
                            crc32_bits(crc, in, 8),  crc32c_bits(crc, in, 1), crc32c_bits(crc, in, 2),
                            crc32c_bits(crc, in, 4), crc32c_bits(crc, in, 8)};
        judge(&bad, &sum, in, NULL, 8, got, want, sizeof got);
    }
    report("__crc32b_h_w_d_and_cb_ch_cw_cd_with_flags", bad, sum);

    bad = 0;
    sum = 0;
    uint64_t words[9];
    uint8_t *buf = (uint8_t *)words;
    fill(buf, sizeof words, 70);
    for (size_t off = 0; off < 8; off++) {
        for (size_t len = 0; len <= 64; len++) {
            uint32_t got = pg_comp_crc32c_armv8(0xffffffffu, buf + off, len);
            uint32_t want = crc32c_bits(0xffffffffu, buf + off, len);
            judge(&bad, &sum, &len, NULL, sizeof len, &got, &want, 4);
        }
    }
    report("pg_comp_crc32c_armv8_with_flags", bad, sum);
    printf("check value %08x\n", pg_comp_crc32c_armv8(0xffffffffu, "123456789", 9) ^ 0xffffffffu);
    DONE();
}
