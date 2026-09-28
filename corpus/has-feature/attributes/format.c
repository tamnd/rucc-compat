/* format: the function takes a printf style format string at the given argument and its
 * arguments from the given position, which is only checked at compile time and changes nothing at
 * run time. Postgres spells it pg_attribute_printf on every elog and ereport. */
#include <stdarg.h>
#include <string.h>
#include "../check.h"

#if __has_attribute(format)
#define HAS 1
#else
#define HAS 0
#endif
#if __has_attribute(format_arg)
#define HAS_ARG 1
#else
#define HAS_ARG 0
#endif

static char last[128];

__attribute__((format(printf, 2, 3))) static int note(int level, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int n = vsnprintf(last, sizeof last, fmt, ap);
    va_end(ap);
    return n + level;
}

__attribute__((format(gnu_printf, 1, 0))) static int vnote(const char *fmt, va_list ap) {
    return vsnprintf(last, sizeof last, fmt, ap);
}

static int vcall(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int n = vnote(fmt, ap);
    va_end(ap);
    return n;
}

__attribute__((format_arg(1))) static const char *translate(const char *msg) {
    return msg;
}

int main(void) {
    CLAIM("__has_attribute(format)", HAS);
    CLAIM("__has_attribute(format_arg)", HAS_ARG);
    CHECK(note(100, "%s=%d", "x", 42) == 104);
    CHECK(strcmp(last, "x=42") == 0);
    CHECK(vcall("%05.1f|%x", 3.14159, 255) == 8);
    CHECK(strcmp(last, "003.1|ff") == 0);
    CHECK(note(0, translate("%d%%"), 7) == 2);
    printf("last %s\n", last);
    DONE();
}
