#include <stdio.h>
#include <stdlib.h>


unsigned power (unsigned x, unsigned y);
void run_check (unsigned x, unsigned y, unsigned ans);

int main(void) {
  
  run_check(0, 0, 1); // special case: 0^0
  run_check(1, 0, 1); // special case: 1^0
  run_check(0, 1, 0); // special case: 0^1
  run_check('A', 1, 65); // pass a character
  run_check(2, 2, 4); // off-by-one?
  run_check(-1,2,1); // neg input?
  run_check(3, 3, 27);
  run_check(2, 3, 8); // different x, y
  run_check(10000,2,100000000); // large number


  return EXIT_SUCCESS;
}

void run_check(unsigned x, unsigned y, unsigned ans) {
  if (power(x,y) != ans) {
    printf("Failed test: x= %u, y= %u\n", x, y);
    exit(EXIT_FAILURE);
  }
}
