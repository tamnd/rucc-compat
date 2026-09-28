/* CRC32C a bit at a time, which is what every intrinsic in the crc32 programs is checked against,
 * and Postgres's loop over the intrinsics, copied from src/port/pg_crc32c_sse42.c. The loop is a
 * macro so that each program can build it the way it builds the intrinsics: inside a function
 * carrying the target attribute, or in a unit built with -msse4.2. */

#ifndef INTRINSICS_CRC_H
#define INTRINSICS_CRC_H

#include <stddef.h>
#include <stdint.h>

static uint32_t crc32c_bits(uint32_t crc, const void *data, size_t len)
{
    const uint8_t *p = data;
    while (len--) {
        crc ^= *p++;
        for (int k = 0; k < 8; k++)
            crc = (crc >> 1) ^ (0x82f63b78u & (0u - (crc & 1)));
    }
    return crc;
}

#define PG_COMP_CRC32C_BODY(crc, data, len)                                                      \
    do {                                                                                         \
        const unsigned char *p = (data);                                                         \
        const unsigned char *pend = p + (len);                                                   \
        while (p + 8 <= pend) {                                                                  \
            uint64_t word_;                                                                      \
            memcpy(&word_, p, 8);                                                                \
            crc = (uint32_t)_mm_crc32_u64(crc, word_);                                           \
            p += 8;                                                                              \
        }                                                                                        \
        if (p + 4 <= pend) {                                                                     \
            uint32_t word_;                                                                      \
            memcpy(&word_, p, 4);                                                                \
            crc = _mm_crc32_u32(crc, word_);                                                     \
            p += 4;                                                                              \
        }                                                                                        \
        while (p < pend) {                                                                       \
            crc = _mm_crc32_u8(crc, *p);                                                         \
            p++;                                                                                 \
        }                                                                                        \
    } while (0)

#endif
