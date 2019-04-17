#include <stdio.h>
#include "my.h"

#define size 6

int main()
{
  double grades[size] = {98, 90, 85.5, 76.5, 93, 77};

  printf("max: %lf\n", my_max(grades, size));
  printf("min: %lf\n", my_min(grades, size));
  printf("sum: %lf\n", my_sum(grades, size));
  printf("avg: %lf\n", my_avg(grades, size));
  
  return 0;
}
