#include "test_runner.h"
#include <iostream>
#include <list>
#include <vector>
using namespace std;

const int MAX_NUMBER = 100'000;

int main(){
    using Position = list<int>::iterator;

    int n = 0, number = 0, next_number = 0;
    cin >> n;

    list<int> row;
    vector<Position> numbers(MAX_NUMBER + 1, row.end());

    for (size_t i = 0; i < n; i++) {
        cin >> number >> next_number;
        numbers[number] = row.insert(numbers[next_number], number);
    }
    for (int x : row)
        cout << x << '\n';

    return 0;
}