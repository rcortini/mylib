#include "histogram.h"

size_t histogram (size_t N, double *data, size_t nbins, double bin_min, double bin_max, gsl_histogram **hist) {
  size_t i;

  /* prepare the gsl_histogram structure */
  *hist = gsl_histogram_alloc (nbins);
  gsl_histogram_set_ranges_uniform (*hist, bin_min, bin_max);

  /* populate the bins in the histogram */
  for (i=0; i<N; i++)
    gsl_histogram_increment (*hist, data [i]);

  /* success */
  return MYLIB_SUCCESS;
}
