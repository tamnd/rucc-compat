/* weak: a weak declaration that nothing defines resolves to a null address rather than failing
 * the link, and a weak definition is used when there is no strong one. */
#include "../check.h"

#if __has_attribute(weak)
#define HAS 1
#else
#define HAS 0
#endif

extern int nobody_defines_this(void) __attribute__((weak));
extern int nor_this __attribute__((weak));

__attribute__((weak)) int fallback(void) {
    return 5;
}

int main(void) {
    CLAIM("__has_attribute(weak)", HAS);
    int (*volatile f)(void) = nobody_defines_this;
    CHECK(f == 0);
    CHECK(&nor_this == 0);
    CHECK(fallback() == 5);
    if (nobody_defines_this)
        CHECK(nobody_defines_this() == 0);
    DONE();
}
