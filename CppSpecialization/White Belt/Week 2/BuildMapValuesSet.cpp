#include <map>
#include <set>
#include <string>
#include <iostream>
using namespace std;

set<string> BuildMapValuesSet(const map<int, string>& m) {
    set<string> res;
    for (auto item : m)
        res.insert(item.second);
    return res;
}

int main(){
    set<string> values = BuildMapValuesSet({
        {1, "odd"},
        {2, "even"},
        {3, "odd"},
        {4, "even"},
        {5, "odd"}
    });

    for (const string& value : values) {
        cout << value << endl;
    }   
    return 0;
}