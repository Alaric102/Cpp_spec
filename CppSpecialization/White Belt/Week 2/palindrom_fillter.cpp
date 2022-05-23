#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool IsPalindrom(string str){
    for (int i = 0; i < str.size()/2; ++i){
        if (str[i] != str[str.size() - 1 - i])
            return false;
    }
    return true;
}

vector<string> PalindromFilter(vector<string> words, int min_size){
    vector<string> res;
    for (auto w : words){
        if (IsPalindrom(w) && w.size() >= min_size)
            res.push_back(w);
    }
    return res;
}

int main(){
    vector<string> words = {"weew", "bro", "code"};
    auto res = PalindromFilter(words, 4);
    for (auto w : res)
        cout << w << ' ';
    return 0;
}