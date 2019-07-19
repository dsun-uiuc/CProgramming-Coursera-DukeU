#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"



kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (NULL == f) {
    fprintf(stderr, "Cannot open file: %s\n", fname);
    exit(EXIT_FAILURE);
  }

  char * line = NULL;
  size_t sz = 0;
  size_t i = 0;
  
  char * ptEq = NULL;
  char * ptNl = NULL;
  
  kvarray_t * kva = malloc(sizeof(*kva));
  kva-> kvparray = NULL;
  
  while(getline(&line, &sz, f) >=0) {

    ptEq = strchr(line, '=');
    ptNl = strchr(line, '\n'); 

    if (NULL == ptEq) {
      perror("Cannot find \'=\' in line!\n");
      exit(EXIT_FAILURE);
    }
    
    char *ptKey = malloc((ptEq - line + 1) * sizeof(*ptKey));
    char *ptValue = malloc((ptNl - (ptEq + 1) + 1) * sizeof(*ptValue));
    
    strncpy(ptKey, line, ptEq - line); // copy the frist (ptEqu - line) characters to pt2
    ptKey[ptEq - line] = '\0';
    strncpy(ptValue, ptEq + 1, ptNl - (ptEq + 1));
    ptValue[ptNl - (ptEq + 1)] = '\0';

    kvpair_t * kvp = malloc(sizeof(*kvp));
    kvp->key = ptKey;
    kvp->value = ptValue;

    kva->kvparray = realloc(kva->kvparray, (i + 1) * sizeof(*(kva->kvparray)));
    kva->length = i + 1;
    (kva->kvparray)[i] = kvp;
    i++;

    char * ptLi = line;
    line = NULL;
    free(ptLi);
    ptKey = NULL;
    ptValue = NULL;
    ptEq = NULL;
    ptNl = NULL;
  }
  free(line);
  fclose(f);
  
  return kva;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->length; i++) {

    free(pairs->kvparray[i]->key);
    free(pairs->kvparray[i]->value);
    free(pairs->kvparray[i]);
  }
  free(pairs->kvparray);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->length; i++) {
    printf("key = %s value = %s\n", pairs->kvparray[i]->key, pairs->kvparray[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i = 0; i < pairs->length; i++) {
    if (!strcmp(key, pairs->kvparray[i]->key)) {
      return pairs->kvparray[i]->value;
    }
  }
  return NULL;
}
