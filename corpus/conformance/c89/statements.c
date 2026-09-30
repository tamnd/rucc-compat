/* C89 statements: if and else with the else going to the nearest if, switch with fall through and
 * default and a value no case matches, while, do while and for loops, break, continue, goto
 * backwards and forwards, a null statement, and blocks whose declarations hide outer ones. */
#include <stdio.h>

static const char *classify(int n)
{
    switch (n) {
    case 0:
        return "zero";
    case 1:
    case 2:
        return "small";
    case 10:
        n = 11;
        /* falls through */
    case 11:
        return n == 11 ? "eleven" : "?";
    default:
        break;
    }
    return "other";
}

int main(void)
{
    int i, j, total;
    int x = 1;
    if (x > 0)
        if (x > 5)
            printf("big\n");
        else
            printf("positive\n");
    printf("%s %s %s %s %s\n", classify(0), classify(2), classify(10), classify(11), classify(-4));
    switch (x) {
    case 5:
        printf("never\n");
    }
    total = 0;
    i = 0;
    while (i < 10) {
        i++;
        if (i % 2)
            continue;
        total += i;
    }
    printf("%d\n", total);
    i = 0;
    do
        i += 3;
    while (i < 10);
    printf("%d\n", i);
    for (i = 0, j = 10; i < j; i++, j--)
        ;
    printf("%d %d\n", i, j);
    for (i = 0;; i++)
        if (i == 4)
            break;
    printf("%d\n", i);
    i = 0;
again:
    i++;
    if (i < 3)
        goto again;
    goto done;
    printf("skipped\n");
done:
    printf("%d\n", i);
    {
        int x = 2;
        {
            int x = 3;
            printf("%d ", x);
        }
        printf("%d ", x);
    }
    printf("%d\n", x);
    return 0;
}
