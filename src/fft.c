#include "fft.h"



/* returns the real coefficient of the k-th frequency of a radix2 
 * or non-radix2 FFT */
double fft_real (unsigned int k, unsigned int N, double *fft_results) {
  if (k<N/2)
    return fft_results [k];
  else
    return fft_results [N-k];
}



/* returns the imaginary coefficient of the k-th frequency of a radix2 
 * or non-radix2 FFT. The storage convention for the two cases is different */
double fft_im (unsigned int k, unsigned int N, double *fft_results) {
  if (k==0 || k==N/2)
    return 0.;
  else {
    if (is_power_of_n (N,2))
      if (k<N/2)
	return fft_results [N-k];
      else
	return -fft_results [N-k];
    else
      if (k<N/2)
	return fft_results [k+1];
      else
	return -fft_results [N-k+1];
  }
}



/* prints the results of the fast Fourier transform fft_results */
void print_fft_results (unsigned int N, double *fft_results, unsigned int vflag) {
  unsigned int i;
  if (vflag) {
    printf ("FAST FOURIER TRANSFORM RESULTS:\n");
    for (i=0; i<N; i++)
      printf ("f[%d] = Re = %.8e Im = %.8e\n",
	  i,
	  fft_real (i, N, fft_results),
	  fft_im (i, N, fft_results));
  }
  else
    for (i=0; i<N; i++)
      printf ("%.8e %.8e\n",
	  fft_real (i, N, fft_results),
	  fft_im (i, N, fft_results));
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
    return gsl_fft_halfcomplex_radix2_inverse (fft_results, 1, N);
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



/* calculates the fast Fourier transform of a complex packed array, and stores
 * it into fft_results. The length of the array is 2*N, and the storage
 * convention is that the real and imaginary parts of the complex number are
 * stored in consecutive locations */
unsigned int complex_fft (unsigned int N, double *data, double *fft_results) {
  unsigned int i;

  /* initialize the data for fft */
  for (i=0; i<2*N; i++) fft_results [i] = data [i];

  /* use the corresponding routine if N is power of 2 */
  if (is_power_of_n (N,2)) {
    /* perform the fft */
    return gsl_fft_complex_radix2_forward (data, 1, N);
  }
  else {
    int retcode;

    /* alloc memory for wavetable and workspace */
    gsl_fft_complex_wavetable * wavetable = gsl_fft_complex_wavetable_alloc (N);
    gsl_fft_complex_workspace * workspace = gsl_fft_complex_workspace_alloc (N);

    /* perform the fft */
    retcode = gsl_fft_complex_forward (fft_results, 1, N, wavetable, workspace);

    /* free memory */
    gsl_fft_complex_wavetable_free (wavetable);
    gsl_fft_complex_workspace_free (workspace);

    return retcode;
  }
}



/* calculates the inverse fast Fourier transform of a complex packed array, and stores
 * it into fft_results. Storage conventions as for complex_fft */
unsigned int complex_inverse_fft (unsigned int N, double *data, double *fft_results) {
  unsigned int i;

  /* initialize the data for fft */
  for (i=0; i<2*N; i++) fft_results [i] = data [i];

  /* use the corresponding routine if N is power of 2 */
  if (is_power_of_n (N,2)) {
    /* perform the fft */
    return gsl_fft_complex_radix2_inverse (data, 1, N);
  }
  else {
    int retcode;

    /* alloc memory for wavetable and workspace */
    gsl_fft_complex_wavetable * wavetable = gsl_fft_complex_wavetable_alloc (N);
    gsl_fft_complex_workspace * workspace = gsl_fft_complex_workspace_alloc (N);

    /* perform the fft */
    retcode = gsl_fft_complex_inverse (fft_results, 1, N, wavetable, workspace);

    /* free memory */
    gsl_fft_complex_wavetable_free (wavetable);
    gsl_fft_complex_workspace_free (workspace);

    return retcode;
  }
}


/* calculates the power spectral density of the signal data and stores
 * it into psd_results */
unsigned int psd (unsigned int N, double *data, double *psd_results) {
  int retcode;
  unsigned int i;
  double *fft_results = (double *) malloc (N*sizeof (double));
  double *data_curated = (double *) malloc (N*sizeof (double));
  double data_average;

  /* subtract average from signal */
  average (N, data, &data_average);
  for (i=0; i<N; i++)
    data_curated [i] = data [i]-data_average;

  /* perform fft of signal */
  retcode = fft (N, data_curated, fft_results);

  /* set the psd as the square modulus of the resulting fft */
  for (i=0; i<N; i++) {
    double re = fft_real (i,N,fft_results);
    double im = fft_im (i,N,fft_results);
    psd_results [i] = re*re+im*im;
  }
  free (fft_results);
  free (data_curated);
  return retcode;
}
