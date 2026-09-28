/* __builtin_types_compatible_p: 1 when the two types are compatible, ignoring top level
 * qualifiers, and 0 otherwise, as an integer constant expression. __builtin_choose_expr picks one
 * of two expressions on a constant without converting either. Postgres builds its
 * StaticAssertExpr and unconstify on these. */
#include "../check.h"

enum colour { RED };
typedef int my_int;
#define TYPE_WORD(x)                                                                             \
    __builtin_choose_expr(__builtin_types_compatible_p(__typeof__(x), double), "double",        \
                          __builtin_choose_expr(__builtin_types_compatible_p(__typeof__(x), int), \
                                                "int", "other"))

#if __has_builtin(__builtin_types_compatible_p)
#define HAS_0 1
#else
#define HAS_0 0
#endif
#if __has_builtin(__builtin_choose_expr)
#define HAS_1 1
#else
#define HAS_1 0
#endif

int main(void) {
    CLAIM("__has_builtin(__builtin_types_compatible_p)", HAS_0);
    CLAIM("__has_builtin(__builtin_choose_expr)", HAS_1);
    CHECK(__builtin_types_compatible_p(int, int) == 1);
    CHECK(__builtin_types_compatible_p(int, const int) == 1);
    CHECK(__builtin_types_compatible_p(int, volatile my_int) == 1);
    CHECK(__builtin_types_compatible_p(int, long) == 0);
    CHECK(__builtin_types_compatible_p(long, long long) == 0);
    CHECK(__builtin_types_compatible_p(char, signed char) == 0);
    CHECK(__builtin_types_compatible_p(char *, const char *) == 0);
    CHECK(__builtin_types_compatible_p(int[], int[5]) == 1);
    CHECK(__builtin_types_compatible_p(int[4], int[5]) == 0);
    CHECK(__builtin_types_compatible_p(int *, int[5]) == 0);
    CHECK(__builtin_types_compatible_p(unsigned, unsigned int) == 1);
    CHECK(__builtin_types_compatible_p(enum colour, int) == 0 ||
          __builtin_types_compatible_p(enum colour, unsigned) == 0);
    static const int folded = __builtin_types_compatible_p(double, double);
    CHECK(folded == 1);
    double d = 1.0;
    int i = 1;
    short s = 1;
    printf("%s %s %s\n", TYPE_WORD(d), TYPE_WORD(i), TYPE_WORD(s));
    CHECK(sizeof(__builtin_choose_expr(1, (char)0, 0.0)) == 1);
    DONE();
}
