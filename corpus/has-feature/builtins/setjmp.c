/* __builtin_setjmp and __builtin_longjmp: GCC's own lightweight pair, which takes a buffer of five
 * words and may only jump back with the value 1. */
#include "../check.h"

static void *buffer[5];
static __attribute__((noinline)) void jump(void) {
    __builtin_longjmp(buffer, 1);
}

#if __has_builtin(__builtin_setjmp)
#define HAS_0 1
#else
#define HAS_0 0
#endif
#if __has_builtin(__builtin_longjmp)
#define HAS_1 1
#else
#define HAS_1 0
#endif

int main(void) {
    CLAIM("__has_builtin(__builtin_setjmp)", HAS_0);
    CLAIM("__has_builtin(__builtin_longjmp)", HAS_1);
    volatile int passes = 0;
    if (__builtin_setjmp(buffer) == 0) {
        passes++;
        jump();
        passes += 100;
    } else {
        passes += 10;
    }
    CHECK(passes == 11);
    DONE();
}
