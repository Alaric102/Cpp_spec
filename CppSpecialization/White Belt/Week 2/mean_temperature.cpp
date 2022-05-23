#include <vector>
#include <iostream>
using namespace std;

int main(){
    int N, mean = 0;
    cin >> N;
    vector<int> temps(N);
    for (auto& i : temps){
        cin >> i;
        mean += i;
    }
    mean /= N;

    vector<int> large_temps;
    for (int i = 0; i < N; ++i)
        if (temps[i] > mean)
            large_temps.push_back(i);
    
    cout << large_temps.size() << endl;
    for (auto i : large_temps)
        cout << i << ' ';
    return 0;
}