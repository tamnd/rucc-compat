// C99 odds and ends: an array parameter with qualifiers and static in its brackets, a trailing
// comma in an enumeration, an implicit return of zero from main, a universal character name in
// a string, and the snprintf and vsnprintf functions the headers now declare.
#include <stdio.h>
#include <string.h>

enum level { LOW, MID, HIGH, };

static int first(const int v[const static 2]) { return v[0] + v[1]; }

int main(void)
{
    int pair[2] = { 5, 6 };
    char small[4];
    int wanted = snprintf(small, sizeof small, "%d", 123456);
    printf("%d %s %d\n", first(pair), small, wanted);
    printf("%d\n", HIGH);
    const char *u = "\u00e9";
    printf("%zu %d %d\n", strlen(u), (unsigned char)u[0], (unsigned char)u[1]);
}
