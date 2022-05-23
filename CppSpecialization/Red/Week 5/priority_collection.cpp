// #include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <utility>
#include <vector>
#include <set>
#include <map>

using namespace std;

template <typename T>
class PriorityCollection {
public:
  using Id = size_t;
  
  Id Add(T object){
    _idToNode.push_back({move(object), 0});
    _priotToId[0].insert(_idToNode.size() - 1);
    return _idToNode.size() - 1;
  };

  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin){
    for (auto i = range_begin; i != range_end; ++i, ids_begin++){
      *ids_begin = Add(move(*i));
    }
  };

  bool IsValid(Id id) const {
    if ((id < 0) || (id >= _idToNode.size())){
      return false;
    } else if (_idToNode[id].priority == -1) {
      return false;
    }
    return true;
  };

  const T& Get(Id id) const{
    return _idToNode[id]._data;
  };

  void Promote(Id id){
    int priority = _idToNode[id].priority;
    auto nodeSet_it = _priotToId.find(priority);
    if (nodeSet_it != _priotToId.end()) {
      nodeSet_it->second.erase(nodeSet_it->second.find(id));
    }
    _priotToId[priority + 1].insert(id);
    _idToNode[id].priority++;
    if (nodeSet_it->second.empty()) {
      _priotToId.erase(nodeSet_it);
    }
  };

  pair<const T&, int> GetMax() const{
    return {_idToNode[*(_priotToId.rbegin()->second.rbegin())]._data, _priotToId.rbegin()->first};
  };

  pair<T, int> PopMax(){
    auto iter_to_last = _priotToId.rbegin()->second.rbegin();
    auto result = std::make_pair(std::move(_idToNode[*(iter_to_last)]._data),
                                 _priotToId.rbegin()->first);

    _idToNode[*(iter_to_last)].priority = -1;
    _priotToId.rbegin()->second.erase(prev(_priotToId.rbegin()->second.end()));
    if (prev(_priotToId.end())->second.empty()) {
      _priotToId.erase(prev(_priotToId.end()));
    }
    return result;
  };

private:
  struct Node {
    T _data;
    int priority;
  };

  static bool CompareNode(const Node& a, const Node& b){
    return a.priority < b.priority;
  }
  vector<Node> _idToNode;
  map<int, set<Id>> _priotToId;
};


class StringNonCopyable : public string {
public:
  using string::string;
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};
/*
void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  vector<StringNonCopyable> sources;
  sources.emplace(sources.end(), "one");
  sources.emplace(sources.end(), "two");
  sources.emplace(sources.end(), "tree");
  vector<size_t> data(3);
  // strings.Add(sources.begin(), sources.end(), begin(data));

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  return 0;
}
*/