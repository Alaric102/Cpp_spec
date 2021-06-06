#include <iostream>
#include <vector>
using namespace std;

vector<int> Reversed(const vector<int>& v){
    vector<int> res;
    for(int i = 0; i < v.size(); ++i){
        res.push_back(v[v.size() - 1 - i]);
    }
    return res;
}

int main(){
    vector<int> numbers = {1, 5, 3, 4, 2};
    auto res = Reversed(numbers);
    for (auto i : res)
        cout << i << ' ';
    return 0;
}