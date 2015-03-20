#include "histogram.h"

unsigned int histogram (unsigned int N, double *data, unsigned int nbins, double bin_min, double bin_max, gsl_histogram **hist) {
  unsigned int i, sum;

  /* prepare the gsl_histogram structure */
  *hist = gsl_histogram_alloc (nbins);
  gsl_histogram_set_ranges_uniform (*hist, bin_min, bin_max);

  /* populate the bins in the histogram */
  for (i=0; i<N; i++)
    gsl_histogram_increment (*hist, data [i]);

  /* success */
  return MYLIB_SUCCESS;
}
