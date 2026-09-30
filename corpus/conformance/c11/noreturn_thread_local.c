// C11 _Noreturn and <stdnoreturn.h>, _Thread_local objects each thread has its own copy of, and
// the <threads.h> functions that start and join a thread.
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <threads.h>

static _Thread_local int counter = 10;

static noreturn void finish(int code)
{
    fflush(stdout);
    exit(code);
}

_Noreturn static void never(void) { abort(); }

static int worker(void *arg)
{
    counter += *(int *)arg;
    return counter;
}

int main(void)
{
    int add = 5;
    thrd_t t;
    int result = 0;
    if (thrd_create(&t, worker, &add) != thrd_success)
        return 1;
    thrd_join(t, &result);
    printf("%d %d\n", result, counter);
    counter = 1;
    printf("%d\n", counter);
    if (add == 0)
        never();
    finish(3);
}
