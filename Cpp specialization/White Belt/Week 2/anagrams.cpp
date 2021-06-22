#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

int main(){
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i){
        string first, second;
        cin >> first >> second;

        map<char, int> first_m, second_m;
        for (auto ch : first)
            ++first_m[ch];
        for (auto ch : second)
            ++second_m[ch];
        if (first_m == second_m)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}