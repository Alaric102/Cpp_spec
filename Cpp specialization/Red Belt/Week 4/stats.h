#pragma once

#include "http_request.h"

#include <string_view>
#include <array>
#include <map>
#include <numeric>
using namespace std;

constexpr int GetHash(string_view line){
  int res = 0;
  for (auto ptr = line.data(); ptr < line.data() + line.size(); ptr++)
    res += (int)(*ptr);
  return res;
}

enum class Methods{
  GET = GetHash("GET"),
  PUT = GetHash("PUT"),
  POST = GetHash("POST"),
  DELETE = GetHash("DELETE")
};

enum class Uri{
  EMPTY = GetHash("/"),
  ORDER = GetHash("/order"),
  PRODUCT = GetHash("/product»"),
  BASKET = GetHash("/basket»"),
  HELP = GetHash("/help»")
};

class Stats {
public:
  Stats();

  void AddMethod(string_view method);

  void AddUri(string_view uri);

  const map<string_view, int>& GetMethodStats() const {
    return _methodsData;
  };

  const map<string_view, int>& GetUriStats() const {
    return _uriData;
  };

private:
  size_t GetCode(string_view line){
    switch (GetHash(line)) {
      case (int)Methods::GET:
        return 0;
      case (int)Methods::PUT:
        return 1;
      case (int)Methods::POST:
        return 2;
      case (int)Methods::DELETE:
        return 3;
      default:
        break;
    }
    return 4;
  }
  
  void CheckData(map<string_view, int>& dict, string_view line){
    auto it = dict.find(line);
    if (it == dict.end()){
      dict["UNKNOWN"]++;
    } else {
      *it++;
    }
  }

  map<string_view, int> _methodsData;
  map<string_view, int> _uriData;

  array<size_t, 5> _methods;
  array<size_t, 5> _uri;
};

HttpRequest ParseRequest(string_view line);

/*
Compile error: b"/usr/bin/ld: /tmp/framework-9b66fc.o: in function 
`ParseRequest(std::basic_string_view<char, std::char_traits<char> >)':
\nframework.cpp:(.text+0x50): multiple definition of 
`ParseRequest(std::basic_string_view<char, std::char_traits<char> >)';
 /tmp/stats-7db2c2.o:stats.cpp:(.text+0x0): first defined here\nclang: 
 fatal error: linker command failed with exit code 1 (use -v to see invocation)\n"
*/