/* The unnamed member can be named by its typedef name. */
#include <stdio.h>

typedef struct Lock { int key; int pc; } Lock;

struct Proc {
	int pid;
	Lock;
	char name[8];
};

int
main(void)
{
	struct Proc p = {0};
	p.pid = 7;
	p.key = 1;
	p.Lock.pc = 42;
	Lock copy = p.Lock;
	printf("%d %d %d %d\n", p.pid, p.key, copy.key, copy.pc);
	return 0;
}
