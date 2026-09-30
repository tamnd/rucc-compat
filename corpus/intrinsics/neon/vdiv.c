/* The vdiv family of arm_neon.h.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vdiv_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x2_t, a0, 0, 32);
        ARG(float32x2_t, a1, 1, 32);
        KEEP(float32x2_t, vdiv_f32(a0, a1));
    }
    SUM("vdiv_f32", sum);
}

static void t_vdiv_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x1_t, a0, 0, 64);
        ARG(float64x1_t, a1, 1, 64);
        KEEP(float64x1_t, vdiv_f64(a0, a1));
    }
    SUM("vdiv_f64", sum);
}

static void t_vdivq_f32(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float32x4_t, a0, 0, 32);
        ARG(float32x4_t, a1, 1, 32);
        KEEP(float32x4_t, vdivq_f32(a0, a1));
    }
    SUM("vdivq_f32", sum);
}

static void t_vdivq_f64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(float64x2_t, a0, 0, 64);
        ARG(float64x2_t, a1, 1, 64);
        KEEP(float64x2_t, vdivq_f64(a0, a1));
    }
    SUM("vdivq_f64", sum);
}

int main(void)
{
    t_vdiv_f32();
    t_vdiv_f64();
    t_vdivq_f32();
    t_vdivq_f64();
    return 0;
}
