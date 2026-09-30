/* The vcge family of arm_neon.h.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vcge_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x8_t, a0, 0, 0);
        ARG(int8x8_t, a1, 1, 0);
        KEEP(uint8x8_t, vcge_s8(a0, a1));
    }
    SUM("vcge_s8", sum);
}

static void t_vcge_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x4_t, a0, 0, 0);
        ARG(int16x4_t, a1, 1, 0);
        KEEP(uint16x4_t, vcge_s16(a0, a1));
    }
    SUM("vcge_s16", sum);
}

static void t_vcge_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x2_t, a0, 0, 0);
        ARG(int32x2_t, a1, 1, 0);
        KEEP(uint32x2_t, vcge_s32(a0, a1));
    }
    SUM("vcge_s32", sum);
}

static void t_vcge_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x1_t, a0, 0, 0);
        ARG(int64x1_t, a1, 1, 0);
        KEEP(uint64x1_t, vcge_s64(a0, a1));
    }
    SUM("vcge_s64", sum);
}

static void t_vcge_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x8_t, a0, 0, 0);
        ARG(uint8x8_t, a1, 1, 0);
        KEEP(uint8x8_t, vcge_u8(a0, a1));
    }
    SUM("vcge_u8", sum);
}

static void t_vcge_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x4_t, a0, 0, 0);
        ARG(uint16x4_t, a1, 1, 0);
        KEEP(uint16x4_t, vcge_u16(a0, a1));
    }
    SUM("vcge_u16", sum);
}

static void t_vcge_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x2_t, a0, 0, 0);
        ARG(uint32x2_t, a1, 1, 0);
        KEEP(uint32x2_t, vcge_u32(a0, a1));
    }
    SUM("vcge_u32", sum);
}

static void t_vcge_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x1_t, a0, 0, 0);
        ARG(uint64x1_t, a1, 1, 0);
        KEEP(uint64x1_t, vcge_u64(a0, a1));
    }
    SUM("vcge_u64", sum);
}

static void t_vcge_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x2_t, a0, 0, 32);
        ARG(float32x2_t, a1, 1, 32);
        KEEP(uint32x2_t, vcge_f32(a0, a1));
    }
    SUM("vcge_f32", sum);
}

static void t_vcge_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x1_t, a0, 0, 64);
        ARG(float64x1_t, a1, 1, 64);
        KEEP(uint64x1_t, vcge_f64(a0, a1));
    }
    SUM("vcge_f64", sum);
}

static void t_vcgeq_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x16_t, a0, 0, 0);
        ARG(int8x16_t, a1, 1, 0);
        KEEP(uint8x16_t, vcgeq_s8(a0, a1));
    }
    SUM("vcgeq_s8", sum);
}

static void t_vcgeq_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x8_t, a0, 0, 0);
        ARG(int16x8_t, a1, 1, 0);
        KEEP(uint16x8_t, vcgeq_s16(a0, a1));
    }
    SUM("vcgeq_s16", sum);
}

static void t_vcgeq_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x4_t, a0, 0, 0);
        ARG(int32x4_t, a1, 1, 0);
        KEEP(uint32x4_t, vcgeq_s32(a0, a1));
    }
    SUM("vcgeq_s32", sum);
}

static void t_vcgeq_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x2_t, a0, 0, 0);
        ARG(int64x2_t, a1, 1, 0);
        KEEP(uint64x2_t, vcgeq_s64(a0, a1));
    }
    SUM("vcgeq_s64", sum);
}

static void t_vcgeq_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x16_t, a0, 0, 0);
        ARG(uint8x16_t, a1, 1, 0);
        KEEP(uint8x16_t, vcgeq_u8(a0, a1));
    }
    SUM("vcgeq_u8", sum);
}

static void t_vcgeq_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x8_t, a0, 0, 0);
        ARG(uint16x8_t, a1, 1, 0);
        KEEP(uint16x8_t, vcgeq_u16(a0, a1));
    }
    SUM("vcgeq_u16", sum);
}

static void t_vcgeq_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x4_t, a0, 0, 0);
        ARG(uint32x4_t, a1, 1, 0);
        KEEP(uint32x4_t, vcgeq_u32(a0, a1));
    }
    SUM("vcgeq_u32", sum);
}

static void t_vcgeq_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x2_t, a0, 0, 0);
        ARG(uint64x2_t, a1, 1, 0);
        KEEP(uint64x2_t, vcgeq_u64(a0, a1));
    }
    SUM("vcgeq_u64", sum);
}

static void t_vcgeq_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x4_t, a0, 0, 32);
        ARG(float32x4_t, a1, 1, 32);
        KEEP(uint32x4_t, vcgeq_f32(a0, a1));
    }
    SUM("vcgeq_f32", sum);
}

static void t_vcgeq_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x2_t, a0, 0, 64);
        ARG(float64x2_t, a1, 1, 64);
        KEEP(uint64x2_t, vcgeq_f64(a0, a1));
    }
    SUM("vcgeq_f64", sum);
}

int main(void)
{
    t_vcge_s8();
    t_vcge_s16();
    t_vcge_s32();
    t_vcge_s64();
    t_vcge_u8();
    t_vcge_u16();
    t_vcge_u32();
    t_vcge_u64();
    t_vcge_f32();
    t_vcge_f64();
    t_vcgeq_s8();
    t_vcgeq_s16();
    t_vcgeq_s32();
    t_vcgeq_s64();
    t_vcgeq_u8();
    t_vcgeq_u16();
    t_vcgeq_u32();
    t_vcgeq_u64();
    t_vcgeq_f32();
    t_vcgeq_f64();
    return 0;
}
