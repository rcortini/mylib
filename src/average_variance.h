#ifndef __MYLIB_AVERAGE_DEVST_H__
#define __MYLIB_AVERAGE_DEVST_H__

#include <stdio.h>
#include <math.h>
#include "mylib_retcodes.h"
#include "utils.h"

unsigned int average (FILE *f_in, int col);

unsigned int variance (FILE *f_in, int col);

unsigned int devst (FILE *f_in, int col);

unsigned int average_variance (FILE *f_in, int col);

#endif
