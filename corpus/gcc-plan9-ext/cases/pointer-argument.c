/* A pointer to the outer struct converts to a pointer to the type of the unnamed member, as
   in a call to lock(&p) in the Plan 9 kernel. */
#include <stdio.h>

typedef struct Lock { int key; } Lock;

struct Proc {
	int pid;
	Lock;
	int state;
};

static void
lock(Lock *l)
{
	l->key++;
}

static int
held(const Lock *l)
{
	return l->key;
}

int
main(void)
{
	struct Proc p = {5, {0}, 9};
	lock(&p);
	lock(&p);
	printf("%d %d %d\n", held(&p), p.pid, p.state);
	printf("%d\n", (int)((char *)(Lock *)&p.Lock - (char *)&p));
	return 0;
}
