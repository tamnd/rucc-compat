#include <u.h>
#include <libc.h>
#include <geometry.h>

void
main(void)
{
	print("struct Point2 %d\n", sizeof(struct Point2));
	print("struct Point2.x %lud\n", offsetof(struct Point2, x));
	print("struct Point2.y %lud\n", offsetof(struct Point2, y));
	print("struct Point2.w %lud\n", offsetof(struct Point2, w));
	print("struct Point3 %d\n", sizeof(struct Point3));
	print("struct Point3.x %lud\n", offsetof(struct Point3, x));
	print("struct Point3.y %lud\n", offsetof(struct Point3, y));
	print("struct Point3.z %lud\n", offsetof(struct Point3, z));
	print("struct Point3.w %lud\n", offsetof(struct Point3, w));
	print("struct Quaternion %d\n", sizeof(struct Quaternion));
	print("struct Quaternion.r %lud\n", offsetof(struct Quaternion, r));
	print("struct Quaternion.i %lud\n", offsetof(struct Quaternion, i));
	print("struct Quaternion.j %lud\n", offsetof(struct Quaternion, j));
	print("struct Quaternion.k %lud\n", offsetof(struct Quaternion, k));
	print("struct RFrame %d\n", sizeof(struct RFrame));
	print("struct RFrame.p %lud\n", offsetof(struct RFrame, p));
	print("struct RFrame.bx %lud\n", offsetof(struct RFrame, bx));
	print("struct RFrame.by %lud\n", offsetof(struct RFrame, by));
	print("struct RFrame3 %d\n", sizeof(struct RFrame3));
	print("struct RFrame3.p %lud\n", offsetof(struct RFrame3, p));
	print("struct RFrame3.bx %lud\n", offsetof(struct RFrame3, bx));
	print("struct RFrame3.by %lud\n", offsetof(struct RFrame3, by));
	print("struct RFrame3.bz %lud\n", offsetof(struct RFrame3, bz));
	exits(nil);
}
