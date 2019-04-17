#include <stdio.h>

double my_sum(doubel *grades, int size) 
{
  double sum = 0;
  for (int i = 0; i < size; i++)
  {
    sum += grades[i];
  }
  return sum;
}
