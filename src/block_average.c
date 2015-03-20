#include "block_average.h"

void print_block_average_results (block_average_results *results, unsigned int vflag) {
  unsigned int i;
  const unsigned int nblocks = results->nblocks;
  if (vflag) {
    printf ("BLOCK AVERAGING RESULTS:\n");
    for (i=0; i<nblocks; i++)
      printf ("nblocks = %d: nvals = %d, nstride = %d, mean = %.8e variance = %.8e\n",
	  i,
	  results->nvals [i],
	  results->nstride [i],
	  results->mean [i],
	  results->var [i]);
  }
  else {
    for (i=0; i<nblocks; i++)
      printf ("%d %d %.8e %.8e\n",
	  results->nvals [i],
	  results->nstride [i],
	  results->mean [i],
	  results->var [i]);
  }
}


/* alloc the memory necessary for the block averaging */
block_average_results * block_average_results_alloc (unsigned int nblocks) {
  block_average_results * results = (block_average_results *) malloc (sizeof (block_average_results));
  results->nblocks = nblocks;
  results->mean = (double *) malloc (nblocks*sizeof (double));
  results->var = (double *) malloc (nblocks*sizeof (double));
  results->nstride = (int *) malloc (nblocks*sizeof (double));
  results->nvals = (int *) malloc (nblocks*sizeof (double));
  return results;
}



/* frees the memory associated to the block average results */
void block_average_results_free (block_average_results *results) {
  free (results->mean);
  free (results->var);
  free (results->nstride);
  free (results->nvals);
  free (results);
}



/* block averaging */
unsigned int block_average (unsigned int N, double *data, unsigned int nblocks, block_average_results *results) {
  unsigned int n, i, j, k;
  double *blockdata = (double *) malloc (N*sizeof (double));
  double *blockmean = (double *) malloc (nblocks*sizeof (double));
  double *blockvar = (double *) malloc (nblocks*sizeof (double));

  /* cycle on all block sizes from n = 1 to nblocks */
  for (n=0; n<nblocks; n++) {
    const unsigned int nstride = N/(n+1);
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
    results->nstride [n] = nstride;
    results->nvals [n] = j;
  }

  /* free memory and return */
  free (blockdata);
  free (blockmean);
  free (blockvar);
  return MYLIB_SUCCESS;
}
