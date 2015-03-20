#include "series_accel.h"

/* calculates the sum of the series using the Levin u-transform method */
double series_sum (series *s, int n_start, int n_terms, double rel_error_tol) {
  int i, j, iter=0, n_non_zero=0, first_index, last_index;
  double xn, *X, accel_sum=0., err;

  /* allocate memory for the calculation */
  X = (double *) malloc (sizeof (double));
  do {
    /* initialize indices */
    iter++;
    first_index = n_start + (iter-1)*n_terms;
    last_index = first_index + n_terms - 1;
    X = (double *) realloc (X, (last_index-n_start+1)*sizeof(double));

    /* calculate n_terms terms of the series, at the iter-th iteration */
    for (i=first_index, j=0; i<=last_index; i++) {
      xn = SERIES_TERM(s,i);
      if (fabs (xn) > MY_SERIES_ACCEL_EPS) {
	X [n_non_zero+j] = xn;
	j++;
      }
    }
    n_non_zero+=j;

    /* case 1: no non-zero elements of the sum were found.
       In this case we return accel_sum. If it is the first
       iteration, this value is zero. Otherwise it's the value of the
       accelerated sum calculated at last iteration. */
    if (j==0) {
      free (X);
      return accel_sum;
    }

    /* case 2: all the other cases. We need to allocate the workspace for series
       acceleration, and then accelerate the series. */
    s->w = gsl_sum_levin_utrunc_alloc (n_non_zero);
    gsl_sum_levin_utrunc_accel (X, n_non_zero, s->w, &accel_sum, &err);
    gsl_sum_levin_utrunc_free (s->w);
  } while (fabs (err/accel_sum) > rel_error_tol);

  free (X);
  return accel_sum;
}
