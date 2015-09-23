#include "correlation.h"
#include <stdio.h>

size_t correlation (size_t N, double *data, double *corr) {
  int psd_retcode;
  size_t i;
  double *psd_results = (double *) malloc (N*sizeof (double));
  double *data_unbiased = (double *) malloc (N*sizeof (double));
  double data_average;

  /* subtract average from signal */
  average (N, data, &data_average);
  for (i=0; i<N; i++)
    data_unbiased [i] = data [i]-data_average;

  /* calculate psd of unbiased data */
  psd_retcode = psd (N, data_unbiased, psd_results);

  /* check if psd calculation succeeded */
  if (psd_retcode != MYLIB_SUCCESS) {
    free (psd_results);
    free (data_unbiased);
    return psd_retcode;
  }
  else {
    int invfft_retcode;
    double data_norm;

    /* prepare the coefficients: create an array of complex numbers 
     * with zero imaginary part */
    double *psd_results_complex = (double *) malloc (2*N*sizeof (double));
    gsl_fft_real_unpack (psd_results, psd_results_complex, 1, N);

    /* inverse transform of psd */
    invfft_retcode = complex_inverse_fft (N, psd_results_complex, corr);

    /* calculate square norm of data */
    calculate_sum2 (N, data_unbiased, &data_norm);

    /* normalize correlation function */
    for (i=0; i<N; i++)
      corr [i] /= data_norm;

    /* free memory and return */
    free (psd_results);
    free (psd_results_complex);
    free (data_unbiased);
    return invfft_retcode;
  }
}
