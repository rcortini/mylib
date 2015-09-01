#ifndef __MYLIB_FFT_H__
#define __MYLIB_FFT_H__

#include "powers.h"
#include "utils.h"
#include "average_variance.h"
#include <gsl/gsl_fft_real.h>
#include <gsl/gsl_fft_halfcomplex.h>
#include <gsl/gsl_fft_complex.h>

double fft_real (size_t k, size_t N, double *fft_results);

double fft_im (size_t k, size_t N, double *fft_results);

void print_fft_results (size_t N, double *fft_results, size_t vflag);

size_t fft (size_t N, double *data, double *fft_results);

size_t inverse_fft (size_t N, double *data, double *fft_results);

size_t complex_fft (size_t N, double *data, double *fft_results);

size_t complex_inverse_fft (size_t N, double *data, double *fft_results);

size_t psd (size_t N, double *data, double *psd_results);

#endif
