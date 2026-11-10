/* The unnamed member can be a union named by a typedef. */
#include <stdio.h>

typedef union Word { unsigned int u; unsigned char b[4]; } Word;

struct Reg {
	int id;
	Word;
};

static unsigned int
low(Word *w)
{
	return w->u & 0xff;
}

int
main(void)
{
	struct Reg r;
	r.id = 1;
	r.u = 0x11223344;
	printf("%d %#x %u\n", r.id, r.u, low(&r));
	printf("%zu\n", sizeof r);
	return 0;
}
