/* The vdup_laneq family of arm_neon.h.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vdup_laneq_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x16_t, a0, 0, 0);
        KEEP(int8x8_t, vdup_laneq_s8(a0, 0));
        KEEP(int8x8_t, vdup_laneq_s8(a0, 7));
        KEEP(int8x8_t, vdup_laneq_s8(a0, 15));
    }
    SUM("vdup_laneq_s8", sum);
}

static void t_vdup_laneq_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x8_t, a0, 0, 0);
        KEEP(int16x4_t, vdup_laneq_s16(a0, 0));
        KEEP(int16x4_t, vdup_laneq_s16(a0, 3));
        KEEP(int16x4_t, vdup_laneq_s16(a0, 7));
    }
    SUM("vdup_laneq_s16", sum);
}

static void t_vdup_laneq_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x4_t, a0, 0, 0);
        KEEP(int32x2_t, vdup_laneq_s32(a0, 0));
        KEEP(int32x2_t, vdup_laneq_s32(a0, 1));
        KEEP(int32x2_t, vdup_laneq_s32(a0, 3));
    }
    SUM("vdup_laneq_s32", sum);
}

static void t_vdup_laneq_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x2_t, a0, 0, 0);
        KEEP(int64x1_t, vdup_laneq_s64(a0, 0));
        KEEP(int64x1_t, vdup_laneq_s64(a0, 1));
    }
    SUM("vdup_laneq_s64", sum);
}

static void t_vdup_laneq_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x16_t, a0, 0, 0);
        KEEP(uint8x8_t, vdup_laneq_u8(a0, 0));
        KEEP(uint8x8_t, vdup_laneq_u8(a0, 7));
        KEEP(uint8x8_t, vdup_laneq_u8(a0, 15));
    }
    SUM("vdup_laneq_u8", sum);
}

static void t_vdup_laneq_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x8_t, a0, 0, 0);
        KEEP(uint16x4_t, vdup_laneq_u16(a0, 0));
        KEEP(uint16x4_t, vdup_laneq_u16(a0, 3));
        KEEP(uint16x4_t, vdup_laneq_u16(a0, 7));
    }
    SUM("vdup_laneq_u16", sum);
}

static void t_vdup_laneq_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x4_t, a0, 0, 0);
        KEEP(uint32x2_t, vdup_laneq_u32(a0, 0));
        KEEP(uint32x2_t, vdup_laneq_u32(a0, 1));
        KEEP(uint32x2_t, vdup_laneq_u32(a0, 3));
    }
    SUM("vdup_laneq_u32", sum);
}

static void t_vdup_laneq_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x2_t, a0, 0, 0);
        KEEP(uint64x1_t, vdup_laneq_u64(a0, 0));
        KEEP(uint64x1_t, vdup_laneq_u64(a0, 1));
    }
    SUM("vdup_laneq_u64", sum);
}

static void t_vdup_laneq_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x4_t, a0, 0, 32);
        KEEP(float32x2_t, vdup_laneq_f32(a0, 0));
        KEEP(float32x2_t, vdup_laneq_f32(a0, 1));
        KEEP(float32x2_t, vdup_laneq_f32(a0, 3));
    }
    SUM("vdup_laneq_f32", sum);
}

static void t_vdup_laneq_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x2_t, a0, 0, 64);
        KEEP(float64x1_t, vdup_laneq_f64(a0, 0));
        KEEP(float64x1_t, vdup_laneq_f64(a0, 1));
    }
    SUM("vdup_laneq_f64", sum);
}

static void t_vdup_laneq_p8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly8x16_t, a0, 0, 0);
        KEEP(poly8x8_t, vdup_laneq_p8(a0, 0));
        KEEP(poly8x8_t, vdup_laneq_p8(a0, 7));
        KEEP(poly8x8_t, vdup_laneq_p8(a0, 15));
    }
    SUM("vdup_laneq_p8", sum);
}

static void t_vdup_laneq_p16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly16x8_t, a0, 0, 0);
        KEEP(poly16x4_t, vdup_laneq_p16(a0, 0));
        KEEP(poly16x4_t, vdup_laneq_p16(a0, 3));
        KEEP(poly16x4_t, vdup_laneq_p16(a0, 7));
    }
    SUM("vdup_laneq_p16", sum);
}

static void t_vdup_laneq_p64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly64x2_t, a0, 0, 0);
        KEEP(poly64x1_t, vdup_laneq_p64(a0, 0));
        KEEP(poly64x1_t, vdup_laneq_p64(a0, 1));
    }
    SUM("vdup_laneq_p64", sum);
}

static void t_vdupq_laneq_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x16_t, a0, 0, 0);
        KEEP(int8x16_t, vdupq_laneq_s8(a0, 0));
        KEEP(int8x16_t, vdupq_laneq_s8(a0, 7));
        KEEP(int8x16_t, vdupq_laneq_s8(a0, 15));
    }
    SUM("vdupq_laneq_s8", sum);
}

static void t_vdupq_laneq_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x8_t, a0, 0, 0);
        KEEP(int16x8_t, vdupq_laneq_s16(a0, 0));
        KEEP(int16x8_t, vdupq_laneq_s16(a0, 3));
        KEEP(int16x8_t, vdupq_laneq_s16(a0, 7));
    }
    SUM("vdupq_laneq_s16", sum);
}

static void t_vdupq_laneq_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x4_t, a0, 0, 0);
        KEEP(int32x4_t, vdupq_laneq_s32(a0, 0));
        KEEP(int32x4_t, vdupq_laneq_s32(a0, 1));
        KEEP(int32x4_t, vdupq_laneq_s32(a0, 3));
    }
    SUM("vdupq_laneq_s32", sum);
}

static void t_vdupq_laneq_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x2_t, a0, 0, 0);
        KEEP(int64x2_t, vdupq_laneq_s64(a0, 0));
        KEEP(int64x2_t, vdupq_laneq_s64(a0, 1));
    }
    SUM("vdupq_laneq_s64", sum);
}

static void t_vdupq_laneq_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x16_t, a0, 0, 0);
        KEEP(uint8x16_t, vdupq_laneq_u8(a0, 0));
        KEEP(uint8x16_t, vdupq_laneq_u8(a0, 7));
        KEEP(uint8x16_t, vdupq_laneq_u8(a0, 15));
    }
    SUM("vdupq_laneq_u8", sum);
}

static void t_vdupq_laneq_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x8_t, a0, 0, 0);
        KEEP(uint16x8_t, vdupq_laneq_u16(a0, 0));
        KEEP(uint16x8_t, vdupq_laneq_u16(a0, 3));
        KEEP(uint16x8_t, vdupq_laneq_u16(a0, 7));
    }
    SUM("vdupq_laneq_u16", sum);
}

static void t_vdupq_laneq_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x4_t, a0, 0, 0);
        KEEP(uint32x4_t, vdupq_laneq_u32(a0, 0));
        KEEP(uint32x4_t, vdupq_laneq_u32(a0, 1));
        KEEP(uint32x4_t, vdupq_laneq_u32(a0, 3));
    }
    SUM("vdupq_laneq_u32", sum);
}

static void t_vdupq_laneq_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x2_t, a0, 0, 0);
        KEEP(uint64x2_t, vdupq_laneq_u64(a0, 0));
        KEEP(uint64x2_t, vdupq_laneq_u64(a0, 1));
    }
    SUM("vdupq_laneq_u64", sum);
}

static void t_vdupq_laneq_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x4_t, a0, 0, 32);
        KEEP(float32x4_t, vdupq_laneq_f32(a0, 0));
        KEEP(float32x4_t, vdupq_laneq_f32(a0, 1));
        KEEP(float32x4_t, vdupq_laneq_f32(a0, 3));
    }
    SUM("vdupq_laneq_f32", sum);
}

static void t_vdupq_laneq_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x2_t, a0, 0, 64);
        KEEP(float64x2_t, vdupq_laneq_f64(a0, 0));
        KEEP(float64x2_t, vdupq_laneq_f64(a0, 1));
    }
    SUM("vdupq_laneq_f64", sum);
}

static void t_vdupq_laneq_p8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly8x16_t, a0, 0, 0);
        KEEP(poly8x16_t, vdupq_laneq_p8(a0, 0));
        KEEP(poly8x16_t, vdupq_laneq_p8(a0, 7));
        KEEP(poly8x16_t, vdupq_laneq_p8(a0, 15));
    }
    SUM("vdupq_laneq_p8", sum);
}

static void t_vdupq_laneq_p16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly16x8_t, a0, 0, 0);
        KEEP(poly16x8_t, vdupq_laneq_p16(a0, 0));
        KEEP(poly16x8_t, vdupq_laneq_p16(a0, 3));
        KEEP(poly16x8_t, vdupq_laneq_p16(a0, 7));
    }
    SUM("vdupq_laneq_p16", sum);
}

static void t_vdupq_laneq_p64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly64x2_t, a0, 0, 0);
        KEEP(poly64x2_t, vdupq_laneq_p64(a0, 0));
        KEEP(poly64x2_t, vdupq_laneq_p64(a0, 1));
    }
    SUM("vdupq_laneq_p64", sum);
}

int main(void)
{
    t_vdup_laneq_s8();
    t_vdup_laneq_s16();
    t_vdup_laneq_s32();
    t_vdup_laneq_s64();
    t_vdup_laneq_u8();
    t_vdup_laneq_u16();
    t_vdup_laneq_u32();
    t_vdup_laneq_u64();
    t_vdup_laneq_f32();
    t_vdup_laneq_f64();
    t_vdup_laneq_p8();
    t_vdup_laneq_p16();
    t_vdup_laneq_p64();
    t_vdupq_laneq_s8();
    t_vdupq_laneq_s16();
    t_vdupq_laneq_s32();
    t_vdupq_laneq_s64();
    t_vdupq_laneq_u8();
    t_vdupq_laneq_u16();
    t_vdupq_laneq_u32();
    t_vdupq_laneq_u64();
    t_vdupq_laneq_f32();
    t_vdupq_laneq_f64();
    t_vdupq_laneq_p8();
    t_vdupq_laneq_p16();
    t_vdupq_laneq_p64();
    return 0;
}
