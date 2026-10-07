#include <stdio.h>
struct point { int x, y; };
static int sum(struct point *p, int n) { int s = 0; for (int i = 0; i < n; i++) s += p[i].x * p[i].y; return s; }
int main(void) { struct point pts[3] = {{1,2},{3,4},{5,6}}; printf("%d\n", sum(pts, 3)); return 0; }
