/* The vaddv family of arm_neon.h.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vaddv_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x8_t, a0, 0, 0);
        KEEP(int8_t, vaddv_s8(a0));
    }
    SUM("vaddv_s8", sum);
}

static void t_vaddv_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x4_t, a0, 0, 0);
        KEEP(int16_t, vaddv_s16(a0));
    }
    SUM("vaddv_s16", sum);
}

static void t_vaddv_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x2_t, a0, 0, 0);
        KEEP(int32_t, vaddv_s32(a0));
    }
    SUM("vaddv_s32", sum);
}

static void t_vaddv_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x8_t, a0, 0, 0);
        KEEP(uint8_t, vaddv_u8(a0));
    }
    SUM("vaddv_u8", sum);
}

static void t_vaddv_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x4_t, a0, 0, 0);
        KEEP(uint16_t, vaddv_u16(a0));
    }
    SUM("vaddv_u16", sum);
}

static void t_vaddv_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x2_t, a0, 0, 0);
        KEEP(uint32_t, vaddv_u32(a0));
    }
    SUM("vaddv_u32", sum);
}

static void t_vaddv_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x2_t, a0, 0, 32);
        KEEP(float32_t, vaddv_f32(a0));
    }
    SUM("vaddv_f32", sum);
}

static void t_vaddvq_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x16_t, a0, 0, 0);
        KEEP(int8_t, vaddvq_s8(a0));
    }
    SUM("vaddvq_s8", sum);
}

static void t_vaddvq_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x8_t, a0, 0, 0);
        KEEP(int16_t, vaddvq_s16(a0));
    }
    SUM("vaddvq_s16", sum);
}

static void t_vaddvq_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x4_t, a0, 0, 0);
        KEEP(int32_t, vaddvq_s32(a0));
    }
    SUM("vaddvq_s32", sum);
}

static void t_vaddvq_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x2_t, a0, 0, 0);
        KEEP(int64_t, vaddvq_s64(a0));
    }
    SUM("vaddvq_s64", sum);
}

static void t_vaddvq_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x16_t, a0, 0, 0);
        KEEP(uint8_t, vaddvq_u8(a0));
    }
    SUM("vaddvq_u8", sum);
}

static void t_vaddvq_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x8_t, a0, 0, 0);
        KEEP(uint16_t, vaddvq_u16(a0));
    }
    SUM("vaddvq_u16", sum);
}

static void t_vaddvq_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x4_t, a0, 0, 0);
        KEEP(uint32_t, vaddvq_u32(a0));
    }
    SUM("vaddvq_u32", sum);
}

static void t_vaddvq_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x2_t, a0, 0, 0);
        KEEP(uint64_t, vaddvq_u64(a0));
    }
    SUM("vaddvq_u64", sum);
}

static void t_vaddvq_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x4_t, a0, 0, 32);
        KEEP(float32_t, vaddvq_f32(a0));
    }
    SUM("vaddvq_f32", sum);
}

static void t_vaddvq_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x2_t, a0, 0, 64);
        KEEP(float64_t, vaddvq_f64(a0));
    }
    SUM("vaddvq_f64", sum);
}

int main(void)
{
    t_vaddv_s8();
    t_vaddv_s16();
    t_vaddv_s32();
    t_vaddv_u8();
    t_vaddv_u16();
    t_vaddv_u32();
    t_vaddv_f32();
    t_vaddvq_s8();
    t_vaddvq_s16();
    t_vaddvq_s32();
    t_vaddvq_s64();
    t_vaddvq_u8();
    t_vaddvq_u16();
    t_vaddvq_u32();
    t_vaddvq_u64();
    t_vaddvq_f32();
    t_vaddvq_f64();
    return 0;
}
