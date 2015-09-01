#ifndef __MYLIB_F_MULTIMIN_H__
#define __MYLIB_F_MULTIMIN_H__

#include <stdio.h>
#include <gsl/gsl_multimin.h>

/* f_multimin.c */
struct f_multimin_par {
  size_t verbose;
  size_t dim;
  double size_tol;
  size_t max_iter;
  gsl_vector *step_size;
  const gsl_multimin_fminimizer_type *type;
  double (*func) (const gsl_vector *X, void *p);
  void *func_p;
};

int f_multimin (const gsl_vector *x_start, gsl_vector *x_min, struct f_multimin_par *par);

#endif
