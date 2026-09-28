/* vector_size: a vector of the element type, as many bytes wide as named, with the arithmetic
 * operators applied element by element. */
#include "../check.h"

#if __has_attribute(vector_size)
#define HAS 1
#else
#define HAS 0
#endif

typedef int v4si __attribute__((vector_size(16)));
typedef float v4sf __attribute__((vector_size(16)));
typedef unsigned char v16qu __attribute__((vector_size(16)));

int main(void) {
    CLAIM("__has_attribute(vector_size)", HAS);
    v4si a = {1, 2, 3, 4};
    v4si b = {10, 20, 30, 40};
    v4si c = a + b;
    v4si d = b * a - a;
    CHECK(sizeof(v4si) == 16);
    CHECK(c[0] == 11 && c[1] == 22 && c[2] == 33 && c[3] == 44);
    CHECK(d[0] == 9 && d[3] == 156);
    v4si m = a > 2;
    CHECK(m[0] == 0 && m[1] == 0 && m[2] == -1 && m[3] == -1);
    v4sf f = {1.5f, 2.5f, 3.5f, 4.5f};
    v4sf g = f * 2.0f;
    CHECK(g[0] == 3.0f && g[3] == 9.0f);
    v16qu bytes = {0};
    bytes[15] = 255;
    bytes += 1;
    CHECK(bytes[0] == 1 && bytes[15] == 0);
    printf("c %d %d %d %d\n", c[0], c[1], c[2], c[3]);
    DONE();
}
