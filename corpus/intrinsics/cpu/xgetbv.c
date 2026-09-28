/* _xgetbv, which Postgres calls from a function built with __attribute__((target("xsave"))) to
 * learn whether the operating system saves the AVX-512 registers before it chooses the AVX-512
 * CRC32C and popcount. It is checked against the instruction run directly, and only when leaf 1
 * of cpuid says the operating system has turned XSAVE on, since xgetbv faults otherwise. */
#include <cpuid.h>
#include <immintrin.h>

#include "../check.h"

static unsigned long long raw(unsigned which)
{
    unsigned lo, hi;
    __asm__ __volatile__("xgetbv" : "=a"(lo), "=d"(hi) : "c"(which));
    return ((unsigned long long)hi << 32) | lo;
}

/* Postgres's zmm_regs_available, from src/port/pg_crc32c_sse42_choose.c. */
__attribute__((target("xsave"))) static int zmm_regs_available(void)
{
    return (_xgetbv(0) & 0xe6) == 0xe6;
}

__attribute__((target("xsave"))) static unsigned long long read_xcr0(void)
{
    return _xgetbv(0);
}

int main(void)
{
    unsigned a, b, c, d;
    if (!__get_cpuid(1, &a, &b, &c, &d) || !(c & bit_OSXSAVE)) {
        printf("no osxsave, nothing to check\n");
        return 0;
    }
    unsigned long long want = raw(0);
    unsigned long long got = read_xcr0();
    if (got != want) {
        printf("FAIL _xgetbv(0) is %#llx, want %#llx\n", got, want);
        failures++;
    }
    int zmm = zmm_regs_available();
    if (zmm != ((want & 0xe6) == 0xe6)) {
        printf("FAIL zmm_regs_available is %d\n", zmm);
        failures++;
    }
    printf("xcr0 x87 %d sse %d avx %d zmm %d\n", (int)(want & 1), (int)(want >> 1 & 1), (int)(want >> 2 & 1), zmm);
    printf("ok _xgetbv\n");
    DONE();
}
