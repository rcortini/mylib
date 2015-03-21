#include "fft.h"



/* returns the real coefficient of the k-th frequency of a radix2 FFT */
double fft_real_radix2 (unsigned int k, unsigned int N, double *fft_results) {
  if (k<N/2)
    return fft_results [k];
  else
    return fft_results [N-k];
}



/* returns the real coefficient of the k-th frequency of a radix2 FFT */
double fft_im_radix2 (unsigned int k, unsigned int N, double *fft_results) {
  if (k==0 || k==N/2)
    return 0.;
  else
    if (k<N/2)
      return fft_results [N-k];
    else
      return -fft_results [N-k];
}



/* returns the real coefficient of the k-th frequency of a FFT */
double fft_real (unsigned int k, unsigned int N, double *fft_results) {
  if (k<N/2)
    return fft_results [k];
  else
    return fft_results [N-k];
}



/* returns the real coefficient of the k-th frequency of a FFT */
double fft_im (unsigned int k, unsigned int N, double *fft_results) {
  if (k==0 || k==N/2)
    return 0.;
  else
    if (k<N/2)
      return fft_results [k+1];
    else
      return -fft_results [N-k+1];
}



/* prints the results of the fast Fourier transform fft_results */
void print_fft_results (unsigned int N, double *fft_results, unsigned int vflag) {
  unsigned int i;
  if (vflag) {
    printf ("FAST FOURIER TRANSFORM RESULTS:\n");
    if (is_power_of_n (N,2))
      for (i=0; i<N; i++)
	printf ("f[%d] = Re = %.8e Im = %.8e\n",
	    i,
	    fft_real_radix2 (i, N, fft_results),
	    fft_im_radix2 (i, N, fft_results));
    else
      for (i=0; i<N; i++)
	printf ("f[%d] = Re = %.8e Im = %.8e\n",
	    i,
	    fft_real (i, N, fft_results),
	    fft_im (i, N, fft_results));
  }
  else {
    if (is_power_of_n (N,2))
      for (i=0; i<N; i++)
	printf ("%.8e %.8e\n",
	    fft_real_radix2 (i, N, fft_results),
	    fft_im_radix2 (i, N, fft_results));
    else
      for (i=0; i<N; i++)
	printf ("%.8e %.8e\n",
	    fft_real (i, N, fft_results),
	    fft_im (i, N, fft_results));
  }
}


/* calculates the fast Fourier transform of signal data, stores it into fft_results */
unsigned int fft (unsigned int N, double *data, double *fft_results) {
  unsigned int i;

  /* initialize the data for fft */
  for (i=0; i<N; i++) fft_results [i] = data [i];

  /* use the corresponding routine if N is power of 2 */
  if (is_power_of_n (N,2)) {
    /* perform the fft */
    return gsl_fft_real_radix2_transform (fft_results, 1, N);
  }
  else {
    int retcode;

    /* alloc memory for real and half-complex wavetables, and workspace */
    gsl_fft_real_wavetable *real_wavetable = gsl_fft_real_wavetable_alloc (N);
    gsl_fft_real_workspace *ws = gsl_fft_real_workspace_alloc (N);

    /* perform the fft */
    retcode = gsl_fft_real_transform (fft_results, 1, N, real_wavetable, ws);

    /* free memory */
    gsl_fft_real_wavetable_free (real_wavetable);
    gsl_fft_real_workspace_free (ws);

    return retcode;
  }
}



/* calculates the inverse Fourier transform of signal data (half-complex),
 * and stores it into fft_results */
unsigned int inverse_fft (unsigned int N, double *data, double *fft_results) {
  unsigned int i;

  /* initialize the data for fft */
  for (i=0; i<N; i++) fft_results [i] = data [i];

  /* use the corresponding routine if N is power of 2 */
  if (is_power_of_n (N,2)) {
    /* perform the fft */
    return gsl_fft_halfcomplex_radix2_transform (fft_results, 1, N);
  }
  else {
    int retcode;

    /* alloc memory for real and half-complex wavetables, and workspace */
    gsl_fft_halfcomplex_wavetable *hc_wavetable = gsl_fft_halfcomplex_wavetable_alloc (N);
    gsl_fft_real_workspace *ws = gsl_fft_real_workspace_alloc (N);

    /* perform the fft */
    retcode = gsl_fft_halfcomplex_inverse (fft_results, 1, N, hc_wavetable, ws);

    /* free memory */
    gsl_fft_halfcomplex_wavetable_free (hc_wavetable);
    gsl_fft_real_workspace_free (ws);

    return retcode;
  }
}
