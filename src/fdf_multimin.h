#ifndef __MYLIB_FDF_MULTIMIN_H__
#define __MYLIB_FDF_MULTIMIN_H__

#include <stdio.h>
#include <gsl/gsl_multimin.h>

/* fdf_multimin.c */
struct fdf_multimin_par {
  size_t verbose;
  size_t dim;
  size_t max_iter;
  double step_size;
  double tol;
  double eps_abs;
  const gsl_multimin_fdfminimizer_type *type;
  double (*func) (const gsl_vector *X, void *p);
  void (*gradient) (const gsl_vector *X, void *p, gsl_vector *df);
  void (*fdf) (const gsl_vector *X, void *p, double *f, gsl_vector *df);
  void *func_p;
};

int fdf_multimin (const gsl_vector *X, gsl_vector *X_min, struct fdf_multimin_par *par);

#endif
