#ifndef __MYLIB_FIT_H__
#define __MYLIB_FIT_H__

#include <gsl/gsl_fit.h>
#include "mylib_retcodes.h"
#include "utils.h"

typedef struct linear_fit_results {
  double c0;
  double c1;
  double cov00;
  double cov01;
  double cov11;
  double chisq;
} linear_fit_results;

unsigned int weighted_linear_fit (unsigned int N, double *x, double *y, double *w, linear_fit_results *fit_results);

#endif
