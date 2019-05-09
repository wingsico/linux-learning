#include<iostream>
#include <fstream>
#include<vector>
#include<string>
#include<sys/time.h>
#include<algorithm>
void outputVector(std::vector<std::string>);
void bubbleSort(std::vector<std::string> &);
void qSort(std::vector<std::string> &, int, int);

int main() {
  using namespace std;
  char buffer[256];
  vector<string> strs;
  ifstream in("File1.txt");

  if (!in.is_open()) {
    cout << "Error opening file" << endl; 
    exit (1);
  }

  while(!in.eof()) {
    in.getline(buffer,100);
    strs.push_back(buffer);
  }

  struct timeval start;
  struct timeval end;
  unsigned long diff;

  gettimeofday(&start,NULL);
  //qSort(strs, 0, strs.size()- 1);
  bubbleSort(strs);
  gettimeofday(&end,NULL);

  diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;

  outputVector(strs);
  
  cout << "runtime: " << diff << "ms" << endl;
  return 0;
}

void outputVector(std::vector<std::string> strs) { 
  using namespace std;
  vector<string>::iterator it;
  for(it=strs.begin();it!=strs.end();it++){
    cout<<*it<<endl;
  }
}

void bubbleSort(std::vector<std::string> &strs) {
  using namespace std;
  string temp;
  for(int i = 0; i < strs.size() - 1; i++) {
    for(int j = 0; j < strs.size() - i - 1; j++) {
      if (strs[j] > strs[j+1]) {
        swap(strs[j+1], strs[j]);
      }
    }
  }
}

void qSort(std::vector<std::string> &strs, int left, int right) {
  if (right <= left) return;
  int i = left;
  int j = right + 1;
  std::string key = strs[left];

  while(true) {
    while(strs[++i] < key) {
      if (i == right) break;
    }

    while(strs[--j] > key) {
      if (j == left) break;
    }
    if (i>=j) break;
    swap(strs[i], strs[j]);
  }

  swap(strs[left], strs[j]);

  qSort(strs, left, j - 1);
  qSort(strs, j+1, right);
}

