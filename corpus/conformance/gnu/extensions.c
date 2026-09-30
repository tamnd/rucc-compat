/* The language extensions GCC documents under "Extensions to the C Language Family" that change
   what a program can say, each used the way real code uses it. Nested functions are not here,
   since rucc turns them down on purpose. */
#include <stdio.h>

int renamed(void) __asm__("the_renamed_function");
int renamed(void) { return 11; }
extern int by_symbol(void) __asm__("the_renamed_function");

static int calls;
static int next(void) { return ++calls; }

struct packet { int length; unsigned char bytes[0]; };
union number { int i; double d; };
static int take(union number n) { return n.i; }

static int ranks[10] = { [0 ... 4] = 1, [5 ... 9] = 2, [7] = 3 };

static const char *kind(int c)
{
    switch (c) {
    case '0' ... '9': return "digit";
    case 'a' ... 'z': case 'A' ... 'Z': return "letter";
    default: return "other";
    }
}

static int run(int n)
{
    static void *const steps[] = { &&zero, &&one, &&two };
    int total = 0;
    goto *steps[n];
zero:
    total += 1;
one:
    total += 10;
two:
    total += 100;
    return total;
}

int main(void)
{
    int squared = ({ int x = 7; x * x; });
    typeof(squared) copy = squared;
    __typeof__(int *) where = &copy;
    typeof_unqual(const int) loose = 3;
    loose += 1;
    printf("statement expression %d %d %d\n", squared, *where, loose);
    printf("asm label %d %d\n", renamed(), by_symbol());
    printf("labels as values %d %d %d\n", run(0), run(1), run(2));
    printf("case ranges %s %s %s\n", kind('5'), kind('q'), kind('#'));
    int got = next() ?: 99;
    int zero = 0;
    int fell = zero ?: 42;
    printf("binary conditional %d %d %d\n", got, calls, fell);
    printf("zero length %d\n", (int)(sizeof(struct packet) == sizeof(int)));
    char buffer[8];
    void *p = buffer;
    p += 3;
    printf("void pointer %d %d\n", (int)((char *)p - buffer), (int)sizeof(void));
    printf("ranges %d %d %d %d\n", ranks[0], ranks[4], ranks[7], ranks[9]);
    printf("cast to union %d\n", take((union number)5));
    __extension__ long long wide = 1LL << 40;
    printf("extension %d\n", (int)(wide >> 40));
    return 0;
}
