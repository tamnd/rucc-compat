#include <dlfcn.h>
#include <stdio.h>
int main(void) {
  void *h = dlopen("./libbig.so", RTLD_NOW);
  if (!h) { puts(dlerror()); return 1; }
  int (*f)(int) = (int (*)(int))dlsym(h, "touch");
  printf("ok %d\n", f(5));
  return 0;
}
