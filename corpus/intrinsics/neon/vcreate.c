/* The vcreate family of arm_neon.h.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vcreate_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64_t, a0, 0, 0);
        KEEP(int8x8_t, vcreate_s8(a0));
    }
    SUM("vcreate_s8", sum);
}

static void t_vcreate_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64_t, a0, 0, 0);
        KEEP(int16x4_t, vcreate_s16(a0));
    }
    SUM("vcreate_s16", sum);
}

static void t_vcreate_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64_t, a0, 0, 0);
        KEEP(int32x2_t, vcreate_s32(a0));
    }
    SUM("vcreate_s32", sum);
}

static void t_vcreate_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64_t, a0, 0, 0);
        KEEP(int64x1_t, vcreate_s64(a0));
    }
    SUM("vcreate_s64", sum);
}

static void t_vcreate_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64_t, a0, 0, 0);
        KEEP(uint8x8_t, vcreate_u8(a0));
    }
    SUM("vcreate_u8", sum);
}

static void t_vcreate_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64_t, a0, 0, 0);
        KEEP(uint16x4_t, vcreate_u16(a0));
    }
    SUM("vcreate_u16", sum);
}

static void t_vcreate_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64_t, a0, 0, 0);
        KEEP(uint32x2_t, vcreate_u32(a0));
    }
    SUM("vcreate_u32", sum);
}

static void t_vcreate_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64_t, a0, 0, 0);
        KEEP(uint64x1_t, vcreate_u64(a0));
    }
    SUM("vcreate_u64", sum);
}

static void t_vcreate_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64_t, a0, 0, 0);
        KEEP(float32x2_t, vcreate_f32(a0));
    }
    SUM("vcreate_f32", sum);
}

static void t_vcreate_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64_t, a0, 0, 0);
        KEEP(float64x1_t, vcreate_f64(a0));
    }
    SUM("vcreate_f64", sum);
}

static void t_vcreate_p8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64_t, a0, 0, 0);
        KEEP(poly8x8_t, vcreate_p8(a0));
    }
    SUM("vcreate_p8", sum);
}

static void t_vcreate_p16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64_t, a0, 0, 0);
        KEEP(poly16x4_t, vcreate_p16(a0));
    }
    SUM("vcreate_p16", sum);
}

static void t_vcreate_p64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64_t, a0, 0, 0);
        KEEP(poly64x1_t, vcreate_p64(a0));
    }
    SUM("vcreate_p64", sum);
}

int main(void)
{
    t_vcreate_s8();
    t_vcreate_s16();
    t_vcreate_s32();
    t_vcreate_s64();
    t_vcreate_u8();
    t_vcreate_u16();
    t_vcreate_u32();
    t_vcreate_u64();
    t_vcreate_f32();
    t_vcreate_f64();
    t_vcreate_p8();
    t_vcreate_p16();
    t_vcreate_p64();
    return 0;
}
