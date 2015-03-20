#ifndef __MY_GSL_SERIES_ACCEL_H__
#define __MY_GSL_SERIES_ACCEL_H__

#define MY_SERIES_ACCEL_EPS 1e-15
#include <math.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_sum.h>

/* This class defines the "Series" object, which contains a function that calculates
   a real number, given an integer and a set of parameters. The class contains the
   methods to evaluate the single terms, and to evaluate the infinite sum, using
   the Levin u-transform method, using its GSL implementation. */

typedef struct series {
  double (*func) (int, void *);
  void *p;
  gsl_sum_levin_utrunc_workspace *w;
} series;

series * series_init (double (*func) (int, void*), void *p);

#define SERIES_TERM(s,n) ((s)->func((n),(s)->p))

double series_sum (series *, int n_start, int n_terms, double rel_error_tol);

#endif
