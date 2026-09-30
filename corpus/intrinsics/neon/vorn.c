/* The vorn family of arm_neon.h.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vorn_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x8_t, a0, 0, 0);
        ARG(int8x8_t, a1, 1, 0);
        KEEP(int8x8_t, vorn_s8(a0, a1));
    }
    SUM("vorn_s8", sum);
}

static void t_vorn_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x4_t, a0, 0, 0);
        ARG(int16x4_t, a1, 1, 0);
        KEEP(int16x4_t, vorn_s16(a0, a1));
    }
    SUM("vorn_s16", sum);
}

static void t_vorn_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x2_t, a0, 0, 0);
        ARG(int32x2_t, a1, 1, 0);
        KEEP(int32x2_t, vorn_s32(a0, a1));
    }
    SUM("vorn_s32", sum);
}

static void t_vorn_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x1_t, a0, 0, 0);
        ARG(int64x1_t, a1, 1, 0);
        KEEP(int64x1_t, vorn_s64(a0, a1));
    }
    SUM("vorn_s64", sum);
}

static void t_vorn_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x8_t, a0, 0, 0);
        ARG(uint8x8_t, a1, 1, 0);
        KEEP(uint8x8_t, vorn_u8(a0, a1));
    }
    SUM("vorn_u8", sum);
}

static void t_vorn_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x4_t, a0, 0, 0);
        ARG(uint16x4_t, a1, 1, 0);
        KEEP(uint16x4_t, vorn_u16(a0, a1));
    }
    SUM("vorn_u16", sum);
}

static void t_vorn_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x2_t, a0, 0, 0);
        ARG(uint32x2_t, a1, 1, 0);
        KEEP(uint32x2_t, vorn_u32(a0, a1));
    }
    SUM("vorn_u32", sum);
}

static void t_vorn_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x1_t, a0, 0, 0);
        ARG(uint64x1_t, a1, 1, 0);
        KEEP(uint64x1_t, vorn_u64(a0, a1));
    }
    SUM("vorn_u64", sum);
}

static void t_vornq_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x16_t, a0, 0, 0);
        ARG(int8x16_t, a1, 1, 0);
        KEEP(int8x16_t, vornq_s8(a0, a1));
    }
    SUM("vornq_s8", sum);
}

static void t_vornq_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x8_t, a0, 0, 0);
        ARG(int16x8_t, a1, 1, 0);
        KEEP(int16x8_t, vornq_s16(a0, a1));
    }
    SUM("vornq_s16", sum);
}

static void t_vornq_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x4_t, a0, 0, 0);
        ARG(int32x4_t, a1, 1, 0);
        KEEP(int32x4_t, vornq_s32(a0, a1));
    }
    SUM("vornq_s32", sum);
}

static void t_vornq_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x2_t, a0, 0, 0);
        ARG(int64x2_t, a1, 1, 0);
        KEEP(int64x2_t, vornq_s64(a0, a1));
    }
    SUM("vornq_s64", sum);
}

static void t_vornq_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x16_t, a0, 0, 0);
        ARG(uint8x16_t, a1, 1, 0);
        KEEP(uint8x16_t, vornq_u8(a0, a1));
    }
    SUM("vornq_u8", sum);
}

static void t_vornq_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x8_t, a0, 0, 0);
        ARG(uint16x8_t, a1, 1, 0);
        KEEP(uint16x8_t, vornq_u16(a0, a1));
    }
    SUM("vornq_u16", sum);
}

static void t_vornq_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x4_t, a0, 0, 0);
        ARG(uint32x4_t, a1, 1, 0);
        KEEP(uint32x4_t, vornq_u32(a0, a1));
    }
    SUM("vornq_u32", sum);
}

static void t_vornq_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x2_t, a0, 0, 0);
        ARG(uint64x2_t, a1, 1, 0);
        KEEP(uint64x2_t, vornq_u64(a0, a1));
    }
    SUM("vornq_u64", sum);
}

int main(void)
{
    t_vorn_s8();
    t_vorn_s16();
    t_vorn_s32();
    t_vorn_s64();
    t_vorn_u8();
    t_vorn_u16();
    t_vorn_u32();
    t_vorn_u64();
    t_vornq_s8();
    t_vornq_s16();
    t_vornq_s32();
    t_vornq_s64();
    t_vornq_u8();
    t_vornq_u16();
    t_vornq_u32();
    t_vornq_u64();
    return 0;
}
