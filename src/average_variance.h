#ifndef __MYLIB_AVERAGE_DEVST_H__
#define __MYLIB_AVERAGE_DEVST_H__

#include <stdio.h>
#include <math.h>
#include "mylib_retcodes.h"
#include "utils.h"

unsigned int average (unsigned int N, double *data, double *av);

unsigned int variance (unsigned int N, double *data, double *var);

unsigned int devst (unsigned int N, double *data, double *ds);

unsigned int average_variance (unsigned int N, double *data, double *av, double *var);

unsigned int average_devst (unsigned int N, double *data, double *av, double *ds);

#endif
