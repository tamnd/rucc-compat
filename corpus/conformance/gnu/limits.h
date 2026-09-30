/* Found through the quote path, so #include_next goes on to the system's limits.h. */
#if __has_include_next(<limits.h>)
#include_next <limits.h>
#endif
static const char *level_name = __FILE_NAME__;
static int level_depth = __INCLUDE_LEVEL__;
