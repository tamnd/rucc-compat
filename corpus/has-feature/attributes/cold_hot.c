/* cold and hot: hints about how often a function runs, which move code around and never change
 * what it does. Postgres marks its error reporting cold through pg_attribute_cold when the
 * compiler claims the attribute. */
#include "../check.h"

#if __has_attribute(cold)
#define HAS_COLD 1
#else
#define HAS_COLD 0
#endif
#if __has_attribute(hot)
#define HAS_HOT 1
#else
#define HAS_HOT 0
#endif

static int reported;

__attribute__((cold, noinline)) static void report(int code) {
    reported = code;
}

__attribute__((hot, noinline)) static int step(int x) {
    return x + 1;
}

int main(void) {
    CLAIM("__has_attribute(cold)", HAS_COLD);
    CLAIM("__has_attribute(hot)", HAS_HOT);
    int x = 0;
    for (int i = 0; i < 1000; i++)
        x = step(x);
    if (x != 1000)
        report(1);
    CHECK(x == 1000);
    CHECK(reported == 0);
    report(9);
    CHECK(reported == 9);
    /* cold on a label says the path after it is unlikely. */
    if (x == 1000)
        goto rare;
    x = 0;
rare:
    __attribute__((cold));
    CHECK(x == 1000);
    DONE();
}
