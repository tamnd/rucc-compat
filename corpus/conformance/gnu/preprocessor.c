/* The preprocessor's extensions: the __has_ operators, #pragma once, #include_next, the GNU
   spellings of variadic macros, and the macros only GCC predefines. */
#include <stdio.h>
#include <string.h>
#include "once.h"
#include "once.h"
#include "limits.h"

#define say(format, args...) printf(format "\n", ##args)
#define count(...) count_of(0, ##__VA_ARGS__, 3, 2, 1, 0)
#define count_of(z, a, b, c, n, ...) n
#define STRING(x) #x
#define PRAGMA(x) _Pragma(STRING(x))

PRAGMA(GCC diagnostic push)
PRAGMA(GCC diagnostic pop)

static const unsigned char bytes[] = {
#embed "once.h" limit(8)
};

enum { first = __COUNTER__, second = __COUNTER__ };

int main(void)
{
#if __has_include(<stdio.h>) && !__has_include("no-such-header.h")
    say("has_include %d", 1);
#endif
#if __has_embed("once.h") == __STDC_EMBED_FOUND__ && __has_embed("nowhere.bin") == __STDC_EMBED_NOT_FOUND__
    say("has_embed %d", 1);
#endif
#if __has_attribute(packed) && __has_attribute(__aligned__) && !__has_attribute(no_such_attribute)
    say("has_attribute %d", 1);
#endif
#if __has_c_attribute(fallthrough) && __has_c_attribute(maybe_unused)
    say("has_c_attribute %d", 1);
#endif
#if __has_builtin(__builtin_expect) && __has_builtin(__builtin_memcpy) && !__has_builtin(__builtin_nothing)
    say("has_builtin %d", 1);
#endif
#if defined __has_feature && defined __has_extension && !__has_feature(no_such_feature) && !__has_extension(no_such_extension)
    say("has_feature %d", 1);
#endif
    say("once %d", included_once);
    say("include_next %s %d %d", level_name, level_depth, INT_MAX == 2147483647);
    say("embed %d %s", (int)sizeof bytes, memcmp(bytes, "#pragma ", 8) == 0 ? "matches" : "differs");
    say("variadic %d %d %d", count(), count(a), count(a, b, c));
    say("counter %d %d", first, second);
    say("base %s %s", __BASE_FILE__, __FILE_NAME__);
    say("level %d", __INCLUDE_LEVEL__);
    say("plain");
    return 0;
}
