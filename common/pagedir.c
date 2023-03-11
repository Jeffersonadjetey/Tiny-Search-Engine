#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pagedir.h"
#include "../libcs50/webpage.h"
#include "../libcs50/mem.h"
#include "../libcs50/file.h"



/************* pagedir_init*************/
bool pagedir_init(const char* pageDirectory){
  //construct the pathname for the .crawler file in that directory.  
  char *path = mem_malloc(strlen(pageDirectory)+10);
  strcpy(path, pageDirectory);
  strcat(path, "/.crawler");

 
  FILE *fp;
  fp = fopen(path, "w"); //file open for writing
  mem_free(path);

  if (fp == NULL){
    return false;
  }
  fclose(fp);
  return true;

}

/*********** pagedir_save **************/
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID){
  //construct the pathname for the page file in pageDirectory
  char *filename = mem_malloc(strlen(pageDirectory)+strlen("/")+(10)+1);
  sprintf(filename, "%s/%d", pageDirectory, docID);


  //open that file for writing
  FILE* fp = fopen(filename, "w");
  if (fp != NULL){
    //print the URL
    fprintf(fp, "%s\n", webpage_getURL(page));
    //print the depth
    fprintf(fp, "%d\n", webpage_getDepth(page));
    //print the contents of the webpage
    fprintf(fp, "%s\n", webpage_getHTML(page));
    //close the file
    fclose(fp);
  }
  mem_free(filename);

}

/**********pagedir_validate************/
bool pagedir_validate(const char* pageDirectory){

  if (pageDirectory == NULL){
    return false;
  }

  char* filename = mem_malloc_assert(strlen(pageDirectory) + 1 + strlen(".crawler") + 1, "crawler file name error");

  sprintf(filename, "%s/%s", pageDirectory, ".crawler");
  printf("%s", filename);
  FILE* fp = fopen(filename, "r");
  if (fp == NULL){
    mem_free(filename);
    return false;
  }
  else{
    fclose(fp);
    mem_free(filename);
    return true;

  }
}


/**********pagedir_load*************/
webpage_t* pagedir_load(const char* pageDirectory, const int ID){
  char* filename = mem_malloc_assert(strlen(pageDirectory) + 12, "Not succesful");  //memory for pageDirectory
  sprintf(filename, "%s/%d", pageDirectory, ID);
  FILE* fp = fopen(filename, "r");   //open the file to read
  if (fp == NULL){
  mem_free(filename);
    return NULL;
  }
  else{
    char* URL = file_readLine(fp);
    char* newURL = mem_malloc(strlen(URL)+1);
    strcpy(newURL, URL);
    mem_free(URL);
    char* depth_string = file_readLine(fp);

    char* HTML = file_readFile(fp);
    char* newHTML = mem_malloc(strlen(HTML)+1);
    strcpy(newHTML, HTML);
    mem_free(HTML);

    fclose(fp);
    mem_free(filename);

    int depth = atoi(depth_string);
    free(depth_string);

    printf("%s", URL);
    //create a webpage
    webpage_t* page = mem_assert(webpage_new(newURL, depth, newHTML),"Not successful");
    return page;
  }

}



