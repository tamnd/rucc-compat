/* The vclez family of arm_neon.h.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vclez_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x8_t, a0, 0, 0);
        KEEP(uint8x8_t, vclez_s8(a0));
    }
    SUM("vclez_s8", sum);
}

static void t_vclez_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x4_t, a0, 0, 0);
        KEEP(uint16x4_t, vclez_s16(a0));
    }
    SUM("vclez_s16", sum);
}

static void t_vclez_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x2_t, a0, 0, 0);
        KEEP(uint32x2_t, vclez_s32(a0));
    }
    SUM("vclez_s32", sum);
}

static void t_vclez_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x1_t, a0, 0, 0);
        KEEP(uint64x1_t, vclez_s64(a0));
    }
    SUM("vclez_s64", sum);
}

static void t_vclez_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x2_t, a0, 0, 32);
        KEEP(uint32x2_t, vclez_f32(a0));
    }
    SUM("vclez_f32", sum);
}

static void t_vclez_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x1_t, a0, 0, 64);
        KEEP(uint64x1_t, vclez_f64(a0));
    }
    SUM("vclez_f64", sum);
}

static void t_vclezq_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x16_t, a0, 0, 0);
        KEEP(uint8x16_t, vclezq_s8(a0));
    }
    SUM("vclezq_s8", sum);
}

static void t_vclezq_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x8_t, a0, 0, 0);
        KEEP(uint16x8_t, vclezq_s16(a0));
    }
    SUM("vclezq_s16", sum);
}

static void t_vclezq_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x4_t, a0, 0, 0);
        KEEP(uint32x4_t, vclezq_s32(a0));
    }
    SUM("vclezq_s32", sum);
}

static void t_vclezq_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x2_t, a0, 0, 0);
        KEEP(uint64x2_t, vclezq_s64(a0));
    }
    SUM("vclezq_s64", sum);
}

static void t_vclezq_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x4_t, a0, 0, 32);
        KEEP(uint32x4_t, vclezq_f32(a0));
    }
    SUM("vclezq_f32", sum);
}

static void t_vclezq_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x2_t, a0, 0, 64);
        KEEP(uint64x2_t, vclezq_f64(a0));
    }
    SUM("vclezq_f64", sum);
}

int main(void)
{
    t_vclez_s8();
    t_vclez_s16();
    t_vclez_s32();
    t_vclez_s64();
    t_vclez_f32();
    t_vclez_f64();
    t_vclezq_s8();
    t_vclezq_s16();
    t_vclezq_s32();
    t_vclezq_s64();
    t_vclezq_f32();
    t_vclezq_f64();
    return 0;
}
