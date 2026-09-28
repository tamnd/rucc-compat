/* pure and const: promises that let the compiler fold repeated calls, and never change what a
 * call that is made returns. */
#include "../check.h"

#if __has_attribute(pure)
#define HAS_PURE 1
#else
#define HAS_PURE 0
#endif
#if __has_attribute(const)
#define HAS_CONST 1
#else
#define HAS_CONST 0
#endif

static int table[4] = {1, 2, 3, 4};

__attribute__((pure, noinline)) int sum(int n) {
    int s = 0;
    for (int i = 0; i < n; i++)
        s += table[i];
    return s;
}

__attribute__((const, noinline)) int cube(int x) {
    return x * x * x;
}

int main(void) {
    CLAIM("__has_attribute(pure)", HAS_PURE);
    CLAIM("__has_attribute(const)", HAS_CONST);
    CHECK(sum(4) == 10);
    CHECK(sum(4) + sum(4) == 20);
    /* A pure function may read memory, so a store in between has to be seen. */
    table[0] = 11;
    CHECK(sum(4) == 20);
    CHECK(cube(3) == 27);
    CHECK(cube(3) + cube(-2) == 19);
    DONE();
}
