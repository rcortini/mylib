#include <stdio.h>
#include "utils.h"

const char *program_name = "utils_test";

int main () {
  log_message ("Hello world!\n");
  err_message ("Error: %s\n", "error_number");
  return 0;
}
