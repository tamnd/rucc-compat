dnl The questions that a typical autoconf and libtool package asks about the compiler.
AC_INIT([fixture], [1.0])
AC_CONFIG_SRCDIR([fix.c])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIRS([m4])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_PROG_CC
LT_INIT
AC_C_BIGENDIAN
AC_C_INLINE
AC_C_RESTRICT
AC_C_CONST
AC_C_VOLATILE
AC_TYPE_SIZE_T
AC_TYPE_INT64_T
AC_SYS_LARGEFILE
AC_CHECK_HEADERS([stdint.h sys/epoll.h threads.h stdatomic.h sys/random.h valgrind/valgrind.h])
AC_CHECK_FUNCS([memfd_create getrandom strlcpy reallocarray qsort_r])
AC_CHECK_SIZEOF([long])
AC_CHECK_SIZEOF([long double])
AC_CHECK_SIZEOF([__int128])
AC_CHECK_ALIGNOF([max_align_t], [#include <stddef.h>])
AC_SEARCH_LIBS([pthread_create], [pthread])
AC_SEARCH_LIBS([cos], [m])
AC_SEARCH_LIBS([dlopen], [dl])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
