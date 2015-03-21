#ifndef __MYLIB_FFT_H__
#define __MYLIB_FFT_H__

#include "powers.h"
#include <stdio.h>
#include <gsl/gsl_fft_real.h>
#include <gsl/gsl_fft_halfcomplex.h>

double fft_real_radix2 (unsigned int k, unsigned int N, double *fft_results);

double fft_im_radix2 (unsigned int k, unsigned int N, double *fft_results);

double fft_real (unsigned int k, unsigned int N, double *fft_results);

double fft_im (unsigned int k, unsigned int N, double *fft_results);

void print_fft_results (unsigned int N, double *fft_results, unsigned int vflag);

unsigned int fft (unsigned int N, double *data, double *fft_results);

unsigned int inverse_fft (unsigned int N, double *data, double *fft_results);

#endif
