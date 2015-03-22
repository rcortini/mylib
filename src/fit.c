#include "fit.h"



/* print linear fitting results */
void print_linear_fit_results (linear_fit_results *fit_results, unsigned int vflag) {
  if (vflag) {
    printf ("LEAST-SQUARE LINEAR REGRESSION:\n");
    printf ("\tGSL exit code = %s\n", gsl_strerror (fit_results->retcode));
    printf ("\tc0 = %f c1 = %f\n\n", fit_results->c0, fit_results->c1);
    printf ("\tcovariance matrix:\n");
    printf ("\t[ %f  %f ]\n", fit_results->cov00, fit_results->cov01);
    printf ("\t[ %f  %f ]\n", fit_results->cov01, fit_results->cov11);
    printf ("\tchi squared = %f\n", fit_results->chisq);
  }
  else
    printf ("%.8e %.8e %.8e %.8e\n", fit_results->c0, fit_results->c1, sqrt (fit_results->cov00), sqrt (fit_results->cov11));
}



/* performes unweighted least-square linear fitting of data stored in x, y */
void linear_fit (unsigned int N, double *x, double *y, linear_fit_results *fit_results) {
  /* check that we have at least two values for the determination of standard deviation */
  if (N < 3) {
    err_message ("Insufficient data for linear fitting!\n");
    fit_results->retcode = MYLIB_FAIL;
    return;
  }

  /* fit */
  fit_results->retcode = gsl_fit_linear (x, 1, y, 1, N,
      &fit_results->c0,
      &fit_results->c1,
      &fit_results->cov00,
      &fit_results->cov01,
      &fit_results->cov11,
      &fit_results->chisq);
}



/* performes weighted least-square linear fitting of data stored in x, y, w */
void weighted_linear_fit (unsigned int N, double *x, double *y, double *w, linear_fit_results *fit_results) {
  /* check that we have at least two values for the determination of standard deviation */
  if (N < 3) {
    err_message ("Insufficient data for linear fitting!\n");
    fit_results->retcode = MYLIB_FAIL;
  }

  /* fit */
  fit_results->retcode = gsl_fit_wlinear (x, 1, w, 1, y, 1, N,
      &fit_results->c0,
      &fit_results->c1,
      &fit_results->cov00,
      &fit_results->cov01,
      &fit_results->cov11,
      &fit_results->chisq);
}



/* print results of multidimensional fitting */
void print_multifit_results (multifit_results *fit_results, unsigned int vflag) {
  unsigned int i, j;
  const unsigned int dim = fit_results->dim;
  if (vflag) {
    printf ("MULTIDIMENSIONAL FITTING RESULTS:\n");
    printf ("\tGSL exit code = %s\n", gsl_strerror (fit_results->retcode));
    printf ("\tBest fit parameters:\n");
    for (i=0; i<dim; i++) {
      printf ("\tc [%d] = %.8e +/- %.8e\n", i, gsl_vector_get (fit_results->c, i), sqrt (gsl_matrix_get (fit_results->cov, i, i)));
    }
    printf ("\tCovariance matrix:\n");
    for (i=0; i<dim; i++) {
      printf ("\t ");
      for (j=0; j<dim; j++)
	printf ("%.8e ", gsl_matrix_get (fit_results->cov, i, j));
      printf ("\n");
    }
  }
  else {
    for (i=0; i<dim; i++)
      printf ("%.8e %.8e\n", gsl_vector_get (fit_results->c, i), sqrt (gsl_matrix_get (fit_results->cov, i, i)));
  }
}



/* allocates memory for multidimensional fitting results */
multifit_results * multifit_results_alloc (unsigned int dim) {
  multifit_results *fit_results = (multifit_results *) malloc (sizeof (multifit_results));
  fit_results->cov = gsl_matrix_alloc (dim, dim);
  fit_results->c = gsl_vector_alloc (dim);
  fit_results->dim = dim;
  return fit_results;
}



/* frees the memory associated to the multidimensional fitting results */
void multifit_results_free (multifit_results *fit_results) {
  gsl_matrix_free (fit_results->cov);
  gsl_vector_free (fit_results->c);
  free (fit_results);
}



/* performs a least-square linear fitting of data to a polynomial of type
 * y = sum_n^degree c_n (x-x0)^2
 * and returns the coefficients c_n */
void polynomial_fit (unsigned int N, double *x, double *y, unsigned int degree, double x0, multifit_results *fit_results) {
  gsl_multifit_linear_workspace *ws;
  gsl_matrix *X = gsl_matrix_alloc (N, degree);
  gsl_vector *Y = gsl_vector_alloc (N);
  unsigned int i, j;

  /* initialize X and Y matrices */
  for (i=0; i<N; i++) {
    gsl_matrix_set (X, i, 0, 1.0);
    for (j=0; j<degree; j++) {
      gsl_matrix_set (X, i, j, pow (x[i]-x0, j));
    }
    gsl_vector_set (Y, i, y [i]);
  }

  /* initialize fitting workspace */
  ws = gsl_multifit_linear_alloc (N, degree);

  /* fit */
  fit_results->retcode = gsl_multifit_linear (X, Y, fit_results->c, fit_results->cov, &fit_results->chisq, ws);

  /* free memory */
  gsl_multifit_linear_free (ws);
  gsl_matrix_free (X);
  gsl_vector_free (Y);
}
