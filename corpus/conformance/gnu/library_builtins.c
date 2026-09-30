/* The library functions GCC also knows as builtins, called by their __builtin_ names, which is
   how glibc's headers and the fortify wrappers reach them. A builtin either folds or becomes a
   call to the function of the same name, and the answers are the same either way. */
#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int chk_vprintf(const char *format, ...)
{
    va_list ap;
    char small[32], sized[32];
    va_start(ap, format);
    int n = __builtin___vsprintf_chk(small, 0, sizeof small, format, ap);
    va_end(ap);
    va_start(ap, format);
    __builtin___vsnprintf_chk(sized, sizeof sized, 0, sizeof sized, format, ap);
    va_end(ap);
    va_start(ap, format);
    __builtin___vprintf_chk(0, format, ap);
    va_end(ap);
    va_start(ap, format);
    __builtin_vprintf(format, ap);
    va_end(ap);
    va_start(ap, format);
    __builtin_vfprintf(stdout, format, ap);
    va_end(ap);
    va_start(ap, format);
    __builtin_vsprintf(small, format, ap);
    va_end(ap);
    va_start(ap, format);
    __builtin_vsnprintf(sized, 4, format, ap);
    va_end(ap);
    __builtin_printf("vchk %d %s %s\n", n, small, sized);
    return n;
}

int main(void)
{
    if (__builtin_strlen("") != 0)
        __builtin_abort();
    char *m = __builtin_malloc(16);
    int *z = __builtin_calloc(4, sizeof(int));
    m = __builtin_realloc(m, 32);
    __builtin_printf("alloc %d %d\n", m != 0, z[3]);
    __builtin_free(z);
    __builtin_printf("abs %d %ld %lld %jd\n", __builtin_abs(-3), __builtin_labs(-4L), __builtin_llabs(-5LL), (intmax_t)__builtin_imaxabs(-6));
    char a[32], b[32];
    __builtin_memset(a, 'a', sizeof a);
    __builtin_memcpy(b, "hello world", 12);
    __builtin_memmove(b + 1, b, 5);
    __builtin_printf("mem %s %d %d %.4s\n", b, __builtin_memcmp("abc", "abd", 3) < 0, (int)((char *)__builtin_memchr(b, 'w', 12) - b), (char *)__builtin_mempcpy(a, "xy", 2) - 2);
    __builtin_bcopy("bc", a, 2);
    __builtin_bzero(a + 2, 30);
    __builtin_printf("bsd %s %s %s\n", a, __builtin_index("path/to/file", '/'), __builtin_rindex("path/to/file", '/'));
    __builtin_printf("strcmp %d %d %d\n", __builtin_strlen("four"), __builtin_strcmp("a", "b") < 0, __builtin_strncmp("abcd", "abce", 3));
    __builtin_strcpy(a, "one");
    __builtin_strcat(a, "two");
    __builtin_strncat(a, "three", 2);
    __builtin_strncpy(b, "pad", 8);
    __builtin_printf("strcpy %s %s %d\n", a, b, b[7]);
    char *end = __builtin_stpcpy(a, "abc");
    end = __builtin_stpncpy(end, "def", 2);
    *end = 0;
    __builtin_printf("stpcpy %s\n", a);
    const char *s = "key=value;rest";
    __builtin_printf("search %s %s %s %d %d %s\n", __builtin_strchr(s, '='), __builtin_strrchr(s, 'e'), __builtin_strstr(s, "val"), (int)__builtin_strspn(s, "key"), (int)__builtin_strcspn(s, ";"), __builtin_strpbrk(s, ";="));
    char *d = __builtin_strdup("copy"), *nd = __builtin_strndup("copy", 2);
    __builtin_printf("strdup %s %s\n", d, nd);
    free(d);
    free(nd);
    char out[64];
    __builtin_sprintf(out, "%d-%s", 7, "x");
    __builtin_snprintf(out + 3, 4, "%s", "truncated");
    __builtin_puts(out);
    __builtin_putchar('p');
    __builtin_putchar('\n');
    __builtin_fprintf(stdout, "fprintf %d\n", 1);
    /* glibc has no fprintf_unlocked, printf_unlocked or puts_unlocked, so these are only ever
       asked about, which is what a header does before it uses one. */
    __builtin_printf("unlocked %d %d %d\n", __has_builtin(__builtin_fprintf_unlocked), __has_builtin(__builtin_printf_unlocked), __has_builtin(__builtin_puts_unlocked));
    __builtin_fputs("fputs\n", stdout);
    __builtin_fputs_unlocked("fputs_unlocked\n", stdout);
    __builtin_fputc('c', stdout);
    __builtin_fputc_unlocked('u', stdout);
    __builtin_putc('p', stdout);
    __builtin_putc_unlocked('q', stdout);
    __builtin_putchar_unlocked('\n');
    __builtin_fwrite("fwrite\n", 1, 7, stdout);
    __builtin_fwrite_unlocked("fwrite_unlocked\n", 1, 16, stdout);
    char buf[16];
    __builtin___memcpy_chk(buf, "0123456789", 11, __builtin_object_size(buf, 0));
    __builtin___memmove_chk(buf + 1, buf, 4, __builtin_object_size(buf + 1, 0));
    char *after = __builtin___mempcpy_chk(buf, "ab", 2, __builtin_object_size(buf, 0));
    __builtin___memset_chk(after, 'z', 2, __builtin_object_size(after, 0));
    __builtin_printf("chk mem %s\n", buf);
    __builtin___strcpy_chk(buf, "st", sizeof buf);
    __builtin___strcat_chk(buf, "ring", sizeof buf);
    __builtin___strncat_chk(buf, "!!!", 1, sizeof buf);
    __builtin_printf("chk str %s\n", buf);
    char *e = __builtin___stpcpy_chk(buf, "ab", sizeof buf);
    __builtin___stpncpy_chk(e, "cdef", 5, sizeof buf - 2);
    __builtin___strncpy_chk(buf + 4, "XY", 2, sizeof buf - 4);
    __builtin_printf("chk stp %s\n", buf);
    __builtin___sprintf_chk(out, 0, sizeof out, "%s:%d", "s", 1);
    __builtin___snprintf_chk(out + 3, 8, 0, sizeof out - 3, "%d", 22);
    __builtin___printf_chk(0, "chk printf %s\n", out);
    chk_vprintf("%s/%d", "v", 3);
    __builtin_putchar('\n');
    free(m);
    fflush(stdout);
    __builtin_exit(0);
}
