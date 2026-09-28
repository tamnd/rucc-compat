/* scalar_storage_order: the scalar members of the structure are stored in the byte order named,
 * and read back in the machine's. */
#include <stdint.h>
#include "../check.h"

#if __has_attribute(scalar_storage_order)
#define HAS 1
#else
#define HAS 0
#endif

struct __attribute__((scalar_storage_order("big-endian"))) big {
    uint32_t word;
    uint16_t half;
};

struct __attribute__((scalar_storage_order("little-endian"))) little {
    uint32_t word;
};

int main(void) {
    CLAIM("__has_attribute(scalar_storage_order)", HAS);
    struct big b;
    b.word = 0x01020304;
    b.half = 0xa1b2;
    unsigned char *p = (unsigned char *)&b;
    CHECK(p[0] == 0x01 && p[1] == 0x02 && p[2] == 0x03 && p[3] == 0x04);
    CHECK(p[4] == 0xa1 && p[5] == 0xb2);
    CHECK(b.word == 0x01020304);
    CHECK(b.half == 0xa1b2);
    struct little l;
    l.word = 0x01020304;
    unsigned char *q = (unsigned char *)&l;
    CHECK(q[0] == 0x04 && q[3] == 0x01);
    DONE();
}
