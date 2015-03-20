lib_LTLIBRARIES = libmylib.la
# pkginclude_HEADERS = mylib.h

libmylib_la_includedir = $(includedir)/mylib
libmylib_la_libincludedir = $(libdir)/include
pkginclude_HEADERS = mylib.h\
		  mylib_retcodes.h\
		  utils.h\
		  average_variance.h\
		  histogram.h\
		  fit.h\
		  f_deriv.h\
		  f_interp.h\
		  f_root.h\
		  f_min.h\
		  f_multimin.h\
		  fdf_multimin.h\
		  series_accel.h

libmylib_la_SOURCES = utils.c utils.h\
		      average_variance.c average_variance.h\
		      histogram.c histogram.h\
		      fit.c fit.h\
		      f_deriv.c f_deriv.h\
		      f_interp.c f_interp.h\
		      f_root.c f_root.h\
		      f_min.c f_min.h\
		      f_multimin.c f_multimin.h\
		      fdf_multimin.c fdf_multimin.h\
		      series_accel.c series_accel.h

libmylib_la_CPPFLAGS = @GSL_INCLUDES@
