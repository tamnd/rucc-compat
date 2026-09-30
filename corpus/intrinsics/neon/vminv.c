/* The vminv family of arm_neon.h.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vminv_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x8_t, a0, 0, 0);
        KEEP(int8_t, vminv_s8(a0));
    }
    SUM("vminv_s8", sum);
}

static void t_vminv_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x4_t, a0, 0, 0);
        KEEP(int16_t, vminv_s16(a0));
    }
    SUM("vminv_s16", sum);
}

static void t_vminv_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x2_t, a0, 0, 0);
        KEEP(int32_t, vminv_s32(a0));
    }
    SUM("vminv_s32", sum);
}

static void t_vminv_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x8_t, a0, 0, 0);
        KEEP(uint8_t, vminv_u8(a0));
    }
    SUM("vminv_u8", sum);
}

static void t_vminv_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x4_t, a0, 0, 0);
        KEEP(uint16_t, vminv_u16(a0));
    }
    SUM("vminv_u16", sum);
}

static void t_vminv_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x2_t, a0, 0, 0);
        KEEP(uint32_t, vminv_u32(a0));
    }
    SUM("vminv_u32", sum);
}

static void t_vminv_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x2_t, a0, 0, 32);
        KEEP(float32_t, vminv_f32(a0));
    }
    SUM("vminv_f32", sum);
}

static void t_vminvq_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x16_t, a0, 0, 0);
        KEEP(int8_t, vminvq_s8(a0));
    }
    SUM("vminvq_s8", sum);
}

static void t_vminvq_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x8_t, a0, 0, 0);
        KEEP(int16_t, vminvq_s16(a0));
    }
    SUM("vminvq_s16", sum);
}

static void t_vminvq_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x4_t, a0, 0, 0);
        KEEP(int32_t, vminvq_s32(a0));
    }
    SUM("vminvq_s32", sum);
}

static void t_vminvq_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x16_t, a0, 0, 0);
        KEEP(uint8_t, vminvq_u8(a0));
    }
    SUM("vminvq_u8", sum);
}

static void t_vminvq_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x8_t, a0, 0, 0);
        KEEP(uint16_t, vminvq_u16(a0));
    }
    SUM("vminvq_u16", sum);
}

static void t_vminvq_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x4_t, a0, 0, 0);
        KEEP(uint32_t, vminvq_u32(a0));
    }
    SUM("vminvq_u32", sum);
}

static void t_vminvq_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x4_t, a0, 0, 32);
        KEEP(float32_t, vminvq_f32(a0));
    }
    SUM("vminvq_f32", sum);
}

static void t_vminvq_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x2_t, a0, 0, 64);
        KEEP(float64_t, vminvq_f64(a0));
    }
    SUM("vminvq_f64", sum);
}

int main(void)
{
    t_vminv_s8();
    t_vminv_s16();
    t_vminv_s32();
    t_vminv_u8();
    t_vminv_u16();
    t_vminv_u32();
    t_vminv_f32();
    t_vminvq_s8();
    t_vminvq_s16();
    t_vminvq_s32();
    t_vminvq_u8();
    t_vminvq_u16();
    t_vminvq_u32();
    t_vminvq_f32();
    t_vminvq_f64();
    return 0;
}
