/* The SSE2 integer intrinsics, each one against the same operation done a lane at a time.
 *
 * Every name here is one rucc's emmintrin.h defines as C over the lanes of a vector, so a wrong
 * answer is a wrong lane width, a signed lane read as unsigned or the other way round, or a
 * saturation or shift count that is handled at the wrong edge. Postgres uses a handful of these
 * through simd.h, and simd_h.c checks those the way Postgres calls them. This file is the rest of
 * the family, so that a program other than Postgres gets the same answers too. */
#include <emmintrin.h>

#include "../check.h"

#define N(T) ((int)(16 / sizeof(T)))

static int sat_i8(int v) { return v < -128 ? -128 : v > 127 ? 127 : v; }
static int sat_u8(int v) { return v < 0 ? 0 : v > 255 ? 255 : v; }
static int sat_i16(int v) { return v < -32768 ? -32768 : v > 32767 ? 32767 : v; }
static int sat_u16(int v) { return v < 0 ? 0 : v > 65535 ? 65535 : v; }

/* One intrinsic of two vectors. `REF` fills `want` from `a` and `b` and must not have a comma
 * outside parentheses in it, since it is a macro argument. */
#define TEST2(NAME, T, U, CALL, REF)                                                             \
    static void t_##NAME(void)                                                                   \
    {                                                                                            \
        int bad = 0;                                                                             \
        uint64_t sum = 0;                                                                        \
        for (int r = 0; r < ROUNDS; r++) {                                                       \
            T a[N(T)];                                                                           \
            T b[N(T)];                                                                           \
            U want[N(U)];                                                                        \
            U got[N(U)];                                                                         \
            __m128i va, vb, vr;                                                                  \
            fill(a, 16, r);                                                                      \
            fill(b, 16, r < 8 ? (r + 3) % 8 : r);                                                \
            memcpy(&va, a, 16);                                                                  \
            memcpy(&vb, b, 16);                                                                  \
            vr = CALL;                                                                           \
            memcpy(got, &vr, 16);                                                                \
            memset(want, 0, 16);                                                                 \
            REF;                                                                                 \
            judge(&bad, &sum, a, b, 16, got, want, 16);                                          \
        }                                                                                        \
        report(#NAME, bad, sum);                                                                 \
    }

/* The same for an intrinsic of one vector, usually with an immediate in the name of the test. */
#define TEST1(NAME, T, U, CALL, REF)                                                             \
    static void t_##NAME(void)                                                                   \
    {                                                                                            \
        int bad = 0;                                                                             \
        uint64_t sum = 0;                                                                        \
        for (int r = 0; r < ROUNDS; r++) {                                                       \
            T a[N(T)];                                                                           \
            U want[N(U)];                                                                        \
            U got[N(U)];                                                                         \
            __m128i va, vr;                                                                      \
            fill(a, 16, r);                                                                      \
            memcpy(&va, a, 16);                                                                  \
            vr = CALL;                                                                           \
            memcpy(got, &vr, 16);                                                                \
            memset(want, 0, 16);                                                                 \
            REF;                                                                                 \
            judge(&bad, &sum, a, NULL, 16, got, want, 16);                                       \
        }                                                                                        \
        report(#NAME, bad, sum);                                                                 \
    }

#define LANES(T, EXPR)                                                                           \
    for (int i = 0; i < N(T); i++) {                                                             \
        T x = a[i];                                                                              \
        T y = b[i];                                                                              \
        (void)y;                                                                                 \
        want[i] = (T)(EXPR);                                                                     \
    }

#define LANES1(T, EXPR)                                                                          \
    for (int i = 0; i < N(T); i++) {                                                             \
        T x = a[i];                                                                              \
        want[i] = (T)(EXPR);                                                                     \
    }

/* Bytes. */
TEST2(add_epi8, uint8_t, uint8_t, _mm_add_epi8(va, vb), LANES(uint8_t, x + y))
TEST2(sub_epi8, uint8_t, uint8_t, _mm_sub_epi8(va, vb), LANES(uint8_t, x - y))
TEST2(adds_epi8, int8_t, int8_t, _mm_adds_epi8(va, vb), LANES(int8_t, sat_i8(x + y)))
TEST2(subs_epi8, int8_t, int8_t, _mm_subs_epi8(va, vb), LANES(int8_t, sat_i8(x - y)))
TEST2(adds_epu8, uint8_t, uint8_t, _mm_adds_epu8(va, vb), LANES(uint8_t, sat_u8(x + y)))
TEST2(subs_epu8, uint8_t, uint8_t, _mm_subs_epu8(va, vb), LANES(uint8_t, sat_u8(x - y)))
TEST2(avg_epu8, uint8_t, uint8_t, _mm_avg_epu8(va, vb), LANES(uint8_t, (x + y + 1) >> 1))
TEST2(min_epu8, uint8_t, uint8_t, _mm_min_epu8(va, vb), LANES(uint8_t, x < y ? x : y))
TEST2(max_epu8, uint8_t, uint8_t, _mm_max_epu8(va, vb), LANES(uint8_t, x > y ? x : y))
TEST2(cmpeq_epi8, int8_t, int8_t, _mm_cmpeq_epi8(va, vb), LANES(int8_t, x == y ? -1 : 0))
TEST2(cmpgt_epi8, int8_t, int8_t, _mm_cmpgt_epi8(va, vb), LANES(int8_t, x > y ? -1 : 0))
TEST2(cmplt_epi8, int8_t, int8_t, _mm_cmplt_epi8(va, vb), LANES(int8_t, x < y ? -1 : 0))

/* Sixteen bit lanes. The products are worked out in 32 bits so that nothing here overflows an
 * int, which the lanes themselves are allowed to and C is not. */
TEST2(add_epi16, uint16_t, uint16_t, _mm_add_epi16(va, vb), LANES(uint16_t, x + y))
TEST2(sub_epi16, uint16_t, uint16_t, _mm_sub_epi16(va, vb), LANES(uint16_t, x - y))
TEST2(adds_epi16, int16_t, int16_t, _mm_adds_epi16(va, vb), LANES(int16_t, sat_i16(x + y)))
TEST2(subs_epi16, int16_t, int16_t, _mm_subs_epi16(va, vb), LANES(int16_t, sat_i16(x - y)))
TEST2(adds_epu16, uint16_t, uint16_t, _mm_adds_epu16(va, vb), LANES(uint16_t, sat_u16(x + y)))
TEST2(subs_epu16, uint16_t, uint16_t, _mm_subs_epu16(va, vb), LANES(uint16_t, sat_u16(x - y)))
TEST2(avg_epu16, uint16_t, uint16_t, _mm_avg_epu16(va, vb), LANES(uint16_t, (x + y + 1) >> 1))
TEST2(min_epi16, int16_t, int16_t, _mm_min_epi16(va, vb), LANES(int16_t, x < y ? x : y))
TEST2(max_epi16, int16_t, int16_t, _mm_max_epi16(va, vb), LANES(int16_t, x > y ? x : y))
TEST2(mullo_epi16, uint16_t, uint16_t, _mm_mullo_epi16(va, vb),
      LANES(uint16_t, (uint32_t)x * (uint32_t)y))
TEST2(mulhi_epi16, int16_t, int16_t, _mm_mulhi_epi16(va, vb),
      LANES(int16_t, ((int32_t)x * (int32_t)y) >> 16))
TEST2(mulhi_epu16, uint16_t, uint16_t, _mm_mulhi_epu16(va, vb),
      LANES(uint16_t, ((uint32_t)x * (uint32_t)y) >> 16))
TEST2(cmpeq_epi16, int16_t, int16_t, _mm_cmpeq_epi16(va, vb), LANES(int16_t, x == y ? -1 : 0))
TEST2(cmpgt_epi16, int16_t, int16_t, _mm_cmpgt_epi16(va, vb), LANES(int16_t, x > y ? -1 : 0))
TEST2(cmplt_epi16, int16_t, int16_t, _mm_cmplt_epi16(va, vb), LANES(int16_t, x < y ? -1 : 0))

/* Thirty two and sixty four bit lanes. */
TEST2(add_epi32, uint32_t, uint32_t, _mm_add_epi32(va, vb), LANES(uint32_t, x + y))
TEST2(sub_epi32, uint32_t, uint32_t, _mm_sub_epi32(va, vb), LANES(uint32_t, x - y))
TEST2(cmpeq_epi32, int32_t, int32_t, _mm_cmpeq_epi32(va, vb), LANES(int32_t, x == y ? -1 : 0))
TEST2(cmpgt_epi32, int32_t, int32_t, _mm_cmpgt_epi32(va, vb), LANES(int32_t, x > y ? -1 : 0))
TEST2(cmplt_epi32, int32_t, int32_t, _mm_cmplt_epi32(va, vb), LANES(int32_t, x < y ? -1 : 0))
TEST2(add_epi64, uint64_t, uint64_t, _mm_add_epi64(va, vb), LANES(uint64_t, x + y))
TEST2(sub_epi64, uint64_t, uint64_t, _mm_sub_epi64(va, vb), LANES(uint64_t, x - y))

/* The whole register as bits. */
TEST2(and_si128, uint64_t, uint64_t, _mm_and_si128(va, vb), LANES(uint64_t, x & y))
TEST2(or_si128, uint64_t, uint64_t, _mm_or_si128(va, vb), LANES(uint64_t, x | y))
TEST2(xor_si128, uint64_t, uint64_t, _mm_xor_si128(va, vb), LANES(uint64_t, x ^ y))
TEST2(andnot_si128, uint64_t, uint64_t, _mm_andnot_si128(va, vb), LANES(uint64_t, ~x & y))

/* The ones whose result is not lane for lane. */
TEST2(madd_epi16, int16_t, uint32_t, _mm_madd_epi16(va, vb),
      for (int i = 0; i < 4; i++) want[i] =
          (uint32_t)((int64_t)a[2 * i] * b[2 * i] + (int64_t)a[2 * i + 1] * b[2 * i + 1]))
TEST2(sad_epu8, uint8_t, uint64_t, _mm_sad_epu8(va, vb),
      for (int i = 0; i < 16; i++) want[i / 8] += (uint64_t)(a[i] > b[i] ? a[i] - b[i] : b[i] - a[i]))
TEST2(mul_epu32, uint32_t, uint64_t, _mm_mul_epu32(va, vb),
      for (int i = 0; i < 2; i++) want[i] = (uint64_t)a[2 * i] * b[2 * i])
TEST2(packs_epi16, int16_t, int8_t, _mm_packs_epi16(va, vb),
      for (int i = 0; i < 8; i++) { want[i] = (int8_t)sat_i8(a[i]); want[8 + i] = (int8_t)sat_i8(b[i]); })
TEST2(packs_epi32, int32_t, int16_t, _mm_packs_epi32(va, vb),
      for (int i = 0; i < 4; i++) {
          want[i] = (int16_t)(a[i] < -32768 ? -32768 : a[i] > 32767 ? 32767 : a[i]);
          want[4 + i] = (int16_t)(b[i] < -32768 ? -32768 : b[i] > 32767 ? 32767 : b[i]);
      })
TEST2(packus_epi16, int16_t, uint8_t, _mm_packus_epi16(va, vb),
      for (int i = 0; i < 8; i++) { want[i] = (uint8_t)sat_u8(a[i]); want[8 + i] = (uint8_t)sat_u8(b[i]); })

#define UNPACK(NAME, T, HALF)                                                                    \
    TEST2(NAME, T, T, _mm_##NAME(va, vb), for (int i = 0; i < N(T) / 2; i++) {                   \
        want[2 * i] = a[HALF + i];                                                               \
        want[2 * i + 1] = b[HALF + i];                                                           \
    })
UNPACK(unpacklo_epi8, uint8_t, 0)
UNPACK(unpackhi_epi8, uint8_t, 8)
UNPACK(unpacklo_epi16, uint16_t, 0)
UNPACK(unpackhi_epi16, uint16_t, 4)
UNPACK(unpacklo_epi32, uint32_t, 0)
UNPACK(unpackhi_epi32, uint32_t, 2)
UNPACK(unpacklo_epi64, uint64_t, 0)
UNPACK(unpackhi_epi64, uint64_t, 1)

/* Shuffles, at a few immediates each. */
#define SHUF32(IMM)                                                                              \
    TEST1(shuffle_epi32_##IMM, uint32_t, uint32_t, _mm_shuffle_epi32(va, IMM),                   \
          for (int i = 0; i < 4; i++) want[i] = a[(IMM >> (2 * i)) & 3])
SHUF32(0x00)
SHUF32(0x1b)
SHUF32(0x4e)
SHUF32(0xd8)
#define SHUFLO(IMM)                                                                              \
    TEST1(shufflelo_epi16_##IMM, uint16_t, uint16_t, _mm_shufflelo_epi16(va, IMM),               \
          for (int i = 0; i < 4; i++) { want[i] = a[(IMM >> (2 * i)) & 3]; want[4 + i] = a[4 + i]; })
#define SHUFHI(IMM)                                                                              \
    TEST1(shufflehi_epi16_##IMM, uint16_t, uint16_t, _mm_shufflehi_epi16(va, IMM),               \
          for (int i = 0; i < 4; i++) { want[i] = a[i]; want[4 + i] = a[4 + ((IMM >> (2 * i)) & 3)]; })
SHUFLO(0x1b)
SHUFLO(0xb1)
SHUFHI(0x1b)
SHUFHI(0xb1)

/* Shifts by an immediate, including the counts at and past the lane width, where a logical shift
 * gives zero and an arithmetic one gives the sign. C cannot shift by the width, so the reference
 * says what the instruction does there in so many words. */
#define SHIFTS(W, T, S, C)                                                                       \
    TEST1(slli_epi##W##_##C, T, T, _mm_slli_epi##W(va, C), LANES1(T, C >= W ? 0 : (T)(x << C % W)))  \
    TEST1(srli_epi##W##_##C, T, T, _mm_srli_epi##W(va, C), LANES1(T, C >= W ? 0 : (T)(x >> C % W)))
#define SRAI(W, S, C)                                                                            \
    TEST1(srai_epi##W##_##C, S, S, _mm_srai_epi##W(va, C),                                      \
          LANES1(S, C >= W ? (x < 0 ? -1 : 0) : (x >> (C % W))))
SHIFTS(16, uint16_t, int16_t, 0)
SHIFTS(16, uint16_t, int16_t, 1)
SHIFTS(16, uint16_t, int16_t, 15)
SHIFTS(16, uint16_t, int16_t, 16)
SHIFTS(32, uint32_t, int32_t, 1)
SHIFTS(32, uint32_t, int32_t, 31)
SHIFTS(32, uint32_t, int32_t, 32)
SHIFTS(64, uint64_t, int64_t, 1)
SHIFTS(64, uint64_t, int64_t, 63)
SHIFTS(64, uint64_t, int64_t, 64)
SRAI(16, int16_t, 3)
SRAI(16, int16_t, 15)
SRAI(16, int16_t, 16)
SRAI(32, int32_t, 7)
SRAI(32, int32_t, 31)
SRAI(32, int32_t, 40)

/* Shifts by a count held in the low quadword of a second vector. */
static void t_shift_by_vector(void)
{
    static const int counts[] = {0, 1, 5, 15, 16, 31, 32, 63, 64, 200};
    int bad = 0;
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS / 10; r++) {
        for (unsigned k = 0; k < sizeof counts / sizeof counts[0]; k++) {
            int c = counts[k];
            uint16_t a16[8], w16[8], g16[8];
            int16_t s16[8], ws16[8], gs16[8];
            uint32_t a32[4], w32[4], g32[4];
            int32_t s32[4], ws32[4], gs32[4];
            uint64_t a64[2], w64[2], g64[2];
            __m128i count = _mm_cvtsi32_si128(c);
            __m128i v;
            fill(a16, 16, r);
            memcpy(s16, a16, 16);
            memcpy(a32, a16, 16);
            memcpy(s32, a16, 16);
            memcpy(a64, a16, 16);
            memcpy(&v, a16, 16);
            for (int i = 0; i < 8; i++) {
                w16[i] = c >= 16 ? 0 : (uint16_t)(a16[i] << c);
                ws16[i] = c >= 16 ? (s16[i] < 0 ? -1 : 0) : (int16_t)(s16[i] >> c);
            }
            for (int i = 0; i < 4; i++) {
                w32[i] = c >= 32 ? 0 : a32[i] >> c;
                ws32[i] = c >= 32 ? (s32[i] < 0 ? -1 : 0) : s32[i] >> c;
            }
            for (int i = 0; i < 2; i++)
                w64[i] = c >= 64 ? 0 : a64[i] << c;
            __m128i r16 = _mm_sll_epi16(v, count);
            __m128i rs16 = _mm_sra_epi16(v, count);
            __m128i r32 = _mm_srl_epi32(v, count);
            __m128i rs32 = _mm_sra_epi32(v, count);
            __m128i r64 = _mm_sll_epi64(v, count);
            memcpy(g16, &r16, 16);
            memcpy(gs16, &rs16, 16);
            memcpy(g32, &r32, 16);
            memcpy(gs32, &rs32, 16);
            memcpy(g64, &r64, 16);
            judge(&bad, &sum, a16, NULL, 16, g16, w16, 16);
            judge(&bad, &sum, a16, NULL, 16, gs16, ws16, 16);
            judge(&bad, &sum, a16, NULL, 16, g32, w32, 16);
            judge(&bad, &sum, a16, NULL, 16, gs32, ws32, 16);
            judge(&bad, &sum, a16, NULL, 16, g64, w64, 16);
        }
    }
    report("sll_sra_srl_by_vector", bad, sum);
}

/* Byte shifts of the whole register. */
#define BYTESHIFT(C)                                                                             \
    TEST1(slli_si128_##C, uint8_t, uint8_t, _mm_slli_si128(va, C),                              \
          for (int i = 0; i < 16; i++) want[i] = i >= C ? a[i - C] : 0)                          \
    TEST1(srli_si128_##C, uint8_t, uint8_t, _mm_srli_si128(va, C),                              \
          for (int i = 0; i < 16; i++) want[i] = i + C < 16 ? a[i + C] : 0)
BYTESHIFT(0)
BYTESHIFT(1)
BYTESHIFT(5)
BYTESHIFT(8)
BYTESHIFT(15)
BYTESHIFT(16)

/* Getting values in and out of a register, and building one from scalars. */
static void t_moves(void)
{
    int bad = 0;
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        uint8_t buf[48];
        uint8_t got[16], want[16];
        __attribute__((aligned(16))) uint8_t aligned[16];
        __m128i v;
        fill(buf, sizeof buf, r);

        v = _mm_loadu_si128((const __m128i *)(buf + 1));
        memcpy(got, &v, 16);
        judge(&bad, &sum, buf + 1, NULL, 16, got, buf + 1, 16);

        _mm_storeu_si128((__m128i *)(buf + 19), v);
        judge(&bad, &sum, buf + 1, NULL, 16, buf + 19, got, 16);

        memcpy(aligned, buf + 3, 16);
        v = _mm_load_si128((const __m128i *)aligned);
        memcpy(got, &v, 16);
        judge(&bad, &sum, aligned, NULL, 16, got, aligned, 16);
        memset(aligned, 0, 16);
        _mm_store_si128((__m128i *)aligned, v);
        judge(&bad, &sum, buf + 3, NULL, 16, aligned, buf + 3, 16);

        v = _mm_loadl_epi64((const __m128i *)(buf + 5));
        memcpy(got, &v, 16);
        memcpy(want, buf + 5, 8);
        memset(want + 8, 0, 8);
        judge(&bad, &sum, buf + 5, NULL, 8, got, want, 16);

        memcpy(want, buf + 32, 16);
        _mm_storel_epi64((__m128i *)(buf + 32), v);
        memcpy(want, buf + 5, 8);
        judge(&bad, &sum, buf + 5, NULL, 8, buf + 32, want, 16);

        memcpy(&v, buf, 16);
        v = _mm_move_epi64(v);
        memcpy(got, &v, 16);
        memcpy(want, buf, 8);
        memset(want + 8, 0, 8);
        judge(&bad, &sum, buf, NULL, 16, got, want, 16);

        int32_t i32;
        int64_t i64;
        memcpy(&i32, buf + 7, 4);
        memcpy(&i64, buf + 11, 8);
        v = _mm_cvtsi32_si128(i32);
        memcpy(got, &v, 16);
        memset(want, 0, 16);
        memcpy(want, &i32, 4);
        judge(&bad, &sum, &i32, NULL, 4, got, want, 16);
        int32_t back32 = _mm_cvtsi128_si32(v);
        judge(&bad, &sum, &i32, NULL, 4, &back32, &i32, 4);

        v = _mm_cvtsi64_si128(i64);
        memcpy(got, &v, 16);
        memset(want, 0, 16);
        memcpy(want, &i64, 8);
        judge(&bad, &sum, &i64, NULL, 8, got, want, 16);
        int64_t back64 = _mm_cvtsi128_si64(v);
        judge(&bad, &sum, &i64, NULL, 8, &back64, &i64, 8);

        v = _mm_setzero_si128();
        memcpy(got, &v, 16);
        memset(want, 0, 16);
        judge(&bad, &sum, want, NULL, 16, got, want, 16);
    }
    report("loads_stores_and_moves", bad, sum);
}

static void t_sets(void)
{
    int bad = 0;
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        uint8_t b[16];
        uint16_t h[8];
        uint32_t w[4];
        uint64_t q[2];
        uint8_t got[16];
        __m128i v;
        fill(b, 16, r);
        memcpy(h, b, 16);
        memcpy(w, b, 16);
        memcpy(q, b, 16);

        v = _mm_setr_epi8((char)b[0], (char)b[1], (char)b[2], (char)b[3], (char)b[4], (char)b[5],
                          (char)b[6], (char)b[7], (char)b[8], (char)b[9], (char)b[10],
                          (char)b[11], (char)b[12], (char)b[13], (char)b[14], (char)b[15]);
        memcpy(got, &v, 16);
        judge(&bad, &sum, b, NULL, 16, got, b, 16);
        v = _mm_set_epi8((char)b[15], (char)b[14], (char)b[13], (char)b[12], (char)b[11],
                         (char)b[10], (char)b[9], (char)b[8], (char)b[7], (char)b[6], (char)b[5],
                         (char)b[4], (char)b[3], (char)b[2], (char)b[1], (char)b[0]);
        memcpy(got, &v, 16);
        judge(&bad, &sum, b, NULL, 16, got, b, 16);
        v = _mm_setr_epi16((short)h[0], (short)h[1], (short)h[2], (short)h[3], (short)h[4],
                           (short)h[5], (short)h[6], (short)h[7]);
        memcpy(got, &v, 16);
        judge(&bad, &sum, b, NULL, 16, got, b, 16);
        v = _mm_set_epi16((short)h[7], (short)h[6], (short)h[5], (short)h[4], (short)h[3],
                          (short)h[2], (short)h[1], (short)h[0]);
        memcpy(got, &v, 16);
        judge(&bad, &sum, b, NULL, 16, got, b, 16);
        v = _mm_setr_epi32((int)w[0], (int)w[1], (int)w[2], (int)w[3]);
        memcpy(got, &v, 16);
        judge(&bad, &sum, b, NULL, 16, got, b, 16);
        v = _mm_set_epi32((int)w[3], (int)w[2], (int)w[1], (int)w[0]);
        memcpy(got, &v, 16);
        judge(&bad, &sum, b, NULL, 16, got, b, 16);
        v = _mm_set_epi64x((long long)q[1], (long long)q[0]);
        memcpy(got, &v, 16);
        judge(&bad, &sum, b, NULL, 16, got, b, 16);

        uint8_t want[16];
        v = _mm_set1_epi8((char)b[3]);
        memcpy(got, &v, 16);
        memset(want, b[3], 16);
        judge(&bad, &sum, b + 3, NULL, 1, got, want, 16);
        v = _mm_set1_epi16((short)h[2]);
        memcpy(got, &v, 16);
        for (int i = 0; i < 8; i++)
            memcpy(want + 2 * i, &h[2], 2);
        judge(&bad, &sum, &h[2], NULL, 2, got, want, 16);
        v = _mm_set1_epi32((int)w[1]);
        memcpy(got, &v, 16);
        for (int i = 0; i < 4; i++)
            memcpy(want + 4 * i, &w[1], 4);
        judge(&bad, &sum, &w[1], NULL, 4, got, want, 16);
        v = _mm_set1_epi64x((long long)q[1]);
        memcpy(got, &v, 16);
        memcpy(want, &q[1], 8);
        memcpy(want + 8, &q[1], 8);
        judge(&bad, &sum, &q[1], NULL, 8, got, want, 16);
    }
    report("set_setr_set1", bad, sum);
}

