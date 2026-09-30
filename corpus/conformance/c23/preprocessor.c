// C23 preprocessing: #elifdef and #elifndef, __has_include, __VA_OPT__, #embed with a limit and
// __has_embed, and __STDC_VERSION__.
#include <stdio.h>

#define HAVE_ONE

#ifdef MISSING
#define WHICH "missing"
#elifdef HAVE_ONE
#define WHICH "elifdef"
#else
#define WHICH "else"
#endif

#ifdef HAVE_ONE
#define OTHER "first"
#elifndef MISSING
#define OTHER "elifndef"
#endif

#if __has_include(<stdio.h>) && !__has_include("no_such_header.h")
#define INCLUDES "has include"
#endif

#if __has_embed("preprocessor.c") == __STDC_EMBED_FOUND__ && __has_embed("no_such_file.bin") == __STDC_EMBED_NOT_FOUND__
#define EMBEDS "has embed"
#endif

#define LOG(fmt, ...) printf(fmt __VA_OPT__(,) __VA_ARGS__)
#define COUNT(...) (0 __VA_OPT__(+ 1))

int main(void)
{
    static const unsigned char self[] = {
#embed "preprocessor.c" limit(4)
    };
    printf("%s %s %s\n", WHICH, OTHER, INCLUDES);
    LOG("no arguments\n");
    LOG("%d %d\n", 1, 2);
    printf("%d %d\n", COUNT(), COUNT(a));
    printf("%zu %c%c\n", sizeof self, self[0], self[1]);
    printf("%s\n", EMBEDS);
    printf("%ld\n", __STDC_VERSION__);
    return 0;
}
