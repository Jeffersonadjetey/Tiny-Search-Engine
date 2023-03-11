### Jefferson Mubarak Adjetey


The querier module implemets the following methods:

```c
int main(int argc, char* argv[]);

static void process_query(index_t* index, char* pageDirectory);

int extract_string(char* line, char** words);

void sorter(counters_t* set, char* pageDirectory);

bool valid_query(char **words, int numWords);

void handle_query(char** words, index_t* index, char* pageDirectory);
```



# Function Prototypes
Short descriptions of function's interfaces are provided above each function.



### Data structures
index
counters
hashtable

### Pseudocode

execute from a command line with usage syntax

./querier pageDirectory indexFilename
where pageDirectory is the pathname of a directory produced by the Crawler, and
where indexFilename is the pathname of a file produced by the Indexer.
validate it received exactly two command-line arguments and that

pageDirectory is the pathname for a directory produced by the Crawler, and
indexFilename is the pathname of a file that can be read;
load the index from indexFilename into an internal data structure.

read search queries from stdin, one per line, until EOF.

clean and parse each query according to the syntax described below.
if the query syntax is somehow invalid, print an error message, do not perform the query, and prompt for the next query.
print the 'clean' query for user to see.
use the index to identify the set of documents that satisfy the query, as described below.
if the query is empty (no words), print nothing.
if no documents satisfy the query, print No documents match.
otherwise, rank the resulting set of documents according to its score, as described below, and print the set of documents in decreasing rank order; for each, list the score, document ID and URL. (Obtain the URL by reading the first line of the relevant document file from the pageDirectory.)
output nothing to stdout other than what is indicated above

exit zero when EOF is reached on stdin; exit with an error message to stderr and non-zero exit status on encountering an unrecoverable error, including

out of memory,
invalid command-line arguments,
unable to read a file named pageDirectory/.crawler,
unable to read a file named pageDirectory/1
unable to read a file named indexFilename



### Error Handling and Recovery
The command-line arguments of ./querier are checked immediately. It checks to make sure that `pageDirectory` is a directory produced by the Crawler and that `indexFilename` is  pathname of a file that can be read.
 
Out of memory errors when creating structs handled by `mem_assert`.
 
That said, certain errors are caught and handled internally: for example, if the querier is unable to read the first file in `pageDirectory`, it will exit nonzero and print an error to stderr.

