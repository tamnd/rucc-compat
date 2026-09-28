/* noreturn: the function never returns to its caller, so a caller may end on the call without a
 * return statement of its own. The three spellings mean the same thing. */
#include <setjmp.h>
#include <stdlib.h>
#include "../check.h"

#if __has_attribute(noreturn)
#define HAS 1
#else
#define HAS 0
#endif
#if __has_attribute(__noreturn__)
#define HAS_SPELLED 1
#else
#define HAS_SPELLED 0
#endif

static jmp_buf out;

__attribute__((noreturn)) static void escape(int code) {
    longjmp(out, code);
}

_Noreturn static void escape_too(int code) {
    longjmp(out, code);
}

static int pick(int x) {
    if (x > 0)
        return x;
    escape(5);
}

__attribute__((noreturn)) static void finish(void) {
    printf("finish\n");
    fflush(stdout);
    exit(failures != 0);
}

int main(void) {
    CLAIM("__has_attribute(noreturn)", HAS);
    CLAIM("__has_attribute(__noreturn__)", HAS_SPELLED);
    CHECK(pick(3) == 3);
    int got = setjmp(out);
    if (got == 0)
        pick(0);
    CHECK(got == 5);
    got = setjmp(out);
    if (got == 0)
        escape_too(6);
    CHECK(got == 6);
    finish();
}
