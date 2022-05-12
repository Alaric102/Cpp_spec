// #include "test_runner.h"
#include <string>
#include <string_view>

#include <deque>
#include <map>

using namespace std;

class Translator {
public:
    Translator(){
        _data.clear();
        _forward.clear();
        _backward.clear();
    };

    void Add(string_view source, string_view target){
        const string_view source_view = GetClonedView(source);
        const string_view target_view = GetClonedView(target);
        _forward[source_view] = target_view;
        _backward[target_view] = source_view;
    };
    string_view TranslateForward(string_view source) const {
        return Translate(_forward, source);
    };
    string_view TranslateBackward(string_view target) const {
        return Translate(_backward, target);
    };

private:
    string_view GetClonedView(string_view s){
        for (const auto* map_ptr : {&_forward, &_backward}){
            const auto it = map_ptr->find(s);
            if (it != map_ptr->end()){
                return it->first;
            }
        }
        return _data.emplace_back(s);
    }

    map<string_view, string_view> _forward;
    map<string_view, string_view> _backward;
    deque<string> _data;

    static string_view Translate(const map<string_view, string_view>& dict, string_view s) {
        if (const auto it = dict.find(s); it != dict.end()){
            return it->second;
        } else {
            return {};
        }
    }
};

// void TestSimple() {
//     Translator translator;
//     string src = "str1"; string trg = "trg1";
//     {
//         translator.Add(string("okno"), string("window"));
//     }
//     translator.Add(src, trg);
//     src = "str2"; trg = "trg2";
//     {
//         translator.Add(string("stol"), string("table"));
//     }
//     translator.Add(src, trg);

//     ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
//     ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
//     ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
// }

// int main() {
//   TestRunner tr;
//   RUN_TEST(tr, TestSimple);
//   return 0;
// }