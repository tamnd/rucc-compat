/* C89 character constants and string literals: every simple escape, octal and hexadecimal escapes,
 * the type of a character constant, adjacent string literals joined, and the size of a literal. */
#include <stdio.h>
#include <string.h>

int main(void)
{
    const char *s = "\a\b\f\n\r\t\v\\\'\"\?";
    int i;
    for (i = 0; s[i] != '\0'; i++)
        printf("%d ", s[i]);
    printf("\n");
    printf("%d %d %d %d\n", '\0', '\101', '\x41', '\177');
    printf("%d %d\n", 'A', '0');
    printf("%lu\n", (unsigned long)sizeof('A'));
    printf("%s|\n", "join" "ed" " " "literals");
    printf("%lu %lu\n", (unsigned long)sizeof("abc"), (unsigned long)strlen("ab\0cd"));
    printf("%d\n", "abc"[1]);
    printf("%s\n", "a\
b");
    return 0;
}
