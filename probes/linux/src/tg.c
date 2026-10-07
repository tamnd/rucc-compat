#include <tgmath.h>
#include <stdio.h>
int main(void) {
  float f = 2;
  double d = 2;
  printf("%g %g\n", sqrt(f), sqrt(d));
  return sizeof(sqrt(f)) == 4 ? 0 : 1;
}
