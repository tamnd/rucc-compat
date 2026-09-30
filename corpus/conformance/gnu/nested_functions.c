/* Nested functions, which rucc turns down today, tamnd/rucc#2486. One is only called, so it
   needs a static chain and no trampoline, and one has its address taken, which is where GCC
   needs a trampoline. */
#include <stdio.h>

static int apply(int (*f)(int), int x) { return f(x); }

static int outer(int base)
{
    int calls = 0;
    int add(int x) { calls++; return base + x; }
    int direct = add(1) + add(2);
    int through = apply(add, 10);
    return direct * 100 + through + calls * 1000;
}

int main(void)
{
    printf("nested %d\n", outer(5));
    return 0;
}
