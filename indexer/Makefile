C = ../common
L = ../libcs50
PROGS = indexer indextest 
LIBS =
LLIBS = $C/common.a $L/libcs50.a



FLAGS = # -DAPPTEST # -DMEMTEST
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS) -I$L -I$C
CC = gcc
MAKE = make
.PHONY: all test clean

########### default ##################
all: $(PROGS)

########### indexer ##################
# indexer source dependencies
indexer: indexer.o $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@
indexer.o: $C/index.h $C/pagedir.h $C/word.h
indexer.o: $L/webpage.h $L/file.h $L/mem.h $L/counters.h $L/hashtable.h


########### indextest ##################
indextest: indextest.o $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@
# indextest source dependencies
indextest.o: $C/index.h
indextest.o: $L/hashtable.h

########### test ##################
test: indexer indextest  testing.sh
	bash -v testing.sh

clean:
	rm -f core
	rm -rf *~ *.o *.dSYM
	rm -f $(PROGS)




