/* C89 external definitions: tentative definitions of one object that together make one definition
 * starting at zero, a later definition with an initializer completing them, internal linkage
 * carried by an earlier static declaration, and mutual recursion through declarations. */
#include <stdio.h>

int tentative;
int tentative;
int completed;
int completed = 5;
static int internal;
extern int internal;
int later[];
int later[3];

static int is_even(unsigned n);
static int is_odd(unsigned n) { return n == 0 ? 0 : is_even(n - 1); }
static int is_even(unsigned n) { return n == 0 ? 1 : is_odd(n - 1); }

int main(void)
{
    printf("%d %d %d\n", tentative, completed, internal);
    internal = 4;
    later[2] = internal;
    printf("%d %lu\n", later[2], (unsigned long)sizeof later);
    printf("%d %d\n", is_even(10), is_odd(7));
    return 0;
}
