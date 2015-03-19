#include <string.h>
#include <unistd.h>
#include "mylib.h"

const char *program_name = "mystat";

void print_usage () {
  printf ("Usage: %s [OPTIONS] <filename> <command> ...\n", program_name);
}

int main (int argc, char *argv[]) {
  int c, col = 1;
  unsigned int retcode;
  char *filename, *command;
  FILE *f_in;

  /* parse command line options */
  while ((c = getopt (argc, argv, "h::")) != -1) {
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
  log_message ("filename = %s\n", filename);
  if (strcmp (filename, "-")==0)
    f_in = stdin;
  else
    f_in = safe_fopen (filename, "r");

  /* the second non-option argument is the command name to execute */
  command = argv [optind+1];
  log_message ("command = %s\n", command);

  /* now check what is the command and act */
  if (strcmp (command, "average_variance")==0) {
    retcode = average_variance (f_in, col);
  }
  else {
    err_message ("Invalid command '%s'\n", command);
    print_usage ();
    exit (EXIT_FAILURE);
  }

  return retcode;
}
