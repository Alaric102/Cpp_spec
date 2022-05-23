#include <string>
#include <vector>
#include <iostream>
using namespace std;

#define GET_NAME(num) var##num

#define GET_NAME_HELPER(num) GET_NAME(num)

#define UNIQ_ID GET_NAME_HELPER(__LINE__)

int main() {
  int UNIQ_ID = 0;
  string UNIQ_ID = "hello";
  vector<string> UNIQ_ID = {"hello", "world"};
  vector<int> UNIQ_ID = {1, 2, 3, 4};
}