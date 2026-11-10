/* An unnamed member of an unnamed member is reached by name through both. */
#include <stdio.h>

typedef struct Inner { int i; } Inner;
typedef struct Middle { Inner; int m; } Middle;

struct Outer {
	int o;
	Middle;
};

static int middle(Middle *p) { return p->i + p->m; }

int
main(void)
{
	struct Outer x;
	x.o = 1;
	x.i = 2;
	x.m = 3;
	printf("%d %d %d %d\n", x.o, x.i, x.m, middle(&x));
	return 0;
}
