#define _GNU_SOURCE
#include <math.h>
#include <stdio.h>
int main(void) {
  _Float128 x = nanf128("");
  _Float128 h = HUGE_VAL_F128;
  printf("%d %d\n", x != x, h > 1);
  return 0;
}
