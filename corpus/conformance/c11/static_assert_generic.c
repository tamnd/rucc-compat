// C11 _Static_assert at file scope, in a block and in a structure, and _Generic selecting on the
// type of its controlling expression after lvalue conversion, with and without a default.
#include <stdio.h>
#include <assert.h>

_Static_assert(sizeof(int) >= 2, "int is at least sixteen bits");

struct holder {
    int value;
    _Static_assert(sizeof(int) == sizeof(unsigned), "the two have one size");
};

#define TYPE_NAME(x) _Generic((x), \
    int: "int", \
    unsigned: "unsigned", \
    long: "long", \
    double: "double", \
    char *: "char *", \
    const char *: "const char *", \
    default: "other")

#define ABS(x) _Generic((x), long: labs_, double: fabs_, default: abs_)(x)

static int abs_(int x) { return x < 0 ? -x : x; }
static long labs_(long x) { return x < 0 ? -x : x; }
static double fabs_(double x) { return x < 0 ? -x : x; }

int main(void)
{
    static_assert(1 + 1 == 2, "arithmetic");
    const int ci = 1;
    char text[] = "x";
    short s = 1;
    float f = 1.0f;
    struct holder h = { 3 };
    printf("%s %s %s %s\n", TYPE_NAME(1), TYPE_NAME(1u), TYPE_NAME(1L), TYPE_NAME(1.0));
    printf("%s %s %s\n", TYPE_NAME(ci), TYPE_NAME(text), TYPE_NAME("literal"));
    printf("%s %s %s\n", TYPE_NAME(s), TYPE_NAME(f), TYPE_NAME((const char *)text));
    printf("%s\n", TYPE_NAME(s + s));
    printf("%d %ld %g %d\n", ABS(-4), ABS(-5L), ABS(-2.5), h.value);
    printf("%d\n", _Generic(1, int: 10, default: 20) + _Generic('a', char: 1, int: 2));
    return 0;
}
