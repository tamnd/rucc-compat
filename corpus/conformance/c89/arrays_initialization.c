/* C89 arrays and initialization: multidimensional arrays, an array whose size comes from its
 * initializer, braces elided in a nested aggregate, a character array from a string, a partial
 * initializer filling the rest with zero, and static objects starting at zero. */
#include <stdio.h>

struct item { const char *name; int qty; double price; };

static int zeroes[4];
static char *nothing;
static int table[] = { 1, 2, 3, 4, 5 };
static struct item stock[] = { { "pen", 3, 1.5 }, { "ink", 1, 4.25 } };
static int *where = &table[2];

int main(void)
{
    int grid[2][3] = { { 1, 2, 3 }, { 4, 5, 6 } };
    int flat[2][3] = { 1, 2, 3, 4 };
    char word[] = "hello";
    char fixed[8] = "hi";
    char letters[3] = { 'a', 'b', 'c' };
    int partial[5] = { 9 };
    struct item one = { "cap" };
    int i, j;
    for (i = 0; i < 2; i++)
        for (j = 0; j < 3; j++)
            printf("%d%d ", grid[i][j], flat[i][j]);
    printf("\n");
    printf("%lu %s %lu\n", (unsigned long)sizeof word, word, (unsigned long)sizeof table / sizeof table[0]);
    printf("%d %d %c\n", fixed[2], fixed[7], letters[2]);
    for (i = 0; i < 5; i++)
        printf("%d", partial[i]);
    printf("\n");
    printf("%s %d %g\n", one.name, one.qty, one.price);
    printf("%s %d %g\n", stock[1].name, stock[1].qty, stock[1].price);
    printf("%d %d %d\n", zeroes[3], nothing == 0, *where);
    return 0;
}
