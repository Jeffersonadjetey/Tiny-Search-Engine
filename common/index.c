/*
 *
 *
 * index.c
 *
 * Jefferson Adjetey
 *
 *
 */




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include "../libcs50/hashtable.h"
#include "../libcs50/file.h"
#include "../libcs50/webpage.h"
#include "../libcs50/mem.h"
#include "../common/pagedir.h"
#include "../libcs50/counters.h"
#include "../libcs50/set.h"
#include "index.h"

//static for helper functions
typedef hashtable_t index_t;



/***************Index New************/

index_t* index_new(const int num_slots){
  return (index_t*)hashtable_new(num_slots);
}

/*************index insert**********/

bool index_insert(index_t* index, const char* word, counters_t* ctr){
  return hashtable_insert(index, word, ctr);
}



/*********index find**********/
void* index_find(index_t* index, const char* key){
  return (counters_t*)hashtable_find(index, key);
}









//delete helper function
void word_delete(void* item){
  counters_t* deleted = item;
  if(deleted != NULL){
    counters_delete(deleted);
  }

}
/***********index_delete************/
void index_delete(index_t* index){
  hashtable_delete(index, word_delete);
}










//Helper function
static void counters_save_helper(void* arg, const int key, int count){
  FILE* fp = arg;
  fprintf(fp, "%d %d", key, count);
}


/*******word_save*************/
static void word_save(void *fp, const char *key, void *item){
  FILE *fp1 = fp;
  //convert void* to counters*
  counters_t* item_new = item;
  //print the key to the file
  fprintf(fp1, "%s ", key);
  counters_iterate(item_new, fp1, (counters_save_helper));
  fprintf(fp, "\n");
}


/****************index_save**************/
bool index_save(char *filename, index_t *index){

	FILE *fp;
	fp = fopen(filename, "w");
  printf("%s", filename);
  if (fp != NULL) {
	  hashtable_iterate(index, fp,(word_save));
    return true;
  }
  else{
    return false;
  }

	fclose(fp);
}









/***********word_print************/
static void word_print(FILE* fp,const char *key,void *item){
 // FILE* fp = arg;
  
  counters_t* counter = item;
  fprintf(fp, "%s ", key);

  if (counter == NULL){
    fprintf(fp, "NULL");
  }
  else{
    counters_print(counter, fp);
  }
}

/************index print***************/
void index_print(index_t* index, FILE* fp){
  if(index != NULL){
    hashtable_print(index, fp, word_print);
    }
}








/*********LOAD***********/
index_t* index_load(const char *filename){
  
  //if the filename is null, print stderr and return NULL
  if (filename == NULL) {
    fprintf(stderr, "error loading\n");
    return NULL;
  }
  
  FILE* fp = fopen(filename, "r");
  //if fp == NULL, print error "cannot open the file and return NULL
  if (fp == NULL) {
    fprintf(stderr, "cannot open the file");
    return NULL;
  }
  //count how many words in the file (file_numLines())
  int num_words = file_numLines(fp);
  //BUild an index using index_new and the num_slots(how many words we have)
  index_t* idx = index_new(num_words/2 + 1);

  
 // int ID = 0;
 // int count = 0;
  char* word;


  //loop through all the words in fp
  while((word = file_readWord(fp)) != NULL) {
    //for each word, make a counter using counters_new

    counters_t* counter =  counters_new();
    int ID;
    int count;
    //Now read in the docID and counter 
    while ((fscanf(fp, "%d %d ", &ID, &count)) == 2) {
      //if it equals two, it still getting the ID and count pair
         if (!counters_set(counter, ID, count)){
           fprintf(stderr, "Error");
         } 
         
    }
     hashtable_insert(idx, word, counter);
   free(word);
  
  
  }
  
  fclose(fp);
  return idx;
}
