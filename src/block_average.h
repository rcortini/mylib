#ifndef __MYLIB_BLOCK_AVERAGE_H__
#define __MYLIB_BLOCK_AVERAGE_H__

#include "average_variance.h"

typedef struct block_average_results {
  double *mean;
  double *var;
  int *nstride;
  int *nvals;
  unsigned int nblocks;
} block_average_results;

void print_block_average_results (block_average_results *results, unsigned int vflag);

block_average_results * block_average_results_alloc (unsigned int nblocks);

void block_average_results_free (block_average_results *results);

unsigned int block_average (unsigned int N, double *data, unsigned int nblocks, block_average_results *results);

#endif
