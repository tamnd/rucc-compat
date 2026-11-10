/* -fplan9-extensions turns on -fms-extensions, so a member that is only a struct tag is an
   unnamed member too. */
#include <stdio.h>

struct Head { int len; int cap; };

struct Buf {
	struct Head;
	char data[16];
};

int
main(void)
{
	struct Buf b = {{3, 16}, "abc"};
	b.len++;
	printf("%d %d %s\n", b.len, b.cap, b.data);
	return 0;
}
