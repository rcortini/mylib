#include "f_multimin.h"

/* This function finds the minimum of a real-valued vector-argument function,
 * given x_start as starting point. Uses algorithm of minimization without
 * derivatives. The parameters are passed through the f_multimin_par structure,
 * which also contains the pointer to the function to minimize, and the parameters
 * of the function to minimize. */
int f_multimin (const gsl_vector *x_start, gsl_vector *x_min, struct f_multimin_par *par) {
  size_t iter, i;
  int status;
  double size;
  gsl_multimin_fminimizer *s;
  gsl_multimin_function my_func;

  /* initializes the function to minimize */
  my_func.n = par->dim;
  my_func.f = par->func;
  my_func.params = par->func_p;

  /* initializes the minimizer */
  s = gsl_multimin_fminimizer_alloc (par->type, par->dim);
  gsl_multimin_fminimizer_set (s, &my_func, x_start, par->step_size);

  /* iterate the minimizer */
  iter = 0;
  do {
    iter++;
    status = gsl_multimin_fminimizer_iterate (s);

    if (status) {
      fprintf (stderr, "f_multimin: warning: %s\n", gsl_strerror (status));
      break;
    }

    size = gsl_multimin_fminimizer_size (s);
    status = gsl_multimin_test_size (size, par->size_tol);

    if (par->verbose) {
      printf ("%lu: f (", iter);
      for (i=0; i<par->dim; i++) printf ("%f, ", gsl_vector_get (s->x, i));
      printf (") = %f, size = %f\n", s->fval, size);
    }
  }
  while (status==GSL_CONTINUE && iter<par->max_iter);

  /* set the minimum, free memory, and exit */
  gsl_vector_memcpy (x_min, s->x);
  gsl_multimin_fminimizer_free (s);
  return GSL_SUCCESS;
}
