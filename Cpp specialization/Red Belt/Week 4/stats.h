#pragma once

#include "http_request.h"

#include <string_view>
#include <array>
#include <map>
using namespace std;

class Stats {
public:
  void AddMethod(string_view method){};
  void AddUri(string_view uri){};
  const map<string_view, int>& GetMethodStats() const {
    return _data;
  };
  const map<string_view, int>& GetUriStats() const {
    return _data;
  };
private:
    map<string_view, int> _data;
};

HttpRequest ParseRequest(string_view line){
    HttpRequest res;
    size_t pos1 = 0, pos2;
    pos2 = line.find(' ', pos1);
    res.method = line.substr(pos1, pos2);
    pos1 = pos2 + 1;

    pos2 = line.find(' ', pos1);
    res.uri = line.substr(pos1, pos2);
    pos1 = pos2 + 1;
    
    pos2 = line.find(' ', pos1);
    res.protocol = line.substr(pos1, pos2);
    return res;
}