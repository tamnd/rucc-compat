/* _mm_popcnt_u32 and _mm_popcnt_u64, called from functions carrying
 * __attribute__((target("popcnt"))) in a unit built for the baseline, which is the shape of
 * Postgres's run time choice between the popcnt instruction and a table. Checked against a count
 * done a bit at a time, and not at all when cpuid says there is no popcnt. */
#include <cpuid.h>
#include <immintrin.h>

#include "../check.h"

__attribute__((target("popcnt"))) static int count32(uint32_t v) { return _mm_popcnt_u32(v); }
__attribute__((target("popcnt"))) static long long count64(uint64_t v) { return _mm_popcnt_u64(v); }

/* The shape of pg_popcount_fast: whole words through the instruction, the rest a byte at a time. */
__attribute__((target("popcnt"))) static uint64_t count_buffer(const uint8_t *buf, size_t n)
{
    uint64_t total = 0;
    while (n >= 8) {
        uint64_t w;
        memcpy(&w, buf, 8);
        total += (uint64_t)_mm_popcnt_u64(w);
        buf += 8;
        n -= 8;
    }
    while (n--)
        total += (uint64_t)_mm_popcnt_u32(*buf++);
    return total;
}

static int bits(uint64_t v)
{
    int n = 0;
    for (; v; v >>= 1)
        n += (int)(v & 1);
    return n;
}

int main(void)
{
    unsigned a, b, c, d;
    if (!__get_cpuid(1, &a, &b, &c, &d) || !(c & bit_POPCNT)) {
        printf("no popcnt, nothing to check\n");
        return 0;
    }
    int bad = 0;
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        uint64_t v;
        fill(&v, 8, r);
        long long got[2] = {count32((uint32_t)v), count64(v)};
        long long want[2] = {bits((uint32_t)v), bits(v)};
        judge(&bad, &sum, &v, NULL, 8, got, want, sizeof got);
    }
    report("_mm_popcnt_u32_u64", bad, sum);

    bad = 0;
    sum = 0;
    uint8_t buf[80];
    fill(buf, sizeof buf, 60);
    for (size_t len = 0; len <= 72; len++) {
        uint64_t want = 0;
        for (size_t i = 0; i < len; i++)
            want += (uint64_t)bits(buf[i + 3]);
        uint64_t got = count_buffer(buf + 3, len);
        judge(&bad, &sum, &len, NULL, sizeof len, &got, &want, 8);
    }
    report("popcount_buffer", bad, sum);
    DONE();
}
