#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <stddef.h>

void rotateM(char matrix[][10]);
int readMatrix(FILE * f, char matrix[][10]);

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

  char matrix[10][10] = {'\0'};
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

int readMatrix(FILE * f, char matrix[][10]) {
  char line[11] = {'\0'};
  unsigned row = 0;
  while (fgets(line, 11, f) != NULL && row < 10) {
    printf("Line %u: %s\n",row,line);
    if (strchr(line, '\n') != NULL) {
      fprintf(stderr,"Line has less than 10 characters!\n");
      return EXIT_FAILURE;
    }

    for (size_t i = 0; i < 10; i++) {
      matrix[row][i] = line[i];
    }
    row++;
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
