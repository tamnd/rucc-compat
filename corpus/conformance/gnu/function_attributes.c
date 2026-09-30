/* The attributes written on functions. Most of them promise something about the function that
   a compiler may use or ignore, so the program checks that each is taken and that the calls
   still do what they say. */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static int hidden_calls;

__attribute__((noreturn)) static void stop(int code) { exit(code); }
__attribute__((always_inline)) static inline int add_one(int x) { return x + 1; }
extern inline __attribute__((gnu_inline, always_inline)) int add_two(int x) { return x + 2; }
__attribute__((noinline, noclone)) static int opaque(int x) { return x * 3; }
static int helper(int x) { return x - 1; }
__attribute__((flatten)) static int flat(int x) { return helper(x) + helper(x); }
__attribute__((hot)) static int often(int x) { return x + 5; }
__attribute__((cold)) static int rarely(int x) { return x - 5; }
__attribute__((pure)) static int peek(const int *p) { return *p; }
__attribute__((const)) static int cube(int x) { return x * x * x; }
__attribute__((malloc)) static void *grab(size_t n) { return malloc(n); }
__attribute__((malloc(free, 1))) static int *grab_int(void) { return malloc(sizeof(int)); }
__attribute__((alloc_size(1))) static void *sized(size_t n) { return malloc(n); }
__attribute__((returns_twice)) static int once_or_twice(void) { return 1; }
__attribute__((no_instrument_function)) static int plain(void) { return 6; }
__attribute__((no_profile_instrument_function)) static int unprofiled(void) { return 7; }
__attribute__((no_stack_protector)) static int unguarded(void) { char b[32]; b[0] = 8; return b[0]; }
__attribute__((stack_protect)) static int guarded(void) { char b[32]; b[0] = 9; return b[0]; }
__attribute__((function_return("keep"), indirect_branch("keep"))) static int kept(void) { return 10; }
__attribute__((zero_call_used_regs("used-gpr"))) static int scrubbed(int x) { return x + 11; }
__attribute__((target("sse2"))) static int targeted(int x) { return x + 12; }
__attribute__((target_clones("default", "sse4.2"))) int cloned(int x) { return x + 13; }
__attribute__((optimize("no-strict-aliasing"))) static int optimized(int x) { return x + 14; }
__attribute__((no_sanitize("address"))) static int unsanitized(int x) { return x + 15; }
__attribute__((used)) static int kept_for_asm(void) { return 16; }
__attribute__((unused)) static int never_called(void) { return 17; }
__attribute__((externally_visible)) int visible_to_all(void) { return 18; }
__attribute__((retain, used)) static int retained(void) { return 19; }
__attribute__((deprecated)) static int outdated(void) { return 20; }
__attribute__((deprecated("gone soon"))) static int outdated_too(void) { return 21; }
__attribute__((warning("called on purpose"))) static int warned(void) { return 22; }
__attribute__((error("never called"))) void refused(void);
__attribute__((format(printf, 1, 2))) static int report(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int n = vprintf(format, ap);
    va_end(ap);
    return n;
}
__attribute__((format_arg(1))) static const char *translate(const char *s) { return s; }
__attribute__((nonnull(1))) static int first(const int *p) { return p[0]; }
static int storage = 23;
__attribute__((returns_nonnull)) static int *somewhere(void) { return &storage; }
__attribute__((warn_unused_result)) static int checked(void) { return 24; }
__attribute__((sentinel)) static int until_null(const char *first_word, ...)
{
    va_list ap;
    int n = first_word != 0;
    va_start(ap, first_word);
    while (va_arg(ap, const char *))
        n++;
    va_end(ap);
    return n;
}
__attribute__((access(read_only, 1, 2))) static int total(const int *p, int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += p[i];
    return sum;
}
static _Alignas(64) char arena[64];
__attribute__((assume_aligned(64))) static void *aligned_arena(void) { return arena; }
__attribute__((noinline)) static int original(void) { return 25; }
__attribute__((copy(original))) static int copied(void) { return 26; }

static int fall(int n)
{
    int r = 0;
    switch (n) {
    case 0:
        r += 1;
        __attribute__((fallthrough));
    case 1:
        r += 2;
        break;
    }
    return r;
}

#if defined __x86_64__
__attribute__((naked)) static int naked_seven(void) { __asm__("movl $7, %eax\n\tret"); }
__attribute__((ms_abi)) static int ms_sum(int a, int b, int c, int d, int e) { return a + b + c + d + e; }
__attribute__((sysv_abi)) static int sysv_sum(int a, int b, int c, int d, int e) { return a + b + c + d + e; }
#elif defined __aarch64__
__attribute__((naked)) static int naked_seven(void) { __asm__("mov w0, #7\n\tret"); }
static int ms_sum(int a, int b, int c, int d, int e) { return a + b + c + d + e; }
static int sysv_sum(int a, int b, int c, int d, int e) { return a + b + c + d + e; }
#endif

int main(void)
{
    int x = 4;
    printf("inline %d %d %d\n", add_one(1), add_two(1), opaque(2));
    printf("flatten %d hot %d cold %d\n", flat(3), often(1), rarely(10));
    printf("pure %d const %d\n", peek(&x), cube(3));
    void *a = grab(8);
    int *b = grab_int();
    void *c = sized(16);
    printf("malloc %d %d %d\n", a != 0, b != 0, c != 0);
    free(a);
    free(b);
    free(c);
    printf("returns_twice %d\n", once_or_twice());
    printf("instrument %d %d\n", plain(), unprofiled());
    printf("stack protector %d %d\n", unguarded(), guarded());
    printf("hardening %d %d\n", kept(), scrubbed(0));
    printf("target %d %d optimize %d sanitize %d\n", targeted(0), cloned(0), optimized(0), unsanitized(0));
    printf("used %d visible %d retain %d\n", kept_for_asm(), visible_to_all(), retained());
    printf("deprecated %d %d warning %d\n", outdated(), outdated_too(), warned());
    report("format %s %d\n", translate("ok"), 1);
    printf("nonnull %d %d\n", first(&x), *somewhere());
    printf("unused result %d\n", checked());
    printf("sentinel %d\n", until_null("a", "b", "c", (char *)0));
    int values[] = { 1, 2, 3 };
    printf("access %d\n", total(values, 3));
    printf("assume_aligned %d\n", aligned_arena() == arena);
    printf("copy %d %d\n", original(), copied());
    printf("fallthrough %d %d\n", fall(0), fall(1));
    printf("naked %d abi %d %d\n", naked_seven(), ms_sum(1, 2, 3, 4, 5), sysv_sum(1, 2, 3, 4, 5));
    fflush(stdout);
    stop(hidden_calls);
}
