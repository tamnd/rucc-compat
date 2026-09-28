/* noinline: the function is never inlined, so it gets a frame of its own however high the
 * optimization level. */
#include "../check.h"

#if __has_attribute(noinline)
#define HAS 1
#else
#define HAS 0
#endif

static __attribute__((noinline)) void *own_frame(void) {
    return __builtin_frame_address(0);
}

static __attribute__((noinline)) int square(int x) {
    return x * x;
}

int main(void) {
    CLAIM("__has_attribute(noinline)", HAS);
    void *mine = __builtin_frame_address(0);
    CHECK(own_frame() != mine);
    CHECK(square(12) == 144);
    DONE();
}
