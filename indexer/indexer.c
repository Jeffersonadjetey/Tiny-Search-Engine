/*
*
*indexer.c
*
*Jefferson Adjetey
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include "../libcs50/webpage.h"
#include "../common/pagedir.h"
#include "../common/word.h"
#include "../common/index.h"
#include "../libcs50/mem.h"
#include "../libcs50/file.h"
#include "../libcs50/counters.h"
//Functions
static void parseArgs(const int argc, char* argv[], char** first, char** second);
static index_t* indexBuild(char* pageDirectory);
void indexPage(index_t* index, webpage_t* page, int ID);
int main(int argc, char *argv[]);



/***********parseArgs******************/
static void parseArgs(int argc, char *argv[], char** first, char** second){
	// Insufficient Number of Arguments
	if (argc != 3)
	{
		fprintf(stderr, "Insufficient number of arguments \n");
		fprintf(stderr, "Usage: ./indexer [pageDir] [indexFname] \n");
  	exit (1);
  }

	// Is page directory crawlable
  *first = argv[1];
	if (!pagedir_validate(*first))
	{
		fprintf(stderr, "Not a valid crawler\n");
		fprintf(stderr, "Usage: ./indexer [pageDir] [indexFname] \n");
		exit (2);
	}

		
	// Index Filename
  *second = argv[2];
	
}


/*************INDEXBUILD**********************/
static index_t* indexBuild(char* pageDirectory){
 int ID = 1;
 index_t* new_index = mem_assert(index_new(900),"Index failure");//  creates a new 'index' object
 webpage_t* webpage = NULL;
 while((webpage = pagedir_load(pageDirectory, ID)) != NULL){  //load a webpage from the document file 
  indexPage(new_index, webpage, ID); //passes the webpage and docID to indexPage
  ID ++;
  webpage_delete(webpage);
 }
 return new_index;
}


/*************indexpage*****************/
void indexPage(index_t* index, webpage_t* page, int ID){
  int position = 0;
  char* word;
  while((word = webpage_getNextWord(page, &position)) != NULL){  //   steps through each word of the webpage,
    if(strlen(word)>2){    //skip trivial words(less than length 3)
     NormalizeWord(word);      
  
      counters_t* wordcount = index_find(index, word); 
      // index_insert(index, word, ID);  //add the word
      if (wordcount == NULL){
        wordcount = counters_new();
        index_insert(index, word, wordcount);
      }
      counters_add(wordcount, ID);    
    }
   free(word);
  }
}

/********MAIN*************/

int main(int argc, char *argv[])
{
 

	// checking arguments
   char* first = NULL;
  char* second = NULL;
 
  parseArgs(argc, argv, &first, &second);
		// creating new index 
		index_t *index = indexBuild(first);
		
		// building the index
  		index_save(second, index);
		
		// delete index and related data
		index_delete(index);
}

