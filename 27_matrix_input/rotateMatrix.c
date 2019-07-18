#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <stddef.h>

void rotateM(char matrix[10][10]);
int readMatrix(FILE * f, char matrix[10][10]);

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Wrong number of input files!\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Could not open file");
    return EXIT_FAILURE;
  }

  char matrix[10][10] = {{'\0'}};
  int read = readMatrix(f, matrix);
  if (read == EXIT_FAILURE) {
    fprintf(stderr,"Failed reading matrix from file!\n");
    return EXIT_FAILURE;
  }
  rotateM(matrix);

  for (size_t i = 0; i < 10; i++) {
    for (size_t j = 0; j < 10; j++) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }


  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return 0;
}

int readMatrix(FILE * f, char matrix[10][10]) {
  char line[12] = {'\0'};
  //printf("Length of line: %lu\n", strlen(line));
  unsigned row = 0;
  while (fgets(line, 12, f) != NULL && row < 11) {
    if(10 == row) {
      fprintf(stderr, "More than 10 lines!\n");
      return EXIT_FAILURE;
    }
    if(line[10] != '\n') {
      if (strchr(line, '\n') == NULL) {
	if(fgetc(f) == EOF) {
	  if(strlen(line) < 10) {
	    fprintf(stderr,"Last line has less than 10 characters!\n");
	    return EXIT_FAILURE;
	  }
	  else {
	    fprintf(stderr,"Newline character missing on last line!\n");
	  }
	}
	else {

	  fprintf(stderr,"Line %d has more than 10 characters!\n", row);
	  return EXIT_FAILURE;
	}
      }
      else {
	fprintf(stderr,"Line %d has less than 10 characters!\n", row);
	return EXIT_FAILURE;
      }
    }

    for (size_t i = 0; i < 10; i++) {
      if( line[i] == '\0' || line[i] == EOF) {
	fprintf(stderr,"Line %d has less than 10 characters!\n", row);
	return EXIT_FAILURE;
      }
      matrix[row][i] = line[i];
    }
    row++;
    line[10] = '\0';
    line[11] = '\0';
  }

  if (row < 10) {
    fprintf(stderr,"File has less than 10 rows!\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

void rotateM(char matrix[10][10]) {
  char n[10][10];
  for (size_t i = 0; i < 10; i++) {
    for (size_t j = 0; j < 10; j++) {
      n[i][j] = matrix[i][j];
    }
  }

  for (size_t i = 0; i < 10; i++) {
    for (size_t j = 0; j < 10; j++) {
      matrix[j][10 - 1 - i] = n[i][j];
    }
  }
}
