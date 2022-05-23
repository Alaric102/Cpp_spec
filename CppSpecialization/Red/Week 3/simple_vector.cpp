#include "simple_vector.h"
#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void TestConstruction() {
  SimpleVector<int> empty;
  ASSERT_EQUAL(empty.Size(), 0u);
  ASSERT_EQUAL(empty.Capacity(), 0u);
  ASSERT(empty.begin() == empty.end());


  SimpleVector<int32_t> ten_Int32(10);
  ASSERT_EQUAL(ten_Int32.Size(), 10u);
  ASSERT(ten_Int32.Size() <= ten_Int32.Capacity());
  for (int i = 0; i < ten_Int32.Size(); ++i) {
    ten_Int32[i] = i;
    ASSERT_EQUAL(ten_Int32[i], i);
  }

  SimpleVector<string> five_strings(5);
  ASSERT_EQUAL(five_strings.Size(), 5u);
  ASSERT(five_strings.Size() <= five_strings.Capacity());
  for (auto& item : five_strings) {
    ASSERT(item.empty());
  }
  five_strings[2] = "Hello";
  ASSERT_EQUAL(five_strings[2], "Hello");
}

void TestPushBack() {
  SimpleVector<int> v;
  for (int i = 10; i >= 1; --i) {
    v.PushBack(i);
    ASSERT(v.Size() <= v.Capacity());
  }
  sort(begin(v), end(v));

  const vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  ASSERT_EQUAL(v.Size(), expected.size());
  ASSERT(equal(begin(v), end(v), begin(expected)));
}

void TestDefaultContructors(){
  SimpleVector<int> emptyInt;
  ASSERT_EQUAL(emptyInt.Size(), 0u);
  ASSERT_EQUAL(emptyInt.Capacity(), 0u);
  ASSERT(emptyInt.begin() == emptyInt.end());

  SimpleVector<int8_t> Int8(10);
  ASSERT_EQUAL(Int8.Size(), 10u);
  ASSERT(Int8.Size() <= Int8.Capacity());

  SimpleVector<int8_t> vInt16(12);
  ASSERT_EQUAL(vInt16.Size(), 12u);
  ASSERT(vInt16.Size() <= vInt16.Capacity());

  SimpleVector<int8_t> vInt32(15);
  ASSERT_EQUAL(vInt32.Size(), 15u);
  ASSERT(vInt32.Size() <= vInt32.Capacity());

  SimpleVector<int> vInt64(0);
  ASSERT_EQUAL(vInt64.Size(), 0u);
  ASSERT_EQUAL(vInt64.Capacity(), 0u);
  ASSERT(vInt64.begin() == vInt64.end());
  
  SimpleVector<string> emptyString;
  ASSERT_EQUAL(emptyString.Size(), 0u);
  ASSERT_EQUAL(emptyString.Capacity(), 0u);
  ASSERT(emptyString.begin() == emptyString.end());
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestDefaultContructors);
  RUN_TEST(tr, TestConstruction);
  RUN_TEST(tr, TestPushBack);
  return 0;
}