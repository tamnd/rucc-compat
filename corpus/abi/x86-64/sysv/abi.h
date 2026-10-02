/* What both halves of every case include. Each half prints what it was handed and what it got
 * back in the same words, so a run where rucc built one half and gcc built the other prints the
 * same lines as the run where gcc built both, and any difference is the two compilers
 * disagreeing about where a value goes. */
#include <stdio.h>
#include <string.h>

/* The bytes of an object, for a type printf has no conversion for, such as _Float128. Only used
 * on objects with no padding in them, since padding is whatever was in the register or the slot
 * and the two compilers have no reason to agree about it. */
static void bytes(const char *what, const void *p, unsigned long n)
{
    const unsigned char *c = p;
    printf("%s", what);
    while (n--)
        printf(" %02x", c[n]);
    printf("\n");
}
