#include <stdio.h>
#include <dlfcn.h>
extern int lib_add(int); extern int lib_data; extern __thread int tls_counter;
int main(void) { printf("lib_add=%d data=%d tls=%d\n", lib_add(1), lib_data, tls_counter);
  void *h = dlopen("./libfoo.so", RTLD_NOW); if (!h) { puts(dlerror()); return 1; }
  int (*f)(int) = (int (*)(int))dlsym(h, "lib_add"); printf("dlsym=%d\n", f(2)); return 0; }
