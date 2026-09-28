/* unused: says that a variable, parameter, function, type or label may go unused, which only
 * silences a warning. Postgres spells it pg_attribute_unused. */
#include "../check.h"

#if __has_attribute(unused)
#define HAS 1
#else
#define HAS 0
#endif

__attribute__((unused)) static int never_called(void) {
    return 1;
}

typedef int spare_type __attribute__((unused));

static int with_spare(int used_one, int spare __attribute__((unused))) {
    int local __attribute__((unused)) = 3;
    return used_one;
}

int main(void) {
    CLAIM("__has_attribute(unused)", HAS);
    CHECK(with_spare(5, 6) == 5);
    goto next;
spare_label: __attribute__((unused));
next:
    CHECK(sizeof(spare_type) == sizeof(int));
    DONE();
}
