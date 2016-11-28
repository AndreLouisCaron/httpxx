#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.59])
AC_INIT(httpxx, 0.1.0, andre.l.caron@gmail.com)
AM_INIT_AUTOMAKE([subdir-objects])
AC_CONFIG_SRCDIR([httpxx/http.hpp])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_RANLIB
#AC_PROG_LIBTOOL
AC_CHECK_PROG(XLC, xlc, yes)
AC_CHECK_PROG(GCC, gcc, yes)
AM_CONDITIONAL(GCC, test "$GCC" = yes)
AM_CONDITIONAL(XLC, test "$XLC" = yes)

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([limits.h stddef.h stdint.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_STRNLEN
AC_CHECK_FUNCS([memchr memset strcasecmp strtoul])

AC_CONFIG_FILES([Makefile httpxx/Makefile test/Makefile])
AC_OUTPUT
