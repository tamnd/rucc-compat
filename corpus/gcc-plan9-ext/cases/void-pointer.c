/* A pointer to void and a pointer to the outer struct itself still convert as in C. */
#include <stdio.h>

typedef struct Ref { int n; } Ref;
typedef struct Obj { Ref; int v; } Obj;

static void *
same(void *p)
{
	return p;
}

int
main(void)
{
	Obj o = {{1}, 2};
	Obj *p = same(&o);
	Ref *r = p;
	printf("%d %d %d\n", p->v, r->n, (void *)r == (void *)&o);
	return 0;
}
