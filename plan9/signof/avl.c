#include <u.h>
#include <libc.h>
#include <avl.h>

void
main(void)
{
	print("Avl %.8lux\n", signof(Avl));
	print("Avltree %.8lux\n", signof(Avltree));
	print("struct Avl %.8lux\n", signof(struct Avl));
	print("struct Avltree %.8lux\n", signof(struct Avltree));
	print("avlinit %.8lux\n", signof avlinit);
	print("avlcreate %.8lux\n", signof avlcreate);
	print("avllookup %.8lux\n", signof avllookup);
	print("avldelete %.8lux\n", signof avldelete);
	print("avlinsert %.8lux\n", signof avlinsert);
	print("avlmin %.8lux\n", signof avlmin);
	print("avlmax %.8lux\n", signof avlmax);
	print("avlnext %.8lux\n", signof avlnext);
	print("avlprev %.8lux\n", signof avlprev);
	exits(nil);
}
