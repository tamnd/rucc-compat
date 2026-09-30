/* C89 comments: a comment is one space, it does not nest, and inside a string or a character
 * constant it is not a comment at all. */
#include <stdio.h>

int main(void)
{
    int a/**/= 4;
    int b = 6 /* six */;
    /* /* a second opener inside a comment is just text */
    printf("%d %d\n", a, b);
    printf("%s\n", "/* not a comment */");
    printf("%d\n", '/' * 1);
    printf("%d\n", 8 /* divide? */ / 2);
    return 0;
}
