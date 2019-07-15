#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

int main(void) {
  size_t n;
  
  int arr1[] = {}; // empty array
  if(maxSeq(arr1,0) != 0) return EXIT_FAILURE;

  int arr2[] = {0}; // 1-element array
  if(maxSeq(arr2, 1) !=1) return EXIT_FAILURE;

  int arr3[] = {0, 1, 2, 3, 3}; // repeated elements, off-by-1 at beginning
  if(maxSeq(arr3, 5) != 4) return EXIT_FAILURE;
  
  int arr4[] = {1, 1, 2, 3}; // off-by-1 at end
  if(maxSeq(arr4, 4) != 3) return EXIT_FAILURE;

  int arr5[] = {-3, -1, 0}; // negative numbers
  if(maxSeq(arr5, 3) != 3) return EXIT_FAILURE;

  int arr6[] = {1, 2, 3, -3, -2, -1}; // two subsets
  if(maxSeq(arr6, 6) != 3) return EXIT_FAILURE;

  int arr7[] = {-10000, 0, 10000}; // large numbers
  if(maxSeq(arr7, 3) != 3) return EXIT_FAILURE;

  int arr8[] = {0, 4, 5, 9, -1, 10, 12, 19, 20, 20, 20};
  if(maxSeq(arr8, 11) != 5) return EXIT_FAILURE;

  
  return EXIT_SUCCESS;
}
