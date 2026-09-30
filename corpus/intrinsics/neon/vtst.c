/* The vtst family of arm_neon.h.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vtst_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x8_t, a0, 0, 0);
        ARG(int8x8_t, a1, 1, 0);
        KEEP(uint8x8_t, vtst_s8(a0, a1));
    }
    SUM("vtst_s8", sum);
}

static void t_vtst_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x4_t, a0, 0, 0);
        ARG(int16x4_t, a1, 1, 0);
        KEEP(uint16x4_t, vtst_s16(a0, a1));
    }
    SUM("vtst_s16", sum);
}

static void t_vtst_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x2_t, a0, 0, 0);
        ARG(int32x2_t, a1, 1, 0);
        KEEP(uint32x2_t, vtst_s32(a0, a1));
    }
    SUM("vtst_s32", sum);
}

static void t_vtst_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x1_t, a0, 0, 0);
        ARG(int64x1_t, a1, 1, 0);
        KEEP(uint64x1_t, vtst_s64(a0, a1));
    }
    SUM("vtst_s64", sum);
}

static void t_vtst_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x8_t, a0, 0, 0);
        ARG(uint8x8_t, a1, 1, 0);
        KEEP(uint8x8_t, vtst_u8(a0, a1));
    }
    SUM("vtst_u8", sum);
}

static void t_vtst_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x4_t, a0, 0, 0);
        ARG(uint16x4_t, a1, 1, 0);
        KEEP(uint16x4_t, vtst_u16(a0, a1));
    }
    SUM("vtst_u16", sum);
}

static void t_vtst_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x2_t, a0, 0, 0);
        ARG(uint32x2_t, a1, 1, 0);
        KEEP(uint32x2_t, vtst_u32(a0, a1));
    }
    SUM("vtst_u32", sum);
}

static void t_vtst_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x1_t, a0, 0, 0);
        ARG(uint64x1_t, a1, 1, 0);
        KEEP(uint64x1_t, vtst_u64(a0, a1));
    }
    SUM("vtst_u64", sum);
}

static void t_vtst_p8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly8x8_t, a0, 0, 0);
        ARG(poly8x8_t, a1, 1, 0);
        KEEP(uint8x8_t, vtst_p8(a0, a1));
    }
    SUM("vtst_p8", sum);
}

static void t_vtst_p16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly16x4_t, a0, 0, 0);
        ARG(poly16x4_t, a1, 1, 0);
        KEEP(uint16x4_t, vtst_p16(a0, a1));
    }
    SUM("vtst_p16", sum);
}

static void t_vtst_p64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly64x1_t, a0, 0, 0);
        ARG(poly64x1_t, a1, 1, 0);
        KEEP(uint64x1_t, vtst_p64(a0, a1));
    }
    SUM("vtst_p64", sum);
}

static void t_vtstq_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x16_t, a0, 0, 0);
        ARG(int8x16_t, a1, 1, 0);
        KEEP(uint8x16_t, vtstq_s8(a0, a1));
    }
    SUM("vtstq_s8", sum);
}

static void t_vtstq_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x8_t, a0, 0, 0);
        ARG(int16x8_t, a1, 1, 0);
        KEEP(uint16x8_t, vtstq_s16(a0, a1));
    }
    SUM("vtstq_s16", sum);
}

static void t_vtstq_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x4_t, a0, 0, 0);
        ARG(int32x4_t, a1, 1, 0);
        KEEP(uint32x4_t, vtstq_s32(a0, a1));
    }
    SUM("vtstq_s32", sum);
}

static void t_vtstq_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x2_t, a0, 0, 0);
        ARG(int64x2_t, a1, 1, 0);
        KEEP(uint64x2_t, vtstq_s64(a0, a1));
    }
    SUM("vtstq_s64", sum);
}

static void t_vtstq_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x16_t, a0, 0, 0);
        ARG(uint8x16_t, a1, 1, 0);
        KEEP(uint8x16_t, vtstq_u8(a0, a1));
    }
    SUM("vtstq_u8", sum);
}

static void t_vtstq_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x8_t, a0, 0, 0);
        ARG(uint16x8_t, a1, 1, 0);
        KEEP(uint16x8_t, vtstq_u16(a0, a1));
    }
    SUM("vtstq_u16", sum);
}

static void t_vtstq_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x4_t, a0, 0, 0);
        ARG(uint32x4_t, a1, 1, 0);
        KEEP(uint32x4_t, vtstq_u32(a0, a1));
    }
    SUM("vtstq_u32", sum);
}

static void t_vtstq_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x2_t, a0, 0, 0);
        ARG(uint64x2_t, a1, 1, 0);
        KEEP(uint64x2_t, vtstq_u64(a0, a1));
    }
    SUM("vtstq_u64", sum);
}

static void t_vtstq_p8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly8x16_t, a0, 0, 0);
        ARG(poly8x16_t, a1, 1, 0);
        KEEP(uint8x16_t, vtstq_p8(a0, a1));
    }
    SUM("vtstq_p8", sum);
}

static void t_vtstq_p16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly16x8_t, a0, 0, 0);
        ARG(poly16x8_t, a1, 1, 0);
        KEEP(uint16x8_t, vtstq_p16(a0, a1));
    }
    SUM("vtstq_p16", sum);
}

static void t_vtstq_p64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly64x2_t, a0, 0, 0);
        ARG(poly64x2_t, a1, 1, 0);
        KEEP(uint64x2_t, vtstq_p64(a0, a1));
    }
    SUM("vtstq_p64", sum);
}

int main(void)
{
    t_vtst_s8();
    t_vtst_s16();
    t_vtst_s32();
    t_vtst_s64();
    t_vtst_u8();
    t_vtst_u16();
    t_vtst_u32();
    t_vtst_u64();
    t_vtst_p8();
    t_vtst_p16();
    t_vtst_p64();
    t_vtstq_s8();
    t_vtstq_s16();
    t_vtstq_s32();
    t_vtstq_s64();
    t_vtstq_u8();
    t_vtstq_u16();
    t_vtstq_u32();
    t_vtstq_u64();
    t_vtstq_p8();
    t_vtstq_p16();
    t_vtstq_p64();
    return 0;
}
