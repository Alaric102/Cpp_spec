#include "search_server.h"
#include "test_runner.h"
#include "profile.h"
#include "parse.h"

#include <string>
#include <vector>

string GenerateString(const size_t size, const size_t step = 20){
    std::string res = "";
    size_t counter = (size_t)('a');
    for (size_t i = 0; i < size; ++i){
        if (i % step == 0){
            res.push_back(' ');
            ++counter %= 255;
        } else {
            res.push_back(to_string(counter).operator[](0));
        }
    }
    return res;
}

vector<string> GenerateDocument(const size_t docsNumber){
    vector<string> res;
    for (size_t i = 0; i < docsNumber; i++){
        res.push_back(GenerateString(1'000'000, 20));
    }
    return res;
}

// void TestSplitAssert(){
//     vector<string> splits1;
//     deque<string_view> splits2;
//     string str = GenerateString(50'000'000, 20);
//     {
//         LOG_DURATION("SplitIntoWords");
//         splits1 = SplitIntoWords(str);
//     }
//     {
//         LOG_DURATION("SplitIntoWordsView");
//         splits2 = SplitIntoWordsView(str);
//     }
//     ASSERT_EQUAL(splits1.size(), splits2.size());
//     for (size_t i = 0; i < splits1.size(); ++i)
//         ASSERT_EQUAL(splits1[i], splits2[i]);
// }

// void TestUpdate(){
//     auto docs = GenerateDocument(50);
//     istringstream docs_input(Join('\n', docs));
//     LOG_DURATION("UpdateDocumentBase");
//     SearchServer srv(docs_input);
// }

// int main(){
//     TestRunner tr;
//     RUN_TEST(tr, TestSplitAssert);
//     RUN_TEST(tr, TestUpdate);
// }