/*
 *querier.c
 *
 *
 *
 * Jefferson Adjetey, Winter 2022
 */






#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <unistd.h>

#include "../libcs50/file.h"
#include "../libcs50/bag.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/webpage.h"
#include "../libcs50/mem.h"
#include "../common/pagedir.h"
#include "../common/index.h"
#include "../common/word.h"


//Function Prototypes
void counterIntersectHelper(void *arg, const int key, const int count);
void countersUnionHelper(void *arg, const int key, const int count);
static bool isOperator(char* word);
int parseArgs(int argc,char* argv[], char** pageDirectory, char** indexFIlename);
void handle_query(char** words, index_t* index, char* pageDirectory);
static void process_query(index_t* index, char* pageDirectory);
int extract_string(char* line, char** words);
static bool valid_query(char **words, int numWords);
void countersUnionHelper(void *arg, const int key, int count);
void countersUnion(counters_t *wordA, counters_t *wordB);
void sorter(counters_t* set, char* pagedir);
int minimum(const int wordA, const int wordB);

// struct for sorting
struct row {
    int maxkey;       
    int maxcount;       
    int* visited;       
    int size;           
};

struct two_counters {
	counters_t *and_sequence;       
	counters_t *or_sequence;      
};


//Local types
//passed into counters_iterate
typedef struct cPack {
  counters_t* wordA;
  counters_t* wordB;
} cPack_t;


//passed into sort
/*
typedef struct doc {
  int ID;
  int count;
} doc_t;

*/

/******************* HELPER FUNCTIONS ************************/
/*
 *counterUnionHelper = Used in countersUnion
 *
 *
 */
void countersUnionHelper(void *arg, const int key, int count){
  counters_t* wordA = arg;
  counters_set(wordA,key, count + counters_get(wordA, key));
}


/*
 *
 *CountersUnion
 *
 */
void countersUnion(counters_t *wordA, counters_t *wordB){
  counters_t *output = counters_new();
  counters_iterate(wordA, output, countersUnionHelper);
  }


/*
 *CountersIntersectHelper = Used in intersectCounters
 *
 */
void counterIntersectHelper(void *arg, const int key, int count) {

   counters_t *wordA = ((cPack_t*)arg)->wordA;
  counters_t *wordB = ((cPack_t*)arg)->wordB;
  //choose the min if both sets have word
  counters_set(wordA, key, minimum(count, counters_get(wordB, key)));
}


/*
 *
 *IntersectCounters
 *
 */
void intersectCounters(counters_t *wordA, counters_t *wordB) {
  if (wordA == NULL || wordB == NULL){
    wordA = NULL;
  }
  counters_t *output = counters_new();
  cPack_t pair = {output, wordB};
  counters_iterate(wordA, &pair, counterIntersectHelper);
 // return output;
}


void selection_sort_helper(void *arg, const int key, const int count)
{
    struct row* node = arg;
    
    for (int i = 0; i < node->size; i++) { 
        if (key == node->visited[i]) { //make sure key is not visited
            return;
        }
    }
    // Update the running max key and count if the current count is higher
    if (node->maxcount < count) {
        node->maxcount = count;
        node->maxkey = key;
    }
}

void counting(void *arg, const int key, const int count)
{
    int* key_count = arg;
    if (count > 0) {
        *key_count += 1;
    }
}

int minimum(const int wordA, const int wordB){
  if (wordA < wordB){
    return wordA;
  }
  else{
    return wordB;
  }
}







/*********** main *********
 * Runs the program
 */

int main(int argc, char* argv[]){

   if (argc != 3) {
        fprintf(stderr, "Invalid number of arguments\n");
        exit(1);
    }
   
    
 
    char* pageDirectory_copy = malloc(strlen(argv[1])+10);
    strcpy(pageDirectory_copy, argv[1]);

    if (pageDirectory_copy[strlen(pageDirectory_copy)-1] != '/') {
        strcat(pageDirectory_copy, "/");
    }


    // Validate inputs
    if (!pagedir_validate(argv[1])) {
        exit(3);
    }

    // Load index and process query
    index_t* index = index_load(argv[2]);
    process_query(index, pageDirectory_copy);

    // Clean up
    free(pageDirectory_copy);
    index_delete(index);
    return 0;
 

}


/******* process_query ***********
 *Reads each line from stdin
 *
 */

static void process_query(index_t* index, char* pageDirectory){


  char* line = NULL;
  int length = 0;

  printf("\nInput your Query: \n");
  while ((line = file_readLine(stdin)) != NULL) {
    //malloc words array according to the strlen
    char** words = calloc(sizeof(char*), strlen(line) + 1);
    length = extract_string(line, words);
    printf("Input your Query: \n");
    for (int i = 0; i < length; i++) {
      //print each word in the query
      printf(" %s", words[i]); 
    }
    printf("\n");

    //validate the query
    if (!valid_query(words, length)){
      free(words);
      free(line);
      continue;
      }

     
    //call handle query
  handle_query(words, index, pageDirectory);
   printf("Input your query:\n");
   free(words);
   free(line);


  }
}
/************  extract string *******
 *Normalizes word extracted
 *
 */

