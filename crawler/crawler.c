/* 
 * crawler.c - CS50 'crawler' module
 *
 *
 * Jefferson Adjetey, February, 2022 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include "../libcs50/bag.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/webpage.h"
#include "../libcs50/mem.h"
#include "../common/pagedir.h"


// functions
int main(const int argc, char* argv[]);
static void parseArgs(const int argc, char* argv[],
                      char** seedURL, char** pageDirectory, int* maxDepth);
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);



static const int maxmaxDepth = 10; //const used in Parse Args



/***************MAIN**************/
int main(const int argc, char* argv[]){
  char* seedURL = NULL;
  int maxDepth = 0;
  char* pageDirectory = NULL;

  parseArgs(argc, argv, &seedURL, &pageDirectory, &maxDepth); //calls parseArgs

  crawl(seedURL, pageDirectory, maxDepth);   //calls crawl
  return 0;


}



 

/****************** PARSE ARGS *************/
static void parseArgs(const int argc, char* argv[],
                      char** seedURL, char** pageDirectory, int* maxDepth){

  if (argc != 4) {
    fprintf(stderr, "Usage:crawler, seedURL, pageDirectory, maxDepth\n");
    exit (1);
  }
  *seedURL = argv[1];
  //if its a valid URL
  char* NormalizeURL = normalizeURL(*seedURL);
  if (NormalizeURL == NULL){
    fprintf(stderr, "Usage: Error, not normal URL\n");
    exit (2);
  }

  if (isInternalURL(NormalizeURL)){
    free(NormalizeURL);
  }
  else{
    fprintf(stderr, "Usage: Not an internal URL\n");
    exit (3);
  }
  *pageDirectory = argv[2];
  if (!(pagedir_init(*pageDirectory))) {
      fprintf(stderr, "Usage: Invalid Page Directory\n");
      exit (4);
  }
  char* maxDepth_string = argv[3];
  char extra;
  if (sscanf(maxDepth_string, "%d%c", maxDepth, &extra) != 1) {
    fprintf(stderr, "Usage: Wrong maxDepth value\n");
    exit (5);
  }
  if (*maxDepth < 0 || *maxDepth > maxmaxDepth) {
    fprintf(stderr, "Usage: maxDepth out of range\n");
    exit (6);
  }
}




  

/******************* CRAWL FUNCTION ******************************/
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth){
  //Initialize hashtable and add the seedURL
  hashtable_t *page_visited = hashtable_new(10);
  int depth = 0;
  int id = 1;
  

  char* s_URL = mem_malloc_assert(strlen(seedURL)+1, "Failed aloocation...\n");
  strcpy(s_URL, seedURL);
  hashtable_insert(page_visited,seedURL, "");
 

  bag_t *toVisit = bag_new(); //bag used for pages to visit

  bag_insert(toVisit, webpage_new(s_URL,0,NULL));
  

  //while there are more webpage to crawl
  webpage_t *webpage;


  //while page is not empty
  while((webpage = bag_extract(toVisit)) != NULL){
    //pull a webpage from the bag
    webpage_fetch(webpage);

    if ((webpage_getHTML(webpage)) != NULL){
      pagedir_save(webpage, pageDirectory, ++id);
    }


    //if webpage is not at maxDepth
    if (webpage_getDepth(webpage) < maxDepth){
      pageScan(webpage, toVisit, page_visited);

    }
    //delete that webpage
  webpage_delete(webpage);


  }
//delete bag and hashtable

  bag_delete(toVisit, NULL);
  hashtable_delete(page_visited, NULL);


}








/******************* PAGE SCAN ***********************************/
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen){

  char* URL;
  int pos = 0;

  while ((URL = webpage_getNextURL(page, &pos)) != NULL) {
    //if that URL is Internal
    char* normalize_URL = normalizeURL(URL);
    if (normalize_URL == NULL){
      printf("URL is not Internal");
      continue;

    }
    if(isInternalURL(normalize_URL)){

      //if that succeeded
      if (hashtable_insert(pagesSeen, normalize_URL, "")){
        //create a webpage for it
        webpage_t *new = webpage_new(normalize_URL, webpage_getDepth(page)+1, NULL);
        //insert the webpage into the bag
        bag_insert(pagesToCrawl, new);
      }
      //free the URL
      else{
      mem_free(normalize_URL);
     }
    }
    else{
       mem_free(normalize_URL);
      }
          }
    }
    


