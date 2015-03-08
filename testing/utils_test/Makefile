program=utils_test
program_sources=utils.c
program_main=$(program).c
program_objects=$(program_sources:.c=.o)

dependencies=utils.h

CFLAGS=-Wall -Wextra -Wshadow -g --pedantic -O0
LDFLAGS=

RM_F=rm -f
TAR=tar
CC=gcc

.PHONY: all clean 

all : $(program)

$(program): $(program_objects) $(program_main)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(program) $(program_main) $(program_objects) $(LDFLAGS)

# object files
%.o: %.c $(dependencies)
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

# clean targets
clean :
	$(RM_F) $(program_objects) $(program)
