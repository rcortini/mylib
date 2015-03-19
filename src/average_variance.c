#include "average_variance.h"

#define _AVERAGE(n,sum) (sum/n)
#define _VARIANCE(n,av,sum2) (n/(n-1.)*(sum2/n - av*av));
#define _DEVST(var) (sqrt(var))

void calculate_sum (unsigned int n, double *data, double *sum) {
  unsigned int i;
  *sum=0.;
  for (i=0; i<n; i++)
    *sum += data[i];
}

void calculate_sum_sum2 (unsigned int n, double *data, double *sum, double *sum2) {
  unsigned int i;
  *sum=0.; *sum2=0.;
  for (i=0; i<n; i++) {
    double value=data[i];
    *sum += value;
    *sum2 += value*value;
  }
}

/* average and standard deviation of a vector */
unsigned int average (FILE *f_in, int col) {
  double sum, av;
  double *data;
  unsigned int N = read_data_single_col (f_in, col, &data);
  double n = (double) N; /* cast to double */

  /* check that we have at least two values for the determination of standard deviation */
  if (N==0) {
    err_message ("Insufficient data to perform average\n");
    return MYLIB_FAIL;
  }

  /* sum */
  calculate_sum (N, data, &sum);

  /* calculate average and standard deviation */
  av = _AVERAGE (n,sum);

  /* output */
  log_message ("average = %.8e\n", av);

  return MYLIB_SUCCESS;
}


/* calculates only the variance */
unsigned int variance (FILE *f_in, int col) {
  double sum, sum2, av, var;
  double *data;
  unsigned int N = read_data_single_col (f_in, col, &data);
  double n = (double) N; /* cast to double */

  /* check that we have at least two values for the determination of standard deviation */
  if (N <= 1) {
    err_message ("Insufficient data to perform calculation of variance\n");
    return MYLIB_FAIL;
  }

  /* calculate sum and square sum */
  calculate_sum_sum2 (N, data, &sum, &sum2);

  /* calculate average and standard deviation */
  av = _AVERAGE (n,sum);
  
  /* calculate variance */
  var = _VARIANCE (n,av,sum2);

  /* output */
  log_message ("variance = %.8e\n", var);

  return MYLIB_SUCCESS;
}

/* calculates only the standard deviation */
unsigned int devst (FILE *f_in, int col) {
  double var = variance (f_in, col);
  double devst = _DEVST (var);
  log_message ("devst = %.8e\n", devst);
  return MYLIB_SUCCESS;
}

/* average and standard deviation of a vector */
unsigned int average_variance (FILE *f_in, int col) {
  double sum, sum2, av, var;
  double *data;
  unsigned int N = read_data_single_col (f_in, col, &data);
  double n = (double) N; /* cast to double */

  /* check that we have at least two values for the determination of standard deviation */
  if (N <= 1) {
    err_message ("Insufficient data to perform average and variance calculation\n");
    return MYLIB_FAIL;
  }

  /* calculate sum and square sum */
  calculate_sum_sum2 (N, data, &sum, &sum2);

  /* calculate average and standard deviation */
  av = _AVERAGE (n,sum);
  
  /* calculate variance */
  var = _VARIANCE (n,av,sum2);

  /* output */
  log_message ("average = %.8e, variance = %.8e\n", av, var);

  return MYLIB_SUCCESS;
}

/* average and standard deviation of a vector */
unsigned int average_devst (FILE *f_in, int col) {
  double sum, sum2, av, var, ds;
  double *data;
  unsigned int N = read_data_single_col (f_in, col, &data);
  double n = (double) N; /* cast to double */

  /* check that we have at least two values for the determination of standard deviation */
  if (N <= 1) {
    err_message ("Insufficient data to perform average and standard deviation calculation\n");
    return MYLIB_FAIL;
  }

  /* calculate sum and square sum */
  calculate_sum_sum2 (N, data, &sum, &sum2);

  /* calculate average and standard deviation */
  av = _AVERAGE (n,sum);
  
  /* calculate variance */
  var = _VARIANCE (n,av,sum2);

  /* calculate standard deviation */
  ds = _DEVST (var);

  /* output */
  log_message ("average = %.8e, standard deviation = %.8e\n", av, ds);

  return MYLIB_SUCCESS;
}


