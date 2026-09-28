/* alias: the declaration is another name for a definition in the same translation unit, the same
 * address and the same body. */
#include "../check.h"

#if __has_attribute(alias)
#define HAS 1
#else
#define HAS 0
#endif

int real_function(int x) {
    return x + 100;
}
int other_name(int x) __attribute__((alias("real_function")));

int real_data = 17;
extern int data_alias __attribute__((alias("real_data")));

int main(void) {
    CLAIM("__has_attribute(alias)", HAS);
    CHECK(other_name(1) == 101);
    CHECK(other_name == real_function);
    CHECK(&data_alias == &real_data);
    data_alias = 18;
    CHECK(real_data == 18);
    DONE();
}
