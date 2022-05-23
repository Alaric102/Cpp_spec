#include "stats.h"

Stats::Stats(){
    _methodsData = {
      {"GET", 0},
      {"PUT", 0},
      {"POST", 0},
      {"DELETE", 0},
      {"UNKNOWN", 0}
    };
    _uriData = {
      {"/", 0},
      {"/order", 0},
      {"/product", 0},
      {"/basket", 0},
      {"/help", 0},
      {"unknown", 0}
    };
}

void Stats::AddMethod(string_view method){
    auto it = _methodsData.find(method);
    if (it == _methodsData.end()){
      _methodsData["UNKNOWN"]++;
    } else {
      it->second++;
    }
}

void Stats::AddUri(string_view uri){
    auto it = _uriData.find(uri);
    if (it == _uriData.end()){
      _uriData["unknown"]++;
    } else {
      it->second++;
    }
}

HttpRequest ParseRequest(string_view line){
    HttpRequest res;
    size_t pos = line.rfind(' ');
    res.protocol = line.substr(pos + 1, line.npos);
    line = line.substr(0, pos);

    pos = line.rfind(' ');
    res.uri = line.substr(pos + 1, line.npos);
    line = line.substr(0, pos);

    pos = line.rfind(' ');
    res.method = line.substr(pos + 1, line.npos);
    return res;
}

