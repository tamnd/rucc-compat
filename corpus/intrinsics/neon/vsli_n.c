/* The vsli_n family of arm_neon.h.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vsli_n_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x8_t, a0, 0, 0);
        ARG(int8x8_t, a1, 1, 0);
        KEEP(int8x8_t, vsli_n_s8(a0, a1, 0));
        KEEP(int8x8_t, vsli_n_s8(a0, a1, 3));
        KEEP(int8x8_t, vsli_n_s8(a0, a1, 7));
    }
    SUM("vsli_n_s8", sum);
}

static void t_vsli_n_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x4_t, a0, 0, 0);
        ARG(int16x4_t, a1, 1, 0);
        KEEP(int16x4_t, vsli_n_s16(a0, a1, 0));
        KEEP(int16x4_t, vsli_n_s16(a0, a1, 7));
        KEEP(int16x4_t, vsli_n_s16(a0, a1, 15));
    }
    SUM("vsli_n_s16", sum);
}

static void t_vsli_n_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x2_t, a0, 0, 0);
        ARG(int32x2_t, a1, 1, 0);
        KEEP(int32x2_t, vsli_n_s32(a0, a1, 0));
        KEEP(int32x2_t, vsli_n_s32(a0, a1, 15));
        KEEP(int32x2_t, vsli_n_s32(a0, a1, 31));
    }
    SUM("vsli_n_s32", sum);
}

static void t_vsli_n_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x1_t, a0, 0, 0);
        ARG(int64x1_t, a1, 1, 0);
        KEEP(int64x1_t, vsli_n_s64(a0, a1, 0));
        KEEP(int64x1_t, vsli_n_s64(a0, a1, 31));
        KEEP(int64x1_t, vsli_n_s64(a0, a1, 63));
    }
    SUM("vsli_n_s64", sum);
}

static void t_vsli_n_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x8_t, a0, 0, 0);
        ARG(uint8x8_t, a1, 1, 0);
        KEEP(uint8x8_t, vsli_n_u8(a0, a1, 0));
        KEEP(uint8x8_t, vsli_n_u8(a0, a1, 3));
        KEEP(uint8x8_t, vsli_n_u8(a0, a1, 7));
    }
    SUM("vsli_n_u8", sum);
}

static void t_vsli_n_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x4_t, a0, 0, 0);
        ARG(uint16x4_t, a1, 1, 0);
        KEEP(uint16x4_t, vsli_n_u16(a0, a1, 0));
        KEEP(uint16x4_t, vsli_n_u16(a0, a1, 7));
        KEEP(uint16x4_t, vsli_n_u16(a0, a1, 15));
    }
    SUM("vsli_n_u16", sum);
}

static void t_vsli_n_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x2_t, a0, 0, 0);
        ARG(uint32x2_t, a1, 1, 0);
        KEEP(uint32x2_t, vsli_n_u32(a0, a1, 0));
        KEEP(uint32x2_t, vsli_n_u32(a0, a1, 15));
        KEEP(uint32x2_t, vsli_n_u32(a0, a1, 31));
    }
    SUM("vsli_n_u32", sum);
}

static void t_vsli_n_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x1_t, a0, 0, 0);
        ARG(uint64x1_t, a1, 1, 0);
        KEEP(uint64x1_t, vsli_n_u64(a0, a1, 0));
        KEEP(uint64x1_t, vsli_n_u64(a0, a1, 31));
        KEEP(uint64x1_t, vsli_n_u64(a0, a1, 63));
    }
    SUM("vsli_n_u64", sum);
}

static void t_vsliq_n_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x16_t, a0, 0, 0);
        ARG(int8x16_t, a1, 1, 0);
        KEEP(int8x16_t, vsliq_n_s8(a0, a1, 0));
        KEEP(int8x16_t, vsliq_n_s8(a0, a1, 3));
        KEEP(int8x16_t, vsliq_n_s8(a0, a1, 7));
    }
    SUM("vsliq_n_s8", sum);
}

static void t_vsliq_n_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x8_t, a0, 0, 0);
        ARG(int16x8_t, a1, 1, 0);
        KEEP(int16x8_t, vsliq_n_s16(a0, a1, 0));
        KEEP(int16x8_t, vsliq_n_s16(a0, a1, 7));
        KEEP(int16x8_t, vsliq_n_s16(a0, a1, 15));
    }
    SUM("vsliq_n_s16", sum);
}

static void t_vsliq_n_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x4_t, a0, 0, 0);
        ARG(int32x4_t, a1, 1, 0);
        KEEP(int32x4_t, vsliq_n_s32(a0, a1, 0));
        KEEP(int32x4_t, vsliq_n_s32(a0, a1, 15));
        KEEP(int32x4_t, vsliq_n_s32(a0, a1, 31));
    }
    SUM("vsliq_n_s32", sum);
}

static void t_vsliq_n_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x2_t, a0, 0, 0);
        ARG(int64x2_t, a1, 1, 0);
        KEEP(int64x2_t, vsliq_n_s64(a0, a1, 0));
        KEEP(int64x2_t, vsliq_n_s64(a0, a1, 31));
        KEEP(int64x2_t, vsliq_n_s64(a0, a1, 63));
    }
    SUM("vsliq_n_s64", sum);
}

static void t_vsliq_n_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x16_t, a0, 0, 0);
        ARG(uint8x16_t, a1, 1, 0);
        KEEP(uint8x16_t, vsliq_n_u8(a0, a1, 0));
        KEEP(uint8x16_t, vsliq_n_u8(a0, a1, 3));
        KEEP(uint8x16_t, vsliq_n_u8(a0, a1, 7));
    }
    SUM("vsliq_n_u8", sum);
}

static void t_vsliq_n_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x8_t, a0, 0, 0);
        ARG(uint16x8_t, a1, 1, 0);
        KEEP(uint16x8_t, vsliq_n_u16(a0, a1, 0));
        KEEP(uint16x8_t, vsliq_n_u16(a0, a1, 7));
        KEEP(uint16x8_t, vsliq_n_u16(a0, a1, 15));
    }
    SUM("vsliq_n_u16", sum);
}

static void t_vsliq_n_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x4_t, a0, 0, 0);
        ARG(uint32x4_t, a1, 1, 0);
        KEEP(uint32x4_t, vsliq_n_u32(a0, a1, 0));
        KEEP(uint32x4_t, vsliq_n_u32(a0, a1, 15));
        KEEP(uint32x4_t, vsliq_n_u32(a0, a1, 31));
    }
    SUM("vsliq_n_u32", sum);
}

static void t_vsliq_n_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x2_t, a0, 0, 0);
        ARG(uint64x2_t, a1, 1, 0);
        KEEP(uint64x2_t, vsliq_n_u64(a0, a1, 0));
        KEEP(uint64x2_t, vsliq_n_u64(a0, a1, 31));
        KEEP(uint64x2_t, vsliq_n_u64(a0, a1, 63));
    }
    SUM("vsliq_n_u64", sum);
}

int main(void)
{
    t_vsli_n_s8();
    t_vsli_n_s16();
    t_vsli_n_s32();
    t_vsli_n_s64();
    t_vsli_n_u8();
    t_vsli_n_u16();
    t_vsli_n_u32();
    t_vsli_n_u64();
    t_vsliq_n_s8();
    t_vsliq_n_s16();
    t_vsliq_n_s32();
    t_vsliq_n_s64();
    t_vsliq_n_u8();
    t_vsliq_n_u16();
    t_vsliq_n_u32();
    t_vsliq_n_u64();
    return 0;
}
