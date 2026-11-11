#include <u.h>
#include <libc.h>
#include <json.h>

void
main(void)
{
	print("struct JSONEl %d\n", sizeof(struct JSONEl));
	print("struct JSONEl.name %lud\n", offsetof(struct JSONEl, name));
	print("struct JSONEl.val %lud\n", offsetof(struct JSONEl, val));
	print("struct JSONEl.next %lud\n", offsetof(struct JSONEl, next));
	print("struct JSON %d\n", sizeof(struct JSON));
	print("struct JSON.t %lud\n", offsetof(struct JSON, t));
	print("struct JSON.n %lud\n", offsetof(struct JSON, n));
	print("struct JSON.s %lud\n", offsetof(struct JSON, s));
	print("struct JSON.first %lud\n", offsetof(struct JSON, first));
	exits(nil);
}
