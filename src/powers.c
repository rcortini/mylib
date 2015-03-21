#include "powers.h"

/* tells whether x is an integer */
unsigned int is_integer (double x) {
  return (ceil(x)==x);
}

/* tells whether x is a power of n */
unsigned int is_power_of_n (int x, int n) {
  return is_integer (gsl_sf_log ((double) x)/gsl_sf_log ((double) n));
}
