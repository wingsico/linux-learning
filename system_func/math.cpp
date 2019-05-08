#include<iostream>
#include<cmath>
#define _USE_MATH_DEFINES

long double getPI();
int showMenuAndGetChoice();
double showTipAndGetVal(bool);
double ang2rad(double);
int main() {
  int choice;
  double value;
  while(true) {
    choice = showMenuAndGetChoice();

    switch(choice) {
      case 0:
        std::cout << "Thanks, bye." << std::endl;
        return 0;
      case 1:
        value = showTipAndGetVal(true);
        std::cout << "sin(rad: " << value << ") = " << sin(value) << std::endl;
        break;
      case 2:
        value = showTipAndGetVal(false);
        std::cout << "sin(angle: " << value << ") = " << sin(ang2rad(value)) << std::endl;
        break;
      case 3:
        value = showTipAndGetVal(true);
        std::cout << "cos(rad: " << value << ") = " << cos(value) << std::endl;
        break;
      case 4: 
        value = showTipAndGetVal(false);
        std::cout << "cos(angle: " << value << ") = " << cos(ang2rad(value)) << std::endl;
        break;
      default:
        std::cout << "Error choice, try again." << std::endl;
        break;
    }
  }
}

/*
 * func
 *
 */
long double getPI() {
  return M_PI;
}

double ang2rad(double angle) {
  return angle*getPI()/180;
}

int showMenuAndGetChoice(){
  using namespace std;
  int choice;
  cout << "********** Calculator ***********" << endl;
  cout << "* 1. sin(rad)                   *" << endl; 
  cout << "* 2. sin(angle)                 *" << endl;
  cout << "* 3. cos(rad)                   *" << endl;
  cout << "* 4. cos(angle)                 *" << endl;
  cout << "* 0. exit                       *" << endl;
  cout << "*********************************" << endl;
  cout << "input your choice: ";
  cin >> choice;
  return choice;
}

double showTipAndGetVal(bool isRad) {
  using namespace std;
  double value;
  cout << "input " << (isRad ? "rad" : "angle") << " value: "; 
  cin >> value;
  return value;
}

