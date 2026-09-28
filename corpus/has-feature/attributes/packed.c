/* packed: members get the smallest alignment, one byte for a member and one bit for a
 * bit-field, unless aligned says otherwise. */
#include <stddef.h>
#include <string.h>
#include "../check.h"

#if __has_attribute(packed)
#define HAS 1
#else
#define HAS 0
#endif

struct __attribute__((packed)) tight {
    char c;
    int i;
    short s;
    long long l;
};

struct loose {
    char c;
    int i __attribute__((packed));
};

struct __attribute__((packed)) bits {
    unsigned a : 3;
    unsigned b : 7;
    unsigned c : 6;
};

int main(void) {
    CLAIM("__has_attribute(packed)", HAS);
    CHECK(sizeof(struct tight) == 15);
    CHECK(offsetof(struct tight, i) == 1);
    CHECK(offsetof(struct tight, s) == 5);
    CHECK(offsetof(struct tight, l) == 7);
    CHECK(_Alignof(struct tight) == 1);
    CHECK(offsetof(struct loose, i) == 1);
    CHECK(sizeof(struct bits) == 2);
    struct tight t[2];
    memset(t, 0, sizeof t);
    t[1].l = 0x0102030405060708LL;
    t[1].i = -7;
    CHECK(t[1].l == 0x0102030405060708LL);
    CHECK(t[1].i == -7);
    CHECK((char *)&t[1] - (char *)&t[0] == 15);
    struct bits b = {5, 100, 33};
    CHECK(b.a == 5 && b.b == 100 && b.c == 33);
    DONE();
}
