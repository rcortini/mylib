#include "f_interp.h"

/* initializes a pointer to an interpolator */
struct f_interp_par * f_interp_init (size_t N, double *x, double *y) {
  size_t i;

  /* memory allocation for the interpolator structure */
  struct f_interp_par *p = (struct f_interp_par *) malloc (sizeof (*p));

  /* initialize number of values */
  p->N = N;

  /* initialize minimum and maximum values of x for the interpolator */
  p->x_min = p->x_max = x [0];
  for (i=0; i<p->N; i++) {
    if (x [i]<p->x_min) p->x_min = x [i];
    if (x [i]>p->x_max) p->x_max = x [i];
  }

  /* allocate the space for the interpolation functions */
  p->interp_accel = gsl_interp_accel_alloc ();
  p->interp_spline = gsl_spline_alloc (gsl_interp_cspline, N);

  /* initialize the interpolator */
  gsl_spline_init (p->interp_spline, x, y, N);

  /* return the pointer to the initialized interpolator */
  return p;
}



/* calculates the value of the interpolated function */
double f_interp (double x, void *p) {
  struct f_interp_par *interp = (struct f_interp_par *) p;

  /* check that x is within the boundaries */
  if (x<interp->x_min || x>interp->x_max) {
    fprintf (stderr, "f_interp: x = %f is out of the boundaries of the supplied data set!\n", x);
    fprintf (stderr, "\tx_min = %f x_max = %f\n", interp->x_min, interp->x_max);
    exit (EXIT_FAILURE);
  }

  /* if it is, then return the interpolated value */
  return gsl_spline_eval (interp->interp_spline, x, interp->interp_accel);
}



/* frees the pointer to the structure */
void f_interp_free (struct f_interp_par *p) {
  gsl_interp_accel_free (p->interp_accel);
  gsl_spline_free (p->interp_spline);
  free (p);
}
