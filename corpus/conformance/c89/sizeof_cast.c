/* C89 sizeof and casts: sizeof of a type name and of an expression that is not evaluated, of
 * arrays and structures, and casts written with abstract declarators. */
#include <stdio.h>

struct pair { char c; int i; };

int main(void)
{
    int n = 3;
    int arr[4][6];
    char *strings[3];
    unsigned long sz;
    sz = sizeof n++;
    printf("%lu %d\n", sz, n);
    printf("%lu %lu %lu\n", (unsigned long)sizeof(char), (unsigned long)sizeof(short), (unsigned long)sizeof(long));
    printf("%lu %lu %lu\n", (unsigned long)sizeof arr, (unsigned long)sizeof arr[0], (unsigned long)sizeof arr[0][0]);
    printf("%lu %lu\n", (unsigned long)sizeof strings, (unsigned long)sizeof(struct pair));
    printf("%lu %lu\n", (unsigned long)sizeof(int *), (unsigned long)sizeof(int (*)[6]));
    printf("%lu\n", (unsigned long)sizeof(int (*)(void)));
    printf("%d %d\n", (int)(char)0x141, (int)(short)-1);
    printf("%lu\n", (unsigned long)(unsigned char)~0);
    printf("%d\n", (int)(((int (*)[6])arr)[1] - arr[0]));
    return 0;
}
