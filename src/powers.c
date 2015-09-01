#include "powers.h"

/* tells whether x is an integer */
size_t is_integer (double x) {
  return (ceil(x)==x);
}

/* tells whether x is a power of n */
size_t is_power_of_n (int x, int n) {
  return is_integer (gsl_sf_log ((double) x)/gsl_sf_log ((double) n));
}
