#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * ct = malloc(sizeof(*ct));
  ct->array  = NULL;
  ct->size   = 0;
  ct->unknown = 0;
  return ct;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  unsigned isNew = 1;
  if (NULL == name) {
    c->unknown++;
  }
  else {
    for (size_t i = 0; i < c-> size; i++) {
      if(! strcmp(name, c->array[i]->name)) {
	c->array[i]->count++;
	isNew = 0;
	break;
      }
    }
    if (isNew) {
      char * newName = malloc((strlen(name) + 1)*sizeof(*newName));
      strcpy(newName, name);

      one_count_t * newCount = malloc(sizeof(*newCount));
      newCount->name = newName;
      newCount->count = 1;
      
      c->array = realloc(c->array,(c->size + 1)*sizeof(*(c->array)));
      c->array[c->size] = newCount;
      c->size++;
    }    
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  if (NULL == outFile) {
    perror("No file to write to.");
    exit(EXIT_FAILURE);
  }

  for (size_t i = 0; i < c->size; i++) {
    fprintf(outFile,"%s: %zu\n", c->array[i]->name, c->array[i]->count);
  }
  fprintf(outFile,"<unknown> : %zu\n", c->unknown);
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (size_t i = 0; i < c->size; i++) {
    free(c->array[i]->name);
    free(c->array[i]);
  }
  free(c->array);
  free(c);
}
