/* no_instrument_function: the function is left out of -finstrument-functions. Without that
 * option there is nothing to see except that it is accepted and the function works. */
#include "../check.h"

#if __has_attribute(no_instrument_function)
#define HAS 1
#else
#define HAS 0
#endif

__attribute__((no_instrument_function)) static int plain(int x) {
    return x + 1;
}

int main(void) {
    CLAIM("__has_attribute(no_instrument_function)", HAS);
    CHECK(plain(41) == 42);
    DONE();
}
