#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char * str) {
  //WRITE ME!
  char * p1 = str;
  char * p2 = strchr(str, '\0');
  if (p2 - p1 == 0) {
    return;
  }
  // do {
  //  char temp = *p1;
  //  *p1 = *p2;
  //  *p2 = temp;
  //  p1++;
  //  p2--;
  //} while (p1 < p2);

  size_t len = p2 - p1;
  p2--;
  for (size_t i = 0; i < len / 2; i++) {
    char temp = *p1;
    *p1 = *p2;
    *p2 = temp;
    p1++;
    p2--;
  }
}

int main(void) {
  char str0[] = "";
  char str1[] = "123";
  char str2[] = "abcd";
  char str3[] = "Captain's log, Stardate 42523.7";
  char str4[] = "Hello, my name is Inigo Montoya.";
  char str5[] = "You can be my wingman anyday!";
  char str6[] = "Executor Selendis! Unleash the full power of your forces! There may be no tomorrow!";
  char * array[] = {str0, str1, str2, str3, str4, str5, str6};
  for (int i = 0; i < 7; i++) {
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}
