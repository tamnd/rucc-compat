/* The vrbit family of arm_neon.h.
 *
 * Written by scripts/arm_neon.py from corpus/intrinsics/arm_neon.txt, which is the file to change. Each
 * function calls one intrinsic over the rounds check.h generates, at every immediate the script
 * picks, and prints a checksum of what came back. The reference builds this program with its own
 * arm_neon.h and has to print the same lines, which is the whole of the check. */
#include <arm_neon.h>

#include "../check.h"
#include "../neon.h"

static void t_vrbit_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x8_t, a0, 0, 0);
        KEEP(int8x8_t, vrbit_s8(a0));
    }
    SUM("vrbit_s8", sum);
}

static void t_vrbit_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x8_t, a0, 0, 0);
        KEEP(uint8x8_t, vrbit_u8(a0));
    }
    SUM("vrbit_u8", sum);
}

static void t_vrbitq_s8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(int8x16_t, a0, 0, 0);
        KEEP(int8x16_t, vrbitq_s8(a0));
    }
    SUM("vrbitq_s8", sum);
}

static void t_vrbitq_u8(void)
{
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        ARG(uint8x16_t, a0, 0, 0);
        KEEP(uint8x16_t, vrbitq_u8(a0));
    }
    SUM("vrbitq_u8", sum);
}

int main(void)
{
    t_vrbit_s8();
    t_vrbit_u8();
    t_vrbitq_s8();
    t_vrbitq_u8();
    return 0;
}