static void t_lanes(void)
{
    int bad = 0;
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        uint16_t h[8], want[8], got[8];
        uint8_t b[16];
        __m128i v;
        fill(h, 16, r);
        memcpy(b, h, 16);
        memcpy(&v, h, 16);

        int e0 = _mm_extract_epi16(v, 0);
        int e3 = _mm_extract_epi16(v, 3);
        int e7 = _mm_extract_epi16(v, 7);
        int we[3] = {h[0], h[3], h[7]};
        int ge[3] = {e0, e3, e7};
        judge(&bad, &sum, h, NULL, 16, ge, we, sizeof ge);

        __m128i ins = _mm_insert_epi16(v, (int)(h[1] ^ 0xa5a5), 5);
        memcpy(got, &ins, 16);
        memcpy(want, h, 16);
        want[5] = (uint16_t)(h[1] ^ 0xa5a5);
        judge(&bad, &sum, h, NULL, 16, got, want, 16);

        int mask = _mm_movemask_epi8(v);
        int wmask = 0;
        for (int i = 0; i < 16; i++)
            wmask |= (b[i] >> 7) << i;
        judge(&bad, &sum, b, NULL, 16, &mask, &wmask, sizeof mask);
    }
    report("extract_insert_movemask", bad, sum);
}

int main(void)
{
    t_add_epi8();
    t_sub_epi8();
    t_adds_epi8();
    t_subs_epi8();
    t_adds_epu8();
    t_subs_epu8();
    t_avg_epu8();
    t_min_epu8();
    t_max_epu8();
    t_cmpeq_epi8();
    t_cmpgt_epi8();
    t_cmplt_epi8();
    t_add_epi16();
    t_sub_epi16();
    t_adds_epi16();
    t_subs_epi16();
    t_adds_epu16();
    t_subs_epu16();
    t_avg_epu16();
    t_min_epi16();
    t_max_epi16();
    t_mullo_epi16();
    t_mulhi_epi16();
    t_mulhi_epu16();
    t_cmpeq_epi16();
    t_cmpgt_epi16();
    t_cmplt_epi16();
    t_add_epi32();
    t_sub_epi32();
    t_cmpeq_epi32();
    t_cmpgt_epi32();
    t_cmplt_epi32();
    t_add_epi64();
    t_sub_epi64();
    t_and_si128();
    t_or_si128();
    t_xor_si128();
    t_andnot_si128();
    t_madd_epi16();
    t_sad_epu8();
    t_mul_epu32();
    t_packs_epi16();
    t_packs_epi32();
    t_packus_epi16();
    t_unpacklo_epi8();
    t_unpackhi_epi8();
    t_unpacklo_epi16();
    t_unpackhi_epi16();
    t_unpacklo_epi32();
    t_unpackhi_epi32();
    t_unpacklo_epi64();
    t_unpackhi_epi64();
    t_shuffle_epi32_0x00();
    t_shuffle_epi32_0x1b();
    t_shuffle_epi32_0x4e();
    t_shuffle_epi32_0xd8();
    t_shufflelo_epi16_0x1b();
    t_shufflelo_epi16_0xb1();
    t_shufflehi_epi16_0x1b();
    t_shufflehi_epi16_0xb1();
    t_slli_epi16_0();
    t_srli_epi16_0();
    t_slli_epi16_1();
    t_srli_epi16_1();
    t_slli_epi16_15();
    t_srli_epi16_15();
    t_slli_epi16_16();
    t_srli_epi16_16();
    t_slli_epi32_1();
    t_srli_epi32_1();
    t_slli_epi32_31();
    t_srli_epi32_31();
    t_slli_epi32_32();
    t_srli_epi32_32();
    t_slli_epi64_1();
    t_srli_epi64_1();
    t_slli_epi64_63();
    t_srli_epi64_63();
    t_slli_epi64_64();
    t_srli_epi64_64();
    t_srai_epi16_3();
    t_srai_epi16_15();
    t_srai_epi16_16();
    t_srai_epi32_7();
    t_srai_epi32_31();
    t_srai_epi32_40();
    t_shift_by_vector();
    t_slli_si128_0();
    t_srli_si128_0();
    t_slli_si128_1();
    t_srli_si128_1();
    t_slli_si128_5();
    t_srli_si128_5();
    t_slli_si128_8();
    t_srli_si128_8();
    t_slli_si128_15();
    t_srli_si128_15();
    t_slli_si128_16();
    t_srli_si128_16();
    t_moves();
    t_sets();
    t_lanes();
    DONE();
}
