/* The vqsub family of arm_neon.h.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vqsub_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x8_t, a0, 0, 0);
        ARG(int8x8_t, a1, 1, 0);
        KEEP(int8x8_t, vqsub_s8(a0, a1));
    }
    SUM("vqsub_s8", sum);
}

static void t_vqsub_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x4_t, a0, 0, 0);
        ARG(int16x4_t, a1, 1, 0);
        KEEP(int16x4_t, vqsub_s16(a0, a1));
    }
    SUM("vqsub_s16", sum);
}

static void t_vqsub_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x2_t, a0, 0, 0);
        ARG(int32x2_t, a1, 1, 0);
        KEEP(int32x2_t, vqsub_s32(a0, a1));
    }
    SUM("vqsub_s32", sum);
}

static void t_vqsub_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x1_t, a0, 0, 0);
        ARG(int64x1_t, a1, 1, 0);
        KEEP(int64x1_t, vqsub_s64(a0, a1));
    }
    SUM("vqsub_s64", sum);
}

static void t_vqsub_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x8_t, a0, 0, 0);
        ARG(uint8x8_t, a1, 1, 0);
        KEEP(uint8x8_t, vqsub_u8(a0, a1));
    }
    SUM("vqsub_u8", sum);
}

static void t_vqsub_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x4_t, a0, 0, 0);
        ARG(uint16x4_t, a1, 1, 0);
        KEEP(uint16x4_t, vqsub_u16(a0, a1));
    }
    SUM("vqsub_u16", sum);
}

static void t_vqsub_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x2_t, a0, 0, 0);
        ARG(uint32x2_t, a1, 1, 0);
        KEEP(uint32x2_t, vqsub_u32(a0, a1));
    }
    SUM("vqsub_u32", sum);
}

static void t_vqsub_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x1_t, a0, 0, 0);
        ARG(uint64x1_t, a1, 1, 0);
        KEEP(uint64x1_t, vqsub_u64(a0, a1));
    }
    SUM("vqsub_u64", sum);
}

static void t_vqsubq_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x16_t, a0, 0, 0);
        ARG(int8x16_t, a1, 1, 0);
        KEEP(int8x16_t, vqsubq_s8(a0, a1));
    }
    SUM("vqsubq_s8", sum);
}

static void t_vqsubq_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x8_t, a0, 0, 0);
        ARG(int16x8_t, a1, 1, 0);
        KEEP(int16x8_t, vqsubq_s16(a0, a1));
    }
    SUM("vqsubq_s16", sum);
}

static void t_vqsubq_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x4_t, a0, 0, 0);
        ARG(int32x4_t, a1, 1, 0);
        KEEP(int32x4_t, vqsubq_s32(a0, a1));
    }
    SUM("vqsubq_s32", sum);
}

static void t_vqsubq_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x2_t, a0, 0, 0);
        ARG(int64x2_t, a1, 1, 0);
        KEEP(int64x2_t, vqsubq_s64(a0, a1));
    }
    SUM("vqsubq_s64", sum);
}

static void t_vqsubq_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x16_t, a0, 0, 0);
        ARG(uint8x16_t, a1, 1, 0);
        KEEP(uint8x16_t, vqsubq_u8(a0, a1));
    }
    SUM("vqsubq_u8", sum);
}

static void t_vqsubq_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x8_t, a0, 0, 0);
        ARG(uint16x8_t, a1, 1, 0);
        KEEP(uint16x8_t, vqsubq_u16(a0, a1));
    }
    SUM("vqsubq_u16", sum);
}

static void t_vqsubq_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x4_t, a0, 0, 0);
        ARG(uint32x4_t, a1, 1, 0);
        KEEP(uint32x4_t, vqsubq_u32(a0, a1));
    }
    SUM("vqsubq_u32", sum);
}

static void t_vqsubq_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x2_t, a0, 0, 0);
        ARG(uint64x2_t, a1, 1, 0);
        KEEP(uint64x2_t, vqsubq_u64(a0, a1));
    }
    SUM("vqsubq_u64", sum);
}

int main(void)
{
    t_vqsub_s8();
    t_vqsub_s16();
    t_vqsub_s32();
    t_vqsub_s64();
    t_vqsub_u8();
    t_vqsub_u16();
    t_vqsub_u32();
    t_vqsub_u64();
    t_vqsubq_s8();
    t_vqsubq_s16();
    t_vqsubq_s32();
    t_vqsubq_s64();
    t_vqsubq_u8();
    t_vqsubq_u16();
    t_vqsubq_u32();
    t_vqsubq_u64();
    return 0;
}
