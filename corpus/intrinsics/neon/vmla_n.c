/* The vmla_n family of arm_neon.h.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vmla_n_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x4_t, a0, 0, 0);
        ARG(int16x4_t, a1, 1, 0);
        ARG(int16_t, a2, 2, 0);
        KEEP(int16x4_t, vmla_n_s16(a0, a1, a2));
    }
    SUM("vmla_n_s16", sum);
}

static void t_vmla_n_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x2_t, a0, 0, 0);
        ARG(int32x2_t, a1, 1, 0);
        ARG(int32_t, a2, 2, 0);
        KEEP(int32x2_t, vmla_n_s32(a0, a1, a2));
    }
    SUM("vmla_n_s32", sum);
}

static void t_vmla_n_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x4_t, a0, 0, 0);
        ARG(uint16x4_t, a1, 1, 0);
        ARG(uint16_t, a2, 2, 0);
        KEEP(uint16x4_t, vmla_n_u16(a0, a1, a2));
    }
    SUM("vmla_n_u16", sum);
}

static void t_vmla_n_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x2_t, a0, 0, 0);
        ARG(uint32x2_t, a1, 1, 0);
        ARG(uint32_t, a2, 2, 0);
        KEEP(uint32x2_t, vmla_n_u32(a0, a1, a2));
    }
    SUM("vmla_n_u32", sum);
}

static void t_vmla_n_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x2_t, a0, 0, 32);
        ARG(float32x2_t, a1, 1, 32);
        ARG(float32_t, a2, 2, 32);
        KEEP(float32x2_t, vmla_n_f32(a0, a1, a2));
    }
    SUM("vmla_n_f32", sum);
}

static void t_vmlaq_n_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x8_t, a0, 0, 0);
        ARG(int16x8_t, a1, 1, 0);
        ARG(int16_t, a2, 2, 0);
        KEEP(int16x8_t, vmlaq_n_s16(a0, a1, a2));
    }
    SUM("vmlaq_n_s16", sum);
}

static void t_vmlaq_n_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x4_t, a0, 0, 0);
        ARG(int32x4_t, a1, 1, 0);
        ARG(int32_t, a2, 2, 0);
        KEEP(int32x4_t, vmlaq_n_s32(a0, a1, a2));
    }
    SUM("vmlaq_n_s32", sum);
}

static void t_vmlaq_n_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x8_t, a0, 0, 0);
        ARG(uint16x8_t, a1, 1, 0);
        ARG(uint16_t, a2, 2, 0);
        KEEP(uint16x8_t, vmlaq_n_u16(a0, a1, a2));
    }
    SUM("vmlaq_n_u16", sum);
}

static void t_vmlaq_n_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x4_t, a0, 0, 0);
        ARG(uint32x4_t, a1, 1, 0);
        ARG(uint32_t, a2, 2, 0);
        KEEP(uint32x4_t, vmlaq_n_u32(a0, a1, a2));
    }
    SUM("vmlaq_n_u32", sum);
}

static void t_vmlaq_n_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x4_t, a0, 0, 32);
        ARG(float32x4_t, a1, 1, 32);
        ARG(float32_t, a2, 2, 32);
        KEEP(float32x4_t, vmlaq_n_f32(a0, a1, a2));
    }
    SUM("vmlaq_n_f32", sum);
}

int main(void)
{
    t_vmla_n_s16();
    t_vmla_n_s32();
    t_vmla_n_u16();
    t_vmla_n_u32();
    t_vmla_n_f32();
    t_vmlaq_n_s16();
    t_vmlaq_n_s32();
    t_vmlaq_n_u16();
    t_vmlaq_n_u32();
    t_vmlaq_n_f32();
    return 0;
}
