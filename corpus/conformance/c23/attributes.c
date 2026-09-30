// C23 attributes in the standard syntax: nodiscard, maybe_unused, deprecated, fallthrough,
// noreturn, unsequenced and reproducible, and the vendor prefixed gnu:: form, with
// __has_c_attribute answering for each.
#include <stdio.h>
#include <stdlib.h>

[[nodiscard]] static int value(void) { return 3; }
[[maybe_unused]] static int unused_helper(void) { return 0; }
[[deprecated("use value")]] static int old(void) { return 1; }
[[noreturn]] static void stop(int code) { exit(code); }
[[unsequenced]] static int square(int x) { return x * x; }
[[reproducible]] static int twice(int x) { return x * 2; }
[[gnu::always_inline]] static inline int one(void) { return 1; }

static int classify(int n)
{
    int r = 0;
    switch (n) {
    case 0:
        r += 10;
        [[fallthrough]];
    case 1:
        r += 1;
        break;
    default:
        r = -1;
    }
    return r;
}

int main(void)
{
    [[maybe_unused]] int spare = 0;
    int v = value();
    printf("%d %d %d %d %d\n", v, square(4), twice(5), one(), classify(0));
    printf("%d %d %d\n", __has_c_attribute(nodiscard) > 0, __has_c_attribute(fallthrough) > 0,
           __has_c_attribute(gnu::packed) > 0);
    printf("%d\n", __has_c_attribute(no_such_attribute));
    (void)old;
    stop(0);
}
