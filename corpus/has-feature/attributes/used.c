/* used: the definition is emitted even though nothing in C refers to it. The only reference here
 * is from assembly, which the compiler cannot see, so without the attribute an optimizing build
 * is entitled to drop the function and the link fails. */
#include "../check.h"

#if __has_attribute(used)
#define HAS 1
#else
#define HAS 0
#endif

__attribute__((used, noinline)) static int kept_by_asm(void) {
    return 42;
}

__attribute__((used)) static int kept_value = 7;

__asm__(".text\n"
        ".globl has_feature_call_kept\n"
        "has_feature_call_kept:\n"
        "\tjmp kept_by_asm\n"
        ".globl has_feature_read_kept\n"
        "has_feature_read_kept:\n"
        "\tmovl kept_value(%rip), %eax\n"
        "\tret\n");

extern int has_feature_call_kept(void);
extern int has_feature_read_kept(void);

int main(void) {
    CLAIM("__has_attribute(used)", HAS);
    CHECK(has_feature_call_kept() == 42);
    CHECK(has_feature_read_kept() == 7);
    DONE();
}
