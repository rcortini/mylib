#include "exp_fit.h"


/* exponential function */
double exp_f (double x, const gsl_vector *par) {
  const double A = gsl_vector_get (par, 0);
  const double lambda = gsl_vector_get (par, 1);
  const double b = gsl_vector_get (par, 2);

  return A*gsl_sf_exp (-lambda*x) + b;
}



/* gradient of the exponential function wrt the parameters A, lambda
 * and b */
double exp_df (unsigned int i, double x, const gsl_vector *par) {
  const double A = gsl_vector_get (par, 0);
  const double lambda = gsl_vector_get (par, 1);
  switch (i) {
    case 0 :
      return gsl_sf_exp (-lambda*x);
      break;
    case 1 :
      return -x*A*gsl_sf_exp (-lambda*x);
      break;
    case 2 :
      return 1.;
      break;
    default :
      err_message ("exp_df: Invalid index %d\n", i);
      exit (EXIT_FAILURE);
  }
}

#define EXP_F_NPARS 3

multifit_results *
exp_fit_w_sigma (
    double A0,
    double lambda0,
    double b0,
    unsigned int N,
    double *x,
    double *y,
    double *sigma) {

  struct nlin_fit_parameters fitpars;
  gsl_vector *x_start = gsl_vector_alloc (EXP_F_NPARS);
  multifit_results * results = multifit_results_alloc (EXP_F_NPARS);

  /* set all parameters for fit */
  fitpars.n = N;
  fitpars.x = x;
  fitpars.y = y;
  fitpars.sigma = sigma;
  fitpars.model_f = exp_f;
  fitpars.model_df = exp_df;
  fitpars.npars = EXP_F_NPARS;
  fitpars.eps_abs = 1e-5;
  fitpars.eps_rel = 1e-5;
  fitpars.max_iter = 100;
  fitpars.type = gsl_multifit_fdfsolver_lmsder;

  /* set the initial values for the fitter function */
  gsl_vector_set (x_start, 0, A0);
  gsl_vector_set (x_start, 1, lambda0);
  gsl_vector_set (x_start, 2, b0);

  /* invoke the fitter function */
  nlin_fit (x_start, &fitpars, results);

  gsl_vector_free (x_start);
  return results;
}
