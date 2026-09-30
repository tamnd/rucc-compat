/* CRC32C a bit at a time, which is what every intrinsic in the crc32 programs is checked against,
 * and Postgres's loops over the intrinsics, copied from src/port/pg_crc32c_sse42.c and
 * src/port/pg_crc32c_armv8.c. The loops are macros so that each program can build them the way it
 * builds the intrinsics: inside a function carrying the target attribute, or in a unit built with
 * -msse4.2 or -march=armv8-a+crc+simd. The plain CRC-32 of zlib is here as well, for the half of
 * arm_acle.h that has no x86 counterpart. */

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

/* The CRC-32 zlib and Ethernet use, which is what `__crc32b` and its siblings step. */
static uint32_t crc32_bits(uint32_t crc, const void *data, size_t len)
{
    const uint8_t *p = data;
    while (len--) {
        crc ^= *p++;
        for (int k = 0; k < 8; k++)
            crc = (crc >> 1) ^ (0xedb88320u & (0u - (crc & 1)));
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

/* pg_comp_crc32c_armv8 as Postgres 18 has it: a byte, a halfword and a word to bring the pointer to
 * eight byte alignment, then doublewords, then what is left. The loads are Postgres's casts rather
 * than memcpy, since that is the code rucc has to build. */
#define PG_COMP_CRC32C_ARMV8_BODY(crc, data, len)                                                \
    do {                                                                                         \
        const unsigned char *p = (data);                                                         \
        const unsigned char *pend = p + (len);                                                   \
        if ((uintptr_t)p % sizeof(uint16_t) != 0 && p + 1 <= pend) {                            \
            crc = __crc32cb(crc, *p);                                                            \
            p += 1;                                                                              \
        }                                                                                        \
        if ((uintptr_t)p % sizeof(uint32_t) != 0 && p + 2 <= pend) {                             \
            crc = __crc32ch(crc, *(uint16_t *)p);                                                \
            p += 2;                                                                              \
        }                                                                                        \
        if ((uintptr_t)p % sizeof(uint64_t) != 0 && p + 4 <= pend) {                             \
            crc = __crc32cw(crc, *(uint32_t *)p);                                                \
            p += 4;                                                                              \
        }                                                                                        \
        while (p + 8 <= pend) {                                                                  \
            crc = __crc32cd(crc, *(uint64_t *)p);                                                \
            p += 8;                                                                              \
        }                                                                                        \
        if (p + 4 <= pend) {                                                                     \
            crc = __crc32cw(crc, *(uint32_t *)p);                                                \
            p += 4;                                                                              \
        }                                                                                        \
        if (p + 2 <= pend) {                                                                     \
            crc = __crc32ch(crc, *(uint16_t *)p);                                                \
            p += 2;                                                                              \
        }                                                                                        \
        if (p < pend)                                                                            \
            crc = __crc32cb(crc, *p);                                                            \
    } while (0)

#endif
