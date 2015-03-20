#include <string.h>
#include <unistd.h>
#include "mylib.h"

const char *program_name = "mystat";

void print_usage () {
  printf ("Usage: %s [OPTIONS] <filename> <command> ...\n", program_name);
  printf ("Commands:\n");
  printf ("\taverage\n");
  printf ("\tvariance\n");
  printf ("\tdevst\n");
  printf ("\taverage_variance\n");
  printf ("\taverage_devst\n");
  printf ("\thistogram <bin_min> <bin_max> <n_bins>\n");
}

int main (int argc, char *argv[]) {
  int c, col = 1;
  unsigned int retcode;
  char *filename, *command;
  FILE *f_in;
  gsl_error_handler_t *old_handler = gsl_set_error_handler_off ();
  (void) old_handler;

  /* parse command line options */
  while ((c = getopt (argc, argv, "c:h::")) != -1) {
    switch (c) {
      case 'h' :
	print_usage (program_name);
	exit (0);
	break;
      case 'c' :
	col = atoi (optarg);
	if (col<1) {
	  err_message ("Column numbers start from 1!\n");
	  exit (EXIT_FAILURE);
	}
	break;
      default :
	err_message ("Incorrect usage\n");
	print_usage (program_name);
	exit (EXIT_FAILURE);
    }
  };

  /* check for proper invocation */
  if (argc < 3) {
    err_message ("Incorrect usage\n");
    print_usage (program_name);
    exit (EXIT_FAILURE);
  }

  /* the first non-option argument is the filename to read */
  filename = argv [optind];
  if (strcmp (filename, "-")==0)
    f_in = stdin;
  else
    f_in = safe_fopen (filename, "r");

  /* the second non-option argument is the command name to execute */
  command = argv [optind+1];

  /* now check what is the command and act */
  if (strcmp (command, "average_variance")==0) {
    double av, var;
    double *data;
    unsigned int N = read_data_single_col (f_in, col, &data);
    retcode = average_variance (N, data, &av, &var);
    log_message ("average = %.8e, variance = %.8e\n", av, var);
    free (data);
  }
  else if (strcmp (command, "average_devst")==0) {
    double av, ds;
    double *data;
    unsigned int N = read_data_single_col (f_in, col, &data);
    retcode = average_devst (N, data, &av, &ds);
    log_message ("average = %.8e, standard deviation = %.8e\n", av, ds);
    free (data);
  }
  else if (strcmp (command, "average")==0) {
    double av;
    double *data;
    unsigned int N = read_data_single_col (f_in, col, &data);
    retcode = average (N, data, &av);
    log_message ("average = %.8e\n", av);
    free (data);
  }
  else if (strcmp (command, "devst")==0) {
    double ds;
    double *data;
    unsigned int N = read_data_single_col (f_in, col, &data);
    retcode = devst (N, data, &ds);
    log_message ("standard deviation = %.8e\n", ds);
    free (data);
  }
  else if (strcmp (command, "variance")==0) {
    double var;
    double *data;
    unsigned int N = read_data_single_col (f_in, col, &data);
    retcode = variance (N, data, &var);
    log_message ("variance = %.8e\n", var);
    free (data);
  }
  else if (strcmp (command, "histogram")==0) {
    unsigned int i, N, argstart=optind+2, nbins;
    double bin_min, bin_max, sum;
    double *data;
    gsl_histogram *hist;/*   = NULL; */

    /* get input parameters */
    if (argc-optind < 5) {
      err_message ("Insufficient arguments for histogram\n");
      print_usage ();
      exit (EXIT_FAILURE);
    }
    bin_min = atof (argv [argstart]);
    bin_max = atof (argv [argstart+1]);
    nbins = atoi (argv [argstart+2]);

    /* read data */
    N = read_data_single_col (f_in, col, &data);

    /* calculate histogram */
    retcode = histogram (N, data, nbins, bin_min, bin_max, &hist);

    /* get total number of values in the histogram */
    sum = gsl_histogram_sum (hist);

    /* output */
    for (i=0; i<nbins; i++) {
      double lower, upper, mean;

      /* get the range of the i-th bin in the histogram, and calculate mean */
      gsl_histogram_get_range (hist, i, &lower, &upper);
      mean = (upper+lower)/2.;

      /* write line in file */
      printf ("%f %f\n", mean, gsl_histogram_get (hist, i)/sum);
    }

    /* free memory */
    gsl_histogram_free (hist);
    free (data);
  }
  else if (strcmp (command, "weighted_linear_fit")==0) {
    double **data;
    unsigned int i, N = read_data (f_in, 3, &data);
    double *w = (double *) malloc (N*sizeof (double));
    double *x, *y;
    linear_fit_results fit_results;

    /* check the values of the input sigmas  and assign weights*/
    for (i=0; i<N; i++) {
      double s = data [2][i];
      if (s==0) {
	err_message ("Zero variance point encountered in weighted linear fit!\n");
	return MYLIB_FAIL;
      }
      w [i] = 1./(s*s);
    }
    x = data[0];
    y = data[1];

    /* do the fit */
    retcode = weighted_linear_fit (N, x, y, w, &fit_results);

    /* print result */
    print_linear_fit_results (retcode, &fit_results);

    /* success */
    free (data[0]);
    free (data[1]);
    free (data[2]);
    free (w);
    free (data);
  }
  else if (strcmp (command, "linear_fit")==0) {
    double **data;
    unsigned int N = read_data (f_in, 2, &data);
    double *x, *y;
    linear_fit_results fit_results;
    x = data[0];
    y = data[1];

    /* do the fit */
    retcode = linear_fit (N, x, y, &fit_results);

    /* print result */
    print_linear_fit_results (retcode, &fit_results);

    /* success */
    free (data[0]);
    free (data[1]);
    free (data);
  }
  else {
    err_message ("Invalid command '%s'\n", command);
    print_usage ();
    exit (EXIT_FAILURE);
  }

  /* close input file */
  fclose (f_in);

  return retcode;
}
