#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "profile.h"
#include <set>

using namespace std;

class RouteManager {
public:
  void AddRoute(int start, int finish) {
    // reachable_lists_[start].push_back(finish);      // log(map)
    // reachable_lists_[finish].push_back(start);      // log(map)
    reachable_lists_[start].insert(finish);      // log(map) + log(set)
    reachable_lists_[finish].insert(start);      // log(map) + log(set)
  }
  int FindNearestFinish(int start, int finish) const {
    int result = abs(start - finish);
    if (reachable_lists_.count(start) < 1) {          // log(M)
        return result;
    }

    // const vector<int>& reachable_stations = reachable_lists_.at(start);
    const set<int>& reachable_stations = reachable_lists_.at(start);
    // -3  -2  -1  0  [1]  2  (3)  4
    // -3 (-2) -1  0  [1]  2   3   4
    const set<int>::const_iterator finish_lb = reachable_stations.lower_bound(finish);
    if (finish_lb != end(reachable_stations)){
      result = min(result, abs(finish - *finish_lb));
    }
    if (finish_lb != begin(reachable_stations)){
      result = min(result, abs(finish - *prev(finish_lb)) );
    }

    // if (!reachable_stations.empty()) {
    //   result = min(
    //       result,
    //       abs(finish - *min_element(
    //           begin(reachable_stations), end(reachable_stations),
    //           [finish](int lhs, int rhs) { return abs(lhs - finish) < abs(rhs - finish); }) // O(N) for min_element(vector<>, predicat)
    //       )
    //   );
    // }
    
    return result;
  }
private:
  // map<int, vector<int>> reachable_lists_;
  map<int, set<int>> reachable_lists_;
};


int main() {
  RouteManager routes;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int start, finish;
    cin >> start >> finish;
    if (query_type == "ADD") {
      routes.AddRoute(start, finish);
    } else if (query_type == "GO") {
      cout << routes.FindNearestFinish(start, finish) << "\n";
    }
  }

  return 0;
}