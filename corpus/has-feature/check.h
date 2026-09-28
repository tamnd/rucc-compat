/* What every test here includes.
 *
 * A test prints one line saying whether the compiler claims the feature, then one line per thing
 * GCC's manual says the feature does, and the run is compared line for line against the same
 * program built by the reference. The claim is printed as 0 or 1 rather than as the number the
 * compiler answers, because GCC answers a C23 attribute such as noreturn with the year of the
 * standard and any nonzero answer is a yes.
 *
 * A line that says FAIL is a behaviour the manual promises and the build did not deliver. The
 * reference is expected to print none, and a test that prints one under the reference is a test
 * that needs fixing rather than a finding. */

#ifndef HAS_FEATURE_CHECK_H
#define HAS_FEATURE_CHECK_H

#include <stdio.h>

static int failures;

#define CLAIM(what, answer) printf("%s %d\n", what, (answer) ? 1 : 0)

#define CHECK(cond)                                                                              \
    do {                                                                                         \
        if (cond) {                                                                              \
            printf("ok %s\n", #cond);                                                            \
        } else {                                                                                 \
            printf("FAIL %s at line %d\n", #cond, __LINE__);                                     \
            failures++;                                                                          \
        }                                                                                        \
    } while (0)

#define DONE() return failures != 0

#endif
