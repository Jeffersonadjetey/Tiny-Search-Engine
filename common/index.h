#include "../libcs50/hashtable.h"
#include "../libcs50/counters.h"


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
