// #include "test_runner.h"

#include <vector>
#include <string>

using namespace std;

template <typename Token>
using Sentence = vector<Token>;

template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
  std::vector<Sentence<Token>> res;
  Sentence<Token> temp_sentence;
  for (auto it = tokens.begin(); it != tokens.end();) {
    if (it->IsEndSentencePunctuation()) {
      while (it->IsEndSentencePunctuation() && it != tokens.end()) {
        temp_sentence.push_back(std::move(*it));
        ++it;
      }
      res.push_back(std::move(temp_sentence));
    } else {
      temp_sentence.push_back(std::move(*it));
      ++it;
    }
  }
  if (!temp_sentence.empty()) {
    res.push_back(std::move(temp_sentence));
  }
  return res;
}

struct TestToken {
  string data;
  bool is_end_sentence_punctuation = false;

  bool IsEndSentencePunctuation() const {
    return is_end_sentence_punctuation;
  }
  bool operator==(const TestToken& other) const {
    return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
  }
};

ostream& operator<<(ostream& stream, const TestToken& token) {
  return stream << token.data;
}

// void TestSplitting() {
//   ASSERT_EQUAL(
//     SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
//     vector<Sentence<TestToken>>({
//         {{"Split"}, {"into"}, {"sentences"}, {"!"}}
//     })
//   );

//   ASSERT_EQUAL(
//     SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
//     vector<Sentence<TestToken>>({
//         {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
//     })
//   );

//   ASSERT_EQUAL(
//     SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
//     vector<Sentence<TestToken>>({
//         {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
//         {{"Without"}, {"copies"}, {".", true}},
//     })
//   );
// }

// int main() {
//   TestRunner tr;
//   RUN_TEST(tr, TestSplitting);
//   return 0;
// }