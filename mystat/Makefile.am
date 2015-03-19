bin_PROGRAMS = mystat
mystat_SOURCES = mystat.c
mystat_CPPFLAGS = -I$(top_srcdir)/src @GSL_INCLUDES@
mystat_LDADD = $(top_builddir)/src/libmylib.la -L$(top_builddir)/src @GSL_LIBS@
