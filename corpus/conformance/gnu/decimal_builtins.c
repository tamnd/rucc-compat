/* The decimal floating builtins, which GCC has on the targets with decimal floating types. */
#include <stdio.h>

int main(void)
{
    _Decimal32 i32 = __builtin_infd32(), n32 = __builtin_nand32(""), s32 = __builtin_nansd32("");
    _Decimal64 i64 = __builtin_infd64(), n64 = __builtin_nand64(""), s64 = __builtin_nansd64("");
    _Decimal128 i128 = __builtin_infd128(), n128 = __builtin_nand128(""), s128 = __builtin_nansd128("");
    printf("isnan %d %d %d %d %d %d\n", __builtin_isnand32(n32) != 0, __builtin_isnand64(n64) != 0, __builtin_isnand128(n128) != 0, __builtin_isnand32(s32) != 0, __builtin_isnand64(s64) != 0, __builtin_isnand128(s128) != 0);
    printf("isinf %d %d %d\n", __builtin_isinfd32(i32) != 0, __builtin_isinfd64(i64) != 0, __builtin_isinfd128(i128) != 0);
    printf("finite %d %d %d\n", __builtin_finited32(1.5DF) != 0, __builtin_finited64(1.0DD) != 0, __builtin_finited128(2.5DL) != 0);
    printf("signbit %d %d %d\n", __builtin_signbitd32(-1.0DF) != 0, __builtin_signbitd64(1.0DD) != 0, __builtin_signbitd128(-0.0DL) != 0);
    return 0;
}
