// C99 declarations: a declaration after a statement, one in the first clause of a for loop whose
// scope is the loop, line comments, long long, _Bool and <stdbool.h>, and restrict.
#include <stdio.h>
#include <stdbool.h>

static void copy(int n, int *restrict to, const int *restrict from)
{
    for (int i = 0; i < n; i++)
        to[i] = from[i] * 2;
}

int main(void)
{
    int a[3] = { 1, 2, 3 };
    printf("%d\n", a[0]); // a statement first
    int b[3];
    copy(3, b, a);
    printf("%d %d %d\n", b[0], b[1], b[2]);
    int i = 100;
    for (int i = 0; i < 2; i++)
        printf("inner %d\n", i);
    printf("outer %d\n", i);
    long long big = 9223372036854775807LL;
    unsigned long long ubig = 18446744073709551615ULL;
    printf("%lld %llu %zu\n", big, ubig, sizeof(long long));
    _Bool flag = 42;
    bool other = false;
    printf("%d %d %d %zu\n", flag, other, true, sizeof(_Bool));
    flag = 0.5;
    printf("%d %d\n", flag, (_Bool)0.0);
    return 0;
}
