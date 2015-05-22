#include "genmath.h"

/* Langevin function */
double langevin_function (double x) {
  return 1./tanh (x) - 1./x;
}
