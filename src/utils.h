#ifndef __MYLIB_UTILS_H__
#define __MYLIB_UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE_SIZE 4096
#define CHUNK_SIZE 100
#define MAX_RANGES 100

void log_message (const char *text, ...);

void err_message (const char *text, ...);

FILE *safe_fopen (const char *path, const char *mode);

int safe_realloc (unsigned int new_vector_size, double **vector);

int file_exists (const char *filename);

unsigned int read_data (FILE *f_in, unsigned int ncols, unsigned int *cols, double ***data);

unsigned int parse_ranges (const char *orig_string, unsigned int **cols);

#endif
