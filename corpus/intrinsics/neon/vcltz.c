/* The vcltz family of arm_neon.h.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vcltz_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x8_t, a0, 0, 0);
        KEEP(uint8x8_t, vcltz_s8(a0));
    }
    SUM("vcltz_s8", sum);
}

static void t_vcltz_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x4_t, a0, 0, 0);
        KEEP(uint16x4_t, vcltz_s16(a0));
    }
    SUM("vcltz_s16", sum);
}

static void t_vcltz_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x2_t, a0, 0, 0);
        KEEP(uint32x2_t, vcltz_s32(a0));
    }
    SUM("vcltz_s32", sum);
}

static void t_vcltz_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x1_t, a0, 0, 0);
        KEEP(uint64x1_t, vcltz_s64(a0));
    }
    SUM("vcltz_s64", sum);
}

static void t_vcltz_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x2_t, a0, 0, 32);
        KEEP(uint32x2_t, vcltz_f32(a0));
    }
    SUM("vcltz_f32", sum);
}

static void t_vcltz_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x1_t, a0, 0, 64);
        KEEP(uint64x1_t, vcltz_f64(a0));
    }
    SUM("vcltz_f64", sum);
}

static void t_vcltzq_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x16_t, a0, 0, 0);
        KEEP(uint8x16_t, vcltzq_s8(a0));
    }
    SUM("vcltzq_s8", sum);
}

static void t_vcltzq_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x8_t, a0, 0, 0);
        KEEP(uint16x8_t, vcltzq_s16(a0));
    }
    SUM("vcltzq_s16", sum);
}

static void t_vcltzq_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x4_t, a0, 0, 0);
        KEEP(uint32x4_t, vcltzq_s32(a0));
    }
    SUM("vcltzq_s32", sum);
}

static void t_vcltzq_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x2_t, a0, 0, 0);
        KEEP(uint64x2_t, vcltzq_s64(a0));
    }
    SUM("vcltzq_s64", sum);
}

static void t_vcltzq_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x4_t, a0, 0, 32);
        KEEP(uint32x4_t, vcltzq_f32(a0));
    }
    SUM("vcltzq_f32", sum);
}

static void t_vcltzq_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x2_t, a0, 0, 64);
        KEEP(uint64x2_t, vcltzq_f64(a0));
    }
    SUM("vcltzq_f64", sum);
}

int main(void)
{
    t_vcltz_s8();
    t_vcltz_s16();
    t_vcltz_s32();
    t_vcltz_s64();
    t_vcltz_f32();
    t_vcltz_f64();
    t_vcltzq_s8();
    t_vcltzq_s16();
    t_vcltzq_s32();
    t_vcltzq_s64();
    t_vcltzq_f32();
    t_vcltzq_f64();
    return 0;
}
