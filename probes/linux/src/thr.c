#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
_Atomic long counter; _Thread_local int mine;
struct big { long a, b; }; _Atomic struct big b16;
void *work(void *p) { for (int i = 0; i < 100000; i++) { atomic_fetch_add(&counter, 1); mine++; } return 0; }
int main(void) { pthread_t t[4]; for (int i = 0; i < 4; i++) pthread_create(&t[i], 0, work, 0);
  for (int i = 0; i < 4; i++) pthread_join(t[i], 0);
  struct big v = {1, 2}; atomic_store(&b16, v); struct big w = atomic_load(&b16);
  unsigned __int128 q = ((unsigned __int128)1 << 100) / 12345; printf("counter=%ld mine=%d w=%ld,%ld q=%llu\n", (long)counter, mine, w.a, w.b, (unsigned long long)(q >> 64)); return 0; }
