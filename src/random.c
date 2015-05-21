#include "random.h"

/* initializes the random number generator */
gsl_rng * rng_init (unsigned long seed) {
  int i;
  gsl_rng * RNG = gsl_rng_alloc (gsl_rng_mt19937);
  gsl_rng_set (RNG, seed);

  /*
    do a few "warm up" rounds 
    because MT is affected by small seeds
    (whose internal reprensetation as bits sequences
    contain a lot of successive 0's or 1's)
   */
  for (i=0; i<MT_RNG_WARMUP_ROUNDS; i++) gsl_rng_set (RNG, gsl_rng_get (RNG));

  return RNG;
}

/* returns a random number uniformly distributed in the interval [min, max) */
double ran_uniform (gsl_rng *RNG, double min, double max) {
  return gsl_ran_flat (RNG, min, max);
}

/* returns a random number distributed in the gaussian N (0,1) distribution */
double ran_gaussian_01 (gsl_rng *RNG) {
  /* apparently the Ziggurat method is the fastest one available (source: GSL manual) */
  return gsl_ran_gaussian_ziggurat (RNG, 1.);
}

/* returns a random number distributed in the gaussian N (mean,sigma) distribution */
double ran_gaussian (gsl_rng *RNG, double mean, double sigma) {
  return mean + gsl_ran_gaussian_ziggurat (RNG, sigma);
}

/* return a random number in the [0,1) interval */
int ran_01 (gsl_rng *RNG) {
  return gsl_rng_uniform_int (RNG, 2);
}
