#include "average_variance.h"

/* average and standard deviation of a vector */
unsigned int average_variance (FILE *f_in, int col) {
  unsigned int i;
  double sum, sum2, average, variance;
  double *data;
  unsigned int N = read_data_single_col (f_in, col, &data);
  double n = (double) N; /* cast to double */

  /* check that we have at least two values for the determination of standard deviation */
  if (N <= 1) {
    err_message ("Insufficient data to perform average and variance calculation\n");
    return MYLIB_FAIL;
  }

  /* calculate the sum and the sum of the squares of the input data */
  for (i=0, sum=0., sum2=0.; i<N; i++) {
    double value = data [i];
    sum+=value;
    sum2+=value*value;
  }

  /* calculate average and standard deviation */
  average = sum/n;
  
  /* calculate variance */
  variance = n/(n-1.)*(sum2/n - average*average);

  /* output */
  log_message ("average = %.8e, variance = %.8e\n", average, variance);

  return MYLIB_SUCCESS;
}


