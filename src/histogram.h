#ifndef __MYLIB_HISTOGRAM_H__
#define __MYLIB_HISTOGRAM_H__

#include <gsl/gsl_histogram.h>
#include "mylib_retcodes.h"

size_t histogram (size_t N, double *data, size_t nbins, double bin_min, double bin_max, gsl_histogram **hist);

#endif
