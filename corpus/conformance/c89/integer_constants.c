/* C89 integer constants: decimal, octal and hexadecimal forms, the suffixes, and the type each
 * constant gets, which is visible through sizeof and through what happens at the edges. */
#include <stdio.h>

int main(void)
{
    printf("%d %d %d\n", 10, 010, 0x10);
    printf("%d %d\n", 0XfF, 0777);
    printf("%lu %lu %lu\n", (unsigned long)sizeof(1), (unsigned long)sizeof(1L), (unsigned long)sizeof(1U));
    printf("%lu %lu\n", (unsigned long)sizeof(1UL), (unsigned long)sizeof(1lu));
    /* An octal or hexadecimal constant too big for int becomes unsigned int, a decimal one does not. */
    printf("%d %d\n", 0xFFFFFFFF > 0, -1 < 0xFFFFFFFF);
    printf("%lu\n", (unsigned long)sizeof(0xFFFFFFFF));
    printf("%lu %lu\n", (unsigned long)sizeof(2147483647), (unsigned long)sizeof(0x7FFFFFFF));
    printf("%u %lu\n", 4294967295U, 4294967295UL);
    printf("%d\n", -2147483647 - 1);
    return 0;
}
