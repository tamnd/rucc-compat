/* The vbic family of arm_neon.h.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vbic_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x8_t, a0, 0, 0);
        ARG(int8x8_t, a1, 1, 0);
        KEEP(int8x8_t, vbic_s8(a0, a1));
    }
    SUM("vbic_s8", sum);
}

static void t_vbic_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x4_t, a0, 0, 0);
        ARG(int16x4_t, a1, 1, 0);
        KEEP(int16x4_t, vbic_s16(a0, a1));
    }
    SUM("vbic_s16", sum);
}

static void t_vbic_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x2_t, a0, 0, 0);
        ARG(int32x2_t, a1, 1, 0);
        KEEP(int32x2_t, vbic_s32(a0, a1));
    }
    SUM("vbic_s32", sum);
}

static void t_vbic_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x1_t, a0, 0, 0);
        ARG(int64x1_t, a1, 1, 0);
        KEEP(int64x1_t, vbic_s64(a0, a1));
    }
    SUM("vbic_s64", sum);
}

static void t_vbic_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x8_t, a0, 0, 0);
        ARG(uint8x8_t, a1, 1, 0);
        KEEP(uint8x8_t, vbic_u8(a0, a1));
    }
    SUM("vbic_u8", sum);
}

static void t_vbic_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x4_t, a0, 0, 0);
        ARG(uint16x4_t, a1, 1, 0);
        KEEP(uint16x4_t, vbic_u16(a0, a1));
    }
    SUM("vbic_u16", sum);
}

static void t_vbic_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x2_t, a0, 0, 0);
        ARG(uint32x2_t, a1, 1, 0);
        KEEP(uint32x2_t, vbic_u32(a0, a1));
    }
    SUM("vbic_u32", sum);
}

static void t_vbic_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x1_t, a0, 0, 0);
        ARG(uint64x1_t, a1, 1, 0);
        KEEP(uint64x1_t, vbic_u64(a0, a1));
    }
    SUM("vbic_u64", sum);
}

static void t_vbicq_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x16_t, a0, 0, 0);
        ARG(int8x16_t, a1, 1, 0);
        KEEP(int8x16_t, vbicq_s8(a0, a1));
    }
    SUM("vbicq_s8", sum);
}

static void t_vbicq_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x8_t, a0, 0, 0);
        ARG(int16x8_t, a1, 1, 0);
        KEEP(int16x8_t, vbicq_s16(a0, a1));
    }
    SUM("vbicq_s16", sum);
}

static void t_vbicq_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x4_t, a0, 0, 0);
        ARG(int32x4_t, a1, 1, 0);
        KEEP(int32x4_t, vbicq_s32(a0, a1));
    }
    SUM("vbicq_s32", sum);
}

static void t_vbicq_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x2_t, a0, 0, 0);
        ARG(int64x2_t, a1, 1, 0);
        KEEP(int64x2_t, vbicq_s64(a0, a1));
    }
    SUM("vbicq_s64", sum);
}

static void t_vbicq_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x16_t, a0, 0, 0);
        ARG(uint8x16_t, a1, 1, 0);
        KEEP(uint8x16_t, vbicq_u8(a0, a1));
    }
    SUM("vbicq_u8", sum);
}

static void t_vbicq_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x8_t, a0, 0, 0);
        ARG(uint16x8_t, a1, 1, 0);
        KEEP(uint16x8_t, vbicq_u16(a0, a1));
    }
    SUM("vbicq_u16", sum);
}

static void t_vbicq_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x4_t, a0, 0, 0);
        ARG(uint32x4_t, a1, 1, 0);
        KEEP(uint32x4_t, vbicq_u32(a0, a1));
    }
    SUM("vbicq_u32", sum);
}

static void t_vbicq_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x2_t, a0, 0, 0);
        ARG(uint64x2_t, a1, 1, 0);
        KEEP(uint64x2_t, vbicq_u64(a0, a1));
    }
    SUM("vbicq_u64", sum);
}

int main(void)
{
    t_vbic_s8();
    t_vbic_s16();
    t_vbic_s32();
    t_vbic_s64();
    t_vbic_u8();
    t_vbic_u16();
    t_vbic_u32();
    t_vbic_u64();
    t_vbicq_s8();
    t_vbicq_s16();
    t_vbicq_s32();
    t_vbicq_s64();
    t_vbicq_u8();
    t_vbicq_u16();
    t_vbicq_u32();
    t_vbicq_u64();
    return 0;
}
