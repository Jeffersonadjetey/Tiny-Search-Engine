# Jefferson Adjetey, February 2022
#
# Makefile fir the 'querier' program
#
#


PROG = querier fuzzquery

OBJS = querier.o fuzzquery.o
LIBS = ../common/common.a ../libcs50/libcs50.a 

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../common -I../libcs50  
CC = gcc 
MAKE = make

.PHONY: test clean all

all: $(PROG)

fuzzquery: fuzzquery.o $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@

querier: querier.o $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@



test: querier testing.sh
	bash -v testing.sh

clean:
	rm -rf *.dSYM  
	rm -f *~ *.o
	rm -f $(PROG)
	
