#include "block_average.h"

void print_block_average_results (block_average_results *results, size_t vflag) {
  size_t i;
  const size_t nblocks = results->nblocks;
  if (vflag) {
    printf ("BLOCK AVERAGING RESULTS:\n");
    for (i=0; i<nblocks; i++)
      printf ("nblocks = %lu: nvals = %lu, nstride = %lu, mean = %.8e variance = %.8e block variance = %.8e\n",
	  i+1,
	  results->nvals [i],
	  results->nstride [i],
	  results->mean [i],
	  results->var [i],
	  results->blockvar [i]);
  }
  else {
    for (i=0; i<nblocks; i++)
      printf ("%lu %lu %.8e %.8e %.8e\n",
	  results->nvals [i],
	  results->nstride [i],
	  results->mean [i],
	  results->var [i],
	  results->blockvar [i]);
  }
}


/* alloc the memory necessary for the block averaging */
block_average_results * block_average_results_alloc (size_t nblocks) {
  block_average_results * results = (block_average_results *) malloc (sizeof (block_average_results));
  results->nblocks = nblocks;
  results->mean = (double *) malloc (nblocks*sizeof (double));
  results->var = (double *) malloc (nblocks*sizeof (double));
  results->blockvar = (double *) malloc (nblocks*sizeof (double));
  results->nstride = (size_t *) malloc (nblocks*sizeof (double));
  results->nvals = (size_t *) malloc (nblocks*sizeof (double));
  return results;
}



/* frees the memory associated to the block average results */
void block_average_results_free (block_average_results *results) {
  free (results->nstride);
  free (results->nvals);
  free (results->mean);
  free (results->var);
  free (results->blockvar);
  free (results);
}



/* block averaging */
size_t block_average (size_t N, double *data, size_t nblocks, block_average_results *results) {
  size_t n, i, j, k;
  double *blockdata = (double *) malloc (N*sizeof (double));
  double *blockmean = (double *) malloc (nblocks*sizeof (double));
  double *blockvar = (double *) malloc (nblocks*sizeof (double));

  /* cycle on all block sizes from n = 1 to nblocks */
  for (n=0; n<nblocks; n++) {
    const size_t nstride = N/(n+1);
    /* we divide the data into n+1 blocks, each of length nstride, then we iterate
     * over every block */
    j=0;
    do {
      /* the index k runs from 0 to nstride */
      for (k=0; k<nstride; k++) {
	/* this is the index of the data in the original data vector */
	i = j*nstride+k;
	blockdata [k] = data [i];
      }
      average_variance (nstride, blockdata, &blockmean[j], &blockvar[j]);

      /* repeat until the next block will be of size smaller than nstride */
      j++;
    } while ((j+1)*nstride<N);

    /* calculate the mean of the values of the means and variances for the n blocks
     * in this iteration */
    average (j, blockmean, &results->mean [n]);
    average (j, blockvar, &results->var [n]);
    if (j>2)
      variance (j, blockmean, &results->blockvar [n]);
    else
      results->blockvar [n] = 0.;
    results->nstride [n] = nstride;
    results->nvals [n] = j;
  }

  /* free memory and return */
  free (blockdata);
  free (blockmean);
  free (blockvar);
  return MYLIB_SUCCESS;
}
