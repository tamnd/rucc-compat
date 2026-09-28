/* cleanup: the function runs with a pointer to the variable when the variable goes out of scope,
 * in reverse order of declaration, however the scope is left. */
#include "../check.h"

#if __has_attribute(cleanup)
#define HAS 1
#else
#define HAS 0
#endif

static char trail[32];
static int at;

static void leave(int *p) {
    trail[at++] = (char)('0' + *p);
}

static int early(int stop) {
    int a __attribute__((cleanup(leave))) = 1;
    for (int i = 0; i < 3; i++) {
        int b __attribute__((cleanup(leave))) = 2 + i;
        if (i == stop)
            return i;
    }
    int c __attribute__((cleanup(leave))) = 9;
    return c;
}

int main(void) {
    CLAIM("__has_attribute(cleanup)", HAS);
    {
        int x __attribute__((cleanup(leave))) = 1;
        int y __attribute__((cleanup(leave))) = 2;
        trail[at++] = (char)('0' + x + y);
    }
    trail[at] = 0;
    printf("trail %s\n", trail);
    CHECK(trail[0] == '3' && trail[1] == '2' && trail[2] == '1');
    at = 0;
    CHECK(early(1) == 1);
    trail[at] = 0;
    printf("trail %s\n", trail);
    at = 0;
    CHECK(early(5) == 9);
    trail[at] = 0;
    printf("trail %s\n", trail);
    DONE();
}
