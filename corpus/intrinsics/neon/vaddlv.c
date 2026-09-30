/* The vaddlv family of arm_neon.h.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vaddlv_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x8_t, a0, 0, 0);
        KEEP(int16_t, vaddlv_s8(a0));
    }
    SUM("vaddlv_s8", sum);
}

static void t_vaddlvq_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x16_t, a0, 0, 0);
        KEEP(int16_t, vaddlvq_s8(a0));
    }
    SUM("vaddlvq_s8", sum);
}

static void t_vaddlv_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x4_t, a0, 0, 0);
        KEEP(int32_t, vaddlv_s16(a0));
    }
    SUM("vaddlv_s16", sum);
}

static void t_vaddlvq_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x8_t, a0, 0, 0);
        KEEP(int32_t, vaddlvq_s16(a0));
    }
    SUM("vaddlvq_s16", sum);
}

static void t_vaddlv_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x2_t, a0, 0, 0);
        KEEP(int64_t, vaddlv_s32(a0));
    }
    SUM("vaddlv_s32", sum);
}

static void t_vaddlvq_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x4_t, a0, 0, 0);
        KEEP(int64_t, vaddlvq_s32(a0));
    }
    SUM("vaddlvq_s32", sum);
}

static void t_vaddlv_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x8_t, a0, 0, 0);
        KEEP(uint16_t, vaddlv_u8(a0));
    }
    SUM("vaddlv_u8", sum);
}

static void t_vaddlvq_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x16_t, a0, 0, 0);
        KEEP(uint16_t, vaddlvq_u8(a0));
    }
    SUM("vaddlvq_u8", sum);
}

static void t_vaddlv_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x4_t, a0, 0, 0);
        KEEP(uint32_t, vaddlv_u16(a0));
    }
    SUM("vaddlv_u16", sum);
}

static void t_vaddlvq_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x8_t, a0, 0, 0);
        KEEP(uint32_t, vaddlvq_u16(a0));
    }
    SUM("vaddlvq_u16", sum);
}

static void t_vaddlv_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x2_t, a0, 0, 0);
        KEEP(uint64_t, vaddlv_u32(a0));
    }
    SUM("vaddlv_u32", sum);
}

static void t_vaddlvq_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x4_t, a0, 0, 0);
        KEEP(uint64_t, vaddlvq_u32(a0));
    }
    SUM("vaddlvq_u32", sum);
}

int main(void)
{
    t_vaddlv_s8();
    t_vaddlvq_s8();
    t_vaddlv_s16();
    t_vaddlvq_s16();
    t_vaddlv_s32();
    t_vaddlvq_s32();
    t_vaddlv_u8();
    t_vaddlvq_u8();
    t_vaddlv_u16();
    t_vaddlvq_u16();
    t_vaddlv_u32();
    t_vaddlvq_u32();
    return 0;
}
