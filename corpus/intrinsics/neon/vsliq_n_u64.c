/* vsliq_n_u64 on its own, because the manifest excuses it by name.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vsliq_n_u64(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint64x2_t, a0, 0, 0);
        ARG(uint64x2_t, a1, 1, 0);
        KEEP(uint64x2_t, vsliq_n_u64(a0, a1, 0));
        KEEP(uint64x2_t, vsliq_n_u64(a0, a1, 31));
        KEEP(uint64x2_t, vsliq_n_u64(a0, a1, 63));
    }
    SUM("vsliq_n_u64", sum);
}

int main(void)
{
    t_vsliq_n_u64();
    return 0;
}
