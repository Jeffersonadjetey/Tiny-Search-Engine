#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
/*
makes the word lowercase
*/
void NormalizeWord(char* word){
for (int i = 0; i < strlen(word); i ++){
		word[i] = tolower(word[i]);
	}
}
