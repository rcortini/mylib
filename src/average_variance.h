#ifndef __MYLIB_AVERAGE_DEVST_H__
#define __MYLIB_AVERAGE_DEVST_H__

#include <stdio.h>
#include <math.h>
#include "mylib_retcodes.h"
#include "utils.h"

size_t average (size_t N, double *data, double *av);

size_t variance (size_t N, double *data, double *var);

size_t devst (size_t N, double *data, double *ds);

size_t average_variance (size_t N, double *data, double *av, double *var);

size_t average_devst (size_t N, double *data, double *av, double *ds);

#endif
