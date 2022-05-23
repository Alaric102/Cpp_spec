#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <string_view>
#include <deque>

using namespace std;

// vector<string> SplitIntoWords(const string& line);
deque<std::string_view> SplitIntoWords(const string_view stringView);

class InvertedIndex {
public:
  void Add(string&& document);
  
  list<pair<size_t, size_t>> Lookup(const string_view word) const;

  const string& GetDocument(size_t id) const {
    return docs[id];
  }

private:
  map<string, list<size_t>> index;
  
  map<string_view, list<pair<size_t, size_t>>> frequency_index;
  deque<string> docs;
};

class SearchServer {
public:
  SearchServer() = default;

  explicit SearchServer(istream& document_input);

  void UpdateDocumentBase(istream& document_input);
  
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
  InvertedIndex index;
};
