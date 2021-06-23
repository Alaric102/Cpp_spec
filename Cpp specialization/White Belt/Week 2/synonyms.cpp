#include <iostream>
#include <string>
#include <set>
#include <map>
using namespace std;

int main(){
    map<string, set<string>> synonyms;
    unsigned int Q;
    cin >> Q;

    string cmd;
    for (unsigned int i = 0; i < Q; ++i){
        cin >> cmd;
        string word1, word2;
        if (cmd == "ADD"){
            cin >> word1 >> word2;
            synonyms[word1].insert(word2);
            synonyms[word2].insert(word1);
        } else if (cmd == "COUNT"){
            cin >> word1;
            cout << synonyms[word1].size() << endl;
        } else if (cmd == "CHECK"){
            cin >> word1 >> word2;
            if (synonyms[word1].count(word2) || synonyms[word2].count(word1))
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        }
    }

    return 0;
}