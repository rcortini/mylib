#include <stdio.h>
#include "utils.h"

const char *program_name = "utils_test";

int main () {
  unsigned int N;
  double *x, *y, *sigma;
  const char *file_name = "test_data.dat";
  log_message ("Hello world!\n");
  err_message ("Error: %s\n", "error_number");
  N = read_data (file_name, &x, &y, &sigma);
  log_message ("read %d lines\n", N);
  free (x);
  free (y);
  free (sigma);
  return 0;
}
