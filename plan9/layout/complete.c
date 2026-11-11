#include <u.h>
#include <libc.h>
#include <complete.h>

void
main(void)
{
	print("struct Completion %d\n", sizeof(struct Completion));
	print("struct Completion.advance %lud\n", offsetof(struct Completion, advance));
	print("struct Completion.complete %lud\n", offsetof(struct Completion, complete));
	print("struct Completion.string %lud\n", offsetof(struct Completion, string));
	print("struct Completion.nmatch %lud\n", offsetof(struct Completion, nmatch));
	print("struct Completion.nfile %lud\n", offsetof(struct Completion, nfile));
	print("struct Completion.filename %lud\n", offsetof(struct Completion, filename));
	exits(nil);
}
