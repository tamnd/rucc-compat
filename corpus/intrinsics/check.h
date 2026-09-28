/* What every program here includes.
 *
 * A program works an intrinsic over a few thousand inputs, works the same thing out a lane at a
 * time in plain C, and prints one line per intrinsic: `ok`, the name and a checksum of everything
 * the intrinsic returned, or `FAIL`, the name and the first input it got wrong. The run is then
 * compared line for line against the same program built by the reference, so a wrong answer shows
 * up twice, once as a FAIL and once as a checksum the reference does not print.
 *
 * The inputs come from a fixed generator, so both builds see the same ones, and the first rounds
 * are the values an intrinsic is most likely to get wrong: zero, all ones, and the lanes either
 * side of the sign bit. */

#ifndef INTRINSICS_CHECK_H
#define INTRINSICS_CHECK_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

static int failures;

#define ROUNDS 2000

static uint64_t rng_state = 0x9e3779b97f4a7c15u;

static inline uint64_t next_random(void)
{
    uint64_t x = rng_state;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    rng_state = x;
    return x;
}

/* Fills `n` bytes for round `round`. The first eight rounds are the edge patterns and the rest are
 * random, with one round in four having a few lanes pinned to an edge value so that saturation and
 * sign handling are exercised in the middle of otherwise random data. */
static inline void fill(void *out, size_t n, int round)
{
    static const uint8_t edges[8] = {0x00, 0xff, 0x80, 0x7f, 0x01, 0xfe, 0x81, 0x55};
    uint8_t *p = out;
    if (round < 8) {
        for (size_t i = 0; i < n; i++)
            p[i] = (round == 7) ? (uint8_t)(i & 1 ? 0x80 : 0x7f) : edges[round];
        return;
    }
    for (size_t i = 0; i < n; i += 8) {
        uint64_t r = next_random();
        size_t k = n - i < 8 ? n - i : 8;
        memcpy(p + i, &r, k);
    }
    if ((round & 3) == 0) {
        uint64_t r = next_random();
        for (int j = 0; j < 3; j++) {
            size_t at = (size_t)((r >> (j * 8)) & 0xff) % n;
            p[at] = edges[(r >> (32 + j * 3)) & 7];
        }
    }
}

/* A running checksum over what an intrinsic returned, so the line printed for a pass says
 * something about the values and not only that the two ways of working them out agreed. */
static inline uint64_t fold(uint64_t sum, const void *data, size_t n)
{
    const uint8_t *p = data;
    for (size_t i = 0; i < n; i++)
        sum = (sum ^ p[i]) * 0x100000001b3u;
    return sum;
}

static inline void show_bytes(const char *label, const void *data, size_t n)
{
    const uint8_t *p = data;
    printf("  %s", label);
    for (size_t i = 0; i < n; i++)
        printf(" %02x", p[i]);
    printf("\n");
}

static inline void report(const char *name, int bad, uint64_t sum)
{
    if (bad) {
        printf("FAIL %s: %d of %d rounds wrong\n", name, bad, ROUNDS);
        failures++;
    } else {
        printf("ok %s %016llx\n", name, (unsigned long long)sum);
    }
}

/* Records one round. On the first wrong round of an intrinsic the inputs, what it returned and
 * what the plain C says it should have returned are printed, which is usually enough to see what
 * went wrong without a debugger. */
static inline void judge(int *bad, uint64_t *sum, const void *a, const void *b, size_t in, const void *got,
                         const void *want, size_t out)
{
    if (memcmp(got, want, out) != 0) {
        if (*bad == 0) {
            show_bytes("a   ", a, in);
            if (b)
                show_bytes("b   ", b, in);
            show_bytes("got ", got, out);
            show_bytes("want", want, out);
        }
        (*bad)++;
    }
    *sum = fold(*sum, got, out);
}

#define DONE() return failures != 0

#endif
