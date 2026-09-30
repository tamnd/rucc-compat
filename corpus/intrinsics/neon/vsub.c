/* The vsub family of arm_neon.h.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vsub_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x8_t, a0, 0, 0);
        ARG(int8x8_t, a1, 1, 0);
        KEEP(int8x8_t, vsub_s8(a0, a1));
    }
    SUM("vsub_s8", sum);
}

static void t_vsub_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x4_t, a0, 0, 0);
        ARG(int16x4_t, a1, 1, 0);
        KEEP(int16x4_t, vsub_s16(a0, a1));
    }
    SUM("vsub_s16", sum);
}

static void t_vsub_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x2_t, a0, 0, 0);
        ARG(int32x2_t, a1, 1, 0);
        KEEP(int32x2_t, vsub_s32(a0, a1));
    }
    SUM("vsub_s32", sum);
}

static void t_vsub_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x1_t, a0, 0, 0);
        ARG(int64x1_t, a1, 1, 0);
        KEEP(int64x1_t, vsub_s64(a0, a1));
    }
    SUM("vsub_s64", sum);
}

static void t_vsub_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x8_t, a0, 0, 0);
        ARG(uint8x8_t, a1, 1, 0);
        KEEP(uint8x8_t, vsub_u8(a0, a1));
    }
    SUM("vsub_u8", sum);
}

static void t_vsub_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x4_t, a0, 0, 0);
        ARG(uint16x4_t, a1, 1, 0);
        KEEP(uint16x4_t, vsub_u16(a0, a1));
    }
    SUM("vsub_u16", sum);
}

static void t_vsub_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x2_t, a0, 0, 0);
        ARG(uint32x2_t, a1, 1, 0);
        KEEP(uint32x2_t, vsub_u32(a0, a1));
    }
    SUM("vsub_u32", sum);
}

static void t_vsub_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x1_t, a0, 0, 0);
        ARG(uint64x1_t, a1, 1, 0);
        KEEP(uint64x1_t, vsub_u64(a0, a1));
    }
    SUM("vsub_u64", sum);
}

static void t_vsub_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x2_t, a0, 0, 32);
        ARG(float32x2_t, a1, 1, 32);
        KEEP(float32x2_t, vsub_f32(a0, a1));
    }
    SUM("vsub_f32", sum);
}

static void t_vsub_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x1_t, a0, 0, 64);
        ARG(float64x1_t, a1, 1, 64);
        KEEP(float64x1_t, vsub_f64(a0, a1));
    }
    SUM("vsub_f64", sum);
}

static void t_vsubq_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x16_t, a0, 0, 0);
        ARG(int8x16_t, a1, 1, 0);
        KEEP(int8x16_t, vsubq_s8(a0, a1));
    }
    SUM("vsubq_s8", sum);
}

static void t_vsubq_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x8_t, a0, 0, 0);
        ARG(int16x8_t, a1, 1, 0);
        KEEP(int16x8_t, vsubq_s16(a0, a1));
    }
    SUM("vsubq_s16", sum);
}

static void t_vsubq_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x4_t, a0, 0, 0);
        ARG(int32x4_t, a1, 1, 0);
        KEEP(int32x4_t, vsubq_s32(a0, a1));
    }
    SUM("vsubq_s32", sum);
}

static void t_vsubq_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x2_t, a0, 0, 0);
        ARG(int64x2_t, a1, 1, 0);
        KEEP(int64x2_t, vsubq_s64(a0, a1));
    }
    SUM("vsubq_s64", sum);
}

static void t_vsubq_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x16_t, a0, 0, 0);
        ARG(uint8x16_t, a1, 1, 0);
        KEEP(uint8x16_t, vsubq_u8(a0, a1));
    }
    SUM("vsubq_u8", sum);
}

static void t_vsubq_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x8_t, a0, 0, 0);
        ARG(uint16x8_t, a1, 1, 0);
        KEEP(uint16x8_t, vsubq_u16(a0, a1));
    }
    SUM("vsubq_u16", sum);
}

static void t_vsubq_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x4_t, a0, 0, 0);
        ARG(uint32x4_t, a1, 1, 0);
        KEEP(uint32x4_t, vsubq_u32(a0, a1));
    }
    SUM("vsubq_u32", sum);
}

static void t_vsubq_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x2_t, a0, 0, 0);
        ARG(uint64x2_t, a1, 1, 0);
        KEEP(uint64x2_t, vsubq_u64(a0, a1));
    }
    SUM("vsubq_u64", sum);
}

static void t_vsubq_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x4_t, a0, 0, 32);
        ARG(float32x4_t, a1, 1, 32);
        KEEP(float32x4_t, vsubq_f32(a0, a1));
    }
    SUM("vsubq_f32", sum);
}

static void t_vsubq_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x2_t, a0, 0, 64);
        ARG(float64x2_t, a1, 1, 64);
        KEEP(float64x2_t, vsubq_f64(a0, a1));
    }
    SUM("vsubq_f64", sum);
}

int main(void)
{
    t_vsub_s8();
    t_vsub_s16();
    t_vsub_s32();
    t_vsub_s64();
    t_vsub_u8();
    t_vsub_u16();
    t_vsub_u32();
    t_vsub_u64();
    t_vsub_f32();
    t_vsub_f64();
    t_vsubq_s8();
    t_vsubq_s16();
    t_vsubq_s32();
    t_vsubq_s64();
    t_vsubq_u8();
    t_vsubq_u16();
    t_vsubq_u32();
    t_vsubq_u64();
    t_vsubq_f32();
    t_vsubq_f64();
    return 0;
}
