#ifndef __MYLIB_HISTOGRAM_H__
#define __MYLIB_HISTOGRAM_H__

#include <gsl/gsl_histogram.h>
#include "mylib_retcodes.h"

unsigned int histogram (unsigned int N, double *data, unsigned int nbins, double bin_min, double bin_max, gsl_histogram **hist);

#endif
