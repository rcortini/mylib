#include "fft.h"


/* prints the results of the fast Fourier transform fft_results */
void print_fft_results (size_t N, double *fft_results, size_t vflag) {
  size_t i;
  if (vflag) {
    printf ("FAST FOURIER TRANSFORM RESULTS:\n");
    for (i=0; i<N; i++)
      printf ("f[%lu] = Re = %.8e Im = %.8e\n",
	  i,
	  fft_results [2*i],
	  fft_results [2*i+1]);
  }
  else
    for (i=0; i<N; i++)
      printf ("%.8e %.8e\n",
	  fft_results [2*i],
	  fft_results [2*i+1]);
}



/* calculates the fast Fourier transform of signal data, stores it into fft_results */
int fft (size_t N, double *data, double *fft_results) {
  size_t i;
  double *fft_data = (double *) calloc (N, sizeof (double));
  int retcode;

  /* initialize the data for fft */
  for (i=0; i<N; i++) fft_data [i] = data [i];

  /* use the corresponding routine if N is power of 2 */
  if (is_power_of_n (N,2)) {
    /* perform the fft */
    retcode = gsl_fft_real_radix2_transform (fft_data, 1, N);
    gsl_fft_halfcomplex_radix2_unpack (fft_data, fft_results, 1, N);
  }
  else {
    /* alloc memory for real and half-complex wavetables, and workspace */
    gsl_fft_real_wavetable *real_wavetable = gsl_fft_real_wavetable_alloc (N);
    gsl_fft_real_workspace *ws = gsl_fft_real_workspace_alloc (N);

    /* perform the fft */
    retcode = gsl_fft_real_transform (fft_data, 1, N, real_wavetable, ws);
    gsl_fft_halfcomplex_unpack (fft_data, fft_results, 1, N);

    /* free memory */
    gsl_fft_real_wavetable_free (real_wavetable);
    gsl_fft_real_workspace_free (ws);
  }
  free (fft_data);
  return retcode;
}



/* calculates the inverse Fourier transform of signal data (half-complex),
 * and stores it into fft_results */
int inverse_fft (size_t N, double *data, double *fft_results) {
  size_t i;
  int retcode;
  double *fft_data = (double *) calloc (N, sizeof (double));

  /* initialize the data for fft */
  for (i=0; i<N; i++) fft_data [i] = data [i];

  /* use the corresponding routine if N is power of 2 */
  if (is_power_of_n (N,2)) {
    /* perform the fft */
    retcode = gsl_fft_halfcomplex_radix2_inverse (fft_results, 1, N);
    gsl_fft_halfcomplex_radix2_unpack (fft_data, fft_results, 1, N);
  }
  else {
    /* alloc memory for real and half-complex wavetables, and workspace */
    gsl_fft_halfcomplex_wavetable *hc_wavetable = gsl_fft_halfcomplex_wavetable_alloc (N);
    gsl_fft_real_workspace *ws = gsl_fft_real_workspace_alloc (N);

    /* perform the fft */
    retcode = gsl_fft_halfcomplex_inverse (fft_data, 1, N, hc_wavetable, ws);
    gsl_fft_halfcomplex_unpack (fft_data, fft_results, 1, N);

    /* free memory */
    gsl_fft_halfcomplex_wavetable_free (hc_wavetable);
    gsl_fft_real_workspace_free (ws);

  }
  free (fft_data);
  return retcode;
}



/* calculates the fast Fourier transform of a complex packed array, and stores
 * it into fft_results. The length of the array is 2*N, and the storage
 * convention is that the real and imaginary parts of the complex number are
 * stored in consecutive locations */
int complex_fft (size_t N, double *data, double *fft_results) {
  size_t i;
  int retcode;

  /* initialize the data for fft */
  for (i=0; i<2*N; i++) fft_results [i] = data [i];

  /* use the corresponding routine if N is power of 2 */
  if (is_power_of_n (N,2)) {
    /* perform the fft */
    retcode = gsl_fft_complex_radix2_forward (fft_results, 1, N);
  }
  else {
    /* alloc memory for wavetable and workspace */
    gsl_fft_complex_wavetable * wavetable = gsl_fft_complex_wavetable_alloc (N);
    gsl_fft_complex_workspace * workspace = gsl_fft_complex_workspace_alloc (N);

    /* perform the fft */
    retcode = gsl_fft_complex_forward (fft_results, 1, N, wavetable, workspace);

    /* free memory */
    gsl_fft_complex_wavetable_free (wavetable);
    gsl_fft_complex_workspace_free (workspace);
  }
  return retcode;
}



/* calculates the inverse fast Fourier transform of a complex packed array, and stores
 * it into fft_results. Storage conventions as for complex_fft */
int complex_inverse_fft (size_t N, double *data, double *fft_results) {
  size_t i;
  int retcode;

  /* initialize the data for fft */
  for (i=0; i<2*N; i++) fft_results [i] = data [i];

  /* use the corresponding routine if N is power of 2 */
  if (is_power_of_n (N,2)) {
    /* perform the fft */
    retcode = gsl_fft_complex_radix2_inverse (fft_results, 1, N);
  }
  else {
    /* alloc memory for wavetable and workspace */
    gsl_fft_complex_wavetable * wavetable = gsl_fft_complex_wavetable_alloc (N);
    gsl_fft_complex_workspace * workspace = gsl_fft_complex_workspace_alloc (N);

    /* perform the fft */
    retcode = gsl_fft_complex_inverse (fft_results, 1, N, wavetable, workspace);

    /* free memory */
    gsl_fft_complex_wavetable_free (wavetable);
    gsl_fft_complex_workspace_free (workspace);
  }
  return retcode;
}


/* calculates the power spectral density of the signal data and stores
 * it into psd_results */
int psd (size_t N, double *data, double *psd_results) {
  int retcode;
  size_t i;
  double *fft_results = (double *) malloc (2*N*sizeof (double));

  /* perform fft of signal */
  retcode = fft (N, data, fft_results);

  /* set the psd as the square modulus of the resulting fft */
  for (i=0; i<N; i++) {
    double re = fft_results [2*i];
    double im = fft_results [2*i+1];
    psd_results [i] = re*re+im*im;
  }
  free (fft_results);
  return retcode;
}
