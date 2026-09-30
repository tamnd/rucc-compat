/* The vceqz family of arm_neon.h.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vceqz_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x8_t, a0, 0, 0);
        KEEP(uint8x8_t, vceqz_s8(a0));
    }
    SUM("vceqz_s8", sum);
}

static void t_vceqz_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x4_t, a0, 0, 0);
        KEEP(uint16x4_t, vceqz_s16(a0));
    }
    SUM("vceqz_s16", sum);
}

static void t_vceqz_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x2_t, a0, 0, 0);
        KEEP(uint32x2_t, vceqz_s32(a0));
    }
    SUM("vceqz_s32", sum);
}

static void t_vceqz_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x1_t, a0, 0, 0);
        KEEP(uint64x1_t, vceqz_s64(a0));
    }
    SUM("vceqz_s64", sum);
}

static void t_vceqz_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x8_t, a0, 0, 0);
        KEEP(uint8x8_t, vceqz_u8(a0));
    }
    SUM("vceqz_u8", sum);
}

static void t_vceqz_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x4_t, a0, 0, 0);
        KEEP(uint16x4_t, vceqz_u16(a0));
    }
    SUM("vceqz_u16", sum);
}

static void t_vceqz_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x2_t, a0, 0, 0);
        KEEP(uint32x2_t, vceqz_u32(a0));
    }
    SUM("vceqz_u32", sum);
}

static void t_vceqz_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x1_t, a0, 0, 0);
        KEEP(uint64x1_t, vceqz_u64(a0));
    }
    SUM("vceqz_u64", sum);
}

static void t_vceqz_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x2_t, a0, 0, 32);
        KEEP(uint32x2_t, vceqz_f32(a0));
    }
    SUM("vceqz_f32", sum);
}

static void t_vceqz_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x1_t, a0, 0, 64);
        KEEP(uint64x1_t, vceqz_f64(a0));
    }
    SUM("vceqz_f64", sum);
}

static void t_vceqzq_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x16_t, a0, 0, 0);
        KEEP(uint8x16_t, vceqzq_s8(a0));
    }
    SUM("vceqzq_s8", sum);
}

static void t_vceqzq_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x8_t, a0, 0, 0);
        KEEP(uint16x8_t, vceqzq_s16(a0));
    }
    SUM("vceqzq_s16", sum);
}

static void t_vceqzq_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x4_t, a0, 0, 0);
        KEEP(uint32x4_t, vceqzq_s32(a0));
    }
    SUM("vceqzq_s32", sum);
}

static void t_vceqzq_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x2_t, a0, 0, 0);
        KEEP(uint64x2_t, vceqzq_s64(a0));
    }
    SUM("vceqzq_s64", sum);
}

static void t_vceqzq_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x16_t, a0, 0, 0);
        KEEP(uint8x16_t, vceqzq_u8(a0));
    }
    SUM("vceqzq_u8", sum);
}

static void t_vceqzq_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x8_t, a0, 0, 0);
        KEEP(uint16x8_t, vceqzq_u16(a0));
    }
    SUM("vceqzq_u16", sum);
}

static void t_vceqzq_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x4_t, a0, 0, 0);
        KEEP(uint32x4_t, vceqzq_u32(a0));
    }
    SUM("vceqzq_u32", sum);
}

static void t_vceqzq_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x2_t, a0, 0, 0);
        KEEP(uint64x2_t, vceqzq_u64(a0));
    }
    SUM("vceqzq_u64", sum);
}

static void t_vceqzq_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x4_t, a0, 0, 32);
        KEEP(uint32x4_t, vceqzq_f32(a0));
    }
    SUM("vceqzq_f32", sum);
}

static void t_vceqzq_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x2_t, a0, 0, 64);
        KEEP(uint64x2_t, vceqzq_f64(a0));
    }
    SUM("vceqzq_f64", sum);
}

int main(void)
{
    t_vceqz_s8();
    t_vceqz_s16();
    t_vceqz_s32();
    t_vceqz_s64();
    t_vceqz_u8();
    t_vceqz_u16();
    t_vceqz_u32();
    t_vceqz_u64();
    t_vceqz_f32();
    t_vceqz_f64();
    t_vceqzq_s8();
    t_vceqzq_s16();
    t_vceqzq_s32();
    t_vceqzq_s64();
    t_vceqzq_u8();
    t_vceqzq_u16();
    t_vceqzq_u32();
    t_vceqzq_u64();
    t_vceqzq_f32();
    t_vceqzq_f64();
    return 0;
}
