/* A member that is only a typedef name of a struct is an unnamed member, and its fields are
   fields of the outer struct. */
#include <stdio.h>

typedef struct Point { int x, y; } Point;

struct Rect {
	Point;
	int w, h;
};

int
main(void)
{
	struct Rect r = {{1, 2}, 3, 4};
	r.x += 10;
	printf("%d %d %d %d\n", r.x, r.y, r.w, r.h);
	printf("%zu %zu\n", sizeof r, sizeof(Point));
	return 0;
}
