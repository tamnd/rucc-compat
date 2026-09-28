/* The SSE2 half of Postgres's src/include/port/simd.h, written the way Postgres writes it.
 *
 * Postgres builds every search in simd.h out of a few SSE2 intrinsics: an unaligned load, a byte
 * or word broadcast, an equality compare, an unsigned minimum, a saturating subtraction, an or, and
 * a movemask to turn the answer into bits. pg_lfind.h puts those together to search arrays, and the
 * JSON lexer and the COPY parser call them on every byte of input. The functions below are copied
 * from simd.h and pg_lfind.h with Postgres's types spelled out, and each is checked against the
 * byte at a time loop it replaces. */
#include <emmintrin.h>
#include <stdbool.h>

#include "../check.h"

typedef __m128i Vector8;
typedef __m128i Vector32;

static inline void vector8_load(Vector8 *v, const uint8_t *s) { *v = _mm_loadu_si128((const __m128i *)s); }
static inline void vector32_load(Vector32 *v, const uint32_t *s) { *v = _mm_loadu_si128((const __m128i *)s); }
static inline Vector8 vector8_broadcast(const uint8_t c) { return _mm_set1_epi8((char)c); }
static inline Vector32 vector32_broadcast(const uint32_t c) { return _mm_set1_epi32((int)c); }
static inline Vector8 vector8_eq(const Vector8 v1, const Vector8 v2) { return _mm_cmpeq_epi8(v1, v2); }
static inline Vector32 vector32_eq(const Vector32 v1, const Vector32 v2) { return _mm_cmpeq_epi32(v1, v2); }
static inline Vector8 vector8_min(const Vector8 v1, const Vector8 v2) { return _mm_min_epu8(v1, v2); }
static inline Vector8 vector8_ssub(const Vector8 v1, const Vector8 v2) { return _mm_subs_epu8(v1, v2); }
static inline Vector8 vector8_or(const Vector8 v1, const Vector8 v2) { return _mm_or_si128(v1, v2); }
static inline Vector32 vector32_or(const Vector32 v1, const Vector32 v2) { return _mm_or_si128(v1, v2); }
static inline bool vector8_is_highbit_set(const Vector8 v) { return _mm_movemask_epi8(v) != 0; }
static inline bool vector32_is_highbit_set(const Vector32 v) { return vector8_is_highbit_set((Vector8)v); }
static inline uint32_t vector8_highbit_mask(const Vector8 v) { return (uint32_t)_mm_movemask_epi8(v); }

static inline bool vector8_has(const Vector8 v, const uint8_t c)
{
    return vector8_is_highbit_set(vector8_eq(v, vector8_broadcast(c)));
}

static inline bool vector8_has_zero(const Vector8 v) { return vector8_has(v, 0); }

static inline bool vector8_has_le(const Vector8 v, const uint8_t c)
{
    return vector8_has_zero(vector8_ssub(v, vector8_broadcast(c)));
}

/* pg_lfind32, the four vector unrolled search over an array of uint32, as pg_lfind.h has it. */
static bool pg_lfind32(uint32_t key, const uint32_t *base, uint32_t nelem)
{
    uint32_t i = 0;
    const uint32_t nelem_per_vector = sizeof(Vector32) / sizeof(uint32_t);
    const uint32_t nelem_per_iteration = 4 * nelem_per_vector;
    const Vector32 keys = vector32_broadcast(key);
    const uint32_t tail_idx = nelem & ~(nelem_per_iteration - 1);

    for (i = 0; i < tail_idx; i += nelem_per_iteration) {
        Vector32 vals1, vals2, vals3, vals4, result1, result2, result3, result4, tmp1, tmp2, result;
        vector32_load(&vals1, &base[i]);
        vector32_load(&vals2, &base[i + nelem_per_vector]);
        vector32_load(&vals3, &base[i + nelem_per_vector * 2]);
        vector32_load(&vals4, &base[i + nelem_per_vector * 3]);
        result1 = vector32_eq(keys, vals1);
        result2 = vector32_eq(keys, vals2);
        result3 = vector32_eq(keys, vals3);
        result4 = vector32_eq(keys, vals4);
        tmp1 = vector32_or(result1, result2);
        tmp2 = vector32_or(result3, result4);
        result = vector32_or(tmp1, tmp2);
        if (vector32_is_highbit_set(result))
            return true;
    }
    for (; i < nelem; i++) {
        if (key == base[i])
            return true;
    }
    return false;
}

/* pg_lfind8 and pg_lfind8_le, which search a byte array one vector at a time. */
static bool pg_lfind8(uint8_t key, const uint8_t *base, uint32_t nelem)
{
    uint32_t i;
    Vector8 chunk;
    for (i = 0; i < nelem - nelem % sizeof(Vector8); i += sizeof(Vector8)) {
        vector8_load(&chunk, &base[i]);
        if (vector8_has(chunk, key))
            return true;
    }
    for (; i < nelem; i++)
        if (key == base[i])
            return true;
    return false;
}

static bool pg_lfind8_le(uint8_t key, const uint8_t *base, uint32_t nelem)
{
    uint32_t i;
    Vector8 chunk;
    for (i = 0; i < nelem - nelem % sizeof(Vector8); i += sizeof(Vector8)) {
        vector8_load(&chunk, &base[i]);
        if (vector8_has_le(chunk, key))
            return true;
    }
    for (; i < nelem; i++)
        if (base[i] <= key)
            return true;
    return false;
}

