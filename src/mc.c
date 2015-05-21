#include "mc.h"

/* Metropolis Monte Carlo method */
int metropolis (gsl_rng *RNG, double beta, double H_initial, double H_final) {
  if (H_final <= H_initial)
    return 1;
  else {
    if (ran_uniform (RNG,0.,1.)<exp (-beta*(H_final-H_initial)))
      return 1;
    else
      return 0;
  }
}

/* do a single Monte Carlo step, starting from x_start */
double do_1D_mc (gsl_rng *RNG,
    double beta,
    double delta,
    Hamiltonian1D *H,
    double x_start) {
  const double H_in = H_EVAL (x_start, H);
  double x, H_fin;
  do {
    do {
      x = ran_01(RNG)==0 ? x_start+delta : x_start-delta;
    } while (!H->check_x (x, H->H_p));
    H_fin = H_EVAL (x, H);
  } while (!metropolis (RNG, beta, H_in, H_fin));
  return x;
}
