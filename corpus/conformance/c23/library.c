// C23 library: checked integer arithmetic from <stdckdint.h>, the bit utilities of <stdbit.h>,
// memccpy, strdup and strndup, and the width macros of <limits.h> and <stdint.h>.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include <stdckdint.h>
#include <stdbit.h>

int main(void)
{
    int r;
    bool over = ckd_add(&r, INT_MAX, 1);
    printf("%d %d\n", over, r);
    over = ckd_mul(&r, 1000, 1000);
    printf("%d %d\n", over, r);
    unsigned char small;
    over = ckd_sub(&small, 0, 1);
    printf("%d %d\n", over, small);
    printf("%u %u %u\n", stdc_count_ones(0xF0u), stdc_leading_zeros(1u), stdc_trailing_zeros(8u));
    printf("%d %u\n", stdc_has_single_bit(64u), stdc_bit_width(255u));
    char out[8] = { 0 };
    char *end = memccpy(out, "ab:cd", ':', sizeof out);
    printf("%s %d\n", out, (int)(end - out));
    char *copy = strdup("dup");
    char *part = strndup("partial", 4);
    printf("%s %s\n", copy, part);
    free(copy);
    free(part);
    printf("%d %d %d\n", INT_WIDTH, LLONG_WIDTH, UINT64_WIDTH);
    return 0;
}
