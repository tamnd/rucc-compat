/* The vneg family of arm_neon.h.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vneg_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x8_t, a0, 0, 0);
        KEEP(int8x8_t, vneg_s8(a0));
    }
    SUM("vneg_s8", sum);
}

static void t_vneg_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x4_t, a0, 0, 0);
        KEEP(int16x4_t, vneg_s16(a0));
    }
    SUM("vneg_s16", sum);
}

static void t_vneg_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x2_t, a0, 0, 0);
        KEEP(int32x2_t, vneg_s32(a0));
    }
    SUM("vneg_s32", sum);
}

static void t_vneg_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x1_t, a0, 0, 0);
        KEEP(int64x1_t, vneg_s64(a0));
    }
    SUM("vneg_s64", sum);
}

static void t_vneg_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x2_t, a0, 0, 32);
        KEEP(float32x2_t, vneg_f32(a0));
    }
    SUM("vneg_f32", sum);
}

static void t_vneg_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x1_t, a0, 0, 64);
        KEEP(float64x1_t, vneg_f64(a0));
    }
    SUM("vneg_f64", sum);
}

static void t_vnegq_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x16_t, a0, 0, 0);
        KEEP(int8x16_t, vnegq_s8(a0));
    }
    SUM("vnegq_s8", sum);
}

static void t_vnegq_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x8_t, a0, 0, 0);
        KEEP(int16x8_t, vnegq_s16(a0));
    }
    SUM("vnegq_s16", sum);
}

static void t_vnegq_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x4_t, a0, 0, 0);
        KEEP(int32x4_t, vnegq_s32(a0));
    }
    SUM("vnegq_s32", sum);
}

static void t_vnegq_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x2_t, a0, 0, 0);
        KEEP(int64x2_t, vnegq_s64(a0));
    }
    SUM("vnegq_s64", sum);
}

static void t_vnegq_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x4_t, a0, 0, 32);
        KEEP(float32x4_t, vnegq_f32(a0));
    }
    SUM("vnegq_f32", sum);
}

static void t_vnegq_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x2_t, a0, 0, 64);
        KEEP(float64x2_t, vnegq_f64(a0));
    }
    SUM("vnegq_f64", sum);
}

int main(void)
{
    t_vneg_s8();
    t_vneg_s16();
    t_vneg_s32();
    t_vneg_s64();
    t_vneg_f32();
    t_vneg_f64();
    t_vnegq_s8();
    t_vnegq_s16();
    t_vnegq_s32();
    t_vnegq_s64();
    t_vnegq_f32();
    t_vnegq_f64();
    return 0;
}
