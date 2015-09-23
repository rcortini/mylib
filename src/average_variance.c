#include "average_variance.h"

#define _AVERAGE(n,sum) ((sum)/(n))
#define _VARIANCE(n,av,sum2) ((n)/((n)-1.)*((sum2)/(n) - (av)*(av)));
#define _DEVST(var) (sqrt(var))



void calculate_sum (size_t n, double *data, double *sum) {
  size_t i;
  *sum=0.;
  for (i=0; i<n; i++)
    *sum += data[i];
}



void calculate_sum2 (size_t n, double *data, double *sum2) {
  size_t i;
  *sum2=0.;
  for (i=0; i<n; i++)
    *sum2 += data[i]*data[i];
}



void calculate_sum_sum2 (size_t n, double *data, double *sum, double *sum2) {
  size_t i;
  *sum=0.; *sum2=0.;
  for (i=0; i<n; i++) {
    double value=data[i];
    *sum += value;
    *sum2 += value*value;
  }
}



/* average and standard deviation of a vector */
size_t average (size_t N, double *data, double *av) {
  double sum;
  double n = (double) N; /* cast to double */

  /* check that we have at least two values for the determination of standard deviation */
  if (N==0) {
    err_message ("Insufficient data to perform average\n");
    return MYLIB_FAIL;
  }

  /* sum */
  calculate_sum (N, data, &sum);

  /* calculate average and standard deviation */
  *av = _AVERAGE (n,sum);

  return MYLIB_SUCCESS;
}



/* calculates only the variance */
size_t variance (size_t N, double *data, double *var) {
  double sum, sum2, av;
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
  *var = _VARIANCE (n,av,sum2);

  return MYLIB_SUCCESS;
}



/* calculates only the standard deviation */
size_t devst (size_t N, double *data, double *ds) {
  double var;
  size_t retcode = variance (N, data, &var);
  *ds = _DEVST (var);
  return retcode;
}



/* average and standard deviation of a vector */
size_t average_variance (size_t N, double *data, double *av, double *var) {
  double sum, sum2;
  double n = (double) N; /* cast to double */

  /* check that we have at least two values for the determination of standard deviation */
  if (N <= 1) {
    err_message ("Insufficient data to perform average and variance calculation\n");
    return MYLIB_FAIL;
  }

  /* calculate sum and square sum */
  calculate_sum_sum2 (N, data, &sum, &sum2);

  /* calculate average and standard deviation */
  *av = _AVERAGE (n,sum);
  
  /* calculate variance */
  *var = _VARIANCE (n,*av,sum2);

  return MYLIB_SUCCESS;
}



/* average and standard deviation of a vector */
size_t average_devst (size_t N, double *data, double *av, double *ds) {
  double sum, sum2, var;
  double n = (double) N; /* cast to double */

  /* check that we have at least two values for the determination of standard deviation */
  if (N <= 1) {
    err_message ("Insufficient data to perform average and standard deviation calculation\n");
    return MYLIB_FAIL;
  }

  /* calculate sum and square sum */
  calculate_sum_sum2 (N, data, &sum, &sum2);

  /* calculate average and standard deviation */
  *av = _AVERAGE (n,sum);
  
  /* calculate variance */
  var = _VARIANCE (n,*av,sum2);

  /* calculate standard deviation */
  *ds = _DEVST (var);

  return MYLIB_SUCCESS;
}



/* recurrence relationship for average:
 * mean(n+1) = mean(n) + (data(n+1)-mean(n))/(n+1).
 * CAREFUL: here "n" is exactly as in the formula above, that is
 * the number of data points that are already in the vector. */
int average_recurrence (size_t n, double average_old, double new_data, double *average_new) {
  if (n>0) {
    *average_new = average_old + (new_data-average_old)/(n+1);
    return MYLIB_SUCCESS;
  }
  else {
    err_message ("Called %s function with n = 0\n", __FUNCTION__);
    return MYLIB_FAIL;
  }
}

/* recurrence relationship for average:
 * var(n+1) = (n-1)/n * var(n) + (data(n+1)-mean(n))^2/(n+1).
 * CAREFUL: here "n" is exactly as in the formula above, that is
 * the number of data points that are already in the vector. */
int variance_recurrence (
    size_t n,
    double variance_old,
    double average_old,
    double new_data,
    double *variance_new) {
  if (n>1) {
    *variance_new = ((double) (n-1))/((double) (n))*variance_old
      + (new_data-average_old)*(new_data-average_old)/(n+1);
    return MYLIB_SUCCESS;
  }
  else {
    err_message ("Called %s function with n <= 1\n", __FUNCTION__);
    return MYLIB_FAIL;
  }
}
