#ifndef __MYLIB_F_MIN_H__
#define __MYLIB_F_MIN_H__

#include <stdio.h>
#include <gsl/gsl_min.h>
#include <gsl/gsl_errno.h>

/* f_min.c */
struct f_min_params {
  size_t verbose;
  double (*func) (double x, void *p);
  void *func_p;
  double eps_rel;
  double eps_abs;
  size_t max_iter;
  const gsl_min_fminimizer_type *type;
};

int f_min (double x_min, double x0, double x_max, double *minimum, struct f_min_params *par);

#endif
