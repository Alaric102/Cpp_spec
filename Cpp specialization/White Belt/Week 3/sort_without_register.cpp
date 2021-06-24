#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

bool abs_sort(long int a, long int b){
    return abs(a) < abs (b);
}

int main(){
    unsigned int N;
    cin >> N;

    vector<string> values(N);
    for (auto& i : values)
        cin >> i;

    sort(begin(values), end(values), [](const string& sl, const string& sr){
        for (const auto& chl : sl)
            for (const auto& chr : sr)
                if (tolower(chl) < tolower(chr))
                    return true;
        return false;
    });
    
    for (const auto i : values)
        cout << i << " ";
    return 0;
}