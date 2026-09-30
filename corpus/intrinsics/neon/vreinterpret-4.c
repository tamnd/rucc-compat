/* The vreinterpret family of arm_neon.h, part 4 of 5.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vreinterpretq_s64_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x16_t, a0, 0, 0);
        KEEP(int64x2_t, vreinterpretq_s64_s8(a0));
    }
    SUM("vreinterpretq_s64_s8", sum);
}

static void t_vreinterpretq_s64_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x8_t, a0, 0, 0);
        KEEP(int64x2_t, vreinterpretq_s64_s16(a0));
    }
    SUM("vreinterpretq_s64_s16", sum);
}

static void t_vreinterpretq_s64_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x4_t, a0, 0, 0);
        KEEP(int64x2_t, vreinterpretq_s64_s32(a0));
    }
    SUM("vreinterpretq_s64_s32", sum);
}

static void t_vreinterpretq_s64_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x16_t, a0, 0, 0);
        KEEP(int64x2_t, vreinterpretq_s64_u8(a0));
    }
    SUM("vreinterpretq_s64_u8", sum);
}

static void t_vreinterpretq_s64_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x8_t, a0, 0, 0);
        KEEP(int64x2_t, vreinterpretq_s64_u16(a0));
    }
    SUM("vreinterpretq_s64_u16", sum);
}

static void t_vreinterpretq_s64_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x4_t, a0, 0, 0);
        KEEP(int64x2_t, vreinterpretq_s64_u32(a0));
    }
    SUM("vreinterpretq_s64_u32", sum);
}

static void t_vreinterpretq_s64_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x2_t, a0, 0, 0);
        KEEP(int64x2_t, vreinterpretq_s64_u64(a0));
    }
    SUM("vreinterpretq_s64_u64", sum);
}

static void t_vreinterpretq_s64_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x4_t, a0, 0, 32);
        KEEP(int64x2_t, vreinterpretq_s64_f32(a0));
    }
    SUM("vreinterpretq_s64_f32", sum);
}

static void t_vreinterpretq_s64_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x2_t, a0, 0, 64);
        KEEP(int64x2_t, vreinterpretq_s64_f64(a0));
    }
    SUM("vreinterpretq_s64_f64", sum);
}

static void t_vreinterpretq_s64_p8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly8x16_t, a0, 0, 0);
        KEEP(int64x2_t, vreinterpretq_s64_p8(a0));
    }
    SUM("vreinterpretq_s64_p8", sum);
}

static void t_vreinterpretq_s64_p16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly16x8_t, a0, 0, 0);
        KEEP(int64x2_t, vreinterpretq_s64_p16(a0));
    }
    SUM("vreinterpretq_s64_p16", sum);
}

static void t_vreinterpretq_s64_p64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly64x2_t, a0, 0, 0);
        KEEP(int64x2_t, vreinterpretq_s64_p64(a0));
    }
    SUM("vreinterpretq_s64_p64", sum);
}

static void t_vreinterpretq_u8_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x16_t, a0, 0, 0);
        KEEP(uint8x16_t, vreinterpretq_u8_s8(a0));
    }
    SUM("vreinterpretq_u8_s8", sum);
}

static void t_vreinterpretq_u8_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x8_t, a0, 0, 0);
        KEEP(uint8x16_t, vreinterpretq_u8_s16(a0));
    }
    SUM("vreinterpretq_u8_s16", sum);
}

static void t_vreinterpretq_u8_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x4_t, a0, 0, 0);
        KEEP(uint8x16_t, vreinterpretq_u8_s32(a0));
    }
    SUM("vreinterpretq_u8_s32", sum);
}

static void t_vreinterpretq_u8_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x2_t, a0, 0, 0);
        KEEP(uint8x16_t, vreinterpretq_u8_s64(a0));
    }
    SUM("vreinterpretq_u8_s64", sum);
}

static void t_vreinterpretq_u8_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x8_t, a0, 0, 0);
        KEEP(uint8x16_t, vreinterpretq_u8_u16(a0));
    }
    SUM("vreinterpretq_u8_u16", sum);
}

static void t_vreinterpretq_u8_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x4_t, a0, 0, 0);
        KEEP(uint8x16_t, vreinterpretq_u8_u32(a0));
    }
    SUM("vreinterpretq_u8_u32", sum);
}

static void t_vreinterpretq_u8_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x2_t, a0, 0, 0);
        KEEP(uint8x16_t, vreinterpretq_u8_u64(a0));
    }
    SUM("vreinterpretq_u8_u64", sum);
}

static void t_vreinterpretq_u8_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x4_t, a0, 0, 32);
        KEEP(uint8x16_t, vreinterpretq_u8_f32(a0));
    }
    SUM("vreinterpretq_u8_f32", sum);
}

static void t_vreinterpretq_u8_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x2_t, a0, 0, 64);
        KEEP(uint8x16_t, vreinterpretq_u8_f64(a0));
    }
    SUM("vreinterpretq_u8_f64", sum);
}

static void t_vreinterpretq_u8_p8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly8x16_t, a0, 0, 0);
        KEEP(uint8x16_t, vreinterpretq_u8_p8(a0));
    }
    SUM("vreinterpretq_u8_p8", sum);
}

static void t_vreinterpretq_u8_p16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly16x8_t, a0, 0, 0);
        KEEP(uint8x16_t, vreinterpretq_u8_p16(a0));
    }
    SUM("vreinterpretq_u8_p16", sum);
}

static void t_vreinterpretq_u8_p64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly64x2_t, a0, 0, 0);
        KEEP(uint8x16_t, vreinterpretq_u8_p64(a0));
    }
    SUM("vreinterpretq_u8_p64", sum);
}

static void t_vreinterpretq_u16_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x16_t, a0, 0, 0);
        KEEP(uint16x8_t, vreinterpretq_u16_s8(a0));
    }
    SUM("vreinterpretq_u16_s8", sum);
}

static void t_vreinterpretq_u16_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x8_t, a0, 0, 0);
        KEEP(uint16x8_t, vreinterpretq_u16_s16(a0));
    }
    SUM("vreinterpretq_u16_s16", sum);
}

static void t_vreinterpretq_u16_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x4_t, a0, 0, 0);
        KEEP(uint16x8_t, vreinterpretq_u16_s32(a0));
    }
    SUM("vreinterpretq_u16_s32", sum);
}

static void t_vreinterpretq_u16_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x2_t, a0, 0, 0);
        KEEP(uint16x8_t, vreinterpretq_u16_s64(a0));
    }
    SUM("vreinterpretq_u16_s64", sum);
}

static void t_vreinterpretq_u16_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x16_t, a0, 0, 0);
        KEEP(uint16x8_t, vreinterpretq_u16_u8(a0));
    }
    SUM("vreinterpretq_u16_u8", sum);
}

static void t_vreinterpretq_u16_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x4_t, a0, 0, 0);
        KEEP(uint16x8_t, vreinterpretq_u16_u32(a0));
    }
    SUM("vreinterpretq_u16_u32", sum);
}

static void t_vreinterpretq_u16_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x2_t, a0, 0, 0);
        KEEP(uint16x8_t, vreinterpretq_u16_u64(a0));
    }
    SUM("vreinterpretq_u16_u64", sum);
}

static void t_vreinterpretq_u16_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x4_t, a0, 0, 32);
        KEEP(uint16x8_t, vreinterpretq_u16_f32(a0));
    }
    SUM("vreinterpretq_u16_f32", sum);
}

static void t_vreinterpretq_u16_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x2_t, a0, 0, 64);
        KEEP(uint16x8_t, vreinterpretq_u16_f64(a0));
    }
    SUM("vreinterpretq_u16_f64", sum);
}

static void t_vreinterpretq_u16_p8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly8x16_t, a0, 0, 0);
        KEEP(uint16x8_t, vreinterpretq_u16_p8(a0));
    }
    SUM("vreinterpretq_u16_p8", sum);
}

static void t_vreinterpretq_u16_p16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly16x8_t, a0, 0, 0);
        KEEP(uint16x8_t, vreinterpretq_u16_p16(a0));
    }
    SUM("vreinterpretq_u16_p16", sum);
}

static void t_vreinterpretq_u16_p64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly64x2_t, a0, 0, 0);
        KEEP(uint16x8_t, vreinterpretq_u16_p64(a0));
    }
    SUM("vreinterpretq_u16_p64", sum);
}

static void t_vreinterpretq_u32_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x16_t, a0, 0, 0);
        KEEP(uint32x4_t, vreinterpretq_u32_s8(a0));
    }
    SUM("vreinterpretq_u32_s8", sum);
}

static void t_vreinterpretq_u32_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x8_t, a0, 0, 0);
        KEEP(uint32x4_t, vreinterpretq_u32_s16(a0));
    }
    SUM("vreinterpretq_u32_s16", sum);
}

static void t_vreinterpretq_u32_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x4_t, a0, 0, 0);
        KEEP(uint32x4_t, vreinterpretq_u32_s32(a0));
    }
    SUM("vreinterpretq_u32_s32", sum);
}

static void t_vreinterpretq_u32_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x2_t, a0, 0, 0);
        KEEP(uint32x4_t, vreinterpretq_u32_s64(a0));
    }
    SUM("vreinterpretq_u32_s64", sum);
}

static void t_vreinterpretq_u32_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x16_t, a0, 0, 0);
        KEEP(uint32x4_t, vreinterpretq_u32_u8(a0));
    }
    SUM("vreinterpretq_u32_u8", sum);
}

static void t_vreinterpretq_u32_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x8_t, a0, 0, 0);
        KEEP(uint32x4_t, vreinterpretq_u32_u16(a0));
    }
    SUM("vreinterpretq_u32_u16", sum);
}

static void t_vreinterpretq_u32_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x2_t, a0, 0, 0);
        KEEP(uint32x4_t, vreinterpretq_u32_u64(a0));
    }
    SUM("vreinterpretq_u32_u64", sum);
}

static void t_vreinterpretq_u32_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x4_t, a0, 0, 32);
        KEEP(uint32x4_t, vreinterpretq_u32_f32(a0));
    }
    SUM("vreinterpretq_u32_f32", sum);
}

static void t_vreinterpretq_u32_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x2_t, a0, 0, 64);
        KEEP(uint32x4_t, vreinterpretq_u32_f64(a0));
    }
    SUM("vreinterpretq_u32_f64", sum);
}

static void t_vreinterpretq_u32_p8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly8x16_t, a0, 0, 0);
        KEEP(uint32x4_t, vreinterpretq_u32_p8(a0));
    }
    SUM("vreinterpretq_u32_p8", sum);
}

static void t_vreinterpretq_u32_p16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly16x8_t, a0, 0, 0);
        KEEP(uint32x4_t, vreinterpretq_u32_p16(a0));
    }
    SUM("vreinterpretq_u32_p16", sum);
}

static void t_vreinterpretq_u32_p64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly64x2_t, a0, 0, 0);
        KEEP(uint32x4_t, vreinterpretq_u32_p64(a0));
    }
    SUM("vreinterpretq_u32_p64", sum);
}

static void t_vreinterpretq_u64_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x16_t, a0, 0, 0);
        KEEP(uint64x2_t, vreinterpretq_u64_s8(a0));
    }
    SUM("vreinterpretq_u64_s8", sum);
}

static void t_vreinterpretq_u64_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x8_t, a0, 0, 0);
        KEEP(uint64x2_t, vreinterpretq_u64_s16(a0));
    }
    SUM("vreinterpretq_u64_s16", sum);
}

static void t_vreinterpretq_u64_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x4_t, a0, 0, 0);
        KEEP(uint64x2_t, vreinterpretq_u64_s32(a0));
    }
    SUM("vreinterpretq_u64_s32", sum);
}

static void t_vreinterpretq_u64_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x2_t, a0, 0, 0);
        KEEP(uint64x2_t, vreinterpretq_u64_s64(a0));
    }
    SUM("vreinterpretq_u64_s64", sum);
}

static void t_vreinterpretq_u64_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x16_t, a0, 0, 0);
        KEEP(uint64x2_t, vreinterpretq_u64_u8(a0));
    }
    SUM("vreinterpretq_u64_u8", sum);
}

static void t_vreinterpretq_u64_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x8_t, a0, 0, 0);
        KEEP(uint64x2_t, vreinterpretq_u64_u16(a0));
    }
    SUM("vreinterpretq_u64_u16", sum);
}

static void t_vreinterpretq_u64_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x4_t, a0, 0, 0);
        KEEP(uint64x2_t, vreinterpretq_u64_u32(a0));
    }
    SUM("vreinterpretq_u64_u32", sum);
}

static void t_vreinterpretq_u64_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x4_t, a0, 0, 32);
        KEEP(uint64x2_t, vreinterpretq_u64_f32(a0));
    }
    SUM("vreinterpretq_u64_f32", sum);
}

static void t_vreinterpretq_u64_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x2_t, a0, 0, 64);
        KEEP(uint64x2_t, vreinterpretq_u64_f64(a0));
    }
    SUM("vreinterpretq_u64_f64", sum);
}

static void t_vreinterpretq_u64_p8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly8x16_t, a0, 0, 0);
        KEEP(uint64x2_t, vreinterpretq_u64_p8(a0));
    }
    SUM("vreinterpretq_u64_p8", sum);
}

static void t_vreinterpretq_u64_p16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly16x8_t, a0, 0, 0);
        KEEP(uint64x2_t, vreinterpretq_u64_p16(a0));
    }
    SUM("vreinterpretq_u64_p16", sum);
}

static void t_vreinterpretq_u64_p64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly64x2_t, a0, 0, 0);
        KEEP(uint64x2_t, vreinterpretq_u64_p64(a0));
    }
    SUM("vreinterpretq_u64_p64", sum);
}

static void t_vreinterpretq_f32_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x16_t, a0, 0, 0);
        KEEP(float32x4_t, vreinterpretq_f32_s8(a0));
    }
    SUM("vreinterpretq_f32_s8", sum);
}

static void t_vreinterpretq_f32_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x8_t, a0, 0, 0);
        KEEP(float32x4_t, vreinterpretq_f32_s16(a0));
    }
    SUM("vreinterpretq_f32_s16", sum);
}

static void t_vreinterpretq_f32_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x4_t, a0, 0, 0);
        KEEP(float32x4_t, vreinterpretq_f32_s32(a0));
    }
    SUM("vreinterpretq_f32_s32", sum);
}

static void t_vreinterpretq_f32_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x2_t, a0, 0, 0);
        KEEP(float32x4_t, vreinterpretq_f32_s64(a0));
    }
    SUM("vreinterpretq_f32_s64", sum);
}

int main(void)
{
    t_vreinterpretq_s64_s8();
    t_vreinterpretq_s64_s16();
    t_vreinterpretq_s64_s32();
    t_vreinterpretq_s64_u8();
    t_vreinterpretq_s64_u16();
    t_vreinterpretq_s64_u32();
    t_vreinterpretq_s64_u64();
    t_vreinterpretq_s64_f32();
    t_vreinterpretq_s64_f64();
    t_vreinterpretq_s64_p8();
    t_vreinterpretq_s64_p16();
    t_vreinterpretq_s64_p64();
    t_vreinterpretq_u8_s8();
    t_vreinterpretq_u8_s16();
    t_vreinterpretq_u8_s32();
    t_vreinterpretq_u8_s64();
    t_vreinterpretq_u8_u16();
    t_vreinterpretq_u8_u32();
    t_vreinterpretq_u8_u64();
    t_vreinterpretq_u8_f32();
    t_vreinterpretq_u8_f64();
    t_vreinterpretq_u8_p8();
    t_vreinterpretq_u8_p16();
    t_vreinterpretq_u8_p64();
    t_vreinterpretq_u16_s8();
    t_vreinterpretq_u16_s16();
    t_vreinterpretq_u16_s32();
    t_vreinterpretq_u16_s64();
    t_vreinterpretq_u16_u8();
    t_vreinterpretq_u16_u32();
    t_vreinterpretq_u16_u64();
    t_vreinterpretq_u16_f32();
    t_vreinterpretq_u16_f64();
    t_vreinterpretq_u16_p8();
    t_vreinterpretq_u16_p16();
    t_vreinterpretq_u16_p64();
    t_vreinterpretq_u32_s8();
    t_vreinterpretq_u32_s16();
    t_vreinterpretq_u32_s32();
    t_vreinterpretq_u32_s64();
    t_vreinterpretq_u32_u8();
    t_vreinterpretq_u32_u16();
    t_vreinterpretq_u32_u64();
    t_vreinterpretq_u32_f32();
    t_vreinterpretq_u32_f64();
    t_vreinterpretq_u32_p8();
    t_vreinterpretq_u32_p16();
    t_vreinterpretq_u32_p64();
    t_vreinterpretq_u64_s8();
    t_vreinterpretq_u64_s16();
    t_vreinterpretq_u64_s32();
    t_vreinterpretq_u64_s64();
    t_vreinterpretq_u64_u8();
    t_vreinterpretq_u64_u16();
    t_vreinterpretq_u64_u32();
    t_vreinterpretq_u64_f32();
    t_vreinterpretq_u64_f64();
    t_vreinterpretq_u64_p8();
    t_vreinterpretq_u64_p16();
    t_vreinterpretq_u64_p64();
    t_vreinterpretq_f32_s8();
    t_vreinterpretq_f32_s16();
    t_vreinterpretq_f32_s32();
    t_vreinterpretq_f32_s64();
    return 0;
}
