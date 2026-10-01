/* The vabd family of arm_neon.h.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vabd_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x8_t, a0, 0, 0);
        ARG(int8x8_t, a1, 1, 0);
        KEEP(int8x8_t, vabd_s8(a0, a1));
    }
    SUM("vabd_s8", sum);
}

static void t_vabd_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x4_t, a0, 0, 0);
        ARG(int16x4_t, a1, 1, 0);
        KEEP(int16x4_t, vabd_s16(a0, a1));
    }
    SUM("vabd_s16", sum);
}

static void t_vabd_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x2_t, a0, 0, 0);
        ARG(int32x2_t, a1, 1, 0);
        KEEP(int32x2_t, vabd_s32(a0, a1));
    }
    SUM("vabd_s32", sum);
}

static void t_vabd_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x8_t, a0, 0, 0);
        ARG(uint8x8_t, a1, 1, 0);
        KEEP(uint8x8_t, vabd_u8(a0, a1));
    }
    SUM("vabd_u8", sum);
}

static void t_vabd_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x4_t, a0, 0, 0);
        ARG(uint16x4_t, a1, 1, 0);
        KEEP(uint16x4_t, vabd_u16(a0, a1));
    }
    SUM("vabd_u16", sum);
}

static void t_vabd_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x2_t, a0, 0, 0);
        ARG(uint32x2_t, a1, 1, 0);
        KEEP(uint32x2_t, vabd_u32(a0, a1));
    }
    SUM("vabd_u32", sum);
}

static void t_vabd_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x2_t, a0, 0, 32);
        ARG(float32x2_t, a1, 1, 32);
        KEEP(float32x2_t, vabd_f32(a0, a1));
    }
    SUM("vabd_f32", sum);
}

static void t_vabd_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x1_t, a0, 0, 64);
        ARG(float64x1_t, a1, 1, 64);
        KEEP(float64x1_t, vabd_f64(a0, a1));
    }
    SUM("vabd_f64", sum);
}

static void t_vabdq_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x16_t, a0, 0, 0);
        ARG(int8x16_t, a1, 1, 0);
        KEEP(int8x16_t, vabdq_s8(a0, a1));
    }
    SUM("vabdq_s8", sum);
}

static void t_vabdq_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x8_t, a0, 0, 0);
        ARG(int16x8_t, a1, 1, 0);
        KEEP(int16x8_t, vabdq_s16(a0, a1));
    }
    SUM("vabdq_s16", sum);
}

static void t_vabdq_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x4_t, a0, 0, 0);
        ARG(int32x4_t, a1, 1, 0);
        KEEP(int32x4_t, vabdq_s32(a0, a1));
    }
    SUM("vabdq_s32", sum);
}

static void t_vabdq_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x16_t, a0, 0, 0);
        ARG(uint8x16_t, a1, 1, 0);
        KEEP(uint8x16_t, vabdq_u8(a0, a1));
    }
    SUM("vabdq_u8", sum);
}

static void t_vabdq_u16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint16x8_t, a0, 0, 0);
        ARG(uint16x8_t, a1, 1, 0);
        KEEP(uint16x8_t, vabdq_u16(a0, a1));
    }
    SUM("vabdq_u16", sum);
}

static void t_vabdq_u32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint32x4_t, a0, 0, 0);
        ARG(uint32x4_t, a1, 1, 0);
        KEEP(uint32x4_t, vabdq_u32(a0, a1));
    }
    SUM("vabdq_u32", sum);
}

static void t_vabdq_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x4_t, a0, 0, 32);
        ARG(float32x4_t, a1, 1, 32);
        KEEP(float32x4_t, vabdq_f32(a0, a1));
    }
    SUM("vabdq_f32", sum);
}

static void t_vabdq_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x2_t, a0, 0, 64);
        ARG(float64x2_t, a1, 1, 64);
        KEEP(float64x2_t, vabdq_f64(a0, a1));
    }
    SUM("vabdq_f64", sum);
}

int main(void)
{
    t_vabd_s8();
    t_vabd_s16();
    t_vabd_s32();
    t_vabd_u8();
    t_vabd_u16();
    t_vabd_u32();
    t_vabd_f32();
    t_vabd_f64();
    t_vabdq_s8();
    t_vabdq_s16();
    t_vabdq_s32();
    t_vabdq_u8();
    t_vabdq_u16();
    t_vabdq_u32();
    t_vabdq_f32();
    t_vabdq_f64();
    return 0;
}
