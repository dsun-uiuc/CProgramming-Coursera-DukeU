#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  int realAge = startAge;
  double balance = initial;
  int months_working = working.months;
  int months_retired = retired.months;
  for (int i = 0; i < months_working; i++) {
    printf("Age %3d month %2d you have $%.2lf\n", realAge / 12, realAge % 12, balance);
    balance *= (1+ working.rate_of_return);
    balance += working.contribution;
    realAge++;
  }

  for (int i = 0; i < months_retired; i++) {
    printf("Age %3d month %2d you have $%.2lf\n", realAge / 12, realAge % 12, balance);
    balance *= (1 + retired.rate_of_return);
    balance += retired.contribution;
    realAge++;
  }
}

int main (void) {

  retire_info working = {489, 1000, 0.045/12};
  retire_info retired = {384, -4000, 0.01/12};
  int startAge = 327;
  double initial = 21345;
  retirement(startAge, initial, working, retired);
  
  return EXIT_SUCCESS;
}
