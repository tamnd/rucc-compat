/* returns_twice: the function may return more than once, the way setjmp does, so the caller has
 * to keep what it needs across the call somewhere a second return can find it. This is the shape
 * of Postgres's PG_TRY, which calls sigsetjmp through a declaration of its own. */
#include <setjmp.h>
#include "../check.h"

#if __has_attribute(returns_twice)
#define HAS 1
#else
#define HAS 0
#endif

/* glibc's own declaration carries no returns_twice, so the attribute here is what does it. */
extern int again(sigjmp_buf env, int save) __asm__("__sigsetjmp") __attribute__((returns_twice));

static sigjmp_buf *current;

static __attribute__((noinline)) void throw_it(int code) {
    siglongjmp(*current, code);
}

static int attempt(int fail) {
    sigjmp_buf here;
    volatile int stage = 0;
    int caught = 0;
    current = &here;
    if (again(here, 0) == 0) {
        stage = 1;
        if (fail)
            throw_it(7);
        stage = 2;
    } else {
        caught = 1;
    }
    return caught * 100 + stage * 10 + (current == &here);
}

int main(void) {
    CLAIM("__has_attribute(returns_twice)", HAS);
    CHECK(attempt(0) == 21);
    CHECK(attempt(1) == 111);
    int total = 0;
    for (int i = 0; i < 5; i++)
        total += attempt(i & 1);
    CHECK(total == 21 * 3 + 111 * 2);
    DONE();
}
