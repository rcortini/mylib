#include <stdio.h>
#include "utils.h"

const char *program_name = "utils_test";

int main () {
  size_t i, j, col_n=4, N;
  /* double **data; */
  double *data;
  const char *big_file_name = "test_big_data.dat";
  FILE *f_in = safe_fopen (big_file_name, "r");

  /* read data from big file */
  /* N = read_data (f_in, ncols, &data);
  log_message ("read %d lines\n", N);
  for (i=0; i<N; i++) {
    for (j=0; j<ncols; j++)
      printf ("%f ", data[j][i]);
    printf ("\n");
  } */

  /* free memory */
  /* for (i=0; i<ncols; i++)
    free (data [i]);
  free (data); */

  /* N = read_data_single_col (f_in, col_n, &data); */
  N = read_data_single_col (stdin, col_n, &data);
  log_message ("read %d lines\n", N);
  for (i=0; i<N; i++)
    printf ("%f\n", data[i]);
  free (data);

  /* close input file */
  fclose (f_in);
  return 0;
}
