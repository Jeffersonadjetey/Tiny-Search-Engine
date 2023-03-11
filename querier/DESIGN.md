### TSE Querier Design Spec

###Jefferson Adjetey, Dartmouth CS50, Summer 2020

In this document we reference the Requirements Specification and focus on the implementation-independent design decisions. The knowledge unit noted that an design spec may include many topics; not all are relevant to the TSE or the Crawler. Here we focus on the core subset:


### User interface
The user interface of the querier is while on the command-line. This uses two arguments:
```c
./querier pageDirectory indexFilename
```

### Inputs and Output
Input = command-line parameters

Output = results of the query including the score, document ID, and URL.

```c
### Functional Decomposition into modules
1. main, which parses arguments and initializes other modules
2. countersUnionHelper, used for or sequence
3. intersectCounters, used for and sequence
4. minimum, finds the minimum
5. process_query, Reads each line from stdin
6. extract_string, Normalizes word extracted
7. sorter, Prints set in descending order
8. valid_query, Checks "or" and "and" in words
9. handle_query, Checks for 'or' and 'and' 
```


### Pseudo code 
The querier will run as follow:

```c
1. execute from a command line with usage syntax
2. validate it received exactly two command-line arguments and that:
    pageDirectory is the pathname for a directory produced by the Crawler, and
    indexFilename is the pathname of a file that can be read;
3.load the index from indexFilename into an internal data structure.
4.read search queries from stdin, one per line, until EOF.
    a.clean and parse each query according to the syntax described below.
    b.if the query syntax is somehow invalid, print an error message, do not perform the query, and prompt for the next query.
    c.print the 'clean' query for user to see.
    d.use the index to identify the set of documents that satisfy the query, as described below.
    e.if the query is empty (no words), print nothing.
    f.if no documents satisfy the query, print No documents match.
    g.otherwise, rank the resulting set of documents according to its score, as described below, and print the set of documents in decreasing rank order; for each, list the score, document ID and URL. (Obtain the URL by reading the first line of the relevant document file from the pageDirectory.)
5.output nothing to stdout other than what is indicated above
6.exit zero when EOF is reached on stdin; exit with an error message to stderr and non-zero exit status on encountering an unrecoverable error, including
    a.out of memory,
    b.invalid command-line arguments,
    c.unable to read a file named pageDirectory/.crawler,
    d.unable to read a file named pageDirectory/1
    e.unable to read a file named indexFilename

```

### Major data structures

1.Counters
2.Hashtable
3.Index


### Testing Plan

Program was tested on:
1. Invalid number of arguments
2. Invalid page directory
3. Invalid indexFile
4. "and" testing
5. "or" testing
6. "or" and "and" testing
7. fuzzquery
8. Valgrind

