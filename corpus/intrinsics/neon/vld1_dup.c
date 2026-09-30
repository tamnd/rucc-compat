/* The vld1_dup family of arm_neon.h.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vld1_dup_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(int8_t, a0, 0, 0);
        KEEP(int8x8_t, vld1_dup_s8(a0));
    }
    SUM("vld1_dup_s8", sum);
}

static void t_vld1_dup_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(int16_t, a0, 0, 0);
        KEEP(int16x4_t, vld1_dup_s16(a0));
    }
    SUM("vld1_dup_s16", sum);
}

static void t_vld1_dup_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(int32_t, a0, 0, 0);
        KEEP(int32x2_t, vld1_dup_s32(a0));
    }
    SUM("vld1_dup_s32", sum);
}

static void t_vld1_dup_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(int64_t, a0, 0, 0);
        KEEP(int64x1_t, vld1_dup_s64(a0));
    }
    SUM("vld1_dup_s64", sum);
}

static void t_vld1_dup_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(uint8_t, a0, 0, 0);
        KEEP(uint8x8_t, vld1_dup_u8(a0));
    }
    SUM("vld1_dup_u8", sum);
}

static void t_vld1_dup_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(uint16_t, a0, 0, 0);
        KEEP(uint16x4_t, vld1_dup_u16(a0));
    }
    SUM("vld1_dup_u16", sum);
}

static void t_vld1_dup_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(uint32_t, a0, 0, 0);
        KEEP(uint32x2_t, vld1_dup_u32(a0));
    }
    SUM("vld1_dup_u32", sum);
}

static void t_vld1_dup_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(uint64_t, a0, 0, 0);
        KEEP(uint64x1_t, vld1_dup_u64(a0));
    }
    SUM("vld1_dup_u64", sum);
}

static void t_vld1_dup_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(float32_t, a0, 0, 32);
        KEEP(float32x2_t, vld1_dup_f32(a0));
    }
    SUM("vld1_dup_f32", sum);
}

static void t_vld1_dup_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(float64_t, a0, 0, 64);
        KEEP(float64x1_t, vld1_dup_f64(a0));
    }
    SUM("vld1_dup_f64", sum);
}

static void t_vld1_dup_p8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(poly8_t, a0, 0, 0);
        KEEP(poly8x8_t, vld1_dup_p8(a0));
    }
    SUM("vld1_dup_p8", sum);
}

static void t_vld1_dup_p16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(poly16_t, a0, 0, 0);
        KEEP(poly16x4_t, vld1_dup_p16(a0));
    }
    SUM("vld1_dup_p16", sum);
}

static void t_vld1_dup_p64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(poly64_t, a0, 0, 0);
        KEEP(poly64x1_t, vld1_dup_p64(a0));
    }
    SUM("vld1_dup_p64", sum);
}

static void t_vld1q_dup_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(int8_t, a0, 0, 0);
        KEEP(int8x16_t, vld1q_dup_s8(a0));
    }
    SUM("vld1q_dup_s8", sum);
}

static void t_vld1q_dup_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(int16_t, a0, 0, 0);
        KEEP(int16x8_t, vld1q_dup_s16(a0));
    }
    SUM("vld1q_dup_s16", sum);
}

static void t_vld1q_dup_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(int32_t, a0, 0, 0);
        KEEP(int32x4_t, vld1q_dup_s32(a0));
    }
    SUM("vld1q_dup_s32", sum);
}

static void t_vld1q_dup_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(int64_t, a0, 0, 0);
        KEEP(int64x2_t, vld1q_dup_s64(a0));
    }
    SUM("vld1q_dup_s64", sum);
}

static void t_vld1q_dup_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(uint8_t, a0, 0, 0);
        KEEP(uint8x16_t, vld1q_dup_u8(a0));
    }
    SUM("vld1q_dup_u8", sum);
}

static void t_vld1q_dup_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(uint16_t, a0, 0, 0);
        KEEP(uint16x8_t, vld1q_dup_u16(a0));
    }
    SUM("vld1q_dup_u16", sum);
}

static void t_vld1q_dup_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(uint32_t, a0, 0, 0);
        KEEP(uint32x4_t, vld1q_dup_u32(a0));
    }
    SUM("vld1q_dup_u32", sum);
}

static void t_vld1q_dup_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(uint64_t, a0, 0, 0);
        KEEP(uint64x2_t, vld1q_dup_u64(a0));
    }
    SUM("vld1q_dup_u64", sum);
}

static void t_vld1q_dup_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(float32_t, a0, 0, 32);
        KEEP(float32x4_t, vld1q_dup_f32(a0));
    }
    SUM("vld1q_dup_f32", sum);
}

static void t_vld1q_dup_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(float64_t, a0, 0, 64);
        KEEP(float64x2_t, vld1q_dup_f64(a0));
    }
    SUM("vld1q_dup_f64", sum);
}

static void t_vld1q_dup_p8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(poly8_t, a0, 0, 0);
        KEEP(poly8x16_t, vld1q_dup_p8(a0));
    }
    SUM("vld1q_dup_p8", sum);
}

static void t_vld1q_dup_p16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(poly16_t, a0, 0, 0);
        KEEP(poly16x8_t, vld1q_dup_p16(a0));
    }
    SUM("vld1q_dup_p16", sum);
}

static void t_vld1q_dup_p64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(poly64_t, a0, 0, 0);
        KEEP(poly64x2_t, vld1q_dup_p64(a0));
    }
    SUM("vld1q_dup_p64", sum);
}

int main(void)
{
    t_vld1_dup_s8();
    t_vld1_dup_s16();
    t_vld1_dup_s32();
    t_vld1_dup_s64();
    t_vld1_dup_u8();
    t_vld1_dup_u16();
    t_vld1_dup_u32();
    t_vld1_dup_u64();
    t_vld1_dup_f32();
    t_vld1_dup_f64();
    t_vld1_dup_p8();
    t_vld1_dup_p16();
    t_vld1_dup_p64();
    t_vld1q_dup_s8();
    t_vld1q_dup_s16();
    t_vld1q_dup_s32();
    t_vld1q_dup_s64();
    t_vld1q_dup_u8();
    t_vld1q_dup_u16();
    t_vld1q_dup_u32();
    t_vld1q_dup_u64();
    t_vld1q_dup_f32();
    t_vld1q_dup_f64();
    t_vld1q_dup_p8();
    t_vld1q_dup_p16();
    t_vld1q_dup_p64();
    return 0;
}
