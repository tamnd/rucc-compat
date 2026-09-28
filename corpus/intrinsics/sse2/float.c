/* The SSE and SSE2 floating point intrinsics, four floats or two doubles at a time, each against
 * the same operation done on one lane at a time.
 *
 * The inputs are drawn from a pool that has the values floating point is usually got wrong on:
 * both zeros, both infinities, a quiet NaN, a denormal, halves that round to even, and values too
 * large for an int. The results are compared bit for bit, so a minimum that returns the wrong one
 * of two zeros, or a conversion that rounds a half the wrong way, is a failure. */
#include <emmintrin.h>
#include <limits.h>
#include <math.h>

#include "../check.h"

static float pick_f(void)
{
    static const float pool[] = {0.0f, -0.0f, 1.0f, -1.0f, 0.5f, 1.5f, 2.5f, -2.5f, 3.0e9f, -3.0e9f,
                                 1.0e-40f, INFINITY, -INFINITY, NAN, 2147483520.0f, -2147483648.0f};
    uint64_t r = next_random();
    if ((r & 3) == 0)
        return pool[(r >> 8) % (sizeof pool / sizeof pool[0])];
    return (float)(int32_t)(r >> 16) / (float)(1 << ((r >> 4) & 15));
}

static double pick_d(void)
{
    static const double pool[] = {0.0, -0.0, 1.0, -1.0, 0.5, 1.5, 2.5, -2.5, 3.0e9, -3.0e9, 1.0e19,
                                  -1.0e19, 4.9e-324, INFINITY, -INFINITY, NAN};
    uint64_t r = next_random();
    if ((r & 3) == 0)
        return pool[(r >> 8) % (sizeof pool / sizeof pool[0])];
    return (double)(int64_t)(r >> 8) / (double)(1u << ((r >> 4) & 31));
}

/* What cvtps2dq and cvttps2dq give: the rounded or truncated value when it fits, and the integer
 * indefinite value, INT_MIN, when it does not or is a NaN. */
static int32_t to_i32(double x, int truncate)
{
    if (isnan(x) || x >= 2147483648.0 || x < -2147483648.0)
        return INT32_MIN;
    return (int32_t)(truncate ? trunc(x) : nearbyint(x));
}

static int64_t to_i64(double x, int truncate)
{
    if (isnan(x) || x >= 9223372036854775808.0 || x < -9223372036854775808.0)
        return INT64_MIN;
    return (int64_t)(truncate ? trunc(x) : nearbyint(x));
}

static uint32_t mask32(int c) { return c ? 0xffffffffu : 0; }
static uint64_t mask64(int c) { return c ? ~(uint64_t)0 : 0; }

