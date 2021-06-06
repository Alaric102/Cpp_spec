#include <iostream>
#include <string>
using namespace std;

bool IsPalindrom(string str){
    for (int i = 0; i < str.size()/2; ++i){
        if (str[i] != str[str.size() - 1 - i])
            return false;
    }
    return true;
}

int main(){
    string line;
    cin >> line;
    cout << IsPalindrom(line);
    return 0;
}