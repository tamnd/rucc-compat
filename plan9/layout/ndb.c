#include <u.h>
#include <libc.h>
#include <bio.h>
#include <ndb.h>

void
main(void)
{
	print("struct Ndb %d\n", sizeof(struct Ndb));
	print("struct Ndb.next %lud\n", offsetof(struct Ndb, next));
	print("struct Ndb.b %lud\n", offsetof(struct Ndb, b));
	print("struct Ndb.buf %lud\n", offsetof(struct Ndb, buf));
	print("struct Ndb.mtime %lud\n", offsetof(struct Ndb, mtime));
	print("struct Ndb.qid %lud\n", offsetof(struct Ndb, qid));
	print("struct Ndb.file %lud\n", offsetof(struct Ndb, file));
	print("struct Ndb.length %lud\n", offsetof(struct Ndb, length));
	print("struct Ndb.nohash %lud\n", offsetof(struct Ndb, nohash));
	print("struct Ndb.hf %lud\n", offsetof(struct Ndb, hf));
	print("struct Ndb.ncache %lud\n", offsetof(struct Ndb, ncache));
	print("struct Ndb.cache %lud\n", offsetof(struct Ndb, cache));
	print("struct Ndbtuple %d\n", sizeof(struct Ndbtuple));
	print("struct Ndbtuple.attr %lud\n", offsetof(struct Ndbtuple, attr));
	print("struct Ndbtuple.val %lud\n", offsetof(struct Ndbtuple, val));
	print("struct Ndbtuple.entry %lud\n", offsetof(struct Ndbtuple, entry));
	print("struct Ndbtuple.line %lud\n", offsetof(struct Ndbtuple, line));
	print("struct Ndbtuple.ptr %lud\n", offsetof(struct Ndbtuple, ptr));
	print("struct Ndbtuple.valbuf %lud\n", offsetof(struct Ndbtuple, valbuf));
	print("struct Ndbs %d\n", sizeof(struct Ndbs));
	print("struct Ndbs.db %lud\n", offsetof(struct Ndbs, db));
	print("struct Ndbs.hf %lud\n", offsetof(struct Ndbs, hf));
	print("struct Ndbs.type %lud\n", offsetof(struct Ndbs, type));
	print("struct Ndbs.ptr %lud\n", offsetof(struct Ndbs, ptr));
	print("struct Ndbs.ptr1 %lud\n", offsetof(struct Ndbs, ptr1));
	print("struct Ndbs.t %lud\n", offsetof(struct Ndbs, t));
	exits(nil);
}
