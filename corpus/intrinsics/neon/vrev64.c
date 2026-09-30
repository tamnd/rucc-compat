/* The vrev64 family of arm_neon.h.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vrev64_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x8_t, a0, 0, 0);
        KEEP(int8x8_t, vrev64_s8(a0));
    }
    SUM("vrev64_s8", sum);
}

static void t_vrev64_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x4_t, a0, 0, 0);
        KEEP(int16x4_t, vrev64_s16(a0));
    }
    SUM("vrev64_s16", sum);
}

static void t_vrev64_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x2_t, a0, 0, 0);
        KEEP(int32x2_t, vrev64_s32(a0));
    }
    SUM("vrev64_s32", sum);
}

static void t_vrev64_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x8_t, a0, 0, 0);
        KEEP(uint8x8_t, vrev64_u8(a0));
    }
    SUM("vrev64_u8", sum);
}

static void t_vrev64_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x4_t, a0, 0, 0);
        KEEP(uint16x4_t, vrev64_u16(a0));
    }
    SUM("vrev64_u16", sum);
}

static void t_vrev64_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x2_t, a0, 0, 0);
        KEEP(uint32x2_t, vrev64_u32(a0));
    }
    SUM("vrev64_u32", sum);
}

static void t_vrev64_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x2_t, a0, 0, 32);
        KEEP(float32x2_t, vrev64_f32(a0));
    }
    SUM("vrev64_f32", sum);
}

static void t_vrev64_p8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly8x8_t, a0, 0, 0);
        KEEP(poly8x8_t, vrev64_p8(a0));
    }
    SUM("vrev64_p8", sum);
}

static void t_vrev64_p16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly16x4_t, a0, 0, 0);
        KEEP(poly16x4_t, vrev64_p16(a0));
    }
    SUM("vrev64_p16", sum);
}

static void t_vrev64q_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x16_t, a0, 0, 0);
        KEEP(int8x16_t, vrev64q_s8(a0));
    }
    SUM("vrev64q_s8", sum);
}

static void t_vrev64q_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x8_t, a0, 0, 0);
        KEEP(int16x8_t, vrev64q_s16(a0));
    }
    SUM("vrev64q_s16", sum);
}

static void t_vrev64q_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x4_t, a0, 0, 0);
        KEEP(int32x4_t, vrev64q_s32(a0));
    }
    SUM("vrev64q_s32", sum);
}

static void t_vrev64q_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x16_t, a0, 0, 0);
        KEEP(uint8x16_t, vrev64q_u8(a0));
    }
    SUM("vrev64q_u8", sum);
}

static void t_vrev64q_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x8_t, a0, 0, 0);
        KEEP(uint16x8_t, vrev64q_u16(a0));
    }
    SUM("vrev64q_u16", sum);
}

static void t_vrev64q_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x4_t, a0, 0, 0);
        KEEP(uint32x4_t, vrev64q_u32(a0));
    }
    SUM("vrev64q_u32", sum);
}

static void t_vrev64q_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x4_t, a0, 0, 32);
        KEEP(float32x4_t, vrev64q_f32(a0));
    }
    SUM("vrev64q_f32", sum);
}

static void t_vrev64q_p8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly8x16_t, a0, 0, 0);
        KEEP(poly8x16_t, vrev64q_p8(a0));
    }
    SUM("vrev64q_p8", sum);
}

static void t_vrev64q_p16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(poly16x8_t, a0, 0, 0);
        KEEP(poly16x8_t, vrev64q_p16(a0));
    }
    SUM("vrev64q_p16", sum);
}

int main(void)
{
    t_vrev64_s8();
    t_vrev64_s16();
    t_vrev64_s32();
    t_vrev64_u8();
    t_vrev64_u16();
    t_vrev64_u32();
    t_vrev64_f32();
    t_vrev64_p8();
    t_vrev64_p16();
    t_vrev64q_s8();
    t_vrev64q_s16();
    t_vrev64q_s32();
    t_vrev64q_u8();
    t_vrev64q_u16();
    t_vrev64q_u32();
    t_vrev64q_f32();
    t_vrev64q_p8();
    t_vrev64q_p16();
    return 0;
}
