/* The INTEGER class for every scalar that has it: _Bool, the character and integer types,
 * enumerations and pointers. Twelve arguments, so the first six go in rdi, rsi, rdx, rcx, r8 and
 * r9 and the rest go on the stack in eightbyte slots, and each type is returned in rax. The
 * narrow types are passed with values whose top bit is set, so a half that reads more of a
 * register than the type has gets a different answer. */
#include "abi.h"

enum colour { RED = -3, GREEN = 7 };

void twelve(_Bool b, char c, signed char sc, unsigned char uc, short s, unsigned short us, int i,
            unsigned u, long l, unsigned long ul, long long ll, enum colour e);
void pointers(int *p, const char *s, void (*f)(void), int *q, int *r, int *t, int *x, char *y);
_Bool give_bool(int);
signed char give_schar(void);
unsigned char give_uchar(void);
short give_short(void);
unsigned short give_ushort(void);
int give_int(void);
unsigned give_uint(void);
long give_long(void);
enum colour give_enum(void);
int *give_pointer(int *);
long back(char c, short s, int i, long l, unsigned char uc, unsigned short us, _Bool b);
void callee_side(void);

#ifdef CALLEE
static int box[4] = { 10, 20, 30, 40 };

void twelve(_Bool b, char c, signed char sc, unsigned char uc, short s, unsigned short us, int i,
            unsigned u, long l, unsigned long ul, long long ll, enum colour e)
{
    printf("twelve %d %d %d %u %d %u %d %u %ld %lu %lld %d\n", b, c, sc, uc, s, us, i, u, l, ul,
           ll, e);
}

void pointers(int *p, const char *s, void (*f)(void), int *q, int *r, int *t, int *x, char *y)
{
    printf("pointers %d %s %d %d %d %d %d %s\n", *p, s, f != 0, *q, *r, *t, *x, y);
    f();
}

_Bool give_bool(int x) { return x; }
signed char give_schar(void) { return -100; }
unsigned char give_uchar(void) { return 200; }
short give_short(void) { return -30000; }
unsigned short give_ushort(void) { return 60000; }
int give_int(void) { return -2000000000; }
unsigned give_uint(void) { return 4000000000u; }
long give_long(void) { return -9000000000000000000L; }
enum colour give_enum(void) { return RED; }
int *give_pointer(int *p) { return p ? p + 1 : box + 2; }

#else
void hello(void) { printf("called back\n"); }

/* The other direction: the callee half calls this, so a run builds a call each way. */
long back(char c, short s, int i, long l, unsigned char uc, unsigned short us, _Bool b)
{
    printf("back %d %d %d %ld %u %u %d\n", c, s, i, l, uc, us, b);
    return l * 2 + c;
}

int main(void)
{
    int a = 1, q = 2, r = 3, t = 4, x = 5;
    char y[] = "last";
    twelve(1, -5, -128, 255, -32768, 65535, -2147483647 - 1, 4294967295u, -1L, 18446744073709551615ul,
           -9223372036854775807LL - 1, GREEN);
    twelve(0, 127, 127, 128, 32767, 32768, 2147483647, 2147483648u, 9223372036854775807L, 1ul,
           123456789012345LL, RED);
    pointers(&a, "text", hello, &q, &r, &t, &x, y);
    printf("bool %d %d\n", give_bool(0), give_bool(256));
    printf("schar %d uchar %u\n", give_schar(), give_uchar());
    printf("short %d ushort %u\n", give_short(), give_ushort());
    printf("int %d uint %u long %ld enum %d\n", give_int(), give_uint(), give_long(), give_enum());
    int row[3] = { 7, 8, 9 };
    printf("pointer %d %d\n", *give_pointer(0), *give_pointer(row));
    callee_side();
    return 0;
}
#endif

#ifdef CALLEE
void callee_side(void)
{
    printf("got %ld\n", back(-7, -300, -70000, 1L << 40, 250, 65000, 1));
}
#endif
