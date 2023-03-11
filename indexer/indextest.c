#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../common/index.h"
#include "../common/pagedir.h"

int main(int argc, char *argv[]){
  if (argc != 3) {
    fprintf(stderr, "Usage: ./indextest oldIndexFilename newIndexFilename\n");   
    exit (1);
  }  
  

  //load the index from the oldIndexFilename into an inverted-index data structure
  index_t* inv_index = index_load(argv[1]);
  if (inv_index == NULL){
    fprintf(stderr, "Error, index is NULL");
    exit (2);
  }
 
    
  index_save(argv[2], inv_index);
  index_delete(inv_index);
 // fclose(fp);
  return 0;

}
