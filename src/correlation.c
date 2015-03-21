#include "correlation.h"

unsigned int correlation (unsigned int N, double *data, double *corr) {
  double *psd_results = (double *) malloc (N*sizeof (double));
  int psd_retcode = psd (N, data, psd_results);
  if (psd_retcode != MYLIB_SUCCESS) {
    free (psd_results);
    return psd_retcode;
  }
  else {
    int invfft_retcode = inverse_fft (N, psd_results, corr);
    free (psd_results);
    return invfft_retcode;
  }
}
