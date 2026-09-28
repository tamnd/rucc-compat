/* aligned: raises the alignment of a variable, a structure member or a type, and never lowers
 * it on its own. */
#include <stddef.h>
#include <stdint.h>
#include "../check.h"

#if __has_attribute(aligned)
#define HAS 1
#else
#define HAS 0
#endif

struct wide {
    char c;
    int i __attribute__((aligned(16)));
};

typedef int line __attribute__((aligned(64)));
struct __attribute__((aligned(32))) block {
    char c;
};

static char before;
static int big __attribute__((aligned(128)));

int main(void) {
    CLAIM("__has_attribute(aligned)", HAS);
    CHECK(offsetof(struct wide, i) == 16);
    CHECK(sizeof(struct wide) == 32);
    CHECK(_Alignof(struct wide) == 16);
    CHECK(_Alignof(line) == 64);
    CHECK(_Alignof(struct block) == 32);
    CHECK(sizeof(struct block) == 32);
    CHECK(((uintptr_t)&big & 127) == 0);
    int local __attribute__((aligned(64))) = 5;
    CHECK(((uintptr_t)&local & 63) == 0);
    CHECK(local + before == 5);
    /* On its own, aligned does not lower an alignment. */
    struct low {
        long long x __attribute__((aligned(1)));
    };
    CHECK(_Alignof(struct low) == _Alignof(long long));
    DONE();
}
