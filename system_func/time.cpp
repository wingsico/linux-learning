#include <ctime>
#include <iostream>
#include <cstdlib>

void showGMT(time_t, int time_area);

int main() {
  time_t t;
  time(&t);
  // 格林尼治
 std::cout << "[格林尼治] "; 
  showGMT(t, 0);
  // 北京
  std::cout << "[Beijing] ";
  showGMT(t, 8);
  return 0;
}

void showGMT(time_t t, int time_area) {
  using namespace std;
  struct tm *p;
  t = t + time_area * 3600;
  cout << "GMT: " << asctime(gmtime(&t));
}

