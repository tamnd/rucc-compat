/* The builtins that ask about the frame, the stack and the layout of objects. */
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "../check.h"

struct point {
    char tag;
    double x;
    int y[3];
};

static __attribute__((noinline)) void *called_from(void) {
    return __builtin_return_address(0);
}

static __attribute__((noinline)) int deeper(void *outer) {
    char here;
    /* The stack grows down on x86-64, so a callee's frame is below its caller's. */
    return (char *)__builtin_frame_address(0) < (char *)outer && &here < (char *)outer;
}

#if __has_builtin(__builtin_frame_address)
#define HAS_0 1
#else
#define HAS_0 0
#endif
#if __has_builtin(__builtin_return_address)
#define HAS_1 1
#else
#define HAS_1 0
#endif
#if __has_builtin(__builtin_alloca)
#define HAS_2 1
#else
#define HAS_2 0
#endif
#if __has_builtin(__builtin_assume_aligned)
#define HAS_3 1
#else
#define HAS_3 0
#endif
#if __has_builtin(__builtin_object_size)
#define HAS_4 1
#else
#define HAS_4 0
#endif
#if __has_builtin(__builtin_offsetof)
#define HAS_5 1
#else
#define HAS_5 0
#endif
#if __has_builtin(__builtin_classify_type)
#define HAS_6 1
#else
#define HAS_6 0
#endif
#if __has_builtin(__builtin_prefetch)
#define HAS_7 1
#else
#define HAS_7 0
#endif

int main(void) {
    CLAIM("__has_builtin(__builtin_frame_address)", HAS_0);
    CLAIM("__has_builtin(__builtin_return_address)", HAS_1);
    CLAIM("__has_builtin(__builtin_alloca)", HAS_2);
    CLAIM("__has_builtin(__builtin_assume_aligned)", HAS_3);
    CLAIM("__has_builtin(__builtin_object_size)", HAS_4);
    CLAIM("__has_builtin(__builtin_offsetof)", HAS_5);
    CLAIM("__has_builtin(__builtin_classify_type)", HAS_6);
    CLAIM("__has_builtin(__builtin_prefetch)", HAS_7);
    void *mine = __builtin_frame_address(0);
    CHECK(mine != 0);
    CHECK(deeper(mine));
    CHECK(called_from() != 0);
    char *p = __builtin_alloca(100);
    memset(p, 'x', 100);
    CHECK(p[99] == 'x' && ((uintptr_t)p & 15) == 0);
    static double table[8] __attribute__((aligned(32)));
    double *t = __builtin_assume_aligned(table, 32);
    CHECK(t == table);
    char buf[40];
    CHECK(__builtin_object_size(buf, 0) == 40);
    CHECK(__builtin_object_size(buf + 10, 0) == 30);
    CHECK(__builtin_object_size(p, 2) == 0 || __builtin_object_size(p, 2) == 100);
    CHECK(__builtin_offsetof(struct point, x) == 8);
    CHECK(__builtin_offsetof(struct point, y[2]) == 24);
    CHECK(__builtin_offsetof(struct point, y) == offsetof(struct point, y));
    CHECK(__builtin_classify_type(1) == 1);
    CHECK(__builtin_classify_type(1.0) == 8);
    CHECK(__builtin_classify_type(p) == 5);
    __builtin_prefetch(table);
    __builtin_prefetch(table, 1, 0);
    DONE();
}
