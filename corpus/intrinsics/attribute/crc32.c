/* _mm_crc32_u8, _mm_crc32_u16, _mm_crc32_u32 and _mm_crc32_u64, called from functions carrying
 * __attribute__((target("sse4.2"))) in a unit built for the baseline, which is how Postgres builds
 * pg_crc32c_sse42.c when it chooses the CRC32C implementation at run time. Each step is checked
 * against CRC32C worked out a bit at a time, and so is Postgres's loop over buffers of every length
 * up to a few words and at every alignment. The check value of "123456789" is printed as well.
 * When cpuid says the processor has no SSE4.2 the program says so and checks nothing. */
#include <cpuid.h>
#include <nmmintrin.h>

#include "../check.h"
#include "../crc.h"

__attribute__((target("sse4.2"))) static uint32_t step8(uint32_t c, uint8_t v) { return _mm_crc32_u8(c, v); }
__attribute__((target("sse4.2"))) static uint32_t step16(uint32_t c, uint16_t v) { return _mm_crc32_u16(c, v); }
__attribute__((target("sse4.2"))) static uint32_t step32(uint32_t c, uint32_t v) { return _mm_crc32_u32(c, v); }
__attribute__((target("sse4.2"))) static uint64_t step64(uint64_t c, uint64_t v) { return _mm_crc32_u64(c, v); }

__attribute__((target("sse4.2"))) static uint32_t pg_comp_crc32c_sse42(uint32_t crc, const void *data, size_t len)
{
    PG_COMP_CRC32C_BODY(crc, data, len);
    return crc;
}

int main(void)
{
    unsigned a, b, c, d;
    if (!__get_cpuid(1, &a, &b, &c, &d) || !(c & bit_SSE4_2)) {
        printf("no sse4.2, nothing to check\n");
        return 0;
    }
    int bad = 0;
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        uint8_t in[8];
        uint32_t crc;
        fill(in, 8, r);
        fill(&crc, 4, r + 1);
        uint16_t h;
        uint32_t w;
        uint64_t q;
        memcpy(&h, in, 2);
        memcpy(&w, in, 4);
        memcpy(&q, in, 8);
        uint64_t got[4] = {step8(crc, in[0]), step16(crc, h), step32(crc, w), step64(crc, q)};
        uint64_t want[4] = {crc32c_bits(crc, in, 1), crc32c_bits(crc, in, 2), crc32c_bits(crc, in, 4),
                            crc32c_bits(crc, in, 8)};
        judge(&bad, &sum, in, NULL, 8, got, want, sizeof got);
        /* The sixty four bit form takes a sixty four bit running value and ignores its top half. */
        uint64_t high = step64(((uint64_t)w << 32) | crc, q);
        judge(&bad, &sum, in, NULL, 8, &high, &want[3], 8);
    }
    report("_mm_crc32_u8_u16_u32_u64", bad, sum);

    bad = 0;
    sum = 0;
    uint8_t buf[64 + 8];
    fill(buf, sizeof buf, 50);
    for (size_t off = 0; off < 8; off++) {
        for (size_t len = 0; len <= 64; len++) {
            uint32_t got = pg_comp_crc32c_sse42(0xffffffffu, buf + off, len);
            uint32_t want = crc32c_bits(0xffffffffu, buf + off, len);
            judge(&bad, &sum, &len, NULL, sizeof len, &got, &want, 4);
        }
    }
    report("pg_comp_crc32c_sse42", bad, sum);

    uint32_t check = pg_comp_crc32c_sse42(0xffffffffu, "123456789", 9) ^ 0xffffffffu;
    printf("check value %08x\n", check);
    if (check != 0xe3069283u) {
        printf("FAIL the CRC32C of 123456789 is e3069283\n");
        failures++;
    }
    DONE();
}
