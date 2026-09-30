/* The eight CRC32 intrinsics of arm_acle.h, called from functions carrying
 * __attribute__((target("+crc"))) in a unit built for the baseline, which is plain armv8-a and has
 * no CRC32 extension. That is how Postgres builds the steps when it chooses between them and the
 * portable loop at run time. `__crc32b`, `__crc32h`, `__crc32w` and `__crc32d` are checked against
 * zlib's CRC-32 a bit at a time, `__crc32cb`, `__crc32ch`, `__crc32cw` and `__crc32cd` against
 * CRC32C, and Postgres's loop over the last four against CRC32C over buffers of every length up to
 * a few words at every alignment. Whether the baseline defines __ARM_FEATURE_CRC32 is printed first,
 * since configure reads it. When the machine has no CRC32 the program says so and checks nothing. */
#include <arm_acle.h>

#include "../arm.h"
#include "../check.h"
#include "../crc.h"

#define STEP(NAME, T) \
    __attribute__((target("+crc"))) static uint32_t step_##NAME(uint32_t c, T v) { return NAME(c, v); }
STEP(__crc32b, uint8_t)
STEP(__crc32h, uint16_t)
STEP(__crc32w, uint32_t)
STEP(__crc32d, uint64_t)
STEP(__crc32cb, uint8_t)
STEP(__crc32ch, uint16_t)
STEP(__crc32cw, uint32_t)
STEP(__crc32cd, uint64_t)

__attribute__((target("+crc"))) static uint32_t pg_comp_crc32c_armv8(uint32_t crc, const void *data, size_t len)
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
        uint32_t got[8] = {step___crc32b(crc, in[0]),  step___crc32h(crc, h),  step___crc32w(crc, w),
                           step___crc32d(crc, q),      step___crc32cb(crc, in[0]), step___crc32ch(crc, h),
                           step___crc32cw(crc, w),     step___crc32cd(crc, q)};
        uint32_t want[8] = {crc32_bits(crc, in, 1),  crc32_bits(crc, in, 2),  crc32_bits(crc, in, 4),
                            crc32_bits(crc, in, 8),  crc32c_bits(crc, in, 1), crc32c_bits(crc, in, 2),
                            crc32c_bits(crc, in, 4), crc32c_bits(crc, in, 8)};
        judge(&bad, &sum, in, NULL, 8, got, want, sizeof got);
    }
    report("__crc32b_h_w_d_and_cb_ch_cw_cd", bad, sum);

    bad = 0;
    sum = 0;
    uint64_t words[9];
    uint8_t *buf = (uint8_t *)words;
    fill(buf, sizeof words, 50);
    for (size_t off = 0; off < 8; off++) {
        for (size_t len = 0; len <= 64; len++) {
            uint32_t got = pg_comp_crc32c_armv8(0xffffffffu, buf + off, len);
            uint32_t want = crc32c_bits(0xffffffffu, buf + off, len);
            judge(&bad, &sum, &len, NULL, sizeof len, &got, &want, 4);
        }
    }
    report("pg_comp_crc32c_armv8", bad, sum);

    uint32_t check = pg_comp_crc32c_armv8(0xffffffffu, "123456789", 9) ^ 0xffffffffu;
    printf("check value %08x\n", check);
    if (check != 0xe3069283u) {
        printf("FAIL the CRC32C of 123456789 is e3069283\n");
        failures++;
    }
    uint32_t zlib = 0xffffffffu;
    for (const char *s = "123456789"; *s; s++)
        zlib = step___crc32b(zlib, (uint8_t)*s);
    zlib ^= 0xffffffffu;
    printf("zlib check value %08x\n", zlib);
    if (zlib != 0xcbf43926u) {
        printf("FAIL the CRC-32 of 123456789 is cbf43926\n");
        failures++;
    }
    DONE();
}
