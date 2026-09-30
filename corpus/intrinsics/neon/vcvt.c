/* The vcvt family of arm_neon.h.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vcvt_f32_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x2_t, a0, 0, 0);
        KEEP(float32x2_t, vcvt_f32_s32(a0));
    }
    SUM("vcvt_f32_s32", sum);
}

static void t_vcvt_s32_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x2_t, a0, 0, 32);
        KEEP(int32x2_t, vcvt_s32_f32(a0));
    }
    SUM("vcvt_s32_f32", sum);
}

static void t_vcvt_f32_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x2_t, a0, 0, 0);
        KEEP(float32x2_t, vcvt_f32_u32(a0));
    }
    SUM("vcvt_f32_u32", sum);
}

static void t_vcvt_u32_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x2_t, a0, 0, 32);
        KEEP(uint32x2_t, vcvt_u32_f32(a0));
    }
    SUM("vcvt_u32_f32", sum);
}

static void t_vcvt_f64_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x1_t, a0, 0, 0);
        KEEP(float64x1_t, vcvt_f64_s64(a0));
    }
    SUM("vcvt_f64_s64", sum);
}

static void t_vcvt_s64_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x1_t, a0, 0, 64);
        KEEP(int64x1_t, vcvt_s64_f64(a0));
    }
    SUM("vcvt_s64_f64", sum);
}

static void t_vcvt_f64_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x1_t, a0, 0, 0);
        KEEP(float64x1_t, vcvt_f64_u64(a0));
    }
    SUM("vcvt_f64_u64", sum);
}

static void t_vcvt_u64_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x1_t, a0, 0, 64);
        KEEP(uint64x1_t, vcvt_u64_f64(a0));
    }
    SUM("vcvt_u64_f64", sum);
}

static void t_vcvtq_f32_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x4_t, a0, 0, 0);
        KEEP(float32x4_t, vcvtq_f32_s32(a0));
    }
    SUM("vcvtq_f32_s32", sum);
}

static void t_vcvtq_s32_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x4_t, a0, 0, 32);
        KEEP(int32x4_t, vcvtq_s32_f32(a0));
    }
    SUM("vcvtq_s32_f32", sum);
}

static void t_vcvtq_f32_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x4_t, a0, 0, 0);
        KEEP(float32x4_t, vcvtq_f32_u32(a0));
    }
    SUM("vcvtq_f32_u32", sum);
}

static void t_vcvtq_u32_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x4_t, a0, 0, 32);
        KEEP(uint32x4_t, vcvtq_u32_f32(a0));
    }
    SUM("vcvtq_u32_f32", sum);
}

static void t_vcvtq_f64_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x2_t, a0, 0, 0);
        KEEP(float64x2_t, vcvtq_f64_s64(a0));
    }
    SUM("vcvtq_f64_s64", sum);
}

static void t_vcvtq_s64_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x2_t, a0, 0, 64);
        KEEP(int64x2_t, vcvtq_s64_f64(a0));
    }
    SUM("vcvtq_s64_f64", sum);
}

static void t_vcvtq_f64_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x2_t, a0, 0, 0);
        KEEP(float64x2_t, vcvtq_f64_u64(a0));
    }
    SUM("vcvtq_f64_u64", sum);
}

static void t_vcvtq_u64_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x2_t, a0, 0, 64);
        KEEP(uint64x2_t, vcvtq_u64_f64(a0));
    }
    SUM("vcvtq_u64_f64", sum);
}

static void t_vcvt_f64_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x2_t, a0, 0, 32);
        KEEP(float64x2_t, vcvt_f64_f32(a0));
    }
    SUM("vcvt_f64_f32", sum);
}

static void t_vcvt_f32_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x2_t, a0, 0, 64);
        KEEP(float32x2_t, vcvt_f32_f64(a0));
    }
    SUM("vcvt_f32_f64", sum);
}

int main(void)
{
    t_vcvt_f32_s32();
    t_vcvt_s32_f32();
    t_vcvt_f32_u32();
    t_vcvt_u32_f32();
    t_vcvt_f64_s64();
    t_vcvt_s64_f64();
    t_vcvt_f64_u64();
    t_vcvt_u64_f64();
    t_vcvtq_f32_s32();
    t_vcvtq_s32_f32();
    t_vcvtq_f32_u32();
    t_vcvtq_u32_f32();
    t_vcvtq_f64_s64();
    t_vcvtq_s64_f64();
    t_vcvtq_f64_u64();
    t_vcvtq_u64_f64();
    t_vcvt_f64_f32();
    t_vcvt_f32_f64();
    return 0;
}
