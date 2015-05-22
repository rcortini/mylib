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
		  series_accel.h\
		  block_average.h\
		  powers.h\
		  fft.h\
		  correlation.h\
		  exp_fit.h\
		  random.h\
		  mc.h\
		  chi2.h\
		  genmath.h

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
		      series_accel.c series_accel.h\
		      block_average.c block_average.h\
		      powers.c powers.h\
		      fft.c fft.h\
		      correlation.c correlation.h\
		      exp_fit.c exp_fit.h\
		      chi2.c chi2.h\
		      random.c random.h\
		      mc.c mc.h\
		      genmath.c genmath.h

libmylib_la_CPPFLAGS = @GSL_INCLUDES@
