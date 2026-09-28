/* gnu_inline: with extern inline, the definition is only for inlining and no out of line copy is
 * emitted, so a call that is not inlined goes to a definition somewhere else. Here that is the
 * second definition, which GCC allows after a gnu_inline one. */
#include "../check.h"

#if __has_attribute(gnu_inline)
#define HAS 1
#else
#define HAS 0
#endif

extern inline __attribute__((gnu_inline)) int twice(int x) {
    return x * 2;
}

int twice(int x) {
    return x * 2;
}

static inline __attribute__((gnu_inline)) int thrice(int x) {
    return x * 3;
}

int main(void) {
    CLAIM("__has_attribute(gnu_inline)", HAS);
    int (*volatile via)(int) = twice;
    CHECK(twice(21) == 42);
    CHECK(via(4) == 8);
    CHECK(thrice(5) == 15);
    DONE();
}
