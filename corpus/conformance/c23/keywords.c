// C23 keywords: bool, true and false without a header, nullptr and nullptr_t, alignas,
// alignof, static_assert and thread_local under their plain names, static_assert with no
// message, and true and false being usable in #if.
#include <stdio.h>
#include <stddef.h>

static_assert(sizeof(bool) == 1);
static thread_local int per_thread = 4;

#if true && !false
#define PP_BOOL "true in #if"
#endif

int main(void)
{
    bool b = true;
    alignas(16) int x = 3;
    int *p = nullptr;
    nullptr_t n = nullptr;
    void *q = n;
    printf("%d %d %zu\n", b, false, sizeof(nullptr_t));
    printf("%d %d %d\n", p == nullptr, q == NULL, !nullptr);
    printf("%zu %d %d\n", alignof(int), (int)(((unsigned long)&x) % 16), per_thread);
    printf("%s %d\n", PP_BOOL, _Generic(true, bool: 1, int: 2));
    return 0;
}
