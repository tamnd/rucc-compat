/* The conversion is done in an assignment, an initializer and a return statement too. */
#include <stdio.h>

typedef struct Ref { long n; } Ref;

typedef struct Chan {
	char tag[3];
	Ref;
	int mode;
} Chan;

static Ref *
ref(Chan *c)
{
	return c;
}

int
main(void)
{
	Chan c = {"ab", {3}, 1};
	Ref *a = &c;
	Ref *b;
	b = &c;
	ref(&c)->n += 4;
	printf("%ld %ld %d\n", a->n, b->n, a == b && b == ref(&c));
	return 0;
}
