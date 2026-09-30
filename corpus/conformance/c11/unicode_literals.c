// C11 Unicode literals: the u8, u and U prefixes on strings, the u and U prefixes on character
// constants, char16_t and char32_t from <uchar.h>, concatenation of a prefixed literal with a
// plain one, and the __STDC_UTF_16__ and __STDC_UTF_32__ macros.
#include <stdio.h>
#include <uchar.h>
#include <string.h>

int main(void)
{
    const char *a = u8"café";
    const char16_t *b = u"été";
    const char32_t *c = U"\U0001F600!";
    char16_t d = u'x';
    char32_t e = U'中';
    printf("%zu", strlen(a));
    for (const unsigned char *p = (const unsigned char *)a; *p; p++)
        printf(" %02x", *p);
    printf("\n%d %d %d\n", b[0], b[1], b[2]);
    printf("%lx %d\n", (unsigned long)c[0], (int)c[1]);
    printf("%d %lx\n", d, (unsigned long)e);
    printf("%zu %zu %zu\n", sizeof(u"ab"), sizeof(U"ab"), sizeof(u8"ab"));
    const char16_t *joined = u"one" "two";
    printf("%d %d %zu\n", joined[3], joined[5], sizeof(u"one" "two") / sizeof(char16_t));
    printf("%d %d\n", __STDC_UTF_16__, __STDC_UTF_32__);
    printf("%zu %zu\n", sizeof(char16_t), sizeof(char32_t));
    return 0;
}
