// C99 variable length arrays: an array whose length is known only at run time, sizeof of one
// evaluated at run time, a parameter declared with a length from an earlier parameter, a pointer
// to a variable length array, and a typedef of one taking its length where it stands.
#include <stdio.h>

static int trace(int n, int m[n][n])
{
    int total = 0;
    for (int i = 0; i < n; i++)
        total += m[i][i];
    return total;
}

static int total(int n, int v[static 1])
{
    int t = 0;
    for (int i = 0; i < n; i++)
        t += v[i];
    return t;
}

int main(void)
{
    int n = 4;
    int v[n];
    for (int i = 0; i < n; i++)
        v[i] = i + 1;
    printf("%zu %d\n", sizeof v, total(n, v));
    int m[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            m[i][j] = i * n + j;
    printf("%d %zu %zu\n", trace(n, m), sizeof m, sizeof m[0]);
    int (*row)[n] = m;
    printf("%d\n", row[2][3]);
    typedef char buffer[n + 1];
    n = 100;
    buffer b;
    printf("%zu\n", sizeof b);
    return 0;
}
