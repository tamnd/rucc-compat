/* __builtin_constant_p: 1 when the compiler can tell the argument is a constant, 0 when it cannot,
 * and it never evaluates the argument. What an optimizer can prove varies, so this asks only what
 * GCC's manual promises: a constant expression is one, a volatile read is not, and the answer is
 * itself a constant expression usable in a static initializer. */
#include "../check.h"

#define MAYBE_FOLD(x) (__builtin_constant_p(x) ? (x) * 2 : -1)
static const int in_static = __builtin_constant_p(3 * 7);
static int calls;
static int touch(void) {
    return ++calls;
}

#if __has_builtin(__builtin_constant_p)
#define HAS_0 1
#else
#define HAS_0 0
#endif

int main(void) {
    CLAIM("__has_builtin(__builtin_constant_p)", HAS_0);
    volatile int v = 4;
    CHECK(__builtin_constant_p(42) == 1);
    CHECK(__builtin_constant_p(3 + 4 * 5) == 1);
    CHECK(__builtin_constant_p("literal") == 1);
    CHECK(__builtin_constant_p(sizeof(long)) == 1);
    CHECK(__builtin_constant_p(v) == 0);
    CHECK(in_static == 1);
    CHECK(MAYBE_FOLD(21) == 42);
    CHECK(__builtin_constant_p(touch()) == 0);
    CHECK(calls == 0);
    DONE();
}
