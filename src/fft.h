#ifndef __MYLIB_FFT_H__
#define __MYLIB_FFT_H__

#include "powers.h"
#include "utils.h"
#include "average_variance.h"
#include <gsl/gsl_fft_real.h>
#include <gsl/gsl_fft_halfcomplex.h>
#include <gsl/gsl_fft_complex.h>

void print_fft_results (size_t N, double *fft_results, size_t vflag);

int fft (size_t N, double *data, double *fft_results);

int inverse_fft (size_t N, double *data, double *fft_results);

int complex_fft (size_t N, double *data, double *fft_results);

int complex_inverse_fft (size_t N, double *data, double *fft_results);

int psd (size_t N, double *data, double *psd_results);

#endif
