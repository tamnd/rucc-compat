/* The vbsl family of arm_neon.h.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vbsl_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x8_t, a0, 0, 0);
        ARG(int8x8_t, a1, 1, 0);
        ARG(int8x8_t, a2, 2, 0);
        KEEP(int8x8_t, vbsl_s8(a0, a1, a2));
    }
    SUM("vbsl_s8", sum);
}

static void t_vbsl_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x4_t, a0, 0, 0);
        ARG(int16x4_t, a1, 1, 0);
        ARG(int16x4_t, a2, 2, 0);
        KEEP(int16x4_t, vbsl_s16(a0, a1, a2));
    }
    SUM("vbsl_s16", sum);
}

static void t_vbsl_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x2_t, a0, 0, 0);
        ARG(int32x2_t, a1, 1, 0);
        ARG(int32x2_t, a2, 2, 0);
        KEEP(int32x2_t, vbsl_s32(a0, a1, a2));
    }
    SUM("vbsl_s32", sum);
}

static void t_vbsl_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x1_t, a0, 0, 0);
        ARG(int64x1_t, a1, 1, 0);
        ARG(int64x1_t, a2, 2, 0);
        KEEP(int64x1_t, vbsl_s64(a0, a1, a2));
    }
    SUM("vbsl_s64", sum);
}

static void t_vbsl_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x8_t, a0, 0, 0);
        ARG(uint8x8_t, a1, 1, 0);
        ARG(uint8x8_t, a2, 2, 0);
        KEEP(uint8x8_t, vbsl_u8(a0, a1, a2));
    }
    SUM("vbsl_u8", sum);
}

static void t_vbsl_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x4_t, a0, 0, 0);
        ARG(uint16x4_t, a1, 1, 0);
        ARG(uint16x4_t, a2, 2, 0);
        KEEP(uint16x4_t, vbsl_u16(a0, a1, a2));
    }
    SUM("vbsl_u16", sum);
}

static void t_vbsl_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x2_t, a0, 0, 0);
        ARG(uint32x2_t, a1, 1, 0);
        ARG(uint32x2_t, a2, 2, 0);
        KEEP(uint32x2_t, vbsl_u32(a0, a1, a2));
    }
    SUM("vbsl_u32", sum);
}

static void t_vbsl_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x1_t, a0, 0, 0);
        ARG(uint64x1_t, a1, 1, 0);
        ARG(uint64x1_t, a2, 2, 0);
        KEEP(uint64x1_t, vbsl_u64(a0, a1, a2));
    }
    SUM("vbsl_u64", sum);
}

static void t_vbsl_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x2_t, a0, 0, 0);
        ARG(float32x2_t, a1, 1, 32);
        ARG(float32x2_t, a2, 2, 32);
        KEEP(float32x2_t, vbsl_f32(a0, a1, a2));
    }
    SUM("vbsl_f32", sum);
}

static void t_vbsl_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x1_t, a0, 0, 0);
        ARG(float64x1_t, a1, 1, 64);
        ARG(float64x1_t, a2, 2, 64);
        KEEP(float64x1_t, vbsl_f64(a0, a1, a2));
    }
    SUM("vbsl_f64", sum);
}

static void t_vbsl_p8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x8_t, a0, 0, 0);
        ARG(poly8x8_t, a1, 1, 0);
        ARG(poly8x8_t, a2, 2, 0);
        KEEP(poly8x8_t, vbsl_p8(a0, a1, a2));
    }
    SUM("vbsl_p8", sum);
}

static void t_vbsl_p16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x4_t, a0, 0, 0);
        ARG(poly16x4_t, a1, 1, 0);
        ARG(poly16x4_t, a2, 2, 0);
        KEEP(poly16x4_t, vbsl_p16(a0, a1, a2));
    }
    SUM("vbsl_p16", sum);
}

static void t_vbsl_p64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x1_t, a0, 0, 0);
        ARG(poly64x1_t, a1, 1, 0);
        ARG(poly64x1_t, a2, 2, 0);
        KEEP(poly64x1_t, vbsl_p64(a0, a1, a2));
    }
    SUM("vbsl_p64", sum);
}

static void t_vbslq_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x16_t, a0, 0, 0);
        ARG(int8x16_t, a1, 1, 0);
        ARG(int8x16_t, a2, 2, 0);
        KEEP(int8x16_t, vbslq_s8(a0, a1, a2));
    }
    SUM("vbslq_s8", sum);
}

static void t_vbslq_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x8_t, a0, 0, 0);
        ARG(int16x8_t, a1, 1, 0);
        ARG(int16x8_t, a2, 2, 0);
        KEEP(int16x8_t, vbslq_s16(a0, a1, a2));
    }
    SUM("vbslq_s16", sum);
}

static void t_vbslq_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x4_t, a0, 0, 0);
        ARG(int32x4_t, a1, 1, 0);
        ARG(int32x4_t, a2, 2, 0);
        KEEP(int32x4_t, vbslq_s32(a0, a1, a2));
    }
    SUM("vbslq_s32", sum);
}

static void t_vbslq_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x2_t, a0, 0, 0);
        ARG(int64x2_t, a1, 1, 0);
        ARG(int64x2_t, a2, 2, 0);
        KEEP(int64x2_t, vbslq_s64(a0, a1, a2));
    }
    SUM("vbslq_s64", sum);
}

static void t_vbslq_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x16_t, a0, 0, 0);
        ARG(uint8x16_t, a1, 1, 0);
        ARG(uint8x16_t, a2, 2, 0);
        KEEP(uint8x16_t, vbslq_u8(a0, a1, a2));
    }
    SUM("vbslq_u8", sum);
}

static void t_vbslq_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x8_t, a0, 0, 0);
        ARG(uint16x8_t, a1, 1, 0);
        ARG(uint16x8_t, a2, 2, 0);
        KEEP(uint16x8_t, vbslq_u16(a0, a1, a2));
    }
    SUM("vbslq_u16", sum);
}

static void t_vbslq_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x4_t, a0, 0, 0);
        ARG(uint32x4_t, a1, 1, 0);
        ARG(uint32x4_t, a2, 2, 0);
        KEEP(uint32x4_t, vbslq_u32(a0, a1, a2));
    }
    SUM("vbslq_u32", sum);
}

static void t_vbslq_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x2_t, a0, 0, 0);
        ARG(uint64x2_t, a1, 1, 0);
        ARG(uint64x2_t, a2, 2, 0);
        KEEP(uint64x2_t, vbslq_u64(a0, a1, a2));
    }
    SUM("vbslq_u64", sum);
}

static void t_vbslq_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x4_t, a0, 0, 0);
        ARG(float32x4_t, a1, 1, 32);
        ARG(float32x4_t, a2, 2, 32);
        KEEP(float32x4_t, vbslq_f32(a0, a1, a2));
    }
    SUM("vbslq_f32", sum);
}

static void t_vbslq_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x2_t, a0, 0, 0);
        ARG(float64x2_t, a1, 1, 64);
        ARG(float64x2_t, a2, 2, 64);
        KEEP(float64x2_t, vbslq_f64(a0, a1, a2));
    }
    SUM("vbslq_f64", sum);
}

static void t_vbslq_p8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x16_t, a0, 0, 0);
        ARG(poly8x16_t, a1, 1, 0);
        ARG(poly8x16_t, a2, 2, 0);
        KEEP(poly8x16_t, vbslq_p8(a0, a1, a2));
    }
    SUM("vbslq_p8", sum);
}

static void t_vbslq_p16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x8_t, a0, 0, 0);
        ARG(poly16x8_t, a1, 1, 0);
        ARG(poly16x8_t, a2, 2, 0);
        KEEP(poly16x8_t, vbslq_p16(a0, a1, a2));
    }
    SUM("vbslq_p16", sum);
}

static void t_vbslq_p64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x2_t, a0, 0, 0);
        ARG(poly64x2_t, a1, 1, 0);
        ARG(poly64x2_t, a2, 2, 0);
        KEEP(poly64x2_t, vbslq_p64(a0, a1, a2));
    }
    SUM("vbslq_p64", sum);
}

int main(void)
{
    t_vbsl_s8();
    t_vbsl_s16();
    t_vbsl_s32();
    t_vbsl_s64();
    t_vbsl_u8();
    t_vbsl_u16();
    t_vbsl_u32();
    t_vbsl_u64();
    t_vbsl_f32();
    t_vbsl_f64();
    t_vbsl_p8();
    t_vbsl_p16();
    t_vbsl_p64();
    t_vbslq_s8();
    t_vbslq_s16();
    t_vbslq_s32();
    t_vbslq_s64();
    t_vbslq_u8();
    t_vbslq_u16();
    t_vbslq_u32();
    t_vbslq_u64();
    t_vbslq_f32();
    t_vbslq_f64();
    t_vbslq_p8();
    t_vbslq_p16();
    t_vbslq_p64();
    return 0;
}
