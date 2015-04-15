#ifndef __MYLIB_EXPFIT_H__
#define __MYLIB_EXPFIT_H__

#include "utils.h"
#include "fit.h"
#include <gsl/gsl_sf.h>

double exp_f (double x, const gsl_vector *par);

double exp_df (unsigned int i, double x, const gsl_vector *par);

multifit_results *
exp_fit_w_sigma (
    double A0,
    double lambda0,
    double b0,
    unsigned int N,
    double *x,
    double *y,
    double *sigma);

#endif
