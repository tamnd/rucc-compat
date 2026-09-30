/* The vshll_n family of arm_neon.h.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vshll_n_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x8_t, a0, 0, 0);
        KEEP(int16x8_t, vshll_n_s8(a0, 0));
        KEEP(int16x8_t, vshll_n_s8(a0, 4));
        KEEP(int16x8_t, vshll_n_s8(a0, 8));
    }
    SUM("vshll_n_s8", sum);
}

static void t_vshll_n_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x4_t, a0, 0, 0);
        KEEP(int32x4_t, vshll_n_s16(a0, 0));
        KEEP(int32x4_t, vshll_n_s16(a0, 8));
        KEEP(int32x4_t, vshll_n_s16(a0, 16));
    }
    SUM("vshll_n_s16", sum);
}

static void t_vshll_n_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x2_t, a0, 0, 0);
        KEEP(int64x2_t, vshll_n_s32(a0, 0));
        KEEP(int64x2_t, vshll_n_s32(a0, 16));
        KEEP(int64x2_t, vshll_n_s32(a0, 32));
    }
    SUM("vshll_n_s32", sum);
}

static void t_vshll_n_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x8_t, a0, 0, 0);
        KEEP(uint16x8_t, vshll_n_u8(a0, 0));
        KEEP(uint16x8_t, vshll_n_u8(a0, 4));
        KEEP(uint16x8_t, vshll_n_u8(a0, 8));
    }
    SUM("vshll_n_u8", sum);
}

static void t_vshll_n_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x4_t, a0, 0, 0);
        KEEP(uint32x4_t, vshll_n_u16(a0, 0));
        KEEP(uint32x4_t, vshll_n_u16(a0, 8));
        KEEP(uint32x4_t, vshll_n_u16(a0, 16));
    }
    SUM("vshll_n_u16", sum);
}

static void t_vshll_n_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x2_t, a0, 0, 0);
        KEEP(uint64x2_t, vshll_n_u32(a0, 0));
        KEEP(uint64x2_t, vshll_n_u32(a0, 16));
        KEEP(uint64x2_t, vshll_n_u32(a0, 32));
    }
    SUM("vshll_n_u32", sum);
}

int main(void)
{
    t_vshll_n_s8();
    t_vshll_n_s16();
    t_vshll_n_s32();
    t_vshll_n_u8();
    t_vshll_n_u16();
    t_vshll_n_u32();
    return 0;
}
