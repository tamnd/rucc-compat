/* The vcgt family of arm_neon.h.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vcgt_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x8_t, a0, 0, 0);
        ARG(int8x8_t, a1, 1, 0);
        KEEP(uint8x8_t, vcgt_s8(a0, a1));
    }
    SUM("vcgt_s8", sum);
}

static void t_vcgt_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x4_t, a0, 0, 0);
        ARG(int16x4_t, a1, 1, 0);
        KEEP(uint16x4_t, vcgt_s16(a0, a1));
    }
    SUM("vcgt_s16", sum);
}

static void t_vcgt_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x2_t, a0, 0, 0);
        ARG(int32x2_t, a1, 1, 0);
        KEEP(uint32x2_t, vcgt_s32(a0, a1));
    }
    SUM("vcgt_s32", sum);
}

static void t_vcgt_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x1_t, a0, 0, 0);
        ARG(int64x1_t, a1, 1, 0);
        KEEP(uint64x1_t, vcgt_s64(a0, a1));
    }
    SUM("vcgt_s64", sum);
}

static void t_vcgt_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x8_t, a0, 0, 0);
        ARG(uint8x8_t, a1, 1, 0);
        KEEP(uint8x8_t, vcgt_u8(a0, a1));
    }
    SUM("vcgt_u8", sum);
}

static void t_vcgt_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x4_t, a0, 0, 0);
        ARG(uint16x4_t, a1, 1, 0);
        KEEP(uint16x4_t, vcgt_u16(a0, a1));
    }
    SUM("vcgt_u16", sum);
}

static void t_vcgt_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x2_t, a0, 0, 0);
        ARG(uint32x2_t, a1, 1, 0);
        KEEP(uint32x2_t, vcgt_u32(a0, a1));
    }
    SUM("vcgt_u32", sum);
}

static void t_vcgt_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x1_t, a0, 0, 0);
        ARG(uint64x1_t, a1, 1, 0);
        KEEP(uint64x1_t, vcgt_u64(a0, a1));
    }
    SUM("vcgt_u64", sum);
}

static void t_vcgt_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x2_t, a0, 0, 32);
        ARG(float32x2_t, a1, 1, 32);
        KEEP(uint32x2_t, vcgt_f32(a0, a1));
    }
    SUM("vcgt_f32", sum);
}

static void t_vcgt_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x1_t, a0, 0, 64);
        ARG(float64x1_t, a1, 1, 64);
        KEEP(uint64x1_t, vcgt_f64(a0, a1));
    }
    SUM("vcgt_f64", sum);
}

static void t_vcgtq_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x16_t, a0, 0, 0);
        ARG(int8x16_t, a1, 1, 0);
        KEEP(uint8x16_t, vcgtq_s8(a0, a1));
    }
    SUM("vcgtq_s8", sum);
}

static void t_vcgtq_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x8_t, a0, 0, 0);
        ARG(int16x8_t, a1, 1, 0);
        KEEP(uint16x8_t, vcgtq_s16(a0, a1));
    }
    SUM("vcgtq_s16", sum);
}

static void t_vcgtq_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x4_t, a0, 0, 0);
        ARG(int32x4_t, a1, 1, 0);
        KEEP(uint32x4_t, vcgtq_s32(a0, a1));
    }
    SUM("vcgtq_s32", sum);
}

static void t_vcgtq_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x2_t, a0, 0, 0);
        ARG(int64x2_t, a1, 1, 0);
        KEEP(uint64x2_t, vcgtq_s64(a0, a1));
    }
    SUM("vcgtq_s64", sum);
}

static void t_vcgtq_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x16_t, a0, 0, 0);
        ARG(uint8x16_t, a1, 1, 0);
        KEEP(uint8x16_t, vcgtq_u8(a0, a1));
    }
    SUM("vcgtq_u8", sum);
}

static void t_vcgtq_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x8_t, a0, 0, 0);
        ARG(uint16x8_t, a1, 1, 0);
        KEEP(uint16x8_t, vcgtq_u16(a0, a1));
    }
    SUM("vcgtq_u16", sum);
}

static void t_vcgtq_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x4_t, a0, 0, 0);
        ARG(uint32x4_t, a1, 1, 0);
        KEEP(uint32x4_t, vcgtq_u32(a0, a1));
    }
    SUM("vcgtq_u32", sum);
}

static void t_vcgtq_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x2_t, a0, 0, 0);
        ARG(uint64x2_t, a1, 1, 0);
        KEEP(uint64x2_t, vcgtq_u64(a0, a1));
    }
    SUM("vcgtq_u64", sum);
}

static void t_vcgtq_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x4_t, a0, 0, 32);
        ARG(float32x4_t, a1, 1, 32);
        KEEP(uint32x4_t, vcgtq_f32(a0, a1));
    }
    SUM("vcgtq_f32", sum);
}

static void t_vcgtq_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x2_t, a0, 0, 64);
        ARG(float64x2_t, a1, 1, 64);
        KEEP(uint64x2_t, vcgtq_f64(a0, a1));
    }
    SUM("vcgtq_f64", sum);
}

int main(void)
{
    t_vcgt_s8();
    t_vcgt_s16();
    t_vcgt_s32();
    t_vcgt_s64();
    t_vcgt_u8();
    t_vcgt_u16();
    t_vcgt_u32();
    t_vcgt_u64();
    t_vcgt_f32();
    t_vcgt_f64();
    t_vcgtq_s8();
    t_vcgtq_s16();
    t_vcgtq_s32();
    t_vcgtq_s64();
    t_vcgtq_u8();
    t_vcgtq_u16();
    t_vcgtq_u32();
    t_vcgtq_u64();
    t_vcgtq_f32();
    t_vcgtq_f64();
    return 0;
}
