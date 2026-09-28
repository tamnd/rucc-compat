/* visibility: sets the ELF visibility of a symbol. Inside one executable every visibility still
 * links and calls, which is what this can see. */
#include "../check.h"

#if __has_attribute(visibility)
#define HAS 1
#else
#define HAS 0
#endif

__attribute__((visibility("hidden"), noinline)) int hidden_one(void) {
    return 1;
}
__attribute__((visibility("default"), noinline)) int default_one(void) {
    return 2;
}
__attribute__((visibility("protected"), noinline)) int protected_one(void) {
    return 3;
}
__attribute__((visibility("internal"), noinline)) int internal_one(void) {
    return 4;
}
__attribute__((visibility("hidden"))) int hidden_data = 5;

#pragma GCC visibility push(hidden)
int pushed(void) {
    return 6;
}
#pragma GCC visibility pop

int main(void) {
    CLAIM("__has_attribute(visibility)", HAS);
    CHECK(hidden_one() + default_one() + protected_one() + internal_one() == 10);
    CHECK(hidden_data == 5);
    CHECK(pushed() == 6);
    int (*volatile p)(void) = hidden_one;
    CHECK(p() == 1);
    DONE();
}