int extract_string(char* line, char** words)
{
    char delimiter[] = " ";                         // space delimeter
    char* word = strtok(line, delimiter);          
    if (word == NULL) {
      printf("%s", "string length is 0\n");
        return 0;
    }

    int i = 1;                                  

    // Normalize word
    NormalizeWord(word);
    words[0] = word;
    while ((word = strtok(NULL, delimiter)) != NULL) {
        NormalizeWord(word);
        *(words + i) = word;
        i++;
    }
   
    return i;
}
/**********sorter*******
 *Prints set in descending order
 *
 */

void sorter(counters_t* set, char* pageDirectory)
{
    // Find the number of docIDs that match stdin
    int length = 0;
    counters_iterate(set, &length, counting);
    if (length == 0) {
        printf("No documents match.\n");
        return;
    }

    int* visited = calloc(sizeof(int), length);
    printf("\nMatches %d documents (ranked):\n", length);
    struct row node = {0, 0, visited, length};

    // For each word in the counters set
    for (int position = 0; position < length; position++) {
        counters_iterate(set, &node, selection_sort_helper);
        visited[position] = node.maxkey;
        if (node.maxcount > 0) {
            // Find the corresponding URL within the crawler directory
            char* num = malloc(sizeof(node.maxkey)+1);
            sprintf(num, "%d", node.maxkey);
            char* urlcopy = malloc(strlen(pageDirectory)+1+sizeof(node.maxkey));
            strcpy(urlcopy, pageDirectory);
            strcat(urlcopy, num);
            //printf("This is urlcopy %s", urlcopy);
            FILE* fp = fopen(urlcopy, "r");
            if (fp == NULL) {
                fprintf(stderr, "sort file could not be opened");
                return;
            }
            char* url = file_readLine(fp);
            // Print the score, docID, and URL for the matched result
            printf("score   %d doc   %d: %s\n", node.maxcount, node.maxkey, url);

            // Clean up
            fclose(fp);
            free(num);
            free(urlcopy);
            free(url);
        }
        node.maxkey = 0;
        node.maxcount = 0;
    }
    free(visited);
}





//helper function
static bool isOperator(char* word){  //add proto
  if (word == NULL){
  return false;
  }

  if (strcmp(word, "and") == 0){
      return true;
   }
  if (strcmp(word, "or")==0){
    return true;
  }
  return false;
}

/******** valid_query*******
 *Checks "or" and "and" in words
 */
bool valid_query(char **words, int numWords) {

  if (numWords <= 0){
    printf( "Error. No words\n");
    return false;
  }
  //check first word
  if (isOperator( words[0])){
        printf( "Error: cannot be first\n");
        return false;
  }


 if (isOperator(words[numWords-1])){
        printf("Error: '%s' cannot be last\n", words[numWords-1]);
        return false;
  }


  for (int i = 1; i < numWords - 1; i++) {
    if (isOperator(words[i-1]) && (isOperator(words[i]))){
        printf( "Cannot be consecutive\n");
        return false;
    }

    return true;

  }
  return true;
}



/********** handle_query********
 *Runs the query
 *Checks for 'or' and 'and'
 */
void handle_query(char** words, index_t* index, char* pageDirectory) 
{

  //countersets
    counters_t* and_sequence = NULL;        
    counters_t* or_sequence = counters_new();
    

    int i = 0;
    char* word = NULL;

    bool shortcircuit = false;//indicates whether there is an empty result in and_sequence 

    //  loops through each word 
    while ((word = words[i]) != NULL) {
        //  if "or"
        if (words[i+1] != NULL && (strcmp(words[i+1], "or") == 0)) { 
            // Merge 
            if (and_sequence == NULL) {
                and_sequence = index_find(index, word);
            }
            else {
                counters_t* curr = index_find(index, word);
                struct two_counters args = {curr, and_sequence}; 
                counters_iterate(curr, &args, counterIntersectHelper);
            }
            // Combine the and_sequence AND clause into the or_sequence counters set
            counters_iterate(and_sequence, or_sequence, countersUnionHelper);
            i+=2;

            if (shortcircuit) {
                counters_delete(and_sequence);
            }
            and_sequence = NULL;
        }
       
        else {
            counters_t* curr = index_find(index, word);
            if (strcmp(word, "and") == 0) {
                i++;
            }
            else if (and_sequence == NULL) {
                // If the word does not exist in the index,
                and_sequence = index_find(index, word);
                if (and_sequence == NULL) {
                    shortcircuit = true;
                    and_sequence = counters_new();
                }
                i++;
            }
            else { 
                // Minimize counts across AND sequence
                struct two_counters args = {curr, and_sequence}; 
                counters_iterate(curr, &args, counterIntersectHelper);
                i++;
            }
        }
    // Merge  and_sequence and or_sequence
    }
    if (and_sequence != NULL ) {
        counters_iterate(and_sequence, or_sequence, countersUnionHelper);
        if (shortcircuit) {
            counters_delete(and_sequence);
        }
    }
    // Print the sorted final set and clean up
    sorter(or_sequence, pageDirectory);
    counters_delete(or_sequence);
}

