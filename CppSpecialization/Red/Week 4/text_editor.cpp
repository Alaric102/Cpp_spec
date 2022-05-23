#include <string>
#include <string_view>
#include <list>

// #include "test_runner.h"
using namespace std;

#define MAX_TEXT_LENGTH 1'000'000

class Editor {
public:
  Editor(){
    _pos = _textList.begin();
  };

  void Left(){
    if (_pos == _textList.begin())
      return;
    _pos = std::prev(_pos);
  };

  void Right(){
    if (_pos == _textList.end())
      return;
    _pos = std::next(_pos);
  };

  void Insert(char token){
    _pos = std::next(_textList.insert(_pos, token));
  };

  void Cut(size_t tokens = 1) {
    Copy(tokens);

    for (int i = 0; (i < tokens) && (_pos != _textList.end()); ++i){
      _pos = std::next(_pos);
      _textList.erase(std::prev(_pos));
    }
  };

  void Copy(size_t tokens = 1) {
    _buffer.clear();
    _buffer.reserve(tokens);
    auto _pose_to_copy = _pos;
    for (int i = 0; i < tokens; ++i){
      _buffer.push_back(*_pose_to_copy);
      _pose_to_copy = std::next(_pose_to_copy);
    }
  };

  void Paste() {
    for (const auto& ch : _buffer){
      Insert(ch);
    }
  };

  string GetText() const {
    return string(_textList.begin(), _textList.end());
  };
private:
  list<char> _textList;
  list<char>::iterator _pos;

  string _buffer;
};

// void TypeText(Editor& editor, const string& text) {
//   for(char c : text) {
//     editor.Insert(c);
//   }
// }

// void TestEditing() {
//   {
//     Editor editor;

//     const size_t text_len = 12;
//     const size_t first_part_len = 7;
//     TypeText(editor, "hello, world");
//     for(size_t i = 0; i < text_len; ++i) {
//       editor.Left();
//     }
//     editor.Cut(first_part_len);
//     for(size_t i = 0; i < text_len - first_part_len; ++i) {
//       editor.Right();
//     }
//     TypeText(editor, ", ");
//     editor.Paste();
//     editor.Left();
//     editor.Left();
//     editor.Cut(3);
    
//     ASSERT_EQUAL(editor.GetText(), "world, hello");
//   }
//   {
//     Editor editor;
    
//     TypeText(editor, "misprnit");
//     editor.Left();
//     editor.Left();
//     editor.Left();
//     editor.Cut(1);
//     editor.Right();
//     editor.Paste();
    
//     ASSERT_EQUAL(editor.GetText(), "misprint");
//   }
// }

// void TestReverse() {
//   Editor editor;

//   const string text = "esreveR";
//   for(char c : text) {
//     editor.Insert(c);
//     editor.Left();
//   }
  
//   ASSERT_EQUAL(editor.GetText(), "Reverse");
// }

// void TestNoText() {
//   Editor editor;
//   ASSERT_EQUAL(editor.GetText(), "");
  
//   editor.Left();
//   editor.Left();
//   editor.Right();
//   editor.Right();
//   editor.Copy(0);
//   editor.Cut(0);
//   editor.Paste();
  
//   ASSERT_EQUAL(editor.GetText(), "");
// }

// void TestEmptyBuffer() {
//   Editor editor;

//   editor.Paste();
//   TypeText(editor, "example");
//   editor.Left();
//   editor.Left();
//   editor.Paste();
//   editor.Right();
//   editor.Paste();
//   editor.Copy(0);
//   editor.Paste();
//   editor.Left();
//   editor.Cut(0);
//   editor.Paste();
  
//   ASSERT_EQUAL(editor.GetText(), "example");
// }

// int main() {
//   TestRunner tr;
//   RUN_TEST(tr, TestEditing);
//   RUN_TEST(tr, TestReverse);
//   RUN_TEST(tr, TestNoText);
//   RUN_TEST(tr, TestEmptyBuffer);
//   return 0;
// }