/* A weak reference: a static name for another symbol that resolves to nothing when the symbol
   is not linked in. rucc refuses it until it can build one, tamnd/rucc#2479. */
#include <stdio.h>

__attribute__((noinline)) int target_function(void) { return 3; }
static int by_weakref(void) __attribute__((weakref("target_function")));
extern int nowhere(void);
static int missing(void) __attribute__((weakref("nowhere")));

int main(void)
{
    printf("weakref %d %d %d\n", by_weakref(), target_function(), missing == 0);
    return 0;
}