#define PS(NAME, CALL, REF)                                                                      \
    static void t_##NAME(void)                                                                   \
    {                                                                                            \
        int bad = 0;                                                                             \
        uint64_t sum = 0;                                                                        \
        for (int r = 0; r < ROUNDS; r++) {                                                       \
            float a[4], b[4];                                                                    \
            union { float f[4]; uint32_t u[4]; int32_t i[4]; double d[2]; } want, got;                              \
            __m128 va, vb;                                                                       \
            for (int i = 0; i < 4; i++) {                                                        \
                a[i] = pick_f();                                                                 \
                b[i] = pick_f();                                                                 \
            }                                                                                    \
            memcpy(&va, a, 16);                                                                  \
            memcpy(&vb, b, 16);                                                                  \
            (void)vb;                                                                            \
            memset(&want, 0, 16);                                                                \
            CALL;                                                                                \
            REF;                                                                                 \
            judge(&bad, &sum, a, b, 16, &got, &want, 16);                                        \
        }                                                                                        \
        report(#NAME, bad, sum);                                                                 \
    }

#define PD(NAME, CALL, REF)                                                                      \
    static void t_##NAME(void)                                                                   \
    {                                                                                            \
        int bad = 0;                                                                             \
        uint64_t sum = 0;                                                                        \
        for (int r = 0; r < ROUNDS; r++) {                                                       \
            double a[2], b[2];                                                                   \
            union { double d[2]; float f[4]; uint64_t u[2]; int64_t q[2]; int32_t i[4]; } want, got; \
            __m128d va, vb;                                                                      \
            for (int i = 0; i < 2; i++) {                                                        \
                a[i] = pick_d();                                                                 \
                b[i] = pick_d();                                                                 \
            }                                                                                    \
            memcpy(&va, a, 16);                                                                  \
            memcpy(&vb, b, 16);                                                                  \
            (void)vb;                                                                            \
            memset(&want, 0, 16);                                                                \
            CALL;                                                                                \
            REF;                                                                                 \
            judge(&bad, &sum, a, b, 16, &got, &want, 16);                                        \
        }                                                                                        \
        report(#NAME, bad, sum);                                                                 \
    }

#define STORE_PS(E) do { __m128 t_ = (E); memcpy(&got, &t_, 16); } while (0)
#define STORE_PD(E) do { __m128d t_ = (E); memcpy(&got, &t_, 16); } while (0)
#define STORE_I(E) do { __m128i t_ = (E); memcpy(&got, &t_, 16); } while (0)
#define EACH4(S) for (int i = 0; i < 4; i++) { float x = a[i]; float y = b[i]; (void)y; S; }
#define EACH2(S) for (int i = 0; i < 2; i++) { double x = a[i]; double y = b[i]; (void)y; S; }

/* Four floats. */
PS(add_ps, STORE_PS(_mm_add_ps(va, vb)), EACH4(want.f[i] = x + y))
PS(sub_ps, STORE_PS(_mm_sub_ps(va, vb)), EACH4(want.f[i] = x - y))
PS(mul_ps, STORE_PS(_mm_mul_ps(va, vb)), EACH4(want.f[i] = x * y))
PS(div_ps, STORE_PS(_mm_div_ps(va, vb)), EACH4(want.f[i] = x / y))
PS(min_ps, STORE_PS(_mm_min_ps(va, vb)), EACH4(want.f[i] = x < y ? x : y))
PS(max_ps, STORE_PS(_mm_max_ps(va, vb)), EACH4(want.f[i] = x > y ? x : y))
PS(add_ss, STORE_PS(_mm_add_ss(va, vb)), EACH4(want.f[i] = i == 0 ? x + y : x))
PS(mul_ss, STORE_PS(_mm_mul_ss(va, vb)), EACH4(want.f[i] = i == 0 ? x * y : x))
PS(min_ss, STORE_PS(_mm_min_ss(va, vb)), EACH4(want.f[i] = i == 0 ? (x < y ? x : y) : x))
PS(and_ps, STORE_PS(_mm_and_ps(va, vb)), EACH4(uint32_t p; uint32_t q; memcpy(&p, &x, 4); memcpy(&q, &y, 4); want.u[i] = p & q))
PS(or_ps, STORE_PS(_mm_or_ps(va, vb)), EACH4(uint32_t p; uint32_t q; memcpy(&p, &x, 4); memcpy(&q, &y, 4); want.u[i] = p | q))
PS(xor_ps, STORE_PS(_mm_xor_ps(va, vb)), EACH4(uint32_t p; uint32_t q; memcpy(&p, &x, 4); memcpy(&q, &y, 4); want.u[i] = p ^ q))
PS(andnot_ps, STORE_PS(_mm_andnot_ps(va, vb)), EACH4(uint32_t p; uint32_t q; memcpy(&p, &x, 4); memcpy(&q, &y, 4); want.u[i] = ~p & q))
PS(cmpeq_ps, STORE_PS(_mm_cmpeq_ps(va, vb)), EACH4(want.u[i] = mask32(x == y)))
PS(cmplt_ps, STORE_PS(_mm_cmplt_ps(va, vb)), EACH4(want.u[i] = mask32(x < y)))
PS(cmple_ps, STORE_PS(_mm_cmple_ps(va, vb)), EACH4(want.u[i] = mask32(x <= y)))
PS(cmpgt_ps, STORE_PS(_mm_cmpgt_ps(va, vb)), EACH4(want.u[i] = mask32(x > y)))
PS(cmpge_ps, STORE_PS(_mm_cmpge_ps(va, vb)), EACH4(want.u[i] = mask32(x >= y)))
PS(cmpneq_ps, STORE_PS(_mm_cmpneq_ps(va, vb)), EACH4(want.u[i] = mask32(!(x == y))))
PS(cmpnlt_ps, STORE_PS(_mm_cmpnlt_ps(va, vb)), EACH4(want.u[i] = mask32(!(x < y))))
PS(cmpnle_ps, STORE_PS(_mm_cmpnle_ps(va, vb)), EACH4(want.u[i] = mask32(!(x <= y))))
PS(cmpord_ps, STORE_PS(_mm_cmpord_ps(va, vb)), EACH4(want.u[i] = mask32(!isnan(x) && !isnan(y))))
PS(cmpunord_ps, STORE_PS(_mm_cmpunord_ps(va, vb)), EACH4(want.u[i] = mask32(isnan(x) || isnan(y))))
PS(unpacklo_ps, STORE_PS(_mm_unpacklo_ps(va, vb)), want.f[0] = a[0]; want.f[1] = b[0]; want.f[2] = a[1]; want.f[3] = b[1])
PS(unpackhi_ps, STORE_PS(_mm_unpackhi_ps(va, vb)), want.f[0] = a[2]; want.f[1] = b[2]; want.f[2] = a[3]; want.f[3] = b[3])
PS(movehl_ps, STORE_PS(_mm_movehl_ps(va, vb)), want.f[0] = b[2]; want.f[1] = b[3]; want.f[2] = a[2]; want.f[3] = a[3])
PS(movelh_ps, STORE_PS(_mm_movelh_ps(va, vb)), want.f[0] = a[0]; want.f[1] = a[1]; want.f[2] = b[0]; want.f[3] = b[1])
PS(shuffle_ps_1b, STORE_PS(_mm_shuffle_ps(va, vb, 0x1b)), want.f[0] = a[3]; want.f[1] = a[2]; want.f[2] = b[1]; want.f[3] = b[0])
PS(shuffle_ps_e4, STORE_PS(_mm_shuffle_ps(va, vb, 0xe4)), want.f[0] = a[0]; want.f[1] = a[1]; want.f[2] = b[2]; want.f[3] = b[3])
PS(movemask_ps, got.i[0] = _mm_movemask_ps(va); got.i[1] = got.i[2] = got.i[3] = 0,
   EACH4(uint32_t p; memcpy(&p, &x, 4); want.i[0] |= (int)(p >> 31) << i))
PS(cvtps_epi32, STORE_I(_mm_cvtps_epi32(va)), EACH4(want.i[i] = to_i32(x, 0)))
PS(cvttps_epi32, STORE_I(_mm_cvttps_epi32(va)), EACH4(want.i[i] = to_i32(x, 1)))
PS(cvtss_si32, got.i[0] = _mm_cvtss_si32(va); got.i[1] = _mm_cvttss_si32(va); got.i[2] = got.i[3] = 0,
   want.i[0] = to_i32(a[0], 0); want.i[1] = to_i32(a[0], 1))
PS(cvtss_si64, got.u[0] = 0; int64_t q_ = _mm_cvtss_si64(va); int64_t t_ = _mm_cvttss_si64(va); memcpy(&got, &q_, 8); memcpy(got.u + 2, &t_, 8),
   int64_t wq_ = to_i64(a[0], 0); int64_t wt_ = to_i64(a[0], 1); memcpy(&want, &wq_, 8); memcpy(want.u + 2, &wt_, 8))
PS(cvtps_pd, STORE_PD(_mm_cvtps_pd(va)), want.d[0] = a[0]; want.d[1] = a[1])
PS(cvtss_f32, got.f[0] = _mm_cvtss_f32(va); got.u[1] = got.u[2] = got.u[3] = 0, want.f[0] = a[0])
PS(set_ps, STORE_PS(_mm_set_ps(a[3], a[2], a[1], a[0])), memcpy(&want, a, 16))
PS(setr_ps, STORE_PS(_mm_setr_ps(a[0], a[1], a[2], a[3])), memcpy(&want, a, 16))
PS(set1_ps, STORE_PS(_mm_set1_ps(a[2])), for (int i = 0; i < 4; i++) want.f[i] = a[2])
PS(set_ss, STORE_PS(_mm_set_ss(a[1])), want.f[0] = a[1])
PS(loadu_storeu_ps, float buf_[6]; _mm_storeu_ps(buf_ + 1, _mm_loadu_ps(a)); memcpy(&got, buf_ + 1, 16), memcpy(&want, a, 16))
PS(cvtsi32_ss, int32_t n_ = (int32_t)next_random(); STORE_PS(_mm_cvtsi32_ss(va, n_)),
   memcpy(&want, a, 16); want.f[0] = (float)n_)

/* Two doubles. */
PD(add_pd, STORE_PD(_mm_add_pd(va, vb)), EACH2(want.d[i] = x + y))
PD(sub_pd, STORE_PD(_mm_sub_pd(va, vb)), EACH2(want.d[i] = x - y))
PD(mul_pd, STORE_PD(_mm_mul_pd(va, vb)), EACH2(want.d[i] = x * y))
PD(div_pd, STORE_PD(_mm_div_pd(va, vb)), EACH2(want.d[i] = x / y))
PD(min_pd, STORE_PD(_mm_min_pd(va, vb)), EACH2(want.d[i] = x < y ? x : y))
PD(max_pd, STORE_PD(_mm_max_pd(va, vb)), EACH2(want.d[i] = x > y ? x : y))
PD(add_sd, STORE_PD(_mm_add_sd(va, vb)), EACH2(want.d[i] = i == 0 ? x + y : x))
PD(and_pd, STORE_PD(_mm_and_pd(va, vb)), EACH2(uint64_t p; uint64_t q; memcpy(&p, &x, 8); memcpy(&q, &y, 8); want.u[i] = p & q))
PD(xor_pd, STORE_PD(_mm_xor_pd(va, vb)), EACH2(uint64_t p; uint64_t q; memcpy(&p, &x, 8); memcpy(&q, &y, 8); want.u[i] = p ^ q))
PD(andnot_pd, STORE_PD(_mm_andnot_pd(va, vb)), EACH2(uint64_t p; uint64_t q; memcpy(&p, &x, 8); memcpy(&q, &y, 8); want.u[i] = ~p & q))
PD(cmpeq_pd, STORE_PD(_mm_cmpeq_pd(va, vb)), EACH2(want.u[i] = mask64(x == y)))
PD(cmplt_pd, STORE_PD(_mm_cmplt_pd(va, vb)), EACH2(want.u[i] = mask64(x < y)))
PD(cmple_pd, STORE_PD(_mm_cmple_pd(va, vb)), EACH2(want.u[i] = mask64(x <= y)))
PD(cmpneq_pd, STORE_PD(_mm_cmpneq_pd(va, vb)), EACH2(want.u[i] = mask64(!(x == y))))
PD(cmpnge_pd, STORE_PD(_mm_cmpnge_pd(va, vb)), EACH2(want.u[i] = mask64(!(x >= y))))
PD(cmpunord_pd, STORE_PD(_mm_cmpunord_pd(va, vb)), EACH2(want.u[i] = mask64(isnan(x) || isnan(y))))
PD(unpacklo_pd, STORE_PD(_mm_unpacklo_pd(va, vb)), want.d[0] = a[0]; want.d[1] = b[0])
PD(unpackhi_pd, STORE_PD(_mm_unpackhi_pd(va, vb)), want.d[0] = a[1]; want.d[1] = b[1])
PD(shuffle_pd_1, STORE_PD(_mm_shuffle_pd(va, vb, 1)), want.d[0] = a[1]; want.d[1] = b[0])
PD(movemask_pd, got.q[0] = _mm_movemask_pd(va); got.q[1] = 0,
   EACH2(uint64_t p; memcpy(&p, &x, 8); want.q[0] |= (int64_t)(p >> 63) << i))
PD(cvtpd_epi32, STORE_I(_mm_cvtpd_epi32(va)), EACH2(want.i[i] = to_i32(x, 0)))
PD(cvttpd_epi32, STORE_I(_mm_cvttpd_epi32(va)), EACH2(want.i[i] = to_i32(x, 1)))
PD(cvtpd_ps, STORE_PS(_mm_cvtpd_ps(va)), EACH2(want.f[i] = (float)x))
PD(cvtsd_si64, int64_t q_ = _mm_cvtsd_si64(va); int64_t t_ = _mm_cvttsd_si64(va); memcpy(&got, &q_, 8); memcpy(got.u + 1, &t_, 8),
   want.q[0] = to_i64(a[0], 0); want.q[1] = to_i64(a[0], 1))
PD(cvtsd_si32, got.i[0] = _mm_cvtsd_si32(va); got.i[1] = _mm_cvttsd_si32(va); got.i[2] = got.i[3] = 0,
   want.i[0] = to_i32(a[0], 0); want.i[1] = to_i32(a[0], 1))
PD(cvtsi64_sd, int64_t n_ = (int64_t)next_random(); STORE_PD(_mm_cvtsi64_sd(va, n_)), want.d[0] = (double)n_; want.d[1] = a[1])
PD(set_pd, STORE_PD(_mm_set_pd(a[1], a[0])), memcpy(&want, a, 16))
PD(set1_pd, STORE_PD(_mm_set1_pd(a[1])), want.d[0] = want.d[1] = a[1])
PD(loadu_storeu_pd, double buf_[3]; _mm_storeu_pd(buf_ + 1, _mm_loadu_pd(a)); memcpy(&got, buf_ + 1, 16), memcpy(&want, a, 16))

/* The integer to floating conversions, which take their input as integers. */
static void t_cvtepi32(void)
{
    int bad = 0;
    uint64_t sum = 0;
    for (int r = 0; r < ROUNDS; r++) {
        int32_t a[4];
        float wf[4], gf[4];
        double wd[2], gd[2];
        __m128i v;
        fill(a, 16, r);
        memcpy(&v, a, 16);
        for (int i = 0; i < 4; i++)
            wf[i] = (float)a[i];
        for (int i = 0; i < 2; i++)
            wd[i] = (double)a[i];
        __m128 f = _mm_cvtepi32_ps(v);
        __m128d d = _mm_cvtepi32_pd(v);
        memcpy(gf, &f, 16);
        memcpy(gd, &d, 16);
        judge(&bad, &sum, a, NULL, 16, gf, wf, 16);
        judge(&bad, &sum, a, NULL, 16, gd, wd, 16);
    }
    report("cvtepi32_ps_pd", bad, sum);
}

int main(void)
{
    t_add_ps(); t_sub_ps(); t_mul_ps(); t_div_ps(); t_min_ps(); t_max_ps();
    t_add_ss(); t_mul_ss(); t_min_ss();
    t_and_ps(); t_or_ps(); t_xor_ps(); t_andnot_ps();
    t_cmpeq_ps(); t_cmplt_ps(); t_cmple_ps(); t_cmpgt_ps(); t_cmpge_ps(); t_cmpneq_ps();
    t_cmpnlt_ps(); t_cmpnle_ps(); t_cmpord_ps(); t_cmpunord_ps();
    t_unpacklo_ps(); t_unpackhi_ps(); t_movehl_ps(); t_movelh_ps(); t_shuffle_ps_1b(); t_shuffle_ps_e4();
    t_movemask_ps(); t_cvtps_epi32(); t_cvttps_epi32(); t_cvtss_si32(); t_cvtss_si64(); t_cvtps_pd();
    t_cvtss_f32(); t_set_ps(); t_setr_ps(); t_set1_ps(); t_set_ss(); t_loadu_storeu_ps(); t_cvtsi32_ss();
    t_add_pd(); t_sub_pd(); t_mul_pd(); t_div_pd(); t_min_pd(); t_max_pd(); t_add_sd();
    t_and_pd(); t_xor_pd(); t_andnot_pd();
    t_cmpeq_pd(); t_cmplt_pd(); t_cmple_pd(); t_cmpneq_pd(); t_cmpnge_pd(); t_cmpunord_pd();
    t_unpacklo_pd(); t_unpackhi_pd(); t_shuffle_pd_1(); t_movemask_pd();
    t_cvtpd_epi32(); t_cvttpd_epi32(); t_cvtpd_ps(); t_cvtsd_si64(); t_cvtsd_si32(); t_cvtsi64_sd();
    t_set_pd(); t_set1_pd(); t_loadu_storeu_pd();
    t_cvtepi32();
    DONE();
}
