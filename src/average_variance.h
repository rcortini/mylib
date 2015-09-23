#ifndef __MYLIB_AVERAGE_DEVST_H__
#define __MYLIB_AVERAGE_DEVST_H__

#include <stdio.h>
#include <math.h>
#include "mylib_retcodes.h"
#include "utils.h"

void calculate_sum (size_t n, double *data, double *sum);

void calculate_sum2 (size_t n, double *data, double *sum2);

void calculate_sum_sum2 (size_t n, double *data, double *sum, double *sum2);
 
size_t average (size_t N, double *data, double *av);

size_t variance (size_t N, double *data, double *var);

size_t devst (size_t N, double *data, double *ds);

size_t average_variance (size_t N, double *data, double *av, double *var);

size_t average_devst (size_t N, double *data, double *av, double *ds);

int average_recurrence (size_t n, double average_old, double new_data, double *average_new);

int variance_recurrence (
    size_t n,
    double variance_old,
    double average_old,
    double new_data,
    double *variance_new);

#endif
