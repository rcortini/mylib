#include "fit.h"

unsigned int weighted_linear_fit (unsigned int N, double *x, double *y, double *w, linear_fit_results *fit_results) {
  int fit_result;

  /* check that we have at least two values for the determination of standard deviation */
  if (N < 3) {
    err_message ("Insufficient data for linear fitting!\n");
    return MYLIB_FAIL;
  }

  /* fit */
  fit_result = gsl_fit_wlinear (x, 1, w, 1, y, 1, N,
      &fit_results->c0,
      &fit_results->c1,
      &fit_results->cov00,
      &fit_results->cov01,
      &fit_results->cov11,
      &fit_results->chisq);

  return fit_result;
}
