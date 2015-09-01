#ifndef __MYLIB_CORRELATION_H__
#define __MYLIB_CORRELATION_H__

#include "mylib_retcodes.h"
#include "fft.h"

size_t correlation (size_t N, double *data, double *corr);

#endif
