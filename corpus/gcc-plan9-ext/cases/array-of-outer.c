/* The conversion works on an element of an array and through a pointer to the outer struct. */
#include <stdio.h>

typedef struct QLock { int locked; } QLock;

typedef struct Dev {
	QLock;
	int nr;
} Dev;

static void
qlock(QLock *q)
{
	q->locked = 1;
}

int
main(void)
{
	Dev d[3] = {{{0}, 10}, {{0}, 11}, {{0}, 12}};
	Dev *p = &d[2];
	qlock(&d[0]);
	qlock(p);
	printf("%d %d %d %d\n", d[0].locked, d[1].locked, d[2].locked, p->nr);
	return 0;
}
