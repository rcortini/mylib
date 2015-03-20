#include "f_int.h"

/* performs the Gauss-Kronrod-Patterson non-adaptive integral calculation: designed for
 * fast calculation of integrals of smooth functions */
int f_int_qng (double a, double b, struct f_int_par *f_int_p, double *result, double *abserr) {
  size_t neval;
  return gsl_integration_qng (f_int_p->f, a, b, f_int_p->eps_abs, f_int_p->eps_rel, result, abserr, &neval);
}
