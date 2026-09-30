/* C89 preprocessing: conditional inclusion with #if, #ifdef, #ifndef, #elif and the defined
 * operator, arithmetic in #if, object-like and function-like macros, # and ##, rescanning, a macro
 * not expanding inside itself, #undef, #line, an unknown #pragma, and the predefined macros. */
#include <stdio.h>
#include <string.h>

#define ANSWER 42
#define SQUARE(x) ((x) * (x))
#define STR(x) #x
#define XSTR(x) STR(x)
#define CAT(a, b) a##b
#define EMPTY
#define APPLY(f, x) f(x)
#define TWICE(x) (2 * (x))

#if defined(ANSWER) && ANSWER > 40 && !defined NOT_DEFINED
#define CHOSEN "first"
#elif 1
#define CHOSEN "second"
#else
#define CHOSEN "third"
#endif

#ifdef SQUARE
#define HAVE_SQUARE 1
#endif
#ifndef HAVE_CUBE
#define HAVE_CUBE 0
#endif

#if (7 / 2) * 2 == 6 && (-1 < 0) && (0x10 | 1) == 17 && (1 ? 2 : 3) == 2
#define ARITH "ok"
#else
#define ARITH "wrong"
#endif

#pragma this_pragma_means_nothing

int main(void)
{
    int self = 1;
    int CAT(var, 1) = 3;
    printf("%d %d %d\n", ANSWER, SQUARE(3 + 1), SQUARE(ANSWER) / ANSWER);
    printf("%s %s %s\n", STR(ANSWER), XSTR(ANSWER), STR(a "b" 'c'));
#define self (self + 1)
    printf("%d %d\n", var1, self);
#undef self
    printf("%s %d %d %s\n", CHOSEN, HAVE_SQUARE, HAVE_CUBE, ARITH);
    printf("%d\n", APPLY(TWICE, 5) EMPTY);
#undef ANSWER
#ifndef ANSWER
    printf("undefined\n");
#endif
#line 500 "renamed.c"
    printf("%d %s\n", __LINE__, __FILE__);
    printf("%d %d\n", __STDC__, (int)strlen(__DATE__) + (int)strlen(__TIME__));
    return 0;
}
