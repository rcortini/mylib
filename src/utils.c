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

/* checks if a file exists. should be very portable */
int file_exists (const char *filename) {
  if (access (filename, F_OK) != -1) {
    return 1;
  }
  else {
    return 0;
  }
}

/* reads the data file f_in and scans for ncols columns, specified by the
 * vector cols, and stores the data into data */
unsigned int read_data (FILE *f_in, unsigned int ncols, unsigned int *cols, double ***data) {
  unsigned int i, j, n, vector_size;
  char word [MAX_LINE_SIZE];

  /* check the "cols" array */
  for (i=1; i<ncols; i++)
    if (cols[i]<=cols[i-1]) {
      err_message ("\"cols\" vector must be strictly increasing!\n");
      exit (EXIT_FAILURE);
    }

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
      int bytes_now=0, bytes_consumed=0;
      i=0;
      j=0;
      while (i<ncols) {
	if (sscanf (word+bytes_consumed, "%lf%n", &val, &bytes_now) == 1) {
	  bytes_consumed += bytes_now;
	  if (j==cols[i])
	    (*data) [i++] [n] = val;
	  j++;
	}
	else {
	  err_message ("Error reading column number %d!\n", j);
	  exit (EXIT_FAILURE);
	}
      }
      n++;
    }
  }

  /* return the number of lines read */
  return n;
}

/* parses a list of ranges, as specified by commas and dashes */
unsigned int parse_ranges (const char *orig_string, unsigned int **cols) {
  unsigned int i, n = 0, ncols = 0;
  const char *comma = ",", *dash = "-";
  char *string, *token;
  char *vals [MAX_RANGES];

  /* alloc memory for the cols vector */
  *cols = (unsigned int *) malloc (MAX_RANGES * sizeof (unsigned int));

  /* copy the original string to a new one, since the function
   * strtok will modify it */
  string = strdup (orig_string);

  /* extract comma-separated values */
  token = strtok (string, comma);
  vals [n++] = token;
  while (token) {
    token = strtok (NULL, comma);
    vals [n++] = token;
  }
  n--;

  /* search for dashes in the values */
  for (i=0; i<n; i++) {
    /* seeks for a dash */
    token = strtok (vals [i], dash);
    sscanf (token, "%u", &(*cols) [ncols++]);

    /* seeks for another dash */
    token = strtok (NULL, dash);
    if (token) {
      unsigned int prev = (*cols) [ncols-1];
      unsigned int tmp;
      sscanf (token, "%u", &tmp);
      if (tmp <= prev) {
	err_message ("Invalid range specified\n");
	exit (EXIT_FAILURE);
      }
      while (prev++!=tmp)
	(*cols) [ncols++] = prev;
    }
  }

  free (string);
  return ncols;
}
