#include <stdio.h>

double my_min(double *grades, int size) 
{
  double min = grades[0];
  for (int i = 1; i < size; i += 1) 
  {
    if (grades[i] < min)
      min = grades[i];
  }
  return min;
}
