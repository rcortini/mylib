#ifndef __MY_GSL_F_INT_H__
#define __MY_GSL_F_INT_H__

#include <stdio.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_errno.h>

struct f_int_par {
  const gsl_function * f;
  double eps_abs;
  double eps_rel;
};

int f_int_qng (double a, double b, struct f_int_par *f_int_p, double *result, double *abserr);

#endif
