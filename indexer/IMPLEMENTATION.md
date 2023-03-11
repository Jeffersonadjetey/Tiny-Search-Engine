###TSE INDEXER IMPLEMENTATION SPEC
The indexer relies on the data structures below.

###indexer
The indexer module uses the following methods

```c
static void parseArgs(const int argc, char* argv[], char** first, char** second);
static index_t* indexBuild(char* pageDirectory);
void indexPage(index_t* index, webpage_t* page, int ID);
int main(int argc, char *argv[]);
```

###common (index)
In the index.c, these methods are used.

```c
typedef hashtable_t index_t;



/********* index_new **************/
index_t* index_new(const int num_slots);




/*********** index_insert **********/
bool index_insert(index_t* index, const char* word, counters_t* ctr);





/*************index_find*************/
void* index_find(index_t* index, const char* key);





/**********index_delete**********/
void index_delete(index_t* index);




/*********index_save**********/
bool index_save(char *filename, index_t *index);



/*********index_print*********/
void index_print(index_t* index, FILE* fp);



/*********index_load********/
index_t* index_load(const char *filename);

```

###Usage
./indexer pageDirectory indexFilename

###Pseudo code for indexer
The indexer will run as follows:

```c
parse the command line, validate parameters, initialize other modules


call indexBuild, with pageDirectory
```

where indexBuild:
```c
  creates a new 'index' object
  loops over document ID numbers, counting from 1
    loads a webpage from the document file 'pageDirectory/id'
    if successful, 
      passes the webpage and docID to indexPage
```
where indexPage:

```c
  steps through each word of the webpage,
   skips trivial words (less than length 3),
   normalizes the word (converts to lower case),
   looks up the word in the index,
     adding the word to the index if needed
   increments the count of occurrences of this word in this docID
```
###Index tester
Loads an index file produced by the indexer and saves it to another file.

###Testing
I could not really test the program correctly. There was no problem when it came to compilation (except for one test) but I couldn't see anything in the indexFilename.