static void t_vector8(void)
{
    int bad = 0;
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        uint8_t a[16], b[16];
        Vector8 v, w;
        fill(a, 16, r);
        fill(b, 16, r < 8 ? (r + 3) % 8 : r);
        vector8_load(&v, a);
        vector8_load(&w, b);
        uint8_t c = (uint8_t)next_random();
        if (r & 1)
            c = a[r % 16];

        int want[8] = {0}, got[8];
        for (int i = 0; i < 16; i++) {
            want[0] |= a[i] == c;
            want[1] |= a[i] == 0;
            want[2] |= a[i] <= c;
            want[3] |= a[i] >> 7;
            want[4] |= (a[i] >> 7) << i;
        }
        uint8_t eq[16], mn[16], ss[16], orr[16];
        uint8_t weq[16], wmn[16], wss[16], wor[16];
        for (int i = 0; i < 16; i++) {
            weq[i] = a[i] == b[i] ? 0xff : 0;
            wmn[i] = a[i] < b[i] ? a[i] : b[i];
            wss[i] = a[i] > b[i] ? (uint8_t)(a[i] - b[i]) : 0;
            wor[i] = a[i] | b[i];
        }
        got[0] = vector8_has(v, c);
        got[1] = vector8_has_zero(v);
        got[2] = vector8_has_le(v, c);
        got[3] = vector8_is_highbit_set(v);
        got[4] = (int)vector8_highbit_mask(v);
        got[5] = got[6] = got[7] = 0;
        judge(&bad, &sum, a, NULL, 16, got, want, sizeof want);
        Vector8 e = vector8_eq(v, w), m = vector8_min(v, w), s = vector8_ssub(v, w), o = vector8_or(v, w);
        memcpy(eq, &e, 16);
        memcpy(mn, &m, 16);
        memcpy(ss, &s, 16);
        memcpy(orr, &o, 16);
        judge(&bad, &sum, a, b, 16, eq, weq, 16);
        judge(&bad, &sum, a, b, 16, mn, wmn, 16);
        judge(&bad, &sum, a, b, 16, ss, wss, 16);
        judge(&bad, &sum, a, b, 16, orr, wor, 16);
    }
    report("vector8", bad, sum);
}

static void t_vector32(void)
{
    int bad = 0;
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        uint32_t a[4], b[4], got[4], want[4];
        Vector32 v, w;
        fill(a, 16, r);
        fill(b, 16, r < 8 ? (r + 3) % 8 : r);
        if (r & 1)
            b[r % 4] = a[r % 4];
        vector32_load(&v, a);
        vector32_load(&w, b);
        Vector32 e = vector32_eq(v, w);
        memcpy(got, &e, 16);
        for (int i = 0; i < 4; i++)
            want[i] = a[i] == b[i] ? 0xffffffffu : 0;
        judge(&bad, &sum, a, b, 16, got, want, 16);
        Vector32 o = vector32_or(v, w);
        memcpy(got, &o, 16);
        for (int i = 0; i < 4; i++)
            want[i] = a[i] | b[i];
        judge(&bad, &sum, a, b, 16, got, want, 16);
        Vector32 k = vector32_broadcast(a[1]);
        memcpy(got, &k, 16);
        for (int i = 0; i < 4; i++)
            want[i] = a[1];
        judge(&bad, &sum, a, NULL, 16, got, want, 16);
        int hb = vector32_is_highbit_set(v), whb = 0;
        for (int i = 0; i < 4; i++)
            whb |= (a[i] >> 31) | ((a[i] >> 23) & 1) | ((a[i] >> 15) & 1) | ((a[i] >> 7) & 1);
        judge(&bad, &sum, a, NULL, 16, &hb, &whb, sizeof hb);
    }
    report("vector32", bad, sum);
}

/* The searches over arrays of every length up to a few iterations of the unrolled loop, with the
 * key at every position and absent, which is where a tail loop that starts one element late or a
 * vector loop that reads one vector too many would show. */
static void t_lfind(void)
{
    int bad = 0;
    uint64_t sum = 0;
    uint32_t words[80];
    uint8_t bytes[80];
    fill(words, sizeof words, 100);
    fill(bytes, sizeof bytes, 101);
    for (uint32_t n = 0; n <= 70; n++) {
        for (uint32_t at = 0; at <= n; at++) {
            uint32_t key = at < n ? words[at] : 0x12345678u;
            int want = 0, got;
            for (uint32_t i = 0; i < n; i++)
                want |= words[i] == key;
            got = pg_lfind32(key, words, n);
            judge(&bad, &sum, &key, NULL, 4, &got, &want, sizeof got);

            uint8_t k8 = at < n ? bytes[at] : (uint8_t)(n * 37);
            int w8 = 0, w8le = 0, g8, g8le;
            for (uint32_t i = 0; i < n; i++) {
                w8 |= bytes[i] == k8;
                w8le |= bytes[i] <= k8;
            }
            g8 = pg_lfind8(k8, bytes, n);
            g8le = pg_lfind8_le(k8, bytes, n);
            judge(&bad, &sum, &k8, NULL, 1, &g8, &w8, sizeof g8);
            judge(&bad, &sum, &k8, NULL, 1, &g8le, &w8le, sizeof g8le);
        }
    }
    report("pg_lfind32_pg_lfind8", bad, sum);
}

int main(void)
{
    t_vector8();
    t_vector32();
    t_lfind();
    DONE();
}
