/* A struct can have more than one unnamed member, and each pointer conversion takes the one
   with the type it needs. */
#include <stdio.h>

typedef struct A { int a; } A;
typedef struct B { int b; } B;

struct C {
	A;
	int mid;
	B;
};

static int geta(A *p) { return p->a; }
static int getb(B *p) { return p->b; }

int
main(void)
{
	struct C c = {{1}, 2, {3}};
	printf("%d %d %d\n", geta(&c), c.mid, getb(&c));
	printf("%d\n", (int)((char *)(B *)&c.B - (char *)&c));
	return 0;
}
