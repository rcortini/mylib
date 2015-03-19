#include "utils.h"

extern const char *program_name;

/* a function to display a message */
void log_message (const char *text, ...) {
  va_list args;
  printf ("%s: INFO: ", program_name);
  va_start (args, text);
  vfprintf (stdout, text, args);
  va_end (args);
  fflush (stdout);
}

/* a function to display an error message */
void err_message (const char *text, ...) {
  va_list args;
  fprintf (stderr, "%s: ERROR: ", program_name);
  va_start (args, text);
  vfprintf (stderr, text, args);
  va_end (args);
  fflush (stderr);
}

/* a function that checks the return value of fopen */
FILE *safe_fopen (const char *path, const char *mode) {
  FILE *fp = fopen (path, mode);
  if (fp == NULL) {
    err_message ("Could not open %s\n", path);
    exit (EXIT_FAILURE);
  }
  else
    return fp;
}

/* a function that checks the return value of realloc */
int safe_realloc (unsigned int new_vector_size, double **vector) {
  double *is_null;
  is_null = (double *) realloc (*vector, new_vector_size * sizeof (double));
  if (is_null == NULL)
    return 1;
  *vector = is_null;
  return 0;
}

/* reads the first ncols of data from input_file, and stores the values
 * in the data [i] pointer */
unsigned int read_data (const char *input_file, unsigned int ncols, double ***data) {
  unsigned int i, n, vector_size;
  char word [MAX_LINE_SIZE];
  FILE *f_in = safe_fopen (input_file, "r");

  /* initialize the vectors to read */
  vector_size = CHUNK_SIZE;
  *data = (double **) malloc (ncols * (sizeof (double *)));
  for (i=0; i<ncols; i++)
    (*data) [i] = (double *) malloc (vector_size * sizeof (double));

  /* scan the input file */
  n = 0;
  while (fgets (word, sizeof (word), f_in) != NULL) { 
    double val;

    /* expand the data array if necessary */
    if (n>vector_size-1) {
      vector_size += CHUNK_SIZE;
      for (i=0; i<ncols; i++)
	if (safe_realloc (vector_size, &(*data) [i])) {
	  err_message ("No more memory!\n");
	  exit (EXIT_FAILURE);
	}
    }

    /* if it is not a comment, scan a line */
    if (word [0] == '#')
      continue;
    else {
      FILE *stream = fmemopen (word, MAX_LINE_SIZE, "r");
      for (i=0; i<ncols; i++) {
	int nvals = fscanf (stream, "%lf ", &val);
	if (nvals == 0) {
	  err_message ("File does not contain %d columns!\n", ncols);
	  exit (EXIT_FAILURE);
	}
	else 
	  (*data) [i] [n] = val;
      }
      fclose (stream);
      n++;
    }
  }
  fclose (f_in);

  return n;
}
