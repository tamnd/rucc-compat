// C17 added no constructs, only answers to defect reports, so what is left to measure is that it
// says which standard it is and that ATOMIC_VAR_INIT, which C17 deprecated, still works.
#include <stdio.h>
#include <stdatomic.h>

int main(void)
{
    atomic_int a = ATOMIC_VAR_INIT(3);
    printf("%ld %d\n", __STDC_VERSION__, atomic_load(&a));
    return 0;
}
