#ifndef __MYLIB_MC_H__
#define __MYLIB_MC_H__

#include "random.h"
#include "math.h"

/* parameters for the potential energy function */
typedef struct {
  double (*F) (double x, void *p);
  int (*check_x) (double x, void *p);
  void *H_p;
} Hamiltonian1D;

/* evaluates the forcing function */
#define H_EVAL(x,H) ((H)->F(x,(H)->H_p))

int metropolis (gsl_rng *, double, double, double);

double do_1D_mc (gsl_rng *, double, double, Hamiltonian1D *, double);

#endif
