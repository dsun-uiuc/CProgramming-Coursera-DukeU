#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename, "r");
  if (NULL == f) {
    fprintf(stderr, "Cannot open file \'%s\' to read value",filename);
    exit(EXIT_FAILURE);
  }
  // read each line of file, then loop up the Value, then addCount
  counts_t * ct = createCounts();
  char * line = NULL;
  size_t sz = 0;
  char * ptNl = NULL;
  while(getline(&line, &sz, f) >= 0) {
    ptNl = strchr(line, '\n');
    *ptNl = '\0'; //replace newline with null
    char * value = lookupValue(kvPairs, line);
    addCount(ct, value);
  }
  free(line);
  if(fclose(f)) {
    fprintf(stderr,"Cannot close counted file \'%s\'", filename);
  }
  return ct;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]); 
 //count from 2 to argc (call the number you count i)
  for (size_t i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c =  countFile(argv[i], kv); 
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);    

    //open the file named by outName (call that f)
    FILE * f = fopen(outName,"w");
    if (NULL == f) {
      perror("Cannot open file to write result");
      return EXIT_FAILURE;
    }
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if(fclose(f)) {
      perror("Cannot close file just written to");
      return EXIT_FAILURE;
    }
    //free the memory for outName and c
    freeCounts(c);
    free(outName);
  }

 //free the memory for kv
  freeKVs(kv);
  
  return EXIT_SUCCESS;
}
