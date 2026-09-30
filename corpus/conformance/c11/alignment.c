// C11 alignment: _Alignas on objects and members, with a type or a constant, _Alignof of types
// and expressions, <stdalign.h> and its macros, max_align_t, and aligned_alloc.
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdalign.h>

struct padded {
    char c;
    _Alignas(16) int x;
    alignas(double) char d;
};

int main(void)
{
    _Alignas(32) char buffer[8];
    alignas(int) unsigned char bytes[sizeof(int)];
    printf("%d %d\n", (int)((uintptr_t)buffer % 32), (int)((uintptr_t)bytes % alignof(int)));
    printf("%zu %zu %zu\n", _Alignof(char), _Alignof(int), alignof(double));
    printf("%zu %zu\n", offsetof(struct padded, x), offsetof(struct padded, d));
    printf("%zu %zu\n", sizeof(struct padded), alignof(struct padded));
    printf("%d\n", alignof(max_align_t) >= alignof(long double));
    printf("%d %d\n", __alignas_is_defined, __alignof_is_defined);
    void *p = aligned_alloc(64, 128);
    printf("%d\n", (int)((uintptr_t)p % 64));
    free(p);
    return 0;
}
