/* transparent_union: a parameter of the union type accepts any of its members' types and is
 * passed the way the first member would be. */
#include "../check.h"

#if __has_attribute(transparent_union)
#define HAS 1
#else
#define HAS 0
#endif

typedef union {
    int *ip;
    const long *lp;
    void *vp;
} __attribute__((transparent_union)) any_pointer;

static int first(any_pointer p) {
    return *p.ip;
}

int main(void) {
    CLAIM("__has_attribute(transparent_union)", HAS);
    int i = 7;
    long l = 9;
    CHECK(first(&i) == 7);
    CHECK(first(&l) == 9);
    CHECK(sizeof(any_pointer) == sizeof(void *));
    DONE();
}
