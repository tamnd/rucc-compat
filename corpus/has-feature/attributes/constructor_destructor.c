/* constructor and destructor: the function runs before main, or after main returns or exit is
 * called, and a priority orders the ones that name it, lowest first for constructors and last for
 * destructors. */
#include "../check.h"

#if __has_attribute(constructor)
#define HAS_CONSTRUCTOR 1
#else
#define HAS_CONSTRUCTOR 0
#endif
#if __has_attribute(destructor)
#define HAS_DESTRUCTOR 1
#else
#define HAS_DESTRUCTOR 0
#endif

static char order[8];
static int at;

__attribute__((constructor(102))) static void second(void) {
    order[at++] = 'b';
}
__attribute__((constructor(101))) static void first(void) {
    order[at++] = 'a';
}
__attribute__((constructor)) static void plain(void) {
    order[at++] = 'c';
}

__attribute__((destructor(101))) static void last_out(void) {
    printf("destructor 101\n");
}
__attribute__((destructor(102))) static void first_out(void) {
    printf("destructor 102\n");
}
__attribute__((destructor)) static void unordered_out(void) {
    printf("destructor\n");
}

int main(void) {
    CLAIM("__has_attribute(constructor)", HAS_CONSTRUCTOR);
    CLAIM("__has_attribute(destructor)", HAS_DESTRUCTOR);
    order[at] = 0;
    printf("order %s\n", order);
    CHECK(at == 3);
    CHECK(order[0] == 'a' && order[1] == 'b' && order[2] == 'c');
    DONE();
}
