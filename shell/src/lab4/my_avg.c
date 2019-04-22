#include <stdio.h>

double my_avg(double *grades, int size)
{
  double sum = 0;
  for (int i = 0; i < size; i++)
  {
    sum += grades[i];
  }
  return sum / size;
}