// C23 typeof, typeof_unqual and auto: the type of an expression or a type name, the second
// without its qualifiers, and auto taking the type of an object's initializer.
#include <stdio.h>

int main(void)
{
    const int c = 5;
    typeof(c) d = 6;
    typeof_unqual(c) e = 7;
    e += 1;
    typeof(int[3]) arr = { 1, 2, 3 };
    typeof(arr[0] * 2.0) f = 1.5;
    auto g = 10L;
    auto h = 'x';
    auto k = 1.0f;
    printf("%d %d %zu %g\n", d, e, sizeof arr, f);
    printf("%zu %zu %zu\n", sizeof g, sizeof h, sizeof k);
    printf("%d %d\n", _Generic(g, long: 1, default: 0), _Generic(e, int: 1, default: 0));
    typeof(char *) s = "typed";
    printf("%s\n", s);
    return 0;
}
