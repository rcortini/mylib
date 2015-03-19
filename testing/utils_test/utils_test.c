#include <stdio.h>
#include "utils.h"

const char *program_name = "utils_test";

int main () {
  unsigned int i, j, ncols=5, N;
  double **data;
  const char *big_file_name = "test_big_data.dat";

  /* read data from big file */
  N = read_data (big_file_name, ncols, &data);
  log_message ("read %d lines\n", N);
  for (i=0; i<N; i++) {
    for (j=0; j<ncols; j++)
      printf ("%f ", data[j][i]);
    printf ("\n");
  }

  /* free memory */
  for (i=0; i<ncols; i++)
    free (data [i]);
  free (data);
  return 0;
}
