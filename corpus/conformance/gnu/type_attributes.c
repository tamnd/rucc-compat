/* The attributes that change how data is laid out or what a type means, checked through sizes,
   offsets and bytes, which is where getting them wrong shows. */
#include <stddef.h>
#include <stdio.h>
#include <string.h>

struct __attribute__((packed)) tight { char c; int i; short s; };
struct loose { char c; int i __attribute__((aligned(16))); };
typedef int wide_aligned __attribute__((aligned(32)));
struct __attribute__((scalar_storage_order("big-endian"))) network { unsigned short port; unsigned int address; };
typedef int int8 __attribute__((mode(QI)));
typedef unsigned int word __attribute__((mode(DI)));
typedef int v4si __attribute__((vector_size(16)));
typedef int aliasing __attribute__((may_alias));
struct __attribute__((designated_init)) point { int x, y; };

union __attribute__((transparent_union)) either { int *ip; long *lp; };
static int deref(union either e) { return *e.ip; }

struct buffer { int count; int items[] __attribute__((counted_by(count))); };

int main(void)
{
    printf("packed %d %d %d\n", (int)sizeof(struct tight), (int)offsetof(struct tight, i), (int)offsetof(struct tight, s));
    printf("aligned %d %d %d\n", (int)sizeof(struct loose), (int)offsetof(struct loose, i), (int)_Alignof(wide_aligned));
    struct network n = { 0x1234, 0x0a000001 };
    unsigned char raw[sizeof n];
    memcpy(raw, &n, sizeof n);
    printf("storage order %02x %02x %02x %02x\n", raw[0], raw[1], raw[offsetof(struct network, address)], raw[offsetof(struct network, address) + 3]);
    printf("storage order read %x %x\n", (unsigned)n.port, n.address);
    printf("mode %d %d\n", (int)sizeof(int8), (int)sizeof(word));
    v4si a = { 1, 2, 3, 4 }, b = { 10, 20, 30, 40 };
    v4si c = a + b * 2;
    printf("vector %d %d %d %d %d\n", (int)sizeof(v4si), c[0], c[1], c[2], c[3]);
    float f = 1.0f;
    aliasing *bits = (aliasing *)&f;
    printf("may_alias %x\n", (unsigned)*bits);
    struct point p = { .y = 2, .x = 1 };
    printf("designated %d %d\n", p.x, p.y);
    int value = 17;
    printf("transparent union %d\n", deref(&value));
    char tag[4] __attribute__((nonstring)) = "abcd";
    printf("nonstring %c%c\n", tag[0], tag[3]);
    int later __attribute__((uninitialized));
    later = 5;
    printf("uninitialized %d\n", later);
    static struct { struct buffer b; int storage[3]; } pool = { { 3 }, { 7, 8, 9 } };
    printf("counted_by %d %d\n", pool.b.count, pool.b.items[2]);
    return 0;
}
