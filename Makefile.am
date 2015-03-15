
ACLOCAL_AMFLAGS = -I aclocal.d ${ACLOCAL_FLAGS}
AM_CFLAGS = -I$(top_srcdir)

SUBDIRS = . t

EXTRA_DIST = 				\
	cmx.pc.in 			\
	$(NULL)

pkgconfigdir = @pkgconfigdir@
pkgconfig_DATA = cmx.pc

cmxincludedir = $(includedir)/cmx
cmxinclude_HEADERS = 			\
	cmx/cmx.h			\
	cmx/cmx-env-default.h		\
	cmx/cmx-env-gcc.h		\
	cmx/cmx-env-glib.h		\
	cmx/cmx-env-posix.h		\
	cmx/cmx-env.h			\
	cmx/cmx-local.h			\
	cmx/cmx-meta.h			\
	cmx/cmx-struct-refs.h		\
	cmx/cmx-struct-shareable.h	\
	cmx/cmx-synchronize.h		\
	cmx/cmx-token.h			\
	$(NULL)

