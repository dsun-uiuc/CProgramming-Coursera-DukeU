#include <stddef.h>

void rotate(char matrix[10][10]) {
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
