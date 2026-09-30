/* C89 bit-fields: signed and unsigned fields of int, wrap on overflow, an unnamed field for padding
 * and a zero width one to start a new unit, and the size of the record they make. */
#include <stdio.h>

struct flags {
    unsigned int ready : 1;
    unsigned int mode : 3;
    signed int delta : 4;
    unsigned int : 2;
    unsigned int level : 5;
    unsigned int : 0;
    unsigned int next : 7;
};

int main(void)
{
    struct flags f;
    f.ready = 1;
    f.mode = 9;
    f.delta = -3;
    f.level = 31;
    f.next = 100;
    printf("%u %u %d %u %u\n", f.ready, f.mode, f.delta, f.level, f.next);
    f.level++;
    f.delta = 7;
    f.delta++;
    printf("%u %d\n", f.level, f.delta);
    printf("%lu\n", (unsigned long)sizeof(struct flags));
    f.mode = f.mode + 7;
    printf("%u\n", f.mode);
    return 0;
}
