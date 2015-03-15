
AC_PREREQ([2.60])
AC_INIT([cmx],[1.0.0],[happy.barney@gmail.com])
AC_CONFIG_SRCDIR([cmx/cmx.h])
AC_CONFIG_AUX_DIR([acaux.d])
dnl AC_CONFIG_HEADERS([config.h])
dnl AC_CONFIG_MACRO_DIR([aclocal.d])

AM_INIT_AUTOMAKE([subdir-objects])

AC_PROG_CC
AC_PROG_CC_C99

# Where to install pkg-config data
PKG_INSTALLDIR

AC_CONFIG_FILES([
    Makefile
    t/Makefile
    cmx.pc
])

AC_OUTPUT
