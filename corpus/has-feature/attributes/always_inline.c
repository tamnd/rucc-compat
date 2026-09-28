/* always_inline: the function is inlined even with no optimization. That is what lets Postgres
 * and glibc define such a function in a header as a plain C99 inline with no external
 * definition anywhere: every call is inlined, so nothing ever has to link against it. */
#include "../check.h"

#if __has_attribute(always_inline)
#define HAS 1
#else
#define HAS 0
#endif

/* C99 inline with no extern declaration, so this file provides no external definition. A call
 * that is not inlined is an undefined reference at link time. */
inline __attribute__((always_inline)) int add_three(int x) {
    return x + 3;
}

static inline __attribute__((always_inline)) int twice(int x) {
    return x * 2;
}

static inline __attribute__((always_inline)) void *frame_here(void) {
    return __builtin_frame_address(0);
}

int main(void) {
    CLAIM("__has_attribute(always_inline)", HAS);
    CHECK(add_three(39) == 42);
    CHECK(twice(add_three(1)) == 8);
    /* Inlined, so the frame is the caller's own. */
    CHECK(frame_here() == __builtin_frame_address(0));
    DONE();
}
