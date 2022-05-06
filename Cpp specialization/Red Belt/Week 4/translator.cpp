#include "test_runner.h"
#include <string>
#include <string_view>

#include <vector>
#include <deque>
#include <list>
#include <map>

using namespace std;

class Translator {
public:
    void Add(string_view source, string_view target){
        
    };
    string_view TranslateForward(string_view source) const {
        return "";
    };
    string_view TranslateBackward(string_view target) const {
        return "";
    };

private:

};

void TestSimple() {
    Translator translator;
    string src = "str1"; string trg = "trg1";
    {
        translator.Add(string("okno"), string("window"));
    }
    translator.Add(src, trg);
    src = "str2"; trg = "trg2";
    {
        translator.Add(string("stol"), string("table"));
    }
    translator.Add(src, trg);

    ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
    ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSimple);
  return 0;
}