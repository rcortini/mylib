#ifndef __MYLIB_RANDOM_H__
#define __MYLIB_RANDOM_H__

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#define MT_RNG_WARMUP_ROUNDS 50

gsl_rng * rng_init (unsigned long seed);

double ran_uniform (gsl_rng *, double min, double max);

double ran_gaussian_01 (gsl_rng *);

double ran_gaussian (gsl_rng *, double mean, double sigma);

int ran_01 (gsl_rng *);

#endif
