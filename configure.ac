#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([dancy], [0.5])
AM_INIT_AUTOMAKE([-Wall -Werror])
AC_CONFIG_SRCDIR([src/test.cpp])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX([g++])
AC_PROG_CC([gcc])

# Checks for libraries.
AC_CHECK_LIB([gstreamer-0.10],[gst_structure_get_int])

# Checks for header files.
AC_CHECK_HEADERS([float.h limits.h malloc.h memory.h stdlib.h string.h sys/ioctl.h termios.h unistd.h wchar.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([floor memset pow sqrt strstr])

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT

