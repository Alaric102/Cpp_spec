// #include "test_runner.h"
// #include "profile.h"

#include <map>
#include <set>
#include <string>
#include <sstream>
#include <iterator>
#include <future>
#include <thread>
#include <functional>
using namespace std;

struct Stats {
  map<string, int> word_frequences;

  void operator += (const Stats& other) {
    for (const auto& [word, freq] : other.word_frequences) {
      word_frequences[word] += freq;
    }
  };
};

template <typename Iterator>
class Page {
private:
    Iterator first_, last_;
    size_t size_;
public:
    Page(Iterator begin, Iterator end):
        first_(begin), 
        last_(end), 
        size_(distance(begin, end))
    {};

    Iterator begin() const {
        return first_;
    }

    Iterator end() const {
        return last_;
    }

    size_t size() const {
        return size_;
    }
};

template <typename Iterator>
class Paginator {
private:
    vector<Page<Iterator>> data_;
public:
    Paginator(Iterator begin, Iterator end, size_t pageSize){
        for (size_t left = distance(begin, end); left > 0; ){
            size_t currentPageSize = min(pageSize, left);
            Iterator currentPageEnd = next(begin, currentPageSize);
            data_.push_back({begin, currentPageEnd});

            begin = currentPageEnd;
            left -= currentPageSize;
        }
    };
    
    auto begin() const {
        return data_.begin();
    }

    auto end() const {
        return data_.end();
    }

    size_t size() const {
        return data_.size();
    }
};

template <typename Container>
auto Paginate(Container& c, size_t page_size) {
    return Paginator(begin(c), end(c), page_size);
}

vector<string> GetWords(istream& input){
    vector<string> words;
    string word;
    while (input >> word){
        words.push_back(word);
    }
    return words;
}

Stats ExploreKeyWordsThread(const set<string>& key_words, Page<vector<string>::iterator>&& page){
    Stats res;
    for (const auto& i : page){
        if (key_words.find(i) != key_words.end()){
            res.word_frequences[i] += 1;
        }
    }
    return res;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    Stats res;
    vector<string> words = GetWords(input);
    size_t threadNumber = 4;
    size_t pageSize = words.size() / threadNumber;
    vector<future<Stats>> results;
    for (auto& page : Paginate(words, pageSize)){
        results.push_back( async(ExploreKeyWordsThread, cref(key_words), page) );
    }
    for (auto& f : results){
        res += f.get();
    }
    return res;
}

// void TestBasic() {
//   const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

//   stringstream ss;
//   ss << "this new yangle service really rocks\n";
//   ss << "It sucks when yangle isn't available\n";
//   ss << "10 reasons why yangle is the best IT company\n";
//   ss << "yangle rocks others suck\n";
//   ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

//   const auto stats = ExploreKeyWords(key_words, ss);
//   const map<string, int> expected = {
//     {"yangle", 6},
//     {"rocks", 2},
//     {"sucks", 1}
//   };
//   ASSERT_EQUAL(stats.word_frequences, expected);
// }

// int main() {
//   TestRunner tr;
//   RUN_TEST(tr, TestBasic);
// }