/* The attributes that decide where a definition goes and how the link sees it, and the ones
   that run code on the way into and out of a scope or a program. */
#include <stdio.h>

static int order[8];
static int seen;

__attribute__((constructor)) static void early(void) { order[seen++] = 1; }
__attribute__((constructor(200))) static void earlier(void) { order[seen++] = 2; }
__attribute__((destructor)) static void late(void) { printf("destructor ran\n"); }

__attribute__((section(".data.conformance"))) int placed = 5;
__attribute__((visibility("hidden"))) int unseen = 6;
__attribute__((visibility("default"))) int shown = 7;
__attribute__((nocommon)) int never_common;

int real_answer(void) { return 42; }
int aliased_answer(void) __attribute__((alias("real_answer")));
extern int nobody_defines_this(void) __attribute__((weak));
__attribute__((weak)) int overridable(void) { return 8; }

static void release(int *p) { order[seen++] = *p; }

static void scoped(void)
{
    int first __attribute__((cleanup(release))) = 30;
    int second __attribute__((cleanup(release))) = 40;
    (void)first;
    (void)second;
}

int main(void)
{
    printf("constructors %d %d %d\n", seen, order[0], order[1]);
    scoped();
    printf("cleanup %d %d\n", order[2], order[3]);
    printf("section %d visibility %d %d common %d\n", placed, unseen, shown, never_common);
    printf("alias %d weak %d %d\n", aliased_answer(), nobody_defines_this == 0, overridable());
    return 0;
}
