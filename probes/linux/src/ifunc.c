#include <stdio.h>
static int impl_a(void) { return 1; }
static int (*resolve(void))(void) { return impl_a; }
int pick(void) __attribute__((ifunc("resolve")));
__attribute__((target_clones("default","avx2"))) int tc(int x) { return x + 1; }
int main(void) { printf("ifunc=%d tc=%d\n", pick(), tc(1)); return 0; }
