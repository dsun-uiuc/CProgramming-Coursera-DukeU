#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define LINE_SIZE 4096

int freqCount(FILE * f, size_t * count);
unsigned largestIndex(size_t * count);

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Wrong number of input files: %d\n", argc);
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }


  size_t count[26] = {0}; // count[] contains counts of each letter

  int countSuccess = freqCount(f,count);
  if (countSuccess == EXIT_FAILURE) {
    return EXIT_FAILURE;
  }

  unsigned id = largestIndex(count); // id should be in [0, 26)

  int k = (id - 4 + 26) % 26;

  printf("%d\n", k);



  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

// read each line from file and count frequency of each letter

int freqCount(FILE * f, size_t * count) {

  // using fgets
  /*
  char line[LINE_SIZE];
  while (fgets(line, LINE_SIZE, f) != NULL) {
    if (strchr(line, '\n') == NULL) {
      perror("Line is too long!\n");
      return EXIT_FAILURE;
    }
    for (size_t i = 0; *(line + i) != '\0'; i++) {
      int c = *(line + i);
      if (isalpha(c)) {
	c = tolower(c);
	c -= 'a';
	count[c]++;
      }
    }
  }
  */
  // using fgetc
  int c = fgetc(f);
  size_t nletter = 0;
  if (c == EOF) {
    perror("Empty file!\n");
    return EXIT_FAILURE;
  }
     
  do {
    if (isalpha(c)) {
      c = tolower(c);
      c -= 'a';
      count[c]++;
      nletter++;
    }
  } while ((c = fgetc(f)) != EOF);

  if (nletter == 0) {
    perror("No letters in file!\n");
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}

unsigned largestIndex(size_t * count) {

  size_t temp = count[0];
  unsigned id = 0;

  for (size_t i = 1; i < 26; i++) {
    if(temp < count[i]) {
      temp = count[i];
      id = i;
    }
  }
  return id;
}
