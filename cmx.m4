
dnl AM_PATH_CMX([VERSION SPEC], [ACTION-IF-FOUND], [ACTION-IF-NOT-FOUND])
dnl =====================================================================
dnl Test for CMX, define CMX_CFLAGS and CMX_LIBS variables and append them
dnl to existing CFLAGS/LIBS

AC_DEFUN([AM_PATH_CMX], [
    AM_PATH_CMX_ONLY([$1], [
        CFLAGS="$CFLAGS $CMX_CFLAGS"
        LIBS="$LIBS $CMX_LIBS"
        $2
    ], [$3])
])

dnl AM_PATH_CMX_ONLY([VERSION SPEC], [ACTION-IF-FOUND], [ACTION-IF-NOT-FOUND])
dnl =====================================================================
dnl Similar to AM_PATH_CMX but doesn't populate CFLAGS/LIBS
AC_DEFUN([AM_PATH_CMX_ONLY], [
    PKG_CHECK_MODULES([CMX], [cmx $1], [
        AM_PATH_GLIB_2_0([2.40.0], [
           CMX_CFLAGS="$CMX_FLAGS $GLIB_CFLAGS"
           CMX_LIBS="$CMX_LIBS $GLIB_LIBS"
           AC_DEFINE([HAVE_CMX_ENV_GLIB], [1], [Enable CMX GLib env])
       ], [])
       [$2]
    ],
    [$3])])
