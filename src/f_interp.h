#ifndef __MY_GSL_F_INTERP_H__
#define __MY_GSL_F_INTERP_H__

#include <stdio.h>
#include <gsl/gsl_spline.h>

struct f_interp_par {
  gsl_interp_accel *interp_accel;
  gsl_spline *interp_spline;
  unsigned int N;
  double x_min;
  double x_max;
};

struct f_interp_par * f_interp_init (unsigned int N, double *x, double *y);

double f_interp (double x, void *p);

void f_interp_free (struct f_interp_par *p);

#endif
