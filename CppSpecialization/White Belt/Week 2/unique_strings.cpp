#include <iostream>
#include <string>
#include <set>
using namespace std;

int main(){
    set<string> unique;
    unsigned int N;
    cin >> N;
    string input;
    for (unsigned int i = 0; i < N; ++i){
        cin >> input;
        unique.insert(input);
    }
    cout << unique.size();
    return 0;
}