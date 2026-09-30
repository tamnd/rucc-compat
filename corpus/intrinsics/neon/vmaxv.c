/* The vmaxv family of arm_neon.h.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vmaxv_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x8_t, a0, 0, 0);
        KEEP(int8_t, vmaxv_s8(a0));
    }
    SUM("vmaxv_s8", sum);
}

static void t_vmaxv_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x4_t, a0, 0, 0);
        KEEP(int16_t, vmaxv_s16(a0));
    }
    SUM("vmaxv_s16", sum);
}

static void t_vmaxv_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x2_t, a0, 0, 0);
        KEEP(int32_t, vmaxv_s32(a0));
    }
    SUM("vmaxv_s32", sum);
}

static void t_vmaxv_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x8_t, a0, 0, 0);
        KEEP(uint8_t, vmaxv_u8(a0));
    }
    SUM("vmaxv_u8", sum);
}

static void t_vmaxv_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x4_t, a0, 0, 0);
        KEEP(uint16_t, vmaxv_u16(a0));
    }
    SUM("vmaxv_u16", sum);
}

static void t_vmaxv_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x2_t, a0, 0, 0);
        KEEP(uint32_t, vmaxv_u32(a0));
    }
    SUM("vmaxv_u32", sum);
}

static void t_vmaxv_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x2_t, a0, 0, 32);
        KEEP(float32_t, vmaxv_f32(a0));
    }
    SUM("vmaxv_f32", sum);
}

static void t_vmaxvq_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x16_t, a0, 0, 0);
        KEEP(int8_t, vmaxvq_s8(a0));
    }
    SUM("vmaxvq_s8", sum);
}

static void t_vmaxvq_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x8_t, a0, 0, 0);
        KEEP(int16_t, vmaxvq_s16(a0));
    }
    SUM("vmaxvq_s16", sum);
}

static void t_vmaxvq_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x4_t, a0, 0, 0);
        KEEP(int32_t, vmaxvq_s32(a0));
    }
    SUM("vmaxvq_s32", sum);
}

static void t_vmaxvq_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x16_t, a0, 0, 0);
        KEEP(uint8_t, vmaxvq_u8(a0));
    }
    SUM("vmaxvq_u8", sum);
}

static void t_vmaxvq_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x8_t, a0, 0, 0);
        KEEP(uint16_t, vmaxvq_u16(a0));
    }
    SUM("vmaxvq_u16", sum);
}

static void t_vmaxvq_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x4_t, a0, 0, 0);
        KEEP(uint32_t, vmaxvq_u32(a0));
    }
    SUM("vmaxvq_u32", sum);
}

static void t_vmaxvq_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x4_t, a0, 0, 32);
        KEEP(float32_t, vmaxvq_f32(a0));
    }
    SUM("vmaxvq_f32", sum);
}

static void t_vmaxvq_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x2_t, a0, 0, 64);
        KEEP(float64_t, vmaxvq_f64(a0));
    }
    SUM("vmaxvq_f64", sum);
}

int main(void)
{
    t_vmaxv_s8();
    t_vmaxv_s16();
    t_vmaxv_s32();
    t_vmaxv_u8();
    t_vmaxv_u16();
    t_vmaxv_u32();
    t_vmaxv_f32();
    t_vmaxvq_s8();
    t_vmaxvq_s16();
    t_vmaxvq_s32();
    t_vmaxvq_u8();
    t_vmaxvq_u16();
    t_vmaxvq_u32();
    t_vmaxvq_f32();
    t_vmaxvq_f64();
    return 0;
}
