/* naked: the function gets no prologue and no epilogue, so its body has to be basic asm that
 * does the whole job, return included. x86-64 only, which is the one target here. */
#include "../check.h"

#if __has_attribute(naked)
#define HAS 1
#else
#define HAS 0
#endif

__attribute__((naked, noinline)) int forty_two(void) {
    __asm__("movl $42, %eax\n\tret");
}

__attribute__((naked, noinline)) long add(long a, long b) {
    __asm__("leaq (%rdi,%rsi), %rax\n\tret");
}

int main(void) {
    CLAIM("__has_attribute(naked)", HAS);
    CHECK(forty_two() == 42);
    CHECK(add(40, 2) == 42);
    CHECK(add(-5, 3) == -2);
    DONE();
}
