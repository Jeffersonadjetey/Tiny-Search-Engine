OBJS = pagedir.o word.o index.o
LIB = common.a
LIBS =../libcs50/libcs50.a
L = ../libcs50

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb  -I../libcs50
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all 

$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

# Dependencies:
index.o: index.h $L/file.h $L/counters.h $L/hashtable.h
pagedir.o: pagedir.h $L/mem.h $L/file.h $L/webpage.h
word.o: word.h

.PHONY: test valgrind clean

clean:
	rm -f *~ *.o
	rm -f $(LIB) *~ *.o




