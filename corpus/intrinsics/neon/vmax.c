/* The vmax family of arm_neon.h.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vmax_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x8_t, a0, 0, 0);
        ARG(int8x8_t, a1, 1, 0);
        KEEP(int8x8_t, vmax_s8(a0, a1));
    }
    SUM("vmax_s8", sum);
}

static void t_vmax_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x4_t, a0, 0, 0);
        ARG(int16x4_t, a1, 1, 0);
        KEEP(int16x4_t, vmax_s16(a0, a1));
    }
    SUM("vmax_s16", sum);
}

static void t_vmax_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x2_t, a0, 0, 0);
        ARG(int32x2_t, a1, 1, 0);
        KEEP(int32x2_t, vmax_s32(a0, a1));
    }
    SUM("vmax_s32", sum);
}

static void t_vmax_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x8_t, a0, 0, 0);
        ARG(uint8x8_t, a1, 1, 0);
        KEEP(uint8x8_t, vmax_u8(a0, a1));
    }
    SUM("vmax_u8", sum);
}

static void t_vmax_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x4_t, a0, 0, 0);
        ARG(uint16x4_t, a1, 1, 0);
        KEEP(uint16x4_t, vmax_u16(a0, a1));
    }
    SUM("vmax_u16", sum);
}

static void t_vmax_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x2_t, a0, 0, 0);
        ARG(uint32x2_t, a1, 1, 0);
        KEEP(uint32x2_t, vmax_u32(a0, a1));
    }
    SUM("vmax_u32", sum);
}

static void t_vmax_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x2_t, a0, 0, 32);
        ARG(float32x2_t, a1, 1, 32);
        KEEP(float32x2_t, vmax_f32(a0, a1));
    }
    SUM("vmax_f32", sum);
}

static void t_vmax_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x1_t, a0, 0, 64);
        ARG(float64x1_t, a1, 1, 64);
        KEEP(float64x1_t, vmax_f64(a0, a1));
    }
    SUM("vmax_f64", sum);
}

static void t_vmaxq_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x16_t, a0, 0, 0);
        ARG(int8x16_t, a1, 1, 0);
        KEEP(int8x16_t, vmaxq_s8(a0, a1));
    }
    SUM("vmaxq_s8", sum);
}

static void t_vmaxq_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x8_t, a0, 0, 0);
        ARG(int16x8_t, a1, 1, 0);
        KEEP(int16x8_t, vmaxq_s16(a0, a1));
    }
    SUM("vmaxq_s16", sum);
}

static void t_vmaxq_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x4_t, a0, 0, 0);
        ARG(int32x4_t, a1, 1, 0);
        KEEP(int32x4_t, vmaxq_s32(a0, a1));
    }
    SUM("vmaxq_s32", sum);
}

static void t_vmaxq_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x16_t, a0, 0, 0);
        ARG(uint8x16_t, a1, 1, 0);
        KEEP(uint8x16_t, vmaxq_u8(a0, a1));
    }
    SUM("vmaxq_u8", sum);
}

static void t_vmaxq_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x8_t, a0, 0, 0);
        ARG(uint16x8_t, a1, 1, 0);
        KEEP(uint16x8_t, vmaxq_u16(a0, a1));
    }
    SUM("vmaxq_u16", sum);
}

static void t_vmaxq_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x4_t, a0, 0, 0);
        ARG(uint32x4_t, a1, 1, 0);
        KEEP(uint32x4_t, vmaxq_u32(a0, a1));
    }
    SUM("vmaxq_u32", sum);
}

static void t_vmaxq_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x4_t, a0, 0, 32);
        ARG(float32x4_t, a1, 1, 32);
        KEEP(float32x4_t, vmaxq_f32(a0, a1));
    }
    SUM("vmaxq_f32", sum);
}

static void t_vmaxq_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x2_t, a0, 0, 64);
        ARG(float64x2_t, a1, 1, 64);
        KEEP(float64x2_t, vmaxq_f64(a0, a1));
    }
    SUM("vmaxq_f64", sum);
}

int main(void)
{
    t_vmax_s8();
    t_vmax_s16();
    t_vmax_s32();
    t_vmax_u8();
    t_vmax_u16();
    t_vmax_u32();
    t_vmax_f32();
    t_vmax_f64();
    t_vmaxq_s8();
    t_vmaxq_s16();
    t_vmaxq_s32();
    t_vmaxq_u8();
    t_vmaxq_u16();
    t_vmaxq_u32();
    t_vmaxq_f32();
    t_vmaxq_f64();
    return 0;
}
