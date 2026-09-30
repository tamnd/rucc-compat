/* The vst2 family of arm_neon.h.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vst2_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(int8_t, a0, 0, 0);
        ARG(int8x8x2_t, a1, 1, 0);
        STORE(vst2_s8(a0, a1), a0);
    }
    SUM("vst2_s8", sum);
}

static void t_vst2_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(int16_t, a0, 0, 0);
        ARG(int16x4x2_t, a1, 1, 0);
        STORE(vst2_s16(a0, a1), a0);
    }
    SUM("vst2_s16", sum);
}

static void t_vst2_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(int32_t, a0, 0, 0);
        ARG(int32x2x2_t, a1, 1, 0);
        STORE(vst2_s32(a0, a1), a0);
    }
    SUM("vst2_s32", sum);
}

static void t_vst2_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(int64_t, a0, 0, 0);
        ARG(int64x1x2_t, a1, 1, 0);
        STORE(vst2_s64(a0, a1), a0);
    }
    SUM("vst2_s64", sum);
}

static void t_vst2_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(uint8_t, a0, 0, 0);
        ARG(uint8x8x2_t, a1, 1, 0);
        STORE(vst2_u8(a0, a1), a0);
    }
    SUM("vst2_u8", sum);
}

static void t_vst2_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(uint16_t, a0, 0, 0);
        ARG(uint16x4x2_t, a1, 1, 0);
        STORE(vst2_u16(a0, a1), a0);
    }
    SUM("vst2_u16", sum);
}

static void t_vst2_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(uint32_t, a0, 0, 0);
        ARG(uint32x2x2_t, a1, 1, 0);
        STORE(vst2_u32(a0, a1), a0);
    }
    SUM("vst2_u32", sum);
}

static void t_vst2_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(uint64_t, a0, 0, 0);
        ARG(uint64x1x2_t, a1, 1, 0);
        STORE(vst2_u64(a0, a1), a0);
    }
    SUM("vst2_u64", sum);
}

static void t_vst2_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(float32_t, a0, 0, 32);
        ARG(float32x2x2_t, a1, 1, 32);
        STORE(vst2_f32(a0, a1), a0);
    }
    SUM("vst2_f32", sum);
}

static void t_vst2_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(float64_t, a0, 0, 64);
        ARG(float64x1x2_t, a1, 1, 64);
        STORE(vst2_f64(a0, a1), a0);
    }
    SUM("vst2_f64", sum);
}

static void t_vst2_p8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(poly8_t, a0, 0, 0);
        ARG(poly8x8x2_t, a1, 1, 0);
        STORE(vst2_p8(a0, a1), a0);
    }
    SUM("vst2_p8", sum);
}

static void t_vst2_p16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(poly16_t, a0, 0, 0);
        ARG(poly16x4x2_t, a1, 1, 0);
        STORE(vst2_p16(a0, a1), a0);
    }
    SUM("vst2_p16", sum);
}

static void t_vst2_p64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(poly64_t, a0, 0, 0);
        ARG(poly64x1x2_t, a1, 1, 0);
        STORE(vst2_p64(a0, a1), a0);
    }
    SUM("vst2_p64", sum);
}

static void t_vst2q_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(int8_t, a0, 0, 0);
        ARG(int8x16x2_t, a1, 1, 0);
        STORE(vst2q_s8(a0, a1), a0);
    }
    SUM("vst2q_s8", sum);
}

static void t_vst2q_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(int16_t, a0, 0, 0);
        ARG(int16x8x2_t, a1, 1, 0);
        STORE(vst2q_s16(a0, a1), a0);
    }
    SUM("vst2q_s16", sum);
}

static void t_vst2q_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(int32_t, a0, 0, 0);
        ARG(int32x4x2_t, a1, 1, 0);
        STORE(vst2q_s32(a0, a1), a0);
    }
    SUM("vst2q_s32", sum);
}

static void t_vst2q_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(int64_t, a0, 0, 0);
        ARG(int64x2x2_t, a1, 1, 0);
        STORE(vst2q_s64(a0, a1), a0);
    }
    SUM("vst2q_s64", sum);
}

static void t_vst2q_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(uint8_t, a0, 0, 0);
        ARG(uint8x16x2_t, a1, 1, 0);
        STORE(vst2q_u8(a0, a1), a0);
    }
    SUM("vst2q_u8", sum);
}

static void t_vst2q_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(uint16_t, a0, 0, 0);
        ARG(uint16x8x2_t, a1, 1, 0);
        STORE(vst2q_u16(a0, a1), a0);
    }
    SUM("vst2q_u16", sum);
}

static void t_vst2q_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(uint32_t, a0, 0, 0);
        ARG(uint32x4x2_t, a1, 1, 0);
        STORE(vst2q_u32(a0, a1), a0);
    }
    SUM("vst2q_u32", sum);
}

static void t_vst2q_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(uint64_t, a0, 0, 0);
        ARG(uint64x2x2_t, a1, 1, 0);
        STORE(vst2q_u64(a0, a1), a0);
    }
    SUM("vst2q_u64", sum);
}

static void t_vst2q_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(float32_t, a0, 0, 32);
        ARG(float32x4x2_t, a1, 1, 32);
        STORE(vst2q_f32(a0, a1), a0);
    }
    SUM("vst2q_f32", sum);
}

static void t_vst2q_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(float64_t, a0, 0, 64);
        ARG(float64x2x2_t, a1, 1, 64);
        STORE(vst2q_f64(a0, a1), a0);
    }
    SUM("vst2q_f64", sum);
}

static void t_vst2q_p8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(poly8_t, a0, 0, 0);
        ARG(poly8x16x2_t, a1, 1, 0);
        STORE(vst2q_p8(a0, a1), a0);
    }
    SUM("vst2q_p8", sum);
}

static void t_vst2q_p16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(poly16_t, a0, 0, 0);
        ARG(poly16x8x2_t, a1, 1, 0);
        STORE(vst2q_p16(a0, a1), a0);
    }
    SUM("vst2q_p16", sum);
}

static void t_vst2q_p64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        BUF(poly64_t, a0, 0, 0);
        ARG(poly64x2x2_t, a1, 1, 0);
        STORE(vst2q_p64(a0, a1), a0);
    }
    SUM("vst2q_p64", sum);
}

int main(void)
{
    t_vst2_s8();
    t_vst2_s16();
    t_vst2_s32();
    t_vst2_s64();
    t_vst2_u8();
    t_vst2_u16();
    t_vst2_u32();
    t_vst2_u64();
    t_vst2_f32();
    t_vst2_f64();
    t_vst2_p8();
    t_vst2_p16();
    t_vst2_p64();
    t_vst2q_s8();
    t_vst2q_s16();
    t_vst2q_s32();
    t_vst2q_s64();
    t_vst2q_u8();
    t_vst2q_u16();
    t_vst2q_u32();
    t_vst2q_u64();
    t_vst2q_f32();
    t_vst2q_f64();
    t_vst2q_p8();
    t_vst2q_p16();
    t_vst2q_p64();
    return 0;
}
