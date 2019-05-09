#include<iostream>
#define NUM 10

int main() {
  int *mp;
  int max, min;

  mp = (int *)malloc(NUM * sizeof(int));  
  // mp = (int *)calloc(NUM, sizeof(int));
  max = min = *mp;
  
  std::cout << "input " << NUM << " numbers:" << std::endl;
  for(int i = 0; i < NUM; i++) {
    std::cin >> *(mp+i);  
    if (*(mp+i) > max) {
      max = *(mp+i);
    }

    if (*(mp+i) < min) {
      min = *(mp+i);
    }
  }

  std::cout << "max: " << max << ", min: " << min << std::endl;
  free(mp);
  return 0;
}
