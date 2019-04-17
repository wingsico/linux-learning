#include <stdio.h>

double my_avg(double *grades, int size)
{
  return my_sum(grades, size) / size;
}
