#include <u.h>
#include <libc.h>
#include <avl.h>

void
main(void)
{
	print("struct Avl %d\n", sizeof(struct Avl));
	print("struct Avl.c %lud\n", offsetof(struct Avl, c));
	print("struct Avl.p %lud\n", offsetof(struct Avl, p));
	print("struct Avl.balance %lud\n", offsetof(struct Avl, balance));
	print("struct Avltree %d\n", sizeof(struct Avltree));
	print("struct Avltree.cmp %lud\n", offsetof(struct Avltree, cmp));
	print("struct Avltree.root %lud\n", offsetof(struct Avltree, root));
	exits(nil);
}
