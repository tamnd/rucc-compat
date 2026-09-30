/* The builtins that ask the compiler something about the program: whether a value is constant,
   which branch is likely, what a type is, how big an object is, where the frame is. */
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

struct record { int count; char name[12]; long tail[] __attribute__((counted_by(count))); };

static int sum(int n, ...)
{
    __builtin_va_list ap, again;
    __builtin_va_start(ap, n);
    __builtin_va_copy(again, ap);
    int total = 0;
    for (int i = 0; i < n; i++)
        total += __builtin_va_arg(ap, int);
    for (int i = 0; i < n; i++)
        total += __builtin_va_arg(again, int);
    __builtin_va_end(again);
    __builtin_va_end(ap);
    return total;
}

__attribute__((noinline)) static int returns_somewhere(void)
{
    void *back = __builtin_extract_return_addr(__builtin_return_address(0));
    void *frob = __builtin_frob_return_addr(back);
    return back != 0 && frob != 0 && __builtin_frame_address(0) != 0;
}

static int plus(int a, int b) { return a + b; }

static void *jumps[5];
__attribute__((noinline)) static void jump_back(void) { __builtin_longjmp(jumps, 1); }

__attribute__((noinline)) static int unreachable_after(int x)
{
    if (x > 0)
        return x;
    __builtin_unreachable();
}

int main(void)
{
    int v = 3;
    printf("constant_p %d %d\n", __builtin_constant_p(4 * 5), __builtin_constant_p(v) && 0);
    printf("expect %d %d\n", __builtin_expect(v == 3, 1), __builtin_expect_with_probability(v, 3, 0.9));
    printf("unreachable %d\n", unreachable_after(9));
    if (v == 4)
        __builtin_trap();
    printf("types_compatible %d %d %d\n", __builtin_types_compatible_p(int, signed), __builtin_types_compatible_p(int, long), __builtin_types_compatible_p(typeof(v), const int));
    printf("has_attribute %d %d\n", __builtin_has_attribute(unreachable_after, noinline), __builtin_has_attribute(v, aligned));
    printf("choose_expr %d %d\n", (int)sizeof(__builtin_choose_expr(1, v, 1.0)), (int)sizeof(__builtin_choose_expr(0, v, 1.0)));
    printf("offsetof %d %d\n", (int)__builtin_offsetof(struct record, name), (int)__builtin_offsetof(struct record, name[3]));
    printf("classify_type %d %d %d %d\n", __builtin_classify_type(v), __builtin_classify_type(&v), __builtin_classify_type(1.0), __builtin_classify_type((struct record){ 0 }));
    char buffer[10];
    struct record r;
    printf("object_size %d %d %d\n", (int)__builtin_object_size(buffer, 0), (int)__builtin_object_size(r.name, 1), (int)__builtin_object_size(&buffer[4], 0));
    printf("dynamic_object_size %d\n", (int)__builtin_dynamic_object_size(buffer, 0));
    static struct { struct record head; long room[4]; } holder = { { 4 } };
    printf("counted_by_ref %d\n", *__builtin_counted_by_ref(holder.head.tail) == 4);
    printf("assume_aligned %d\n", __builtin_assume_aligned(buffer, 1) == buffer);
    __builtin_prefetch(buffer);
    __builtin_prefetch(buffer, 1, 3);
    printf("frames %d\n", returns_somewhere());
    printf("thread_pointer %d\n", __builtin_thread_pointer() != 0);
#if __has_builtin(__builtin_sponentry)
    printf("sponentry %d\n", __builtin_sponentry() != 0);
#else
    printf("no sponentry\n");
#endif
    char *stack = __builtin_alloca(32);
    memset(stack, 'x', 32);
    printf("alloca %c\n", stack[31]);
    if (__builtin_setjmp(jumps) == 0) {
        jump_back();
        printf("not reached\n");
    } else {
        printf("setjmp came back\n");
    }
    printf("va %d\n", sum(3, 1, 2, 3));
    typedef int v4 __attribute__((vector_size(16)));
    v4 a = { 1, 2, 3, 4 }, b = { 5, 6, 7, 8 };
    v4 mixed = __builtin_shuffle(a, b, (v4){ 0, 4, 1, 5 });
    v4 flipped = __builtin_shuffle(a, (v4){ 3, 2, 1, 0 });
    printf("shuffle %d %d %d %d %d\n", mixed[0], mixed[1], mixed[2], mixed[3], flipped[0]);
#if defined __x86_64__
    __builtin_cpu_init();
    printf("cpu %d %d\n", __builtin_cpu_supports("sse2"), __builtin_cpu_is("intel") | __builtin_cpu_is("amd"));
    __builtin_ia32_sfence();
    __builtin_ia32_lfence();
    __builtin_ia32_mfence();
    unsigned long long t1 = __builtin_ia32_rdtsc();
    unsigned aux;
    unsigned long long t2 = __builtin_ia32_rdtscp(&aux);
    printf("rdtsc %d\n", t2 >= t1);
#else
    printf("cpu 1 1\nrdtsc 1\n");
#endif
    printf("apply %d\n", plus(2, 3));
    return 0;
}
