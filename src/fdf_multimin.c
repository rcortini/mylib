#include "fdf_multimin.h"

int fdf_multimin (const gsl_vector *X, gsl_vector *X_min, struct fdf_multimin_par *par) {
  size_t iter;
  int status;
  gsl_multimin_fdfminimizer *s;
  gsl_multimin_function_fdf my_func;
  
  /* init the minimizer */
  s = gsl_multimin_fdfminimizer_alloc (par->type, par->dim);

  /* set the gsl_multimin_function_df structure */
  my_func.n = par->dim;
  my_func.f = par->func;
  my_func.df = par->gradient;
  my_func.fdf = par->fdf;
  my_func.params = par->func_p;

  /* set the minimizer */
  gsl_multimin_fdfminimizer_set (s, &my_func, X, par->step_size, par->tol);

  /* start the iteration */
  iter = 0;
  do {
    size_t i;
    iter++;
    status = gsl_multimin_fdfminimizer_iterate (s);

    /* print information on the iteration */
    if (par->verbose) {
      printf ("%lu : f ( ", (long unsigned) iter);
      for (i=0; i<par->dim; i++) printf ("%f, ", gsl_vector_get (s->x, i));
      printf (") = %f\n", gsl_multimin_fdfminimizer_minimum (s));
    }

    /* TODO: put some true error condition here */
    if (status) {
      fprintf (stderr, "fdfminimizer: warning: %s\n", gsl_strerror (status));
      break;
    }

    /* test gradient condition */
    status = gsl_multimin_test_gradient (s->gradient, par->eps_abs);
  }
  while (status==GSL_CONTINUE && iter<par->max_iter);

  /* copy the result to the new vector, and free the minimizer */
  gsl_vector_memcpy (X_min, s->x);
  gsl_multimin_fdfminimizer_free (s);

  return status;
}
