#ifndef __MYLIB_UTILS_H__
#define __MYLIB_UTILS_H__

#include <stdio.h>
#include <stdarg.h>

void log_message (const char *text, ...);

void err_message (const char *text, ...);

FILE *safe_fopen (const char *path, const char *mode);

int safe_realloc (unsigned int new_vector_size, double **vector);

unsigned int read_data (const char *input_file, double **x, double **y, double **sigma);

#endif
