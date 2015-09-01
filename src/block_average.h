#ifndef __MYLIB_BLOCK_AVERAGE_H__
#define __MYLIB_BLOCK_AVERAGE_H__

#include "average_variance.h"

typedef struct block_average_results {
  double *mean;
  double *var;
  double *blockvar;
  size_t *nstride;
  size_t *nvals;
  size_t nblocks;
} block_average_results;

void print_block_average_results (block_average_results *results, size_t vflag);

block_average_results * block_average_results_alloc (size_t nblocks);

void block_average_results_free (block_average_results *results);

size_t block_average (size_t N, double *data, size_t nblocks, block_average_results *results);

#endif
