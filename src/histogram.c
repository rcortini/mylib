#include "histogram.h"

unsigned int histogram (unsigned int N, double *data, unsigned int nbins, double bin_min, double bin_max) {
  unsigned int i, sum;

  /* prepare the gsl_histogram structure */
  gsl_histogram *hist = gsl_histogram_alloc (nbins);
  gsl_histogram_set_ranges_uniform (hist, bin_min, bin_max);

  /* increment the corresponding bin in the histogram */
  for (i=0; i<N; i++)
    gsl_histogram_increment (hist, data [i]);

  /* get total number of values in the histogram */
  sum = gsl_histogram_sum (hist);

  /* output */
  for (i=0; i<nbins; i++) {
    double lower, upper, mean;
    
    /* get the range of the i-th bin in the histogram, and calculate mean */
    gsl_histogram_get_range (hist, i, &lower, &upper);
    mean = (upper+lower)/2.;

    /* write line in file */
    printf ("%f %f\n", mean, gsl_histogram_get (hist, i)/sum);
  }

  /* free memory, close files, and exit */
  gsl_histogram_free (hist);

  /* success */
  return MYLIB_SUCCESS;
}
