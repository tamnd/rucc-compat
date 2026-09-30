/* __builtin_apply_args and __builtin_apply forward a call without knowing its arguments, and
   __builtin_va_arg_pack forwards the anonymous ones of an always-inline variadic wrapper. */
#include <stdio.h>

static int last_sum;
static void plus(int a, int b) { last_sum = a + b; }

static void forward(int a, int b)
{
    void *args = __builtin_apply_args();
    __builtin_apply((void (*)())plus, args, 64);
    (void)a;
    (void)b;
}

extern inline __attribute__((gnu_inline, always_inline)) int wrapped(const char *format, ...)
{
    if (__builtin_va_arg_pack_len() > 2)
        return -1;
    return printf(format, __builtin_va_arg_pack());
}

int main(void)
{
    forward(2, 3);
    printf("apply %d\n", last_sum);
    wrapped("pack %d %d\n", 4, 5);
    printf("pack refused %d\n", wrapped("%d %d %d\n", 1, 2, 3));
    return 0;
}
