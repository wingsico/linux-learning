#include <stdio.h>

double my_max(double *grades, int size)
{
  double max = grades[0];
  for (int i = 1; i < size; i += 1)
  {
    if (grades[i] > max)
      max = grades[i];
  }
  return max;
}
