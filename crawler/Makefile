# Makefile for 'crawler' program
# Jefferson Adjetey- CS50 Winter 2022 
CC = gcc
CLFAGS = -Wall -pedantic -std=c11 -ggdb -I../libcs50

OBJS = crawler.o
LIBS = -lm
LLIBS = ../libcs50/libcs50.a ../common/common.a
MAKE = make

# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

.PHONY: all clean test

all: crawler

test: crawler testing.sh
	bash -v testing.sh

# executable depends on object files

crawler: $(OBJS) $(LLIBS)
		$(CC) $(CFLAGS) $(OBJS) $(LLIBS) $(LIBS) -o crawler

# object files depend on include files

crawler.o: ../libcs50/webpage.h ../libcs50/bag.h ../libcs50/hashtable.h ../common/pagedir.h

valgrind: crawler
	$(VALGRIND) ./crawler

clean:
	rm -f *~ *.o
	rm -f crawler
	rm -rf *.dSYM

