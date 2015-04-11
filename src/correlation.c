#include "correlation.h"
#include <stdio.h>

unsigned int correlation (unsigned int N, double *data, double *corr) {
  int psd_retcode;
  double *psd_results = (double *) malloc (N*sizeof (double));

  /* calculate psd of curated data */
  psd_retcode = psd (N, data, psd_results);

  /* check if psd calculation succeeded */
  if (psd_retcode != MYLIB_SUCCESS) {
    free (psd_results);
    return psd_retcode;
  }
  else {
    int invfft_retcode;

    /* prepare the coefficients: create an array of complex numbers 
     * with zero imaginary part */
    double *psd_results_complex = (double *) malloc (2*N*sizeof (double));
    gsl_fft_real_unpack (psd_results, psd_results_complex, 1, N);

    /* inverse transform of psd */
    invfft_retcode = complex_inverse_fft (N, psd_results_complex, corr);

    /* free memory and return */
    free (psd_results);
    free (psd_results_complex);
    return invfft_retcode;
  }
}
