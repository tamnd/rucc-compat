/* What the programs under neon/ call to make their inputs, on top of check.h.
 *
 * Every argument of every intrinsic is filled by `neon_arg`: the argument's bytes from `fill`, with
 * the edge rounds turned by the argument's position so that the two operands of an addition are
 * not the same edge pattern, and on one round in three past the edges a floating point argument is
 * ordinary numbers instead. Random bits are nearly all huge, tiny, infinite or not a number when
 * read as a float, and an operation that is only wrong on the numbers people actually add would
 * never be asked about one. */

#ifndef INTRINSICS_NEON_H
#define INTRINSICS_NEON_H

#include "check.h"

static inline void neon_arg(void *out, size_t n, int round, int k, int float_bits)
{
    fill(out, n, round < 8 ? (round + 3 * k) % 8 : round);
    if (float_bits == 0 || round < 8 || round % 3 != 1)
        return;
    uint8_t *p = out;
    size_t width = (size_t)float_bits / 8;
    for (size_t i = 0; i + width <= n; i += width) {
        double v = (double)((int64_t)(next_random() % 4001) - 2000) / 16.0;
        if (float_bits == 32) {
            float f = (float)v;
            memcpy(p + i, &f, 4);
        } else {
            memcpy(p + i, &v, 8);
        }
    }
}

/* The shape every generated function is written in, so that a program of sixty intrinsics reads as
 * sixty lists of calls rather than as the same ten lines of bookkeeping sixty times. Each one
 * expects the round in `r` and the running checksum in `sum`. `ARG` is one argument, `BUF` is
 * sixty four lanes for an intrinsic that loads or stores through a pointer, `KEEP` folds what an
 * intrinsic returned into the checksum and `STORE` folds what it wrote. */
#define ARG(T, NAME, K, FLOAT) T NAME; neon_arg(&NAME, sizeof NAME, r, K, FLOAT)
#define BUF(T, NAME, K, FLOAT) T NAME[64]; neon_arg(NAME, sizeof NAME, r, K, FLOAT)
#define KEEP(T, CALL)                                                                             \
    do {                                                                                          \
        T kept_ = CALL;                                                                           \
        sum = fold(sum, &kept_, sizeof kept_);                                                    \
    } while (0)
#define STORE(CALL, NAME)                                                                         \
    do {                                                                                          \
        CALL;                                                                                     \
        sum = fold(sum, NAME, sizeof NAME);                                                       \
    } while (0)
#define SUM(NAME, SUM) printf("sum %s %016llx\n", NAME, (unsigned long long)(SUM))

#endif
