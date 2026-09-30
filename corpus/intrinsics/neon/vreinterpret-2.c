/* The vreinterpret family of arm_neon.h, part 2 of 5.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vreinterpret_u16_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x8_t, a0, 0, 0);
        KEEP(uint16x4_t, vreinterpret_u16_u8(a0));
    }
    SUM("vreinterpret_u16_u8", sum);
}

static void t_vreinterpret_u16_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x2_t, a0, 0, 0);
        KEEP(uint16x4_t, vreinterpret_u16_u32(a0));
    }
    SUM("vreinterpret_u16_u32", sum);
}

static void t_vreinterpret_u16_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x1_t, a0, 0, 0);
        KEEP(uint16x4_t, vreinterpret_u16_u64(a0));
    }
    SUM("vreinterpret_u16_u64", sum);
}

static void t_vreinterpret_u16_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x2_t, a0, 0, 32);
        KEEP(uint16x4_t, vreinterpret_u16_f32(a0));
    }
    SUM("vreinterpret_u16_f32", sum);
}

static void t_vreinterpret_u16_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x1_t, a0, 0, 64);
        KEEP(uint16x4_t, vreinterpret_u16_f64(a0));
    }
    SUM("vreinterpret_u16_f64", sum);
}

static void t_vreinterpret_u16_p8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly8x8_t, a0, 0, 0);
        KEEP(uint16x4_t, vreinterpret_u16_p8(a0));
    }
    SUM("vreinterpret_u16_p8", sum);
}

static void t_vreinterpret_u16_p16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly16x4_t, a0, 0, 0);
        KEEP(uint16x4_t, vreinterpret_u16_p16(a0));
    }
    SUM("vreinterpret_u16_p16", sum);
}

static void t_vreinterpret_u16_p64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly64x1_t, a0, 0, 0);
        KEEP(uint16x4_t, vreinterpret_u16_p64(a0));
    }
    SUM("vreinterpret_u16_p64", sum);
}

static void t_vreinterpret_u32_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x8_t, a0, 0, 0);
        KEEP(uint32x2_t, vreinterpret_u32_s8(a0));
    }
    SUM("vreinterpret_u32_s8", sum);
}

static void t_vreinterpret_u32_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x4_t, a0, 0, 0);
        KEEP(uint32x2_t, vreinterpret_u32_s16(a0));
    }
    SUM("vreinterpret_u32_s16", sum);
}

static void t_vreinterpret_u32_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x2_t, a0, 0, 0);
        KEEP(uint32x2_t, vreinterpret_u32_s32(a0));
    }
    SUM("vreinterpret_u32_s32", sum);
}

static void t_vreinterpret_u32_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x1_t, a0, 0, 0);
        KEEP(uint32x2_t, vreinterpret_u32_s64(a0));
    }
    SUM("vreinterpret_u32_s64", sum);
}

static void t_vreinterpret_u32_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x8_t, a0, 0, 0);
        KEEP(uint32x2_t, vreinterpret_u32_u8(a0));
    }
    SUM("vreinterpret_u32_u8", sum);
}

static void t_vreinterpret_u32_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x4_t, a0, 0, 0);
        KEEP(uint32x2_t, vreinterpret_u32_u16(a0));
    }
    SUM("vreinterpret_u32_u16", sum);
}

static void t_vreinterpret_u32_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x1_t, a0, 0, 0);
        KEEP(uint32x2_t, vreinterpret_u32_u64(a0));
    }
    SUM("vreinterpret_u32_u64", sum);
}

static void t_vreinterpret_u32_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x2_t, a0, 0, 32);
        KEEP(uint32x2_t, vreinterpret_u32_f32(a0));
    }
    SUM("vreinterpret_u32_f32", sum);
}

static void t_vreinterpret_u32_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x1_t, a0, 0, 64);
        KEEP(uint32x2_t, vreinterpret_u32_f64(a0));
    }
    SUM("vreinterpret_u32_f64", sum);
}

static void t_vreinterpret_u32_p8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly8x8_t, a0, 0, 0);
        KEEP(uint32x2_t, vreinterpret_u32_p8(a0));
    }
    SUM("vreinterpret_u32_p8", sum);
}

static void t_vreinterpret_u32_p16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly16x4_t, a0, 0, 0);
        KEEP(uint32x2_t, vreinterpret_u32_p16(a0));
    }
    SUM("vreinterpret_u32_p16", sum);
}

static void t_vreinterpret_u32_p64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly64x1_t, a0, 0, 0);
        KEEP(uint32x2_t, vreinterpret_u32_p64(a0));
    }
    SUM("vreinterpret_u32_p64", sum);
}

static void t_vreinterpret_u64_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x8_t, a0, 0, 0);
        KEEP(uint64x1_t, vreinterpret_u64_s8(a0));
    }
    SUM("vreinterpret_u64_s8", sum);
}

static void t_vreinterpret_u64_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x4_t, a0, 0, 0);
        KEEP(uint64x1_t, vreinterpret_u64_s16(a0));
    }
    SUM("vreinterpret_u64_s16", sum);
}

static void t_vreinterpret_u64_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x2_t, a0, 0, 0);
        KEEP(uint64x1_t, vreinterpret_u64_s32(a0));
    }
    SUM("vreinterpret_u64_s32", sum);
}

static void t_vreinterpret_u64_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x1_t, a0, 0, 0);
        KEEP(uint64x1_t, vreinterpret_u64_s64(a0));
    }
    SUM("vreinterpret_u64_s64", sum);
}

static void t_vreinterpret_u64_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x8_t, a0, 0, 0);
        KEEP(uint64x1_t, vreinterpret_u64_u8(a0));
    }
    SUM("vreinterpret_u64_u8", sum);
}

static void t_vreinterpret_u64_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x4_t, a0, 0, 0);
        KEEP(uint64x1_t, vreinterpret_u64_u16(a0));
    }
    SUM("vreinterpret_u64_u16", sum);
}

static void t_vreinterpret_u64_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x2_t, a0, 0, 0);
        KEEP(uint64x1_t, vreinterpret_u64_u32(a0));
    }
    SUM("vreinterpret_u64_u32", sum);
}

static void t_vreinterpret_u64_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x2_t, a0, 0, 32);
        KEEP(uint64x1_t, vreinterpret_u64_f32(a0));
    }
    SUM("vreinterpret_u64_f32", sum);
}

static void t_vreinterpret_u64_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x1_t, a0, 0, 64);
        KEEP(uint64x1_t, vreinterpret_u64_f64(a0));
    }
    SUM("vreinterpret_u64_f64", sum);
}

static void t_vreinterpret_u64_p8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly8x8_t, a0, 0, 0);
        KEEP(uint64x1_t, vreinterpret_u64_p8(a0));
    }
    SUM("vreinterpret_u64_p8", sum);
}

static void t_vreinterpret_u64_p16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly16x4_t, a0, 0, 0);
        KEEP(uint64x1_t, vreinterpret_u64_p16(a0));
    }
    SUM("vreinterpret_u64_p16", sum);
}

static void t_vreinterpret_u64_p64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly64x1_t, a0, 0, 0);
        KEEP(uint64x1_t, vreinterpret_u64_p64(a0));
    }
    SUM("vreinterpret_u64_p64", sum);
}

static void t_vreinterpret_f32_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x8_t, a0, 0, 0);
        KEEP(float32x2_t, vreinterpret_f32_s8(a0));
    }
    SUM("vreinterpret_f32_s8", sum);
}

static void t_vreinterpret_f32_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x4_t, a0, 0, 0);
        KEEP(float32x2_t, vreinterpret_f32_s16(a0));
    }
    SUM("vreinterpret_f32_s16", sum);
}

static void t_vreinterpret_f32_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x2_t, a0, 0, 0);
        KEEP(float32x2_t, vreinterpret_f32_s32(a0));
    }
    SUM("vreinterpret_f32_s32", sum);
}

static void t_vreinterpret_f32_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x1_t, a0, 0, 0);
        KEEP(float32x2_t, vreinterpret_f32_s64(a0));
    }
    SUM("vreinterpret_f32_s64", sum);
}

static void t_vreinterpret_f32_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x8_t, a0, 0, 0);
        KEEP(float32x2_t, vreinterpret_f32_u8(a0));
    }
    SUM("vreinterpret_f32_u8", sum);
}

static void t_vreinterpret_f32_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x4_t, a0, 0, 0);
        KEEP(float32x2_t, vreinterpret_f32_u16(a0));
    }
    SUM("vreinterpret_f32_u16", sum);
}

static void t_vreinterpret_f32_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x2_t, a0, 0, 0);
        KEEP(float32x2_t, vreinterpret_f32_u32(a0));
    }
    SUM("vreinterpret_f32_u32", sum);
}

static void t_vreinterpret_f32_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x1_t, a0, 0, 0);
        KEEP(float32x2_t, vreinterpret_f32_u64(a0));
    }
    SUM("vreinterpret_f32_u64", sum);
}

static void t_vreinterpret_f32_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x1_t, a0, 0, 64);
        KEEP(float32x2_t, vreinterpret_f32_f64(a0));
    }
    SUM("vreinterpret_f32_f64", sum);
}

static void t_vreinterpret_f32_p8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly8x8_t, a0, 0, 0);
        KEEP(float32x2_t, vreinterpret_f32_p8(a0));
    }
    SUM("vreinterpret_f32_p8", sum);
}

static void t_vreinterpret_f32_p16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly16x4_t, a0, 0, 0);
        KEEP(float32x2_t, vreinterpret_f32_p16(a0));
    }
    SUM("vreinterpret_f32_p16", sum);
}

static void t_vreinterpret_f32_p64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly64x1_t, a0, 0, 0);
        KEEP(float32x2_t, vreinterpret_f32_p64(a0));
    }
    SUM("vreinterpret_f32_p64", sum);
}

static void t_vreinterpret_f64_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x8_t, a0, 0, 0);
        KEEP(float64x1_t, vreinterpret_f64_s8(a0));
    }
    SUM("vreinterpret_f64_s8", sum);
}

static void t_vreinterpret_f64_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x4_t, a0, 0, 0);
        KEEP(float64x1_t, vreinterpret_f64_s16(a0));
    }
    SUM("vreinterpret_f64_s16", sum);
}

static void t_vreinterpret_f64_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x2_t, a0, 0, 0);
        KEEP(float64x1_t, vreinterpret_f64_s32(a0));
    }
    SUM("vreinterpret_f64_s32", sum);
}

static void t_vreinterpret_f64_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x1_t, a0, 0, 0);
        KEEP(float64x1_t, vreinterpret_f64_s64(a0));
    }
    SUM("vreinterpret_f64_s64", sum);
}

static void t_vreinterpret_f64_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x8_t, a0, 0, 0);
        KEEP(float64x1_t, vreinterpret_f64_u8(a0));
    }
    SUM("vreinterpret_f64_u8", sum);
}

static void t_vreinterpret_f64_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x4_t, a0, 0, 0);
        KEEP(float64x1_t, vreinterpret_f64_u16(a0));
    }
    SUM("vreinterpret_f64_u16", sum);
}

static void t_vreinterpret_f64_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x2_t, a0, 0, 0);
        KEEP(float64x1_t, vreinterpret_f64_u32(a0));
    }
    SUM("vreinterpret_f64_u32", sum);
}

static void t_vreinterpret_f64_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x1_t, a0, 0, 0);
        KEEP(float64x1_t, vreinterpret_f64_u64(a0));
    }
    SUM("vreinterpret_f64_u64", sum);
}

static void t_vreinterpret_f64_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x2_t, a0, 0, 32);
        KEEP(float64x1_t, vreinterpret_f64_f32(a0));
    }
    SUM("vreinterpret_f64_f32", sum);
}

static void t_vreinterpret_f64_p8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly8x8_t, a0, 0, 0);
        KEEP(float64x1_t, vreinterpret_f64_p8(a0));
    }
    SUM("vreinterpret_f64_p8", sum);
}

static void t_vreinterpret_f64_p16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly16x4_t, a0, 0, 0);
        KEEP(float64x1_t, vreinterpret_f64_p16(a0));
    }
    SUM("vreinterpret_f64_p16", sum);
}

static void t_vreinterpret_f64_p64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly64x1_t, a0, 0, 0);
        KEEP(float64x1_t, vreinterpret_f64_p64(a0));
    }
    SUM("vreinterpret_f64_p64", sum);
}

static void t_vreinterpret_p8_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x8_t, a0, 0, 0);
        KEEP(poly8x8_t, vreinterpret_p8_s8(a0));
    }
    SUM("vreinterpret_p8_s8", sum);
}

static void t_vreinterpret_p8_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x4_t, a0, 0, 0);
        KEEP(poly8x8_t, vreinterpret_p8_s16(a0));
    }
    SUM("vreinterpret_p8_s16", sum);
}

static void t_vreinterpret_p8_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x2_t, a0, 0, 0);
        KEEP(poly8x8_t, vreinterpret_p8_s32(a0));
    }
    SUM("vreinterpret_p8_s32", sum);
}

static void t_vreinterpret_p8_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x1_t, a0, 0, 0);
        KEEP(poly8x8_t, vreinterpret_p8_s64(a0));
    }
    SUM("vreinterpret_p8_s64", sum);
}

static void t_vreinterpret_p8_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x8_t, a0, 0, 0);
        KEEP(poly8x8_t, vreinterpret_p8_u8(a0));
    }
    SUM("vreinterpret_p8_u8", sum);
}

static void t_vreinterpret_p8_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x4_t, a0, 0, 0);
        KEEP(poly8x8_t, vreinterpret_p8_u16(a0));
    }
    SUM("vreinterpret_p8_u16", sum);
}

static void t_vreinterpret_p8_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x2_t, a0, 0, 0);
        KEEP(poly8x8_t, vreinterpret_p8_u32(a0));
    }
    SUM("vreinterpret_p8_u32", sum);
}

static void t_vreinterpret_p8_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x1_t, a0, 0, 0);
        KEEP(poly8x8_t, vreinterpret_p8_u64(a0));
    }
    SUM("vreinterpret_p8_u64", sum);
}

int main(void)
{
    t_vreinterpret_u16_u8();
    t_vreinterpret_u16_u32();
    t_vreinterpret_u16_u64();
    t_vreinterpret_u16_f32();
    t_vreinterpret_u16_f64();
    t_vreinterpret_u16_p8();
    t_vreinterpret_u16_p16();
    t_vreinterpret_u16_p64();
    t_vreinterpret_u32_s8();
    t_vreinterpret_u32_s16();
    t_vreinterpret_u32_s32();
    t_vreinterpret_u32_s64();
    t_vreinterpret_u32_u8();
    t_vreinterpret_u32_u16();
    t_vreinterpret_u32_u64();
    t_vreinterpret_u32_f32();
    t_vreinterpret_u32_f64();
    t_vreinterpret_u32_p8();
    t_vreinterpret_u32_p16();
    t_vreinterpret_u32_p64();
    t_vreinterpret_u64_s8();
    t_vreinterpret_u64_s16();
    t_vreinterpret_u64_s32();
    t_vreinterpret_u64_s64();
    t_vreinterpret_u64_u8();
    t_vreinterpret_u64_u16();
    t_vreinterpret_u64_u32();
    t_vreinterpret_u64_f32();
    t_vreinterpret_u64_f64();
    t_vreinterpret_u64_p8();
    t_vreinterpret_u64_p16();
    t_vreinterpret_u64_p64();
    t_vreinterpret_f32_s8();
    t_vreinterpret_f32_s16();
    t_vreinterpret_f32_s32();
    t_vreinterpret_f32_s64();
    t_vreinterpret_f32_u8();
    t_vreinterpret_f32_u16();
    t_vreinterpret_f32_u32();
    t_vreinterpret_f32_u64();
    t_vreinterpret_f32_f64();
    t_vreinterpret_f32_p8();
    t_vreinterpret_f32_p16();
    t_vreinterpret_f32_p64();
    t_vreinterpret_f64_s8();
    t_vreinterpret_f64_s16();
    t_vreinterpret_f64_s32();
    t_vreinterpret_f64_s64();
    t_vreinterpret_f64_u8();
    t_vreinterpret_f64_u16();
    t_vreinterpret_f64_u32();
    t_vreinterpret_f64_u64();
    t_vreinterpret_f64_f32();
    t_vreinterpret_f64_p8();
    t_vreinterpret_f64_p16();
    t_vreinterpret_f64_p64();
    t_vreinterpret_p8_s8();
    t_vreinterpret_p8_s16();
    t_vreinterpret_p8_s32();
    t_vreinterpret_p8_s64();
    t_vreinterpret_p8_u8();
    t_vreinterpret_p8_u16();
    t_vreinterpret_p8_u32();
    t_vreinterpret_p8_u64();
    return 0;
}
