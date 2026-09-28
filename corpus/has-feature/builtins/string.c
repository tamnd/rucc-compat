/* The string and memory builtins, which are the library functions under another name, folded
 * where the arguments allow and called where they do not. glibc's fortify headers reach the _chk
 * forms. */
#include <string.h>
#include "../check.h"

#if __has_builtin(__builtin_memcpy)
#define HAS_0 1
#else
#define HAS_0 0
#endif
#if __has_builtin(__builtin_memset)
#define HAS_1 1
#else
#define HAS_1 0
#endif
#if __has_builtin(__builtin_memcmp)
#define HAS_2 1
#else
#define HAS_2 0
#endif
#if __has_builtin(__builtin_memmove)
#define HAS_3 1
#else
#define HAS_3 0
#endif
#if __has_builtin(__builtin_memchr)
#define HAS_4 1
#else
#define HAS_4 0
#endif
#if __has_builtin(__builtin_strlen)
#define HAS_5 1
#else
#define HAS_5 0
#endif
#if __has_builtin(__builtin_strcmp)
#define HAS_6 1
#else
#define HAS_6 0
#endif
#if __has_builtin(__builtin_strncmp)
#define HAS_7 1
#else
#define HAS_7 0
#endif
#if __has_builtin(__builtin_strcpy)
#define HAS_8 1
#else
#define HAS_8 0
#endif
#if __has_builtin(__builtin_strchr)
#define HAS_9 1
#else
#define HAS_9 0
#endif
#if __has_builtin(__builtin_strrchr)
#define HAS_10 1
#else
#define HAS_10 0
#endif
#if __has_builtin(__builtin_strstr)
#define HAS_11 1
#else
#define HAS_11 0
#endif
#if __has_builtin(__builtin_snprintf)
#define HAS_12 1
#else
#define HAS_12 0
#endif
#if __has_builtin(__builtin___memcpy_chk)
#define HAS_13 1
#else
#define HAS_13 0
#endif
#if __has_builtin(__builtin___snprintf_chk)
#define HAS_14 1
#else
#define HAS_14 0
#endif

int main(void) {
    CLAIM("__has_builtin(__builtin_memcpy)", HAS_0);
    CLAIM("__has_builtin(__builtin_memset)", HAS_1);
    CLAIM("__has_builtin(__builtin_memcmp)", HAS_2);
    CLAIM("__has_builtin(__builtin_memmove)", HAS_3);
    CLAIM("__has_builtin(__builtin_memchr)", HAS_4);
    CLAIM("__has_builtin(__builtin_strlen)", HAS_5);
    CLAIM("__has_builtin(__builtin_strcmp)", HAS_6);
    CLAIM("__has_builtin(__builtin_strncmp)", HAS_7);
    CLAIM("__has_builtin(__builtin_strcpy)", HAS_8);
    CLAIM("__has_builtin(__builtin_strchr)", HAS_9);
    CLAIM("__has_builtin(__builtin_strrchr)", HAS_10);
    CLAIM("__has_builtin(__builtin_strstr)", HAS_11);
    CLAIM("__has_builtin(__builtin_snprintf)", HAS_12);
    CLAIM("__has_builtin(__builtin___memcpy_chk)", HAS_13);
    CLAIM("__has_builtin(__builtin___snprintf_chk)", HAS_14);
    char a[32], b[32];
    volatile int n = 6;
    __builtin_memset(a, 0, sizeof a);
    __builtin_memcpy(a, "hello world", 12);
    CHECK(__builtin_strlen(a) == 11);
    CHECK(__builtin_strlen("constant") == 8);
    __builtin_memmove(a + 2, a, n);
    CHECK(__builtin_memcmp(a, "hehello rld", 11) == 0);
    CHECK(__builtin_memchr(a, 'o', 11) == a + 6);
    __builtin_strcpy(b, "abcabc");
    CHECK(__builtin_strcmp(b, "abcabc") == 0 && __builtin_strcmp(b, "abd") < 0);
    CHECK(__builtin_strncmp(b, "abcx", 3) == 0);
    CHECK(__builtin_strchr(b, 'c') == b + 2 && __builtin_strrchr(b, 'c') == b + 5);
    CHECK(__builtin_strstr(b, "cab") == b + 2 && __builtin_strstr(b, "zz") == 0);
    CHECK(__builtin_snprintf(b, sizeof b, "%d-%s", 42, "x") == 4 && __builtin_strcmp(b, "42-x") == 0);
    __builtin___memcpy_chk(b, "chk", 4, __builtin_object_size(b, 0));
    CHECK(__builtin_strcmp(b, "chk") == 0);
    CHECK(__builtin___snprintf_chk(b, sizeof b, 1, sizeof b, "%03d", 7) == 3 && __builtin_strcmp(b, "007") == 0);
    printf("%s|%s\n", a, b);
    DONE();
}
