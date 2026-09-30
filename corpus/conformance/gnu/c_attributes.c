/* The standard attributes GCC answers __has_c_attribute for, written with the double brackets
   and with the gnu:: prefix GCC also takes. */
#include <stdio.h>
#include <stdlib.h>

[[deprecated]] static int old(void) { return 1; }
[[deprecated("use new")]] static int older(void) { return 2; }
[[nodiscard]] static int must(void) { return 3; }
[[nodiscard("why")]] static int must_too(void) { return 4; }
[[noreturn]] static void leave(int code) { exit(code); }
static int square(int x) [[unsequenced]] { return x * x; }
static int twice(int x) [[reproducible]] { return 2 * x; }
[[gnu::always_inline]] static inline int inlined(int x) { return x + 1; }

static int bucket(int n)
{
    int total = 0;
    switch (n) {
    case 0:
        total += 1;
        [[fallthrough]];
    case 1:
        total += 10;
        break;
    default:
        break;
    }
    return total;
}

int main(void)
{
    [[maybe_unused]] int spare = 0;
    printf("deprecated %d %d\n", old(), older());
    printf("nodiscard %d %d\n", must(), must_too());
    printf("fallthrough %d %d\n", bucket(0), bucket(1));
    printf("function types %d %d\n", square(5), twice(5));
    printf("gnu prefix %d\n", inlined(1));
    leave(0);
}
