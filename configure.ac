

AC_INIT(flactag,2.0.4)
AC_CONFIG_SRCDIR(flactag.cc)

AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE

AC_CANONICAL_HOST
AM_CONFIG_HEADER(config.h)

AC_LIBTOOL_WIN32_DLL

AC_PROG_CC
AC_PROG_CXX
gl_EARLY
gl_INIT

AC_PROG_INSTALL

AC_PROG_LIBTOOL

AC_PROG_LN_S

PKG_CHECK_MODULES([DEP_ALL], [libdiscid])
PKG_CHECK_MODULES([DEP_FLACTAG], [neon slang libmusicbrainz5 flac++ unac])
AC_SEARCH_LIBS([jpeg_read_header], jpeg, , [
     AC_MSG_ERROR([unable to find jpeg_read_header, install libjpeg-dev and/or set CPPFLAGS/LDFLAGS])
])

AC_OUTPUT(
	Makefile
	)

