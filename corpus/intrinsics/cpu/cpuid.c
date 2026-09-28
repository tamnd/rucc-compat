/* cpuid.h: __get_cpuid_max, __get_cpuid, __get_cpuid_count, __cpuidex and the two macros, each
 * against the instruction run directly, and the bit_ names against the values gcc gives them.
 *
 * Postgres calls __get_cpuid from its CRC32C and popcount choosers and __get_cpuid_count for the
 * AVX-512 check, and a configure probe for each decides whether the fast path is built at all.
 * What the processor answers is the same for both builds, since they run on the same machine, so
 * the printed feature bits are compared against the reference as well. The APIC id in leaf 1 is
 * masked, because it says which core the program ran on. */
#include <cpuid.h>

#include "../check.h"

static void raw(unsigned leaf, unsigned sub, unsigned r[4])
{
    __asm__ __volatile__("cpuid" : "=a"(r[0]), "=b"(r[1]), "=c"(r[2]), "=d"(r[3]) : "a"(leaf), "c"(sub));
}

static void mask_apic(unsigned leaf, unsigned r[4])
{
    if (leaf == 1)
        r[1] &= 0x00ffffffu;
}

static void same(const char *what, unsigned leaf, const unsigned got[4], const unsigned want[4])
{
    unsigned g[4], w[4];
    memcpy(g, got, sizeof g);
    memcpy(w, want, sizeof w);
    mask_apic(leaf, g);
    mask_apic(leaf, w);
    if (memcmp(g, w, sizeof g) != 0) {
        printf("FAIL %s leaf %#x: got %08x %08x %08x %08x, want %08x %08x %08x %08x\n", what, leaf,
               g[0], g[1], g[2], g[3], w[0], w[1], w[2], w[3]);
        failures++;
    }
}

int main(void)
{
    unsigned want[4], got[4];
    unsigned sig = 0;

    raw(0, 0, want);
    unsigned max = __get_cpuid_max(0, &sig);
    if (max != want[0] || sig != want[1]) {
        printf("FAIL __get_cpuid_max(0): %#x %#x, want %#x %#x\n", max, sig, want[0], want[1]);
        failures++;
    }
    raw(0x80000000u, 0, want);
    unsigned emax = __get_cpuid_max(0x80000000u, NULL);
    if (emax != want[0]) {
        printf("FAIL __get_cpuid_max(0x80000000): %#x, want %#x\n", emax, want[0]);
        failures++;
    }

    char vendor[13];
    raw(0, 0, want);
    memcpy(vendor, &want[1], 4);
    memcpy(vendor + 4, &want[3], 4);
    memcpy(vendor + 8, &want[2], 4);
    vendor[12] = 0;
    printf("vendor %s\n", vendor);

    static const unsigned leaves[] = {0, 1, 7, 0xd, 0x80000000u, 0x80000001u};
    for (unsigned k = 0; k < sizeof leaves / sizeof leaves[0]; k++) {
        unsigned leaf = leaves[k];
        unsigned top = leaf & 0x80000000u ? emax : max;
        if (leaf > top)
            continue;
        /* __get_cpuid and __cpuid leave ecx as it was, so for leaves with subleaves, such as 7 and
         * 0xd, what they return depends on whatever ecx held. Only compare the leaves without. */
        int ok;
        if (leaf != 7 && leaf != 0xd) {
            raw(leaf, 0, want);
            memset(got, 0, sizeof got);
            ok = __get_cpuid(leaf, &got[0], &got[1], &got[2], &got[3]);
            if (!ok) {
                printf("FAIL __get_cpuid(%#x) said the leaf is not there\n", leaf);
                failures++;
            }
            same("__get_cpuid", leaf, got, want);

            memset(got, 0, sizeof got);
            __cpuid(leaf, got[0], got[1], got[2], got[3]);
            same("__cpuid", leaf, got, want);
        }

        for (unsigned sub = 0; sub < 2; sub++) {
            raw(leaf, sub, want);
            memset(got, 0, sizeof got);
            ok = __get_cpuid_count(leaf, sub, &got[0], &got[1], &got[2], &got[3]);
            if (!ok) {
                printf("FAIL __get_cpuid_count(%#x, %u) said the leaf is not there\n", leaf, sub);
                failures++;
            }
            same("__get_cpuid_count", leaf, got, want);

            memset(got, 0, sizeof got);
            __cpuid_count(leaf, sub, got[0], got[1], got[2], got[3]);
            same("__cpuid_count", leaf, got, want);

            int info[4] = {0, 0, 0, 0};
            __cpuidex(info, (int)leaf, (int)sub);
            memcpy(got, info, sizeof got);
            same("__cpuidex", leaf, got, want);
        }
    }

    /* A leaf past the top has to be refused, and the outputs left alone. */
    got[0] = got[1] = got[2] = got[3] = 0xdeadbeefu;
    if (__get_cpuid(max + 1, &got[0], &got[1], &got[2], &got[3]) != 0 || got[0] != 0xdeadbeefu) {
        printf("FAIL __get_cpuid(max + 1) answered a leaf that is not there\n");
        failures++;
    }
    if (__get_cpuid_count(emax + 1, 0, &got[0], &got[1], &got[2], &got[3]) != 0 || got[0] != 0xdeadbeefu) {
        printf("FAIL __get_cpuid_count(emax + 1) answered a leaf that is not there\n");
        failures++;
    }

    /* What the processor has, as the bit_ names read it. Both builds run here, so both print the
     * same thing when the names have the values gcc gives them. */
    unsigned a = 0, b = 0, c = 0, d = 0;
    __get_cpuid(1, &a, &b, &c, &d);
    printf("leaf 1 ecx: sse3 %d pclmul %d ssse3 %d sse4.1 %d sse4.2 %d popcnt %d xsave %d osxsave %d avx %d\n",
           !!(c & bit_SSE3), !!(c & bit_PCLMUL), !!(c & bit_SSSE3), !!(c & bit_SSE4_1), !!(c & bit_SSE4_2),
           !!(c & bit_POPCNT), !!(c & bit_XSAVE), !!(c & bit_OSXSAVE), !!(c & bit_AVX));
    printf("leaf 1 edx: mmx %d sse %d sse2 %d cmov %d\n", !!(d & bit_MMX), !!(d & bit_SSE), !!(d & bit_SSE2),
           !!(d & bit_CMOV));
    if (max >= 7) {
        __get_cpuid_count(7, 0, &a, &b, &c, &d);
        printf("leaf 7 ebx: avx2 %d bmi %d bmi2 %d avx512f %d avx512bw %d avx512vl %d\n", !!(b & bit_AVX2),
               !!(b & bit_BMI), !!(b & bit_BMI2), !!(b & bit_AVX512F), !!(b & bit_AVX512BW), !!(b & bit_AVX512VL));
        printf("leaf 7 ecx: vpclmulqdq %d avx512vpopcntdq %d\n", !!(c & bit_VPCLMULQDQ), !!(c & bit_AVX512VPOPCNTDQ));
    }
    printf("bits %#x %#x %#x %#x %#x %#x %#x %#x\n", bit_SSE4_2, bit_POPCNT, bit_OSXSAVE, bit_AVX,
           bit_AVX2, bit_AVX512F, bit_AVX512BW, (unsigned)bit_AVX512VL);
    printf("ok cpuid\n");
    DONE();
}
