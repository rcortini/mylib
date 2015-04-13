#ifndef __MYLIB_FIT_H__
#define __MYLIB_FIT_H__

#include <gsl/gsl_blas.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_fit.h>
#include <gsl/gsl_multifit.h>
#include <gsl/gsl_multifit_nlin.h>
#include "mylib_retcodes.h"
#include "utils.h"
#include "chi2.h"

/* linear fitting */

typedef struct linear_fit_results {
  double c0;
  double c1;
  double cov00;
  double cov01;
  double cov11;
  double chisq;
  int retcode;
} linear_fit_results;

void print_linear_fit_results (linear_fit_results *fit_results, unsigned int vflag);

void linear_fit (unsigned int N, double *x, double *y, linear_fit_results *fit_results);

void weighted_linear_fit (unsigned int N, double *x, double *y, double *w, linear_fit_results *fit_results);

/* multidimensional fitting */

typedef struct multifit_results {
  gsl_vector *c;
  gsl_matrix *cov;
  unsigned int dim;
  int retcode;
  double chisq;
} multifit_results;

void print_multifit_results (multifit_results *fit_results, unsigned int vflag);

multifit_results * multifit_results_alloc (unsigned int degree);

void multifit_results_free (multifit_results *fit_results);

void polynomial_fit (unsigned int N, double *x, double *y, unsigned int degree, double x0, multifit_results *fit_result);

/* this structure contains all the information necessary to perform the
 * non-linear least-square fit */
struct nlin_fit_parameters {
  size_t n;
  double *x;
  double *y;
  double *sigma;
  double (*model_f) (double x, const gsl_vector *par);
  double (*model_df) (unsigned int i, double x, const gsl_vector *par);
  size_t npars;
  double eps_abs;
  double eps_rel;
  size_t max_iter;
  const gsl_multifit_fdfsolver_type *type;
};

void nlin_fit (const gsl_vector *x_start, struct nlin_fit_parameters *fit_p, multifit_results *results);

double chi2_from_fit (gsl_vector *fit, struct nlin_fit_parameters *fit_pars);

#endif
