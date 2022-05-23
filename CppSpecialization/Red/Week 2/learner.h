#include <algorithm>
#include <string>
#include <vector>
#include <vector>
#include <string>
#include <set>

using namespace std;

class Learner {
 private:
  set<string> dict;

 public:
  int Learn(const vector<string>& words) {
    int newWords = 0;
    for (const auto& word : words) {
    //   if (find(dict.begin(), dict.end(), word) == dict.end()) {
    //     ++newWords;
    //     dict.push_back(word);
    //   }
        auto insert = dict.insert(word);
        if (insert.second){
            newWords++;
        }
    }
    return newWords;
  }

  vector<string> KnownWords() {
    // sort(dict.begin(), dict.end());
    // dict.erase(unique(dict.begin(), dict.end()), dict.end());
    return {dict.begin(), dict.end()};
  }
};