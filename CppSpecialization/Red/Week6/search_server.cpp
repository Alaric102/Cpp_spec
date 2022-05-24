#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>

deque<std::string_view> SplitIntoWords(string_view line){
  deque<std::string_view> res;
  size_t first = line.find_first_not_of(' ', 0);
  while (true) {                                                        // O(W), W - words count
    size_t space_pos = line.find(' ', first);                           // O(L), L string length
    res.emplace_back(line.substr(first, space_pos - first));            // O(1) amortized

    if (space_pos == line.npos){
      break;
    } else {
      first = line.find_first_not_of(' ', space_pos);
      if (first == line.npos)
        break;
    }
  }
  return res;
}

SearchServer::SearchServer(istream& document_input) {
  UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
  InvertedIndex new_index;

  for (string current_document; getline(document_input, current_document); ) {  //O(D), D - docs number
    new_index.Add(move(current_document));
  }
  
  // Lock index for updating
  {
    lock_guard<mutex> lock(m);
    swap(new_index, index);
  }
}

void SearchServer::AddQueriesStream(istream& query_input, ostream& search_results_output) {
  auto future = [&query_input, &search_results_output, this]() {
    vector<size_t> doc_rate(50'000);      // accumulate document hitcount
    vector<size_t> doc_id_found(50'000);  //accumulate doc ID which was meet

    for (string current_query; getline(query_input, current_query); ) {
      size_t counter = 0;                 // store number of found events

      for (const auto& word : SplitIntoWords(current_query)) {
        
        // Lock index for LookUp method
        vector<pair<size_t, size_t>> looking_in;
        {
          lock_guard<mutex> lockSearch(m);
          looking_in = index.Lookup(word);
        }

        for (const auto& [docid, hitcount] : looking_in) {
          if (doc_rate[docid] == 0){
            doc_id_found[counter++] = docid;
          }
          doc_rate[docid] += hitcount;
        }
      }

      vector<pair<size_t, size_t>> search_results;
      for (size_t docid = 0; docid < counter; ++docid) {
        size_t count = 0;
        size_t id = 0;
        std::swap(count, doc_rate[doc_id_found[docid]]);
        std::swap(id, doc_id_found[docid]);
        search_results.emplace_back(id, count);
      }

      partial_sort(
        begin(search_results),
        begin(search_results) + min<size_t>(5, search_results.size()),
        end(search_results),
        [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
          int64_t lhs_docid = lhs.first;
          auto lhs_hit_count = lhs.second;
          int64_t rhs_docid = rhs.first;
          auto rhs_hit_count = rhs.second;
          return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
        }
      );

      search_results_output << current_query << ':';
      for (auto [docid, hitcount] : Head(search_results, 5)) {
        search_results_output << " {"
          << "docid: " << docid << ", "
          << "hitcount: " << hitcount << '}';
      }
      search_results_output << endl;
    }
  };
  futures.push_back(std::async(future));
}

void InvertedIndex::Add(string&& document) {
  // vector.push_back() reallocation -> deque.push_back()
  // copy(string) constructor -> move(string)
  docs.push_back(move(document)); 

  const size_t docid = docs.size() - 1;
  for (const auto& word : SplitIntoWords(docs.back())) {
    // automaticly allocate new word
    auto& word_freq = frequency_index[word];
    if (word_freq.empty() || word_freq.back().first != docid){ 
      // If current word has never appeared or 
      // word doesn't have assotiation with current docID
      // Append new pair for word with {docID, hitpoint = 1}
      word_freq.emplace_back(docid, 1);
    } else {
      // If word was meet for this docID, increase hitpoint
      word_freq.back().second++;
    }
  }
}

vector<pair<size_t, size_t>> InvertedIndex::Lookup(const string_view word) const {
  if (auto it = frequency_index.find(word); it != frequency_index.end()) {
    return it->second;
  } else {
    return {};
  }
}
