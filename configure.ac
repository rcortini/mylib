#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([mylib], [0.0.0], [ruggero.cortini@gmail.com])
AC_CONFIG_HEADERS([config.h])

# package info
PACKAGE=mylib
VERSION=0.0.0
AC_SUBST(PACKAGE)
AC_SUBST(VERSION)

# Checks for programs.
AC_PROG_CC

# init automake and libtool
AM_INIT_AUTOMAKE(subdir-objects)
AC_PROG_LIBTOOL
AC_CONFIG_MACRO_DIR([m4])

# Checks for libraries.

# Checks for GSL
AC_ARG_WITH(gsl,
            [  --with-gsl=DIR        Directory where the GSL is installed (optional)],
            GSL_DIR="$withval")

GSL_CONFIG=
AC_PATH_PROG([GSL_CONFIG], [gsl-config],, [$GSL_DIR/bin:$PATH])

GSL_INCLUDES=
GSL_LIBS=

if test -x "$GSL_CONFIG"; then
  GSL_INCLUDES=`$GSL_CONFIG --cflags`
  GSL_LIBS=`$GSL_CONFIG --libs`
else
  AC_ERROR([GSL not found. You need gsl to compile this package.
      See http://www.gnu.org/software/gsl/])
fi

AC_SUBST(GSL_INCLUDES)
AC_SUBST(GSL_LIBS)

# C flags
WARN_FLAGS="-Wall -Wextra -Wshadow -Wno-variadic-macros --pedantic"
CFLAGS="$WARN_FLAGS -O0"
CFLAGS_save="$CFLAGS"

# Checks for header files.
AC_CHECK_HEADERS([stdio.h stdarg.h stdlib.h unistd.h string.h])

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC

# the lib-specific flags
MYLIB_CFLAGS="-I$includedir"
MYLIB_LIBS="-L$libdir -lmylib"

AC_SUBST(MYLIB_CFLAGS)
AC_SUBST(MYLIB_LIBS)

# output
AC_CONFIG_FILES([mylib.pc Makefile
		 mystat/Makefile
		 src/Makefile])
AC_OUTPUT
