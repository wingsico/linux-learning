#include <iostream>
#include <ctime>
#include <cstdlib>

int rdInt(int, int);

int main() {
  using namespace std;
  
  srand((unsigned)time(NULL));
  
  int randInt = rdInt(1, 1000);
  int tryTime = 1;
  int tryValue = 0;
  const int MAX_TRY_TIME = 10;
  cout << "There is an integer(1-1000), please guess its value.(in " << MAX_TRY_TIME << " times)" << endl;

  while (true) {
    if (tryTime > MAX_TRY_TIME) {
      cout << "Sorry. All chances be used. You losed." << endl;
      break;
    }
    cout << "try" << tryTime++ << ": ";
    cin >> tryValue;
    if (tryValue > randInt) {
      cout << "Larger, try again." << endl;
    } else if (tryValue < randInt) {
      cout << "Smaller, try again." << endl;
    } else {
      cout << "Great! You got it." << endl;
      break; 
    }
  }
  return 0;
}
int rdInt(int min, int max) {
  return rand()%(max-min+1) + min;
}
