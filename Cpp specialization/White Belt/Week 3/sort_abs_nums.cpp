#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

bool abs_sort(long int a, long int b){
    return abs(a) < abs (b);
}

int main(){
    unsigned int N;
    cin >> N;

    vector<long int> values(N);
    for (auto& i : values)
        cin >> i;
    sort(begin(values), end(values), abs_sort);
    for (const auto i : values)
        cout << i << " ";
    return 0;
}