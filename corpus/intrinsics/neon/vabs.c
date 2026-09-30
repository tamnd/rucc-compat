/* The vabs family of arm_neon.h.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vabs_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x8_t, a0, 0, 0);
        KEEP(int8x8_t, vabs_s8(a0));
    }
    SUM("vabs_s8", sum);
}

static void t_vabs_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x4_t, a0, 0, 0);
        KEEP(int16x4_t, vabs_s16(a0));
    }
    SUM("vabs_s16", sum);
}

static void t_vabs_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x2_t, a0, 0, 0);
        KEEP(int32x2_t, vabs_s32(a0));
    }
    SUM("vabs_s32", sum);
}

static void t_vabs_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x1_t, a0, 0, 0);
        KEEP(int64x1_t, vabs_s64(a0));
    }
    SUM("vabs_s64", sum);
}

static void t_vabsq_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x16_t, a0, 0, 0);
        KEEP(int8x16_t, vabsq_s8(a0));
    }
    SUM("vabsq_s8", sum);
}

static void t_vabsq_s16(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int16x8_t, a0, 0, 0);
        KEEP(int16x8_t, vabsq_s16(a0));
    }
    SUM("vabsq_s16", sum);
}

static void t_vabsq_s32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int32x4_t, a0, 0, 0);
        KEEP(int32x4_t, vabsq_s32(a0));
    }
    SUM("vabsq_s32", sum);
}

static void t_vabsq_s64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int64x2_t, a0, 0, 0);
        KEEP(int64x2_t, vabsq_s64(a0));
    }
    SUM("vabsq_s64", sum);
}

int main(void)
{
    t_vabs_s8();
    t_vabs_s16();
    t_vabs_s32();
    t_vabs_s64();
    t_vabsq_s8();
    t_vabsq_s16();
    t_vabsq_s32();
    t_vabsq_s64();
    return 0;
}
